(function ($) {
    Drupal.behaviors.photo_film_style_step = {
        attach: function (context, settings) {
            $('.single-style-info').click(function () {
                if ($(this).find('.video-src').length > 0) {
                    if ($(this).find('.video-src').length > 0) {
                       $('.photo-video-style-step').show().find('iframe').attr('src', $(this).find('.video-src').text());
                    }
                }
            });
        }
    }
})(jQuery)