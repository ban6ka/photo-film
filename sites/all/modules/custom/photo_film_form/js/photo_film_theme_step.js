(function ($) {
    Drupal.behaviors.photo_film_themes_step = {
        attach: function (context, settings) {
            Drupal.initThemesSelector();
        }
    }

    Drupal.themeControls = {
        form: null,
        items: null,
        inputs: null
    }
    Drupal.initThemesSelector = function () {
        Drupal.themeControls.form = $("form.photo-film-form");
        Drupal.themeControls.inputs = $("input.radios-theme-step", Drupal.themeControls.form);
        Drupal.themeControls.items = $("div.image-toolbar", Drupal.themeControls.form);

        Drupal.themeControls.items.on("click", $.proxy(this.initThemesSelected, this));
    }
    Drupal.initThemesSelected = function (e) {
        var item = $(e.currentTarget);
        if ($(e.target).is("div.checkbox")) {
            var theme_id = item.attr("id").replace("theme-", ""),
                radio = this.themeControls.inputs.filter("#edit-term-ids-" + theme_id);

            if (radio.length) {
                radio.trigger("click");

                this.themeControls.items.removeClass("selected");
                item.addClass("selected");
            }
        }
    }
})(jQuery)