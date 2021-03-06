<?php
/**
 * File that handles the first step of the photo_film_form multi step form.
 * Including submit, validate and theme functions.
 */

/**
 * Generate first step of the photo_film_form multi step form.
 */
function photo_film_form_select_theme_step($form, &$form_state) {
  if ($themes_vocabulary_vid = variable_get('photo_film_form_theme_vid', FALSE)) {
    if ($vocabulary_terms = taxonomy_get_tree($themes_vocabulary_vid)) {
      // adding our theme to the first step form
      $form['#theme'] = array('photo_film_form_select_theme_wrapper');
      $form['#attributes'] = array();
      $form['#attributes']['class'] = array();
      $form['#attributes']['class'][] = 'photo-film-form';
      // Attach the CSS and JS to the form
      $form['#attached'] = array(
        'css' => array(
          'type' => 'file',
          'data' => drupal_get_path('module', 'photo_film_form') . '/css/photo_film_form.css',
        ),
        'js' => array(
          'type' => 'file',
          'data' => drupal_get_path('module', 'photo_film_form') . '/js/photo_film_theme_step.js',
        ),
      );
      $options = array();
      foreach ($vocabulary_terms as $value) {
        if ($value->depth == 0) {
          // load term with all its fields
          $term = taxonomy_term_load($value->tid);
          // storing options, so in future we can fetch theme
          $options[$value->tid] = $value->tid;
          $image = field_get_items('taxonomy_term', $term, 'field_image');

          $form['image_' . $value->tid] = array(
            '#type' => 'value',
            '#value' => $image[0]['uri']
          );

          $form['title_' . $value->tid] = array(
            '#type' => 'value',
            '#value' => $term->name
          );
        }
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
      if (!empty($cache->theme['theme'])) {
        $form['terms']['term_ids']['#default_value'] = $cache->theme['theme'];
      }
    }
  }

  return $form;
}

/**
 * Submit handler for photo_film_form_select_theme_step form
 */
function photo_film_form_select_theme_step_submit(&$form, &$form_state) {
  if (!empty($form_state['values']['term_ids']) && !empty($form_state['object'])) {
    $form_state['object']->current_step = $form_state['next'];
    $form_state['object']->theme = array(
      'theme' => $form_state['values']['term_ids']
    );
  }
}

/**
 * Validate function for a photo_film_form_select_theme_step form
 */
function photo_film_form_select_theme_step_validate(&$form, &$form_state) {
  if (empty($form_state['values']['term_ids'])) {
    form_set_error('radios', t('You must choose theme to proceed'));
  }
}

/**
 *  Theme function for the photo_film_form_choose_theme_step form
 */
function theme_photo_film_form_select_theme_wrapper($variables) {
  $form = reset($variables);
  $output = '';
  // check if we have term ids in the form
  if (!empty($form['terms']['term_ids']['#options']) && $term_ids = $form['terms']['term_ids']['#options']) {
    // adding form action attribute, so it looks like a normal form
    $form['#attributes']['action'] = $form['#action'];
    $output .= '<form' . drupal_attributes($form['#attributes']) . '>';

    // loop through all terms that given in the form and add them to our output
    $items = array();
    foreach ($term_ids as $id) {
      if (!empty($form['title_' . $id]['#value']) && !empty($form['image_' . $id]['#value'])) {
        $items[] = array(
          'id' => $id,
          'image_path' => $form['image_' . $id]['#value'],
          'title' => $form['title_' . $id]['#value'],
        );
      }
    }

    $output .= theme('photo_film_form_select_theme_content', array(
      'title' => variable_get('photo_film_form_theme_form_title', ''),
      'items' => $items,
    ));

    // render form "id" so drupal can process this form as usual form
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