
<?php //var_dump($form);?>

<?php 
	unset($form["actions"]["preview"]); 
	print drupal_render_children($form);
?>
<input type="time" class="time start-time form-text" value="09:00">
<input type="time" class="time end-time form-text" value="09:00">