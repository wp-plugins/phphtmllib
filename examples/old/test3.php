<?php

include_once("localinc.php");

$page = new HTMLPageclass("test3.php");
$page->add_css_link("/phphtmllib/css/defaulttheme.php");

$table = new InfoTable("Some Title Here", "60%");

$table->add_row(_HTML_SPACE, "foo", _HTML_SPACE);
$table->add_row("multiple", "crap", "here");
$table->add_row("Even more", "&nbsp;", _HTML_SPACE);

$page->add( $table );

print $page->render();
?>
