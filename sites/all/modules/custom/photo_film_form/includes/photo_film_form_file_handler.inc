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
    // if we have one file rearange structure for our upload
    if (!is_array($files['name'])) {
      foreach ($files as &$file) {
        $file = array($file);
      }
    }

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
          $result->path = file_create_url($saved->uri);
          
          // if it was an image give an url for preview          
          if ($is_image) {
            $result->image_preview = image_style_url('photo_film_style_thumb', $saved->uri);
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
  //drupal_json_output($results);
  echo drupal_json_encode($results);
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
function photo_film_form_delete_file() {
  $results = array(
    'Success' => FALSE,
    'Result' => array(),
    'ErrorMessage' => 'File could not be deleted',
  );

  if (!empty($_POST['fid']) && $file = file_load($_POST['fid'])) {
    if (file_delete($file) == TRUE) {
      $results['Success'] = TRUE;
      $results['ErrorMessage'] = "";
    }
    ;
  }

  drupal_json_output($results);
  exit;
}

/**
 * Create's order info file
 * @param $cache_object
 * @return array
 */
function photo_film_form_create_info_file($cache_object) {
  $data = '';
  /*if (!empty($cache_object->order_info)) {
    foreach ($cache_object->order_info as $key => $option) {
      $data .= $key . ' = ' . $option . ";\n";
    }
  }*/
  if (!empty($cache_object->theme['theme'])) {
    if ($term = taxonomy_term_load($cache_object->theme['theme'])) {
      $data .= t('Theme') . ' = ' . $term->name . ";\n";
    }
  }

  if (!empty($cache_object->style['style'])) {
    if ($term = taxonomy_term_load($cache_object->style['style'])) {
      $data .= t('Style') . ' = ' . $term->name . ";\n";
    }
  }


  if (!empty($cache_object->pictures)) {
    $data .= t('Picture subtitles') . "\n";
    $subtitles_initial = !empty($cache_object->pictures[0]['subtitles_initial']) ? $cache_object->pictures[0]['subtitles_initial'] : '';
    $subtitles_final = !empty($cache_object->pictures[0]['subtitles_final']) ? $cache_object->pictures[0]['subtitles_final'] : '';

    $data .= t('Initial subtitles') . ' : ' . $subtitles_initial . "\n";
    $data .= t('Final subtitles') . ' : ' . $subtitles_final . "\n";

    foreach ($cache_object->pictures as $file_info) {

      if (isset($file_info['serial_number'])) {
        $description = (!empty($file_info['description']) ? $file_info['description'] : '');
        $data .= t('Picture') . ' ' . ($file_info['serial_number'] + 1) . ':' . $description . "\n";
      }
    }
  }

  $directory = variable_get('file_temporary_path', "/tmp");
  if (file_prepare_directory($directory)) {
    // Create temporary file
    $file_name = tempnam($directory, "photo_film_info");

    // Write file
    $fp = fopen($file_name, 'w');
    $data = mb_convert_encoding($data, 'UTF-8');
    fwrite($fp, pack("CCC", 0xef, 0xbb, 0xbf));
    fwrite($fp, $data);
    // Clodse and write
    fclose($fp);

    return array(
      'real_path' => $file_name,
      'name' => 'order-info.txt'
    );
  }
}


/**
 * Get all loaded by user files
 * @param $cache_object
 * @return array
 */
function photo_film_form_prepare_files($cache_object) {
  $files = array();

  $files[] = photo_film_form_create_info_file($cache_object);
  if (!empty($cache_object->music['fid']) && $file = file_load($cache_object->music['fid'])) {
    $path_parts = pathinfo($file->uri);

    $files[] = array(
      'real_path' => drupal_realpath($file->uri),
      'name' => '/music/music.' . $path_parts['extension'],
    );
  }
  if (!empty($cache_object->pictures)) {
    foreach ($cache_object->pictures as $file_info) {
      if (!empty($file_info['fid']) && isset($file_info['serial_number']) && $file = file_load($file_info['fid'])) {
        $path_parts = pathinfo($file->uri);
        $files[] = array(
          'real_path' => drupal_realpath($file->uri),
          'name' => '/pictures/' . $file_info['serial_number'] . '.' . $path_parts['extension'],
        );
      }
    }
  }

  return $files;
}

/**
 * Create archive with the files
 * @param $files
 * @param $archive_name
 */
function photo_film_form_create_archive($files, $archive_name) {
  module_load_include('inc', 'photo_film_form', 'includes/archive');
  $zip = new zipfile();

  foreach ($files as $file) {
    $zip->addFile(file_get_contents($file['real_path']), $file['name']); // the second parameter specifies the filename in the zip
  }

  $destination = file_build_uri(variable_get('photo_film_form_archive_upload_destination', ''));

  $file = file_save_data($zip->file(), $destination . '/' . $archive_name . '.zip');

  if (empty($file)) {
    watchdog('photo_film_form_archive', t('The zip could not be created.'));
  }

  return $file;
}