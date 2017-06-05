<?php
/**
 * @file
 * vacation_days_logs_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function vacation_days_logs_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function vacation_days_logs_feature_node_info() {
  $items = array(
    'vacation_days_logs' => array(
      'name' => t('Vacation days logs'),
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
