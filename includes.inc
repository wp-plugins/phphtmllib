<?php

/**
 * the script that includes this file MUST
 * set the $phphtmllib var.  Its used to determine
 * the base path on the filesystem where the php html libs
 * live.
 *
 * $Id: includes.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */

if (!defined('PHPHTMLLIB_ABSPATH'))
    include_once("phpHtmlLib.inc") ;

/**
 * include the defines first
 */
include_once(PHPHTMLLIB_ABSPATH . "/defines.inc");

/**
 * this is the base class of them ALL
 */
include_once(PHPHTMLLIB_ABSPATH . "/ContainerClass.inc");

/**
 * get the XML tag class
 */
include_once(PHPHTMLLIB_ABSPATH . "/XMLTagClass.inc");

/**
 * get the parent tag class
 */
include_once(PHPHTMLLIB_ABSPATH . "/HTMLTagClass.inc");

/**
 * now get all of the supported tag.
 */
include_once(PHPHTMLLIB_ABSPATH . "/tag_classes/includes.inc");

/**
 * lets get all of the tag utility functions.
 */
include_once(PHPHTMLLIB_ABSPATH . "/tag_utils/includes.inc");

/**
 * lets get all of the widget classes
 * that are based on the tag classes and 
 * tag util functions
 */
include_once(PHPHTMLLIB_ABSPATH . "/widgets/includes.inc");

/**
 * Get the version #string and the version functions
 */
include_once(PHPHTMLLIB_ABSPATH . "/version.inc");

?>
