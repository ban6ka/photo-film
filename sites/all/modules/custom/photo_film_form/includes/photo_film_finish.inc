<?php 

function photo_film_form_finish($form, $form_state) {
  unset($form['ctools_trail']);
  unset($form['buttons']['cancel']);
  unset($form['buttons']['previous']);

  $form['#attributes'] = array();
  $form['#attributes']['class'] = array();
  $form['#attributes']['class'][] = 'photo-film-form';

  $success_message = variable_get('photo_film_form_success_message', '');

  $form['success_message'] = array(
      '#type' => 'markup',
      '#markup' => (!empty($success_message['value']) ? $success_message['value'] : '')
  );

  // finish submit button
  if (!empty($form['buttons']['return'])) {
    $form['buttons']['return']['#value'] = t("Order");
    $form['buttons']['return'] = photo_film_form_render_submit_button($form['buttons']['return'], "");
  }

  return $form;
}