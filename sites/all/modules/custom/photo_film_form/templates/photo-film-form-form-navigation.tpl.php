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

<?php if (!empty($steps)):
  $is_active = TRUE; ?>
  <ul class="photo-film-navigation">
    <?php foreach ($steps as $key => $single_step):
    if ($key === $current) :
      $is_active = FALSE;
    endif;
    if ($is_active):
      $single_step['attributes'] = array('attributes' => array('class' => array('active')));
    endif ?>
    <li class="<?php print ($is_active ? "active-step " : "") ?> clearfix">
      <?php print l(t($single_step['title']), $single_step['href'], $single_step['attributes']) ?>
      <span class="navigation-separator">&nbsp;</span>
    </li>
    <?php endforeach; ?>
  </ul>
<?php endif ?>
<hr class="separator" />