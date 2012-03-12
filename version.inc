<?php

/**
 * this contains the current version
 * define and some util functions
 * related to the lib version.
 *
 * $Id: version.inc 3553 2012-03-09 13:03:14Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 *
 */


/**
 * This is the version of the libs
 * @var string - the version string.
 */
define("PHPHTMLLIB_VERSION", '2.6.3.3556');


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
