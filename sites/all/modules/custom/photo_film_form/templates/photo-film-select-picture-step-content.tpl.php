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

<div class="photos-step clearfix">
  <div class="photos-uploader-wrap">
    <div class="user-file-upload">
      <div class="file-uploader-holder">
        <span><?php print t("Drag files here") ?></span>
      </div>
    </div>
  </div>

  <?php if (!empty($warning)): ?>
    <div class="form-warning-message"><?php print $warning ?></div>
  <?php endif; ?>

  <ul class="user-photos-wrap">
    <li style="display: none;">
      <img src="" width="220" height="120" align="left" />
      <div class="photo-number">1</div>
      <div class="photo-toolbar clearfix">
        <div class="photo-comment"><?php print t("comment") ?></div>
        <div class="photo-remove"><?php print t("remove") ?></div>
      </div>
    </li>
  </div>
</div>
