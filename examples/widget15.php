<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the use of the 
 * TabControl Widget.  This widget gives you
 * the ability to build content for n # of tabs
 * and have the browser switch between the tabs
 * without a request to the server.
 *
 *
 * @author Culley Harrelson <culley@fastmail.fm> 
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version $Id: widget15.php 3145 2008-08-22 03:28:13Z mpwalsh8 $
 *
 */ 

/**
 * Include the phphtmllib libraries
 *
 */
include("includes.inc");
include_once(PHPHTMLLIB_ABSPATH ."/widgets/TabControlWidget.inc");

//create the page object
$page = new HTMLPageClass("phpHtmlLib Widgets - Tab Control Example",
						  XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}
//use the default theme
$page->add_css_link(PHPHTMLLIB_RELPATH . "/css/defaulttheme.php" );

$tab = new TabControlWidget(html_big('My Big Dumb Tab Control'), 'right');
$tab->add_tab(html_a("javascript:e=document.getElementById('secretitem'); e.style.display='block';void(0)", 'Click Me Tab'), false);
$tab->add_tab(html_a('#', 'Dumb Tab #2'), true);
$tab->add_tab(html_a('javascript:alert(\'he haw\');void(0)', 'Super really long tab for the verbose'), false);
$page->add($tab);
$div = html_div('', 'Surprise!');
$div->set_id('secretitem');
$div->set_style('display:none;');
$page->add(html_br(2), $div);


$title = html_h3('Click every tab before you leave');
//$title->set_tag_attribute('align', 'right');
//$title->set_style('padding: 5px;');
$tab2 = new TabControlWidget();
for ($i = 1; $i<6; $i++) {
    if (!array_key_exists('tab', $_GET) and $i == 1) {
        $tab2->add_tab(html_a("{$_SERVER['PHP_SELF']}?tab=$i", "Tab $i"), true);
    } else if (array_key_exists('tab', $_GET) and $_GET['tab'] == $i) {
        $tab2->add_tab(html_a("{$_SERVER['PHP_SELF']}?tab=$i", "Tab $i"), true);
    } else {
        $tab2->add_tab(html_a("{$_SERVER['PHP_SELF']}?tab=$i", "Tab $i"), false);
    }
}
$page->add($title, $tab2);

print $page->render();
?>
