<?php
/**
 * File that handles the first step of the photo_film_form multi step form.
 * Including submit, validate and theme functions.
 */

/**
 * Generate third step of the photo_film_form multi step form.
 */
function photo_film_select_picture_step($form, &$form_state) {
  $form['#theme'] = array('photo_film_form_choose_theme_step_theme');
  // Attach the CSS and JS to the form
  drupal_add_js(libraries_get_path('jquery_file_upload') . '/js/vendor/jquery.ui.widget.js');
  drupal_add_js(libraries_get_path('jquery_file_upload') . '/js/jquery.iframe-transport.js');
  drupal_add_js(libraries_get_path('jquery_file_upload') . '/js/jquery.fileupload.js');
  $form['#attached'] = array(
    'css' => array(
      'type' => 'file',
      'data' => drupal_get_path('module', 'photo_film_form') . '/css/photo_film_form.css',
    ),
    'js' => array(
      'type' => 'file',
      'data' => drupal_get_path('module', 'photo_film_form') . '/js/photo_film_select_picture_step.js',
    ),
  );

  $form['tracks_list'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="user-track-list"></div>',
  );

  $form['user_file_upload'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="user-file-upload">' .
      '<div class="file-uploader-holder" style="width: 300px; height: 100px; border: 1px dotted #ccc;">' .
      '<div class="user-photos-info"></div>' .
      '</div>' .
      // todo remove this check "music select" step
      '<input id="photos-upload" type="file" name="photos-file[]" />' .
      '</div>',
  );

  return $form;
}

/**
 * Submit handler for photo_film_form_choose_theme_step form
 */
function photo_film_select_picture_step_submit(&$form, &$form_state) {

}

/**
 * Validate function for a photo_film_form_choose_theme_step form
 */
function photo_film_select_picture_step_validate(&$form, &$form_state) {

}