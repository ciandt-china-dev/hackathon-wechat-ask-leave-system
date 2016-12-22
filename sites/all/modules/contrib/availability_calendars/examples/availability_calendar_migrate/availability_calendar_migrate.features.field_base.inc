<?php
/**
 * @file
 * availability_calendar_migrate.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function availability_calendar_migrate_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_availability'.
  $field_bases['field_availability'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_availability',
    'indexes' => array(
      'cid' => array(
        0 => 'cid',
      ),
    ),
    'locked' => 0,
    'module' => 'availability_calendar',
    'settings' => array(
      'allocation_type' => 'night',
      'allowed_states' => array(
        1 => 0,
        2 => 2,
        3 => 3,
        4 => 4,
      ),
      'default_state' => 1,
    ),
    'translatable' => 0,
    'type' => 'availability_calendar',
  );

  return $field_bases;
}
