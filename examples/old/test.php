<?php

include_once("localinc.php");

$page = new HTMLPageClass("First example script", XHTML_STRICT);
$page->set_text_debug( $_GET["debug"] );


$attributes = array("width"=>"600",
                    "border"=>1,
                    "cellspacing"=>0,
                    "cellpadding"=>0);
$table = new TABLEtag( $attributes );
$td = new TDtag( array("bgcolor"=>"#FFFFFF",
                       "colspan" => 4) );

$td->add( "Hello World" );

$table->add_row( $td );
$table->add_row( "test", "1", "2", "3");
$page->add( $table, html_br(),
             build_spacergif_imgtag(1,1));

print $page->render();
?>
