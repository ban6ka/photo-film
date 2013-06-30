<?php
/**
 * @file
 * panel_music.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function panel_music_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}
