<?php
/**
 * @file
 * panel_how_it_works.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function panel_how_it_works_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'how_it_works';
  $page->task = 'page';
  $page->admin_title = 'How it works';
  $page->admin_description = '';
  $page->path = 'how-it-works';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_how_it_works_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'how_it_works';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'How it works',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'main_layout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'region-one' => NULL,
      'region-two' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-1';
    $pane->panel = 'region-one';
    $pane->type = 'panels_mini';
    $pane->subtype = 'header_mini_panel';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-1'] = $pane;
    $display->panels['region-one'][0] = 'new-1';
    $pane = new stdClass();
    $pane->pid = 'new-2';
    $pane->panel = 'region-two';
    $pane->type = 'custom';
    $pane->subtype = 'back_link';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '',
      'format' => 'filtered_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
      'style' => 'default',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-2'] = $pane;
    $display->panels['region-two'][0] = 'new-2';
    $pane = new stdClass();
    $pane->pid = 'new-3';
    $pane->panel = 'region-two';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'How it works',
      'title' => '',
      'body' => '<h3>&nbsp;</h3><h5><span style="font-size:18px;"><strong>Как это работает?</strong></span></h5><div>&nbsp;</div><div>Пользоваться сайтом предельно просто, Вам необходимо пройти пять шагов&nbsp;</div><div>на каждом и которых выбрать определенные данные, заполнить форму и оплатить услугу.</div><div>Более подробно описано ниже.</div><div>&nbsp;</div><div>&nbsp;</div><div>&nbsp;</div><div><table border="0" cellpadding="22" cellspacing="0" style="width: 940px;" valign="middle"><tbody><tr style="background: #f2f2f2;"><td width="300"><h5 style="text-align: right;"><strong><span style="font-size:28px;">Тема</span></strong></h5></td><td width="100">&nbsp;</td><td><div>&nbsp;</div><div>Необходимо выбрать наиболее подходящую, для вас, тему ролика.&nbsp;</div><div>Если такой темы нет в предложенных вы можете связаться с нами и оформить&nbsp;</div><div>индивидуальный заказ.</div><div>&nbsp;</div></td></tr><tr style="background: #f6f6f6;"><td><h5 style="text-align: right;"><strong><span style="font-size:28px;">Стиль</span></strong></h5></td><td>&nbsp;</td><td><div>&nbsp;</div><div>Тут вы можете выбрать наиболее подходящий стиль оформления вашего ролика.</div><div>При необходимости просмотреть более детально конкретный стиль про нажмити&nbsp;</div><div>на картинку &nbsp;с интересующим вас стилем.</div><div>&nbsp;</div></td></tr><tr style="background: #f2f2f2;"><td><h5 style="text-align: right;"><span style="font-size:28px;">Музыка</span></h5></td><td>&nbsp;</td><td><div>&nbsp;</div><div>На этом шаге вы можете выбрать музыкальное сопровождение к ролику, можете</div><div>выбрать изпредложенного (список слева) , загрузить свою композицию, или же</div><div>отказаться от музыкального сопровождения вовсе.</div><div>&nbsp;</div></td></tr><tr style="background: #f6f6f6;"><td><h5 style="text-align: right;"><span style="font-size:28px;">Фото</span></h5></td><td>&nbsp;</td><td><div>&nbsp;</div><div>На данном этам вам необходимо загрузить ваши фотографии. Если вы выбрали</div><div>музыкальное сопровождение для ролика то вам будет предложено оптимальное</div><div>количество фотографий в зависимости от продолжительности зввукового&nbsp;</div><div>сопровождения, в противном случае вы должны указать желаемую&nbsp;</div><div>продолжительность ролика.&nbsp;</div><div>&nbsp;</div><div><strong>Важно!</strong></div><div>Порядок фотографий в ролике будет соответствовать порядку, в котором они&nbsp;</div><div>расположены на сайте.</div><div>&nbsp;</div></td></tr><tr style="background: #f2f2f2;"><td><h5 style="text-align: right;"><span style="font-size:28px;">Заказать</span></h5></td><td>&nbsp;</td><td><div>&nbsp;</div><div>Это последний шаг на котором требуется заполнить форму с Вашимим контактными</div><div>данными. Так же Вам будет предоставлена сумма оплаты.</div><div>&nbsp;</div></td></tr></tbody></table><p>&nbsp;</p><p>&nbsp;</p><p>&nbsp;</p></div><p>&nbsp;</p><p>&nbsp;</p>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $display->content['new-3'] = $pane;
    $display->panels['region-two'][1] = 'new-3';
    $pane = new stdClass();
    $pane->pid = 'new-4';
    $pane->panel = 'region-two';
    $pane->type = 'panels_mini';
    $pane->subtype = 'footer_mini_panel';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $display->content['new-4'] = $pane;
    $display->panels['region-two'][2] = 'new-4';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-1';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['how_it_works'] = $page;

  return $pages;

}
