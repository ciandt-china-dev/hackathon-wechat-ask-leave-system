<?php
/**
 * @file
 * vocation_feature.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function vocation_feature_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create vocation content'.
  $permissions['create vocation content'] = array(
    'name' => 'create vocation content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
