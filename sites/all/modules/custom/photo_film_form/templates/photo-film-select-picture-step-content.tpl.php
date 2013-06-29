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
        <span><?php print t("Click here to upload photos") ?></span>
      </div>
    </div>
  </div>

  <?php if (!empty($warning)): ?>
    <div class="form-warning-message"><?php print $warning ?></div>
  <?php endif; ?>

  <ul class="user-photos-wrap clearfix">
  </ul>

  <div id="comment-dialog" class="hidden" title="<?php print t("Comment photo") ?>">
    <textarea name="comment" id="comment" class="text ui-widget-content"></textarea>
  </div>
</div>
