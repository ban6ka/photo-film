<?php
/**
 * @file
 * panel_page_not_found.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function panel_page_not_found_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}
