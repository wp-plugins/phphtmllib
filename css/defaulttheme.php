<?php

include_once("local_includes.inc");

require_once(PHPHTMLLIB_ABSPATH . "/widgets/includes.inc");

//cache this 
Header("Cache-Control: public");

print $css_container->render();
?>
