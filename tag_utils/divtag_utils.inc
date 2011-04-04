<?php

/**
 * this file holds special DIVtag rendering functions.
 * Since the <div> is commonly used for special things
 * we automate some common used <div> content </div>
 * rendering functions.
 *
 * $Id: divtag_utils.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */


/**
 * make sure we include the required functions
 */
require_once(PHPHTMLLIB_ABSPATH . "/tag_utils/html_utils.inc");


/**
 * Render a div w/ a spacer give as its content.
 *
 * @author  Walter A. Boring IV
 * @param   int $width - the width of the img
 *                       ( DEFAULT : 1)
 * @param   int $height - the height of the img
 *                       ( DEFAULT : 1)
 * @return  DIVtag object.
 */
function div_build_spacergif_tag( $width, $height ) {
    $attributes = array( "style" => "font-family: times new roman; font-size: 2px;");
    $div = new DIVtag( $attributes );
    $div->push( build_spacergif_imgtag( $width, $height, "/images" ) );
    return $div;
}

/**
 * build a new div tag with default attributes of
 * "align=center"
 *
 * @author  Walter A. Boring IV
 * @param mixed - any # of arguments
 *                that will live in the <div></div> 
 * @return  DIVtag object.
 */
function html_div_center() {
    $attributes = array("align" => "center");
	$tag = new DIVtag( $attributes );
	$num_args = func_num_args();
	for ($i=0;$i<$num_args;$i++) {
		$tag->push(func_get_arg($i));
	}
    return $tag;
 }

/**
 * build a new div tag with content
 *
 * @author  Walter A. Boring IV
 *
 * @param string $class - the css class for the div
 * @param mixed - any # of arguments
 *                that will live in the <div></div> 
 * @return  DIVtag object.
 */
function html_div($class="") {

	$tag = new DIVtag();
	if ($class != "") {
		$tag->set_class($class);
	}
	$num_args = func_num_args();
	for ($i=1;$i<$num_args;$i++) {
		$tag->push(func_get_arg($i));
	}
    return $tag;
}


/**
 * This builds the 1px font size
 * DIVtag object, which can 
 * be used anywhere
 *
 * @param mixed - any # of arguments
 *                that will live in the <div></div>
 *
 * @return DIVtag object.
 */
function html_div_small() {
	$tag = new DIVtag( array("style" => "font-size: 1px;line-height: 1px;") );
	$num_args = func_num_args();
	for ($i=0;$i<$num_args;$i++) {
		$tag->push(func_get_arg($i));
	}
    return $tag;
}
?>
