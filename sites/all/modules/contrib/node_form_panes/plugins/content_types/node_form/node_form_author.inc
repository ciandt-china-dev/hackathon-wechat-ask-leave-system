<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'icon' => 'icon_node_form.png',
  'title' => t('Node form author information'),
  'description' => t('Author information on the Node form.'),
  'required context' => new ctools_context_required(t('Form'), 'node_form'),
  'category' => t('Node Form Panes'),
  'edit form' => 'node_form_panes_node_form_content_type_edit_form',
  'render callback' => 'node_form_panes_node_form_author_content_type_render',
  'admin title' => 'node_form_panes_node_form_author_content_type_admin_title',
);

function node_form_panes_node_form_author_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = t('node_form');
  $block->delta = 'author-options';

  if (isset($context->form)) {
    if (!empty($context->form['author'])) {
      $block->content['author'] = $context->form['author'];
      if (isset($block->content['author']['#group'])) {
        if (isset($block->content['author']['date']['#size'])) {
          $block->content['author']['name']['#size'] /= 2;
        }
        if (isset($block->content['author']['date']['#size'])) {
          $block->content['author']['date']['#size'] /= 2;
        }
        node_form_panes_node_form_process_element($block->content['author'], $conf);
        if (!$conf['display_in_fieldset']) {
          $block->title = t('Authoring information');
        }
      }

      // Set access to false on the original rather than removing so that
      // vertical tabs doesn't clone it. I think this is due to references.
      $context->form['author']['#access'] = FALSE;
    }
  }
  else {
    $block->content = t('Authoring information.');
  }
  return $block;
}

function node_form_panes_node_form_author_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" node form author information', array('@s' => $context->identifier));
}
