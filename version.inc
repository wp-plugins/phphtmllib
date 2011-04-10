<?php

/**
 * this contains the current version
 * define and some util functions
 * related to the lib version.
 *
 * $Id: version.inc 3542 2011-01-28 13:49:18Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 *
 */


/**
 * This is the version of the libs
 * @var string - the version string.
 */
define("PHPHTMLLIB_VERSION", '2.6.2.3546');


/**
 * get the current version of
 * the phphtmllib libraries.
 *
 * @return string - the current version string
 */
function phphtmllib_get_version() {
    return PHPHTMLLIB_VERSION;
}


?>
