<?php
/**
 * @file
 * Template for a 3 column panel layout.
 *
 * This template provides a very simple "one column" panel display layout.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   $content['middle']: The only panel in the layout.
 */
?>
<div class="panel-display clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div class="logo">
    <?php print $content['region-one']; ?>
  </div>

  <div class="slogan">
    <?php print $content['region-two']; ?>
  </div>

  <div class="help-mail">
    <?php print $content['region-three']; ?>
  </div>

</div>

