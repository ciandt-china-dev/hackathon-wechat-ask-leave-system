<?php
/**
 * @file
 * availability_calendar_migrate.features.inc
 */

/**
 * Implements hook_node_info().
 */
function availability_calendar_migrate_node_info() {
  $items = array(
    'availability_calendar_migrate' => array(
      'name' => t('Migrate example - Availability Calendar'),
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
