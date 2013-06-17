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

  $form['vocabularies'] = array(
    '#type' => 'fieldset',
    '#title' => t('Select taxonomy per step'),
  );

  $form['vocabularies']['photo_film_form_themes_vid'] = array(
    '#title' => t('Themes vocabulary'),
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => variable_get('photo_film_form_themes_vid', FALSE),
    '#required' => TRUE,
  );

  $form['vocabularies']['photo_film_form_styles_vid'] = array(
    '#title' => t('Styles vocabulary'),
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => variable_get('photo_film_form_styles_vid', FALSE),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

