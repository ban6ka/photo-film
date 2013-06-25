<?php
/**
 * @file
 * delivery_method.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function delivery_method_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'taxonomy_term-delivery_method-field_coefficient'
  $field_instances['taxonomy_term-delivery_method-field_coefficient'] = array(
    'bundle' => 'delivery_method',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_coefficient',
    'label' => 'Сoefficient',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Сoefficient');

  return $field_instances;
}
