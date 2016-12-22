<?php

if (module_exists('path')) {
  /**
   * Plugins are described by creating a $plugin array which will be used
   * by the system that includes this file.
   */
  $plugin = array(
    'single' => TRUE,
    'icon' => 'icon_node_form.png',
    'title' => t('Node form url path settings'),
    'description' => t('Publishing options on the Node form.'),
    'required context' => new ctools_context_required(t('Form'), 'node_form'),
    'category' => t('Node Form Panes'),
    'edit form' => 'node_form_panes_node_form_content_type_edit_form',
    'render callback' => 'node_form_panes_node_form_path_content_type_render',
    'admin title' => 'node_form_panes_node_form_path_content_type_admin_title',
  );
}

function node_form_panes_node_form_path_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = t('node_form');
  $block->delta = 'url-path-options';
  // Attach our css and js
  $block->content['#attached'] = array(
    'js' => array(drupal_get_path('module', 'node_form_panes') . '/js/node_form_panes.js'),
    'css' => array(drupal_get_path('module', 'node_form_panes') . '/css/node_form_panes.css'),
  );

  if (isset($context->form)) {
    if (isset($context->form['path'])) {
      $block->content['path'] = $context->form['path'];
      if (isset($block->content['path']['alias']['#size'])) {
        $block->content['path']['alias']['#size'] /= 2;
      }
      node_form_panes_node_form_process_element($block->content['path'], $conf);
      unset($block->content['path']['alias']['#description']);
      $block->content['path']['alias']['#title'] = '<span class="label-wrapper"><strong>' . t('Permalink') . ':</strong> ';
      $block->content['path']['alias']['#title'] .= (isset($_SERVER['HTTPS'])) ? 'https://' . $_SERVER['HTTP_HOST'] . '/' : 'http://' . $_SERVER['HTTP_HOST'] . '/</span>';
      if (isset($block->content['path']['pathauto'])) {
        $block->content['path']['alias']['#states'] = array();
        if (!$block->content['path']['alias']['#default_value']) {
          $block->content['path']['alias']['#attributes'] = array('placeholder' => '<' . t('magically generated') . '>');
        }
        // This tells our submit handler to run
        $context->form['node_form_path_submit']['#value'] = 1;
      }
      if (!$conf['display_in_fieldset']) {
        $block->title = t('URL path options');
      }

      // Set access to false on the original rather than removing so that
      // vertical tabs doesn't clone it. I think this is due to references.
      $context->form['path']['#access'] = FALSE;
    }
  }
  else {
    $block->content = t('URL Path options.');
  }
  return $block;
}

function node_form_panes_node_form_path_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" node form path options', array('@s' => $context->identifier));
}
