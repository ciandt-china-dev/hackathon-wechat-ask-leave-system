<?php

/**
 * @file
 * Migrate field handlers.
 *
 * @see https://www.drupal.org/node/1429096.
 */

/**
 * Migrates availability data to availability_calendar fields.
 */
class AvailabilityCalendarFieldHandler extends MigrateFieldHandler {
  /**
   * Registers the availability_calendar field type.
   */
  public function __construct() {
    $this->registerTypes(array('availability_calendar'));
  }

  /**
   * Prepares data accordingly for the field API.
   */
  public function prepare($entity, array $field_info, array $instance, array $values) {
    module_load_include('inc', 'availability_calendar', 'availability_calendar.widget');
    $migration = Migration::currentMigration();
    $arguments = (isset($values['arguments'])) ? $values['arguments'] : array();
    $language = $this->getFieldLanguage($entity, $field_info, $arguments);
    $delta = 0;
    $return = array();
    // In order to be compatible with the way Availability Calendars works, see
    // prepareCalendar() method.
    $element = array(
      'availability_states' => array(
        '#options' => availability_calendar_get_states(),
      ),
      'availability_calendar' => array(
        '#settings' => $instance['widget']['settings'],
      ),
      '#field_name' => $instance['field_name'],
      '#language' => $language,
    );
    foreach ($values as $value) {
      $element['#delta'] = $delta;
      $cid = $this->prepareCalendar($value, $element, $entity);
      if (!$cid) {
        return NULL;
      }
      $return[$language][$delta] = array(
        'enabled' => 1,
        'name' => '',
        'cid' => $cid,
      );
      $delta++;
    }

    return $return;
  }

  /**
   * Prepares an Availability Calendar.
   *
   * The actual availability data is not stored in field storage but in tables
   * specific to the module. Therefore we have to prepare a calendar field by
   * first storing the availability data in those module owned tables and then
   * storing the reference to that data, the cid (= calendar ID), in the field.
   *
   * @param string|array[] $dates
   *   Availability data, either in a string format, see README.txt, or in an
   *   array as accepted by
   *   availability_calendar_update_multiple_availability().
   * @param array $element
   *   Field configuration expected by
   *   availability_calendar_field_widget_month_form_validate_line().
   * @param object $entity
   *   Entity about to be created by Migrate.
   *
   * @return int
   *   ID of the newly created availability calendar entity.
   */
  protected function prepareCalendar($dates, $element, $entity) {
    if (is_string($dates)) {
      $dates = $this->convertAvailabilityString($dates, $element);
    }
    $field_name = $element['#field_name'];
    $language_code = $element['#language'];
    $delta = $element['#delta'];

    // Update or create calendar.
    $cid = isset($entity->{$field_name}[$language_code][$delta]['cid']) ? $entity->{$field_name}[$language_code][$delta]['cid'] : NULL;
    $cid = availability_calendar_update_multiple_availability($cid, $dates);
    if (!isset($entity->{$field_name}[$language_code][$delta]['cid']) || $cid != $entity->{$field_name}[$language_code][$delta]['cid']) {
      // New calendar: update field.
      $entity->{$field_name}[$language_code][$delta]['cid'] = $cid;
    }
    return $cid;
  }

  /**
   * Converts a string specifying the availability to an array.
   *
   * Converts a string specifying the availability to a "multiple availability"
   * array.
   *
   * @param string $dates
   *   Availability data, see README.txt for a description of the expected
   *   format.
   * @param array $element
   *   Field configuration expected by
   *   availability_calendar_field_widget_month_form_validate_line().
   *
   * @return array
   *   Array with the availability as accepted by
   *   availability_calendar_update_multiple_availability().
   *
   * @see availability_calendar_field_widget_month_form_validate()
   * @see availability_calendar_field_attach_submit_inc()
   */
  protected function convertAvailabilityString($dates, $element) {
    $changes = array();
    $lines = explode("\n", $dates);
    foreach ($lines as $line) {
      $line = trim($line);
      if (!empty($line)) {
        $change = availability_calendar_field_widget_month_form_validate_line($line, $element, TRUE);
        if ($change === FALSE) {
          watchdog('availability_calendar', "Invalid availability data: %line", array('%line' => $line), WATCHDOG_ERROR);
          return FALSE;
        }
        $changes[] = $change;
      }
    }
    return $changes;
  }

}
