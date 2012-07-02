$(function () {
  var tp = Drupal.settings.theme_path;
  $('body')
    .append('<script src="' + tp + '/libs/jquery/jquery-1.7.2.min.js"><\/script>')
    .append('<script src="' + tp + '/libs/chosen/chosen/chosen.jquery.min.js"><\/script>')
    // Create a jQuery_172 variable which can be used later in the execution stack
    .append('<script>var jQuery_172 = jQuery.noConflict(true);</script>');
});

