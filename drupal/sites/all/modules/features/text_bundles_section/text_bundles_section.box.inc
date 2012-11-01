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
  $box->title = 'Using Text Bundles';
  $box->description = 'Text Bundles: Read this before you start';
  $box->options = array(
    'body' => '

Here are some themed texts for use in a Scriptural Reasoning group. They have all been tried by members of the SR team. Under each theme are four pdfs - the first three each contain a text in its original language (Hebrew, Greek, Arabic) with an English translation and a short introduction. (We realise that Christians do not often read the Bible in Greek, and you shouldn’t worry if nobody in your group has Greek skills). The fourth pdf has all three texts and introductions in English only, for when you want to study in English. Remember that not every one in the group reads Arabic or Greek or Hebrew, so you should use the original languages to clarify points, not to close down discussion. ',
    'format' => '1',
  );
  $export['text_bundles_intro'] = $box;

  return $export;
}
