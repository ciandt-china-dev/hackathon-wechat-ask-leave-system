<?php
/**
 * @file
 * Define functions for getting user list.
 */

/**
 * Function to get user list by department id.
 */
function _ciandt_wechat_vacation_get_user_lists() {
  $user_infos = variable_get('ciandt_wechat_user_list_all');
  return !empty($user_infos) ? $user_infos : array();
}

/**
 * Function to get user list by cron.
 */
function _ciandt_wechat_vacation_get_all_user($department = 1) {
  $we_obj = _ciandt_wechat_vacation_init_obj();
  $user_list = $we_obj->getUserList($department);
  $user_infos = [];
  if (!empty($user_list['userlist'])) {
    foreach ($user_list['userlist'] as $u) {
      $info = $we_obj->getUserInfo($u['userid']);
      $info['userid'] = strtolower($info['userid']);
      $user_infos[$info['userid']] = [
        'email' => $info['email'],
        'avatar' => substr($info['avatar'], 0, strrpos($info['avatar'], '/')) . '/100',
        'userid' => $info['userid'],
        'name' => $info['name'],
      ];
    }
    ksort($user_infos);
  }
  variable_set('ciandt_wechat_user_list_all', $user_infos);
  return $user_infos;
}
