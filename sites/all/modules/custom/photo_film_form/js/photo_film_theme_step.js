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
        this.controls.form = $("form.photo-film-form");
        this.controls.inputs = $("input.radios-theme-step", Drupal.controls.form);
        this.controls.items = $("div.theme-toolbar", Drupal.controls.form);

        this.controls.items.on("click", $.proxy(this.initThemeSelected, this));

        if (this.controls.inputs.filter(":checked").length) {
            var style_id = this.controls.inputs.filter(":checked").attr("id").replace("edit-term-ids-", "");
            this.controls.items.filter("[theme_id=" + style_id + "]").click();
        }
    }
    Drupal.initThemeSelected = function (e) {
        var item = $(e.currentTarget),
            theme_id = item.attr("theme_id"),
            radio = this.controls.inputs.filter("#edit-term-ids-" + theme_id);

        if (radio.length) {
            radio.trigger("click");

            this.controls.items.removeClass("selected");
            item.addClass("selected");
            this.enableSubmitButton();
        }
    }

    Drupal.enableSubmitButton = function () {
        $("div.form-button-wrap").addClass("active");
    }
})(jQuery)