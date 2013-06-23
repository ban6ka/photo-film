<?php
/**
 * File that handles the second step of the photo_film_form multi step form.
 * Including submit, validate and theme functions.
 */

/**
 * Generate second step of the photo_film_form multi step form.
 */
function photo_film_form_order($form, &$form_state) {
  unset($form['ctools_trail']);
  unset($form['buttons']['cancel']);
  unset($form['buttons']['previous']);

  $form['title'] = array(
    '#type' => 'markup',
    '#markup' => '<h4>' . variable_get('photo_film_form_order_title', '') . '</h4>',
    '#weight' => -10,
  );

  $form['theme'] = array(
    '#type' => 'textfield',
    '#title' => t('Theme'),
    '#title_display' => 'none',
    '#theme' => array('photo_film_form_textfield'),
    '#disabled' => TRUE,
    '#value' => 'picked theme'
  );

  $form['style'] = array(
    '#type' => 'textfield',
    '#title' => t('Style'),
    '#title_display' => 'none',
    '#theme' => array('photo_film_form_textfield'),
    '#disabled' => TRUE,
    '#value' => 'picked style'
  );

  $form['music'] = array(
    '#type' => 'textfield',
    '#title' => t('Music'),
    '#title_display' => 'none',
    '#theme' => array('photo_film_form_textfield'),
    '#disabled' => TRUE,
    '#value' => 'picked music track'
  );

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#title_display' => 'none',
    '#theme' => array('photo_film_form_textfield'),
  );

  $form['country'] = array(
    '#type' => 'textfield',
    '#title' => t('Country'),
    '#title_display' => 'none',
    '#theme' => array('photo_film_form_textfield'),
  );

  $form['city'] = array(
    '#type' => 'textfield',
    '#title' => t('Country'),
    '#title_display' => 'none',
    '#theme' => array('photo_film_form_textfield'),
  );

  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#title_display' => 'none',
    '#required' => TRUE,
    '#theme' => array('photo_film_form_textfield'),
  );

  $form['mobile'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile'),
    '#title_display' => 'none',
    '#required' => TRUE,
    '#theme' => array('photo_film_form_textfield'),
  );

  $form['format'] = array(
    '#type' => 'select',
    '#title' => t('Format'),
    '#required' => TRUE,
    '#options' => array(),
  );

  $options = photo_film_order_prepare_radios(variable_get('photo_film_form_video_formats', ''));
  $form['format'] = array(
    '#type' => 'select',
    '#title' => t('Format'),
    '#required' => TRUE,
    '#options' => $options,
    '#title_display' => 'none',
    '#theme' => array('photo_film_form_select'),
  );

  $options = photo_film_order_prepare_radios(variable_get('photo_film_form_delivery_methods', ''));
  $form['delivery'] = array(
    '#type' => 'select',
    '#title' => t('Delivery method'),
    '#required' => TRUE,
    '#title_display' => 'none',
    '#options' => $options,
    '#theme' => array('photo_film_form_select'),
  );
  $form['discount'] = array(
    '#type' => 'textfield',
    '#title' => t('Discount'),
    '#title_display' => 'none',
    '#theme' => array('photo_film_form_textfield'),
  );

  return $form;
}

/**
 * Helper function to parce string(key|value) and return an array
 * @param $text text with options
 */
function photo_film_order_prepare_radios($text) {
  $result = array();
  $options_sets = explode("\n", $text);
  foreach ($options_sets as $set) {
    $option = explode('|', $set);
    if (!empty($option[0]) && !empty($option[1])) {
      $result[$option[0]] = $option[1];
    }
  }

  return $result;
}