<?php
/**
 * File that handles the first step of the photo_film_form multi step form.
 * Including submit, validate and theme functions.
 */

/**
 * Generate third step of the photo_film_form multi step form.
 */
function photo_film_select_picture_step($form, &$form_state) {
  unset($form['ctools_trail']);
  unset($form['buttons']['cancel']);
  unset($form['buttons']['previous']);

  // Attach the CSS and JS to the form
  drupal_add_js(libraries_get_path('jquery_file_upload') . '/js/vendor/jquery.ui.widget.js');
  drupal_add_js(libraries_get_path('jquery_file_upload') . '/js/jquery.iframe-transport.js');
  drupal_add_js(libraries_get_path('jquery_file_upload') . '/js/jquery.fileupload.js');

  $form['#theme'] = array('photo_film_form_choose_theme_step_theme');
  $form['#attributes'] = array();
  $form['#attributes']['class'] = array();
  $form['#attributes']['class'][] = 'photo-film-form';

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
  $warning = variable_get('photo_film_select_picture_step_warning', '');
  $form['user_file_upload'] = array(
    '#type' => 'markup',
    '#markup' => theme('photo_film_select_picture_step_content', array(
      'title' => variable_get('photo_film_select_picture_step_title', ''),
      'warning' => (!empty($warning['value']) ? $warning['value'] : ''),
    ))
  );

  $form['file'] = array(
    '#name' => 'photo-files[]',
    '#type' => 'file',
    '#title' => t('File'),
    '#id' => 'photos-upload',
    '#attributes' => array('multiple' => 'multiple')
  );

  return $form;
}

/**
 * Submit handler for photo_film_form_choose_theme_step form
 */
function photo_film_select_picture_step_submit(&$form, &$form_state) {
  $form_state['object']->pictures = array(
    'fids' => 'some_value',
  );
  if (!empty($form_state['values']['file_fid']) && !empty($form_state['object']->user_theme)) {
    $form_state['object']->current_step = $form_state['next'];

  }
}

/**
 * Validate function for a photo_film_form_choose_theme_step form
 */
function photo_film_select_picture_step_validate(&$form, &$form_state) {

}