<?php
/**
 * @file
 * vocation_feature.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function vocation_feature_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'approved_vacations';
  $page->task = 'page';
  $page->admin_title = 'Approved Vacations';
  $page->admin_description = '';
  $page->path = 'vacation/approved-list';
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
  $handler->name = 'page_approved_vacations__panel_context_4fb48d57-dadd-4c32-8f0e-465a5cda1509';
  $handler->task = 'page';
  $handler->subtask = 'approved_vacations';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '我已审批';
  $display->uuid = '42cfd64b-0e85-4ab5-901e-027c006909c1';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-96ccc0e6-1dca-4aa9-b4ef-a9e2c51de250';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'vacation_approved-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '96ccc0e6-1dca-4aa9-b4ef-a9e2c51de250';
    $display->content['new-96ccc0e6-1dca-4aa9-b4ef-a9e2c51de250'] = $pane;
    $display->panels['middle'][0] = 'new-96ccc0e6-1dca-4aa9-b4ef-a9e2c51de250';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['approved_vacations'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'my_vacations';
  $page->task = 'page';
  $page->admin_title = 'My Vacations';
  $page->admin_description = '';
  $page->path = 'vacation/my-vacation-history';
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
  $handler->name = 'page_my_vacations__panel_context_e36e1def-6f5d-431e-a817-2bec62adc09f';
  $handler->task = 'page';
  $handler->subtask = 'my_vacations';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '请假记录';
  $display->uuid = 'a50ea028-75c2-4fe9-84c5-3b9634bda9ee';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-07b87b00-9555-4888-9a9e-f1c328c6b0cb';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'vacation_history-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '07b87b00-9555-4888-9a9e-f1c328c6b0cb';
    $display->content['new-07b87b00-9555-4888-9a9e-f1c328c6b0cb'] = $pane;
    $display->panels['middle'][0] = 'new-07b87b00-9555-4888-9a9e-f1c328c6b0cb';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['my_vacations'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'pending_vacations';
  $page->task = 'page';
  $page->admin_title = 'Pending Vacations';
  $page->admin_description = '';
  $page->path = 'vacation/pending-list';
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
  $handler->name = 'page_pending_vacations__panel_context_ad3f61e0-acb9-4f5c-9e17-4dd26eba92df';
  $handler->task = 'page';
  $handler->subtask = 'pending_vacations';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '待我审批';
  $display->uuid = '6ee71c14-ec38-4a11-887d-9d251b44b25b';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-957015ba-ed31-4a6f-bc9c-53383cfaab2c';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'vacation_pending-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '957015ba-ed31-4a6f-bc9c-53383cfaab2c';
    $display->content['new-957015ba-ed31-4a6f-bc9c-53383cfaab2c'] = $pane;
    $display->panels['middle'][0] = 'new-957015ba-ed31-4a6f-bc9c-53383cfaab2c';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['pending_vacations'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'vacation_request';
  $page->task = 'page';
  $page->admin_title = 'Vacation Request';
  $page->admin_description = '';
  $page->path = 'vacation/request';
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
  $handler->name = 'page_vacation_request__panel_context_de9312e6-661e-4190-92d6-8d5900e501bd';
  $handler->task = 'page';
  $handler->subtask = 'vacation_request';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '发起请假';
  $display->uuid = 'f7bc5a37-8afe-458e-8ed0-e5638226e60d';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-e5ece5b6-bbb2-43d0-8342-0823f732167c';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'formblock-vocation';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'e5ece5b6-bbb2-43d0-8342-0823f732167c';
    $display->content['new-e5ece5b6-bbb2-43d0-8342-0823f732167c'] = $pane;
    $display->panels['middle'][0] = 'new-e5ece5b6-bbb2-43d0-8342-0823f732167c';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['vacation_request'] = $page;

  return $pages;

}
