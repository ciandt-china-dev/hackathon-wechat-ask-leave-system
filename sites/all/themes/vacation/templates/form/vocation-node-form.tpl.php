<?php $starttime = strtotime($form['field_leave_duration'][LANGUAGE_NONE][0]['#default_value']['value']);?>
<?php $endtime = strtotime($form['field_leave_duration'][LANGUAGE_NONE][0]['#default_value']['value2']);?>
<?php unset($form["actions"]["preview"]);?>
<?php unset($form["field_approver"]["und"]["add_more"]);?>
<?php unset($form["field_approver_vocation_status"]);?>
<?php
if (empty($form["nid"]['value'])) {
  unset($form["field_reject_reason"]);
}
?>

<?php unset($form["actions"]["preview"]);?>
<?php unset($form["field_approver"]["und"]["add_more"]);?>
<?php unset($form["field_approver_vocation_status"]);?>
<?php
if (empty($form["nid"]['value'])) {
  unset($form["field_reject_reason"]);
}
?>

<?php unset($form["actions"]["preview"]);?>
<?php //hide($form["actions"]);?>

<?php $form["actions"]["submit"]["#value"] = t("Submit", array(), array('context' => 'vocation submit'));?>

<?php print render($form["field_type_of_leave"]);?>
<?php print render($form["field_leave_duration"]);?>
<div class="custom-leave-duration">
	<label><?php print t("Leave Duration", array(), array('context' => 'vacation request'));?> <span class="form-required" title="<?php print t("This field is required.");?>">*</span></label>
	<div class="date-field">
		<input type="date" class="date start-date form-text" value="<?php echo date('Y-m-d',$starttime); ?>">
		<input type="time" class="time start-time form-text" value="<?php echo date('H:i',$starttime); ?>">
	</div>
	<label><?php print t("to:");?> <span class="form-required" title="<?php print t("This field is required.");?>">*</span></label>
	<div class="date-field">
		<input type="date" class="date end-date form-text" value="<?php echo date('Y-m-d',$endtime); ?>">
		<input type="time" class="time end-time form-text" value="<?php echo date('H:i',$endtime); ?>">
	</div>
</div>
<?php print render($form["field_total_days"]);?>
<?php print render($form["field_comment"]);?>
<?php print render($form["field_approver"]);?>
<div class="approver-wrapper">
	<div class="selected-approver">
            <ul class="selected-approver-field">
                <?php if(!empty($form['userinfo_userid'])):?>
                <li class="user-item" data-uid="<?php print $form['userinfo_userid']['#value'];?>">
                    <span class="image">
                        <img src="<?php print $form['userinfo_avatar']['#value'];?>">
                    </span>
                    <span class="name"><?php print $form['userinfo_name']['#value'];?></span>
                    <div class="remove-approver">-</div>
                </li>
                <?php endif;?>
            </ul>
	</div>
	<div class="add-approver"></div>
</div>
<?php print render($form["actions"]);?>
<input name="approve_user_id" type="hidden" value="<?php print $form['userinfo_userid']['#value'];?>" />
<?php print drupal_render_children($form);?>

