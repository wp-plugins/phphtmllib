<?php

include_once("localinc.php");

$page = new HTMLPageClass("test #4");

$form_attributes = array( "name" => "myform",
                          "method" => "GET",
                          "action" => $_SERVER["PHP_SELF"]);

$form = new FORMtag( $form_attributes );

$form->add( form_text("test", "testing",15,10) );
$form->add( form_button("test", "testing" ) );
$form->add( form_submit("test", "testing" ) );

$page->add( $form );


print $page->render();
?>
