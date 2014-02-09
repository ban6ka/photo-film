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

<div class="tracks-step clearfix">
  <div class="tracks-list-wrap">
    <?php if (!empty($items)): ?>
      <h2><?php print t("We propose") ?></h2>
        <ul class="tracks-list">
          <?php $pos = 0; ?>
          <?php foreach ($items as $key => $item): ?>
            <li class="track-item <?php print ($pos %2 == 0 ? 'even' : 'odd') . ($item['fid'] == $default_value ? ' checked' : '') ?>" track_id="<?php print $item['fid'] ?>">
              <div class="title clearfix">
                <span><?php print $item['title'] ?></span>
                <strong class="author">(<?php print $item['author'] ?>)</strong>
              </div>
              <audio preload="none" src="<?php print $item['path'] ?>" type="audio/mpeg" width="400"></audio>
            </li>
            <?php $pos++; ?>
          <?php endforeach ?>
        </ul>
    <?php endif; ?>
  </div>

  <div class="track-uploader-wrap">
    <h2><?php print t("I want to upload my music") ?></h2>
    <div class="user-file-upload">
      <div class="file-uploader-holder">
        <span><?php print $help_text ?></span>
      </div>
      <div class="user-track-wrap" style="display: none;">
        <h5><?php print t("Uploaded") ?></h5>
        <div class="user-track-info clearfix">
          <div class="status">&nbsp;</div>
          <div class="title"></div>
          <div class="remove">&nbsp;</div>
        </div>
      </div>
      <div class="messages error" id="music-error" style="display: none;"></div>
    </div>

    <?php if (!empty($warning)): ?>
      <div class="form-warning-message"><?php print $warning ?></div>
    <?php endif; ?>

    <div class="refuse-music-wrap">
      <h3><?php print t("No, thank you, I don't want incidental music") ?></h3>
      <input type="checkbox" name="refuse_music" id="refuse-music-checkbox" value="" />
      <label for="refuse-music-checkbox"><?php print t("refuse") ?></label>
    </div>

  </div>
</div>