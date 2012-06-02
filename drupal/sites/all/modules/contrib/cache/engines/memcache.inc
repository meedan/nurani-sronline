<?php
// $Id: memcache.inc,v 1.1.2.7 2009/08/16 13:33:24 doq Exp $

/**
 * @file
 * Memcache caching engine.
 */

/**
 * Memcache PECL version required for memcache caching engine to work
 * properly.
 *
 * According to http://drupal.org/project/memcache - memcache PECL package (2.2.1)
 * (or a higher 2.2.x version) required to avoid a bug with deletes not happening.
 *
 * Cache module requires memcache version 2.1.0 API, but we will check for 2.2.1
 * like memcache module suggests.
 */
define('PECL_MEMCACHE_VERSION', '2.2.1');

/**
 * Memcache caching engine.
 */
class memcacheCacheEngine extends CacheEngine {
  var $memcache;
  var $flags = 0;

  /**
   * Implementation of getInfo().
   */
  static function getInfo() {
    return array(
      'name' => t('Memcache'),
      'description' => t('Memcached caching.'),
      'site' => 'http://www.danga.com/memcached/',
    );
  }

  /**
   * @return TRUE if cache engine is available; FALSE otherwise.
   */
  function status() {
    if (!class_exists('Memcache')) {
      return FALSE;
    }

    if (!version_compare(phpversion('memcache'), PECL_MEMCACHE_VERSION, '>=')) {
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
      $this->flags |= MEMCACHE_COMPRESSED;
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
        $ret = $this->memcache->set($this->key($key), $cache, $this->flags, $ttl);
      }
      else {
        $ret = $this->memcache->set($this->key($key), $cache, $this->flags);
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
        $ret = $this->memcache->set($this->lookup, $lookup, $this->flags);
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
      $this->memcache->set($this->lookup, $lookup, $this->flags);
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
        $this->memcache->set($this->lookup, $lookup, $this->flags, 0);

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
        if ($this->memcache->add($this->lock, $this->flags, 0, 2) === TRUE) {
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
          _cache_early_watchdog('cache', '%count times tried to add memcache lock variable.', array('%count' => $count), WATCHDOG_WARNING);
        }
        else {
          // @todo format_plural?
          _cache_early_watchdog('cache', '%count times tried to add memcache lock variable and failed.', array('%count' => $count), WATCHDOG_ERROR);
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
    $this->memcache =& new Memcache;
    foreach ($this->settings['server'] as $server) {
      // Support UNIX sockets. Use the following format: 'unix:///path/to/socket:0'.
      $colon_pos = strrpos($server, ':');
      assert($colon_pos !== FALSE);
      $host = substr($server, 0, $colon_pos);
      $port = substr($server, $colon_pos + 1);
      if (!$this->memcache->addServer($host, $port) || !$this->memcache->getServerStatus($host, $port)) {
        // watchdog() may be unavailable here.
        _cache_early_watchdog('cache', 'Unable to connect to memcache server %host:%port.', array('%host' => $host, '%port' => $port), WATCHDOG_ERROR);
        return FALSE;
      }

      if ($this->settings['check_connection']) {
        // If this is a UNIX socket then error "Notice: MemcachePool::get(): Server unix://path/to/socket (tcp 0, udp 0) failed with: Permission denied (13)"
        // is possible. We should check permissions on that file. Looks like
        // Memcache::getServerStatus() not always returns FALSE in such case. My memcache extension version is 3.0.3.
        if (strncmp('unix:///', $host, 8) == 0) {
          // Port should be 0 when UNIX socket is specified.
          assert($port == 0);

          $file = substr($host, 7);
          if (!is_writable($file)) {
            // watchdog() may be unavailable here.
            _cache_early_watchdog('cache', 'Memcache server UNIX socket %socket is not writable.', array('%socket' => $host), WATCHDOG_ERROR);
            return FALSE;
          }
        }
        // The same problem appear with socket connections.
        else {
          if (FALSE == ($fp = @fsockopen($host, $port, $errno, $errstr))) {
            // watchdog() may be unavailable here.
            _cache_early_watchdog('cache', 'Connection to memcache server %host:%port failed: %errno, %error.', array('%host' => $host, '%port' => $port, '%errno' => $errno, '%error' => $errstr), WATCHDOG_ERROR);
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

  function close() {
    $this->memcache->close();
  }

  /**
   * Statistics information.
   */
  function stats() {
    $memcache_stats = $this->memcache->getStats();
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
/*
  function key($key) {
    $prefix = strlen($this->prefix) > 0 ? urlencode($this->prefix) .',' : '';
    $full_key = urlencode($prefix . $this->name .','. $key);
    // Memcache truncates keys longer than 250
    // characters: http://drupal.org/node/525400
    return strlen($full_key) > 250 ? urlencode($prefix . $this->name .',') . md5($key) : $full_key;
  }
*/

  /**
   * @todo Add call to Memcache::getVersion to show server version.
   */
  static function requirements() {
    if (class_exists('Memcache')) {
      if (version_compare(phpversion('memcache'), PECL_MEMCACHE_VERSION, '>=')) {
        $requirements['memcache']['severity'] = REQUIREMENT_OK;
        $requirements['memcache']['value'] = l(phpversion('memcache'), 'admin/reports/status/php', array('fragment' => 'module_memcache'));
      }
      else {
        $requirements['memcache'] = array(
          'value' => l(phpversion('memcache'), 'admin/reports/status/php', array('fragment' => 'module_memcache')),
          'severity' => REQUIREMENT_ERROR,
          'description' => t('The Memcache extension version %version is required. Please check the <a href="@url">PHP Memcache documentation</a> for information on how to correct this.', array('%version' => PECL_MEMCACHE_VERSION, '@url' => 'http://www.php.net/manual/en/memcache.setup.php')),
        );
      }
    }
    else {
      $requirements['memcache'] = array(
        'value' => t('Not installed'),
        'severity' => REQUIREMENT_ERROR,
        'description' => t('The Memcache extension for PHP is disabled. Please check the <a href="@url">PHP Memcache documentation</a> for information on how to correct this.', array('@url' => 'http://www.php.net/manual/en/memcache.setup.php')),
      );
    }
    $requirements['memcache']['title'] = t('Memcache extension');

    $zlib = phpversion('zlib');
    if ($zlib) {
      $requirements['zlib']['severity'] = REQUIREMENT_OK;
      $requirements['zlib']['value'] = l(t('Enabled'), 'admin/reports/status/php', array('fragment' => 'module_zlib'));
    }
    else {
      $requirements['zlib'] = array(
        'value' => t('Disabled'),
        'severity' => REQUIREMENT_WARNING,
        'description' => t('ZLIB compression was not enabled. Memcache get / set operations will fail when <code>MEMCACHE_COMPRESSED</code> flag will be used.'),
      );
    }
    $requirements['zlib']['title'] = t('ZLIB compression');
    return $requirements;
  }

}
