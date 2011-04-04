<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Another example of how to build an
 * SVG Image with phpHtmlLib.
 * SVG = Scalable Vector Graphics. 
 * that phpHtmlLib provides.
 *
 *
 * $Id: example7.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage examples
 * @version 2.0.0
 *
 */ 

/**
 * Include the phphtmllib libraries
 */
include_once("includes.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/svg/SVGDocumentClass.inc");

//build the SVG Document object and set the
//width=400, height=200 attributes on the 'svg' root
//xml tag;
$svgdoc = new SVGDocumentClass(400,200);

//build and add a css class 
$style = svg_style("text/css", "/*this is a test*/");
$style->add( ".mylink {\n color: #000000;\n".
			 "text-decoration:underline;\n".
			 "font-size:20;\n }");
$svgdoc->add( $style );

//add a nice line around it all
$rect = svg_rect(0,0,400,200,"none","black",1);
$svgdoc->add( $rect );

//build the circle
$g = svg_g("stroke:black", "translate(190 80)");
$circle = svg_circle(0,0,50,"blue", "black", 2);

//add a neat mouseover to the circle
$circle->set_tag_attribute("onmouseover", "evt.target.setAttribute('style', 'stroke:red; stroke-width:2');");
$circle->set_tag_attribute("onmouseout", "evt.target.setAttribute('style', '');");
$g->add( $circle );
//add it to the image
$svgdoc->add( $g );

$g2 = svg_g("stroke:black", "translate(100 80)");
$text = svg_text(0,80,NULL,NULL, "SVG built by");
$text->set_style("font-size:20;");
$text->set_collapse();
$linktext = svg_text(114,80,NULL,"mylink","phpHtmlLib");

//$linktext->set_style("font-size:20;color:#FF0000;text-decoration:underline;");

$link = svg_a("http://phphtmllib.newsblob.com", $linktext);
$g2->add( $text, $link );
$svgdoc->add( $g2 );

print $svgdoc->render();
?>
