<?php
// $Id: xcache.inc,v 1.1.2.7 2009/08/16 14:40:07 doq Exp $

/**
 * @file
 *
 */

/**
 * XCache cache engine.
 */
class xcacheCacheEngine extends CacheEngine {
  /**
   * Implementation of getInfo().
   */
  static function getInfo() {
    return array(
      'name' => t('XCache'),
      'description' => t('XCache PHP op-code and variable caching.'),
      'site' => 'http://xcache.org/',
    );
  }

  /**
   * @return
   *   TRUE if cache engine is available; FALSE otherwise.
   */
  function status() {
    return function_exists('xcache_get');
  }

  /**
   *
   */
  function page_fast_cache() {
    return $this->fast_cache;
  }
  
  /**
   * Return item from cache if it is available.
   *
   * @param string $key
   *   The key to fetch.
   * @return mixed object|bool
   *   Returns either the cache object or FALSE on failure
   */
  function get($key) {
    $cache = parent::get($key);
    if (isset($cache)) {
      return $cache;
    }

    // Get item from cache.
    $cache = unserialize(xcache_get($this->key($key)));

    // Update static cache.
    parent::set($key, $cache);

    return $cache;
  }

  /**
   * Add item into cache.
   *
   * @param string $key
   *   The key to set.
   * @param string $value
   *   The data to store in the cache.
   * @param string $expire
   *   The time to expire in seconds.
   * @param string $headers
   *   The page headers.
   * @return bool
   *   Returns TRUE on success or FALSE on failure
   */
  function set($key, $value, $expire = CACHE_PERMANENT, $headers = NULL) {
    if ($expire != CACHE_PERMANENT && $expire != CACHE_TEMPORARY) {
      //$ttl = $expire - time();
      //assert($ttl >= 0);
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

    $data = serialize($cache);

    if (!empty($key) && $this->lock()) {
      // Get lookup table to be able to keep track of bins.
      $lookup = unserialize(xcache_get($this->lookup));

      // If the lookup table is empty, initialize table.
      if (empty($lookup)) {
        $lookup = array();
      }

      // Set key to $expire so we can keep track of the bin.
      $lookup[$key] = $expire;

      // Attempt to store full key and value
      if (isset($ttl)) {
        $result = xcache_set($this->key($key), $data, $ttl);
      }
      else {
        $result = xcache_set($this->key($key), $data);
      }
      if (!$result) {
        unset($lookup[$key]);
        $return = FALSE;
      }
      else {
        // Update static cache
        parent::set($key, $cache);
        $return = TRUE;
      }

      // Resave the lookup table (even on failure)
      $lookup_data = serialize($lookup);
      xcache_set($this->lookup, $lookup_data);

      // Remove lock.
      $this->unlock();
    }

    return $return;
  }

  /**
   * Remove item from cache.
   *
   * @param string $key
   *   The key to set.
   * @return mixed object|bool
   *   Returns either the cache object or FALSE on failure
   */
  function delete($key, $wildcard) {
    // Remove from static array cache.
    parent::delete($key, $wildcard);

    $lookup = unserialize(xcache_get($this->lookup));
    if (!is_array($lookup)) {
      return;
    }

    /// @todo This stuff should have lock also.
    if ($wildcard) {
      if ($key == '*') {
        foreach ($lookup as $k => $v) {
          xcache_unset($this->key($k));
          unset($lookup[$k]);
        }
      }
      else {
        foreach ($lookup as $k => $v) {
          if (0 == strncmp($k, $key, strlen($key))) {
            xcache_unset($this->key($k));
            unset($lookup[$k]);
          }
        }
      }
    }
    else {
      xcache_unset($this->key($key));
      unset($lookup[$key]);
    }

    if ($this->lock()) {
      $lookup_data = serialize($lookup);
      xcache_set($this->lookup, $lookup_data);
      $this->unlock();
    }
  }

  /**
   * Flush the entire cache.
   *
   * @param none
   * @return mixed bool
   *   Returns TRUE
   */
  function flush($flush = 0) {
    $flush = !$flush ? time() : $flush;
    parent::flush();
    if ($this->lock()) {
      // Get lookup table to be able to keep track of bins.
      $lookup = unserialize(xcache_get($this->lookup));

      // If the lookup table is empty, remove lock and return.
      if (empty($lookup)) {
        $this->unlock();
        return TRUE;
      }

      // Cycle through keys and remove each entry from the cache.
      foreach ($lookup as $k => $v) {
        if ($lookup[$k] != CACHE_PERMANENT && $lookup[$k] < $flush) {
          if (xcache_unset($this->key($k))) {
            unset($lookup[$k]);
          }
        }
      }

      // Resave the lookup table (even on failure).
      $lookup_data = serialize($lookup);
      xcache_set($this->lookup, $lookup_data);

      // Remove lock.
      $this->unlock();
    }
    return TRUE;
  }

  /**
   * lock()
   *   lock the cache from other writes.
   *
   * @param none
   * @return string
   *   Returns TRUE on success, FALSE on failure
   */
  function lock() {
    // Lock once by trying to add lock file, if we can't get the lock, we will loop
    // for 3 seconds attempting to get lock.  If we still can't get it at that point,
    // then we give up and return FALSE.
    if (xcache_isset($this->lock) === TRUE) {
      $time = time();
      while (xcache_isset($this->lock) === TRUE) {
        if (time() - $time >= 3) {
          return FALSE;
        }
      }
    }
    $data = serialize(TRUE);
    xcache_set($this->lock, $data);
    return TRUE;
  }

  /**
   * unlock()
   *   lock the cache from other writes.
   *
   * @param none
   * @return bool
   *   Returns TRUE on success, FALSE on failure
   */
  function unlock() {
    return xcache_unset($this->lock);
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
}
