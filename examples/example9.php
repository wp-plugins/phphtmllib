<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/** 
 *
 * The ideal way to use phphtmllib is to use the PageWidget object to create
 * complete html documents. If you are managing an existing code base with its
 * own structure and templates the ideal setup might not be practical. This
 * doesn't mean you can't use phphtmllib. Every descendant from the Container
 * object (all the classes for html tags) have a render() method which allow
 * you to generate output.
 * 
 * This example generates a short html table fragment that could be inserted
 * anywhere in your code. It also attempts to make use of most of the TABLETag
 * methods.
 *
 * $Id: example9.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @package phpHtmlLib 
 * @subpackage examples 
 * @version 1.0.0
 *
 */ 

// load the phphtmllib files
include_once("includes.inc") ;
include_once(PHPHTMLLIB_ABSPATH . "/includes.inc");


// html_table() is a built-in helper function that returns a table object
$table = html_table('95%', 1, 5, 5);

// add caption tag as the first element in the table.  TR tags should be added with add_row()
$table->add(html_caption("A Caption for the table"));

// default attributes for TDTags
$table->set_default_col_attributes(array('nowrap' => 'nowrap'));
// default attributes for TRTags
$table->set_default_row_attributes(array('align' => 'center'));

// these methods are available to all html tags
$table->set_class('myclass');
$table->set_id('table1');
$table->set_style('background-color:#EEE'); 
$table->set_tag_attribute('name', 'the name of my table');

// add some data
for ($i = 0; $i<20; $i++) {
    // add_row takes any number of arguments.  Each argument will be a cell in the row
    // any item can be another html attribute-- the first column here is a BTag object
    $table->add_row(html_b(rand(1,1000)), rand(2000,3000), rand(3000,4000));
}

// update a cells content and attributes-- row and column settings are 0 based
$table->set_cell_content(1, 2, 'this cell is special and it will not wrap because we set no wrap above');
$table->set_cell_attributes(1, 2, array('align' => 'right', 'style' => 'background-color:#F00;'));

// udate a row
$table->set_row_attributes(5, array('align' => 'left'));

// set the summary attribute of the table
$table->set_summary('the sum of all tables');

// generate the html
print $table->render();

?>
