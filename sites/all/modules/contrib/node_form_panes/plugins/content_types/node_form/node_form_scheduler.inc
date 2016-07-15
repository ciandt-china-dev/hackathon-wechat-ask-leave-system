<?php

if (module_exists('scheduler')) {
  /**
   * Plugins are described by creating a $plugin array which will be used
   * by the system that includes this file.
   */
  $plugin = array(
    'single' => TRUE,
    'icon' => 'icon_node_form.png',
    'title' => t('Node form scheduler settings'),
    'description' => t('Scheduler options on the Node form.'),
    'required context' => new ctools_context_required(t('Form'), 'node_form'),
    'category' => t('Node Form Panes'),
    'edit form' => 'node_form_panes_node_form_content_type_edit_form',
    'render callback' => 'node_form_panes_node_form_scheduler_content_type_render',
    'admin title' => 'node_form_panes_node_form_scheduler_content_type_admin_title',
  );
}

function node_form_panes_node_form_scheduler_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = t('node_form');

  $block->delta = 'scheduler-path-options';

  if (isset($context->form)) {
    if (isset($context->form['scheduler_settings'])) {
      $block->content['scheduler_settings'] = $context->form['scheduler_settings'];
      node_form_panes_node_form_process_element($block->content['scheduler_settings'], $conf);
      if (!$conf['display_in_fieldset']) {
        $block->title = t('Scheduler options');
      }
      // Set access to false on the original rather than removing so that
      // vertical tabs doesn't clone it. I think this is due to references.
      $context->form['scheduler_settings']['#access'] = FALSE;
    }
  }
  else {
    $block->content = t('Scheduler options.');
  }

  return $block;
}

function node_form_panes_node_form_scheduler_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" node form scheduler options', array('@s' => $context->identifier));
}
