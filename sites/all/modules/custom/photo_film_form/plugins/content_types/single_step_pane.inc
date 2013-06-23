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
  $form_info = array(
    'id' => 'photo_film_form',
    'path' => "photo-film-form/nojs/%step",
    'show trail' => TRUE,
    'show back' => TRUE,
    'show cancel' => TRUE,
    'show return' => FALSE,
    'next callback' => 'photo_film_form_wizard_next',
    'finish callback' => 'photo_film_form_wizard_finish',
    'cancel callback' => 'photo_film_form_wizard_cancel',
    // we need to override this
    'order' => array(
      'themes' => t('Select theme for your video'),
      'styles' => t('Select style for your video'),
      'user_music_upload' => t('Select music for your video'),
      'photo_film_select_picture_step' => t('Select photos for your video'),
      'photo_film_form_order' => t('Order'),
    ),
    'forms' => array(
      'themes' => array(
        'form id' => 'photo_film_form_choose_theme_step',
        'include' => drupal_get_path('module', 'photo_film_form') . '/includes/photo_film_choose_theme_step.inc',
      ),
      'styles' => array(
        'form id' => 'photo_film_form_choose_style_step',
        'include' => drupal_get_path('module', 'photo_film_form') . '/includes/photo_film_style_step.inc',
      ),
      'user_music_upload' => array(
        'form id' => 'photo_film_form_user_music_upload_step',
        'include' => drupal_get_path('module', 'photo_film_form') . '/includes/photo_film_user_music_upload_step.inc',
      ),
      'photo_film_select_picture_step' => array(
        'form id' => 'photo_film_select_picture_step',
        'include' => drupal_get_path('module', 'photo_film_form') . '/includes/photo_film_select_picture_step.inc',
      ),
      'photo_film_form_order' => array(
        'form id' => 'photo_film_form_order',
        'include' => drupal_get_path('module', 'photo_film_form') . '/includes/photo_film_order.inc',
      ),
    ),
  );
  // TODO do it in normal way this is really ugly

  // We're not using any real storage here, so we're going to set our
  // object_id to 1. When using wizard forms, id management turns
  // out to be one of the hardest parts. Editing an object with an id
  // is easy, but new objects don't usually have ids until somewhere
  // in creation.
  //
  // We skip all this here by just using an id of 1.
  $object_id = 1;
  if (!empty($args)) {
    $step = array_pop($args);
  }
  else {
    // We reset the form when $step is NULL because that means they have
    // for whatever reason started over.
    photo_film_form_cache_clear($object_id);
    $step = 'themes';
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
    $results = photo_film_form_get_result($object);

    $output = render($results) . "\n\r" . l(t('Back'), 'example-link');
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
