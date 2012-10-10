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
 * Implementation of hook_default_fe_nodequeue_queue().
 */
function sronline_video_default_fe_nodequeue_queue() {
  $export = array();

  $fe_nodequeue_queue = new stdClass;
  $fe_nodequeue_queue->name = 'videos_page_listing';
  $fe_nodequeue_queue->title = 'Videos listing';
  $fe_nodequeue_queue->subqueue_title = '';
  $fe_nodequeue_queue->size = '4';
  $fe_nodequeue_queue->link = 'Feature videos';
  $fe_nodequeue_queue->link_remove = 'Unfeature videos';
  $fe_nodequeue_queue->owner = 'nodequeue';
  $fe_nodequeue_queue->show_in_ui = '1';
  $fe_nodequeue_queue->show_in_tab = '1';
  $fe_nodequeue_queue->show_in_links = '1';
  $fe_nodequeue_queue->reference = '0';
  $fe_nodequeue_queue->reverse = '0';
  $fe_nodequeue_queue->i18n = '1';
  $fe_nodequeue_queue->types = array(
    0 => 'video',
  );
  $fe_nodequeue_queue->roles = array();
  $fe_nodequeue_queue->count = 0;
  $fe_nodequeue_queue->machine_name = 'videos_page_listing';

  $export['videos_page_listing'] = $fe_nodequeue_queue;

  return $export;
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
