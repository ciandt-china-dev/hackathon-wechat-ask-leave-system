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
  $items['ciandt_wechat_vacation_group_notification'] = array(
    'label' => t('Wechat notification to group'),
    'group' => t('Wechat notification'),
    'parameter' => array(
      'tag' => array(
        'type' => 'text',
        'label' => t('Notification tag'),
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

/**
 * Implementats hook_rules_event_info().
 */
function ciandt_wechat_vacation_rules_event_info() {
  return array(
    'vocation_approved' => array(
      'group' => 'ciandt_wechat_vacation',
      'label' => t('After a vocation approved'),
      'module' => 'ciandt_wechat_vacation',
    ),
  );
}
