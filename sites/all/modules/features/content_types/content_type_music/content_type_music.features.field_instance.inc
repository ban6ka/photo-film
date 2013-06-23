<?php
/**
 * @file
 * content_type_music.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function content_type_music_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-music-field_composition'
  $field_instances['node-music-field_composition'] = array(
    'bundle' => 'music',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'file',
        'settings' => array(),
        'type' => 'file_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_composition',
    'label' => 'Composition',
    'required' => 0,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => 'photo-film/music',
      'file_extensions' => 'mp3 waw flac',
      'max_filesize' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'media',
      'settings' => array(
        'allowed_schemes' => array(
          'public' => 'public',
        ),
        'allowed_types' => array(
          'audio' => 0,
          'default' => 0,
          'image' => 'image',
          'video' => 0,
        ),
        'progress_indicator' => 'throbber',
      ),
      'type' => 'media_generic',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Composition');

  return $field_instances;
}
