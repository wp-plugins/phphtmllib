<?php

include_once("local_includes.inc");

require_once(PHPHTMLLIB_ABSPATH . "/widgets/includes.inc");

//cache this 
Header("Cache-Control: public");


//update all the background-color defs
$css_container->update_all_values("background-color",
                              "#999999", "#d31919");
$css_container->update_all_values("background-color",
                              "#eeeeee", "#ffa8a8");

//update all the color defs
$css_container->update_all_values("color",
                              "#777777", "#d31919");
$css_container->update_all_values("color",
                              "#828282", "#d31919");

//update all the border defs
$css_container->update_all_values("border",
                              "1px solid #999999", 
                              "1px solid #d31919");
$css_container->update_all_values("border-left",
                              "1px solid #999999", 
                              "1px solid #d31919");
$css_container->update_all_values("border-bottom",
                              "1px solid #999999", 
                              "1px solid #d31919");
$css_container->update_all_values("border-top",
                              "1px solid #999999", 
                              "1px solid #d31919");
$css_container->update_all_values("border-right",
                              "1px solid #999999", 
                              "1px solid #d31919");

$css_container->update_all_values("border-left",
                              "1px solid #828282", 
                              "1px solid #700000");
$css_container->update_all_values("border-bottom",
                              "1px solid #828282", 
                              "1px solid #700000");
$css_container->update_all_values("border-top",
                              "1px solid #828282", 
                              "1px solid #700000");
$css_container->update_all_values("border-right",
                              "1px solid #828282", 
                              "1px solid #700000");

$css_container->update_all_values("border",
                              "1px solid #a1a1a1", 
							  "1px solid #d31919");
$css_container->update_all_values("border-left",
							  "1px solid #a1a1a1", 
							  "1px solid #d31919");
$css_container->update_all_values("border-bottom",
							  "1px solid #a1a1a1", 
							  "1px solid #d31919");
$css_container->update_all_values("border-top",
							  "1px solid #a1a1a1", 
							  "1px solid #d31919");
$css_container->update_all_values("border-right",
							  "1px solid #a1a1a1", 
							  "1px solid #d31919");

print $css_container->render();
?>
