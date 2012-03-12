<?php

/**
 * this file includes all of the currently supported
 * tag classes.
 *
 * $Id: includes.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */

/**
 * include all the HTML/XHTML tags
 */
include_once(PHPHTMLLIB_ABSPATH . "/tag_classes/ALLTAGS.inc");

/**
 * include all the XML tags used by HTML
 */
include_once(PHPHTMLLIB_ABSPATH . "/tag_classes/XMLTAGS.inc");

/**
 * include all the WML specific tags
 */
include_once(PHPHTMLLIB_ABSPATH . "/tag_classes/WMLTAGS.inc");

/**
 * include all the SVG specific tags
 */
include_once(PHPHTMLLIB_ABSPATH . "/tag_classes/SVGTAGS.inc");
?>
