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
  $page->name = 'wechat_vocation';
  $page->task = 'page';
  $page->admin_title = 'Wechat Vocation';
  $page->admin_description = '';
  $page->path = 'wechat-vocation';
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
  $display->title = '';
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
