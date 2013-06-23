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
        Drupal.controls.form = $("form.photo-film-form");
        Drupal.controls.inputs = $("input.radios-theme-step", Drupal.controls.form);
        Drupal.controls.items = $("div.style-toolbar", Drupal.controls.form);

        Drupal.controls.inputs.each(function () {
            $(this).attr("checked", null);

            var style_id = $(this).attr("id").replace("edit-term-ids-", ""),
                place = Drupal.controls.items.filter("#style-" + style_id);
            if (place.length) {
                place.children(".checkbox").append(this);
            }
        });
    }
})(jQuery)