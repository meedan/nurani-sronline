<?php

function _cambridge_media_data_from_element($element) {
  if (isset($element['#item']['cambridge_media'])) {
    $data = $element['#item']['cambridge_media'];
  }
  else {
    $data = cambridge_media_load_by_vid($element['#node']->vid);
    $data['thumbnail_file'] = db_fetch_object(db_query("SELECT * FROM {files} WHERE fid = %d", $data['thumbnail_fid']));
  }
  return $data;
}

function theme_cambridge_media_formatter_media_small($element) {
  $data = _cambridge_media_data_from_element($element);
  return theme('cambridge_media', $data['media_id'], $data['download_url'], $data['thumbnail_file']->filepath, 293, 173, FALSE);
}

function theme_cambridge_media_formatter_media_normal($element) {
  $data = _cambridge_media_data_from_element($element);
  return theme('cambridge_media', $data['media_id'], $data['download_url'], $data['thumbnail_file']->filepath, 480, 288, FALSE);
}

function theme_cambridge_media_formatter_media_large($element) {
  $data = _cambridge_media_data_from_element($element);
  return theme('cambridge_media', $data['media_id'], $data['download_url'], $data['thumbnail_file']->filepath, 556, 322, FALSE);
}

function theme_cambridge_media($media_id, $video_url, $thubmnail_path, $width, $height, $autoplay) {
  $path = 'sites/all/libraries/mediaelement/build';
  drupal_add_js($path . '/mediaelement-and-player.min.js');
  drupal_add_css($path . '/mediaelementplayer.min.css');
  drupal_add_js(drupal_get_path('module', 'cambridge_media') . '/cambridge_media.js');

  $width         = filter_xss($width);
  $height        = filter_xss($height);
  $thubmnail_url = url($thubmnail_path);
  $preload       = 'none';

  $output .= '<video controls="controls" width="' . $width . '" height="' . $height . '" poster="' . $thubmnail_url . '" preload="' . $preload . '"' . ($autoplay ? ' autoplay="true"' : '') . '>';
  $output .=   '<source type="video/mp4" src="' . filter_xss($video_url) . '" />';
  $output .=   '<object width="' . $width . '" height="' . $height . '" type="application/x-shockwave-flash" data="' . $path . '/flashmediaelement.swf">';
  $output .=     '<param name="movie" value="' . $path . '/flashmediaelement.swf" />';
  $output .=     '<param name="flashvars" value="controls=true&amp;poster=' . urlencode($thubmnail_url) . '&amp;file=' . urlencode($video_url) . '" />';
  $output .=     '<img src="' . $thubmnail_url . '" width="' . $width . '" height="' . $height . '" title="No video playback capabilities" />';
  $output .=   '</object>';
  $output .= '</video>';

  return $output;
}

