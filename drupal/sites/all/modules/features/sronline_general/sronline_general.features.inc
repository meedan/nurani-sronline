<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function sronline_general_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => 3);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_default_fe_nodequeue_queue().
 */
function sronline_general_default_fe_nodequeue_queue() {
  $export = array();

  $fe_nodequeue_queue = new stdClass;
  $fe_nodequeue_queue->name = 'featured_text_bundles';
  $fe_nodequeue_queue->title = 'Featured text bundles';
  $fe_nodequeue_queue->subqueue_title = '';
  $fe_nodequeue_queue->size = '5';
  $fe_nodequeue_queue->link = 'Feature text bundle';
  $fe_nodequeue_queue->link_remove = 'Unfeature text bundle';
  $fe_nodequeue_queue->owner = 'nodequeue';
  $fe_nodequeue_queue->show_in_ui = '1';
  $fe_nodequeue_queue->show_in_tab = '1';
  $fe_nodequeue_queue->show_in_links = '1';
  $fe_nodequeue_queue->reference = '0';
  $fe_nodequeue_queue->reverse = '0';
  $fe_nodequeue_queue->i18n = '1';
  $fe_nodequeue_queue->types = array(
    0 => 'text_bundle',
  );
  $fe_nodequeue_queue->roles = array();
  $fe_nodequeue_queue->count = 0;
  $fe_nodequeue_queue->machine_name = 'featured_text_bundles';

  $export['featured_text_bundles'] = $fe_nodequeue_queue;

  return $export;
}

/**
 * Implementation of hook_node_info().
 */
function sronline_general_node_info() {
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
    'webform' => array(
      'name' => t('Webform'),
      'module' => 'features',
      'description' => t('Create a new form or questionnaire accessible to users. Submission results and statistics are recorded and accessible to privileged users.'),
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
function sronline_general_views_api() {
  return array(
    'api' => '2',
  );
}
