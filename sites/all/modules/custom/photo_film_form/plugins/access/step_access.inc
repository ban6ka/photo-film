<?php

/**
 * @file
 * Plugin to provide access control/visibility based on user cookie with key pfizer_password_node.
 */

/**
 * Implement hook_ctools_access().
 */
function photo_film_form_step_access_ctools_access() {
  return array(
    'title' => t('Photo film form access'),
    'description' => t('Control access to the current step'),
    'callback' => 'photo_film_form_step_access_ctools_access_check',
    'summary' => 'photo_film_form_step_access_ctools_access_summary',
  );
}

/**
 * Check for access.
 */
function photo_film_form_step_access_ctools_access_check($conf, $context, $plugin) {
  global $user;

  // if he is an admin then let him
  if ($user->uid == 1) {
    return TRUE;
  }

  $args = arg();
  $step = array_pop($args);
  // if this is a first step
  if ($step == 'themes') {
    return TRUE;
  }

  $cache = photo_film_form_cache_get(1);
  // if user try to go from first to 5 then cache object doesn't exists
  if (empty($cache->current_step)) {
    return FALSE;
  }

  $form_info = photo_film_form_ctools_multi_step_form_info();
  // if current step doesn't exists
  if (!array_key_exists($step, $form_info['order'])) {
    return FALSE;
  }

  $steps_order = array_keys($form_info['order']);

  return array_search($cache->current_step, $steps_order) >= array_search($step, $steps_order);
}
