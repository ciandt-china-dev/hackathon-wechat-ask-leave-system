<?php $starttime = strtotime($form['field_leave_duration'][LANGUAGE_NONE][0]['#default_value']['value']);?>
<?php $endtime = strtotime($form['field_leave_duration'][LANGUAGE_NONE][0]['#default_value']['value2']);?>
<?php unset($form["actions"]["preview"]);?>
<?php unset($form["field_approver"][LANGUAGE_NONE]["add_more"]);?>
<?php unset($form["field_carbon_copy_user"][LANGUAGE_NONE]["add_more"]);?>
<?php unset($form["field_approver_vocation_status"]);?>
<?php
if (empty($form["nid"]['value'])) {
  unset($form["field_reject_reason"]);
}
?>
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
			<?php if(!empty($form['user_info_arr']['#value'])):?>
				<?php foreach (unserialize($form['user_info_arr']['#value']) as $user_info) {?>
					<li class="user-item" data-uid="<?php print $user_info['user_info_user_id'];?>">
						<span class="image">
							<img src="<?php print $user_info['user_info_avatar'];?>">
						</span>
						<span class="name"><?php print $user_info['user_info_name'];?></span>
						<div class="remove-approver">-</div>
					</li>
				<?php };?>
			<?php endif;?>
		</ul>
	</div>
	<div class="add-approver"></div>
</div>
<?php // Add CC user element. ?>
<?php print render($form["field_carbon_copy_user"]);?>
<div class="cc-wrapper">
	<div class="selected-cc">
		<ul class="selected-cc-field">
			<?php if(!empty($form['cc_user_info_arr']['#value'])): ?>
				<?php foreach (unserialize($form['cc_user_info_arr']['#value']) as $cc_user_info): ?>
					<li class="user-item" data-uid="<?php print $cc_user_info['user_info_user_id'];?>">
						<span class="image">
							<img src="<?php print $cc_user_info['user_info_avatar'];?>">
						</span>
						<span class="name"><?php print $cc_user_info['user_info_name'];?></span>
						<div class="remove-cc">-</div>
					</li>
				<?php endforeach;?>
			<?php endif;?>
		</ul>
	</div>
	<div class="add-cc"></div>
</div>
<?php print render($form["actions"]);?>
<input name="approve_user_id" type="hidden" value="<?php if(!empty($form['userinfo_userid'])){print $form['userinfo_userid']['#value'];}?>" />
<input name="cc_user_id" type="hidden" value="<?php if(!empty($form['cc_userinfo_userid'])){print $form['cc_userinfo_userid']['#value'];}?>" />
<?php print drupal_render_children($form);?>

