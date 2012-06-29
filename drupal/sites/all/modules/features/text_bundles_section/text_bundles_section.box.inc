<?php

/**
 * Implementation of hook_default_box().
 */
function text_bundles_section_default_box() {
  $export = array();

  $box = new stdClass;
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'text_bundles_intro';
  $box->plugin_key = 'simple';
  $box->title = 'Read this before you start';
  $box->description = 'Text Bundles: Read this before you start';
  $box->options = array(
    'body' => 'Why do SR?
Why Jewish/Christian/Muslim: shared ground between the traditions differences between the traditions, e.g.:
<ul>
  <li>the nature of God in each tradition</li>
  <li>what is the scripture and why sacred in each tradition</li>
</ul>',
    'format' => '1',
  );
  $export['text_bundles_intro'] = $box;

  return $export;
}
