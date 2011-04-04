<?php
/**
 * This file contains helper functions related
 * to framesets and frames
 *
 * $Id: frame_utils.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */


/**
 * This function is used to build a 
 * FRAMESETtag object with the most
 * common attributes.
 * NOTE: It comes with the following attributes
 *       defaulted to:
 *       framespacing = "0"
 *       frameborder = "no"
 *
 * @param string - $rows - the rows attribute
 * @param string - $cols - the cols attribute
 * @param int    - $border - the border attribute
 * @return FRAMESETtag object
 */
function html_frameset( $rows, $cols, $border="0" ) {

    $attributes = array("border" => $border,
                        "framespacing" => "0",
                        "frameborder" => "no",
                        "rows" => $rows,
                        "cols" => $cols);

    return new FRAMESETtag( $attributes );
}

/**
 * This function is used to build a
 * FRAMEtag object with some common attributes
 * already set.
 * NOT: this comes with the following attribtes 
 *      defaulted to:
 *      marginwidth = "0"
 *      marginheight = "0"
 *      noresize
 *      frameborder = "0"
 * 
 * @param string - $name - the "name" attribute
 * @param string - $src  - the "src" atribute
 * @param string - $scrolling - the "scrolling" attribute
 * @return FRAMEtag object.
 */
function html_frame( $name, $src, $scrolling="no") {

    $attributes = array("name" => $name,
			"src" => $src,
			"scrolling" => $scrolling,
			"marginwidth" => "0",
			"marginheight" => "0",
			"noresize",
			"frameborder" => "no");

    return new FRAMEtag( $attributes );
}
 

?>
