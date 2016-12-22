<?php

if (module_exists('metatag')) {
  /**
   * Plugins are described by creating a $plugin array which will be used
   * by the system that includes this file.
   */
  $plugin = array(
    'single' => TRUE,
    'icon' => 'icon_node_form.png',
    'title' => t('Node form metatag settings'),
    'description' => t('Metatags options on the Node form.'),
    'required context' => new ctools_context_required(t('Form'), 'node_form'),
    'category' => t('Node Form Panes'),
    'edit form' => 'node_form_panes_node_form_content_type_edit_form',
    'render callback' => 'node_form_panes_node_form_metatag_content_type_render',
    'admin title' => 'node_form_panes_node_form_metatag_content_type_admin_title',
  );
}

function node_form_panes_node_form_metatag_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = t('node_form');
  $block->delta = 'metatag-path-options';

  if (isset($context->form)) {

    if (isset($context->form['metatags'])) {

      $block->content['metatags'] = $context->form['metatags'];
      node_form_panes_node_form_process_element($block->content['metatags'], $conf);
      if (!$conf['display_in_fieldset']) {
        $block->title = t('Metatags');
      }

      // Set access to false on the original rather than removing so that
      // vertical tabs doesn't clone it. I think this is due to references.
      $context->form['metatags']['#access'] = FALSE;
    }
  }
  else {
    $block->content = t('Metatags options.');
  }
  return $block;
}

function node_form_panes_node_form_metatag_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" node form metatag options', array('@s' => $context->identifier));
}
