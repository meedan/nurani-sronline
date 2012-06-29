$(function () {

  // Equalize height of floated blocks on some pages by using the equalHeights
  // jQuery plugin.
  $('.page-home .center-wrapper .panel-panel .block').equalHeightsPerRow();  
  $('.page-text-bundles .view-text-bundles .view-content > .item-list').equalHeightsPerRow();

  // Use the "Chosen" plugin to style select boxes
  $('.page-text-bundles .view-text-bundles .view-filters select').chosen();

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