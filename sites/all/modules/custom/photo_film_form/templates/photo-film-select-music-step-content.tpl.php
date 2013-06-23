<?php
/**
 * @file
 * Default theme implementation to display a first step of photo film form.
 *
 * Available variables:
 * - $title: information about step.
 * - $items: array of items to display which contains:
 *  - $items[][fid]: file id in drupal system
 *  - $items[][title] : title of the node related to the file
 * - $warning: warning message
 */
?>
<?php if (!empty($title)): ?>
  <h4><?php print $title ?></h4>
<?php endif; ?>

<?php if (!empty($items)): ?>
  <ul class="proposed-list">
    <?php foreach ($items as $item): ?>
      <li class="item-<?php print $item['fid'] ?>">
        <span><?php print $item['title'] ?></span>
      </li>
    <?php endforeach ?>
  </ul>
<?php endif; ?>

<div class="user-file-upload">
  <div class="file-uploader-holder" style="width: 300px; height: 100px; border: 1px dotted #ccc;">  </div>
  <div class="user-track-info">test</div>
  <input id="track-upload" type="file" name="track-file[]"/>
</div>

<?php if (!empty($warning)): ?>
  <div class="user-warning"><?php print $warning ?></div>
<?php endif; ?>
