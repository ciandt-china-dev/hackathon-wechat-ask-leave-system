<?php

if (module_exists('rabbit_hole')) {
  /**
   * Plugins are described by creating a $plugin array which will be used
   * by the system that includes this file.
   */
  $plugin = array(
    'single' => TRUE,
    'icon' => 'icon_node_form.png',
    'title' => t('Node form rabbit_hole settings'),
    'description' => t('Rabbit hole options on the Node form.'),
    'required context' => new ctools_context_required(t('Form'), 'node_form'),
    'category' => t('Node Form Panes'),
    'edit form' => 'node_form_panes_node_form_content_type_edit_form',
    'render callback' => 'node_form_panes_node_form_rabbit_hole_content_type_render',
    'admin title' => 'node_form_panes_node_form_rabbit_hole_content_type_admin_title',
  );
}

function node_form_panes_node_form_rabbit_hole_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = t('node_form');

  $block->delta = 'rabbit_hole-path-options';

  if (isset($context->form)) {
    if (isset($context->form['rabbit_hole'])) {
      $block->content['rabbit_hole'] = $context->form['rabbit_hole'];
      node_form_panes_node_form_process_element($block->content['path'], $conf);
      if (!$conf['display_in_fieldset']) {
        $block->title = t('Rabbit hole settings');
      }

      // Set access to false on the original rather than removing so that
      // vertical tabs doesn't clone it. I think this is due to references.
      $context->form['rabbit_hole']['#access'] = FALSE;
    }
  }
  else {
    $block->content = t('Rabbit hole options.');
  }
  return $block;
}

function node_form_panes_node_form_rabbit_hole_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" node form rabbit hole options', array('@s' => $context->identifier));
}

