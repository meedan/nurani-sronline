<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function home_section_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function home_section_imagecache_default_presets() {
  $items = array(
    'Home-image_613' => array(
      'presetname' => 'Home-image_613',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '613',
            'height' => '312',
          ),
        ),
      ),
    ),
    'Home-newsthumb-60' => array(
      'presetname' => 'Home-newsthumb-60',
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
            'width' => '60',
            'height' => '60',
          ),
        ),
      ),
    ),
    'Home-video_294' => array(
      'presetname' => 'Home-video_294',
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
            'width' => '294',
            'height' => '174',
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
function home_section_node_info() {
  $items = array(
    'home_banner' => array(
      'name' => t('Home banner'),
      'module' => 'features',
      'description' => t('A content type to upload banner on the home page'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'testimonial' => array(
      'name' => t('Testimonial'),
      'module' => 'features',
      'description' => t('Create Testimonial Content'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'text_bundle' => array(
      'name' => t('Text Bundles'),
      'module' => 'features',
      'description' => t('A Content Type to create Text bundles'),
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

/**
 * Implementation of hook_views_api().
 */
function home_section_views_api() {
  return array(
    'api' => '2',
  );
}
