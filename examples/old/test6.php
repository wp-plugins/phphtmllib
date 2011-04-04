<?php

include_once("localinc.php");

$page = new HTMLPageClass("test.php");
$page->set_body_attributes(array("bgcolor"=> "#ffffff"));

$nav_table = new NavTable("Test title", "test subtitle", "30%");

//get the link to the widget's css file.
$page->add_css_link( "/phphtmllib/css/defaulttheme.php" );

$nav_table->add("http://www.cnn.com", "Go to CNN");
$nav_table->add_blank();
$nav_table->add("http://www.yahoo.com", "Go to Yahoo dude");
$nav_table->add_blank();
$nav_table->add_text("Some lame text here");


$page->add( $nav_table );

print $page->render();
?>
