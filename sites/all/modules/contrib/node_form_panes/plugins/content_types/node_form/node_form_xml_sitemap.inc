<?php
/**
 * @file
 * Provides node form pane for xml sitemap.
 */

if (module_exists('xmlsitemap')) {
  // Plugins definition.
  $plugin = array(
    'single' => TRUE,
    'icon' => 'icon_node_form.png',
    'title' => t('Node form XML sitemap settings'),
    'description' => t('XML sitemap options on the Node form.'),
    'required context' => new ctools_context_required(t('Form'), 'node_form'),
    'category' => t('Node Form Panes'),
    'edit form' => 'node_form_panes_node_form_content_type_edit_form',
    'render callback' => 'node_form_panes_node_form_xmlsitemap_content_type_render',
    'admin title' => 'node_form_panes_node_form_xmlsitemap_content_type_admin_title',
  );
}

function node_form_panes_node_form_xmlsitemap_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = t('node_form');

  $block->delta = 'xmlsitemap-path-options';

  if (isset($context->form)) {
    if (isset($context->form['xmlsitemap'])) {
      $block->content['xmlsitemap'] = $context->form['xmlsitemap'];
      node_form_panes_node_form_process_element($block->content['xmlsitemap'], $conf);
      if (!$conf['display_in_fieldset']) {
        $block->title = t('XML sitemap settings');
      }

      // Set access to false on the original rather than removing so that
      // vertical tabs doesn't clone it. I think this is due to references.
      $context->form['xmlsitemap']['#access'] = FALSE;
    }
  }
  else {
    $block->content = t('XML sitemap options.');
  }
  return $block;
}

/**
 * Admin title callback.
 */
function node_form_panes_node_form_xmlsitemap_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" node form XML sitemap options', array('@s' => $context->identifier));
}
