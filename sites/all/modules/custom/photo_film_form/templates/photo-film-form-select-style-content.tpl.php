<?php
/**
 * @file
 * Default theme implementation to display a second step of photo film form.
 *
 * Available variables:
 * - $title: information about step.
 * - $items: array of items to display which contains:
 *  - $items[][id]: term id (basic information)
 *  - $items[][image_path] : path to the terms image
 *  - $items[][id][title] : title of term
 * - $items[][id][video_url] : url of the video attached to the term
 */
?>

  <div class="not-picked">
    <div class="to-the-left"></div>
    <div class="iframe"></div>
    <div class="to-the-right"></div>
  </div>

<?php if (!empty($title)): ?>
  <h4><?php print $title ?></h4>
<?php endif; ?>

<?php if (!empty($items)): ?>
  <ul>
    <?php foreach ($items as $item): ?>
      <li>
        <?php print theme('image_style', array(
          'style_name' => 'photo_film_form_image_style',
          'path' => $item['image_path'],
          'width' => 0,
          'height' => 0,
        )); ?>
        <span><?php print $item['title'] ?></span>
        <span><?php print $item['video_url'] ?></span>
      </li>
    <?php endforeach ?>
  </ul>
<?php endif; ?>