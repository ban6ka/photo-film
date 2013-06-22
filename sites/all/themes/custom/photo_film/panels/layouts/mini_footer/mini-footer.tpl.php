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

  <div class="prefooter-wrap">
    <div class="prefooter">
      <div class="blocks">
        <?php print $content['region-one']; ?>
      </div>
      <div class="blocks">
        <?php print $content['region-two']; ?>
      </div>
      <div class="blocks">
        <?php print $content['region-three']; ?>
      </div>
    </div>
  </div>

<div class="footer-end-wrap">
  <footer class="footer-container">
    <div class="information">
      <?php print $content['region-four']; ?>
    </div>
    <div class="custom-pics">
      <?php print $content['region-five']; ?>
    </div>
  </footer>
</div>
</div>

