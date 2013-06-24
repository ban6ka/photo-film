(function ($) {
    Drupal.behaviors.photo_film_themes_step = {
        attach: function (context, settings) {

            Drupal.initTrackUploader();
        }
    }

    Drupal.controls = {
        uploader: null,
        drop_zone: null,
        file_holder: null,
        tracks_list: null
    }

    // todo all constant in to backend!
    Drupal.form_settings = {
        max_files: 1,
        max_weight: 10000000, // 10 MB
        accept_types: /(\.|\/)(gif|jpe?g|png)$/i,
        uploaded_files: 0
    }
    Drupal.initTrackUploader = function () {
        this.controls.uploader =  $("#track-upload");
        this.controls.drop_zone = $("div.file-uploader-holder");
        this.controls.file_holder = $("div.user-track-info");
        this.controls.tracks_list = $("ul.tracks-list");

        this.controls.tracks_list.scrollbar();

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
        .bind('fileuploadsend', function (e, data) {
            var fileCount = data.files.length,
                maxAllowed = maxFiles - uploadedFilesNumber;

            if (maxAllowed <= 0)
                return false;

            if (fileCount > maxAllowed) {
                data.files = data.files.splice(0, fileCount - maxAllowed + 1);
            }
            uploadedFilesNumber += data.files.length;
        })
        .bind('fileuploaddone', Drupal.renderTrackFile)
        .bind('fileuploadfail', function (e, data) { console.log('Processing ' + data.files[0].name + ' fail.'); });


    }

    // RESPONSE Format:
    // {
    //   Success: bool TRUE|FALSE
    //   ErrorMessage: string for Success = FALSE
    //   Result: array of IDs
    // }
    Drupal.renderTrackFile = function (e, data) {
        console.log('Processing ' + data.files[0].name + ' done.');
        var uploadFilesBox = $("div.user-track-info");
        $.each(data.files, function (index, file) {
            var newFileDiv = $("<div class='uploadBox' id='fileDiv_" + file.name + "'><div class='leftEle'><a href='#' id='link_" + index + "' class='removeFile'>Remove</a></div><div class='midEle'>" + file.name + "</div></div>");
            uploadFilesBox.append(newFileDiv);

            newFileDiv.find('a').on('click', { filename: file.name, files: data.files }, function (event) {
                event.preventDefault();
                var uploadFilesBox = uploadFilesBox;
                var remDiv = $(document.getElementById("fileDiv_" + event.data.filename));
                remDiv.remove();
                data.files.length = 0;    //zero out the files array
            });

            data.context = newFileDiv;
        });

        $('#myButton').click(function () {
            if (data.files.length > 0) {     //only submit if we have something to upload
                data.submit();
            }
        });
    }

    Drupal.removeUploadedFile = function (event) {
        event.preventDefault();
        $.ajax({

        });
        var remDiv = $(document.getElementById("fileDiv_" + event.data.filename));
        remDiv.remove();
        data.files.length = 0;
    }
})(jQuery)