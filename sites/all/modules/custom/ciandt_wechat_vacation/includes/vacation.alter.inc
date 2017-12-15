<?php
/**
 * @file
 * Define functions for altering.
 */

/**
 * Function to add CC user related form eletement.
 */
function _vocation_node_form_alter_cc_user_list_placement(&$form, &$form_state, $user) {
  // Get CC List.
  $cc_options = _ciandt_wechat_vacation_get_user_lists();
  // Get rid of current login user.
  if (isset($user->name) && isset($cc_options[$user->name])) {
    unset($cc_options[$user->name]);
  }
  $cc_output = '<div class="cc-popup"><div class="cc-popup-top"><span class="cc-close-btn">X</span></div>';
  $cc_output .= '<div class="cc-autocomplete"><input id="cc-autocomplete-search" class="form-text"/></div><ul class="initial-cc-list">';
  foreach ($cc_options as $key => $option) {
    $image = '<img src="' . $option['avatar'] . '"/>';
    $cc_output .= '<li class="user-item" data-uid="' . $option['userid'] . '"><span class="image">' . $image . '</span><span class="name">' . $option['name'] . '</span></li>';
  }
  $cc_output .= "</ul></div>";

  if ($cc_options) {
    $form['cc_user_list'] = array(
      '#title' => 'CC Users List',
      '#markup' => $cc_output,
    );
    $form_state['storage']['cc_user_list'] = $cc_options;
  }
}

/**
 * Function to add exist CC user info.
 */
function _vocation_node_form_alter_exist_cc_user_info(&$form, &$form_state, $node) {
  // Get CC user by entity_metadata_wrapper.
  $node_wrapper = entity_metadata_wrapper('node', $node);
  $cc_user_all = $node_wrapper->field_carbon_copy_user->value();
  $cc_user_info_arr = array();
  $cc_userinfo_userid = '';
  $cc_options = _ciandt_wechat_vacation_get_user_lists();
  if(count($cc_user_all) != 0) {
    foreach ($cc_user_all as $key => $ccer) {
      $field_target_id = $cc_user_all[$key]['target_id'];
      $user_info = user_load($field_target_id);
      if (array_key_exists($user_info->name, $cc_options)) {
        $user_infomation = $cc_options[$user_info->name];
        if (!empty($user_info)) {
          $cc_user_info_arr[$key]['user_info_user_id'] = $user_infomation['userid'];
          $cc_user_info_arr[$key]['user_info_avatar'] = $user_infomation['avatar'];
          $cc_user_info_arr[$key]['user_info_name'] = $user_infomation['name'];
          $cc_userinfo_userid .= $user_info->name . ',';
        }
      }
    };
  }
  $form['cc_userinfo_userid'] = array(
    '#type' => 'hidden',
    '#value' => rtrim($cc_userinfo_userid, ","),
  );
  $form['cc_user_info_arr'] = array(
    '#type' => 'hidden',
    '#value' => serialize($cc_user_info_arr),
  );
}

/**
 * Alter field carbon copy form_state value by post value from front end.
 */
function _vocation_node_form_submit_alter_field_carbon_copy(&$form, &$form_state, $approve_user_id_arr) {
  $cc_user_id_all = filter_input(INPUT_POST, 'cc_user_id');
  $cc_user_id_arr = !empty($cc_user_id_all) ? explode(',', $cc_user_id_all) : array();
  foreach ($cc_user_id_arr as $key => $cc_user_id) {
    $full_user_info = $form_state['storage']['cc_user_list'][$cc_user_id];

    $cc_user = user_load_by_mail($full_user_info['email']);

    if (!$cc_user) {
      $edit = array(
        'mail' => $full_user_info['email'],
        'name' => $full_user_info['userid'],
        'roles' => array(
          DRUPAL_AUTHENTICATED_RID => 'authenticated user',
        ),
      );
      // Check if the CC user is an approver.
      if (in_array($cc_user_id, $approve_user_id_arr)) {
        $edit['roles'] = array(
          DRUPAL_AUTHENTICATED_RID => 'authenticated user',
          DRUPAL_APPROVER_RID => 'Vacation Approver',
        );
      }
      $cc_user = user_save(NULL, $edit);
    }
    $form_state['values']['field_carbon_copy_user'][LANGUAGE_NONE][$key]['target_id'] = $cc_user->uid;
    $form_state['values']['field_carbon_copy_user'][LANGUAGE_NONE][$key]['target_type'] = 'user';
  }
}
