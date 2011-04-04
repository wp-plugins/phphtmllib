<?php
/**
 * This file holds helper functions
 * for things related to SVG Tags
 * (Scalable Vector Graphics)
 *
 * $Id: svg_utils.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @link http://phphtmllib.newsblob.com
 */


/**
 * This function is used to build an
 * SVG <a> tag
 *
 * @param string - the 'xlink:href' attribute
 * @param mixed - any N number of params for
 *                content for the tag
 * @return Asvgtag object
 * @link http://www.w3.org/TR/SVG/linking.html#AElement
 */
function svg_a($xlinkhref) {
	$tag = new Asvgtag( array("xlink:href" => $xlinkhref));
	$num_args = func_num_args();
	for ($i=1;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
	return $tag;
}

/**
 * This function is used to build an
 * SVG <animate> tag
 *
 * @param string - the 'from' attribute
 * @param string - the 'to' attribute
 * @param string - the 'duration' attribute
 * @param string - the 'attributeName' attribute
 * @param string - the 'attributeType' attribute
 * @param string - the 'repeatCount' attribute
 * @param string - the 'fill' attribute
 * @return ANIMATEsvgtag object
 * @link http://www.w3.org/TR/SVG/animate.html#AnimateElement
 */
function svg_animate($from, $to, $duration, $attributename, 
					 $attributetype, $repeatcount=NULL, $fill=NULL) {
	$tag = new ANIMATEsvgtag( array("from" => $from, "to" => $to,
									"duration" => $duration,
									"attributeName" => $attributename,
									"attributeType" => $attributetype));
	if ($repeatcount) {
		$tag->set_tag_attribute("repeatCount", $repeatcount);
	}
	if ($fill) {
		$tag->set_tag_attribute("fill", $fill);
	}

	return $tag;
}

/**
 * This function is used to build an
 * SVG <circle> tag and its common 
 * attributes
 *
 * @param int - the 'cx' attribute. The x-axis 
 *              coordinate of the center of the circle
 * @param int - the 'cy' attribute. The y-axis 
 *              coordinate of the center of the circle 
 * @param string - the 'r' (radius) attribute
 * @param string - the 'fill' attribute
 * @param string - the 'stroke' attribute
 * @param string - the 'stroke-width' attribute
 * @param string - the 'style' attribyte
 * @return CIRCLEsvgtag object
 * @link http://www.w3.org/TR/SVG/shapes.html
 */
function svg_circle($cx, $cy, $radius, $fill="none",
					$stroke=NULL, $strokewidth=NULL, $style=NULL) {
	$tag = new CIRCLEsvgtag( array("cx" => $cx, "cy" => $cy,
								   "r" => $radius));
	if ($fill) {
		$tag->set_tag_attribute("fill", $fill);
	}
	if ($stroke) {
		$tag->set_tag_attribute("stroke", $stroke);
	}
	if ($strokewidth) {
		$tag->set_tag_attribute("stroke-width", $strokewidth);
	}
	if ($style) {
		$tag->set_style($style);
	}
	return $tag;
}

/**
 * This function is used for building an
 * SVG <defs> tag
 *
 * @param mixed - any N number of params for
 *                content for the tag
 * @return DESCsvgtag object
 */
function svg_defs() {
	$tag = new DEFSsvgtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
	return $tag;
}

/**
 * This function is used for building an
 * SVG <desc> tag
 *
 * @param mixed - any N number of params for
 *                content for the tag
 * @return DESCsvgtag object
 */
function svg_desc() {
	$tag = new DESCsvgtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
	return $tag;
}

/**
 * This function is used to build an
 * SVG <ellipse> tag and its common 
 * attributes
 *
 * @param int - the 'cx' attribute. The x-axis 
 *              coordinate of the center of the circle
 * @param int - the 'cy' attribute. The y-axis 
 *              coordinate of the center of the circle 
 * @param int - the 'rx' attribute. The x-axis radius of 
 *              the ellipse. 
 * @param int - the 'ry' attribute. The y-axis radius of 
 *              the ellipse. 
 * @param string - the 'fill' attribute
 * @param string - the 'stroke' attribute
 * @param string - the 'stroke-width' attribute
 * @param string - the 'style' attribyte
 * @return ELLIPSEsvgtag object
 * @link http://www.w3.org/TR/SVG/shapes.html
 */
function svg_ellipse($cx, $cy, $rx, $ry, $fill="none",
					$stroke=NULL, $strokewidth, $style=NULL) {
	$tag = new ELLIPSEsvgtag( array("cx" => $cx, "cy" => $cy,
									"rx" => $rx, "ry" => $ry));
	if ($fill) {
		$tag->set_tag_attribute("fill", $fill);
	}
	if ($stroke) {
		$tag->set_tag_attribute("stroke", $stroke);
	}
	if ($strokewidth) {
		$tag->set_tag_attribute("stroke-width", $strokewidth);
	}
	if ($style) {
		$tag->set_style($style);
	}
	return $tag;
}

/**
 * this function builds an SVG
 * <font> tag
 *
 * @param string - the required 'horiz-adv-x' attribute
 * @return FONTsvgtag object
 */
function svg_font( $horizadvx ) {
	$tag = new FONTsvgtag( array("horiz-adv-x" => 
								 $horizadvx));
    $num_args = func_num_args();
	for ($i=1;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
	return $tag;
}

/**
 * This function builds an SVG
 * <g> tag
 *
 * @param string - the 'style' attribute
 * @param string - the 'transform' attribute
 * @return Gsvgtag object
 */
function svg_g($style=NULL, $transform=NULL) {
	$tag = new Gsvgtag;
	if ($style) {
		$tag->set_style($style);
	}

	if ($transform) {
		$tag->set_transform( $transform );
	}

	return $tag;
}


/**
 * This function is used for building an 
 * SVG <line> tag 
 *
 * @param int - the 'x1' attribute
 * @param int - the 'y1' attribute
 * @param int - the 'x2' attribute
 * @param int - the 'y2' attribute
 * @param string - the 'stroke' attribute
 * @param string - the 'stroke-width' attribute
 * @param string - the 'style' attribute
 * @return LINEsvgtag object
 * @link http://www.w3.org/TR/SVG/shapes.html
 */
function svg_line($x1, $y1, $x2, $y2, $stroke=NULL,
					  $strokewidth, $style=NULL) {
	$tag = new LINEsvgtag(array("x1" => $x1, "y1" => $y1,
								"x2" => $x2, "y2" => $y2));
	if ($stroke) {
		$tag->set_tag_attribute("stroke", $stroke);
	}
	if ($strokewidth) {
		$tag->set_tag_attribute("stroke-width", $strokewidth);
	}
	if ($style) {
		$tag->set_style( $style );
	}

	return $tag;
}

/**
 * This function is used for building an 
 * SVG <marker> tag
 *
 * @param string - the 'refX' attribute
 * @param string - the 'refY' attribute
 * @param string - the 'markerUnits' attribute
 * @param string - the 'markerWidth' attribute
 * @param string - the 'markerHeight' attribute
 * @param string - the 'orient' attribute
 * @return MARKERsvgtag object
 * @link http://www.w3.org/TR/SVG/painting.html#MarkerElement
 */
function svg_marker($refx, $refY, $markerunits=NULL,
					$markerwidth=NULL, $markerheight=NULL,
					$orient=NULL) {
	$tag = new MARKERsvgtag( array("refx" => $refx,
								   "refy" => $refy));

	if ($markerunits) {
		$this->set_tag_attribute("markerUnits", $markerunits );
	}
	if ($markerwidth) {
		$this->set_tag_attribute("markerWidth", $markerwidth );
	}
	if ($markerheight) {
		$this->set_tag_attribute("markerHeight", $markerheight );
	}
	if ($orient) {
		$this->set_tag_attribute("orient", $orient );
	}
	
	return $tag;
}

/**
 * This function is used for building an 
 * SVG <polygon> tag 
 *
 * @param int - the 'points' attribute
 * @param string - the 'fill' attribute
 * @param string - the 'stroke' attribute
 * @param string - the 'stroke-width' attribute
 * @param string - the 'style' attribute
 * @return POLYGONsvgtag object
 * @link http://www.w3.org/TR/SVG/shapes.html
 */
function svg_polygon($points, $fill="none", $stroke=NULL,
					 $strokewidth, $style=NULL) {
	$tag = new POLYGONsvgtag;

	if ($fill) {
		$tag->set_tag_attribute("fill", $fill);
	}
	if ($stroke) {
		$tag->set_tag_attribute("stroke", $stroke);
	}
	if ($strokewidth) {
		$tag->set_tag_attribute("stroke-width", $strokewidth);
	}
	if ($style) {
		$tag->set_style( $style );
	}

	//do this instead of the constructor
	//because the output is easier to read.
	$tag->set_tag_attribute("points", $points);

	return $tag;
}

/**
 * This function is used for building an 
 * SVG <polyline> tag 
 *
 * @param int - the 'points' attribute
 * @param string - the 'fill' attribute
 * @param string - the 'stroke' attribute
 * @param string - the 'stroke-width' attribute
 * @param string - the 'style' attribute
 * @return POLYLINEsvgtag object
 * @link http://www.w3.org/TR/SVG/shapes.html
 */
function svg_polyline($points, $fill="none", $stroke=NULL,
					  $strokewidth, $style=NULL) {
	$tag = new POLYLINEsvgtag;

	if ($fill) {
		$tag->set_tag_attribute("fill", $fill);
	}
	if ($stroke) {
		$tag->set_tag_attribute("stroke", $stroke);
	}
	if ($strokewidth) {
		$tag->set_tag_attribute("stroke-width", $strokewidth);
	}
	if ($style) {
		$tag->set_style( $style );
	}

	//do this instead of the constructor
	//because the output is easier to read.
	$tag->set_tag_attribute("points", $points);

	return $tag;
}


/**
 * This function creates a <script>
 * tag and wraps the javascript in the 
 * appropriate  <![CDATA[ JAVASCRIPT ]]>
 * that is required for svg.
 *
 * @param string the 'type' attribute
 * @param mixed - any N number of params for
 *                content for the tag
 * @return SCRIPTsvgtag object
 */
function svg_script( $type="text/javascript" ) {
	$tag = new SCRIPTsvgtag(array("type" => $type));
	$num_args = func_num_args();
	for ($i=1;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
	return $tag;
}

/**
 * This function creates a <script>
 * tag and wraps the javascript in the 
 * appropriate  <![CDATA[ JAVASCRIPT ]]>
 * that is required for svg.
 *
 * @param string the 'type' attribute
 * @param mixed - any N number of params for
 *                content for the tag
 * @return SCRIPTsvgtag object
 */
function svg_style( $type="text/css" ) {
	$tag = new STYLEsvgtag(array("type" => $type));
	$num_args = func_num_args();
	for ($i=1;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
	return $tag;
}


/**
 * This function is used to build an
 * SVG <rect> tag and its common 
 * attributes
 *
 * @param int - the 'x' attribute
 * @param int - the 'y' attribute
 * @param string - the 'width' attribute
 * @param string - the 'height' attribute
 * @param string - the 'fill' attribute
 * @param string - the 'stroke' attribute
 * @param string - the 'stroke-width' attribyte 
 * @param string - the 'style' attribyte
 * @return RECTsvgtag object
 * @link http://www.w3.org/TR/SVG/shapes.html
 */
function svg_rect($x, $y, $width, $height, $fill=NULL,
				  $stroke=NULL, $strokewidth=NULL, $style=NULL) {
	$tag = new RECTsvgtag( array("x" => $x, "y" => $y,
								 "width" => $width,
								 "height" => $height));
	if ($fill) {
		$tag->set_tag_attribute("fill", $fill);
	}
	if ($stroke) {
		$tag->set_tag_attribute("stroke", $stroke);
	}
	if ($strokewidth) {
		$tag->set_tag_attribute("stroke-width", $strokewidth);
	}

	if ($style) {
		$tag->set_style($style);
	}
	return $tag;
}

/**
 * This function is used to build an
 * SVG <text> tag
 *
 * @param int - the 'x' attribute
 * @param int - the 'y' attribute
 * @param string - the 'rotate' attribute
 * @param style - the 'class' attribute
 * @param mixed - any N number of params for
 *                content for the tag
 * @return TEXTsvgtag object.
 * @link http://www.w3.org/TR/SVG/text.html
 */
function svg_text($x, $y, $rotate=NULL, $class=NULL) {
	$tag = new TEXTsvgtag( array("x" => $x, "y" => $y));
	if ($rotate) {
		$tag->set_tag_attribute( "rotate", $rotate );
	}
	if ($class) {
		$tag->set_class( $class );
	}
	$num_args = func_num_args();
	for ($i=4;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
	return $tag;
}

/**
 * This function is used to build an
 * SVG <textpath> tag.
 *
 * @param string - the 'xlink:href' attribute
 * @param string - the 'class' attribute
 * @param mixed - any N number of params for
 *                content for the tag
 * @return TEXTPATHsvgtag object.
 * @link http://www.w3.org/TR/SVG/text.html#TextPathElement
 */
function svg_textpath($xlinkhref, $class=NULL) {
	$tag = new TEXTPATHsvgtag( array("xlink:href" => $xlinkhref));
	if ($class) {
		$tag->set_class( $class );
	}
	$num_args = func_num_args();
	for ($i=2;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
	return $tag;
}

/**
 * This function is used to build an
 * SVG <tref> tag
 *
 * @param string - the 'xlink:href' required attribute
 * @param string - the 'class' attribute
 * @param mixed - any N number of params for
 *                content for the tag
 * @return TREFsvgtag object.
 * @link http://www.w3.org/TR/SVG/text.html
 */
function svg_tref($xlinkhref, $class=NULL) {
	$tag = new TREFsvgtag( array("xlink:href" => $xlinkhref));
	if ($class) {
		$tag->set_class( $class );
	}
	$num_args = func_num_args();
	for ($i=2;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
	return $tag;
}

/**
 * This function is used to build an
 * SVG <tref> tag.
 *
 * @param string - the 'x' attribute
 * @param string - the 'y' attribute
 * @param string - the 'class' attribute
 * @return TSPANsvgtag object.
 * @link http://www.w3.org/TR/SVG/text.html
 */
function svg_tspan($x, $y, $class=NULL) {
	$tag = new TSPANsvgtag( array("x" => $x,
								  "y" => $y));
	if ($class) {
		$tag->set_class( $class );
	}
	return $tag;
}


?>
