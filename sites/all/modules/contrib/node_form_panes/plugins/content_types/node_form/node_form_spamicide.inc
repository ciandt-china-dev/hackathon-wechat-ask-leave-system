<?php

/**
 * @file
 * Ctools pane plugin for the node_form_panes module to provide the Spamicide
 * module field as a content pane.
 *
 */
if (module_exists('spamicide')) {
  $plugin = array(
    'single' => TRUE,
    'icon' => 'icon_node_form.png',
    'title' => t('Node Form Spamicide add protection link'),
    'description' => t('The Spamicide "Add protection to this form" link.'),
    'required context' => new ctools_context_required(t('Form'), 'node_form'),
    'category' => t('Node Form Panes'),
    'edit form' => 'node_form_panes_node_form_content_type_edit_form',
    'render callback' => 'node_form_panes_node_form_spamicide_content_type_render',
    'admin title' => 'node_form_panes_node_form_spamicide_content_type_admin_title',
  );
}

function node_form_panes_node_form_spamicide_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = t('node_form');
  $block->delta = 'spamicide';
  if (isset($context->form)) {
    if (!empty($context->form['spamicide']['add_spamicide'])) {
      $block->content['spamicide'] = $context->form['spamicide'];
      node_form_panes_node_form_process_element($block->content['spamicide'], $conf);
      if (!$conf['display_in_fieldset']) {
        $block->title = t('Spamicide options');
      }
      // Set access to false on the original rather than removing so that
      // vertical tabs doesn't clone it. I think this is due to references.
      $context->form['spamicide']['#access'] = FALSE;
    }
  }
  else {
    $block->content = t('Spamicide options.');
  }

  return $block;
}

function node_form_panes_node_form_spamicide_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" node form spamicide add protection link', array('@s' => $context->identifier));
}
