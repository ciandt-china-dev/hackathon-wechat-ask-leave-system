<?php
/**
 * @file
 * Rules hook functions.
 */

/**
 * Implements hook_rules_action_info().
 */
function ciandt_wechat_vacation_rules_action_info() {
  $items = array();

  $items['ciandt_wechat_vacation_push_wechat_notification'] = array(
    'label' => t('vacation Wechat notification to approver'),
    'group' => t('Wechat notification'),
    'parameter' => array(
      'target' => array(
        'type' => 'text',
        'label' => t('Target Notification Receiver'),
      ),
      'message' => array(
        'type' => 'text',
        'label' => t('Notification message'),
      ),
      'url' => array(
        'type' => 'text',
        'label' => t('URL'),
      ),
      'picurl' => array(
        'type' => 'text',
        'label' => t('Picture URL'),
      ),
    ),
  );
  return $items;
}
