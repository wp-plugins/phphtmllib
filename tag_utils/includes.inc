<?php

/**
 * this file includes all of the utility function files.
 * these files define utility functions that help 
 * the creation of the tag objects.
 *
 * $Id: includes.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */

/**
 * do the includes
 */
include_once(PHPHTMLLIB_ABSPATH . "/tag_utils/divtag_utils.inc");
include_once(PHPHTMLLIB_ABSPATH . "/tag_utils/font_utils.inc");
include_once(PHPHTMLLIB_ABSPATH . "/tag_utils/form_utils.inc");
include_once(PHPHTMLLIB_ABSPATH . "/tag_utils/frame_utils.inc");
include_once(PHPHTMLLIB_ABSPATH . "/tag_utils/html_utils.inc");
include_once(PHPHTMLLIB_ABSPATH . "/tag_utils/misc_utils.inc");

//include the xml stuff
include_once(PHPHTMLLIB_ABSPATH . "/tag_utils/xml_utils.inc");
include_once(PHPHTMLLIB_ABSPATH . "/tag_utils/wml_utils.inc");
include_once(PHPHTMLLIB_ABSPATH . "/tag_utils/svg_utils.inc");

?>
