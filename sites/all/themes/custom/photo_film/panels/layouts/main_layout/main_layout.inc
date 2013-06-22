<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Main Layout'),
  'category' => t('Photo Film Panel'),
  'icon' => 'main_layout.png',
  'theme' => 'main-layout',
  'css' => 'main_layout.css',
  'regions' => array(
    'region-one' => t('Header'),
    'region-two' => t('Main Content')
  ),
);
