<?php

/**
 * This example illustrates how to use the
 * HTMLPageClass to build a complete html
 * page.
 *
 *
 * $Id: example1.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage examples
 * @version 2.0.0
 *
 */ 

/**
 * Include the phphtmllib libraries
 * All subsequent examples will use the
 * inlude_once("includes.inc"); which contains
 * the following 2 lines
 */

include_once("includes.inc") ;
include_once(PHPHTMLLIB_ABSPATH . "/includes.inc");


//create the page object

//the first parameter is the title of the page. 
//this will automatically get placed inside the <title>
//inside the head.

//we want XHTML output instead of HTML
//IF you want HTML output, then just leave off the
//2nd parameter to the constructor.

//Be default, phpHtmlLib will nicely indent all of the output
//of the html source, to make it easy to read.  If you want
//all of the html source output to be left justified, then
//pass INDENT_LEFT_JUSTIFY as the 3rd parameter.
$page = new HTMLPageClass("phpHtmlLib Example 1 - Hello World",
						  XHTML_TRANSITIONAL);

//if you want phphtmllib to render the
//output as viewable source code
//then add ?debug=1 to the query string to this script
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}



//add the obligitory hello world
//calling the add method will add the object
//into the page.  It will get rendered when
//you call the HTMLPageClass' render() method.
$page->add( html_span(NULL, "hello world"), html_br(2) );

//note the calls to the 2 helper functions
//html_span() and html_br()  These are wrapper 
//functions for constructing tags and adding common
//attributes, along with content.
// All of the helper functions live in phphtmllib/tag_utils
//html_span() takes a string as the first parameter
//which will set the class="something" attribute
//any n number of parameters after that will be
//added to the content of the tag.

//html_br() builds a <br> tag.  The parameter is
//how many <br>'s to build.  


//lets add a simple link to this script
//and turn debugging on
$page->add( html_a($_SERVER["PHP_SELF"]."?debug=1", "Show Debug source") );


//this will render the entire page
//with the content you have added
//wrapped inside all the required
//elements for a complete HTML/XHTML page.
//NOTE: all the objects in phphtmllib have
//      the render() method.  So you can call
//      render on any phphtmlib object.
print $page->render();
?>
