$(function () {

  // HACK: Workaround for issue where $().offset() does not return valid results
  //       for floated elements.
  setTimeout(function () {
    // Equalize height of floated blocks on some pages by using the equalHeights
    // jQuery plugin.
    $('.page-home .center-wrapper .panel-panel .block').equalHeightsPerRow();  
    $('.page-text-bundles .view-text-bundles .view-content > .item-list').equalHeightsPerRow();
  }, 0);

  // Use the "Chosen" plugin to style select boxes
  // @see boostrap_lib_chosen.js for inclusion of jQuery-1.7.2 and creation of
  //      the jQuery_172 variable.
  jQuery_172('.page-text-bundles .view-text-bundles .view-filters select').chosen();

  // Add even / odd classes to views item-lists
  var i = 0;
  $('.page-text-bundles .view-text-bundles .view-content > .item-list')
    .each(function () {
      i += 1;
      $(this)
        .addClass(i % 2 == 0 ? 'item-list-even' : 'item-list-odd')
        .addClass('item-list-' + i);
    });

});