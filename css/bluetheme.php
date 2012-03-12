<?php

include_once("local_includes.inc");

require_once(PHPHTMLLIB_ABSPATH . "/widgets/includes.inc");

//cache this 
header("Cache-Control: public");

//update all the background-color defs
$css_container->update_all_values("background-color",
                              "#999999", "#30669a");
$css_container->update_all_values("background-color",
                              "#eeeeee", "#dbe0ff");

//update all the color defs
$css_container->update_all_values("color",
                              "#777777", "#30669a");
$css_container->update_all_values("color",
                              "#828282", "#30669a");

//update all the border defs
$css_container->update_all_values("border",
                              "1px solid #999999", 
                              "1px solid #30669a");
$css_container->update_all_values("border-left",
                              "1px solid #999999", 
                              "1px solid #30669a");
$css_container->update_all_values("border-bottom",
                              "1px solid #999999", 
                              "1px solid #30669a");
$css_container->update_all_values("border-top",
                              "1px solid #999999", 
                              "1px solid #30669a");
$css_container->update_all_values("border-right",
                              "1px solid #999999", 
                              "1px solid #30669a");

$css_container->update_all_values("border-left",
                              "1px solid #828282", 
                              "1px solid #8e9dff");
$css_container->update_all_values("border-bottom",
                              "1px solid #828282", 
                              "1px solid #8e9dff");
$css_container->update_all_values("border-top",
                              "1px solid #828282", 
                              "1px solid #8e9dff");
$css_container->update_all_values("border-right",
                              "1px solid #828282", 
                              "1px solid #8e9dff");

$css_container->update_all_values("border",
                              "1px solid #a1a1a1", 
							  "1px solid #30669a");
$css_container->update_all_values("border-left",
							  "1px solid #a1a1a1", 
							  "1px solid #30669a");
$css_container->update_all_values("border-bottom",
							  "1px solid #a1a1a1", 
							  "1px solid #30669a");
$css_container->update_all_values("border-top",
							  "1px solid #a1a1a1", 
							  "1px solid #30669a");
$css_container->update_all_values("border-right",
							  "1px solid #a1a1a1", 
							  "1px solid #30669a");

print $css_container->render();
?>
