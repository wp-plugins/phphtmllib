<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the use of the 
 * RoundTitleTable widget.
 *
 *
 * $Id: widget11.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version 2.4.0
 *
 */ 

/**
 * Include the phphtmllib libraries
 *
 */
include_once("includes.inc");


//create the page object
$page = new HTMLPageClass("phpHtmlLib Widgets - RoundTable", 
						  HTML);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}

//add the css link to the default theme which will
//automatically generate the css classes used 
//by the Navtable widget, as well as the other widgets.
$page->add_css_link(PHPHTMLLIB_RELPATH . "/css/defaulttheme.php" );
$page->add_css_link(PHPHTMLLIB_RELPATH . "/css/fonts.css" );

//create the RoundTitleTable Object
//create the widget with a 
//title of "Some lame title"
//overall width of 300 pixels ( u can use % as well )
$dialog = new StandardDialogWidget("Some title", "300", "center");
//$dialog->add_button();

$dialog->add_block("TESTING","This is a message");
$dialog->add("This is a message");


$page->add( $dialog );


//this will render the entire page
//with the content you have added
//wrapped inside all the required
//elements for a complete HTML/XHTML page.
//NOTE: all the objects in phphtmllib have
//      the render() method.  So you can call
//      render on any phphtmlib object.
print $page->render();
?>
