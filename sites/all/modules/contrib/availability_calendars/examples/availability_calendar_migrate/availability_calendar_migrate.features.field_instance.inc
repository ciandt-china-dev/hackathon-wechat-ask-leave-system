<?php
/**
 * @file
 * availability_calendar_migrate.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function availability_calendar_migrate_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'node-availability_calendar_migrate-field_availability'.
  $field_instances['node-availability_calendar_migrate-field_availability'] = array(
    'bundle' => 'availability_calendar_migrate',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'availability_calendar',
        'settings' => array(
          'first_day_of_week' => 6,
          'selectable' => FALSE,
          'show_number_of_months' => 12,
          'show_only_first_letter' => 0,
          'show_split_day' => 0,
          'show_week_number' => 0,
          'viewport' => array(
            'button_placement' => 'after',
            'cols' => 3,
            'dimensions_calculation' => 'fixed',
            'rows' => 1,
            'scroll' => 1,
          ),
        ),
        'type' => 'availability_calendar_viewport',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_availability',
    'label' => 'Availability',
    'required' => 0,
    'settings' => array(
      'add_name' => 1,
      'allow_disable' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'availability_calendar',
      'settings' => array(
        'first_day_of_week' => 6,
        'show_number_of_months' => 18,
        'show_only_first_letter' => 0,
        'show_split_day' => 0,
        'show_week_number' => 0,
        'viewport' => array(
          'button_placement' => 'before',
          'cols' => 3,
          'dimensions_calculation' => 'fixed',
          'rows' => 2,
          'scroll' => 1,
        ),
      ),
      'type' => 'availability_calendar_viewport',
      'weight' => -4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Availability');

  return $field_instances;
}
