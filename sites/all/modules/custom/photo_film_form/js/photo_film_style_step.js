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

        $("a[rel=style_video]", this.controls.form).fancybox({
            'type'				: 'iframe',

            'transitionIn'		: 'none',
            'transitionOut'		: 'none',
            'titlePosition' 	: 'over',

            'width'				: '75%',
            'height'			: '75%',
            'autoScale'     	: true
        });
        this.controls.items.on("click", $.proxy(this.initStyleSelected, this));

        if (this.controls.inputs.filter(":checked").length) {
            var style_id = this.controls.inputs.filter(":checked").attr("id").replace("edit-term-ids-", "");
            this.controls.items.filter("[style_id=" + style_id + "]").click();
        }
    }
    Drupal.initStyleSelected = function (e) {
        var item = $(e.currentTarget),
            theme_id = item.attr("style_id"),
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