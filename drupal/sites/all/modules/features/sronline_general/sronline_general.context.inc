<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function sronline_general_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'sidebar_menu';
  $context->description = '';
  $context->tag = 'sronline';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'node/*' => 'node/*',
        'news' => 'news',
        'news/*' => 'news/*',
        'text-bundles' => 'text-bundles',
        'text-bundles/*' => 'text-bundles/*',
        'videos' => 'videos',
        'videos/*' => 'videos/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu_block-1' => array(
          'module' => 'menu_block',
          'delta' => 1,
          'region' => 'right',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('sronline');
  $export['sidebar_menu'] = $context;

  return $export;
}
