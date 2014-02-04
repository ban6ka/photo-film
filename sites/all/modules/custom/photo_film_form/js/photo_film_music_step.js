(function ($) {
    Drupal.behaviors.photo_film_themes_step = {
        attach: function (context, settings) {
            $('audio').mediaelementplayer();
            
            jQuery.each((Drupal.settings.music_settings), function(key, value) {
                Drupal.form_settings[key] = value;
            });
            // try to fetch duration of the audio track
            $('#photo-film-form-select-music-step').submit(function() {
                var fid = $('input[name="file_fid"]').val();
                if (fid != undefined) {
                    var $musicItem = $('li[track_id="' + fid + '"]');
                    if ($musicItem.length ==0) {
                        $musicItem = $('div.user-track-wrap');
                    }
                }

                if ($musicItem != undefined && $musicItem.length > 0) {
                    var duration = $musicItem.find('span.mejs-duration');
                    if (duration.length != 0) {
                        $('input[name="audio_length"]').val(duration.text());                        
                    }
                }

            })
            
            Drupal.initMusicStep();
        }
    }

    Drupal.form_settings = {
        max_files: null,
        max_weight: null,
        accept_types: null,
        uploaded_files: 0
    }
    Drupal.controls = {
        uploader: null,
        uploader_wrap: null,
        drop_zone: null,
        file_holder: null,
        file_input: null,
        tracks_list: null,
        tracks_items: null,
        refuse_input: null
    }
    Drupal.control_classes = {
        loading: "loading",
        locked: "locked",
        checked: "checked"
    }
    Drupal.initMusicStep = function () {
        this.controls.uploader =  $("#track-upload");
        this.controls.uploader_wrap = $("div.form-type-file");
        this.controls.drop_zone = $("div.file-uploader-holder");
        this.controls.file_holder = $("div.user-track-info");
        this.controls.file_input = $("input[name=file_fid]");
        if (this.controls.file_input.val().length != 0) {
            $("div.form-button-wrap").addClass('active');
        }
        
        this.controls.tracks_list = $("ul.tracks-list");
        this.controls.tracks_items = this.controls.tracks_list.find("li.track-item");
        this.controls.refuse_input = $("#refuse-music-checkbox");

        this.controls.tracks_list.scrollbar();
        this.initTrackUploader();

        this.controls.tracks_items.on("click", $.proxy(this.onTrackSelected, this));
        this.controls.file_holder.children("div.remove").on("click", $.proxy(this.removeUploadedFile, this));
        this.controls.refuse_input.on("click", $.proxy(this.onRefuseClicked, this));
    }

    Drupal.initTrackUploader = function () {
        this.controls.uploader.fileupload({
            url: '/admin/photo-film/file/save/file',
            type: 'POST',
            dataType: 'json',
            autoUpload: true,
            singleFileUploads: false,
            acceptFileTypes: this.form_settings.accept_types,
            maxNumberOfFiles: this.form_settings.max_files,
            maxFileSize: this.form_settings.max_weight,
            disableAudioPreview: true,

            fileInput: this.controls.uploader,
            replaceFileInput: jQuery.browser.msie ? true : false,
            dropZone: this.controls.drop_zone
        })
        .bind('fileuploadsend', $.proxy(this.beforeTrackUploaded, this))
        .bind('fileuploaddone', $.proxy(this.onTrackUploaded, this));

        if (!jQuery.browser.msie) {
            this.controls.uploader_wrap.addClass("hidden");
            this.controls.drop_zone.on("click", function (e) {
                e.preventDefault();
                if (!($(this).hasClass(Drupal.control_classes.locked) || $(this).hasClass(Drupal.control_classes.loading)))
                    Drupal.controls.uploader.click()
            });
        } else {
            var txt = this.controls.drop_zone.children("span");
            txt.text(txt.text().substring(0, txt.text().indexOf(" или перетащите")));
        }
    }

    Drupal.lockTracksList = function (lock) {
        if (lock) {
            this.controls.tracks_list.addClass(this.control_classes.locked);
            this.controls.tracks_items.removeClass(this.control_classes.checked);
        } else {
            this.controls.tracks_list.removeClass(this.control_classes.locked);
        }
        this.enableSubmitButton();
    }

    Drupal.lockTracksUploader = function (lock) {
        if (lock) {
            this.controls.drop_zone.addClass(this.control_classes.locked);
        } else {
            this.controls.drop_zone.removeClass(this.control_classes.locked);
        }
        if (jQuery.browser.msie) {
            this.controls.uploader_wrap.css("display", lock ? "none" : "block");
        }
        this.enableSubmitButton();
    }

    Drupal.onTrackSelected = function (e) {
        var track = $(e.currentTarget),
            is_selected = track.hasClass(this.control_classes.checked);

        this.controls.tracks_items.removeClass(this.control_classes.checked);

        if (!is_selected) {
            track.addClass(this.control_classes.checked);
            this.controls.file_input.val(track.attr("track_id"));
        } else {
            this.controls.file_input.val("");
        }
        this.lockTracksUploader(!is_selected);
    }

    Drupal.beforeTrackUploaded = function (e, data) {
        var fileCount = data.files.length,
            maxAllowed = this.form_settings.max_files - this.form_settings.uploaded_files,
            fileType = new RegExp(this.form_settings.accept_types, "i"),
            fileSize = this.form_settings.max_weight,
            errorMessage = "";

        if (maxAllowed <= 0)
            return false;

        if (fileCount > maxAllowed) {
            data.files = data.files.splice(0, fileCount - maxAllowed + 1);
            errorMessage = "<p>Вы не можете загрузить больше " + maxAllowed + " файла</p>";
        }

        for (var index = 0; index < data.files.length; index ++) {
            if (!fileType.test(data.files[index].name) || fileSize < data.files[index].size) {
                data.files.splice(index, 1);
                errorMessage = ("Разрешены только аудио файлы (mp3|waw|flac), не более " + Math.round(fileSize / 1024 / 1024) + "МБ.");
                index -= 1;
            }
        }

        if (data.files.length) {
            this.form_settings.uploaded_files += data.files.length;
            this.controls.drop_zone.addClass(this.control_classes.loading);
        } else {
            this.renderErrorMessage(errorMessage);
            return false;
        }
    }

    // RESPONSE Format:
    // {
    //   Success: bool TRUE|FALSE
    //   ErrorMessage: string for Success = FALSE
    //   Result: array of IDs
    // }
    Drupal.onTrackUploaded = function (e, data) {
        var response = data._response.result;
        if (response.Success) {
            for (var i = 0; i < response.Result.length; i ++) {
                var id = response.Result[i].fid,
                    file = data.files[i];
                    path = response.Result[i].path;
                this.renderTrackFile(id, file, path);
            }
            data.files.length = 0;
            this.lockTracksList(true);
        } else {
            this.renderErrorMessage(response.ErrorMessage);
        }

        this.controls.drop_zone.removeClass(this.control_classes.loading)
                               .hide();
        if (jQuery.browser.msie) {
            this.controls.uploader_wrap.hide();
        }
    }

    Drupal.renderTrackFile = function (id, file, path) {
        this.controls.file_input.val(id);
        this.controls.file_holder.attr("fid", id)
                                 .children("div.title").html(file.name + '<audio type="audio/mpeg" src="' + path + '"></audio>')
                                 .end()
                                 .parent().show();
         $('audio').mediaelementplayer();
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
                this.controls.file_holder.parent().removeClass(Drupal.control_classes.loading);
                if (response.Success) {
                    this.controls.uploader[0].value = "";

                    this.controls.file_input.val("");
                    this.controls.file_holder.attr("fid", null);
                    this.form_settings.uploaded_files -= 1;

                    this.controls.file_holder.parent().hide();
                    this.controls.drop_zone.show();
                    if (jQuery.browser.msie) {
                        this.controls.uploader_wrap.show();
                    }

                    this.lockTracksList(this.controls.refuse_input.is(":checked"));
                } else {
                    this.renderErrorMessage(response.ErrorMessage);
                }

            }
        });
    }

    Drupal.onRefuseClicked = function () {
        var is_checked = this.controls.refuse_input.is(":checked");
        if (is_checked && this.form_settings.uploaded_files > 0) {
            this.controls.file_holder.children("div.remove").click();
        }
        this.lockTracksUploader(is_checked);
        this.lockTracksList(is_checked);
    }

    Drupal.renderErrorMessage = function (message) {
        var error = $("#music-error");
        error.html(message)
             .fadeIn(250);
        window.setTimeout(function () {
            error.fadeOut(500);
        }, 5000);
    }

    Drupal.enableSubmitButton = function () {
        var wrap = $("div.form-button-wrap");
        if (this.controls.refuse_input.is(":checked")
            || this.form_settings.uploaded_files > 0
            || this.controls.tracks_items.filter("." + this.control_classes.checked).length) {
            
            wrap.addClass("active");

        } else {
            wrap.removeClass("active");
        }
    }
})(jQuery)