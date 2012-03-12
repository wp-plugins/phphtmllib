<?php

/**
 * This file holds some global defines used by several
 * classes of phpHtmlLib.
 *
 * $Id: defines.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */ 

/**
 * Some global defines, used by the classes and widgets
 * to specify what type of output document format to use.
 *
 */
define("XHTML_TRANSITIONAL", "xhtml_transitional");
define("XHTML", "xhtml_transitional");
define("XHTML_STRICT", "xhtml_strict");
define("XHTML_FRAMESET", "xhtml_frameset");
define("HTML", "html");

/** 
 * set the default render type for
 * html tags
 */
$GLOBALS["HTML_RENDER_TYPE"] = HTML;

/**
 * Some defines to tell the class what style of
 * indenting of the output the user wants.
 */
define("INDENT_NICE", 0);
define("INDENT_LEFT_JUSTIFY", -1);


/**
 * some nice globals
 */
define( "_HTML_SPACE", "&nbsp;");
define( "_HTML_MDASH", "&mdash;");

/**
 * Some global defines for the tag classes
 */
define( "_INDENT_STR", "  ");

define( "_NEWLINEAFTERCONTENT", 1);
define( "_NEWLINEAFTEROPENTAG", 2);
define( "_NEWLINEAFTERCLOSETAG", 4);
define( "_CONTENTREQUIRED", 8);
define( "_CLOSETAGREQUIRED", 16);
define( "_DEPRICATED", 32);
define( "_INDENT", 64);
define( "_COLLAPSE", 128);
define( "_ALWAYS_UPPERCASE", 256);
define( "_ALWAYS_LOWERCASE", 512);
define( "_NOFINISHSLASHXHTML", 1024);
define( "_CDATACONTENTWRAP", 2048);
define( "_XHTMLCOMPLIANT", 4096);

define( "_TAG_PREFIX", "<");
define( "_TAG_SUFFIX", ">");
?>
