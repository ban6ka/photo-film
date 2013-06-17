<?php
/**
 * Generates first form.
 *
 * @ingroup forms
 */
function photo_film_form_choose_theme_step($form, &$form_state) {
  $form['#theme'] = array('photo_film_form_choose_theme_step_theme');
  if ($themes_vocabulary_vid = variable_get('photo_film_form_themes_vid', FALSE)) {
    if ($vocabulary_terms = taxonomy_get_tree($themes_vocabulary_vid)) {
      foreach ($vocabulary_terms as $key => $value) {
        $term = taxonomy_term_load($value->tid);

        if ($image = field_get_items('taxonomy_term', $term, 'field_image')) {
          $markup = theme('image_style', array(
            'style_name' => 'photo_film_form_image_style',
            'width' => 0,
            'height' => 0,
            'path' => $image[0]['uri']
          ));
        }

        $form[$term->tid]['term'] = array(
          '#type' => 'markup',
          '#markup' => $markup,
        );
      }

    }
  }

  return $form;
}

function photo_film_form_choose_theme_step_theme(&$variables){
  krumo('hi');
  die();
}