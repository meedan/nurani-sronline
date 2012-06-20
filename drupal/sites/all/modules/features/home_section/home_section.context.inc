<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function home_section_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'home_page';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-Featured_video_home-block_1' => array(
          'module' => 'views',
          'delta' => 'Featured_video_home-block_1',
          'region' => 'content_top_right',
          'weight' => 0,
        ),
        'webform-client-block-1' => array(
          'module' => 'webform',
          'delta' => 'client-block-1',
          'region' => 'content_top_right',
          'weight' => 1,
        ),
        'views-home_page_banner-block_1' => array(
          'module' => 'views',
          'delta' => 'home_page_banner-block_1',
          'region' => 'content_top_left',
          'weight' => 0,
        ),
        'views-news_articles_featured-block_1' => array(
          'module' => 'views',
          'delta' => 'news_articles_featured-block_1',
          'region' => 'home_left',
          'weight' => 0,
        ),
        'views-text_bundles_featured-block_1' => array(
          'module' => 'views',
          'delta' => 'text_bundles_featured-block_1',
          'region' => 'home_center',
          'weight' => 0,
        ),
        'views-32bfceaf56e91407f76ac3a77c3d8a4b' => array(
          'module' => 'views',
          'delta' => '32bfceaf56e91407f76ac3a77c3d8a4b',
          'region' => 'home_right',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;
  $export['home_page'] = $context;

  return $export;
}
