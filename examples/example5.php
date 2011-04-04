<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Another example of how to build an
 * XML Document with the XML support 
 * that phpHtmlLib provides.
 *
 *
 * $Id: example5.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
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
include_once(PHPHTMLLIB_ABSPATH . "/widgets/xml/XMLDocumentClass.inc");

//build the xml document object with a 
//root xml tag of <example5>, and a <!DOCTYPE> 
//link attribute of "some doctype link"
$xmldoc = new XMLDocumentClass("example5", "http://foo.com/DTDS/mail.dtd");

//make sure we have the XMLDocumentClass automatically
//output the correct http Content-Type value
$xmldoc->show_http_header();

//add some tags to the root element
$xmldoc->add( xml_tag("testing", array(), "foo",
					  xml_tag("blah", array("value" => 1)) ) );

//build an array that represents
//xml tags and their values.
$arr = array("Foo" => array("bar" => "bleh",
							"bar" => array("testing" => "php")));
//add those tags from the array
$xmldoc->add( array_to_xml_tree( $arr ) );

//this will render the entire page
print $xmldoc->render();
?>
