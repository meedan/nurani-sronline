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
 * Implementation of hook_imagecache_default_presets().
 */
function news_section_imagecache_default_presets() {
  $items = array(
    'news-image-104' => array(),
    'news-image-294' => array(),
  );
  return $items;
}
