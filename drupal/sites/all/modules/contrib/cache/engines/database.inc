<?php
// $Id: database.inc,v 1.1.2.5 2009/08/16 14:40:07 doq Exp $

/**
 * Database cache engine.
 */
class databaseCacheEngine extends CacheEngine {
  /**
   * Implementation of getInfo().
   */
  static function getInfo() {
    return array(
      'name' => t('Database'),
      'description' => t('Alternative database cache handler.'),
      'site' => 'http://drupal.org/',
    );
  }

  /**
   * @return
   *   TRUE if cache engine is available; FALSE otherwise.
   */
  function status() {
    // Always available.
    return TRUE;
  }

  function page_fast_cache() {
    return FALSE;
  }

  function get($key) {
    $cache = db_fetch_object(db_query("SELECT data, created, headers, expire, serialized FROM {". $this->name ."} WHERE cid = '%s'", $key));
    if (isset($cache->data)) {
      $cache->data = db_decode_blob($cache->data);
    }
    return $cache;
  }
  
  function set($key, $value, $expire = CACHE_PERMANENT, $headers = NULL) {
    $serialized = 0;
    if (is_object($value) || is_array($value)) {
      $value = serialize($value);
      $serialized = 1;
    }
    $created = time();
    db_query("UPDATE {". $this->name ."} SET data = %b, created = %d, expire = %d, headers = '%s', serialized = %d WHERE cid = '%s'", $value, $created, $expire, $headers, $serialized, $key);
    if (!db_affected_rows()) {
      @db_query("INSERT INTO {". $this->name ."} (cid, data, created, expire, headers, serialized) VALUES ('%s', %b, %d, %d, '%s', %d)", $key, $value, $created, $expire, $headers, $serialized);
    }
  }

  function delete($key, $wildcard) {
    if ($wildcard) {
      if ($key == '*') {
        db_query("DELETE FROM {". $this->name ."}");
      }
      else {
        db_query("DELETE FROM {". $this->name ."} WHERE cid LIKE '%s%%'", $key);
      }
    }
    else {
      db_query("DELETE FROM {". $this->name ."} WHERE cid = '%s'", $key);
    }
  }

  function flush($flush = 0) {
    $flush = !$flush ? time() : $flush;
    db_query("DELETE FROM {". $this->name ."} WHERE expire != %d AND expire < %d", CACHE_PERMANENT, $flush);
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
}
