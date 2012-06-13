<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function news_section_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_default_fe_nodequeue_queue().
 */
function news_section_default_fe_nodequeue_queue() {
  $export = array();

  $fe_nodequeue_queue = new stdClass;
  $fe_nodequeue_queue->name = 'featured_news_articles';
  $fe_nodequeue_queue->title = 'featured news article';
  $fe_nodequeue_queue->subqueue_title = '';
  $fe_nodequeue_queue->size = '4';
  $fe_nodequeue_queue->link = 'feature news articles';
  $fe_nodequeue_queue->link_remove = 'unfeature news articles';
  $fe_nodequeue_queue->owner = 'nodequeue';
  $fe_nodequeue_queue->show_in_ui = '1';
  $fe_nodequeue_queue->show_in_tab = '1';
  $fe_nodequeue_queue->show_in_links = '1';
  $fe_nodequeue_queue->reference = '0';
  $fe_nodequeue_queue->reverse = '0';
  $fe_nodequeue_queue->i18n = '1';
  $fe_nodequeue_queue->types = array(
    0 => 'news_articles',
  );
  $fe_nodequeue_queue->roles = array();
  $fe_nodequeue_queue->count = 0;
  $fe_nodequeue_queue->machine_name = 'featured_news_article';

  $export['featured_news_article'] = $fe_nodequeue_queue;

  return $export;
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function news_section_imagecache_default_presets() {
  $items = array(
    'news-image-104' => array(
      'presetname' => 'news-image-104',
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
            'width' => '104',
            'height' => '104',
          ),
        ),
      ),
    ),
    'news-image-294' => array(
      'presetname' => 'news-image-294',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '294',
            'height' => '271',
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
function news_section_node_info() {
  $items = array(
    'news_articles' => array(
      'name' => t('News Articles'),
      'module' => 'features',
      'description' => t('Content type for creating News Articles'),
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
function news_section_views_api() {
  return array(
    'api' => '2',
  );
}
