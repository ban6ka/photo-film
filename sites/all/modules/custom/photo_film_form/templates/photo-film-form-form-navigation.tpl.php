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
      $attributes['fragment'] = 'content';
      $attributes['attributes']['name'] = 'content';
      if ($key === $current) :
        $is_active = FALSE;
      endif;
      if ($is_active):
        $single_step['attributes'] = array('fragment' => 'content', 'attributes' => array('class' => array('active'), 'name' => 'content'));
      endif ?>
      <li class="<?php print ($is_active ? "active-step " : "") ?> clearfix">
        <?php print l(t($single_step['title']), $single_step['href'], !empty($single_step['attributes']) ? $single_step['attributes'] : $attributes) ?>
        <?php if (end($steps) != $single_step) : ?>
          <span class="navigation-separator">&nbsp;</span>
        <?php endif ?>
      </li>
    <?php endforeach; ?>
  </ul>
<?php endif ?>
<hr class="separator" />