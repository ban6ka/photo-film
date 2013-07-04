<?php
/**
 * File that handles creation of the order nodes
 */

/**
 * Create order  node from form cache object
 * @param $cache
 */
function photo_film_create_order_node($cache, $archive = NULL, $name = 'test') {
  global $user;

  $node = new stdClass();
  $node->title = $name;
  $node->type = 'order';
  $node->language = LANGUAGE_NONE;
  $node->uid = $user->uid;
  $node->status = 0;
  $node->promote = 0;
  $node->comment = 0;

  // Invokes hook_prepare() and hook_node_prepare().
  node_object_prepare($node);
  // add necessary options to the file object
  $archive->display = 1;
  $archive->description = "";

  if (!empty($archive)) {
    $node->field_archive[$node->language][] = (array) $archive;
  }

  if (!empty($cache->theme['theme'])) {
    $node->field_theme[$node->language][]['tid'] = $cache->theme['theme'];
  }

  if (!empty($cache->style['style'])) {
    $node->field_style[$node->language][]['tid'] = $cache->style['style'];
  }
  $restricted = array();
  if (!empty($cache->order_info['format'])) {
    $node->field_video_format[$node->language][]['tid'] = $cache->order_info['format'];
    $restricted[] = 'format';
  }

  if (!empty($cache->order_info['delivery'])) {
    $node->field_delivery_method[$node->language][]['tid'] = $cache->order_info['delivery'];
    $restricted[] = 'delivery';
  }

  if (!empty($cache->order_info['city'])) {
    $node->field_city[$node->language][]['tid'] = $cache->order_info['city'];
    $restricted[] = 'city';

  }

  foreach ($cache->order_info as $key => $field) {
    if (!empty($field) && !in_array($key, $restricted)) {
      $node->{'field_' . $key}[$node->language][]['value'] = $field;
    }
  }
  // Prepare node for saving
  $node = node_submit($node);

  node_save($node);
}