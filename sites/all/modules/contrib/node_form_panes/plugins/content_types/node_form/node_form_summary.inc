<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'icon' => 'icon_node_form.png',
  'title' => t('Node form summary'),
  'description' => t('Summary of node properties such as published, publish date, author etc.'),
  'required context' => new ctools_context_required(t('Form'), 'node_form'),
  'category' => t('Node Form Panes'),
  'edit form' => 'node_form_panes_node_form_summary_content_type_edit_form',
  'render callback' => 'node_form_panes_node_form_summary_content_type_render',
  'admin title' => 'node_form_panes_node_form_summary_content_type_admin_title',
  'defaults' => array(
    'summary_options' => array(
      'buttons' => 0,
      'hide_buttons' => 1,
      'published' => 1,
      'authored_by' => 1,
      'authored_on' => 1,
      'promote' => 1,
      'promote_text' => t('Promoted to front page'),
      'sticky' => 1,
      'scheduler' => 1,
    ),
  ),
);

/**
 * Render Callback for the node form summary content type
 */
function node_form_panes_node_form_summary_content_type_render($subtype, $conf, $panel_args, &$context) {

  $block = new stdClass();
  $block->module = t('node_form');
  $block->delta = 'node-form-summary';
  $block->content = array();

  // If we're displaying this block in a fieldset...
  if ($conf['display_in_fieldset']) {
    $block->content = array(
      '#type' => 'fieldset',
      '#title' => t('Summary'),
      '#collapsible' => $conf['collapsible'],
      '#collapsed' => $conf['collapsed'],
      '#attributes' => array(
        'class' => array('node-form-summary'),
      ),
    );
  }
  else {
    $block->title = t('Summary');
    $block->content['#prefix'] = '<div class="node-form-summary">';
    $block->content['#suffix'] = '</div>';
  }

  // Attach our css and js
  $block->content['#attached'] = array(
    'css' => array(drupal_get_path('module', 'node_form_panes') . '/css/node_form_panes.css'),
    'js' => array(drupal_get_path('module', 'node_form_panes') . '/js/node_form_panes.js'),
  );

  // Add the submit buttons to the block if it's configured
  if ($conf['buttons']) {
    $block->content['buttons'] = array(
      '#weight' => -1,
    );
    foreach (array('actions', 'form_token', 'form_build_id', 'form_id') as $element) {
      $block->content['buttons'][$element] = isset($context->form[$element]) ? $context->form[$element] : NULL;
      // Remove the action buttons if configured to do so.
      $hide_buttons = isset($conf['hide_buttons']) ? $conf['hide_buttons'] : 1;
      if ($hide_buttons || $element != 'actions') {
        unset($context->form[$element]);
      }
    }
  }

  // Process the publishing options
  node_form_panes_process_publishing_options($block, $context, $conf);

  // Process the scheduler options
  node_form_panes_process_scheduler($block, $context, $conf);

  // Process the authoring information
  node_form_panes_process_authoring_info($block, $context, $conf);

  return $block;
}

/**
 * Callback for the admin title
 */
function node_form_panes_node_form_summary_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" node form summary', array('@s' => $context->identifier));
}

/**
 * The settings form for the content type
 */
function node_form_panes_node_form_summary_content_type_edit_form($form, &$form_state) {

  // Using ctools dependent fields because it does that nifty indent thing.
  ctools_include('dependent');

  $conf = $form_state['conf'];

  $form['summary_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Summary Options'),
    '#tree' => FALSE,
    '#weight' => 10,
  );

  $form['summary_options']['buttons'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include form buttons in summary block.'),
    '#default_value' => isset($conf['buttons']) ? $conf['buttons'] : 0,
    '#weight' => 10,
  );

  $form['summary_options']['hide_buttons'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide buttons on original form?'),
    '#default_value' => isset($conf['hide_buttons']) ? $conf['hide_buttons'] : 1,
    '#weight' => 10,
    '#states' => array(
      // Only show this field when the 'toggle_me' checkbox is enabled.
      'visible' => array(
        ':input[name="buttons"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['summary_options']['published'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include a summary for if the node is published or not'),
    '#default_value' => isset($conf['published']) ? $conf['published'] : 1,
    '#weight' => 11,
  );

  $form['summary_options']['authored_by'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include the "Authored by" field'),
    '#description' => t('It is recommended that you disable the "Authoring Information" node form pane when this field is enabled.'),
    '#default_value' => isset($conf['authored_by']) ? $conf['authored_by'] : 1,
    '#weight' => 12,
  );

  $form['summary_options']['authored_on'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include the "Authored on" field'),
    '#description' => t('It is recommended that you disable the "Authoring Information" node form pane when this field is enabled.'),
    '#default_value' => isset($conf['authored_by']) ? $conf['authored_by'] : 1,
    '#weight' => 13,
  );

  $form['summary_options']['promote'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include the "Promoted to front page" field'),
    '#description' => t('It is recommended that you disable the "Publishing Options" node form pane when this field is enabled.'),
    '#default_value' => isset($conf['promote']) ? $conf['promote'] : 1,
    '#weight' => 14,
  );

  $form['summary_options']['promote_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Promoted text:'),
    '#description' => t('You may choose to customize the promoted text in the node form summary.'),
    '#default_value' => isset($conf['promote_text']) ? $conf['promote_text'] : t('Promoted to front page'),
    '#weight' => 14,
    '#dependency' => array('edit-promote' => array(1)),
  );

  $form['summary_options']['sticky'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include the "Sticky at top of lists" field'),
    '#description' => t('It is recommended that you disable the "Publishing Options" node form pane when this field is enabled.'),
    '#default_value' => isset($conf['sticky']) ? $conf['sticky'] : 1,
    '#weight' => 15,
  );

  if (module_exists('scheduler')) {
    $form['summary_options']['scheduler'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add scheduler support for "Authored on" field'),
      '#description' => t('If scheduled publishing is enabled on this node type, dates set in the future for the "Authored On" field will also set the node to be scheduled to be published. Also, the scheduler "Unpublish on" field will be added. It is recommended that you disable the "Scheduler settings" node form pane when this setting is enabled'),
      '#default_value' => isset($conf['scheduler']) ? $conf['scheduler'] : 1,
    '#weight' => 16,
    );
  }

  // Steal the display options from our unified form
  $form += node_form_panes_node_form_content_type_edit_form($form, $form_state);

  return $form;
}

/**
 * Submit handler for the settings form.
 */
function node_form_panes_node_form_summary_content_type_edit_form_submit($form, &$form_state) {
  foreach ($form_state['values'] as $key => $value) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/***********************************************************************
 *
 * Helper Functions
 *
 ***********************************************************************/

/**
 * Process the authoring information part of the node form
 *
 * @param  object $block
 *         The node form summary form
 *
 * @param  object $context
 *         The ctools content type context
 */
function node_form_panes_process_authoring_info(&$block, &$context, $conf) {
  // If the authored by field is configured to show
  if ($conf['authored_by'] && node_form_summary_check_element_access($context->form['author']['name'])) {
    // Grab the default value
    $authored_by = $context->form['author']['name']['#default_value'] ? $context->form['author']['name']['#default_value'] : t('not set');
    // Add our authored by markup. Link is configured to toggle the actual field
    $block->content['author']['authored_by'] = array(
      '#markup' => '<span class="label">Authored by:</span> <span class="value authored-by">' . $authored_by . '</span> <a href="#" class="edit-authored-by node-form-summary-toggle" data-toggle="form-item-name">edit</a>',
      '#prefix' => '<div class="node-form-summary-summary node-form-authored-by">',
      '#suffix' => '</div>',
      '#weight' => 1,
    );
    // Add the name field. Field is hidden by css and shown when the
    // 'edit' link is clicked (defined above) using js in node_form_panes.js
    $block->content['author']['name'] = $context->form['author']['name'];
    // Configure weights
    $block->content['author']['name']['#weight'] = 2;
    $block->content['author']['#weight'] = 1;
  }


  if ($conf['authored_on'] && node_form_summary_check_element_access($context->form['author']['date'])) {
    // Grab the authored on date default value
    $authored_on_date = isset($context->data->date) ? format_date($context->data->created) : t('now');
    // Add our authored by markup. Link is configured to toggle the actual field
    $block->content['author']['authored_on'] = array(
      '#markup' => '<span class="label">Authored on:</span> <span class="value authored-on-date">' . $authored_on_date . '</span> <a href="#" class="edit-authored-on-date node-form-summary-toggle" data-toggle="form-item-date">edit</a>',
      '#prefix' => '<div class="node-form-summary-summary node-form-authored-on-date">',
      '#suffix' => '</div>',
      '#weight' => 3,
    );
    // Add the date field. Field is hidden by css and shown when the
    // 'edit' link is clicked (defined above) using js in node_form_panes.js
    $block->content['author']['date'] = $context->form['author']['date'];
    $block->content['author']['date']['#date_increment'] = 15;
    // Extra functionality description
    $authored_on_description = ' Leave blank to set authored on date to now.';
    // Support for scheduler
    if ($conf['scheduler']) {
      $authored_on_description .= '<br> Dates in the future will be scheduled to be published.';
      // This is a little trick to sneak a custom submit handler in to add
      // scheduled publishing support to the 'published on' field. We can't just
      // add a submit handler here because the form has already been procesed.
      // So, we've added a special hidden element 'node_form_summary_submit' and
      // a custom submit handler in node_form_panes.module.
      // @see node_form_panes_submit_node_form for more info
      $context->form['node_form_summary_submit']['#value'] = '1';
    }
    // Add description and weight
    if (!empty($block->content['author']['date']['#description'])) {
      $block->content['author']['date']['#description'] .= $authored_on_description;
    }
    else {
      $block->content['author']['date']['#description'] = $authored_on_description;
    }
    $block->content['author']['date']['#weight'] = 4;
  }

  // Set hide authored settings from vertical tabs
  if ($conf['authored_by'] || $conf['authored_on']) {
    $context->form['author']['#access'] = FALSE;
  }
}

/**
 * Process the authoring information part of the node form
 *
 * @param  object $block
 *         The node form summary form
 *
 * @param  object $context
 *         The ctools content type context
 */
function node_form_panes_process_scheduler(&$block, &$context, $conf) {
  // Add scheduler if it's configured to show and the node type is configured
  // for scheduled publishing. Note that this only adds the unpublish field
  // since scheduled publishing is handled through the "authored on" field
  if (!empty($conf['scheduler'])) {
    if (isset($context->form['scheduler_settings']['unpublish_on'])) {
      // Get the default value of the unpublish date
      $unpublish_on_date = $context->form['scheduler_settings']['unpublish_on']['#default_value'] ?
                            $context->form['scheduler_settings']['unpublish_on']['#default_value'] :
                            'not set';
      // Link is configured to toggle the actual field
      $block->content['scheduler_settings']['unpublish'] = array(
        '#markup' => '<span class="label">Unpublish on:</span> <span class="value unpublish-on-date">' . $unpublish_on_date . '</span> <a href="#" class="edit-unpublish-date node-form-summary-toggle" data-toggle="form-item-unpublish-on">edit</a>',
        '#prefix' => '<div class="node-form-summary-summary node-form-unpublish-date">',
        '#suffix' => '</div>',
        '#weight' => 5,
      );
      // Add the unpublish field. Field is hidden by css and shown when the
      // 'edit' link is clicked (defined above) using js in node_form_panes.js
      $block->content['scheduler_settings']['unpublish_on'] = $context->form['scheduler_settings']['unpublish_on'];
      // Set some weights
      $block->content['scheduler_settings']['unpublish_on']['#weight'] = 6;
      $block->content['scheduler_settings']['#weight'] = 3;
      // Set hide scheduler settings from vertical tabs
      $context->form['scheduler_settings']['#access'] = FALSE;
    }
  }
}

/**
 * Process the Publishing options part of the node form
 *
 * @param  object $block
 *         The node form summary form
 *
 * @param  object $context
 *         The ctools content type context
 */
function node_form_panes_process_publishing_options(&$block, &$context, $conf) {
  // Add publishing information to the form if it's configured
  if ($conf['published']) {
    $block->content['published'] = array(
      '#type' => 'html_tag',
      '#tag' => 'div',
      '#attributes' => array(
        'class' => array('node-form-summary-publish'),
      ),
      '#weight' => 0,
    );
    // Check if the content is published, unpublished or new
    if (empty($context->data->nid)) {
      // New Content
      $block->content['published']['#value'] = 'This is new content and has not been saved yet';
      $block->content['published']['#attributes']['class'][] = 'new';
    }
    elseif (!empty($context->data->status) && $context->data->status) {
      // Published
      $block->content['published']['#value'] = 'This content is currently published';
      $block->content['published']['#attributes']['class'][] = 'published';
    }
    else {
      // Unpublished
      $block->content['published']['#value'] = 'This content is currently unpublished';
      $block->content['published']['#attributes']['class'][] = 'unpublished';
    }
  }
  // dpm($context->form['options']);
  // dpm($conf);
  if (!empty($conf['promote']) && node_form_summary_check_element_access($context->form['options']['promote'])) {

    // Sort out the promoted label
    $promote_text = t('Promoted to front page');
    if (!empty($conf['promote_text'])) {
      $promote_text = $conf['promote_text'];
      $context->form['options']['promote']['#title'] = $promote_text;
    }

    // Grab the default value
    $promoted = $context->form['options']['promote']['#default_value'] ? t('Yes') : t('No');
    // Add our authored by markup. Link is configured to toggle the actual field
    $block->content['options']['promoted'] = array(
      '#markup' => '<span class="label">' . $promote_text . ':</span> <span class="value promoted">' . $promoted . '</span> <a href="#" class="edit-promoted node-form-summary-toggle" data-toggle="form-item-promote">edit</a>',
      '#prefix' => '<div class="node-form-summary-summary node-form-promote">',
      '#suffix' => '</div>',
      '#weight' => 8,
    );
    // Add the name field. Field is hidden by css and shown when the
    // 'edit' link is clicked (defined above) using js in node_form_panes.js
    $block->content['options']['promote'] = $context->form['options']['promote'];
    // Configure weights
    $block->content['options']['promote']['#weight'] = 9;
    $block->content['options']['#weight'] = 4;
  }

  if (!empty($conf['sticky']) && node_form_summary_check_element_access($context->form['options']['sticky'])) {
    // Grab the default value
    $promoted = $context->form['options']['sticky']['#default_value'] ? t('Yes') : t('No');
    // Add our authored by markup. Link is configured to toggle the actual field
    $block->content['options']['sticky_summary'] = array(
      '#markup' => '<span class="label">Sticky at top of lists:</span> <span class="value sticky">' . $promoted . '</span> <a href="#" class="edit-promoted node-form-summary-toggle" data-toggle="form-item-sticky">edit</a>',
      '#prefix' => '<div class="node-form-summary-summary node-form-sticky">',
      '#suffix' => '</div>',
      '#weight' => 10,
    );
    // Add the name field. Field is hidden by css and shown when the
    // 'edit' link is clicked (defined above) using js in node_form_panes.js
    $block->content['options']['sticky'] = $context->form['options']['sticky'];
    // Configure weights
    $block->content['options']['sticky']['#weight'] = 11;
    $block->content['options']['#weight'] = 4;
  }

  // Do this no matter what. These options don't belong in the vertical tabs
  // anyway... right? This might not be a good idea...
  $context->form['options']['#access'] = FALSE;
}

/**
 * Utility function to help check the #access of a form element. If the #access
 * property is there, we check it. Otherwise we assume access is granted.
 *
 * @param array $element
 *        The element to check for #access
 *
 * @return boolean
 *         TRUE or FALSE depending on access
 */
function node_form_summary_check_element_access($element) {
  $access = TRUE;
  if (isset($element['#access']) && !$element['#access']) {
    $access = FALSE;
  }
  return $access;
}
