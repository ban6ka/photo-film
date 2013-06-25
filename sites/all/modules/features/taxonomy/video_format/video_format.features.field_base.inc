<?php
/**
 * @file
 * video_format.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function video_format_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_coefficient'
  $field_bases['field_coefficient'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_coefficient',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'decimal_separator' => '.',
      'precision' => 10,
      'scale' => 3,
    ),
    'translatable' => 0,
    'type' => 'number_decimal',
  );

  return $field_bases;
}
