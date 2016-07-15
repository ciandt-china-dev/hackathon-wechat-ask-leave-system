
<?php unset($form["actions"]["preview"]);?>
<?php hide($form["actions"]);?>
<input name="approve_user_id" type="hidden"/>
<?php print drupal_render_children($form);?>
<div>eeee</div>
<?php print render($form["actions"]);?>
<input type="time" class="time start-time form-text" value="09:00">
<input type="time" class="time end-time form-text" value="09:00">
