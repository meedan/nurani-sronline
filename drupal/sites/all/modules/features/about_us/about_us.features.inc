<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function about_us_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function about_us_imagecache_default_presets() {
  $items = array(
    'about_us_560' => array(
      'presetname' => 'about_us_560',
      'actions' => array(
        '0' => array(
          'weight' => '-10',
          'module' => 'imagecache',
          'action' => 'imagecache_sharpen',
          'data' => array(
            'radius' => '0.5',
            'sigma' => '0.5',
            'amount' => '100',
            'threshold' => '0.05',
          ),
        ),
        '1' => array(
          'weight' => '-9',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '560',
            'height' => '272',
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function about_us_node_info() {
  $items = array(
    'basic_page' => array(
      'name' => t('Basic pages'),
      'module' => 'features',
      'description' => t('Content type to be used for creating information pages on the website. E.g About us page, How to do SR e.t.c'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
