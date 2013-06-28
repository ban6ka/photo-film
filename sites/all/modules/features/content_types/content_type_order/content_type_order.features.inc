<?php
/**
 * @file
 * content_type_order.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function content_type_order_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function content_type_order_node_info() {
  $items = array(
    'order' => array(
      'name' => t('Заказать'),
      'base' => 'node_content',
      'description' => t('Storage for all created orders'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
