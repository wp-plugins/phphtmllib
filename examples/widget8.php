<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the use of the 
 * ActiveTab Widget.  This widget gives you
 * the ability to build content for n # of tabs
 * and have the browser switch between the tabs
 * without a request to the server.
 *
 * $Id: widget8.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
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
include("includes.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/ActiveTab.inc");

//create the page object
$page = new HTMLPageClass("phpHtmlLib Widgets - ActiveTab Example",
						  XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}
//use the default theme
$page->add_css_link(PHPHTMLLIB_RELPATH . "/css/defaulttheme.php" );


//build the active tab widget
//with a width of 500 pixels wide
//and a height (MUST BE SET) of 200px tall.
$tab = new ActiveTab(500, "300px");

//build a NavTable widget
$navtable = new NavTable("NavTable", "Widget", "200");
$navtable->add("#", "Some Link", "This is title text");
$navtable->add("#", "Another");
$navtable->add_blank();
$navtable->add("#", "Some Link", "This is title text");
$navtable->add("#", "Another");

//build a VerticalCSSNavTable widget
$cssnavtable = new VerticalCSSNavTable("VerticalCSSNavTable", "Widget", "300");
$cssnavtable->add("#", "Some Link", "This is title text");
$cssnavtable->add("#", "Another");
$cssnavtable->add("#", "Another", "This is title text");

//build a form for one of the tabs
$formname = "fooform";
$form = html_form($formname, "#");
$form->add( form_active_checkbox("foo", "some foo text", "ass"),html_br() );
$form->add( form_active_checkbox("bar", "some bar text", "bar"),html_br() );
$form->add( form_active_checkbox("blah", "some blah text", "blah"), html_br() );
$form->add( html_br(2) );

$form->add( form_active_radio("assradio", array("foo"=>1, "bar"=>2), 2, FALSE ) );
$form->add( html_br(2),
			form_active_radio("assradio2", array("foo"=>1, "bar"=>2, "testing"=> 3), 2 ));


//now add the tabs and their content.
$tab->add_tab("Foo Tab", $navtable);
$tab->add_tab("Bar", $form);
$tab->add_tab("Hemna", $cssnavtable, TRUE);
$tab->add_tab("Walt", "Walt tab content");

//add the tab to the page and render everything.
$page->add( $tab );
print $page->render();
?>
