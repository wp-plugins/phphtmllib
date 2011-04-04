<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the use of the 
 * DataList object classes.  This object
 * can show a list of data from any data source
 * and have any GUI layout and provide the 
 * features of:
 * searching, sorting, paging of the data.
 *
 * This page shows the Data coming a CSV 
 * (comma seperated values) file on disk.
 *
 * $Id: widget7.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version 2.0
 *
 */ 

/**
 * Include the phphtmllib libraries
 *
 */
include_once("includes.inc");
include_once("db_defines.inc");

include_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/includes.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/CSVFILEDataListSource.inc");


/**
 * This class shows how to use the data coming
 * from a CSV Formatted file
 *
 */
class csvfilelist extends DefaultGUIDataList {

	function get_data_source() {
		$source = new CSVFILEDataListSource("test.csv");
		$this->set_data_source($source);
	}

	function user_setup() {
		$this->add_header_item("First Name", "200", "FName", SORTABLE, SEARCHABLE);
        $this->add_header_item("Last Name", "200", "LName", SORTABLE, SEARCHABLE);
        $this->add_header_item("Email", "200", "Email", SORTABLE, SEARCHABLE, "center");

        //turn on the 'collapsable' search block.
        //The word 'Search' in the output will be clickable,
        //and hide/show the search box.
        $this->_collapsable_search = TRUE;

        //lets add an action column of checkboxes,
        //and allow us to save the checked items between pages.
        $this->add_action_column('checkbox', 'FIRST', 'Email');

        //we have to be in POST mode, or we could run out
        //of space in the http request with the saved
        //checkbox items
        $this->set_form_method('POST');

        //set the flag to save the checked items
        //between pages.
        $this->save_checked_items(TRUE);
	}

    function actionbar_cell() {
        //don't actually do anything.
        //just show how to add a button
        return $this->action_button('Test','');
    }
}


//create the page object
$page = new HTMLPageClass("phpHtmlLib Widgets - DataList Example",
						  XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}

//add the css
$page->add_head_css( new DefaultGUIDataListCSS );

//build the csv file data list object.
$csvlist = new csvfilelist("CSV File list", 600, "LName");

$page->add( html_span("font10", "View the source ",
					  html_a("test.csv", "test.csv file.")),
			html_br(2),
            $csvlist );

print $page->render();
?>
