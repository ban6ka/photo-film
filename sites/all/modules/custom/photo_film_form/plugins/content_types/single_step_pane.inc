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
  // Define array for ctools multistep wizard.
  $form_info = array(
    'id' => 'photo_film_form',
    'path' => "example/nojs/form/%step",
    'show trail' => TRUE,
    'show back' => TRUE,
    'show cancel' => TRUE,
    'show return' => FALSE,
    'next callback' => 'photo_film_form_wizard_next',
    'finish callback' => 'photo_film_form_wizard_finish',
    'cancel callback' => 'photo_film_form_wizard_cancel',
    // Define forms order.
    'order' => array(
      'start' => t('Enter your info'),
      'second' => t('What do you know?'),
      'third' => t('What do think about drupal?'),
      'fourth' => t('Do you like cookies?'),
    ),
    // Define forms
    'forms' => array(
      'start' => array(
        'form id' => 'photo_film_form_start'
      ),
      'second' => array(
        'form id' => 'photo_film_form_second'
      ),
      'third' => array(
        'form id' => 'photo_film_form_third'
      ),
      'fourth' => array(
        'form id' => 'photo_film_form_fourth'
      ),
    ),
  );
  // TODO do it in normal way

  // We're not using any real storage here, so we're going to set our
  // object_id to 1. When using wizard forms, id management turns
  // out to be one of the hardest parts. Editing an object with an id
  // is easy, but new objects don't usually have ids until somewhere
  // in creation.
  //
  // We skip all this here by just using an id of 1.
  $object_id = 1;

  if (empty($step)) {

    // We reset the form when $step is NULL because that means they have
    // for whatever reason started over.
    photo_film_form_cache_clear($object_id);
    $step = 'start';
  }

  // This automatically gets defaults if there wasn't anything saved.
  $object = photo_film_form_cache_get($object_id);

  // live $form_state changes.
  $form_state = array(
    'ajax' => $js,
    // Put our object and ID into the form state cache so we can easily find it.
    'object_id' => $object_id,
    'object' => &$object,
  );

  // Send this all off to our form. This is like drupal_get_form only wizardly.
  ctools_include('wizard');
  $form = ctools_wizard_multistep_form($form_info, $step, $form_state);
  $output = drupal_render($form);
  if ($js) {

    // If javascript is active, we have to use a render array.
    $commands = array();
    if ($output === FALSE || !empty($form_state['complete'])) {
      // Dismiss the modal.
      $commands[] = ajax_command_html('#ctools-sample', render(photo_film_form_get_result($object)));
      $commands[] = ctools_modal_command_dismiss();
    }
    elseif (!empty($form_state['cancel'])) {

      // If cancelling, return to the activity.
      $commands[] = ctools_modal_command_dismiss();
    }
    else {
      $commands = ctools_modal_form_render($form_state, $output);
    }
    print ajax_render($commands);
  }
  else {
    if ($output === FALSE || !empty($form_state['complete'])) {

      return render(photo_film_form_get_result($object)) . "\n\r" . l(t('Back'), 'example-link');
    }
    elseif (!empty($form_state['cancel'])) {
      drupal_goto('example-link');
    }
    else {
      return $output;
    }
  }

  $block = new stdClass();
  $block->title = t('Single step of the photo_film_form form');
  $block->content = $output;

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
