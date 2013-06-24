(function ($) {
    Drupal.behaviors.photo_film_themes_step = {
        attach: function (context, settings) {

            Drupal.initMusicStep();
        }
    }

    // TODO: all constant in to backend!
    Drupal.form_settings = {
        max_files: 1,
        max_weight: 10000000, // 10 MB
        accept_types: /(\.|\/)(gif|jpe?g|png)$/i,
        uploaded_files: 0
    }
    Drupal.controls = {
        uploader: null,
        drop_zone: null,
        file_holder: null,
        file_input: null,
        tracks_list: null
    }
    Drupal.control_classes = {
        loading: "loading",
        locked: "locked",
        checked: "checked"
    }
    Drupal.initMusicStep = function () {
        this.controls.uploader =  $("#track-upload");
        this.controls.drop_zone = $("div.file-uploader-holder");
        this.controls.file_holder = $("div.user-track-info");
        this.controls.file_input = $("input[name=file_fid]");
        this.controls.tracks_list = $("ul.tracks-list");

        this.controls.tracks_list.scrollbar();
        this.initTrackUploader();

        this.controls.tracks_list.children().on("click", $.proxy(this.onTrackSelected, this));
        this.controls.file_holder.children("div.remove").on("click", $.proxy(this.removeUploadedFile, this));
    }

    Drupal.initTrackUploader = function () {
        this.controls.uploader.fileupload({
            url: '/admin/photo-film/file/save/file',
            dataType: 'json',
            autoUpload: true,
            singleFileUploads: true,
            acceptFileTypes: this.form_settings.accept_types,
            maxNumberOfFiles: this.form_settings.max_files,
            maxFileSize: this.form_settings.max_weight,
            disableAudioPreview: true,

            dropZone: this.controls.drop_zone
        })
        .bind('fileuploadsend', $.proxy(this.beforeTrackUploaded, this))
        .bind('fileuploaddone', $.proxy(this.onTrackUploaded, this))
        .bind('fileuploadfail', function (e, data) { console.log('Processing ' + data.files[0].name + ' fail.'); });
    }

    Drupal.lockTracksList = function (lock) {
        if (lock) {
            this.controls.tracks_list.addClass(this.control_classes.locked)
                                     .children().removeClass(this.control_classes.checked);
        } else {
            this.controls.tracks_list.removeClass(this.control_classes.locked);
        }
    }

    Drupal.onTrackSelected = function (e) {
        var track = $(e.currentTarget),
            is_selected = track.hasClass(this.control_classes.checked);

        this.controls.tracks_list.children().removeClass(this.control_classes.checked);

        if (!is_selected) {
            track.addClass(this.control_classes.checked);
            this.controls.file_input.val(track.attr("track_id"));
            this.controls.drop_zone.addClass(this.control_classes.locked);
        } else {
            this.controls.drop_zone.removeClass(this.control_classes.locked);
            this.controls.file_input.val("");
        }
    }

    Drupal.beforeTrackUploaded = function (e, data) {
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

    // RESPONSE Format:
    // {
    //   Success: bool TRUE|FALSE
    //   ErrorMessage: string for Success = FALSE
    //   Result: array of IDs
    // }
    Drupal.onTrackUploaded = function (e, data) {
        var response = jQuery.parseJSON(data.jqXHR.responseText);
        if (response.Success) {
            for (var i = 0; i < response.Result.length; i ++) {
                var id = response.Result[i].fid,
                    file = data.files[i];

                this.renderTrackFile(id, file);
            }
            data.files.length = 0;
            this.lockTracksList(true);
        } else {
            this.renderErrorMessage(response.ErrorMessage);
        }
        this.controls.drop_zone.removeClass(this.control_classes.loading)
                               .hide();
    }

    Drupal.renderTrackFile = function (id, file) {
        this.controls.file_input.val(id);
        this.controls.file_holder.attr("fid", id)
                                 .children("div.title").text(file.name)
                                 .end()
                                 .parent().show();
    }

    Drupal.removeUploadedFile = function (event) {
        event.preventDefault();
        $.ajax({
            url: "/admin/photo-film/file/remove/file",
            type: "POST",
            dataType: "json",
            data: {
                fid: $(event.currentTarget).parent().attr("fid")
            },
            context: this,
            beforeSend: function () {
                Drupal.controls.file_holder.parent().addClass(Drupal.control_classes.loading);
            },
            success: function (response) {
                this.controls.file_holder.parent().addClass(Drupal.control_classes.loading);
                if (response.Success) {
                    this.controls.file_input.val("");
                    this.controls.file_holder.attr("fid", null);
                    this.controls.file_holder.parent().hide();

                    this.controls.drop_zone.show();
                    this.lockTracksList(false);
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