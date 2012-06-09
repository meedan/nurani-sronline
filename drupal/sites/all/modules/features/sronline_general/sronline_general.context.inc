<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function sronline_general_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'header';
  $context->description = '';
  $context->tag = 'sronline';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu_block-2' => array(
          'module' => 'menu_block',
          'delta' => 2,
          'region' => 'header',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('sronline');
  $export['header'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'nav_bar';
  $context->description = '';
  $context->tag = 'sronline';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-primary-links' => array(
          'module' => 'menu',
          'delta' => 'primary-links',
          'region' => 'naviagion_bar',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('sronline');
  $export['nav_bar'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'right_sidebar';
  $context->description = '';
  $context->tag = 'sronline';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '~<front>' => '~<front>',
        '~node/8' => '~node/8',
        '~node/5' => '~node/5',
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
        'webform-client-block-1' => array(
          'module' => 'webform',
          'delta' => 'client-block-1',
          'region' => 'right',
          'weight' => 1,
        ),
        'views-text_bundles_featured-block_1' => array(
          'module' => 'views',
          'delta' => 'text_bundles_featured-block_1',
          'region' => 'right',
          'weight' => 2,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('sronline');
  $export['right_sidebar'] = $context;

  return $export;
}
