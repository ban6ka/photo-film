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
  // get the form previous step info
  $cache = photo_film_form_cache_get(1);

  drupal_add_js(libraries_get_path('jquery_maskedinput') . '/jquery.maskedinput.min.js');

  $form['#attributes'] = array();
  $form['#attributes']['class'] = array();
  $form['#attributes']['class'][] = 'photo-film-form';
  $form['#attributes']['class'][] = 'order-form';

  $form['#attached'] = array(
    'js' => array(
      'type' => 'file',
      'data' => drupal_get_path('module', 'photo_film_form') . '/js/photo_film_order_step.js',
    ),
  );

  $info = variable_get('photo_film_form_order_info', '');
  $form['info'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="info-block-wrap">' .
                    '<a class="close-info" href="#">' . t("close") . '&nbsp;&nbsp;&nbsp;x</a>' .
                    '<div class="info-message">' . (!empty($info['value']) ? $info['value'] : '') . '</div>' .
                    '<a class="open-info" href="#">' . t("Info") . '</a>' .
                 '</div>',
    '#weight' => -21,
  );

  $form['title'] = array(
    '#type' => 'markup',
    '#markup' => '<h4>' . variable_get('photo_film_form_order_title', '') . '</h4>',
    '#weight' => -20,
  );

  $form['theme'] = array(
    '#type' => 'textfield',
    '#title' => t('Theme') . ':',
    '#disabled' => TRUE,
    '#weight' => -19
  );
  // provide value that user picked up at first step
  if (!empty($cache->theme['theme']) && $theme = $cache->theme['theme']) {
    $theme = taxonomy_term_load($theme);
    $form['theme']['#value'] = (!empty($theme->name) ? $theme->name : '');
  }

  $form['style'] = array(
    '#type' => 'textfield',
    '#title' => t('Style') . ':',
    '#disabled' => TRUE,
    '#weight' => -17
  );
  // provide value that user picked up at second step
  if (!empty($cache->style['style']) && $style = $cache->style['style']) {
    $style = taxonomy_term_load($style);
    $form['style']['#value'] = (!empty($style->name) ? $style->name : '');
  }

  $form['music'] = array(
    '#type' => 'textfield',
    '#title' => t('Music') . ':',
    '#disabled' => TRUE,
    '#value' => 'picked music track',
    '#weight' => -15
  );

  // provide value that user picked up at third step
  if (!empty($cache->music['fid']) && $music = $cache->music['fid']) {
    $file = file_load($music);
    $path_parts = isset($file->uri) ? pathinfo($file->uri) : '';

    $form['music']['#value'] = (!empty($path_parts['basename']) ? $path_parts['basename'] : '');
  }

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name') . ':',
    '#required' => TRUE,
    '#default_value' => (!empty($cache->order_info['name']) ? $cache->order_info['name'] : ''),
    '#weight' => -14
  );

  $form['country'] = array(
    '#type' => 'textfield',
    '#title' => t('Country') . ':',
    '#value' => t('Ukraine'),
    '#disabled' => TRUE,
    '#required' => TRUE,
    '#weight' => -18
  );

  $form['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City') . ':',
    '#rules' => array(
      'alpha',
    ),
    '#required' => TRUE,
    '#autocomplete_path' => 'taxonomy/autocomplete/field_city',
    '#weight' => -16
  );

  if (!empty($cache->order_info['city']) && $city = taxonomy_term_load($cache->order_info['city'])) {
    $form['city']['#default_value'] = $city->name; 
  }

  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email') . ':',
    '#rules' => array(
      'email',
    ),
    '#default_value' => (!empty($cache->order_info['email']) ? $cache->order_info['email'] : ''),
    '#required' => TRUE,
    '#weight' => -12
  );

  $form['mobile'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile') . ':',
    '#default_value' => (!empty($cache->order_info['mobile']) ? $cache->order_info['mobile'] : ''),
    '#required' => TRUE,
    '#weight' => -10
  );

  $options = array('' => t('Select'));
  if ($themes_vocabulary_vid = variable_get('photo_film_form_video_formats_vid', FALSE)) {
    if ($terms = taxonomy_get_tree($themes_vocabulary_vid)) {
      foreach ($terms as $term) {
        $options[$term->tid] = $term->name;
      }
    }
  }

  $form['format'] = array(
    '#type' => 'select',
    '#title' => t('Format') . ':',
    '#required' => TRUE,
    '#options' => $options,
    '#default_value' => (!empty($cache->order_info['format']) ? $cache->order_info['format'] : ''),
    '#ajax' => array(
      'callback' => 'photo_film_form_order_get_amount',
      'wrapper' => 'order-amount',
      'method' => 'replace',
      'effect' => 'none',
    ),
    '#weight' => -13,
    '#prefix' => '<div class="form-delimeter">&nbsp;</div>'
  );

  $options = array('' => t('Select'));
  if ($themes_vocabulary_vid = variable_get('photo_film_form_delivery_methods_vid', FALSE)) {
    if ($terms = taxonomy_get_tree($themes_vocabulary_vid)) {
      foreach ($terms as $term) {
        $options[$term->tid] = $term->name;
      }
    }
  }

  $form['delivery'] = array(
    '#type' => 'select',
    '#title' => t('Delivery method') . ':',
    '#required' => TRUE,
    '#default_value' => (!empty($cache->order_info['delivery']) ? $cache->order_info['delivery'] : ''),
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
    '#default_value' => (!empty($cache->order_info['discount']['code']) ? $cache->order_info['discount']['code'] : ''),
    '#weight' => -8
  );

  $form['apply_discount'] = array(
    '#type' => 'submit',
    '#value' => t('Apply'),
    '#prefix' => '<div class="form-item form-item-apply-btn">',
    '#ajax' => array(
      'callback' => 'photo_film_form_order_apply_discount',
      'wrapper' => 'order-amount',
      'method' => 'replace',
      'effect' => 'none',
    ),
    '#tree' => 'TRUE',
    '#suffix' => '</div>',
    '#weight' => -7
  );

  // next step submit button
  if (!empty($form['buttons']['next'])) {
    $form['buttons']['next'] = photo_film_form_render_submit_button($form['buttons']['next'], "");
  }

  $amount = photo_film_form_calculate_amount($cache);
  $form['total'] = photo_film_form_order_get_amount_element($amount);

  array_push($form['#submit'], 'photo_film_form_insert_order');
  
  return $form;
}

/**
 * Form submit function for photo_film_form_order
 */
function photo_film_form_order_submit($form, &$form_state) {
  if (!empty($form_state['object'])) {
    $form_state['object']->current_step = 'order_info';
    $form_state['object']->order_info = array(
      'id' => photo_film_form_get_next_order_id(),
      'name' => !empty($form_state['values']['name']) ? $form_state['values']['name'] : '',
      'country' => !empty($form_state['values']['country']) ? $form_state['values']['country'] : '',
      'city' => !empty($form_state['values']['city']) ? $form_state['values']['city'] : '',
      'email' => !empty($form_state['values']['email']) ? $form_state['values']['email'] : '',
      'mobile' => !empty($form_state['values']['mobile']) ? $form_state['values']['mobile'] : '',
      'format' => !empty($form_state['values']['format']) ? $form_state['values']['format'] : '',
      'delivery' => !empty($form_state['values']['delivery']) ? $form_state['values']['delivery'] : '',
      'discount' => array(
        'code' => !empty($form_state['values']['discount']) ? $form_state['values']['discount'] : '',
        'value' => photo_film_form_order_get_discount($form_state['values']['discount']),
      )
    );

 //   $form_state['object']->order_info['discount']['value'] = !empty($form_state['values']['discount']) ? $form_state['values']['discount'] : '';
  }
}

/**
 * Validate function for photo_film_form_order form
 */
function photo_film_form_order_validate($form, &$form_state) {
  if (!empty($form_state['values']['city'])) {
    if ($terms = taxonomy_get_term_by_name($form_state['values']['city'], 'cities')) {
     $term = array_pop($terms);
     $form_state['values']['city'] = $term->tid;
    }
    else {
     form_set_error('city', t('City doesn\'t exists'));
    }
  }
}
