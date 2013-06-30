<?php
/**
 * @file
 * mini_panel_contact_us.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mini_panel_contact_us_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "panels_mini" && $api == "panels_default") {
    return array("version" => "1");
  }
}
