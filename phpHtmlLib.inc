<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Determine absolute file system path and document root path
 * for phpHtmlLib.  It would be nice to use PHP's built in
 * $_SERVER['DOCUMENT_ROOT'] but it doesn't always exist (IIS &
 * PHP4) and it doesn't always return the expected data (IIS and
 * PHP5).  So we improvise and figure it out!
 *
 * For the Library to work correctly, two constants must be
 * defined:
 *
 * -  PHPHTMLLIB_ABSPATH is used to reference include files and
 *    should be a file system path which is used by include(),
 *    require(), include_once(), and require_once().
 *
 * -  PHPHTMLLIB_RELPATH is used to reference images, css, and
 *    other assorted internal library paths in the context of a
 *    valid URL.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 * @subpackage examples
 * @version 2.0.0
 * @since 2.6.0
 */

//  PHPHTMLLIB_ABSPATH - used in library for include
//  references.  Pretty easy to determine the absolute
//  path.  Unfortunately, the relative (to the URL) path
//  is not so easy!

if (!defined('PHPHTMLLIB_ABSPATH'))
    define('PHPHTMLLIB_ABSPATH', dirname(__FILE__));

//  Figure out what the "absolute url-like" path is
//  URL will always have forward slashes so stripping
//  the absolute file system stuff off the path isn't
//  too hard.  Under Windows, it is a little harder
//  because of the Windows pathnames.


function ComposeRelativeURLPath()
{
    $script = $_SERVER['SCRIPT_NAME'] ;
    $file = strtr(__FILE__, "/", DIRECTORY_SEPARATOR) ;

    //  Need to decompose based on directory separator
    //  Script will always have forward slash but __FILE__
    //  may not depending on if the script is running under
    //  IIS.

    $script_path = explode("/", $script) ;
    $file_path = explode(DIRECTORY_SEPARATOR, $file) ;

    //  Clean up null strings resulting from leading slashes

    while ($script_path[0] == "")
        array_shift($script_path) ;

    //  Prune the leading directory hierarchy
    //  from the absolute path until a match with
    //  the relative URL hierarchy is found.

    while ($script_path[0] != $file_path[0])
    {
         array_shift($file_path) ;

         if (empty($file_path)) break ;
    }

    //  Reconstruct path by assembling pieces
    //  that match between the absolute and the
    //  relative URL path

    $relUrl = "" ;

    if (!empty($script_path) && !empty($file_path))
    {
        while ($script_path[0] == $file_path[0])
        {
            $relUrl .= "/" . $script_path[0] ;
            array_shift($script_path) ;
            array_shift($file_path) ;

            if (empty($script_path) || empty($file_path)) break ;
        }
    }

    return $relUrl ;
}


//  PHPHTMLLUB_RELPATH - used in widgets for images,
//  CSS links, and other internal library references.

if (!defined('PHPHTMLLIB_RELPATH'))
    define('PHPHTMLLIB_RELPATH',  ComposeRelativeURLPath()) ;

if (PHPHTMLLIB_RELPATH == "")
    die("phpHtmlLib error::  Unable to set PHPHTMLLIB_RELPATH, please configure phpHtmlLib before proceeding.") ;

if (defined('DEBUG'))
{
    if (DEBUG)
    {
        echo PHPHTMLLIB_ABSPATH . "<br>" ;
        echo PHPHTMLLIB_RELPATH . "<br>" ;
    }
}
?>
