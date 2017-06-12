<?php

/**
 * Implements hook_theme().
 */
function vacation_theme($existing, $type, $theme, $path) {
  return array(
    'vocation_node_form' => array(
      'render element' => 'form',
      'template' => 'vocation-node-form',
      // this will set to module/theme path by default:
      'path' => path_to_theme('vacation') . '/templates/form',
    ),
  );
}


/**
 * Implements hook_css_alter().
 */
function vacation_css_alter(&$css) {
  // Remove defaults.css file.
  unset($css[drupal_get_path('module', 'date') . '/date_api/date.css']);
  unset($css[drupal_get_path('module', 'views') . '/css/views.css']);
}
