
<?php //var_dump($form);?>

<?php 
	unset($form["actions"]["preview"]); 
	print drupal_render_children($form);

?>
<input name="approve_user_id" type="hidden"/>