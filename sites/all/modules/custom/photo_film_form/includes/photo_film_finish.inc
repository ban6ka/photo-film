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

	// Webmoney inputs
  $form['#action'] = 'https://merchant.webmoney.ru/lmi/payment.asp';

  $form['LMI_PAYEE_PURSE'] = array(
    '#type' => 'hidden',
    '#value' => variable_get('photo_film_form_webmoney_pursues', ''),
  );

  $cache = photo_film_form_cache_get(1);

  $form['LMI_PAYMENT_AMOUNT'] = array(
    '#type' => 'hidden',
    // todo do it in right way
    '#value' => photo_film_form_calculate_amount($cache),
  );

  $form['LMI_PAYMENT_DESC'] = array(
    '#type' => 'hidden',
    '#value' => 'my_description',

  );
  
	return $form;
}