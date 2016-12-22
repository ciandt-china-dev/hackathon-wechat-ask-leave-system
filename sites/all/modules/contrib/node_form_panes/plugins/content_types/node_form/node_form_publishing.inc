<?php

/**
 * @file
 * Publishing options form for the node. This contains the basic settings
 * like published, moderated, node revision, etc.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Node form publishing options'),
  'icon' => 'icon_node_form.png',
  'description' => t('Publishing options on the Node form.'),
  'required context' => new ctools_context_required(t('Form'), 'node_form'),
  'category' => t('Node Form Panes'),
  'edit form' => 'node_form_panes_node_form_content_type_edit_form',
  'render callback' => 'node_form_panes_node_form_publishing_content_type_render',
  'admin title' => 'node_form_panes_node_form_publishing_content_type_admin_title',
);

function node_form_panes_node_form_publishing_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();

  $block->module = t('node_form');
  $block->delta = 'publishing-options';

  if (isset($context->form)) {
    if (isset($context->form['options'])) {
      $block->content['options'] = $context->form['options'];
      node_form_panes_node_form_process_element($block->content['options'], $conf);
      if (!$conf['display_in_fieldset']) {
        $block->title = t('Publishing options');
      }

      // Set access to false on the original rather than removing so that
      // vertical tabs doesn't clone it. I think this is due to references.
      $context->form['options']['#access'] = FALSE;
    }
  }
  else {
    $block->content = t('Publishing options.');
  }
  return $block;
}

function node_form_panes_node_form_publishing_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" node form publishing options', array('@s' => $context->identifier));
}
