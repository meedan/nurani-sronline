<?php
// $Id: memcached.inc,v 1.1.2.1 2009/08/16 17:52:46 doq Exp $

/**
 * @file
 * Memcached caching engine.
 */

/**
 * Require latest stable version.
 */
define('PECL_MEMCACHED_VERSION', '1.0.0');

/**
 * Memcached caching engine.
 */
class memcachedCacheEngine extends CacheEngine {
  var $memcache;
  var $options = array();

  /**
   * Implementation of getInfo().
   */
  static function getInfo() {
    return array(
      'name' => t('Memcached'),
      'description' => t('Memcached caching based on memcached PECL extension.'),
      'site' => 'http://pecl.php.net/package/memcached',
    );
  }

  /**
   * @return TRUE if cache engine is available; FALSE otherwise.
   */
  function status() {
    if (!class_exists('Memcached')) {
      return FALSE;
    }

    if (!version_compare(phpversion('memcached'), PECL_MEMCACHED_VERSION, '>=')) {
      return FALSE;
    }

    return $this->connect();
  }

  function page_fast_cache() {
    return $this->fast_cache;
  }

  function __construct($settings) {
    parent::__construct($settings);

    // Add defaults.
    $this->settings += array(
      'server' => array('localhost:11211'),
      'compress' => FALSE,
      'shared' => TRUE,
      'clear' => FALSE,
      'flush_all' => FALSE,
      'check_connection' => TRUE,
    );

    if ($this->settings['compress']) {
      $this->options[Memcached::OPT_COMPRESSION] = TRUE;
    }
  }

  function get($key) {
    // Attempt to pull from static cache.
    $cache = parent::get($key);
    if (isset($cache)) {
      return $cache;
    }

    // Get from memcache.
    $cache = $this->memcache->get($this->key($key));

    // Update static cache.
    parent::set($key, $cache);

    return $cache;
  }

  function set($key, $value, $expire = CACHE_PERMANENT, $headers = NULL) {
    if ($expire != CACHE_PERMANENT && $expire != CACHE_TEMPORARY) {
      // This stuff can't be used since Drupal's minimum cache lifetime might
      // be changed sometime.
/*
      $ttl = $expire - time() + variable_get('cache_lifetime', 0);
      assert($ttl >= 0);
      if ($ttl >= 2592000) {
        $ttl = 2592000 - 1;
      }
*/
      $ttl = NULL;
    }
    else {
      $ttl = NULL;
    }

    // Create new cache object.
    $cache = new stdClass;
    $cache->cid = $key;
    $cache->created = time();
    $cache->expire = $expire;
    $cache->headers = $headers;
    $cache->data = $value;
    $cache->serialized = FALSE;

    assert(strlen($key) > 0);

    if ($this->lock()) {
      if (!$this->settings['flush_all']) {
        // Get lookup table to be able to keep track of bins.
        $lookup = $this->memcache->get($this->lookup);

        // If the lookup table is empty, initialize table.
        if (empty($lookup)) {
          $lookup = array();
        }

        // Set key to 1 so we can keep track of the bin.
        $lookup[$key] = $expire;
      }

      // Attempt to store full key and value.
      if (isset($ttl)) {
        $ret = $this->memcache->set($this->key($key), $cache, $ttl);
      }
      else {
        $ret = $this->memcache->set($this->key($key), $cache);
      }
      assert($ret);
      if (!$ret) {
        unset($lookup[$key]);
        $return = FALSE;
      }
      else {
        // Update static cache.
        parent::set($key, $cache);
        $return = TRUE;
      }

      if (!$this->settings['flush_all']) {
        // Resave the lookup table (even on failure).
        $ret = $this->memcache->set($this->lookup, $lookup);
        assert($ret);
      }

      // Remove lock.
      $this->unlock();

      return $return;
    }

    return FALSE;
  }


  function delete($key, $wildcard) {
    // Remove from static array cache.
    parent::delete($key, $wildcard);

    $lookup = $this->memcache->get($this->lookup);
    if (empty($lookup)) {
      return;
    }

    /// @todo This stuff should have lock also.
    if ($wildcard) {
      if ($key == '*') {
        foreach ($lookup as $k => $v) {
          $this->memcache->delete($this->key($k), 0);
          unset($lookup[$k]);
        }
      }
      else {
        foreach ($lookup as $k => $v) {
          if (0 == strncmp($k, $key, strlen($key))) {
            $this->memcache->delete($this->key($k), 0);
            unset($lookup[$k]);
          }
        }
      }
    }
    else {
      $this->memcache->delete($this->key($key), 0);
      unset($lookup[$key]);
    }

    if ($this->lock()) {
      $this->memcache->set($this->lookup, $lookup);
      $this->unlock();
    }
  }



  function flush($flush = 0) {
    $flush = !$flush ? time() : $flush;
    parent::flush();

    // If this is a shared cache, we need to cycle through the lookup table
    // and remove individual items directly.
    if (!$this->settings['flush_all']) {
      if ($this->lock()) {
        // Get lookup table to be able to keep track of bins.
        $lookup = $this->memcache->get($this->lookup);

        // If the lookup table is empty, remove lock and return.
        if (empty($lookup)) {
          $this->unlock();
          return TRUE;
        }

        // Cycle through keys and remove each entry from the cache.
        foreach ($lookup as $k => $v) {
          if ($lookup[$k] != CACHE_PERMANENT && $lookup[$k] < $flush) {
            if ($this->memcache->delete($this->key($k), 0)) {
              unset($lookup[$k]);
            }
          }
        }

        // Resave the lookup table (even on failure).
        $this->memcache->set($this->lookup, $lookup);

        // Remove lock.
        $this->unlock();
      }
    }
    else {
      // Flush memcache.
      return $this->memcache->flush();
    }
  }

  function lock() {
    $return = TRUE;
    if ($this->settings['shared']) {
      // Lock once by trying to add lock file, if we can't get the lock, we will loop
      // for 3 seconds attempting to get lock. If we still can't get it at that point,
      // then we give up and return FALSE.
      $count = 0;
      $time = time();
      do {
        if ($this->memcache->add($this->lock, 0, 2) === TRUE) {
          break;
        }
          // Sleep for 5 ms.
//          usleep(5 * 1000);
        ++$count;
        if (time() - $time >= 3) {
          $return = FALSE;
          break;
        }
      }
      while (TRUE);

      if ($count > 0) {
        if ($return) {
          // @todo format_plural?
          _cache_early_watchdog('cache', '%count times tried to add memcached lock variable.', array('%count' => $count), WATCHDOG_WARNING);
        }
        else {
          // @todo format_plural?
          _cache_early_watchdog('cache', '%count times tried to add memcached lock variable and failed.', array('%count' => $count), WATCHDOG_ERROR);
        }
      }
    }
    return $return;
  }

  function unlock() {
    if ($this->settings['shared']) {
      // Set timeout to zero because there is some bug that doesn't
      // set it to zero by default.
      $ret = $this->memcache->delete($this->lock, 0);
      assert($ret);
      return $ret;
    }
    return TRUE;
  }

  function connect() {
    /// @todo Add memcache as static variable. Don't reconnect for every cache bin.
    $this->memcache =& new Memcached;
    foreach ($this->settings['server'] as $server) {
      // Support UNIX sockets. Use the following format: 'unix:///path/to/socket:0'.
      /// @todo UNIX sockets are not supported with Memcached?
      $colon_pos = strrpos($server, ':');
      assert($colon_pos !== FALSE);
      $host = substr($server, 0, $colon_pos);
      $port = substr($server, $colon_pos + 1);
      /// @todo Use Memcached::addServers() here.
      if (!$this->memcache->addServer($host, $port)) {
        // watchdog() may be unavailable here.
        _cache_early_watchdog('cache', 'Unable to connect to memcached server %host:%port.', array('%host' => $host, '%port' => $port), WATCHDOG_ERROR);
        return FALSE;
      }

      foreach ($this->options as $key => $value) {
        $this->memcache->setOption($key, $value);
      }

      if ($this->settings['check_connection']) {
        // If this is a UNIX socket then error "Notice: MemcachePool::get(): Server unix://path/to/socket (tcp 0, udp 0) failed with: Permission denied (13)"
        // is possible. We should check permissions on that file. Looks like
        // Memcache::getServerStatus() not always returns FALSE in such case. My memcache extension version is 3.0.3.
        /// @todo Not supported.
        if (strncmp('unix:///', $host, 8) == 0) {
          // Port should be 0 when UNIX socket is specified.
          assert($port == 0);

          $file = substr($host, 7);
          if (!is_writable($file)) {
            // watchdog() may be unavailable here.
            _cache_early_watchdog('cache', 'Memcached server UNIX socket %socket is not writable.', array('%socket' => $host), WATCHDOG_ERROR);
            return FALSE;
          }
        }
        // The same problem appear with socket connections.
        else {
          if (FALSE == ($fp = @fsockopen($host, $port, $errno, $errstr))) {
            // watchdog() may be unavailable here.
            _cache_early_watchdog('cache', 'Connection to memcached server %host:%port failed: %errno, %error.', array('%host' => $host, '%port' => $port, '%errno' => $errno, '%error' => $errstr), WATCHDOG_ERROR);
            return FALSE;
          }
          fclose($fp);
        }
      }
      
      
      /// @todo Is only one memcache server enough to get variable from it?
    }

    if ($this->settings['clear'] == TRUE) {
      $this->memcache->flush();
    }

    return TRUE;
  }

  /**
   * Statistics information.
   */
  function stats() {
    $memcache_stats = $this->memcache->getStats();
    /// @todo We get statistics only of 1st server. What if there are several.
    $memcache_stats = reset($memcache_stats);
    
    $stats = array(
      'uptime' => $memcache_stats['uptime'],
      'bytes_used' => $memcache_stats['bytes'],
      'bytes_total' => $memcache_stats['limit_maxbytes'],
      'gets' => $memcache_stats['cmd_get'],
      'sets' => $memcache_stats['cmd_set'],
      'hits' => $memcache_stats['get_hits'],
      'misses' => $memcache_stats['get_misses'],
      'req_rate' => ($memcache_stats['cmd_get'] + $memcache_stats['cmd_set']) / $memcache_stats['uptime'],
      'hit_rate' => $memcache_stats['get_hits'] / $memcache_stats['uptime'],
      'miss_rate' => $memcache_stats['get_misses'] / $memcache_stats['uptime'],
      'set_rate' => $memcache_stats['cmd_set'] / $memcache_stats['uptime'],
    );
    return $stats;
  }

  function key($key) {
    $prefix = strlen($this->prefix) > 0 ? urlencode($this->prefix) .',' : '';
    $full_key = urlencode($prefix . $this->name .','. $key);
    // 250 is max length for key, tested on Memcached extension version 1.0.0.
    return strlen($full_key) > 250 ? urlencode($prefix . $this->name .',') . md5($key) : $full_key;
  }

  /**
   * @todo Add call to Memcached::getVersion to show server version.
   */
  static function requirements() {
    if (class_exists('Memcached')) {
      if (version_compare(phpversion('memcached'), PECL_MEMCACHED_VERSION, '>=')) {
        $requirements['memcached']['severity'] = REQUIREMENT_OK;
        $requirements['memcached']['value'] = l(phpversion('memcached'), 'admin/reports/status/php', array('fragment' => 'module_memcached'));
      }
      else {
        $requirements['memcached'] = array(
          'value' => l(phpversion('memcached'), 'admin/reports/status/php', array('fragment' => 'module_memcached')),
          'severity' => REQUIREMENT_ERROR,
          'description' => t('The Memcached extension version %version is required. Please check the <a href="@url">PHP Memcached documentation</a> for information on how to correct this.', array('%version' => PECL_MEMCACHED_VERSION, '@url' => 'http://www.php.net/manual/en/memcached.setup.php')),
        );
      }
    }
    else {
      $requirements['memcached'] = array(
        'value' => t('Not installed'),
        'severity' => REQUIREMENT_ERROR,
        'description' => t('The Memcached extension for PHP is disabled. Please check the <a href="@url">PHP Memcached documentation</a> for information on how to correct this.', array('@url' => 'http://www.php.net/manual/en/memcached.setup.php')),
      );
    }
    $requirements['memcached']['title'] = t('Memcached extension');

    $zlib = phpversion('zlib');
    if ($zlib) {
      $requirements['memcached_zlib']['severity'] = REQUIREMENT_OK;
      $requirements['memcached_zlib']['value'] = l(t('Enabled'), 'admin/reports/status/php', array('fragment' => 'module_zlib'));
    }
    else {
      $requirements['memcached_zlib'] = array(
        'value' => t('Disabled'),
        'severity' => REQUIREMENT_WARNING,
        'description' => t('ZLIB compression was not enabled. Memcached get / set operations will fail when <code>Memcached::OPT_COMPRESSION</code> flag will be used.'),
      );
    }
    $requirements['memcached_zlib']['title'] = t('ZLIB compression');
    return $requirements;
  }

}
