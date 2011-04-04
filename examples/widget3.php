<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the use of the 
 * TextCSSNav widget.
 *
 *
 * $Id: widget3.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
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
$page = new HTMLPageClass("phpHtmlLib Widgets - TextCSSNav",
						  XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}

//add the css
$page->add_css_link(PHPHTMLLIB_RELPATH . "/css/defaulttheme.php" );

//create the InfoTable Object
//create the widget and enable
//the auto highlighting of the selected Nav
$textcssnav = new TextCSSNav(TRUE);
$textcssnav->add($_SERVER["PHP_SELF"], "TextCSSNav", "Some Link dude");
$textcssnav->add($_SERVER["PHP_SELF"], "Some Link", "Some Link dude");
$textcssnav->add($_SERVER["PHP_SELF"], "Another", "Another link...Click me");
$textcssnav->add($_SERVER["PHP_SELF"], "And another", "Some Link dude");

$page->add( $textcssnav );

print $page->render();
?>
