$(function () {
  var tp = Drupal.settings.theme_path;
  $('body')
    // $, jQuery is replaced with the 1.7.2 version. Old is moved to _$, _jQuery
    .append('<script src="' + tp + '/libs/jquery/jquery-1.7.2.min.js"><\/script>')
    // chosen.jquery.min.js relies on the 'jQuery' variable being > v1.7.2.
    .append('<script src="' + tp + '/libs/chosen/chosen/chosen.jquery.min.js"><\/script>')
    // Create a jQuery_172 variable which can be used later in the execution
    .append('<script>var jQuery_172 = jQuery.noConflict(true);</script>');
    // Now $ and jQuery refer to jQuery-1.3.2 again, @see $.noConflict()
});

