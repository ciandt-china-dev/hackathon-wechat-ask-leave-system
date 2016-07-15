<?php
/**
 * @file
 * vocation_feature.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function vocation_feature_default_rules_configuration() {
  $items = array();
  $items['rules_notify_approver'] = entity_import('rules_config', '{ "rules_notify_approver" : {
      "LABEL" : "Notify Approver",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "ciandt_wechat_vocation" ],
      "ON" : { "node_insert--vocation" : { "bundle" : "vocation" } },
      "DO" : [
        { "ciandt_wechat_vocation_push_wechat_notification" : {
            "target" : "[node:field-approver]",
            "message" : "Hello [node:field-approver]!\\r\\n[node:field-name] Ask for a vocation."
          }
        }
      ]
    }
  }');
  return $items;
}
