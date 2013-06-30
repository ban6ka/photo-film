(function ($) {
    Drupal.behaviors.photo_film_order_step = {
        attach: function (context, settings) {
            Drupal.initOrderStep();
        }
    }

    Drupal.controls = {
        form: null,
        inputs: null,
        info_block: null
    }
    Drupal.initOrderStep = function () {
        this.controls.form = $("form.photo-film-form");
        this.controls.inputs = $("input.required, select.required", this.controls.form);
        this.controls.info_block = $("div.info-block-wrap", this.controls.form);

        $("#edit-mobile").mask("(999) 999-99-99");
        this.controls.inputs.on("keyup change", $.proxy(this.enableSubmitButton, this));

        $("a.open-info", this.controls.info_block).on("click", $.proxy(this.openInfoBlock, this));
        $("a.close-info", this.controls.info_block).on("click", $.proxy(this.closeInfoBlock, this));
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

    Drupal.openInfoBlock = function (e) {
        e.preventDefault();
        if (this.controls.info_block.height() == 0) {
            this.controls.info_block.children("div.info-message").slideDown(200);
        }
    }

    Drupal.closeInfoBlock = function (e) {
        e.preventDefault();
        if (!this.controls.info_block.height() == 0) {
            this.controls.info_block.children("div.info-message").slideUp(200);
        }
    }

})(jQuery)