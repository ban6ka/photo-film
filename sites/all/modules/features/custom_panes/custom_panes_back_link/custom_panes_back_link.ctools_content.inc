<?php
/**
 * @file
 * custom_panes_back_link.ctools_content.inc
 */

/**
 * Implements hook_default_ctools_custom_content().
 */
function custom_panes_back_link_default_ctools_custom_content() {
  $export = array();

  $content = new stdClass();
  $content->disabled = FALSE; /* Edit this to true to make a default content disabled initially */
  $content->api_version = 1;
  $content->name = 'back_link';
  $content->admin_title = 'Back Link';
  $content->admin_description = '';
  $content->category = 'HTML Blocks';
  $content->settings = array(
    'admin_title' => '',
    'title' => '',
    'body' => '<div class="photo-film-back-link"><a href="/">Вернуться к форме заказа</a></div><hr class="separator" />',
    'format' => 'full_html',
    'substitute' => 1,
  );
  $export['back_link'] = $content;

  return $export;
}
