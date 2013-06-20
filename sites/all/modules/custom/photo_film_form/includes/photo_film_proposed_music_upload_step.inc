<?php
/**
 * File that handles the first step of the photo_film_form multi step form.
 * Including submit, validate and theme functions.
 */

/**
 * Generate third step of the photo_film_form multi step form.
 */
function photo_film_form_user_music_upload_step($form, &$form_state) {
  $form['#theme'] = array('photo_film_form_choose_theme_step_theme');
  // Attach the CSS and JS to the form
  $form['#attached'] = array(
    'css' => array(
      'type' => 'file',
      'data' => drupal_get_path('module', 'photo_film_form') . '/css/photo_film_form.css',
    ),
    'js' => array(
      'type' => 'file',
      'data' => drupal_get_path('module', 'photo_film_form') . '/js/photo-film_user_music_upload_step.js',
    ),
  );

  $form['user_file_upload'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="user-file-upload"></div>',
  );

  $form['user_file_upload'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="user-track-list"></div>',
  );

  return $form;
}

/**
 * Submit handler for photo_film_form_choose_theme_step form
 */
function photo_film_form_user_music_upload_step_submit(&$form, &$form_state) {

}

/**
 * Validate function for a photo_film_form_choose_theme_step form
 */
function photo_film_form_user_music_upload_step_validate(&$form, &$form_state) {

}