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

  $form['#attributes'] = array();
  $form['#attributes']['class'] = array();
  $form['#attributes']['class'][] = 'photo-film-form';
  $form['#attributes']['class'][] = 'order-form';

  $form['title'] = array(
    '#type' => 'markup',
    '#markup' => '<h4>' . variable_get('photo_film_form_order_title', '') . '</h4>',
    '#weight' => -20,
  );

  $form['theme'] = array(
    '#type' => 'textfield',
    '#title' => t('Theme') . ':',
    '#disabled' => TRUE,
    '#value' => 'picked theme',
    '#weight' => -19
  );

  $form['style'] = array(
    '#type' => 'textfield',
    '#title' => t('Style') . ':',
    '#disabled' => TRUE,
    '#value' => 'picked style',
    '#weight' => -17
  );

  $form['music'] = array(
    '#type' => 'textfield',
    '#title' => t('Music') . ':',
    '#disabled' => TRUE,
    '#value' => 'picked music track',
    '#weight' => -15
  );

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name') . ':',
    '#weight' => -18
  );

  $form['country'] = array(
    '#type' => 'textfield',
    '#title' => t('Country') . ':',
    '#rules' => array(
      'alpha',
    ),
    '#weight' => -16
  );

  $form['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City') . ':',
    '#rules' => array(
      'alpha',
    ),
    '#weight' => -14
  );

  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email') . ':',
    '#rules' => array(
      'email',
    ),
    '#required' => TRUE,
    '#weight' => -12
  );

  $form['mobile'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile') . ':',
    '#required' => TRUE,
    '#weight' => -10
  );

  $options = photo_film_order_prepare_radios(variable_get('photo_film_form_video_formats', ''));
  $form['format'] = array(
    '#type' => 'select',
    '#title' => t('Format') . ':',
    '#required' => TRUE,
    '#options' => $options,
    '#default_value' => 'key',
    '#weight' => -13,
    '#prefix' => '<div class="form-delimeter">&nbsp;</div>'
  );

  $options = photo_film_order_prepare_radios(variable_get('photo_film_form_delivery_methods', ''));
  $form['delivery'] = array(
    '#type' => 'select',
    '#title' => t('Delivery method') . ':',
    '#required' => TRUE,
    '#default_value' => 'key',
    '#options' => $options,
    '#weight' => -11
  );

  $form['separator'] = array(
    '#type' => 'markup',
    '#markup' => '<hr class="separator" />',
    '#weight' => -9
  );

  $form['discount'] = array(
    '#type' => 'textfield',
    '#title' => t('Discount') . ':',
    '#weight' => -8
  );

  $form['total'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="form-item payment-item"><label>' . t('Pay amount') . ':</label><span>2000 </span></div>',
    '#weight' => -7
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

/**
 * Form submit function for photo_film_form_order
 */
function photo_film_form_order_submit($form, &$form_state) {
  if (!empty($form_state['object'])) {
    $form_state['object']->current_step = 'order_info';
    $form_state['object']->order_info = array(
      'name' => !empty($form_state['values']['name']) ? $form_state['values']['name'] : '',
      'country' => !empty($form_state['values']['country']) ? $form_state['values']['country'] : '',
      'city' => !empty($form_state['values']['city']) ? $form_state['values']['city'] : '',
      'email' => !empty($form_state['values']['email']) ? $form_state['values']['email'] : '',
      'mobile' => !empty($form_state['values']['mobile']) ? $form_state['values']['mobile'] : '',
      'format' => !empty($form_state['values']['format']) ? $form_state['values']['format'] : '',
      'delivery' => !empty($form_state['values']['delivery']) ? $form_state['values']['delivery'] : '',
      'discount' => !empty($form_state['values']['format']) ? $form_state['values']['format'] : '',
    );
  }
}
