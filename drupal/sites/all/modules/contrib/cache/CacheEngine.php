<?php
// $Id: CacheEngine.php,v 1.1.2.10 2009/08/16 14:40:07 doq Exp $

/**
 * This function can be then called by cache module
 * and it will run watchdog entries through watchdog() function.
 */
function _cache_early_watchdog($type = FALSE) {
  static $watchdog = array();

  if ($type === FALSE) {
    if (count($watchdog) > 0) {
      foreach ($watchdog as $entry) {
        call_user_func_array('watchdog', $entry);
      }
      // Clear array.
      $watchdog = array();
    }
  }
  else {
    $watchdog[] = func_get_args();
  }
}

/**
 * Base cache engine class.
 *
 * @todo Consider separating class into CacheBin class and CacheEngine interface.
 */
abstract class CacheEngine {
  /**
   * Caching engine settings.
   */
  var $settings = array();

  /**
   * Key/value pairs cached when $this->static is set to TRUE.
   */
  var $content = array();

  /**
   * Unique web-site prefix. Use for multisite environment.
   */
  var $prefix = '';

  /**
   * Name of bin (table), e.g. cache, cache_page, cache_form etc.
   */
  var $name = NULL;

  /**
   * Lookup key name. This key will contain array of all variables
   * set for current bin using this caching engine.
   */
  var $lookup = '';

  /**
   * Lock key name. Special key that is set to prevent concurrent
   * writes.
   */
  var $lock = '';

  /**
   * Whether page_fast_cache feature is turned on / off.
   */
  var $fast_cache = TRUE;

  /**
   * If TRUE then also cache fetched values in $this->content variable. Might
   * increase performance when enabled for cache_path_alias, cache_path_source
   * cache bins.
   */
  var $static = FALSE;

  function __construct($settings) {
    $this->settings = $settings;

    // Add defaults.
    $this->settings += array(
      'prefix' => '',
      'static' => FALSE,
      'fast_cache' => TRUE,
    );

    $this->prefix = $this->settings['prefix'];
    $this->name = $this->settings['bin'];
    $this->static = $this->settings['static'];
    $this->fast_cache = $this->settings['fast_cache'];

    // Setup prefixed lookup and lock table names for shared storage.
    $prefix = strlen($this->prefix) > 0 ? $this->prefix .',' : '';
    $this->lookup = $prefix .'lookup,'. $this->name;
    $this->lock = $prefix .'lock,'. $this->name;
  }

  function get($key) {
    if ($this->static && isset($this->content[$key])) {
      return $this->content[$key];
    }
  }

  function set($key, $value) {
    if ($this->static) {
      $this->content[$key] = $value;
    }
  }

  function delete($key, $wildcard) {
    if ($this->static) {
      if ($key == '*') {
        // Delete all caches.
        $this->content = array();
      }
      else if (substr($key, -1, 1) == '*') {
        $len = strlen($key) - 1;
        foreach ($this->content as $k => $v) {
          if (0 == strncmp($key, $k, $len)) {
            unset($this->content[$k]);
          }
        }
      }
      else {
        unset($this->content[$key]);
      }
    }
  }

  function flush() {
    if ($this->static) {
      $this->content = array();
    }
  }

  /**
   * Get the full key of the item.
   *
   * @param string $key
   *   The key to set.
   * @return string
   *   Returns the full key of the cache item.
   */
  function key($key) {
    $prefix = strlen($this->prefix) > 0 ? $this->prefix .',' : '';
    return urlencode($prefix . $this->name .','. $key);
  }

  /**
   * Implementation of getInfo().
   */
  static abstract function getInfo();

  /**
   * Cache engine requirements.
   */
  static function requirements() {
    // By default no requirements.
    return array();
  }

  /**
   * Statistics information.
   */
  function stats() {
    return NULL;
  }

}
