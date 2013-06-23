<?php
/**
 * @file
 * Default theme implementation to display a fourth step of photo film form.
 *
 * Available variables:
 * - $title: information about step.
 * - $warning: warning message
 */
?>
<?php if (!empty($title)): ?>
  <h4><?php print $title ?></h4>
<?php endif; ?>

<div class="user-file-upload">
  <div class="file-uploader-holder" style="width: 300px; height: 100px; border: 1px dotted #ccc;">
    <div class="user-photos-info"></div>
  </div>
  <input id="photos-upload" type="file" name="photos-file[]" multiple/>
</div>

<?php if (!empty($warning)): ?>
  <div class="user-warning"><?php print $warning ?></div>
<?php endif; ?>
