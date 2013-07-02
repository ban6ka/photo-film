<?php
/**
 * @file
 * content_type_music.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function content_type_music_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function content_type_music_node_info() {
  $items = array(
    'music' => array(
      'name' => t('Музыка'),
      'base' => 'node_content',
      'description' => t('Музыка которая предоставляется клиенту для выбора.'),
      'has_title' => '1',
      'title_label' => t('Заголовок'),
      'help' => '',
    ),
  );
  return $items;
}
