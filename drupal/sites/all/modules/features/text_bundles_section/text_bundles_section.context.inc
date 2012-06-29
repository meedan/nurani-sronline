<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function text_bundles_section_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'text_bundles';
  $context->description = '';
  $context->tag = 'sronline';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'text-bundles' => 'text-bundles',
        'text-bundles/*' => 'text-bundles/*',
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
        'boxes-text_bundles_intro' => array(
          'module' => 'boxes',
          'delta' => 'text_bundles_intro',
          'region' => 'content_top_left',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('sronline');
  $export['text_bundles'] = $context;

  return $export;
}
