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
    '#title' => t('Enter the title of the first step, which will be displayed to user'),
    '#type' => 'textarea',
    '#default_value' => variable_get('photo_film_form_style_form_title', ''),
    '#required' => FALSE,
  );

  return system_settings_form($form);
}
