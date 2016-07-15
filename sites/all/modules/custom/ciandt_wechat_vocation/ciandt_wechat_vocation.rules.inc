<?php
/**
 * @file
 * Rules hook functions.
 */

/**
 * Implements hook_rules_action_info().
 */
function ciandt_wechat_vocation_rules_action_info() {
  $items = array();

  $items['ciandt_wechat_vocation_push_wechat_notification'] = array(
    'label' => t('Vocation Wechat notification to approver'),
    'group' => t('Wechat notification'),
    'parameter' => array(
      'target' => array(
        'type' => 'text',
        'label' => t('Target Approver'),
      ),
      'message' => array(
        'type' => 'text',
        'label' => t('Notification message'),
      ),
    ),
  );
  return $items;
}
