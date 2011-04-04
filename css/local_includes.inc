<?php

//$doc_root = $_SERVER["DOCUMENT_ROOT"];
//  $_SERVER['DOCUMENT_ROOT'] isn't supported under IIS so the
//  initialization of phpHtmlLib needs to account for it.  Use
//  the include file shipped with the library to figure it out.

include_once("../phpHtmlLib.inc") ;

include_once(PHPHTMLLIB_ABSPATH . "/includes.inc");

//build the $css_container object
include_once(PHPHTMLLIB_ABSPATH . "/css/css_container.inc");

?>
