(function ($) {

Drupal.behaviors.cambridgeMedia = function(context) {
  $('video,audio', context)
    .not('.cambridge-media-processed')
    .addClass('cambridge-media-processed')
    .mediaelementplayer();

  $('.cambridge-media-video a[rel^="lightmodal"]')
    .not('.cambridge-media-processed')
    .addClass('cambridge-media-processed')
    .append('<span class="cambridge-video-play"></span>');
}

})(jQuery);
