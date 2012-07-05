<?php

/**
 * Implementation of hook_input_formats().
 */
function sronline_general_input_formats() {
  $input_formats = array();

  $input_format = new stdClass;
  $input_format->api_version = 1;
  $input_format->name = 'Filtered HTML';
  $input_format->roles = array(
    1 => 'anonymous user',
    2 => 'authenticated user',
    3 => 'administrator',
    5 => 'ICanLocalize manager',
    4 => 'ICanLocalize translator',
  );
  $input_format->cache = TRUE;
  $input_format->settings = array(
    // Settings for: filter module
    'filter' => array(
      'filter_html' => '1',
      'allowed_html' => '<a> <em> <strong> <ul> <ol> <li> <sup>',
      'filter_html_help' => 1,
      'filter_html_nofollow' => 0,
    ),
  );
  $input_format->filters = array(
    'filter' => array(
      '2' => '0',
      '0' => '1',
      '1' => '2',
      '3' => '10',
    ),
  );
  $input_format->machine = 'filtered_html';
  $input_formats['filtered_html'] = $input_format;

  return $input_formats;

}
