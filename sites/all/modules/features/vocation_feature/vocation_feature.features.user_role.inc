<?php
/**
 * @file
 * vocation_feature.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function vocation_feature_user_default_roles() {
  $roles = array();

  // Exported role: Approver.
  $roles['Approver'] = array(
    'name' => 'Approver',
    'weight' => 2,
  );

  return $roles;
}
