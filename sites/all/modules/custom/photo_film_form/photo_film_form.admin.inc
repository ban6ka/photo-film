<?php


/**
 * Settings form for photo_film_form module
 */
function photo_film_form_settings_form($form_state) {
  $vocabularies = taxonomy_get_vocabularies();
  $options = array();

  foreach ($vocabularies as $vocabulary) {
    $options[$vocabulary->vid] = $vocabulary->name;
  }

  $form = array();

  $form['basic'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic settings of the photo film multi step form'),
  );

  $form['basic']['photo_film_form_music_upload_destination'] = array(
    '#title' => t('Music upload destination'),
    '#description' => t('Drupal relative path'),
    '#type' => 'textfield',
    '#default_value' => variable_get('photo_film_form_music_upload_destination', ''),
    '#required' => TRUE,
  );

  $form['basic']['photo_film_form_delivery_methods'] = array(
    '#title' => t('Delivery methods'),
    '#type' => 'textarea',
    '#default_value' => variable_get('photo_film_form_delivery_methods', ''),
    '#required' => TRUE,
  );

  $form['basic']['photo_film_form_video_formats'] = array(
    '#title' => t('Video format'),
    '#type' => 'textarea',
    '#default_value' => variable_get('photo_film_form_video_formats', ''),
    '#required' => TRUE,
  );

  $form['basic']['photo_film_form_picture_upload_destination'] = array(
    '#title' => t('Pictures upload destination'),
    '#description' => t('Drupal relative path'),
    '#type' => 'textfield',
    '#default_value' => variable_get('photo_film_form_picture_upload_destination', ''),
    '#required' => TRUE,
  );

  $form['first_step'] = array(
    '#type' => 'fieldset',
    '#title' => t('Select taxonomy per step'),
  );

  $form['first_step']['photo_film_form_theme_vid'] = array(
    '#title' => t('Themes vocabulary'),
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => variable_get('photo_film_form_theme_vid', FALSE),
    '#required' => TRUE,
  );

  $form['first_step']['photo_film_form_theme_form_title'] = array(
    '#title' => t('Enter the title of the first step, which will be displayed to user'),
    '#type' => 'textarea',
    '#default_value' => variable_get('photo_film_form_theme_form_title', ''),
    '#required' => FALSE,
  );

  $form['second_step'] = array(
    '#type' => 'fieldset',
    '#title' => t('Select taxonomy for second step'),
  );

  $form['second_step']['photo_film_form_style_vid'] = array(
    '#title' => t('Styles vocabulary'),
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => variable_get('photo_film_form_style_vid', FALSE),
    '#required' => TRUE,
  );

  $form['second_step']['photo_film_form_style_form_title'] = array(
    '#title' => t('Enter the title of the second step, which will be displayed to user'),
    '#type' => 'textarea',
    '#default_value' => variable_get('photo_film_form_style_form_title', ''),
    '#required' => FALSE,
  );

  $form['third_step'] = array(
    '#type' => 'fieldset',
    '#title' => t('Third step configuration'),
  );

  $form['third_step']['photo_film_user_music_upload_step_title'] = array(
    '#title' => t('Enter the title of the third step, which will be displayed to user'),
    '#type' => 'textarea',
    '#default_value' => variable_get('photo_film_user_music_upload_step_title', ''),
    '#required' => FALSE,
  );

  $form['third_step']['photo_film_user_music_upload_step_user_warning'] = array(
    '#title' => t('Enter warning message for user'),
    '#description' => t('Warning about quantity of user music items per video'),
    '#type' => 'textarea',
    '#default_value' => variable_get('photo_film_user_music_upload_step_user_warning', ''),
    '#required' => FALSE,
  );

  $form['fourth_step'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fourth step configuration'),
  );

  $form['fourth_step']['photo_film_select_picture_step_title'] = array(
    '#title' => t('Enter the title of the fourth step, which will be displayed to user'),
    '#type' => 'textarea',
    '#default_value' => variable_get('photo_film_select_picture_step_title', ''),
    '#required' => FALSE,
  );

  $form['fourth_step']['photo_film_select_picture_step_warning'] = array(
    '#title' => t('Enter warning message for user'),
    '#description' => t('Warning about quantity of user pictures items per video'),
    '#type' => 'textarea',
    '#default_value' => variable_get('photo_film_select_picture_step_warning', ''),
    '#required' => FALSE,
  );

  $form['fifth_step'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fifth step configuration'),
  );

  $form['fifth_step']['photo_film_form_order_title'] = array(
    '#title' => t('Enter the title of the fifth step, which will be displayed to user'),
    '#type' => 'textarea',
    '#default_value' => variable_get('photo_film_form_order_title', ''),
    '#required' => FALSE,
  );

  $form['finish'] = array(
    '#type' => 'fieldset',
    '#title' => t('Finish message'),
  );

  $form['finish']['photo_film_form_success_message'] = array(
    '#title' => t('Enter success message here'),
    '#type' => 'text_format',
    '#format' => 'full_html',
    '#default_value' => variable_get('photo_film_form_success_message', ''),
    '#required' => FALSE,
  );

  return system_settings_form($form);
}
