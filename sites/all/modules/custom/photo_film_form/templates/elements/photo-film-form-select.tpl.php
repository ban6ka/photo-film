<?php
/**
 * @file
 * Default theme implementation to display a photo film textfield.
 *
 * Available variables:
 * - $element: element of form that ready for render.
 */
?>
<dl>
  <?php if (!empty($element['#title'])): ?>
    <dt><?php print $element['#title']; ?></dt>
  <?php endif; ?>
  <dd>
    <select <?php print drupal_attributes($element['#attributes']); ?>>
      <?php print form_select_options($element) ?>
    </select>
  </dd>
</dl>

