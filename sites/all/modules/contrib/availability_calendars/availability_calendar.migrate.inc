<?php

/**
 * @file
 * Integration with Migrate.
 */

/**
 * Implements hook_migrate_api().
 */
function availability_calendar_migrate_api() {
  return array(
    'api' => 2,
    'field handlers' => array(
      'AvailabilityCalendarFieldHandler',
    ),
  );
}
