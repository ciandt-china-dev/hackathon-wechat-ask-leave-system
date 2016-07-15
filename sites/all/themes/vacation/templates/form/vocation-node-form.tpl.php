
<?php unset($form["actions"]["preview"]);?>
<?php hide($form["actions"]);?>
<input name="approve_user_id" type="hidden"/>
<?php print drupal_render_children($form);?>
<div>eeee</div>
<?php print render($form["actions"]);?>
