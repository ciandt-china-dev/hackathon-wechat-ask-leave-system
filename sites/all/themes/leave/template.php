<?php

/**
 * Implements hook_theme().
 */
function leave_theme($existing, $type, $theme, $path) {
  return array(
    'vocation_node_form' => array(
      'render element' => 'form',
      'template' => 'vocation-node-form',
      // this will set to module/theme path by default:
      'path' => path_to_theme('leave') . '/templates/form',
    ),
  );
}
