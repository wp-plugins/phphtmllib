<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the use of the 
 * FooterNav widget.
 *
 *
 * $Id: widget5.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
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
$page = new HTMLPageClass("phpHtmlLib Widgets - FooterNav Example",
						  XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}

//add the css
$page->add_css_link(PHPHTMLLIB_RELPATH . "/css/defaulttheme.php" );

//Build the Footer Widget object
$footer = new FooterNav("PHPHtmlLib");

//Set the copyright flag, to automatically show
//a copyright string under the links
$footer->set_copyright_flag( TRUE );

//set the email address for the webmaster
//this will automatically build a clickable
//mailto link for that email address
$footer->set_webmaster_email("waboring@newsblob.com");

//now build a few links that the user can click on
//for a common footer navigational object.
$footer->add("/", "Home");
$footer->add("index.php", "Examples");
$footer->add($_SERVER["PHP_SELF"]."?debug=1", "Debug");

$page->add( $footer );

print $page->render();
?>
