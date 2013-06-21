(function ($) {
    Drupal.behaviors.photo_film_themes_step = {
        attach: function (context, settings) {

            Drupal.initTrackUploader();
        }
    }

    Drupal.initTrackUploader = function () {
        // todo all constant in to backend!
        $("#track-upload").fileupload({
            url: '/admin/photo-film/music/save/file',
            dataType: 'json',
            autoUpload: true,
            acceptFileTypes: /(\.|\/)(gif|jpe?g|png)$/i,
            maxNumberOfFiles: 1,
            maxFileSize: 5000000, // 5 MB

            dropZone: $('div.file-uploader-holder'),
            filesContainer: $('div.user-track-info'),
            /*drop: function (e, data) {
                $.each(data.files, function (index, file) {
                    alert('Dropped file: ' + file.name);
                });
            }*/
        });
    }
})(jQuery)