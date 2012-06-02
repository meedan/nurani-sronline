<?php
// $Id: Cache.php,v 1.1.2.8 2009/09/03 09:56:10 doq Exp $

include_once dirname(__FILE__) .'/CacheEngine.php';

/**
 * Organizes work between different caching handlers.
 */
class DrupalCache {
  /**
   * Array of cache engine bins. e.g.
   *   'default' => engines, // 'default' is not a bin but special keyword.
   *   'cache' => engines,
   *   'cache_page' => engines,
   *   'cache_form' => engines,
   */
  var $bins = array();

  function __construct() {
    global $conf;

    // Apply default settings: use database for caching as in standard
    // Drupal's cache.inc implementation.
    if (!isset($conf['cache_settings'])) {
      $conf['cache_settings'] = array(
        'engines' => array(
          'database-engine' => array(
            'engine' => 'database',
          ),
        ),
        'schemas' => array(
          'database-schema' => array(
            'database-engine',
          )
        ),
        'bins' => array(
          'default' => 'database-schema',
        ),
      );

    }

  }

  private function __init($bin) {
    global $conf;

    if (!isset($conf['cache_settings']['bins'][$bin])) {
      assert(isset($conf['cache_settings']['bins']['default']));
      $schema = $conf['cache_settings']['bins']['default'];
    }
    else {
      $schema = $conf['cache_settings']['bins'][$bin];
    }

    assert(isset($conf['cache_settings']['schemas'][$schema]));
    $engine_names = $conf['cache_settings']['schemas'][$schema];
    $engines = array();
    $this->bins[$bin] = array();
    foreach ($engine_names as $engine_name) {
      assert(isset($conf['cache_settings']['engines'][$engine_name]['engine']));
      $engine_type = $conf['cache_settings']['engines'][$engine_name]['engine'];

      $class = $engine_type .'CacheEngine';
      if (!class_exists($class)) {
        include dirname(__FILE__) .'/engines/'. $engine_type .'.inc';
      }
      $settings = $conf['cache_settings']['engines'][$engine_name];
      /// @todo I don't like the idea creating own CacheEngine object per every bin but still the best solution I have found.
      $engine =& new $class($settings + array('bin' => $bin));

      if ($engine->status()) {
        $this->bins[$bin][] = $engine;
      }
      else {
        _cache_early_watchdog('error', 'Caching engine %engine is unavailable for %bin cache bin. It might worth disabling it.', array('%engine' => $engine_type, '%bin' => $bin), WATCHDOG_WARNING);
      }
    }

    // If all engines are unavailable - e.g. no APC, memcache extensions are
    // installed etc. - then we can always use standard database handler for
    // caching.
    if (count($this->bins[$bin]) == 0) {
      if (!class_exists('databaseCacheEngine')) {
        include dirname(__FILE__) .'/engines/database.inc';
      }
      $default =& new databaseCacheEngine(array('bin' => $bin));
      $this->bins[$bin][] =& $default;
    }
  }

  public function get($key, $bin) {
    global $conf;

    if (!isset($this->bins[$bin])) {
      $this->__init($bin);
    }

    foreach ($this->bins[$bin] as $engine) {
      $value = $engine->get($key);
      if ($value) {
        return $value;
      }
    }
    return FALSE;
  }

  public function set($key, $value, $expire, $headers, $bin) {
    global $conf;

    if (!isset($this->bins[$bin])) {
      $this->__init($bin);
    }

    $ret = TRUE;
    foreach ($this->bins[$bin] as $engine) {
      $ret &= $engine->set($key, $value, $expire, $headers);
    }
    return $ret;
  }

  public function delete($key, $wildcard, $bin) {
    global $conf;

    if (!isset($this->bins[$bin])) {
      $this->__init($bin);
    }

    $ret = TRUE;
    foreach ($this->bins[$bin] as $engine) {
      $ret &= $engine->delete($key, $wildcard);
    }
    return $ret;

  }

  public function flush($bin) {
    global $conf;

    if (!isset($this->bins[$bin])) {
      $this->__init($bin);
    }

    $ret = TRUE;
    foreach ($this->bins[$bin] as $engine) {
      $ret &= $engine->flush();
    }
    return $ret;
  }

  public function page_fast_cache($bin) {
    global $conf;

    if (!isset($this->bins[$bin])) {
      $this->__init($bin);
    }

    $ret = TRUE;
    foreach ($this->bins[$bin] as $engine) {
      // If database engine is registered then we don't want
      // it to fail.
      $ret &= $engine->page_fast_cache();
      if (!$ret) {
        return FALSE;
      }
    }

    return $ret;
  }

  public function getStatistics($bin) {
    global $conf;

    if (!isset($this->bins[$bin])) {
      $this->__init($bin);
    }

    /// @todo There can be chain from several caching engines.
    foreach ($this->bins[$bin] as $engine) {
      return $engine->stats();
    }

//    return $this->bins[$bin]->getStatistics();
  }

  /**
   * Get array of bins used.
   */
  public function getBins() {
    global $conf;
    return array_keys($conf['cache_settings']['bins']);
  }
/*
  public function getType($bin) {
    /// @todo
    $bin = ($bin == 'default') ? 'cache' : $bin;
    return $this->type[$bin];
  }
*/
}
