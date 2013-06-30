<?php

/**
 * @file
 * Single step of photo_film_form pane
 */

/**
 * Callback function to supply a list of content types.
 */
function photo_film_form_single_step_pane_ctools_content_types() {
  return array(
    'title' => t('Single step pane'),
    'single' => TRUE,
    'content_types' => array(''),
    'render callback' => 'photo_film_form_single_step_pane_render',
    'edit form' => 'photo_film_form_single_step_pane_edit_form',
    'category' => t('Photo film'),
  );
}

/**
 * Run-time rendering single step of multiple photo_film_form form
 */
function photo_film_form_single_step_pane_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->title = t('Single step of the photo_film_form form');
  $block->content = '';

  // Define array for ctools multistep wizard.
  $form_info = photo_film_form_ctools_multi_step_form_info();
  $object_id = 1;
  if (!empty($args)) {
    $step = array_pop($args);
  }

  // This automatically gets defaults if there wasn't anything saved.
  $object = photo_film_form_cache_get($object_id);
  // live $form_state changes.
  $form_state = array(
    'ajax' => 0,
    // Put our object and ID into the form state cache so we can easily find it.
    'object_id' => $object_id,
    'object' => &$object,
  );
  // Send this all off to our form. This is like drupal_get_form only wizardly.
  ctools_include('wizard');
  $form = ctools_wizard_multistep_form($form_info, $step, $form_state);

  if (!empty($form)) {
    $output = drupal_render($form);
  }

  if (empty($output) || !empty($form_state['complete'])) {
    //success callback should be here
    $output = '';
  }

  $steps = array();

  foreach ($form_info['order'] as $key => $single_step) {
    $attributes = array();
    // add next class to the next step
    if (!empty($form_state['next']) && $form_state['next'] == $key) {
      $attributes = array('attributes' => array('class' => array('next')));
    }
    $steps[$key] = array('title' => $single_step, 'href' => 'photo-film-form/nojs/' . $key, 'attributes' => $attributes);
  }

  $block->content = theme('photo_film_form_breadcrumb', array(
    'steps' => $steps,
    'current' => $step
  ));
  $block->content .= $output;

  return $block;
}

/**
 * Edit form for photo_film_form_pane
 * @param $form
 * @param $form_state
 * @return mixed
 */
function photo_film_form_single_step_pane_edit_form($form, $form_state) {

  return $form;
}
