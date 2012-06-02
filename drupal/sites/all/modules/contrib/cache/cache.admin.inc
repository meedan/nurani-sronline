<?php
// $Id: cache.admin.inc,v 1.1.2.4 2009/08/16 15:05:27 doq Exp $

/**
 * @file
 * Admin pages for cache module.
 */

/**
 * Menu callback.
 */
function cache_reports_page() {
  global $cache;

  $output = '';

  $output .= '<h2>'. t('Supported caching engines') .'</h2>';
  /// @todo Should retrieve sorted list by name.
  $engine_files = file_scan_directory(drupal_get_path('module', 'cache') .'/engines', '\.inc$', array('.', '..', 'CVS'), 0, FALSE);
  $rows = array();
  foreach ($engine_files as $engine_file) {
    $engine_type = $engine_file->name;
    $class = $engine_type .'CacheEngine';
    if (!class_exists($class)) {
      include $engine_file->filename;
    }
    eval("\$info = $class::getInfo();");
    $name = isset($info['site']) ? l($info['name'], $info['site']) : $info['name'];
    $rows[] = array($name, '<code>'. $engine_type .'</code>', $info['description']);
  }
  $header = array(t('Name'), t('Engine type'), t('Description'));
  $output .= theme('table', $header, $rows);

  if (isset($cache)) {
    foreach ($cache->getBins() as $bin) {
      $stats = $cache->getStatistics($bin);
      $output .= _cache_reports_page($bin, $stats);
    }
  }

  return $output;
}


function _cache_reports_page($bin, $stats) {
  $output = '<h2>'. t('%bin cache bin statistics', array('%bin' => $bin)) .'</h2>';
  if ($stats == NULL) {
    $output .= t('Statistics not supported.');
    return $output;
  }

  // Get cache stats table with graphs.
  $stats_header = array(t('Memory'), t('Hit / Miss'), t('Get / Set'));
  $stats_attributes = array('id' => 'cacherouter-stats');
  $stats_table = array();

  // First do our calculations for percentages and sizes.
  if ($stats['bytes_used'] && $stats['bytes_total']) {
    $mem_used = round(($stats['bytes_used'] / $stats['bytes_total']) * 100);
    $mem_free = round(100 - $mem_used);
    if ($mem_free == 100) {
      $mem_free = 99;
      $mem_used = 1;
    }
    $url = 'http://chart.apis.google.com/chart?chs=250x100&chd=t:'. $mem_used .','. $mem_free . '&cht=p3&chl=Used|Free&chco=3399cc,cbe2f1';
    $chart1 = theme('image', $url, '', '', array('width' => 250, 'height' => 100), FALSE);
    assert(strlen($chart1) > 0);
  }
  else {
    $chart1 = t('No information available.');
  }


  if ($stats['hits'] > 0) {
    $hits_hit = round(($stats['hits'] / ($stats['hits'] + $stats['misses'])) * 100);
  }
  else {
    $hits_hit = 0;
  }

  if ($stats['misses'] > 0) {
    $hits_misses = round(($stats['misses'] / ($stats['hits'] + $stats['misses'])) * 100);
  }
  else {
    $hits_misses = 0;
  }


  if ($hits_hit || $hits_misses) {
    $url = 'http://chart.apis.google.com/chart?chs=250x100&chd=t:'. $hits_hit .','. $hits_misses .'&cht=p3&chl=Hit|Miss&chco=3399cc,cbe2f1';
    $chart2 = theme('image', $url, '', '', array('width' => 250, 'height' => 100), FALSE);
    assert(strlen($chart2) > 0);
  }
  else {
    $chart2 = t('No information available.');
  }


  if ($stats['gets'] > 0) {
    $req_gets = round(($stats['gets'] / ($stats['gets'] + $stats['sets'])) * 100);
  }
  else {
    $req_gets = 0;
  }

  if ($stats['sets'] > 0) {
    $req_sets = round(($stats['sets'] / ($stats['gets'] + $stats['sets'])) * 100);
  }
  else {
    $req_sets = 0;
  }


  if ($req_gets || $req_sets) {
    $url = 'http://chart.apis.google.com/chart?chs=250x100&chd=t:'. $req_gets .','. $req_sets .'&cht=p3&chl=Get|Set&chco=3399cc,cbe2f1';
    $chart3 = theme('image', $url, '', '', array('width' => 250, 'height' => 100), FALSE);
    assert(strlen($chart3) > 0);
  }
  else {
    $chart3 = t('No information available.');
  }


  // First row is images
  $stats_table[] = array($chart1, $chart2, $chart3);

  // Next row is stats and key for images
  $stats_table[] = array(
    _cache_admin_stats_key(t('Used'), drupal7_format_size($stats['bytes_used']) .' ('. $mem_used .'%)',
      t('Free'), drupal7_format_size($stats['bytes_total'] - $stats['bytes_used']) .' ('. $mem_free .'%)'),
    _cache_admin_stats_key(t('Hits'), $stats['hits'] .' ('. $hits_hit .'%)',
      t('Misses'), $stats['misses'] . ' ('. $hits_misses .'%)'),
    _cache_admin_stats_key(t('Gets'), $stats['gets'] .' ('. $req_gets .'%)',
      t('Sets'), $stats['sets'] .' ('. $req_sets .'%)'),
  );

  $output .= theme('table', $stats_header, $stats_table, $stats_attributes);

  $info_header = array(t('Cache info'), t('Value'));
  $info_table = array();

  // Row 1 - Request Rate.
  $info_table[] = array(
    t('Request Rate'),
    sprintf('%.2f %s', $stats['req_rate'], t('requests / second')),
  );

  // Row 2 - Hit Rate.
  $info_table[] = array(
    t('Hit Rate'),
    sprintf('%.2f %s', $stats['hit_rate'], t('requests / second')),
  );

  // Row 3 - Miss Rate.
  $info_table[] = array(
    t('Miss Rate'),
    sprintf('%.2f %s', $stats['miss_rate'], t('requests / second')),
  );

  // Row 4 - Set Rate.
  $info_table[] = array(
    t('Set Rate'),
    sprintf('%.2f %s', $stats['set_rate'], t('requests / second')),
  );

  $output .= theme('table', $info_header, $info_table);
  
 
  return $output;
}

function _cache_admin_stats_key($key1, $value1, $key2, $value2) {
  $output  = '<div class="cr-key">';
  $output .= '<div class="cr-primary-1"></div>';
  $output .= '<span><strong>'. $key1 .':</strong> '. $value1 .'</span>';
  $output .= '</div>';
  $output .= '<div class="cr-key">';
  $output .= '<div class="cr-primary-2"></div>';
  $output .= '<span><strong>'. $key2 .':</strong> '. $value2 .'</span>';
  $output .= '</div>';

  return $output;
}

/**
 * Generate a string representation for the given byte count.
 *
 * @param $size
 *   A size in bytes.
 * @param $langcode
 *   Optional language code to translate to a language other than what is used
 *   to display the page.
 * @return
 *   A translated string representation of the size.
 */
function drupal7_format_size($size, $langcode = NULL) {
  if ($size < 1024) {
    return format_plural($size, '1 byte', '@count bytes', array(), $langcode);
  }
  else {
    $size = $size / 1024; // Convert bytes to kilobytes.
    $units = array(
      t('@size KB', array(), $langcode),
      t('@size MB', array(), $langcode),
      t('@size GB', array(), $langcode),
      t('@size TB', array(), $langcode),
      t('@size PB', array(), $langcode),
      t('@size EB', array(), $langcode),
      t('@size ZB', array(), $langcode),
      t('@size YB', array(), $langcode),
    );
    foreach ($units as $unit) {
      if (round($size, 2) >= 1024) {
        $size = $size / 1024;
      }
      else {
        break;
      }
    }
    return str_replace('@size', round($size, 2), $unit);
  }
}
