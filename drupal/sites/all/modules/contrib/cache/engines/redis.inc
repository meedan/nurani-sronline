<?php
// $Id: redis.inc,v 1.1.2.7 2009/08/16 14:40:07 doq Exp $

include dirname(__FILE__) .'/redis.php';

/**
 * Redis cache engine.
 *
 * http://code.google.com/p/redis/
 */
class redisCacheEngine extends CacheEngine {
  var $redis;

  /**
   * Implementation of getInfo().
   */
  static function getInfo() {
    return array(
      'name' => t('Redis'),
      'description' => t('Volatile key-value database wih support of lists and sets with atomic operations to push / pop elements.'),
      'site' => 'http://code.google.com/p/redis/',
    );
  }

  /**
   * @return TRUE if cache engine is available; FALSE otherwise.
   */
  function status() {
    if (!class_exists('Redis')) {
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
      'server' => array('localhost:6379'),
      'shared' => TRUE,
      'index' => 0,
      'clear' => FALSE,
      'bin_per_db' => FALSE,
    );

    assert(is_numeric($this->settings['index']));
  }

  function get($key) {
    assert(strlen($key) > 0);
  
    $cache = parent::get($key);
    if (isset($cache)) {
      return $cache;
    }

    $cache = $this->redis->get($this->key($key));
    if (strlen($cache) > 0) {
      $cache = unserialize($cache);
    }

    // Update static cache.
    parent::set($key, $cache);

    return $cache;
  }

  function set($key, $value, $expire = CACHE_PERMANENT, $headers = NULL) {
    // Create new cache object.
    $cache = new stdClass;
    $cache->cid = $key;
    $cache->created = time();
    $cache->expire = $expire;
    $cache->headers = $headers;
    $cache->data = $value;
    $cache->serialized = 0;

    $cache = serialize($cache);
    assert($cache != NULL);

    assert(strlen($key) > 0);

    if ($this->lock()) {
      if (!$this->settings['bin_per_db']) {
        // Get lookup table to be able to keep track of bins.
        $lookup = $this->redis->get($this->lookup);

        // If the lookup table is empty, initialize table.
        if (strlen($lookup) == 0) {
          $lookup = array();
        }
        else {
          $lookup = unserialize($lookup);
          assert(is_array($lookup));
        }

        // Set key to 1 so we can keep track of the bin.
        $lookup[$key] = $expire;
      }

      // Attempt to store full key and value.
      $ret = $this->redis->set($this->key($key), $cache);
//      $this->redis->expire($key, $expire);
      assert($ret == 'OK');
      if ($ret != 'OK') {
        unset($lookup[$key]);
        $return = FALSE;
      }
      else {
        // Update static cache.
        parent::set($key, $cache);
        $return = TRUE;
      }

      if (!$this->settings['bin_per_db']) {
        // Resave the lookup table (even on failure).
        /// @todo Use Redis lists here.
        $ret = $this->redis->set($this->lookup, serialize($lookup));
        assert($ret == 'OK');
      }

      // Remove lock.
      $this->unlock();

      return $return;
    }

    return FALSE;
  }

  function delete($key, $wildcard) {
    // Delete from static cache.
    parent::delete($key, $wildcard);

    $lookup = unserialize($this->redis->get($this->lookup));
    if (!is_array($lookup)) {
      return;
    }

    /// @todo This stuff should have lock also.
    if ($wildcard) {
      if ($key == '*') {
        foreach ($lookup as $k => $v) {
          $this->redis->delete($this->key($k));
          unset($lookup[$k]);
        }
      }
      else {
        foreach ($lookup as $k => $v) {
          if (0 == strncmp($k, $key, strlen($key))) {
            $this->redis->delete($this->key($k));
            unset($lookup[$k]);
          }
        }
      }
    }
    else {
      $this->redis->delete($this->key($key));
      unset($lookup[$key]);
    }

    if ($this->lock()) {
      $lookup_data = serialize($lookup);
      $this->redis->set($this->key($key), $lookup_data);
      $this->unlock();
    }
  }

  function flush($flush = 0) {
    $flush = !$flush ? time() : $flush;
    // Flush static cache.
    parent::flush();

    // If this is a shared cache, we need to cycle through the lookup
    // table and remove individual items directly.
    if (!$this->settings['bin_per_db']) {
      if ($this->lock()) {
        // Get lookup table to be able to keep track of bins.
        $lookup = $this->redis->get($this->lookup);

        // If the lookup table is empty, remove lock and return.
        if (strlen($lookup) == 0) {
          $this->unlock();
          return TRUE;
        }
        else {
          $lookup = unserialize($lookup);
          assert(is_array($lookup));
        }

        // Cycle through keys and remove each entry from the cache.
        foreach ($lookup as $k => $v) {
          if ($lookup[$k] != CACHE_PERMANENT && $lookup[$k] < $flush) {
            if ($this->redis->delete($this->key($k))) {
              unset($lookup[$k]);
            }
          }
        }

        // Resave the lookup table (even on failure).
        $this->redis->set($this->lookup, serialize($lookup));

        // Remove lock.
        $this->unlock();
      }
    }
    else {
      // Flush redis.
      /// @todo Fast implementation but not correct since removes even PERMANENT cache also.
      return $this->redis->flushdb($this->settings['index']);
    }
  }

  function lock() {
    if ($this->settings['shared']) {
      // Lock once by trying to add lock file, if we can't get the lock, we will loop
      // for 3 seconds attempting to get lock. If we still can't get it at that point,
      // then we give up and return FALSE.
      if (!$this->redis->set($this->lock, '', TRUE)) {
        $time = time();
        while (!$this->redis->set($this->lock, '', TRUE)) {
          if (time() - $time >= 3) {
            return FALSE;
          }
        }
      }
      return TRUE;
    }
    return TRUE;
  }

  function unlock() {
    if ($this->settings['shared']) {
      $ret = $this->redis->delete($this->lock);
      assert((int)$ret);
      return $ret;
    }
    return TRUE;
  }

  function connect() {
    $server = reset($this->settings['server']);
    list($host, $port) = explode(':', $server);
    /// @todo Add redis as static variable. Don't reconnect for every cache bin.
    $this->redis =& new Redis($host, $port);
    if (!$this->redis->connect()) {
      _cache_early_watchdog('cache', 'Unable to connect to Redis server %host:%port', array('%host' => $host, '%port' => $port), WATCHDOG_ERROR);
      return FALSE;
    }

    // Change redis database if not default (0) specified.
    if ($this->settings['index'] != 0) {
      if ($this->redis->select_db($this->settings['index']) != 'OK') {
        return FALSE;
      }
    }

    if ($this->settings['clear'] == TRUE) {
      /// @todo Add ability to clear only specified Redis database. e.g. when we don't want to clear cache_form bin.
      $this->redis->flushall();
    }

    return TRUE;
  }

  function close() {
    $this->redis->close();
  }

  /**
   * Statistics information.
   * @todo
   */
/*
  function stats() {
    $stats = array(
      'uptime' => time(),
      'bytes_used' => 0,
      'bytes_total' => 0,
      'gets' => 0,
      'sets' => 0,
      'hits' => 0,
      'misses' => 0,
      'req_rate' => 0,
      'hit_rate' => 0,
      'miss_rate' => 0,
      'set_rate' => 0,
    );
    return $stats;
  }
*/

  /**
   * Get the full key of the item.
   *
   * @param string $key
   *   The key to set.
   * @return string
   *   Returns the full key of the cache item.
   */
  function key($key) {
    $prefix = strlen($this->prefix) > 0 ? urlencode($this->prefix) .':' : '';
    return $prefix . urlencode($this->name) .':'. urlencode($key);
  }

}
