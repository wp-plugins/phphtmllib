<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the use of the 
 * VerticalCSSNavTable widget.
 *
 *
 * $Id: widget4.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version 2.0
 *
 */ 

/**
 * Include the phphtmllib libraries
 *
 */
include_once("includes.inc");


//create the page object
$page = new HTMLPageClass("phpHtmlLib Widgets - VerticalCSSNavTable", 
						  XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}

//add the css
$page->add_css_link(PHPHTMLLIB_RELPATH . "/css/defaulttheme.php");

//create the VerticalCSSNavTable Object
//create the widget with
//Title of 'VerticalCSSNavTable' and
//subtitle of 'Widget'
//overall width of 400 pixels ( u can use % as well )
$cssnavtable = new VerticalCSSNavTable("VerticalCSSNavTable", "Widget", 400);
$cssnavtable->add("#", "Some Link", "This is title text");
$cssnavtable->add("#", "Another");
$cssnavtable->add("#", "Another", "This is title text");

$page->add( $cssnavtable );

print $page->render();
?>
