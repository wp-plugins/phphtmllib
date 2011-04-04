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
 * $Id$
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version 2.0
 * @since 2.5.5
 *
 */ 

/**
 * Include the phphtmllib libraries
 *
 */
include_once("includes.inc");
include_once("db_defines.inc");
include_once("MyLayoutPage.inc");

include_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/includes.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/CSVFILEDataListSource.inc");


/**
 * This class shows how to use the data coming
 * from a CSV Formatted file
 *
 */
class csvfilelist extends DefaultGUIDataList {

    function get_data_source()
    {
	    $csvFile = "http://" .
	        preg_replace("/^localhost$/", "127.0.0.1", $_SERVER['SERVER_NAME'])
       	        . PHPHTMLLIB_RELPATH . "/examples/test.csv";

		$source = new RemoteCSVFILEDataListSource($csvFile);
		$this->set_data_source( $source );
	}

	function user_setup()
   	{
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

class Widget23LayoutPage extends MyLayoutPage
{
    function content_block()
    {
        $container = container() ;

        //build the csv file data list object.
        $csvlist = new csvfilelist("CSV File list", 600, "LName");

        $container->add( html_span("font10", "View the source ",
	    html_a("test.csv", "test.csv file.")), html_br(2), $csvlist );

	    return $container ;
    }
}

//create the page object
$page = new Widget23LayoutPage("phpHtmlLib Widgets - DataList Example");

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}

//add the css
$page->add_head_css( new DefaultGUIDataListCSS );

print $page->render();
?>
