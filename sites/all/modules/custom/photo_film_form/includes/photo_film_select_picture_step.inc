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

  drupal_add_library('system', 'ui');
  drupal_add_css(drupal_get_path('module', 'jquery_update') . '/replace/ui/themes/base/jquery-ui.css');
  drupal_add_css(drupal_get_path('module', 'jquery_update') . '/replace/ui/themes/base/jquery.ui.dialog.css');

  drupal_add_js(array('photo_settings' => array(
    'max_files' => 100,
    'max_weight' => 10485760, // 10 MB
    'accept_types' => '(\.|\/)(gif|jpe?g|png)$'
  )), 'setting');

  // get the form previous step info
  $cache = photo_film_form_cache_get(1);

  $form['#theme'] = array('photo_film_form_choose_theme_step_theme');
  $form['#attributes'] = array();
  $form['#attributes']['class'] = array();
  $form['#attributes']['class'][] = 'photo-film-form';

  $form['#attached'] = array(
    'js' => array(
      'type' => 'file',
      'data' => drupal_get_path('module', 'photo_film_form') . '/js/photo_film_photo_step.js',
    ),
  );
     
  $form['user_file_upload'] = array(
    '#type' => 'markup',
    '#markup' => theme('photo_film_select_picture_step_content', array(
      'title' => variable_get('photo_film_select_picture_step_title', ''),
      'help_text' => variable_get('photo_film_select_picture_step_drop_zone_message', ''),
    ))
  );

  $warning = variable_get('photo_film_select_picture_step_warning', '');
  
  if (!empty($cache->music['playtime']) && !empty($warning['value'])) {
    // make token replacement
    $warning['value'] = str_replace('[%min]', round($cache->music['playtime'] / 5), $warning['value']);
    $warning['value'] = str_replace('[%max]', round($cache->music['playtime'] / 3), $warning['value']);
    // add warning on the form user man and min file upload
    $form['user_file_upload']['#markup']['warning'] = $warning['value'];
  }

  $form['file'] = array(
    '#name' => 'photo-files[]',
    '#type' => 'file',
    '#title' => t('File'),
    '#id' => 'photos-upload',
    '#attributes' => array('multiple' => 'multiple', 'accept' => 'image/*')
  );

  // next step submit button
  if (!empty($form['buttons']['next'])) {
    $form['buttons']['next'] = photo_film_form_render_submit_button($form['buttons']['next']);
  }

  return $form;
}

/**
 * Submit handler for photo_film_form_choose_theme_step form
 */
function photo_film_select_picture_step_submit(&$form, &$form_state) {
  if (!empty($form_state['input']['photos_id']) && !empty($form_state['object'])) {
    $form_state['object']->current_step = $form_state['next'];
    $form_state['object']->pictures = array();

    foreach ($form_state['input']['photos_id'] as $key => $fid) {
      $serial_number =(!empty($form_state['input']['photos_order'][$key]) ? $form_state['input']['photos_order'][$key] : 0);
      $description = (!empty($form_state['input']['photos_comment'][$key]) ? $form_state['input']['photos_comment'][$key] : '');
      $form_state['object']->pictures[] = array(
        'fid' => $fid,
        'serial_number' => $serial_number,
        'description' => $description,
      );
    }
  }
}

/**
 * Validate function for a photo_film_form_choose_theme_step form
 */
function photo_film_select_picture_step_validate(&$form, &$form_state) {
  if (empty($form_state['input']['photos_id'])) {
    form_set_error('op', t('You should upload photos for the video'));
  }
}