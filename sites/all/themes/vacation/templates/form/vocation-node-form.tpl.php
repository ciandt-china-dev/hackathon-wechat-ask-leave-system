<?php unset($form["actions"]["preview"]);?>
<?php hide($form["actions"]);?>
<?php $form["actions"]["submit"]["#value"] = t("Submit", array(), array('context' => 'vocation submit'));?>
<input name="approve_user_id" type="hidden"/>
<?php print drupal_render_children($form);?>
<div class="approver-wrapper">
	<div class="selected-approver">
		<div class="remove-approver">-</div>
		<div class="selected-approver-field"></div>
	</div>
	<div class="add-approver">+</div>
</div>
<?php print render($form["actions"]);?>
<input type="time" class="time start-time form-text" value="09:00">
<input type="time" class="time end-time form-text" value="09:00">
