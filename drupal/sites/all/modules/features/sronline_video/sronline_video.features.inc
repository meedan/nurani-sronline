<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function sronline_video_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function sronline_video_imagecache_default_presets() {
  $items = array(
    'Video_image_295' => array(
      'presetname' => 'Video_image_295',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '295',
            'height' => '200',
          ),
        ),
      ),
    ),
    'Video_image_556' => array(
      'presetname' => 'Video_image_556',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '556',
            'height' => '322',
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
function sronline_video_node_info() {
  $items = array(
    'video' => array(
      'name' => t('Video'),
      'module' => 'features',
      'description' => t('Upload a scriptural reasoning video.'),
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
function sronline_video_views_api() {
  return array(
    'api' => '2',
  );
}
