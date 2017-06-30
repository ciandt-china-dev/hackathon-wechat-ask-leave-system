<?php
/**
 * @file
 * Define functions for getting user list.
 */

/**
 * Function to get user list by department id.
 */
function _ciandt_wechat_vacation_get_user_lists($department = 1) {
  if ($cache = cache_get('ciandt_wechat_user_list_department_' . $department)) {
    return $cache->data;
  }
  $we_obj = _ciandt_wechat_vacation_init_obj();
  $user_list = $we_obj->getUserList($department);
  $user_infos = [];
  if (!empty($user_list['userlist'])) {
    foreach ($user_list['userlist'] as $u) {
      $info = $we_obj->getUserInfo($u['userid']);
      $info['userid'] = strtolower($info['userid']);
      $user_infos[$info['userid']] = [
        'email' => $info['email'],
        'avatar' => $info['avatar'] . '64',
        'userid' => $info['userid'],
        'name' => $info['name'],
      ];
    }
    ksort($user_infos);
  }
  cache_set('ciandt_wechat_user_list_department_' . $department, $user_infos);
  return $user_infos;
}
