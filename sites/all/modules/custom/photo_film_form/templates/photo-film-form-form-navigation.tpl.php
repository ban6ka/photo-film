<?php
/**
 * @file
 * Default theme implementation to display photo film form navigation.
 *
 * Available variables:
 * - $steps: array of steps
 * - $current: key for current step:
 */
?>
<div class="photo-film-breadcrumb">
  <?php if (!empty($steps)): ?>
  <ul>
    <?php foreach ($steps as $single_step): ?>
      <li> <?php print l(t($single_step['title']), $single_step['href'], $single_step['attributes']) ?></li>
    <?php endforeach; ?>
    <?php endif ?>
  </ul>
</div>