<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Header'),
  'category' => t('Photo Film Minipanels'),
  'icon' => 'mini_header.png',
  'theme' => 'mini-header',
  'css' => 'mini_header.css',
  'regions' => array(
    'region-one'      => t('Logo'),
    'region-two'      => t('Slogan'),
	'region-three'    => t('Help Mail')
  ),
);
