(function ($) {
    Drupal.behaviors.photo_film_themes_step = {
        attach: function (context, settings) {

            Drupal.initTrackUploader();
        }
    }

    Drupal.initTrackUploader = function () {
        // todo all constant in to backend!
        var maxFiles = 1,
            uploadedFilesNumber = 0;
        $("#track-upload").fileupload({
            url: '/admin/photo-film/file/save/file',
            dataType: 'json',
            autoUpload: true,
            singleFileUploads: true,
            acceptFileTypes: /(\.|\/)(gif|jpe?g|png)$/i,
            maxNumberOfFiles: maxFiles,
            maxFileSize: 5000000, // 5 MB
            disableAudioPreview: true,

            dropZone: $('div.file-uploader-holder')
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
        //.bind('fileuploadsend', function (e, data) {/* ... */})
        .bind('fileuploaddone', Drupal.renderTrackFile)
        .bind('fileuploadfail', function (e, data) { console.log('Processing ' + data.files[0].name + ' fail.'); });


    }

    // RESPONSE should be in next format:
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
})(jQuery)