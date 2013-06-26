<?php 

function photo_film_form_finish($form, $form_state) {
  unset($form['ctools_trail']);
  unset($form['buttons']['cancel']);
  unset($form['buttons']['previous']);

  $success_message = variable_get('photo_film_form_success_message', '');

	$form['success_message'] = array(
		'#type' => 'markup',
		'#markup' => (!empty($success_message['value']) ? $success_message['value'] : '')
	);

	return $form;
}