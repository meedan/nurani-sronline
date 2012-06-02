<?php
// $Id: file.inc,v 1.1.2.9 2009/08/16 13:33:24 doq Exp $

/**
 * File cache engine.
 */
class fileCacheEngine extends CacheEngine {
  var $fspath = '/tmp/filecache';
  var $msft_invalid_file_characters = array('?', '*', '/', '\\', ':', ';', '<', '>');

  /**
   * Implementation of getInfo().
   */
  static function getInfo() {
    return array(
      'name' => t('File'),
      'description' => t('Caching into files.'),
    );
  }

  /**
   * @return
   *   TRUE if cache engine is available; FALSE otherwise.
   */
  function status() {
    return TRUE;
  }

  function page_fast_cache() {
    return $this->fast_cache;
  }

  function __construct($settings) {
    parent::__construct($settings);

    if (isset($this->settings['path'])) {
      $this->fspath = $this->settings['path'];
    }
  }

  
  function get($key) {
    $cache = NULL;
    $cache_file = $this->key($key);

    if (file_exists($cache_file)) {
      if ($fp = fopen($cache_file, 'r')) {
        if (flock($fp, LOCK_SH)) {
          $data = fread($fp, filesize($cache_file));
          assert(strlen($data) == filesize($cache_file));
          flock($fp, LOCK_UN);
          $cache = unserialize($data);
        }
        fclose($fp);
      }
    }
    return $cache;
  }
  
  function set($key, $value, $expire = CACHE_PERMANENT, $headers = NULL) {
    static $subdirectories;

    $cache = new stdClass;
    $cache->cid = $key;
    $cache->created = time();
    $cache->expire = $expire;
    $cache->headers = $headers;
    $cache->data = $value;
    $cache->serialized = FALSE;

    $data = serialize($cache);

    assert(strlen($key) > 0);

    $file = $this->key($key);
    if ($fp = @fopen($file, 'a')) {
      // Only write to the cache file if we can obtain an exclusive lock.
      if (flock($fp, LOCK_EX)) {
        ftruncate($fp, 0);
        fwrite($fp, $data);
        flock($fp, LOCK_UN);
      }
      fclose($fp);

      chmod($file, 0664); // Necessary for non-webserver users.

      if ($expire == CACHE_PERMANENT) {
        touch($file, 1000);
      }
    }
    else {
      _early_cache_watchdog('cache', 'Cache write error, failed to open file %file.', array('%file' => $file), WATCHDOG_ERROR);
    }
  }
  
  function delete($key, $wildcard) {
    // Remove from static array cache.
    parent::delete($key, $wildcard);

    if ($wildcard) {
      if ($key == '*') {
        $fspath = $this->fspath;
        $files = file_scan_directory($fspath .'/'. $this->name, '.*', array('.', '..', 'CVS')/*, 0, FALSE*/);
        foreach ($files as $file) {
          if ($fp = fopen($file->filename, 'a')) {
            // Only delete the cache file once we obtain an exclusive lock to prevent
            // deleting a cache file that is currently being read.
            if (flock($fp, LOCK_EX)) {
              unlink($file->filename);
            }
          }
        }
      }
      else {
        $fspath = $this->fspath;

        // Change characters that MSFT hates to dash.
        $key = str_replace($this->msft_invalid_file_characters, '-', $key);

        $filename = '--'. $key;
        /// @todo 255 should be configurable in case e.g. reiserfs is used.
        $this->truncate_filename($filename, 255 - strlen(md5('test')));

        $filename = quotemeta($filename);

        // Filename: abcdef12345verylongmd5code--content:123456:987654
        $files = file_scan_directory($fspath .'/'. $this->name, ".$filename.", array('.', '..', 'CVS')/*, 0, FALSE*/);
        foreach ($files as $file) {
          if ($fp = fopen($file->filename, 'a')) {
            // Only delete the cache file once we obtain an exclusive lock to prevent
            // deleting a cache file that is currently being read.
            if (flock($fp, LOCK_EX)) {
              unlink($file->filename);
            }
          }
        }
      }
    }
    else {
      $file = $this->key($key);
      if (file_exists($file) && ($fp = fopen($file, 'a'))) {
        // only delete the cache file once we obtain an exclusive lock to prevent
        // deleting a cache file that is currently being read.
        if (flock($fp, LOCK_EX)) {
          unlink($file);
        }
      }
    }

  }
  
  function flush($flush = 0) {
    $flush = !$flush ? time() : $flush;
    
    $table = $this->name;
    $fspath = $this->fspath;
    
    $ivalfrom = ord("a");
    $ivalto = ord("f");
    
    for ($i = $ivalfrom; $i <= $ivalto; ++$i) {
      $this->purge("$fspath/$table/". chr($i), $flush);
    }

    for ($i = 0; $i < 10; ++$i) {
      $this->purge("$fspath/$table/". $i, $flush);
    }
  }
  
  function key($key) {
    $table = $this->name;
    $fspath = $this->fspath;// . ((strlen($this->prefix)) > 0 ? '/'. $this->prefix : '');

    // Make sure we have a good filename when we concatentate $hash with $appendix:
    // * Can't be over 255 bytes (ext2, 3, 4) or 255 characters (NTFS, FAT) as per
    //  http://en.wikipedia.org/wiki/Comparison_of_file_systems#Limits
    // * Can't include "? * / \ : ; < >" in NTFS and FAT as per
    //  http://technet.microsoft.com/en-us/library/cc722482.aspx

    $hash = md5($key);

    // Change characters that MSFT hates to dash.
    $appendix = str_replace($this->msft_invalid_file_characters, '-', $key);

    $filename = $hash .'--'. $appendix;
    /// @todo 255 should be configurable in case e.g. reiserfs is used.
    /// @todo This truncation might cause problems when flushing cache - several files with the same beginning will be deleted.
    $this->truncate_filename($filename, 255);

    $this->create_directory($fspath, $hash{0});
    
    return "$fspath/$table/". $hash{0} .'/'. $filename;
  }
  
  /**
   * Create the necessary $table directory and/or letter/number subdirectory if
   * it doesn't exist.  We store the directories we've created in a static 
   * so we don't bother doing an fstat on that more than one time per page load.
   */
  function create_directory($fspath, $hash) {
    static $dirs = array();
    $table = $this->name;
    
    $create = array($fspath, "$fspath/$table", "$fspath/$table/$hash");

    foreach ($create as $dir) {
      $dir = rtrim($dir, '/\\');
      // Check the static $dirs to avoid excessive fstats.
      if (!isset($dirs[$dir])) {
        $dirs[$dir] = 1;
        if (!is_dir($dir)) {
          if (!mkdir($dir)) {
            _early_cache_watchdog('cache', 'Failed to create directory %dir.', array('%dir' => $dir), WATCHDOG_ERROR);
          }
          else {
            @chmod($dir, 0775); // Necessary for non-webserver users.
          }
        }
      }
    }
  }

  function truncate_filename(&$filename, $filename_length) {
    if (function_exists('mb_substr')) {
      $filename = mb_substr($filename, 0, $filename_length, '8bit');
    }
    else {
      // We'll have to assume we're working with ASCII if mbstring extension isn't installed.
      $filename = substr($filename, 0, $filename_length);
    }
  }


  function purge($dir, $flush) {
    $files = file_scan_directory($dir, '.*', array('.', '..', 'CVS'), 0, FALSE);
    foreach ($files as $file) {
      $mtime = filemtime($file->filename);
      if ($mtime != 1000 && $mtime < ($flush/* - $cache_lifetime*/)) {
        if ($fp = fopen($file->filename, 'r')) {
          // We need an exclusive lock, but don't block if we can't get it as
          // we can simply try again next time cron is run.
          if (flock($fp, LOCK_EX | LOCK_NB)) {
            unlink($file->filename);
          }
        }
      }
    }
  }

  /**
   * Statistics information.
   */
  function stats() {
    $stats = array(
      'uptime' => time(),
      'bytes_used' => disk_total_space($this->fspath) - disk_free_space($this->fspath),
      'bytes_total' => disk_total_space($this->fspath),
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
}
