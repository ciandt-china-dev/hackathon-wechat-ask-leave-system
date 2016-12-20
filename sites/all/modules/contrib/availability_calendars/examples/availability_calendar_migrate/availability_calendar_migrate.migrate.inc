<?php
/**
 * @file
 * Example of availability data migration.
 */

/**
 * Migration class to test import of availability data.
 */
class MigrateExampleAvailabilityCalendar extends XMLMigration {
  /**
   * Describe migration.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Import availability data');

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'Technical ID',
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    // Source fields available in the XML file.
    $fields = array(
      'id' => t('Source id'),
      'title' => t('Title'),
      'availability' => t('Availability data'),
    );

    // Our test data is in an XML file.
    $xml_folder = drupal_get_path('module', 'availability_calendar_migrate');
    $items_url = $xml_folder . '/availability_calendar_migrate.xml';
    $item_xpath = '/source_data/item';
    $item_id_xpath = 'id';
    $items_class = new MigrateItemsXML($items_url, $item_xpath, $item_id_xpath);
    $this->source = new MigrateSourceMultiItems($items_class, $fields);
    $this->destination = new MigrateDestinationNode('availability_calendar_migrate');

    // Basic fields.
    $this->addFieldMapping('title', 'title')
         ->xpath('title');
    $this->addFieldMapping('uid')
         ->defaultValue(1);
    $this->addFieldMapping('field_availability', 'availability')
         ->xpath('availability');

    // Unmapped destination fields.
    $this->addUnmigratedDestinations(array('is_new', 'status', 'promote',
      'revision', 'language', 'sticky', 'created', 'changed', 'revision_uid',
      'path',
    ));
  }

  /**
   * Convert source data to another format before the migration.
   *
   * Your data are quite likely to be in a very different format in the source,
   * compared with the format expected by Availability Calendar. In our case,
   * they are stored in the XML file as as string containing as many characters
   * as days in a year, each character representing availability for the
   * corresponding day in the year (in a positional way, the first character
   * stands for January 1, the second January 2, and so on until the last one
   * which stands for December 31).
   */
  public function prepareRow($row) {
    parent::prepareRow($row);

    if (!isset($row->xml->availability)) {
      return;
    }

    // Match booking states codes, see availability_calendar_state table.
    $availability_states_codes = array(
      // N = Not communicated.
      'N' => 1,
      // D = Available.
      'D' => 2,
      // C = Fully booked.
      'C' => 3,
    );

    // Handle "F" state (closed) like "C" (fully booked).
    $row->xml->availability = str_replace('F', 'C', $row->xml->availability);

    $availability_per_year = explode('##', $row->xml->availability);
    $all_availability = '';
    foreach ($availability_per_year as $availability_one_year) {
      list($year, $states) = explode(':', $availability_one_year);
      // Detect availability intervals in the source, for instance FFF, D and F
      // when the source string is NNNFFFDNFN.
      $states_matches = array();
      preg_match_all('/([^N])\1*/', $states, $states_matches, PREG_OFFSET_CAPTURE);
      // Convert intervals into the format used by the availability_calendar
      // field type, which takes as input availability states changes, like
      // this:
      // 2,2016-01-21,2016-01-23
      // 4,2016-02-12,2016-02-27
      // 3,2016-03-10,2016-04-24
      // 1,2016-06-09,2016-06-11.
      foreach ($states_matches[0] as $state_match) {
        $state = $state_match[0][0];
        $day1 = $state_match[1] + 1;
        $day2 = $day1 + strlen($state_match[0]) - 1;
        if (!isset($availability_states_codes[$state])) {
          // Invalid availability code.
          continue;
        }
        $all_availability .= sprintf("%d,%s,%s\n",
          $availability_states_codes[$state],
          date('Y-m-d', mktime(0, 0, 0, 1, $day1, (int) $year)),
          date('Y-m-d', mktime(0, 0, 0, 1, $day2, (int) $year))
        );
      }
    }
    $row->xml->availability = $all_availability;
  }

}
