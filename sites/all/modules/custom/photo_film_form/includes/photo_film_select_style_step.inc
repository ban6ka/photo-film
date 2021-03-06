<?php
/**
 * File that handles the second step of the photo_film_form multi step form.
 * Including submit, validate and theme functions.
 */

/**
 * Generate second step of the photo_film_form multi step form.
 */
function photo_film_form_select_style_step($form, &$form_state) {
  $previous_step_section = photo_film_form_cache_get(1);
  if (!empty($previous_step_section->theme['theme']) && $parent = $previous_step_section->theme['theme']) {
    if ($vocabulary_terms = taxonomy_get_tree(variable_get('photo_film_form_theme_vid', FALSE), $parent)) {
      // adding our theme to the first step form
      $form['#theme'] = array('photo_film_form_select_style_wrapper');
      // Attach the CSS and JS to the form
      drupal_add_js(libraries_get_path('jquery_fancybox') . '/jquery.fancybox-1.3.4.js');
      drupal_add_css(libraries_get_path('jquery_fancybox') . '/jquery.fancybox-1.3.4.css');

      $form['#attributes'] = array();
      $form['#attributes']['class'] = array();
      $form['#attributes']['class'][] = 'photo-film-form';
      // Attach the CSS and JS to the form
      $form['#attached'] = array(
        'js' => array(
          'type' => 'file',
          'data' => drupal_get_path('module', 'photo_film_form') . '/js/photo_film_style_step.js',
        ),
      );
      $form['#attributes']['class'] = array('photo-film-form');
      $options = array();
      foreach ($vocabulary_terms as $value) {
        // load term with all its fields
        $term = taxonomy_term_load($value->tid);
        // storing options, so in future we can fetch theme
        $options[$value->tid] = $value->tid;
        $image = field_get_items('taxonomy_term', $term, 'field_image');
        $video = field_get_items('taxonomy_term', $term, 'field_video_url');
        $coefficient = field_get_items('taxonomy_term', $term, 'field_coefficient');

        $form['image_' . $value->tid] = array(
          '#type' => 'value',
          '#value' => $image[0]['uri']
        );

        $form['video_' . $value->tid] = array(
          '#type' => 'value',
          '#value' => $video[0]['safe_value']
        );

        $form['title_' . $value->tid] = array(
          '#type' => 'value',
          '#value' => $term->name
        );

        $form['price_' . $value->tid] = array(
          '#type' => 'value',
          '#value' => (float) $coefficient[0]['value']
        );
      }

      $form['terms'] = array(
        '#type' => 'fieldset',
      );
      // https://api.drupal.org/comment/23168#comment-23168
      // so we should do validation by ourselfs
      $form['terms']['term_ids'] = array(
        '#attributes' => array('class' => array('radios-theme-step')),
        '#type' => 'radios',
        '#options' => $options,
        //'#required' => TRUE,
      );

      $cache = photo_film_form_cache_get(1);
      if (!empty($cache->style['style'])) {
        $form['terms']['term_ids']['#default_value'] = $cache->style['style'];
      }
    }
  }

  return $form;
}

/**
 * Submit handler for photo_film_form_select_theme_step form
 */
function photo_film_form_select_style_step_submit(&$form, &$form_state) {
  if (!empty($form_state['values']['term_ids']) && !empty($form_state['object'])) {
    $form_state['object']->current_step = $form_state['next'];
    $form_state['object']->style = array(
      'style' => $form_state['values']['term_ids']
    );
  }
}

/**
 * Validate function for a photo_film_form_select_theme_step form
 */
function photo_film_form_select_style_step_validate(&$form, &$form_state) {
  if (empty($form_state['values']['term_ids'])) {
    form_set_error('radios', t('You must choose style to proceed'));
  }
}

/**
 *  Theme function for the photo_film_form_select_theme_step form
 */
function theme_photo_film_form_select_style_wrapper($variables) {
  $form = reset($variables);

  // check if we have term ids in the form
  if (!empty($form['terms']['term_ids']['#options']) && $term_ids = $form['terms']['term_ids']['#options']) {
    $output = '';

    // loop through all terms that given in the form and add them to our output
    $items = array();
    foreach ($term_ids as $id) {
      if (!empty($form['title_' . $id]['#value']) && !empty($form['image_' . $id]['#value'])) {
        $items[] = array(
          'id' => $id,
          'image_path' => $form['image_' . $id]['#value'],
          'title' => $form['title_' . $id]['#value'],
          'video_url' => $form['video_' . $id]['#value'],
          'coefficient' => $form['price_' . $id]['#value'],
        );
      }
    }
    // adding form action attribute
    $form['#attributes']['action'] = $form['#action'];
    $output .= theme('photo_film_form_select_style_slider');
    $output .= '<form' . drupal_attributes($form['#attributes']) . '><ul class="style-list">';

    $output .= theme('photo_film_form_select_style_content', array(
      'title' => variable_get('photo_film_form_style_form_title', ''),
      'items' => $items,
    ));
    // render form "id" so drupal can process this form as usual
    $output .= drupal_render($form['form_id']);
    $output .= drupal_render($form['form_build_id']);
    $output .= drupal_render($form['form_token']);
    // render radios
    $output .= drupal_render($form['terms']['term_ids']);
    // next step submit button
    if (!empty($form['buttons']['next'])) {
      $form['buttons']['next'] = photo_film_form_render_submit_button($form['buttons']['next']);
      $output .= drupal_render($form['buttons']['next']);
    }

    $output .= '</form>';
  }

  return $output;
}