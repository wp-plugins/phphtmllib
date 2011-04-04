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
 * $Id: widget22.php,v 1.1.1.1 2005/10/10 20:28:30 mike Exp $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Mike Walsh <mike_walsh@mindspring.com>
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
include_once("MyLayoutPage.inc");

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
		$this->set_data_source( $source );
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
        $c = container() ;
        $t = html_table("") ;

        $s = $this->action_select("_action",
            array('one' => 1, 'two' => 2, 'three' => 3, 'four' => 4),
            "", false, array("style" => "width: 150px; margin-right: 10px;"),
            $_SERVER['PHP_SELF']); 

        //don't actually do anything.
        //just show how to add a button

        $t->add_row($s, _HTML_SPACE,
            $this->action_button('Test',$_SERVER['PHP_SELF']));

        $c->add($t) ;

        return $c ;
    }
}

class Widget22LayoutPage extends MyLayoutPage
{
    function footer_block()
    {
        $f = new FooterNav("phpHtmlLib Examples") ;
        $f->set_date_string(date("Y")) ;
        $f->add("index.php", "Examples") ;
        $f->add(basename(__FILE__), basename(__FILE__)) ;

        return $f ;
    }

    function content_block()
    {
        $container = container() ;

        //build the csv file data list object.
        $csvlist = new csvfilelist("CSV File list", 600, "LName");

        $container->add( html_span("font10", "View the source ",
	    html_a("test.csv", "test.csv file.")), html_br(2), $csvlist );

        if (!empty($_POST))
        {
            $t = new InfoTable("POST Vars", "500", "center") ;

            foreach ($_POST as $p => $v)
            {
                if (empty($v))
                    $t->add_row($p, _HTML_SPACE) ;
                else if (is_array($v))
                    $t->add_row($p, join($v, ", ")) ;
                else
                    $t->add_row($p, $v) ;
            }

            $container->add(html_br(2), $t, html_br(2)) ;
        }

	    return $container ;
    }
}

//create the page object
$page = new Widget22LayoutPage("phpHtmlLib Widgets - DataList Example");

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}

//add the css
$page->add_head_css( new DefaultGUIDataListCSS );

print $page->render();
?>
