(function ($) {
    Drupal.behaviors.photo_film_select_picture_step = {
        attach: function (context, settings) {
            Drupal.initPhotosUploader();
        }
    }

    // TODO: all constant in to backend!
    Drupal.form_settings = {
        max_files: 100,
        max_weight: 10000000, // 10 MB
        accept_types: /(\.|\/)(gif|jpe?g|png)$/i,
        uploaded_files: 0
    }
    Drupal.controls = {
        uploader: null,
        drop_zone: null,
        files_holder: null,
        comment_dialog: null
    }
    Drupal.control_classes = {
        loading: "loading"
    }
    Drupal.item_template =
        '<li>' +
            '<img src="" width="220" height="120" align="left" />' +
            '<div class="photo-number"></div>' +
            '<div class="photo-toolbar clearfix">' +
            '<div class="photo-comment">коментировать</div>' +
            '<div class="photo-remove">удалить</div>' +
          '</div>' +
          '<input type="text" class="photo-id hidden" name="photos_id[]" />' +
          '<input type="text" class="photo-order hidden" name="photos_order[]" />' +
          '<textarea class="photo-desc hidden" name="photos_comment[]" />' +
        '</li>';

    Drupal.initPhotosUploader = function () {
        this.controls.uploader = $("#photos-upload");
        this.controls.drop_zone = $("div.file-uploader-holder");
        this.controls.files_holder = $("ul.user-photos-wrap");
        this.controls.comment_dialog = $("#comment-dialog");

        this.controls.uploader.fileupload({
            url: '/admin/photo-film/file/save/file',
            dataType: 'json',
            autoUpload: true,
            singleFileUploads: true,
            acceptFileTypes: this.form_settings.accept_types,
            maxNumberOfFiles: this.form_settings.max_files,
            maxFileSize: this.form_settings.max_weight,
            disableImagePreview: true,

            dropZone: this.controls.drop_zone
        })
        .bind('fileuploadsend', $.proxy(this.beforePhotoUploaded, this))
        .bind('fileuploaddone', $.proxy(this.onPhotoUploaded, this))
        .bind('fileuploadfail', function (e, data) { console.log('Processing ' + data.files[0].name + ' fail.'); });
    }

    Drupal.beforePhotoUploaded = function (e, data) {
        var fileCount = data.files.length,
            maxAllowed = this.form_settings.max_files - this.form_settings.uploaded_files;

        if (maxAllowed <= 0)
            return false;

        if (fileCount > maxAllowed) {
            data.files = data.files.splice(0, fileCount - maxAllowed + 1);
        }
        this.form_settings.uploaded_files += data.files.length;
        this.controls.drop_zone.addClass(this.control_classes.loading);
    }

    // RESPONSE should be in next format:
    // {
    //   Success: bool TRUE|FALSE
    //   ErrorMessage: string for Success = FALSE
    //   Result: array of objects { fid, image_preview }
    // }
    Drupal.onPhotoUploaded = function (e, data) {
        var response = jQuery.parseJSON(data.jqXHR.responseText);
        if (response.Success) {
            for (var i = 0; i < response.Result.length; i ++) {
                var id = response.Result[i].fid,
                    thumb = response.Result[i].image_preview;

                this.renderPhotoFile(id, thumb);
            }
            data.files.length = 0;
        } else {
            this.renderErrorMessage(response.ErrorMessage);
        }
        this.controls.drop_zone.removeClass(this.control_classes.loading);
    }

    Drupal.renderPhotoFile = function (id, thumb) {
        var item = $(this.item_template).clone(),
            order = this.controls.files_holder.children("li").length;

        item.attr("fid", id)
            .children("img").attr("src", thumb)
            .end()
            .children("div.photo-number").text(order + 1)
            .end()
            .children("input.photo-id").val(id)
            .end()
            .children("input.photo-order").val(order)
            .end()
            .find("div.photo-comment").on("click", $.proxy(this.commentUploadedFile, this))
            .end()
            .find("div.photo-remove").on("click", $.proxy(this.removeUploadedFile, this));

        this.controls.files_holder.append(item);
        this.initPhotosSorting();
    }

    Drupal.initPhotosSorting = function () {
        this.controls.files_holder.sortable({
            placeholder: "photo-placeholder",
            stop:$.proxy(this.updatePhotoNumbers, this)
        });
        this.controls.files_holder.disableSelection();
    }

    Drupal.updatePhotoNumbers = function () {
        this.controls.files_holder.children("li").each(function (index) {
            $(this).children("input.photo-order").val(index)
                   .end()
                   .children("div.photo-number").text(index + 1);
        });
    }

    Drupal.commentUploadedFile = function (event) {
        event.preventDefault();

        var item = $(event.currentTarget).parents("li"),
            comment = $("#comment"),
            input = item.children("textarea.photo-desc");

        comment.val(input.val());
        this.controls.comment_dialog.dialog({
            autoOpen: false,
            width: 350,
            height: 215,
            modal: true,
            resizable: false,
            buttons: {
                "Сохранить": function() {
                    $(this).dialog('close');
                    input.val(comment.val());
                }
            }
        }).dialog("open");
    }

    Drupal.removeUploadedFile = function (event) {
        event.preventDefault();

        var item = $(event.currentTarget).parents("li");
        $.ajax({
            url: "/admin/photo-film/file/remove/file",
            type: "POST",
            dataType: "json",
            data: {
                fid: item.attr("fid")
            },
            context: this,
            beforeSend: function () {
                item.addClass(Drupal.control_classes.loading);
            },
            success: function (response) {
                item.addClass(Drupal.control_classes.loading);
                if (response.Success) {
                    item.remove();
                    this.updatePhotoNumbers();
                    this.form_settings.uploaded_files --;

                } else {
                    this.renderErrorMessage(response.ErrorMessage);
                }
            }
        });
    }

    //TODO: refactor
    Drupal.renderErrorMessage = function (message) {
        alert(message);
    }
})(jQuery)