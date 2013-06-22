/* Place your theme's javascript here! */

(function($) {
  // Use strict mode to avoid errors: https://developer.mozilla.org/en/JavaScript/Strict_mode
  "use strict";

/*------------------------------------------------------------------------------
  Outer Plugins and modules
*/
function makeScrollbar(context){
  jQuery('#scrollbar').tinyscrollbar();
}

function aviaSlider(context){
  jQuery('.front-slider ul').aviaSlider({
    blockSize: {height: 520, width:40},
    display: 'topleft',
    transition: 'fade',
    betweenBlockDelay:80,
    animationSpeed: 400,
    switchMovement: true
  });
}


/*------------------------------------------------------------------------------
  Safari (Mac) Fix submit button gradient
*/

  function getOS(context) {

    var mac = /mac/.test(navigator.platform.toLowerCase());
    var safari = /safari/.test(navigator.userAgent.toLowerCase());

    if (mac && safari || safari) {
      jQuery('.node-webform #edit-actions input').addClass('safari-mac-fix');
      jQuery('.node-webform .form-actions input').addClass('safari-mac-fix');
    }
  }


/*------------------------------------------------------------------------------
  Internet Explrore fixes
*/

function niceButton(context) {
  jQuery('.read-more, #edit-actions input, #edit-actions--2 input').wrap('<div class="nice-wrap" />');
}

function reviewWrap(context) {
  jQuery('.reviewed').wrap('<div class="review-wrap" />');
  jQuery('<span class="icon">&nbsp</span>').prependTo('.review-wrap');
}

function leftMenuFix(context) {
  jQuery('<div class="menu-bottom" />').appendTo('.lt-ie9 .menu-level-2');
}

function enablePlaceholders() {
    $('input[placeholder]').placeholder();
}

function evenOdd(context) {
    jQuery('#webform-component-person-detail .webform-component:odd').addClass('odd');
  }


/*------------------------------------------------------------------------------
  To learn more about Javascript in Drupal 7 check out:
  http://drupal.org/node/756722
*/
  Drupal.behaviors.photo_film = {
    attach: function(context, settings) {
      /*makeScrollbar(context);
      aviaSlider(context);
      getOS(context);*/

      if (jQuery.browser.msie) {

        enablePlaceholders();

         // IE 8.0 or less
        /*if (jQuery.browser.version < 9.0) {
          niceButton(context);
          reviewWrap(context);
          leftMenuFix(context);
          evenOdd(context);
        }*/

        // IE 8.0 only
        if (jQuery.browser.version == 8.0) {

        };

        // IE 7.0 only
        if (jQuery.browser.version < 8.0) {

        };
      }
    }
  };

})(jQuery);
