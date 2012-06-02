<?php
// $Id: null.inc,v 1.1.2.4 2009/08/16 14:40:07 doq Exp $

/**
 * Disable caching.
 *
 * This engine should not be used on production.
 * It only might be useful for development.
 */
class nullCacheEngine extends CacheEngine {
  /**
   * Implementation of getInfo().
   */
  static function getInfo() {
    return array(
      'name' => t('No caching'),
      'description' => t('Disable caching for specified cache bin.'),
    );
  }

  function page_fast_cache() {
    return FALSE;
  }

  function status() {
    return TRUE;
  }

  function get() {
    // Do nothing.
    return 0;
  }

  function set() {
    // Do nothing.
  }

  function delete() {
    // Do nothing.
  }

  function flush() {
    // Do nothing.
  }

  function gc() {
    // Do nothing.
  }

  /**
   * Statistics information.
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
