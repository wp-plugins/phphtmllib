<?php

include_once("localinc.php");

$page = new HTMLPageClass("test.php");

$options = array("bunz" => "hole",
                 "foo" => "bar",
                 "hello" => "world");
$form = new FORMtag(array("name"=> "testform",
                          "method" => "GET",
                          "action" => $PHP_SELF));


$form->add( form_select("test", $options, "foo") );

$textarea = form_textarea( "this is a long ass test" );
$textarea->set_tag_attributes( array("cols" => "40",
                                     "rows" => "20") );

$form->add( html_br(), $textarea );

$page->add( $form );

print $page->render();
?>
