<?php

/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 *
 * @ingroup themeable
 */
global $user;
$edit = true;
foreach($field_approver_vocation_status as $key => $v){
  $target_id = get_approver_vocation_status('pending', 'vocation_status');
  if($v['target_id']!=$target_id){
      if(isset($approver_vocation_status)){
          $approver_vocation_status .= "<br/>".$field_approver[$key]['entity']->name."(".t($v['entity']->name).")";
      }else{
          $approver_vocation_status = $field_approver[$key]['entity']->name."(".t($v['entity']->name).")";
      } 
      if($v['entity']->name=='approved'){
          $edit = false;
      }
  }
}
if($field_vocation_status[0]['value']=='rejected' || $field_vocation_status[0]['value']=='pending'){
    $edit = true;
}
if (!empty($field_leave_duration[0]["value"]) && !empty($field_leave_duration[0]["value2"])):
$start_date =$field_leave_duration[0]["value"];
$end_date = $field_leave_duration[0]["value2"];
$start_date_timestamp = strtotime($field_leave_duration[0]["value"]);
$end_date_timestamp = strtotime($field_leave_duration[0]["value2"]);
$start_date_set = array(
  'month' => date('m', $start_date_timestamp),
  'day' => date('d', $start_date_timestamp),
  'week' => format_date($start_date_timestamp, 'custom', 'l'),
);
$end_date_set = array(
  'month' => date('m', $end_date_timestamp),
  'day' => date('d', $end_date_timestamp),
  'week' => format_date($end_date_timestamp, 'custom', 'l'),
);
$start_date_circle = t("!monthMonth!dayDay!week", array(
  '!month' => "<span class='month'>" . $start_date_set['month'] . "</span>",
  '!day' => "<span class='day'>" . $start_date_set['day'] . "</span>",
  '!week' => "<span class='week'>" . $start_date_set['week'] . "</span>",
));
$end_date_circle = t("!monthMonth!dayDay!week", array(
  '!month' => "<span class='month'>" . $end_date_set['month'] . "</span>",
  '!day' => "<span class='day'>" . $end_date_set['day'] . "</span>",
  '!week' => "<span class='week'>" . $end_date_set['week'] . "</span>",
));
else:
  $start_date_circle = $end_date_circle = $start_date = $end_date = '';
endif;
?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print $user_picture; ?>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if ($display_submitted): ?>
    <div class="submitted">
      <?php print $submitted; ?>
    </div>
  <?php endif; ?>

  <div class="content"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
    ?>
    <div class="detail-header">
      <h2><?php print $node->title; ?></h2>

      <div class="circle-item">
        <div class="circle">
          <?php print $start_date_circle;?>
        </div>
        <?php print t("Start Date");?>
      </div>
      <span>~</span>
      <div class="circle-item">
        <div class="circle">
          <?php print $end_date_circle;?>
        </div> 
        <?php print t("End Date");?>
      </div>
    </div>

    <div class="detail-content">
      <div class="item">
        <?php print t("Start:");?> 
        <?php print $start_date;?>
      </div>
      <div class="item">
        <?php print t("End:");?>
        <?php print $end_date;?>
      </div>
      <?php if(!empty($content['field_comment'])): ?>
        <div class="item">
          <?php print render($content['field_comment']);?>
        </div>
      <?php endif; ?>
      <?php if(!empty($content['field_approver'])): ?>
        <div class="item">
          <?php print render($content['field_approver']);?>
        </div>
      <?php endif; ?>
      <?php if(!empty($approver_vocation_status)): ?>
        <div class="item">
            <strong><?php print t("Approved:");?></strong><br/>
            <?php print $approver_vocation_status;?>
        </div>
      <?php endif; ?>
	  <?php if(!empty($content['field_vocation_status'])): ?>
        <div class="item">
          <?php print render($content['field_vocation_status']);?>
        </div>
      <?php endif; ?>
      <?php if(!empty($content['field_reject_reason'])): ?>
        <div class="item">
          <?php print render($content['field_reject_reason']);?>
        </div>
      <?php endif; ?>
        <?php if($edit && $user->uid==$node->uid):?>
          <div class="item">
            <a  class="form-submit form-submit-edit" href="/vacation/<?php print $node->nid; ?>/edit">编辑</a>
          </div>
        <?php endif;?>
    </div>
  </div>

  <?php print render($content['links']); ?>

  <?php print render($content['comments']); ?>

</div>
