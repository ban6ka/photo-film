(function ($) {
    Drupal.behaviors.photo_film_select_picture_step = {
        attach: function (context, settings) {
            Drupal.initPhotosUploader();
        }
    }

    Drupal.initPhotosUploader = function () {
        // todo all constant in to backend!
        var maxFiles = 100,
            uploadedFilesNumber = 0;
        $("#photos-upload").fileupload({
            url: '/admin/photo-film/file/save/file',
            dataType: 'json',
            autoUpload: true,
            singleFileUploads: false,
            acceptFileTypes: /(\.|\/)(gif|jpe?g|png)$/i,
            maxNumberOfFiles: maxFiles,
            maxFileSize: 5000000, // 5 MB
            disableImagePreview: true,

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
        .bind('fileuploaddone', Drupal.renderPhotoFiles)
        .bind('fileuploadfail', function (e, data) { console.log('Processing ' + data.files[0].name + ' fail.'); });


    }

    // RESPONSE should be in next format:
    // {
    //   Success: bool TRUE|FALSE
    //   ErrorMessage: string for Success = FALSE
    //   Result: array of objects { ID, ThumbPath }
    // }
    Drupal.renderPhotoFiles = function (e, data) {
        console.log('Processing ' + data.files[0].name + ' done.');
        var uploadFilesBox = $("div.user-photos-info");
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