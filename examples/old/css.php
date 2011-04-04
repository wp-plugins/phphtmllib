<?php

include_once( "localinc.php" );

$page = new HTMLPageClass("lame");
$theme = $_GET["theme"];
if ($theme == "") {
	$page->add_css_link( "/css/defaulttheme.php");
} else if ($theme == "blue") {
	$page->add_css_link( "/css/bluetheme.php");
} else if ($theme == "red") {
	$page->add_css_link( "/css/redtheme.php");
}

if ($_GET["debug"]) {
	$page->set_text_debug(TRUE);
	
}

$base_link = $_SERVER["PHP_SELF"];

$info = new InfoTable("test", "300");
$info->add_row("test", "foo");
$info->add_row("test", "foo");
$info->add_row("test", "foo");

$page->add( $info, html_br(2) );

$textcss = new TextCSSNav;
$textcss->add($base_link, "Home", "home dude");
$textcss->add($base_link, "something", 
			  "This is like..another link");

$page->add( $textcss, html_br(2) );

$navtable = new NavTable("Something", "more here", 300);
$navtable->add($base_link, "Home");
$navtable->add($base_link, "Click ME!");
$navtable->add_blank();
$navtable->add($base_link, "Click ME!");

$page->add( $navtable, html_br(2) );

$info2 = new InfoTable("Some lame table", 400);
$info2->add_column_header("foo", 200);
$info2->add_column_header("bar", 100);
$info2->add_column_header("blah blah", 100);

$info2->add_row("123", "456", 789);
$info2->add_row("hrmm", "what?", 0123);
$info2->add_row("test", "ing", 123);

$page->add( $info2, html_br(2) );


$nav = new VerticalCSSNavTable("Some title", "Some lame subtitle", 300);
$nav->add($base_link, "Home","Go home dude!");
$nav->add($base_link, "Something","Go Somewhere else");
$nav->add($base_link, "Home Depot","Head to get some stuff!");

$page->add( $nav, html_br(2) );


$footernav = new FooterNav("Qualys");
$footernav->set_legalnotice_url("foo.html");
$footernav->set_privacypolicy_url("foo.html");
$footernav->set_webmaster_email("you@suck.com");

$footernav->add($base_link, "Home");
$footernav->add($base_link, "Login");
if ($theme) {
	$link .= $base_link."?theme=".$theme."&debug=1";
} else {
	$link .= $base_link."?debug=1";
}
$footernav->add($link, "DEBUG THIS PAGE");


$page->push( $footernav );

print $page->render();
?>
