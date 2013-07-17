<?php


/**
 * Settings form for commerce_ua module
 */
function commerce_ua_settings_form($form_state) {
  
  $form = array();

  $form['webmoney'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic settings of the photo film multi step form'),
    '#collapsable' => TRUE,
    '#collapsed' => FALSE
  );

  $form['webmoney']['commerce_ua_webmoney_wmid'] = array(
    '#title' => t('Webmoney wmid'),
    '#type' => 'textfield',
    '#default_value' => variable_get('commerce_ua_webmoney_wmid', ''),
    '#required' => TRUE,
  );

  $form['webmoney']['commerce_ua_webmoney_pursues'] = array(
    '#title' => t('Webmoney pursues'),
    '#type' => 'textfield',
    '#default_value' => variable_get('commerce_ua_webmoney_pursues', ''),
    '#required' => TRUE,
  );

    $form['privat24'] = array(
    '#type' => 'fieldset',
    '#title' => t('Basic settings of the photo film multi step form'),
    '#collapsable' => TRUE,
    '#collapsed' => FALSE
  );

  $form['privat24']['commerce_ua_privat24_merchant_id'] = array(
    '#title' => t('Merchant id'),
    '#type' => 'textfield',
    '#default_value' => variable_get('commerce_ua_privat24_merchant_id', ''),
    '#required' => TRUE,
  );

  $form['privat24']['commerce_ua_privat24_merchant_signature'] = array(
    '#title' => t('Merchant signature'),
    '#type' => 'textfield',
    '#default_value' => variable_get('commerce_ua_privat24_merchant_signature', ''),
    '#required' => TRUE,
  );

  $form['privat24']['commerce_ua_privat24_success_url'] = array(
    '#title' => t('Success url'),
    '#type' => 'textfield',
    '#default_value' => variable_get('commerce_ua_privat24_success_url', 'commerce-ua/return-url'),
    '#required' => TRUE,
  );
  
  $form['privat24']['commerce_ua_privat24_fail_url'] = array(
    '#title' => t('Fail url'),
    '#type' => 'textfield',
    '#default_value' => variable_get('commerce_ua_privat24_fail_url', 'commerce-ua/server-url'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
