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
  <ul class="images-list clearfix">
    <?php foreach ($items as $item): ?>
      <li>
        <div class="style-image-wrap clearfix">
          <div class="price"><?php print $item['coefficient'] . ' UAH' ?></div>
          <?php print theme('image_style', array(
            'style_name' => 'photo_film_style_thumb',
            'path' => $item['image_path'],
            'width' => 0,
            'height' => 0,
            'attributes' => array('align' => 'left')
          )); ?>
          <div class="style-example">
            <a rel="style_video" href="<?php print $item['video_url'] ?>"><?php print t("Preview example") ?></a>
          </div>
        </div>
        <div class="style-toolbar clearfix" style_id="<?php print $item['id'] ?>">
          <div class="title"><?php print $item['title'] ?></div>
          <div class="checkbox">&nbsp;</div>
        </div>
        <span class="hidden"><?php print $item['video_url'] ?></span>
      </li>
    <?php endforeach ?>
  </ul>
<?php endif; ?>