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
  $page->name = 'approved_vocations';
  $page->task = 'page';
  $page->admin_title = 'Approved Vocations';
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
  $handler->name = 'page_approved_vocations__panel';
  $handler->task = 'page';
  $handler->subtask = 'approved_vocations';
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
    'name' => 'panel',
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
    $pane->pid = 'new-63ea4a7e-bbe8-4c40-8f6b-02ce64902d10';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'vocation_approved-panel_pane_1';
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
    $pane->uuid = '63ea4a7e-bbe8-4c40-8f6b-02ce64902d10';
    $display->content['new-63ea4a7e-bbe8-4c40-8f6b-02ce64902d10'] = $pane;
    $display->panels['middle'][0] = 'new-63ea4a7e-bbe8-4c40-8f6b-02ce64902d10';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['approved_vocations'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'my_vocations';
  $page->task = 'page';
  $page->admin_title = 'My Vocations';
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
  $handler->name = 'page_my_vocations__panel';
  $handler->task = 'page';
  $handler->subtask = 'my_vocations';
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
    'name' => 'panel',
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
    $pane->pid = 'new-69ce7246-24cf-464b-8da0-a070a8ecac48';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'vocation_history-panel_pane_1';
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
    $pane->uuid = '69ce7246-24cf-464b-8da0-a070a8ecac48';
    $display->content['new-69ce7246-24cf-464b-8da0-a070a8ecac48'] = $pane;
    $display->panels['middle'][0] = 'new-69ce7246-24cf-464b-8da0-a070a8ecac48';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['my_vocations'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'pending_vocations';
  $page->task = 'page';
  $page->admin_title = 'Pending Vocations';
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
  $handler->name = 'page_pending_vocations__panel';
  $handler->task = 'page';
  $handler->subtask = 'pending_vocations';
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
    'name' => 'panel',
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
    $pane->pid = 'new-619ef744-7882-4d36-9b89-6013053e6a00';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'vocation_pending-panel_pane_1';
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
    $pane->uuid = '619ef744-7882-4d36-9b89-6013053e6a00';
    $display->content['new-619ef744-7882-4d36-9b89-6013053e6a00'] = $pane;
    $display->panels['middle'][0] = 'new-619ef744-7882-4d36-9b89-6013053e6a00';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-619ef744-7882-4d36-9b89-6013053e6a00';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['pending_vocations'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'wechat_vocation';
  $page->task = 'page';
  $page->admin_title = 'Wechat Vocation';
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
  $handler->name = 'page_wechat_vocation__panel';
  $handler->task = 'page';
  $handler->subtask = 'wechat_vocation';
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
    'name' => 'panel',
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
  $pages['wechat_vocation'] = $page;

  return $pages;

}
