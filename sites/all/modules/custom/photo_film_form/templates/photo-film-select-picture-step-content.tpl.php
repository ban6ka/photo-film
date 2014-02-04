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
      <textarea rows="5" cols="15" name="subtitles_initial"><?php !empty($items[0]['subtitles_initial'])? print $items[0]['subtitles_initial']: '' ?></textarea>
      <span><?php print t("This field is not required and can be left empty if you want") ?></span>
    </div>
  </div>

  <ul class="user-photos-wrap clearfix ui-sortable">
    <h2 style="display: none;">Вы пока не загрузили фотографий</h2>
    <?php if (!empty($items)): ?>
      <?php foreach($items as $key => $value): ?>
        <li fid="<?php print $value['fid']; ?>">
          
          <?php print theme('image_style', array('style_name' => 'photo_film_style_thumb', 'path' => $value['original']->uri))?>  
          <div class="photo-number"><?php print $value['serial_number'] + 1?></div>
          <div class="photo-toolbar clearfix">
            <div class="photo-comment">коментировать</div>
            <div class="photo-remove">удалить</div>
          </div>
          <input type="text" class="photo-id hidden" name="photos_id[]" value="<?php print $value['fid'] ?>" /> 
          <input type="text" class="photo-order hidden" name="photos_order[]" value="<?php print $value['serial_number'] + 1?>" />
          <textarea class="photo-desc hidden" name="photos_comment[]"><?php print $value['description']; ?></textarea>
        </li>
      <?php endforeach;?>
    <?php endif;?>
  </ul>
  <div class="subtitles-block final-subtitles clearfix">
    <div class="subtitles-body hidden">
      <textarea rows="5" cols="15" name="subtitles_final"> <?php !empty($items[0]['subtitles_final'])? print $items[0]['subtitles_final']: '' ?></textarea>
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
