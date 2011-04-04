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
 * This page shows the Data coming from 2 different
 * types of DB objects.  One from a PEAR::DB object,
 * and another from a ADODB object.
 *
 * $Id: widget6.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
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
include_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/PEARSQLDataListSource.inc");

//add the include path for adodb
//assuming you have the adodb dir in your
//site's document root.
//ini_set("include_path", 
//        ini_get("include_path").":".$_SERVER["DOCUMENT_ROOT"]."/adodb");
//ini_set("include_path", 
//        ini_get("include_path").":". PHPHTMLLIB_ABSPATH ."/adodb");

//  Where is document root?  Count the number of slahes in
//  PHPHTMLLIB_RELPATH and back track up the hierarchy the
//  appropriate number of times.

$relpath = "/" ;
$nodes = explode("/", PHPHTMLLIB_RELPATH) ;

if (!empty($nodes) && $nodes[0] == "") array_shift($nodes) ;

foreach($nodes as $node) $relpath .= "../" ;

require_once(PHPHTMLLIB_ABSPATH . $relpath . "adodb/adodb.inc.php" );

include_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/ADODBSQLDataListSource.inc");
include_once(PHPHTMLLIB_ABSPATH . "/form/includes.inc");

/**
 * This is an example that shows how to use a PEAR db object
 * as the source for the data to show.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version 2.0
 */
class pearmysqllist extends DefaultGUIDataList {
    //change the # of rows to display to 20 from 10
    var $_default_rows_per_page = 20;

    /**
     * This function is called automatically by
     * the DataList constructor.  It must be
     * extended by the child class to actually
     * set the DataListSource object.
     *
     * 
     */
    function get_data_source() {
        //build the PEAR DB object and connect
        //to the database.
        $dsn = "mysql://".DB_USERNAME.":".DB_PASSWORD."@".DB_HOSTNAME."/".DB_NAME;
        $db = DB::connect($dsn, TRUE);
        if (DB::isError($db)) {
            die( $db->getMessage() );
        }

        //create the DataListSource object
        //and pass in the PEAR DB object
        $source = new PEARSQLDataListSource($db);

        //set the DataListSource for this DataList
        //Every DataList needs a Source for it's data.
        $this->set_data_source( $source );

        //set the prefix for all the internal query string 
        //variables.  You really only need to change this
        //if you have more then 1 DataList object per page.
        $this->set_global_prefix("pear_");
    }

    /**
     * This method is used to setup the options
     * for the DataList object's display. 
     * Which columns to show, their respective 
     * source column name, width, etc. etc.
     *
     * The constructor automatically calls 
     * this function.
     *
     */
    function user_setup() {
        //add the columns in the display that you want to view.
        //The API is :
        //Title, width, DB column name, field SORTABLE?, field SEARCHABLE?, align
        $this->add_header_item("IP", "100", "ip_address", SORTABLE, 
                               SEARCHABLE, "left");
        $this->add_header_item("Version", "100", "version", SORTABLE,
                                SEARCHABLE,"center");
        $this->add_header_item("Time", "200", "time", SORTABLE, 
                               NOT_SEARCHABLE,"center");

        
        $this->_db_setup();     
    }


    /**
     * Build this method so we can override it in the child class
     * for the advanced search capability.
     * 
     * @return VOID
     */
    function _db_setup() {
        $columns = "*";
        $tables = "user_downloads u, versions v";
        $where_clause = "u.version_id=v.version_id";
        $this->_datasource->setup_db_options($columns, $tables, $where_clause);
    }

    /**
     * This is the basic function for letting us
     * do a mapping between the column name in
     * the header, to the value found in the DataListSource.
     *
     * NOTE: this function is can be overridden
     *       so that you can return whatever you want for
     *       any given column.  
     *
     * @param array - $row_data - the entire data for the row
     * @param string - $col_name - the name of the column header
     *                             for this row to render.
     * @return  mixed - either a HTMLTag object, or raw text.
     */
    function build_column_item($row_data, $col_name) {
        switch ($col_name) {
        case "Time":
            $obj = date("m/d/Y h:i A", strtotime($row_data["time"]));
            //$obj = $row_data["time"];
            break;
        default:
            $obj = DefaultGUIDataList::build_column_item($row_data, $col_name);
            break;
        }
        return $obj;
    }    
}

/**
 * This is a subclass of the pear mysql list object.
 * The only difference being is the DataListSource object
 * for an ADODB object, instead of a PEAR DB object.
 *
 */
class adodbmysqllist extends pearmysqllist {

    /**
     * This function is called automatically by
     * the DataList constructor.  It must be
     * extended by the child class to actually
     * set the DataListSource object.
     *
     * 
     */
    function get_data_source() {
        //build the PEAR DB object and connect
        //to the database.
        $db = &ADONewConnection('mysql');  # create a connection
        $db->PConnect(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD,DB_NAME);

        //create the DataListSource object
        //and pass in the PEAR DB object
        $source = new ADODBSQLDataListSource($db);

        //set the DataListSource for this DataList
        //Every DataList needs a Source for it's data.
        $this->set_data_source( $source );

        //set the prefix for all the internal query string 
        //variables.  You really only need to change this
        //if you have more then 1 DataList object per page.
        $this->set_global_prefix("adodb_");
    }

    /**
     * Build this method so we can override it in the child class
     * for the advanced search capability.
     * 
     * @return VOID
     */
    function _db_setup() {
        $columns = "*";
        $tables = "user_downloads u, versions v";
        $where_clause = "u.version_id=v.version_id";

        //enable the advanced search calls
        $this->advanced_search_enable();

        if ($advanced_search_where = $this->advanced_search_where_clause()) {
            $where_clause .= " and " . $advanced_search_where;
        }

        $this->_datasource->setup_db_options($columns, $tables, $where_clause);
    }
    /**
     * This builds the UI for the advanced search form
     * 
     */
    function advanced_search_form() {
        // build the form fields
        $table = html_table("100%", 0, 0, 2);
        $table->set_default_col_attributes(array("style"=>"border-bottom:1px solid #dedede;"));

        $cur_year = date('Y');
        $years = new FEYears('years', TRUE, NULL, NULL, 2000, $cur_year);
        $years->set_style_attribute('vertical-align', 'middle');

        if (!isset($_REQUEST['years'])) {
            $years->set_value($cur_year);
        }

        $td = html_td();
        $current_month = '';
        $current_year = '';
        $td->add('Download Year',
                 _HTML_SPACE._HTML_SPACE,
                 $years->get_element(),
                 _HTML_SPACE._HTML_SPACE,
                 form_submit($this->get_form_name(),
                             $this->_search_text["button"], array("style"=>"vertical-align:middle;")));

        $table->add_row( $td );
        return $table;
    }


    /**
     * This function builds the portion of the where clause
     * pertaining to the advanced search/filtering
     * 
     * @return string
     */
    function advanced_search_where_clause() {

        //now build the data search from 
        $years = 0;
        if (isset($_REQUEST['years'])) {
            $years = $_REQUEST['years'];
            //small sanity check
            settype($years, 'int');
        }   

        if (empty($years))
            $years = date("Y");

        return "u.time like '".$years."%'";
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

//build the PEAR list and sort by ip_address by default
$pearlist = new pearmysqllist("PEAR::MySQL List", 600, "ip_address", TRUE);
$pearlist->set_align("right");

//build the ADODB list using the same exact table in the DB
//and sort by version by default
$adodblist = new adodbmysqllist("ADODB::MySQL List", 600, "version", TRUE);
$adodblist->set_align("left");

$page->add( $pearlist, html_br(2), $adodblist );

print $page->render();
?>
