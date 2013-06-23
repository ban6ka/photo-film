<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Footer'),
  'category' => t('Photo Film Minipanels'),
  'icon' => 'mini_footer.png',
  'theme' => 'mini-footer',
  'css' => 'mini_footer.css',
  'regions' => array(
    'region-one' => t('Footer Menu')
	),
);
