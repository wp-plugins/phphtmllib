<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the use of the 
 * InfoTable widget.
 *
 *
 * $Id: widget2.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
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
$page = new HTMLPageClass("phpHtmlLib Widgets - InfoTable",
						  XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}
$page->add_css_link(PHPHTMLLIB_RELPATH . "/css/defaulttheme.php" );


//create the InfoTable Object
//create the widget with a 
//title of "Some lame title"
//overall width of 300 pixels ( u can use % as well )
$infotable = new InfoTable("Some lame title", "300");

$infotable->add_row("this is a","test");
$infotable->add_row("this is a test", "&nbsp;");
$infotable->add_row("this is a","test");            
$infotable->add_row("this is a test", "&nbsp;");

$page->add( $infotable );

print $page->render();
?>
