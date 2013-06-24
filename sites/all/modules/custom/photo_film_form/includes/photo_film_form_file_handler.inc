<?php
/**
 * File: handlers for file upload store delete rename and archive them
 */

/**
 * Page callback for admin/photo-film/file/save
 * Stores user files
 */
function photo_film_form_save_file_wrapper() {
  $results = array(
    'Success' => FALSE,
    'Result' => array(),
    'ErrorMessage' => '',
  );

  if (!empty($_FILES)) {
    // jquery user file upload library adds it's own key which depends on input id
    $files = array_pop($_FILES);
    foreach ($files['name'] as $key => $value) {
      if (!empty($files['tmp_name'][$key]) && !empty($files['size'][$key]) && !empty($files['type'][$key])) {
        $destination = '';
        $is_image = FALSE;
        // form an array for photo_film_form_save_file function
        $file_to_save = array(
          'tmp_name' => $files['tmp_name'][$key],
          'type' => $files['type'][$key],
          'size' => $files['size'][$key],
          'name' => $value,
        );

        // depending on the file type we have different destinations
        if (strpos($file_to_save['type'], 'audio') !== FALSE) {
          $destination = variable_get('photo_film_form_music_upload_destination', '');
        }
        elseif (strpos($file_to_save['type'], 'image') !== FALSE) {
          $is_image = TRUE;
          $destination = variable_get('photo_film_form_picture_upload_destination', '');
        }
        // save file to destination and prepare results for js
        if (!empty($destination) && $saved = photo_film_form_save_file($file_to_save, $destination)) {
          $result = new stdClass();
          $result->fid = $saved->fid;
          // if it was an image give an url for preview
          if ($is_image) {
            $result->image_preview = image_style_url('photo_film_form_image_style', $saved->uri);
          }
          $results['Result'][] = $result;
        }
      }
    }
  }

  if (!empty($results['Result'])) {
    $results['Success'] = TRUE;
  }
  else {
    $results['ErrorMessage'] = t('We can\'t upload that, please, contact site administrator');
  }
  // output json for js
  drupal_json_output($results);
  exit;
}

/**
 * Helper function to store files.
 * Moves file from php temporary storage to destination and save it in to the db
 * @param $file_to_upload basically global $FILES single item
 * @param $destination to save the file
 * @return File object on success false otherwise
 */
function photo_film_form_save_file($file_to_upload, $destination) {
  // get the user which try to download file on the server
  global $user;

  $uploaded_file = FALSE;

  if (!empty($file_to_upload['tmp_name']) && $file_name = basename($file_to_upload['name'])) {
    // we need this to se whether file with this name is already exists if does that we will add _0 or _1
    $uri = file_build_uri($destination) . '/';
    $future_file_name = file_destination($uri . $file_name, FILE_EXISTS_RENAME);
    $future_file_name = explode('/', $future_file_name);
    $future_file_name = array_pop($future_file_name);

    // get the path of drupal file folder
    $file_path = variable_get('file_public_path', 'sites/default/files') . '/';

    // get the path where admin want to store a file
    $file_path .= $destination . '/' . $future_file_name;
    // try to save a file and add it to db, if not return false
    if ($file_loaded = drupal_move_uploaded_file($file_to_upload['tmp_name'], getcwd() . '/' . $file_path)) {
      // creating a file object, which will be saved in to the db
      $file = new stdClass();

      $file->uid = $user->uid;
      $file->name = $future_file_name;
      $file->uri = $uri . $future_file_name;
      $file->filemime = file_get_mimetype($file_name);
      $file->filesize = $file_to_upload['size'];
      $uploaded_file = file_save($file);
      // delete file from file usage table, so system can delete it per cron run
      file_usage_delete($uploaded_file, 'file');

    }
  }

  return $uploaded_file;
}

/**
 * Callback function for admin/photo-film/file/remove page
 */
function photo_film_form_delete_file(){
  $results = array(
    'Success' => FALSE,
    'Result' => array(),
    'ErrorMessage' => 'File could not be deleted',
  );

  if (!empty($_POST['fid']) && $file = file_load($_POST['fid'])) {
    if (file_delete($file) == TRUE) {
      $results['Success'] = TRUE;
      $results['ErrorMessage'] = "";
    };
  }


  drupal_json_output($results);
  exit;
}