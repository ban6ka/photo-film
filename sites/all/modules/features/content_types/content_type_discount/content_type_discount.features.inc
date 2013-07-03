<?php
/**
 * @file
 * content_type_discount.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function content_type_discount_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function content_type_discount_node_info() {
  $items = array(
    'discount' => array(
      'name' => t('Discount'),
      'base' => 'node_content',
      'description' => t('Storage for all orders discount'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
