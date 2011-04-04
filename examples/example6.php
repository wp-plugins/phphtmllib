<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Another example of how to build an
 * XML Document with the WML support 
 * that phpHtmlLib provides.
 *
 *
 * $Id: example6.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage examples
 * @version 2.0.0
 *
 */ 

/**
 * Include the phphtmllib libraries
 */
include_once("includes.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/wml/WMLDocumentClass.inc");

//build the wml document object.
$wmldoc = new WMLDocumentClass;

//turn off the rendering of the http Content-type
//so we can see the output in a non WAP browser.
$wmldoc->show_http_header(FALSE);

$card1 = wml_card("Testing", "card1");
$card1->add(wml_do("accept", wml_go("#card2")));

$options = array("Testing1" => "test1",
				 "Testing2" => "test2",
				 "Foo" => "bar");
$card1->add( html_p( form_select("name", $options) ) );
$wmldoc->add( $card1 );


$card2 = wml_card("Foo", "card2");
$card2->add( html_p( "This is card #2!"));
$wmldoc->add( $card2 );

//this will render the entire page
print $wmldoc->render();
?>
