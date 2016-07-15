<?php
/**
 * @file
 * vocation_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function vocation_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function vocation_feature_node_info() {
  $items = array(
    'vocation' => array(
      'name' => t('Vocation'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
