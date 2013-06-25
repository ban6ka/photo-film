(function ($) {
    Drupal.behaviors.photo_film_style_step = {
        attach: function (context, settings) {
            Drupal.initStylesSelector();
        }
    }

    Drupal.controls = {
        form: null,
        items: null,
        inputs: null
    }
    Drupal.initStylesSelector = function () {
        this.controls.form = $("form.photo-film-form");
        this.controls.inputs = $("input.radios-theme-step", Drupal.controls.form);
        this.controls.items = $("div.style-toolbar", Drupal.controls.form);

        this.controls.inputs.each(function () {
            var style_id = $(this).attr("id").replace("edit-term-ids-", ""),
                place = Drupal.controls.items.filter("[style_id=" + style_id + "]");
            if (place.length) {
                place.children(".checkbox").append(this);
            }
        });

        $("a[rel=style_video]", this.controls.form).fancybox({
            'type'				: 'iframe',

            'transitionIn'		: 'none',
            'transitionOut'		: 'none',
            'titlePosition' 	: 'over',

            'width'				: '75%',
            'height'			: '75%',
            'autoScale'     	: true
        });

    }
})(jQuery)