<?php

include_once("localinc.php");

$page = new HTMLPageClass("test.php");

$page->add_css_link( "/phphtmllib/css/bluetheme.php" );

$nav = new TextNav( 760 );

//get the link to the widget's css file.

$nav->add("http://www.cnn.com", "Home", 80);
$nav->add("http://www.cnn.com", "Mailing List", 94);
$nav->add("http://www.cnn.com", "News Headlines", 120);
$nav->add("http://www.cnn.com", "Top Fifty", 98);
$nav->add("http://www.cnn.com", "The Fifty Monthly", 100);
$nav->add("http://www.cnn.com", "The Essentials", 94);
$nav->add("http://www.cnn.com", "Gear's Choice", 94);
$nav->add("http://www.cnn.com", "Contact Us", 94);

$page->add( $nav, html_br() );

$nav = new TextNav( 200 );

$nav->add("http://www.slashdot.org", "Slashdot", 100);
$nav->add("http://www.freshmeat.net", "Freshmeat", 100);

$page->add( $nav, html_br() );


print $page->render();
?>
