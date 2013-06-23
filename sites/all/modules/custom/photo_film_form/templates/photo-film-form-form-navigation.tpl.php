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

<?php if (!empty($steps)): ?>
  <ul class="photo-film-navigation">
    <?php foreach ($steps as $key => $single_step):
      $class = "clearfix" . ($key == $current ? " active-step" : ""); ?>
      <li class="<?php print $class ?>">
        <?php print l(t($single_step['title']), $single_step['href'], $single_step['attributes']) ?>
        <span class="navigation-separator">&nbsp;</span>
      </li>
    <?php endforeach; ?>
  </ul>
<?php endif ?>