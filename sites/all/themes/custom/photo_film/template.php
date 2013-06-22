<?php
/**
 * @file
 * Contains theme override functions and process & preprocess functions for Zentropy pfizer_main.
 *
 * @TODO Add your own template_preprocess hooks here.
 */

/**
 * Implements template_preprocess_maintenance_page().
 */
function photo_film_preprocess_maintenance_page(&$variables) {
  drupal_add_css(drupal_get_path('theme', 'photo_film') . '/css/photo_film-maintenance.css', array('group' => CSS_THEME));
}

/**
 * Implements template_preprocess_html().
 */
function photo_film_preprocess_html(&$variables) {
  //drupal_add_css('http://f.fontdeck.com/s/css/Uf28uh55+ApRRbdMqWM/5y2U+0o/http://pfizer.an.ppl.ua/.ua/28524.css', array('type' => 'external'));
  //drupal_add_css('http://f.fontdeck.com/s/css/Uf28uh55+ApRRbdMqWM/5y2U+0o/http://pfizer-stag.propeople.com.ua//28524.css', array('type' => 'external'));
  //drupal_add_css('http://f.fontdeck.com/s/css/Uf28uh55+ApRRbdMqWM/5y2U+0o/phar.se.lr1.sta7.vecweb.net/28524.css', array('type' => 'external'));

  // Set the mode, when CSS is aggregated by Drupal Production mode is TRUE
  // Borrowed from Adaptivethemes
  $mode = variable_get('preprocess_css', '') == 1 ? TRUE : FALSE;

  // Get responsive styles fallback option
  $fallback = theme_get_setting('zentropy_responsive_fallback', 'zentropy');

  // CSS files for Internet Explorer-specific styles.
  drupal_add_css(path_to_theme() . '/css/ie/photo_film-ielt9.css', array('group' => CSS_THEME, 'every_page' => TRUE, 'media' => 'screen', 'browsers' => array('IE' => 'lt IE 9', '!IE' => FALSE), 'preprocess' => FALSE));
  drupal_add_css(path_to_theme() . '/css/ie/photo_film-ielt8.css', array('group' => CSS_THEME, 'every_page' => TRUE, 'media' => 'screen', 'browsers' => array('IE' => 'lt IE 8', '!IE' => FALSE), 'preprocess' => FALSE));

  // CSS files for custom Google-fonts
  drupal_add_css('http://fonts.googleapis.com/css?family=Open+Sans:400,300', array('group' => CSS_THEME, 'every_page' => TRUE, 'type' => 'external', 'preprocess' => FALSE));
  drupal_add_css('http://fonts.googleapis.com/css?family=PT+Sans:400,700', array('group' => CSS_THEME, 'every_page' => TRUE, 'type' => 'external', 'preprocess' => FALSE));

  // Responsive stylesheets.
  if (theme_get_setting('zentropy_responsive_enable')) {
    drupal_add_css(path_to_theme() . '/css/layout/photo_film-320.css', array('preprocess' => $mode, 'group' => CSS_THEME, 'every_page' => TRUE));
    drupal_add_css(path_to_theme() . '/css/layout/photo_film-480.css', array('preprocess' => $mode, 'group' => CSS_THEME, 'every_page' => TRUE));
    drupal_add_css(path_to_theme() . '/css/layout/photo_film-768.css', array('preprocess' => $mode, 'group' => CSS_THEME, 'every_page' => TRUE));
    drupal_add_css(path_to_theme() . '/css/layout/photo_film-992.css', array('preprocess' => $mode, 'group' => CSS_THEME, 'every_page' => TRUE));
    drupal_add_css(path_to_theme() . '/css/layout/photo_film-1382.css', array('preprocess' => $mode, 'group' => CSS_THEME, 'every_page' => TRUE));

    // Styles for iPhone 4+, iPad 3+, Opera Mobile 11+ and other high pixel ratio browsers and devices.
    drupal_add_css(path_to_theme() . '/css/layout/photo_film-hipixel.css', array('group' => CSS_THEME, 'every_page' => TRUE));

    // Styles for iPads (portrait & landscape).
    //drupal_add_css(path_to_theme() . '/css/layout/photo_film-ipad.css', array('group' => CSS_THEME, 'every_page' => TRUE));

  }
  // If not, use fallback stylesheet.
  elseif (isset($fallback) && $fallback != FALSE) {
    drupal_add_css(path_to_theme() . "/css/layout/photo_film-{$fallback}.css", array('preprocess' => $mode, 'group' => CSS_THEME, 'every_page' => TRUE));
  }

  /* Add your own custom logic in between the following lines:
	--------------------------------------------------------------------*/







  /* STOP!!!! Don't edit this function below this line!
	--------------------------------------------------------------------*/

  // The below code comments are placeholders for Zentropy optional components downloaded and installed via Drush.
  // For more information see the section "Advanced Drush Integration" in Zentropy's README.txt or the project page on drupal.org: http://drupal.org/project/zentropy

  // To find out how to manually enable components (without Drush), read the handbook: http://drupal.org/node/1515894

  // IMPORTANT: DO NOT EDIT OR REMOVE THE LINES BELOW UNLESS YOU REALLY KNOW WHAT YOU ARE DOING!

  $zentropy_scripts_head = array();

  #modernizr#

  #easing#

  #hoverintent#

  #bgiframe#

  $variables['zentropy_scripts_head'] .= implode("\n", $zentropy_scripts_head);
}

/**
 * Implements theme_breadcrumb().
 */

/* Put Breadcrumbs in a ul li structure */
 function photo_film_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  $crumbs = '';
   if (!empty($breadcrumb)) {

			//$breadcrumb[] = drupal_get_title();

      $crumbs = '<ul class="breadcrumbs">';

      foreach($breadcrumb as $value) {
           $crumbs .= '<li>'.$value.'</li>';
      }
      $crumbs .= '<li class="current">' . drupal_get_title() . '</li>';
      $crumbs .= '</ul>';
    }
      return $crumbs;
 }


/**
 * Implements hook_html_head_alter().
 */
function photo_film_html_head_alter(&$head_elements) {
  // Remove Generator META tag.
  if (isset($head_elements['metatag_generator'])) {
    unset($head_elements['metatag_generator']);
  }
}

/**
 * Implementation of hook_css_alter()
 */
function photo_film_css_alter(&$css) {
  $exclude = array(
    'modules/field/theme/field.css' => FALSE,
    'modules/aggregator/aggregator.css' => FALSE,
    'modules/block/block.css' => FALSE,
    'modules/book/book.css' => FALSE,
    'modules/comment/comment.css' => FALSE,
    'modules/dblog/dblog.css' => FALSE,
    'modules/file/file.css' => FALSE,
    'modules/filter/filter.css' => FALSE,
    'modules/forum/forum.css' => FALSE,
    'modules/help/help.css' => FALSE,
    'modules/menu/menu.css' => FALSE,
    'modules/node/node.css' => FALSE,
    'modules/openid/openid.css' => FALSE,
    'modules/poll/poll.css' => FALSE,
    'modules/profile/profile.css' => FALSE,
    'modules/search/search.css' => FALSE,
    'modules/statistics/statistics.css' => FALSE,
    'modules/syslog/syslog.css' => FALSE,
    'modules/system/admin.css' => FALSE,
    'modules/system/maintenance.css' => FALSE,
    'modules/system/system.css' => FALSE,
    'modules/system/system.admin.css' => FALSE,
    'modules/system/system.maintenance.css' => FALSE,
    'modules/system/system.menus.css' => FALSE,
    'modules/system/system.theme.css' => FALSE,
    'modules/system/system.messages.css' => FALSE,
    'modules/taxonomy/taxonomy.css' => FALSE,
    'modules/tracker/tracker.css' => FALSE,
    'modules/update/update.css' => FALSE,
    'modules/user/user.css' => FALSE,
    'misc/vertical-tabs.css' => FALSE,
    'misc/ui/jquery.ui.theme.css' => FALSE,
    'misc/ui/jquery.ui.core.css' => FALSE,
    'misc/ui/jquery.ui.tabs.css' => FALSE,

    'sites/all/themes/contrib/zentropy/css/zentropy.css' => FALSE,
    'sites/all/themes/custom/msf/panels/layouts/mini_footer/mini_footer.css' => FALSE,
    'sites/all/themes/custom/msf/panels/layouts/mini_header/mini_header.css' => FALSE,
    'sites/all/themes/custom/msf/panels/layouts/frontpage/frontpage.css' => FALSE,
    'sites/all/themes/contrib/zentropy/css/layout/zentropy-320.css' => FALSE,
    'sites/all/themes/contrib/zentropy/css/layout/zentropy-480.css' => FALSE,
    'sites/all/themes/contrib/zentropy/css/layout/zentropy-768.css' => FALSE,
    'sites/all/themes/contrib/zentropy/css/layout/zentropy-992.css' => FALSE,
    'sites/all/themes/contrib/zentropy/css/layout/zentropy-1382.css' => FALSE,
    'sites/all/modules/contrib/views/css/views.css' => FALSE,
    'sites/all/modules/contrib/tagadelic/tagadelic.css' => FALSE,
    'sites/all/modules/contrib/ctools/css/ctools.css' => FALSE,
    'sites/all/modules/contrib/panels/css/panels.css' => FALSE,
    'sites/all/modules/contrib/tagadelic/tagadelic.css' => FALSE,
    'sites/all/modules/contrib/webform/css/webform.css' => FALSE,
    'sites/all/modules/contrib/field_collection/field_collection.theme.css' => FALSE,

  );
  $css = array_diff_key($css, $exclude);
}
