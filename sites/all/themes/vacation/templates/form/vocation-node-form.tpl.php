
<?php //var_dump($form);?>

<?php 
	unset($form["actions"]["preview"]); 
	print "<h1>" . t("Leave Application") . "</h1>";
	print drupal_render_children($form);

?>
