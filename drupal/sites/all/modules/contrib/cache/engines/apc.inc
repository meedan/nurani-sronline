<?php
// $Id: apc.inc,v 1.1.2.7 2009/08/16 14:40:07 doq Exp $

/**
 * @file
 *
 */

/**
 * APC cache engine.
 */
class apcCacheEngine extends CacheEngine {
  /**
   * Implementation of getInfo().
   */
  static function getInfo() {
    return array(
      'name' => t('APC'),
      'description' => t('Alternative PHP cache.'),
      'site' => 'http://pecl.php.net/package/APC',
    );
  }

  /**
   * @return
   *   TRUE if cache engine is available; FALSE otherwise.
   */
  function status() {
    return function_exists('apc_fetch');
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
    $cache = unserialize(apc_fetch($this->key($key)));

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

    $return = FALSE;

    if (!empty($key) && $this->lock()) {
      // Get lookup table to be able to keep track of bins.
      $lookup = unserialize(apc_fetch($this->lookup));

      // If the lookup table is empty, initialize table.
      if (empty($lookup)) {
        $lookup = array();
      }

      // Set key to $expire so we can keep track of the bin.
      $lookup[$key] = $expire;

      // Attempt to store full key and value
      if (isset($ttl)) {
        $result = apc_fetch($this->key($key), $data, $ttl);
      }
      else {
        $result = apc_store($this->key($key), $data);
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
      apc_store($this->lookup, $lookup_data);

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

    $lookup = unserialize(apc_fetch($this->lookup));
    if (!is_array($lookup)) {
      return;
    }

    /// @todo This stuff should have lock also.
    if ($wildcard) {
      if ($key == '*') {
        foreach ($lookup as $k => $v) {
          apc_delete($this->key($k));
          unset($lookup[$k]);
        }
      }
      else {
        foreach ($lookup as $k => $v) {
          if (0 == strncmp($k, $key, strlen($key))) {
            apc_delete($this->key($k));
            unset($lookup[$k]);
          }
        }
      }
    }
    else {
      apc_delete($this->key($key));
      unset($lookup[$key]);
    }

    if ($this->lock()) {
      $lookup_data = serialize($lookup);
      apc_store($this->lookup, $lookup_data);
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
      $lookup = unserialize(apc_fetch($this->lookup));

      // If the lookup table is empty, remove lock and return.
      if (empty($lookup)) {
        $this->unlock();
        return TRUE;
      }

      // Cycle through keys and remove each entry from the cache.
      foreach ($lookup as $k => $v) {
        if ($lookup[$k] != CACHE_PERMANENT && $lookup[$k] < $flush) {
          if (apc_delete($this->key($k))) {
            unset($lookup[$k]);
          }
        }
      }

      // Resave the lookup table (even on failure).
      $lookup_data = serialize($lookup);
      apc_store($this->lookup, $lookup_data);

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
    static $new_apc;
    if (!isset($new_apc)) {
      $new_apc = function_exists('apc_add');
    }

    if ($new_apc) {
      // Lock once by trying to add lock file, if we can't get the lock, we will loop
      // for 3 seconds attempting to get lock. If we still can't get it at that point,
      // then we give up and return FALSE.
      if (apc_add($this->lock, TRUE) === FALSE) {
        $time = time();
        while (apc_add($this->lock, TRUE) === FALSE) {
          if (time() - $time >= 3) {
            return FALSE;
          }
        }
      }
    }
    else {
      // For older versions of APC (before 3.0.13).
      $time = time();
      while (apc_fetch($this->lock)) {
        if (time() - $time >= 3) {
          return FALSE;
        }
      }
      apc_store($this->lock, TRUE);
    }

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
    return apc_delete($this->lock);
  }

  /**
   * Statistics information.
   * @todo
   */
  /*
  function stats() {
    $stats = array(
    );
    return $stats;
  }
  */

  static function requirements() {
    if (!function_exists('apc_fetch')) {
      $requirements['apc'] = array(
        'value' => t('Not installed'),
        'severity' => REQUIREMENT_ERROR,
        'description' => t('The APC extension for PHP is disabled. Please check the <a href="@url">PHP APC documentation</a> for information on how to correct this.', array('@url' => 'http://www.php.net/manual/en/apc.setup.php')),
      );
    }
    else {
      //$shm_segments = ini_get('apc.shm_segments');
      //$shm_size = ini_get('apc.shm_size');
      // Get size in bytes to be used in format_size() function.
      //$shm_size *= 1024 * 1024;
      $mem = apc_sma_info();

      $text1 = format_plural($mem['num_seg'], '1 shared memory segment allocated for the compiler cache.', '%count shared memory segments allocated for the compiler cache.');
      $text2 = t('The size of each shared memory segment: %size.', array('%size' => format_size($mem['seg_size'])));
      $requirements['apc'] = array(
        'value' => l(phpversion('apc'), 'admin/reports/status/php', array('fragment' => 'module_apc')),
        'severity' => REQUIREMENT_OK,
        'description' => $text1 .' '. $text2,
      );
    }
    $requirements['apc']['title'] = t('APC extension');
    return $requirements;
  }

}
