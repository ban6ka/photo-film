(function ($) {
    Drupal.behaviors.photo_film_themes_step = {
        attach: function (context, settings) {
            Drupal.initThemesSelector();
        }
    }

    Drupal.controls = {
        form: null,
        items: null,
        inputs: null
    }
    Drupal.initThemesSelector = function () {
        Drupal.controls.form = $("form.photo-film-form");
        Drupal.controls.inputs = $("input.radios-theme-step", Drupal.controls.form);
        Drupal.controls.items = $("div.theme-toolbar", Drupal.controls.form);

        Drupal.controls.items.on("click", $.proxy(this.initThemesSelected, this));
    }
    Drupal.initThemesSelected = function (e) {
        var item = $(e.currentTarget);
        if ($(e.target).is("div.checkbox")) {
            var theme_id = item.attr("theme_id"),
                radio = this.controls.inputs.filter("#edit-term-ids-" + theme_id);

            if (radio.length) {
                radio.trigger("click");

                this.controls.items.removeClass("selected");
                item.addClass("selected");
            }
        }
    }
})(jQuery)