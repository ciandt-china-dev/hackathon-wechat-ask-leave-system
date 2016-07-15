(function ($) {

  'use strict';

  Drupal.behaviors.nodeFormPanesEditAuthoredOn = {
    attach: function (context, settings) {
      $('a.node-form-summary-toggle').once('node-form-summary-toggle').click(function (event) {
        event.preventDefault();
        $('.' + $(this).attr('data-toggle'), $(this).parents('.node-form-summary')).show();
        $(this).parent().hide();
      });
    }
  };

  /**
    * Make the path alias field inline with the "Permalink: http://domain.com/"
    */
  Drupal.behaviors.nodeFormPanesPathauto = {
    attach: function (context, settings) {
      var width = $('.node-form .form-item-path-alias .label-wrapper').width();
      $('.node-form .form-item-path-alias label').css('width', width);
      // Display: table-cell is "experimental" on input fields so we're going
      // to wrap it
      $('.node-form .form-item-path-alias input').wrap('<span class="input-wrapper"></span>');
    }
  };

})(jQuery);
