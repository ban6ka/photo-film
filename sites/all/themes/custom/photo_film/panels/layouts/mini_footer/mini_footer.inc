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
    'region-one'      => t('Our sites'),
    'region-two'      => t('Quick links'),
	'region-three'    => t('Related links'),
    'region-four'     => t('Information'),
    'region-five'     => t('Pictures')
	),
);
