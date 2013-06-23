<?php
/**
 * @file
 * Default theme implementation to display a first step of photo film form.
 *
 * Available variables:
 * - $title: information about step.
 * - $items: array of items to display which contains:
 *  - $items[][id]: term id (basic information)
 *  - $items[][image_path] : path to the terms image
 *  - $items[][id][title] : title of term
 */
?>
<?php if (!empty($title)): ?>
  <h4><?php print $title ?></h4>
<?php endif; ?>

<?php if (!empty($items)): ?>
  <ul class="images-list clearfix">
    <?php foreach ($items as $item): ?>
      <li>
        <?php print theme('image_style', array(
          'style_name' => 'photo_film_form_image_style',
          'path' => $item['image_path'],
          'width' => 0,
          'height' => 0,
        )); ?>
        <div class="title"><?php print $item['title'] ?></div>
      </li>
    <?php endforeach ?>
  </ul>
<?php endif; ?>