<?php
/**
 * File that handles the first step of the photo_film_form multi step form.
 * Including submit, validate and theme functions.
 */

/**
 * Generate third step of the photo_film_form multi step form.
 */
function photo_film_form_user_music_upload_step($form, &$form_state) {
  $form['#theme'] = array('photo_film_select_picture_step_theme');
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
      'data' => drupal_get_path('module', 'photo_film_form') . '/js/photo_film_user_music_upload_step.js',
    ),
  );

  $form['tracks_list'] = array(
    '#type' => 'fieldset',
    '#markup' => '<div class="user-track-list"></div>',
  );

  $preselected_list = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->condition('n.status', 1)
    ->condition('n.type', 'music')
    ->execute();
  $track_list = array();

  if ($preselected_list->rowCount() > 0) {
    foreach ($preselected_list as $item) {
      // load node
      if ($music_item = node_load($item->nid)) {
        // fetch each composition
        if ($composition = field_get_items('node', $music_item, 'field_composition', $music_item->language)) {
          $track_list[] = $composition[0]['fid'];

          $form['tracks_list']['track_' . $item->nid] = array(
            '#title' => t('Track'),
            '#type' => 'markup',
            '#markup' => $music_item->title,
          );
        }
      }
    }
  }

  $form['photo_film_compositions'] = array(
    '#type' => 'radios',
    '#options' => $track_list,
  );

  $form['user_file_upload'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="user-file-upload">' .
      '<div class="file-uploader-holder" style="width: 300px; height: 100px; border: 1px dotted #ccc;">' .
      '</div>' .
      '<div class="user-track-info">test</div>' .
      '<input id="track-upload" type="file" name="track-file[]" />' .
      '</div>',
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


/**
 *  Theme function for the photo_film_form_choose_theme_step form
 */
function theme_photo_film_select_picture_step_theme($variables) {

  $form = reset($variables);
  $output = '';
  // adding form action attribute, so it looks like a normal form
  $form['#attributes']['action'] = $form['#action'];
  $output .= '<form' . drupal_attributes($form['#attributes']) . '><ul class="theme-list">';

  if (!empty($form['tracks_list'])) {
    $output .= drupal_render($form['tracks_list']);
  }

  if (!empty($form['photo_film_compositions'])) {
    $output .= drupal_render($form['photo_film_compositions']);
  }

  if (!empty($form['user_file_upload'])) {
    $output .= drupal_render($form['user_file_upload']);
  }

  // next step submit button
  if (!empty($form['buttons']['next'])) {
    $output .= drupal_render($form['buttons']['next']);
  }

  // render form "id" so drupal can process this form as usual form
  $output .= drupal_render($form['form_id']);
  $output .= drupal_render($form['form_build_id']);
  $output .= drupal_render($form['form_token']);

  $output .= '</form>';

  return $output;
}
