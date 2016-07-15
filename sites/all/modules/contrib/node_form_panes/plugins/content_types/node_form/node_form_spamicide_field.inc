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
    'title' => t('Node Form Spamicide hidden field'),
    'description' => t('Hidden spam honeypot field from the Spamicide module'),
    'required context' => new ctools_context_required(t('Form'), 'node_form'),
    'category' => t('Node Form Panes'),
    'edit form' => 'node_form_panes_node_form_spamicide_field_edit_form',
    'render callback' => 'node_form_panes_node_form_spamicide_field_content_type_render',
    'admin title' => 'node_form_panes_node_form_spamicide_field_content_type_admin_title',
  );
}

function node_form_panes_node_form_spamicide_field_edit_form($form, &$form_state) {

  // Allow the default pane wrapper to be overriden.
  $conf = $form_state['conf'];
  $form['spamicide_aligner_start'] = array(
    '#markup' => '<div class="option-text-aligner clearfix">',
  );
  $form['override_spamicide_wrapper'] = array(
    '#type' => 'checkbox',
    '#default_value' => isset($conf['override_spamicide_wrapper']) ? $conf['override_spamicide_wrapper'] : '',
    '#title' => t('Override Spamicide pane wrapper class'),
    '#id' => 'override-spamicide-wrapper-checkbox',
  );
  $form['override_spamicide_wrapper_text'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($conf['override_spamicide_wrapper_text']) ? $conf['override_spamicide_wrapper_text'] : '',
    '#size' => 35,
    '#id' => 'override-spamicide-wrapper-textfield',
    '#dependency' => array('override-spamicide-wrapper-checkbox' => array(1)),
    '#dependency_type' => 'disable',
  );
    $form['spamicide_aligner_stop'] = array(
    '#markup' => '</div>',
  );
  $form['override_spamicide_markup'] = array(
    '#prefix' => '<div class="description">',
    '#suffix' => '</div>',
    '#markup' => t('To futher obsure the purpose of the field you can set the wrapper class here, otherwise the name set in the Spamicide configuration will be used.'),
  );

  return $form;
}

function node_form_panes_node_form_spamicide_field_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['override_spamicide_wrapper'] = $form_state['values']['override_spamicide_wrapper'];
  $form_state['conf']['override_spamicide_wrapper_text'] = $form_state['values']['override_spamicide_wrapper_text'];
}

function node_form_panes_node_form_spamicide_field_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = t('node_form');
  $block->delta = 'spamicide';
  if (isset($context->form)) {
    if (isset($context->form['spamicide'])) {
      module_load_include('inc', 'spamicide');
      if ($spamicide_field = _spamicide_get_field($context->form['#form_id'])) {
        $block->content['spamicide'] = $context->form[$spamicide_field];
        // Set access to false on the original rather than removing so that
        // it doesn't get output again
        $context->form[$spamicide_field]['#access'] = FALSE;
      }
    }
  }
  return $block;
}

function node_form_panes_node_form_spamicide_field_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" node form spamicide hidden field', array('@s' => $context->identifier));
}
