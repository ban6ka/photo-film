(function ($) {
    Drupal.behaviors.photo_film_order_step = {
        attach: function (context, settings) {
            Drupal.initOrderStep();
        }
    }

    Drupal.controls = {
        form: null,
        inputs: null
    }
    Drupal.initOrderStep = function () {
        this.controls.form = $("form.photo-film-form");
        this.controls.inputs = $("input.required, select.required", this.controls.form);

        $("#edit-mobile").mask("(999) 999-99-99");
        this.controls.inputs.on("keyup change", $.proxy(this.enableSubmitButton, this));
    }

    Drupal.enableSubmitButton = function () {
        var active = true;
        this.controls.inputs.each(function () {
            active = active && ($(this).val().length > 0);
        });

        if (active) {
            $("div.form-button-wrap").addClass("active");
        } else {
            $("div.form-button-wrap").removeClass("active");
        }
    }

})(jQuery)