<?php

if (module_exists('upload')) {
  /**
   * Plugins are described by creating a $plugin array which will be used
   * by the system that includes this file.
   */
  $plugin = array(
    'single' => TRUE,
    'icon' => 'icon_node_form.png',
    'title' => t('Node form file attachments'),
    'description' => t('File attachments on the Node form.'),
    'required context' => new ctools_context_required(t('Form'), 'node_form'),
    'category' => t('Node Form Panes'),
    'edit form' => 'node_form_panes_node_form_content_type_edit_form',
    'render callback' => 'node_form_panes_node_form_attachments_content_type_render',
    'admin title' => 'node_form_panes_node_form_attachments_content_type_admin_title',
  );
}

function node_form_panes_node_form_attachments_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = t('node_form');
  $block->delta = 'url-path-options';

  if (isset($context->form)) {
    if (isset($context->form['attachments'])) {
      $block->content = $context->form['attachments'];
      if (isset($block->content['attachments']['#group'])) {
        node_form_panes_node_form_process_element($block->content['attachments'], $conf);
        if (!$conf['display_in_fieldset']) {
          $block->title = t('Attach files');
        }
      }
      // Set access to false on the original rather than removing so that
      // vertical tabs doesn't clone it. I think this is due to references.
      $context->form['attachments']['#access'] = FALSE;
    }
  }
  else {
    $block->content = t('Attach files.');
  }
  return $block;
}

function node_form_panes_node_form_attachments_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" node form attach files', array('@s' => $context->identifier));
}
