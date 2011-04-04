<?php

/**
 * Another example of how to build a table
 * with some data
 *
 *
 * $Id: example2.php 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage examples
 * @version 2.0.0
 *
 */ 

/**
 * Include the phphtmllib libraries
 */
include_once("includes.inc");


//create the page object
$page = new HTMLPageClass("phpHtmlLib Example 2 - Table example script",
						   XHTML_TRANSITIONAL);

if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}


//build a <style> tag and a little bit
//of local css declarations to spruce up
//the look of the table.
//You can also easily add external stylesheet
//links.  I'll show that in other examples.
$style = html_style();
$style->add( "span.foo { font-size: 1em; font-weight: bolder;}" );
$style->add( "td { padding-left: 5px; text-align: center;}" );
$style->add( "table {border: 2px solid #999999;}" );
$style->add( "th {background-color: #eeeeee; ".
			      "border-bottom: 2px solid #999999;}" );
$style->add( "caption { font-size: 14pt; font-weight: bold;}" );
$page->add_head_content( $style );


//lets add a simple link to this script
//and turn debugging on,
//then add 2 <br> tags
$page->add( html_a($_SERVER["PHP_SELF"]."?debug=1", "Show Debug Source"),
			html_br(2) );


//build the table that will hold the data
$data_table = html_table("500", 0, 0);

//add a caption for the table.
$data_table->add( html_caption("A Caption for the table") );

//Add 1 <tr> to the table with 3 <th> tags.
$data_table->add_row( html_th("Column 1"), html_th("Column 2"),
					  html_th("BAR") );


//now demonstrate an easy way to add
//20 rows to a table 1 row at a time.
//You could easily pull the row data from
//a DB
for($x=0; $x<20; $x++) {
	//add 1 <tr> to the table with 3 <td>'s
	//the last <td> contains a span with a
	//class attribute of "foo"
	$data_table->add_row("Row #".($x+1),
						 $x*2,
						 html_span("foo", "something else"));
}

//add the table to the page.
$page->add( $data_table );


//this will render the entire page
print $page->render();
?>
