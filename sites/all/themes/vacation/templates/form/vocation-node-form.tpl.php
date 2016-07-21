<?php unset($form["actions"]["preview"]);?>
<?php //hide($form["actions"]);?>

<?php $form["actions"]["submit"]["#value"] = t("Submit", array(), array('context' => 'vocation submit'));?>

<?php print render($form["field_type_of_leave"]);?>
<?php print render($form["field_leave_duration"]);?>
<div class="custom-leave-duration">
	<label><?php print t("Leave Duration", array(), array('context' => 'vacation request'));?> <span class="form-required" title="<?php print t("This field is required.");?>">*</span></label>
	<div class="date-field">
		<input type="date" class="date start-date form-text" value="<?php echo date('Y-m-d'); ?>">
		<input type="time" class="time start-time form-text" value="09:00">
	</div>
	<label><?php print t("to:");?> <span class="form-required" title="<?php print t("This field is required.");?>">*</span></label>
	<div class="date-field">
		<input type="date" class="date end-date form-text" value="<?php echo date('Y-m-d'); ?>">
		<input type="time" class="time end-time form-text" value="09:00">
	</div>
</div>
<?php print render($form["field_total_days"]);?>
<?php print render($form["field_comment"]);?>
<?php print render($form["field_approver"]);?>

<div class="approver-wrapper">
	<div class="selected-approver">
		<div class="remove-approver">-</div>
		<div class="selected-approver-field"></div>
	</div>
	<div class="add-approver"></div>
</div>
<?php print render($form["actions"]);?>

<input name="approve_user_id" type="hidden"/>
<?php print drupal_render_children($form);?>

