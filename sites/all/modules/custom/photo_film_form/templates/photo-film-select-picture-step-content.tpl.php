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
        <span><?php print $help_text ?></span>
      </div>
      <div class="messages error" id="photo-error" style="display: none;"></div>
    </div>
  </div>

  <?php if (!empty($warning)): ?>
    <div class="form-warning-message"><?php print $warning ?></div>
  <?php endif; ?>

  <div class="subtitles-block initial-subtitles clearfix">
    <a class="subtitles-button" href=""><?php print t("Initial subtitles") ?></a>
    <span class="subtitles-desc"><?php print t("You can add text for initial subtitles in your movie") ?></span>
    <hr class="separator" />
    <div class="subtitles-body hidden">
      <textarea rows="5" cols="15" name="subtitles_initial"></textarea>
      <span><?php print t("This field is not required and can be left empty if you want") ?></span>
    </div>
  </div>

  <ul class="user-photos-wrap clearfix">
    <h2><?php print t("You didn't upload photos yet") ?></h2>
  </ul>

  <div class="subtitles-block final-subtitles clearfix">
    <div class="subtitles-body hidden">
      <textarea rows="5" cols="15" name="subtitles_final"></textarea>
      <span><?php print t("This field is not required and can be left empty if you want") ?></span>
    </div>
    <hr class="separator" />
    <a class="subtitles-button" href=""><?php print t("Final subtitles") ?></a>
    <span class="subtitles-desc"><?php print t("Also you can add text for final subtitles that will be placed at the end of your movie") ?></span>
  </div>


  <div id="comment-dialog" class="hidden" title="<?php print t("Comment photo") ?>">
    <textarea name="comment" id="comment" class="text ui-widget-content"></textarea>
  </div>
</div>
