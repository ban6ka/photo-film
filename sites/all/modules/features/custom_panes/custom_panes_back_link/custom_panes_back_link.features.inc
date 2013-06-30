<?php
/**
 * @file
 * custom_panes_back_link.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function custom_panes_back_link_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ctools_custom_content" && $api == "ctools_content") {
    return array("version" => "1");
  }
}
