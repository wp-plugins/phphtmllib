<?php
/**
 * This is the base class for managing a list
 * of data points.
 *
 * $Id: DataList.inc 3577 2015-05-19 01:09:35Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */

if (!defined('PHPHTMLLIB_WIDGET_IMAGEPATH'))
    define('PHPHTMLLIB_WIDGET_IMAGEPATH', PHPHTMLLIB_RELPATH . '/images/widgets') ;

/**
 * Some global defines used
 */
define("NOT_SORTABLE", 0);
define("SORTABLE", 1);
//case insensitive sorting.
define("SORTABLE_ICASE", 2);
//numeric type sorting.
define("SORTABLE_NUMERIC", 3);

define("SEARCHABLE", TRUE);
define("NOT_SEARCHABLE", FALSE);

//Some defines for setting up the search
//modifier fields.
define("SEARCH_BEGINS_WITH", 1);
define("SEARCH_CONTAINS", 2);
define("SEARCH_EXACT", 4);
define("SEARCH_ENDS_WITH", 8);
define("SEARCH_ALL", 15);


/**
 * This object is the base class that can be
 * used to build a widget that shows lists of
 * data from any source via the DataListSource
 * object.  It fetches/builds/gets its data
 * from the DataListSource object, which can
 * be written to support any data source
 * (MySQL, Oracle, comma delimited file, xml, etc.)
 *
 * This base class MUST be extended by a child to
 * actually render the list.  The job of the DataList
 * class is to provide the basic API and abstraction
 * mechanism to handling searching, showing, sorting
 * lists of data.
 *
 * Each column of data is associated with a title and a
 * name.  The title is what is shown to the user for that
 * column.  The name is the mapping between the column and
 * the DataListSource.  Each column can be marked
 * as sortable and searchable.  If a column is sortable,
 * the title is a link that can be clicked on to sort.
 * The sorting is done in the DataListSource object (
 * via the sql query, or sort() functions depending on the
 * data source itself)
 *
 * The DataList object will build the title, the search block
 * (if any), the datalist controls (the links/imges for
 * first, prev, next, last, all).  Then the data columns/labels.
 * Then it will fetch each of the rows of data to display
 * from the DataListSource.
 *
 * The logic of the output calls follows in the order:
 *
 * title
 * search table/block
 * datalist controls (first, prev, next, last, all)
 * data columns/labels
 * data rows x through y
 *
 *
 * REQUIREMENTS:
 *  You must use/define a DataListSource object.
 *  You MUST override/extend the following methods:
 *
 *  * get_data_source() - used to set the DataListSource
 *                         by this class.
 *  * user_setup() - used to set the columns to show and any
 *                   options used by the DataList class and
 *                   DataListSource object.
 *
 *
 *  UI ABSTRACTION METHODS
 *  These methods allow for some level of abstraction for
 *  the layout/look/feel of the actual list of data.
 *
 *
 *  * gui_init() - the function gives the child class a chance
 *                 to do any building of the objects that will
 *                 hold the search area, column headers and the
 *                 rows of data.
 *
 *  * child_build_column_header() - This method is responsible
 *                                  for building and inserting
 *                                  the column header title into
 *                                  the UI object.
 *
 *  * child_add_row_cell() - This function is responsible for adding
 *                           the cell in the current row.  The method
 *                           is responsible for keeping track of the
 *                           location in its UI object for the current
 *                           row.
 *
 *  * child_get_gui() - This method returns the entire UI in 1 object
 *                      or container.  At this point the entire UI
 *                      has been constructed, the entire list of data
 *                      has been walked and inserted.
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class DataList extends BaseWidget {

    /**
     * This value holds the number
     * of pages of data we have
     * to display.
     *
     */
    var $_num_pages=1;

    /**
     * The number of rows of data
     * to show per "page".
     * The default is 20.
     *
     */
    var $_default_rows_per_page = 10;

    /**
     * The max number of rows to
     * show when the user does the
     * "EXPAND" command.
     */
    var $_max_rows = 200;

    /**
     * Flag to tell us to show every
     * row that comes from the DB or not.
     * By default this is off.
     */
    var $_show_all_rows = FALSE;    

    /**
     * prefix for all list variable
     * names, so we can potentially
     * have more then 1 list per page.
     */
    var $_global_prefix = '';


    /**
     * Holds an array of all the
     * form vars we need for this
     * class to work.
     */
    var $_vars = array("offsetVar" => "offset",
                       "orderbyVar" => "orderby",
                       "reverseorderVar" => "reverseorder",
                       "numrowsVar" => "numrows",
                       "expandrowsVar" => "expandrows",
                       "search_fieldVar" => "search_field",
                       "search_valueVar" => "search_value",
                       "search_typeVar" => "search_type",
                       "simple_search_modifierVar" => "simple_search_modifier");

    /**
     * Holds the db column name that
     * we want to order by default.
     */
    var $_default_orderby = '';

    /**
     * Holds a flag to let us know to
     * reverse order the column by default
     */
    var $_default_reverseorder = "false";

    /**
     * Flag to let us know that search
     * is enabled.
     *
     */
    var $_search_flag = FALSE;

    /**
     * Flag to let us know that
     * advanced search is enabled
     *
     */
    var $_advanced_search_flag = FALSE;

    /**
     * Flag to enable simple search modifyer.
     * IF enabled it will add a select that adds
     * the "beings with", "contains" options for
     * a simple search.
     */
    var $_simple_search_modifier = FALSE;


    /**
     * Holds the object block that is the
     * search UI
     */
    var $_search_table = NULL;

    /**
     * This holds a list of
     * name=>value vars that the
     * caller/child wants to propogate
     * automatically.
     *
     */
    var $_save_vars = array();


    /**
     * The column descriptions
     * for the data we are working on
     *
     * @var array
     */
    var $_columns = array();

    /**
     * Keeps track of the # of columns we have
     */
    var $_num_columns = 0;


    /**
     * This holds the form attributes
     *
     */
    var $_form_attributes = array("method" => "get",
                                  "target" => "",
                                  "action" => "",
                                  "name" => "datalist");

    /**
     * Build everything inside a form?
     *
     */
    var $_form_render_flag = FALSE;


    /**
     * flag to let us know if we want to show
     * the results or not.
     */
    var $_show_results_flag = TRUE;


    /**
     * Holds our reference/copy of the
     * DataListSource object which is used to
     * access the data that this object uses
     *
     * @var DataListSource object
     */
    var $_datasource = NULL;

    /**
     * This stores the base path to where the
     * tool link images live.  This lets you
     * specify a new path to where your images
     * live.
     */
    var $_image_path = PHPHTMLLIB_WIDGET_IMAGEPATH ;

    /**
     * flag indicating if we should scrub the data
     */
    var $_clean_string = TRUE;


    /**
     * debugging flag for debugging queries.
     *
     */
    var $_debug = FALSE;

	/**
     * This is the message displayed when no data
     * was retrieved from the database
     */
    var $_not_found_message = "No data was found";


    /**
     * The constructor
     *
     * @param string - the title of the data list
     * @param string - the overall width
     * @param string - the column to use as the default sorting order
     * @param boolean - sort the default column in reverse order?
     */
    function DataList($title, $width = "100%", $default_orderby='',
                      $default_reverseorder=FALSE) {
        $this->set_title( $title );

        if ($title != NULL && $title != "") {
            $this->set_form_name(strtolower(preg_replace('/(\W|^\d)/', '_', $title)));
        }

        $this->set_width( $width );


        $this->_default_orderby = $default_orderby;
        if ( $default_reverseorder === TRUE ) {
            $default_reverseorder = "true";
        }if ( $default_reverseorder === FALSE ) {
            $default_reverseorder = "false";
        }
        $this->_default_reverseorder = $default_reverseorder;


        //Set the global prefix for our variables.
        //want to make sure we can have multiple
        //item lists per html page.
        $this->set_global_prefix('');

        //allow someone to do some generic
        //action before we get the data source
        //and start processing rows.
        $this->do_action();

        //child class MUST override this
        //method to automatically set
        //the DataListSource object.
        //This class doesn't work without it.
        $this->get_data_source();

        //Call the subclass setup function.
        //This is a way to get around having
        //to override the constructor and
        //pass in the same params.
        $this->user_setup();
    }

    /**
     * This function renders the final
     * widget
     *
     */
    function render($indent_level=0, $output_debug=0) {

        //setup the columns in their sorts
        $this->setup_columns();

        //do any data prefetch work
        //which may be child specific
        if ( $this->_show_results() ) {
            $this->data_prefetch();
        }

        //This function gives the child class
        //a chance to build the tables/divs/containers
        //that will be responsible for the look/feel
        //of the DataList
        $this->gui_init();

        //see if we need to build the search area.
        if ( $this->is_search_enabled() || $this->is_advanced_search_enabled() ) {
            $this->_search_table = $this->child_build_search_table();
            if ( $this->_search_table ) {
                $this->set_form_render(TRUE);
            }
        }


        if ( $this->get_form_render() ) {
            $form =  new FORMtag( array("method" => $this->get_form_method(),
                                        "action" => $this->build_base_url(),
                                        "name" => $this->get_form_name(),
                                        "style" => "margin-top: 0px;margin-bottom:0px;") );

            $target = $this->get_form_target();
            if ( $target != NULL )
                $form->set_tag_attribute("target",$target);

            $action = $this->get_form_action();
            if ( $action != NULL )
                $form->set_tag_attribute("action",$action);

            //now build the UI and return it
            $form->add( $this->build_gui() );

        } else {
            $form = container();

            //now build the UI and return it
            $form->add( $this->build_gui() );
        }

        //add the hidden vars if we are a POST
        if ($this->get_form_method() == "POST") {
            $form->add( $this->_build_default_vars() );
        }

        //add the save vars the user wants.
        $form->add( $this->_build_save_vars() );

        //add any javascript required
        $container = container( $this->_javascript(), $form );
        return $container->render( $indent_level, $output_debug );
    }

    /**
     * This function is responsible for calling the child
     * class's methods for building the GUI container.
     * This function builds the search area, the
     * title, page controls, the column headers,
     * and walks the rows of data and adds them
     *
     * A child class can override this method to
     * move the placement of the search box
     * relative to the data list.  By default
     * the search area comes above the table
     * for the data list and page controls
     *
     * @return Container
     */
    function build_gui() {
        $container = container();

        //if we have a search area to show
        //add it to the ui.
        if ( $this->_search_table ) {
            $container->add( $this->_search_table );
        }

        if ( $this->_show_results() ) {
            //walk the list of columns and call the child
            //method to add it
            $column_count = count($this->_columns);
            foreach( $this->_columns as $name => $col ) {
                $this->child_build_column_header( $name, $col, $column_count);
            }

            if ($this->_query_worked) {
                //now walk the list of rows and build and add the
                //cells of data
				$even = TRUE;
                while ( $row = $this->_datasource->get_next_data_row() ) {
                    //try and filter the row.
                    if (!$this->_datasource->row_filter($row)) {
                        $this->_datasource->set_total_rows( $this->_datasource->get_total_rows() -1);
                        continue;
                    }
                    $cnt = 1;
                    foreach( $this->_columns as $col_name => $data ) {
                        if ($this->_clean_string) {
                            $obj = $this->_clean_string($this->build_column_item($row, $col_name),
                                                        $col_name);
                        } else {
                            $obj = $this->build_column_item($row, $col_name);
                        }

                        $this->child_add_row_cell($obj, $col_name,
                                                  (($cnt == $column_count) ? TRUE : FALSE),
                                                  $row, $even);
                        $cnt++;
                    }
					$even = !$even;
                }
            }
            $container->add( $this->child_get_gui() );
        }


        return $container;
    }


    /**
     * This method is called prior to get_data_source
     * and user_setup() to allow you to do some generic
     * action on data.  By default this does nothing.
     *
     */
    function do_action() {
        return null;
    }

    /**
     * This function is called automatically by
     * the DataList constructor.  It must be
     * extended by the child class to actually
     * set the DataListSource object.
     *
     *
     */
    function get_data_source() {
        user_error("DataList::get_data_source() - ".
                   "child class must override this to ".
                   "set the the DataListSource object.");
    }

    /**
     * A subclass can override this function
     * to setup the class variables after
     * the constructor.  The constructor
     * automatically calls this function.
     *
     */
    function user_setup() {
        user_error("DataList::user_setup() - ".
                   "child class must override this method ".
                   "to set the columns, and any options for ".
                   "the DataListSource.");
    }

    /**
     * A subclass can override this function
     * to setup the class variables after
     * the constructor.  The constructor
     * automatically calls this function.
     *
     */
    function gui_init() {
        user_error("DataList::gui_init() - ".
                   "child class must override this method ".
                   "to set up the containers/objects that will ".
                   "hold the search area, page controls, ".
                   "column headers and the data cells");
    }

    /**
     * This method is supposed to be written by
     * the child class to build and add the column
     * title to the UI
     *
     * @param string - the title of the column
     * @param array - the column data ( from $this->_columns )
     * @param int - the column #
     *
     */
    function child_build_column_header($title, $col_data, $col_count) {
        user_error("DataList::child_build_column_header() - ".
                   "child class must override this method ".
                   "to build the object that will be the ".
                   "individual column header/itle");
    }

    /**
     * This method is supposed to be written by
     * the child class to add the cell data to the
     * current row in the UI
     *
     * @param mixed - the object/string/entity that
     *                should get put into the column row cell.
     * @param string - the name/title of the column that the
     *                 object will live in
     * @param boolean - flag that tells the function if this is
     *                  is the last cell for the current row.
     *
     */
    function child_add_row_cell($obj, $col_name, $last_in_row_flag, $row_data, $even_row) {
        user_error("DataList::child_add_row_cell() - ".
                   "child class must override this method ".
                   "to build the object that will be the ".
                   "individual column data cell");
    }

    /**
     * This function is called after all of the data has
     * been added to the UI object.  It just returns the
     * container that is the entire UI for the DataList
     *
     * @return Container
     */
    function child_get_gui() {
        user_error("DataList::child_get_gui() - ".
                   "child class must override this method ".
                   "to return the wrapper that contains ".
                   "the entire UI.");
    }

    /**
     * This function builds the search
     * block that lives above the results
     *
     * @return Container
     */
    function child_build_search_table() {
        user_error("DataList::child_build_search_table() - ".
                   "child class must override this");
        return NULL;
    }

    /**
     * This function provides a way to automatically
     * add javascript to this object.
     * This function is meant to be extended by the
     * child class.
     *
     * @return SCRIPTtag object
     */
    function _javascript() {
        return NULL;
    }

    /**
     * This function adds a header item to the column headers
     * from a list of parameters.
     *
     * @param string - $label - the label to use for
     *                          the column header.
     * @param int    - $size - the size for the table column.
     * @param string - $dbfield - the db field associated
     *                            with this label from the query.
     * @param boolean - $sortable - flag to make this column sortable.
     * @param boolean - $searchable - flag to make this column searchable.
     * @param string - header align value.
     * @param string - the sort order
     * @param string - the maximum # of characters to allow in the cell.
     *
     * @return array a single header array
     */
    function add_header_item( $label, $size=100, $data_name=NULL,
                              $sortable=FALSE, $searchable=FALSE,
                              $align="left", $sortorder="",
                              $max_text_length=NULL) {

        $this->_columns[$label] = array("size" => $size,
                                        "data_name" => $data_name,
                                        "sortable" => $sortable,
                                        "searchable" => $searchable,
                                        "align" => $align,
                                        "sortorder" => $sortorder,
                                        "maxtextlength" => $max_text_length,
                                        "reverseorder"=>false);
        //$this->_num_headers++;

        $this->_check_datasource("add_header_item");
        $this->_datasource->add_column($label, $data_name, $sortable,
                                       $searchable, $sortorder);
    }


    /**
     * This function sets a prefix for all
     * variables that are used in the item list
     * table on a page.  This allows you to have
     * multiple itemlists on a single html page.
     *
     * @param string $prefix - the prefix for all vars.
     */
    function set_global_prefix($prefix) {
        $this->_global_prefix = $prefix;
        //update all the vars used
        foreach ($this->_vars as $name => $value ) {
            $this->_vars[$name] = $prefix.$value;
        }
    }

    /**
     * returns the current variable prefix
     * string being used.
     *
     * @return string - current global prefix
     */
    function get_global_prefix() {
        return $this->_global_prefix;
    }

    /**
     * This function is used to set the
     * DataListSource object for this instance
     *
     * @param DataListSource object
     */
    function set_data_source( $datasource ) {
        $this->_datasource = &$datasource;
    }

    /**
     * Enable the search ability.
     *
     * @param boolean
     */
    function search_enable( ) {
        $this->_search_flag = TRUE;
        if ( !$this->is_advanced_search_enabled() ) {
            $this->set_search_type("simple");
        }
    }

    /**
     * Disable the search ability.
     *
     * @param boolean
     */
    function search_disable( ) {
        $this->_search_flag = FALSE;
    }

    /**
     * get the status of the search
     * ability.
     *
     * @return boolean
     */
    function is_search_enabled() {
        return $this->_search_flag;
    }


    /**
     * Enable the advanced search
     * capability
     * NOTE: Child class MUST
     *       extend the
     *       _build_advanced_search_table
     */
    function advanced_search_enable() {
        $this->_advanced_search_flag = TRUE;
		$this->set_search_type("advanced");
    }

    /**
     * Disable the advanced search
     * capability
     *
     */
    function advanced_search_disable() {
        $this->_advanced_search_flag = FALSE;
    }

    /**
     * This returns the status of the
     * advanced search flag.
     *
     * @return boolean
     */
    function is_advanced_search_enabled() {
        return $this->_advanced_search_flag;
    }

    /**
     * Set the simple search modifyer
     * flag.
     * NOTE: by default all the modifiers
     *       are enabled.  You can limit the
     *       modifiers by passing in the
     *       string of defines of which ones
     *       you want enabled.
     *
     * MODIFIERS:
     *          SEARCH_BEGINS_WITH
     *          SEARCH_CONTAINS
     *      SEARCH_EXACT
     *      SEARCH_ENDS_WITH
     *
     *       ie. SEARCH_BEGINS_WITH.SEARCH_EXACT
     *           will enable ONLY the
     *           "begins with" and "exact" modifiers.
     *
     * @param string
     */
    function set_simple_search_modifier( $modifier = SEARCH_ALL ) {
        if ( $modifier == 0 ) {
            $this->_simple_search_modifier = SEARCH_BEGINS_WITH |
                                             SEARCH_CONTAINS |
                                             SEARCH_EXACT |
                                             SEARCH_ENDS_WITH;
        } else {
            $this->_simple_search_modifier = $modifier;
        }
    }

    /**
     * gets the value of the search modifier
     * flag.
     */
    function get_simple_search_modifier() {
        return $this->_simple_search_modifier;
    }

    /**
     * This function sets the default # of rows
     * per page to display.  By default its 10.
     * This lets the user override this value.
     *
     * @param int - the # of rows to use.
     */
    function set_default_num_rows( $num_rows ) {
        $this->_default_rows_per_page = $num_rows;
    }

    /**
     * This function gets the current default
     * number of rows to display setting.
     *
     * @return int
     */
    function get_default_num_rows( ) {
        return $this->_default_rows_per_page;
    }

    /**
     * This returns the Maximum # of rows to
     * display when in expand mode
     *
     * @return int
     */
    function get_max_rows() {
        return $this->_max_rows;
    }

    /**
     * This sets the maximum # of rows to
     * display when in expand mode
     *
     * @param int - new # of maximum rows
     *              to display when in 'expand' mode
     *
     */
    function set_max_rows( $max ) {
        $this->_max_rows = $max;
    }

    /**
     * This method sets the flag to tell us if we want to clean the data
     *
     *
     * @param boolean TRUE = clean it
     */
    function set_cleanstring($flag=TRUE) {
        $this->_clean_string = $flag;
    }

    /**
     * return the value of the clean string flag
     *
     *
     * @return boolean
     */
    function get_cleanstring() {
        return $this->_clean_string;
    }

    /**
     * This method sets the flag to tell us
     * to show every row found in the DataListSource.
     *
     * @param boolean TRUE = show all rows
     */
    function set_showall($flag=TRUE) {
        $this->_show_all_rows = $flag;
    }

    /**
     * This returns the value of the show all rows
     * flag
     *
     * @return boolean
     */
    function get_showall() {
        return $this->_show_all_rows;
    }



    /**
     * This function is used to set up any
     * data that needs to be munged before the
     * data is fetched from the DataListSource
     *
     */
    function data_prefetch() {
        $this->_check_datasource("data_prefetch");

        if ( $this->expandrows() ) {
            if ($this->get_showall()) {
                $limit = -1;
            } else {
                $this->set_default_num_rows( $this->get_max_rows() );
                $this->set_numrows( $this->get_max_rows() );
                $limit = $this->numrows();
            }
        } else {
            $limit = $this->numrows();
        }

        //sanity check on the allowed sortable columns
        //this is to help prevent someone hacking the
        //orderby value.
        $this->pre_query_sanity_check();


        //now execute the query
        $this->_query_worked = $this->_datasource->query($this->offset(), $limit,
                                                         $this->orderby(), $this->reverseorder(),
                                                         $this->search_field(), $this->search_value(),
                                                         $this->simple_search_modifier_value(),
                                                         $this->search_type() );
    }


    /**
     * This method is used to do a sanity check on the data
     * that is about to be passed to the query for security
     * reasons and data type checks.
     *
     * This function is responsible for detecting any invalid
     * values and setting them to their defaults if they are
     * bogus to protect the query
     *
     * @return none
     */
    function pre_query_sanity_check() {
        //do a sanity check on the data
        $orderby = $this->orderby();
        $found = FALSE;
        foreach( $this->_columns as $column ) {
            if ($column['sortable'] && $column['data_name'] == $orderby) {
                $found=TRUE;
            }
        }

        if (!$found) {
            $this->set_orderby($this->_default_orderby);
        }
    }



    /*
     * Takes an array of (name, sortable, db_field, alignment,
     * size), with one element corresponding to each column.
     */
    function setup_columns() {
        $temp_headers = array();

        foreach( $this->_columns as $col_name => $data ) {
            if ( $data["sortorder"] == "reverse" ) {
                $data["reverseorder"] = "true";
            } else {
                $data["reverseorder"] = "false";
            }
            $temp_headers[$col_name] = $data;
        }
        $this->_columns = $temp_headers;
    }



    /**
     * general DataListSource object checker.
     *
     */
    function _check_datasource($function_name) {
        if ( !is_object($this->_datasource) ) {
            user_error("DataList::".$function_name."() - DataListSource object is not set");
            exit;
        }
    }


    /*********************************************/
    /*     REQUEST VARIABLE SECTION              */
    /*********************************************/



    /**
     * Function used to get the current
     * value of one of the control vars
     * for this class
     *
     * @param string - the name we want to get
     * @param mixed - the default value if not set
     * @return the current value or default if not set
     */
    function _get($name, $default_value=NULL) {
        if ( !isset($_REQUEST[$this->_vars[$name]]) ) {
            $this->_set($name, $default_value);
        }

        return $_REQUEST[$this->_vars[$name]];
    }

    /**
     * This function is used to set the
     * value of the control var
     *
     * @param string - the name we want to get
     * @param mixed - the new value for it.
     */
    function _set($name, $value) {
        $_REQUEST[$this->_vars[$name]] = $value;
    }

    /**
     * This function returns the current value
     * of the offset variable. This is an offset
     * into the query return data set.
     *
     * @return int - the current value.
     */
    function offset() {
        if ($this->get_showall() && $this->expandrows()) {
            return 0;
        } else {
            return (int)$this->_get("offsetVar", 0);
        }
    }

    /**
     * This function is used to set/change
     * the offset for this list.
     *
     * @param int - the new offset.
     */
    function set_offset($new_offset) {
        $this->_set("offsetVar", $new_offset);
    }

    /**
     * This function returns the value of the
     * current orderby variable.
     *
     * @return string.
     */
    function orderby() {
        return $this->_get("orderbyVar", $this->_default_orderby);
    }

    /**
     * This is used to reset the orderby
     *
     * @param string
     */
    function set_orderby($orderby) {
        $this->_set('orderbyVar', $orderby);
    }


    /**
     * This builds a query string var for the
     * orderby value.
     *
     * @return string - "orderby=(thevalue)"
     */
    function build_orderby_querystring() {
        $str = $this->_vars["orderbyVar"]."=".urlencode($this->orderby());
        return $str;
    }

    /**
     * This function returns the current value of
     * the reverse order member variable.
     *
     * @return string.
     */
    function reverseorder() {
        return $this->_get("reverseorderVar", $this->_default_reverseorder);
    }

    /**
     * This function sets the reverse order flag
     * to a new value.
     *
     * @param string - the new value.
     */
    function set_reverseorder($new_value) {
        $this->_set("reverseorderVar", $new_value);
    }

    /**
     * This builds a query string var for the
     * reverseorder value.
     *
     * @return string - "orderby=(thevalue)"
     */
    function build_reverseorder_querystring() {
        $str = $this->_vars["reverseorderVar"]."=".urlencode($this->reverseorder());
        return $str;
    }

    /**
     * This function returns the number of rows
     * that the query found.
     *
     * @return int - the number of rows
     */
    function numrows() {
        return(int)$this->_get("numrowsVar", $this->_default_rows_per_page);
    }

    /**
     * This function sets the # of rows to display
     * per page.
     *
     * @param int - the # of rows
     */
    function set_numrows($new_numrows) {
        $this->_set("numrowsVar", $new_numrows);
    }

    /**
     * returns the current value of
     * the search field name
     *
     * @return string
     */
    function search_field() {
        return $this->_get("search_fieldVar", '');
    }

    /**
     * This builds a query string var for the
     * searchfield value.
     *
     * @return string - "orderby=(thevalue)"
     */
    function build_searchfield_querystring() {
        $str = $this->_vars["search_fieldVar"]."=".urlencode($this->searchfield());
        return $str;
    }

    /**
     * returns the current value of
     * te search field value.
     *
     * @return string
     */
    function search_value() {
        return $this->_get("search_valueVar", '');
    }

    /**
     * This builds a query string var for the
     * searchfield value.
     *
     * @return string - "orderby=(thevalue)"
     */
    function build_searchvalue_querystring() {
        $str = $this->_vars["search_valueVar"]."=".urlencode($this->search_value());
        return $str;
    }

    /**
     * returns the current value of the
     * simple search modifier
     *
     * @return string
     */
    function simple_search_modifier_value() {
        return $this->_get("simple_search_modifierVar", '');
    }


    /**
     * returns the type of search being used
     *
     * @return string
     */
    function search_type() {
        return $this->_get("search_typeVar", "simple");
    }

    /**
     * This function sets the search type
     *
     * @param string - the search type
     *                 "simple" or "advanced"
     */
    function set_search_type($type) {
        $this->_set("search_typeVar", $type);
    }


    /**
     * returns the current value of the expandrows
     * flag.  This tells us if they want the entire
     * list of data back from the DB.
     *
     * @return string - the current value
     */
    function expandrows() {
        if ($this->get_showall()) {
            $default = 1;
        } else {
            $default = 0;
        }
        return(int)$this->_get("expandrowsVar", $default);
    }

    /**
     * This sets the expandrows.
     *
     * @param boolean
     */
    function set_expandrows($flag=TRUE) {
        $flag = ($flag ? 1:0);
        $this->_set("expandrowsVar", $flag);
    }

    /**
     * This is the basic function for letting us
     * do a mapping between the column name in
     * the header, to the value found in the DB.
     *
     * NOTE: this function is meant to be overridden
     *       so that you can push whatever you want.
     *
     * @param array - $row_data - the entire data for the row
     * @param string - $col_name - the name of the column header
     *                             for this row to render.
     * @return  mixed - either a HTMLTag object, or raw text.
     */
    function build_column_item($row_data, $col_name) {
        $key = $this->_columns[$col_name]["data_name"];

        if (!isset($row_data[$key]) || ($row_data[$key] == '' && $row_data[$key] !== 0)) {
            return " ";
        } else {
            return $row_data[$key];
        }
    }


    /**
     * This does some magic filtering on the data
     * that we display in a column.  This helps
     * to prevent nast data that may have html
     * tags in it.
     *
     * @param string - the column data u want to filter
     * @return string the cleaned/filtered data
     */
    function _filter_column_string($data) {
        return htmlspecialchars(trim($data));
    }


    /*******************************************/
    /*         FORM VARIABLES SECTION          */
    /*******************************************/

    /**
     * This function is used to set the
     * form name
     *
     * @param string
     */
    function set_form_name($name) {
        $this->_form_attributes["name"] = $name;
    }

    /**
     * This function is used to get
     * the form name
     *
     * @return string
     */
    function get_form_name() {
        return $this->_form_attributes["name"];
    }

    /**
     * This function is used to set the
     * form target
     *
     * @param string
     */
    function set_form_target($target) {
        $this->_form_attributes["target"] = $target;
    }

    /**
     * This function is used to get
     * the form target
     *
     * @return string
     */
    function get_form_target() {
        return $this->_form_attributes["target"];
    }

    /**
     * This function is used to set the
     * form method
     *
     * @param string (POST or GET)
     */
    function set_form_method($method) {
        if ( strcasecmp($method,"GET") !=0 && strcasecmp($method,"POST") !=0 ) {
            user_error("DataList::set_form_method() - INVALID Form method ".$method);
        } else {
            $this->_form_attributes["method"] = $method;
        }
    }

    /**
     * This function is used to get
     * the form method
     *
     * @return string (POST or GET)
     */
    function get_form_method() {
        return $this->_form_attributes["method"];
    }

    /**
     * Sets the form action
     *
     * @param string
     */
    function set_form_action($action) {
        $this->_form_attributes["action"] = $action;
    }

    /**
     * This function is used to get
     * the form action
     *
     * @return string (POST or GET)
     */
    function get_form_action() {
        return $this->_form_attributes["action"];
    }

    /**
    * Sets whether to the output into a form
    *
    * @param bool
    */
    function set_form_render($flag) {
        $this->_form_render_flag = $flag;
    }

    /**
    * Return the state of the form render
    *
    * @return bool
    */
    function get_form_render() {
        return $this->_form_render_flag;
    }

    /**
     * This function is used to set the
     * message displayed when no data is found
     *
     * @param string
     */
    function set_not_found_message($mesg) {
        $this->_not_found_message = $mesg;
    }

	/**
     * This function is used to get the
     * message displayed when no data is found
     *
     * @return string
     */
    function get_not_found_message() {
        return $this->_not_found_message;
    }


    /**
     * This function is used to set the value
     * of the _show_results_flag
     *
     * @param boolean - TRUE to show the results
     */
    function set_show_results( $flag=TRUE ) {
        $this->_show_results_flag = $flag;
    }


    /**
     * This function is used to let render() know
     * that we should show the results or not.
     *
     * @return boolean
     */
    function _show_results() {
        return $this->_show_results_flag;
    }

    /**
     * this method builds some hidden
     * form fields to automatically
     * be placed inside the form.
     *
     * This method returns a list of
     * hidden form fields if we are a POST.
     * It returns a portion of a query string
     * If we are a GET.
     *
     * @return mixed depending on form method
     */
    function _build_save_vars() {
        $container = container();
        foreach($this->_save_vars as $name => $value) {
            $container->add(form_hidden($name, $value));
        }
        return $container;
    }

    /**
     * This function sets the save variables
     * that the user/child wants to automatically
     * propogate
     *
     * @param array - name=>value pairs of the data
     *                that they want to propogate
     */
    function set_save_vars($vars) {
        $this->_save_vars = array_merge($this->_save_vars, $vars);
    }

    /**
     * This function builds the list of
     * default hidden form vars for when
     * the datalist is being rendered
     * as a POST
     *
     * @return Container
     */
    function _build_default_vars() {
        // the navigation links will set the offset anyway
        $container = container(form_hidden($this->_vars["offsetVar"], $this->offset()),
                               form_hidden($this->_vars["orderbyVar"], $this->orderby()),
                               form_hidden($this->_vars["reverseorderVar"], $this->reverseorder()),
                               form_hidden($this->_vars["expandrowsVar"], $this->expandrows()));
        return $container;
    }

    /**
     * This builds the base url used
     * by the column headers as well
     * as the page tool links.
     *
     * it basically builds:
     * $_SELF?$_GET
     *
     * @return string
     */
    function build_base_url() {

        $url = $_SERVER["PHP_SELF"]."?";

        if ( $this->get_form_method() == "POST" ) {
            return $url;
        }

        $vars = array_merge($_POST, $_GET);
        //request method independant access to
        //browser variables
        if ( count($vars) ) {
            //walk through all of the get vars
            //and add them to the url to save them.
            foreach($vars as $name => $value) {

                if ( $name != $this->_vars["offsetVar"] &&
                     $name != $this->_vars["orderbyVar"] &&
                     $name != $this->_vars["reverseorderVar"] &&
                     $name != $this->_vars["search_valueVar"]
                   ) {
                    if ( is_array($value) ) {
                        $url .= $name."[]=".implode("&".$name."[]=",$value)."&";
                    } else {
                        $url .= $name."=".urlencode(stripslashes($value))."&";
                    }
                }
            }
        }

        return $url;
    }

    /**
     * This function builds the 'tool' images that
     * allow  you to walk through the data list itself.
     * It provides image links for
     * first - go to the first page in the data list
     * prev - go to the previous page in the data list
     * next - go to the next page in the data list
     * last - go to the last page in the data list
     * all - show the rest of the list from the current offset
     *
     * @param string - which tool image to build
     * @return Object
     */
    function build_tool_link( $which ) {
        $num_pages = $this->get_num_pages();
        $cur_page = $this->get_current_page();
        $last_page = $this->get_last_page();

        $image_path = $this->get_image_path();
        switch ( $which ) {

        case "first":
            $rows_string = "First ".$this->get_default_num_rows()." Rows";
            if ( $this->offset() <= 0 ) {
                $obj = html_img($image_path."/first_group_button_inactive.gif",
                                '','',0,$rows_string, NULL, $rows_string . ": Disabled Link");
            } else {
                $url = $this->_build_tool_url(0);
                $obj = html_img_href($url, $image_path."/first_group_button.gif",
                                     '','',0, $rows_string, NULL, NULL, $rows_string);
            }
            break;

        case "prev":
            $rows_string = "Previous ".$this->get_default_num_rows()." Rows";
            if ( $this->offset() <= 0 ) {
                $obj = html_img($image_path."/prev_group_button_inactive.gif",
                                '','',0,$rows_string, NULL, $rows_string . ": Disabled Link");
            } else {
                $offset = $this->offset() - $this->numrows();
                if ( $offset < 0 ) {
                    $offset = 0;
                }
                $url = $this->_build_tool_url($offset);
                $obj = html_img_href($url, $image_path."/prev_group_button.gif",
                                     '','',0, $rows_string, NULL, NULL, $rows_string);
            }
            break;

        case "next":
            $rows_string = "Next ".$this->get_default_num_rows()." Rows";
            if ( ($num_pages == 1) || ($cur_page == $last_page) ) {
                $obj = html_img($image_path."/next_group_button_inactive.gif",
                                '','',0, $rows_string, NULL, $rows_string . ": Disabled Link");
            } else {
                $offset = $this->offset() + $this->numrows();
                $url = $this->_build_tool_url($offset);
                $obj = html_img_href($url, $image_path."/next_group_button.gif",
                                     '','',0, $rows_string, NULL, NULL, $rows_string);
            }
            break;

        case "last":
            $rows_string = "Last ".$this->get_default_num_rows()." Rows";
            if ( ($num_pages == 1) || ($cur_page == $last_page) ) {
                $obj = html_img($image_path."/last_group_button_inactive.gif",
                                '','',0, $rows_string, NULL, $rows_string . ": Disabled Link");
            } else {
                $offset = (int)(($num_pages - 1) * $this->numrows());
                $url = $this->_build_tool_url($offset);
                $obj = html_img_href($url, $image_path."/last_group_button.gif",
                                     '','',0, $rows_string, NULL, NULL, $rows_string);
            }
            break;

        case "expand":
            $offset = $this->offset();
            if ( $this->expandrows() ) {
                $url = $this->_build_tool_url($offset, TRUE, 0);
                $obj = html_img_href($url, $image_path."/close_group_button.gif",
                                     '','',0,"Collapse Rows", NULL, NULL, "Collapse Rows");
            } else {
                if ( ($num_pages == 1) ) {
                    $obj = html_img($image_path."/expand_group_button_inactive.gif",
                                    '','',0, "Expand Rows", NULL, "Expand Rows" . ": Disabled Link");
                } else {
                    $url = $this->_build_tool_url($offset, TRUE, 1);
                    $obj = html_img_href($url, $image_path."/expand_group_button.gif",
                                         '','',0,"Expand Rows", NULL, NULL, "Expand Rows");
                }
            }
            //so we don't save it into the mozilla navigation bar links
            unset($url);
            break;
        }

        if ( !empty($url) ) {
            $this->_save_mozilla_nav_link($which, $url);
        }

        return $obj;
    }

    /**
     * This function is used to build the url
     * for a tool link.
     * (first, prev, next, last, all)
     *
     * @param int - the offset for the link
     * @param boolean - add the expandrows value to the url
     * @param int - the expandrows value to use if the flag is on
     *
     * @return string
     */
    function _build_tool_url($offset, $expandrows_flag=FALSE, $expandrows_value=0) {
        if ( $this->get_form_method() == "POST" ) {
            $form_name = $this->get_form_name();
            $url = "javascript: document.".$form_name;
            $url .= ".".$this->_vars["offsetVar"].".value='".$offset."';";

            //add the expandrows variable to the post
            if ( $expandrows_flag ) {
                $form_field = $this->_vars["expandrowsVar"];
                $url .= "document.".$form_name.".";
                $url .= $form_field.".value='".$expandrows_value."';";
            }

            $url .= "document.".$form_name.".submit();";
        } else {
            $url = $this->build_base_url();
            $url .= $this->build_state_vars_query_string($offset, $expandrows_flag,
                                                         $expandrows_value);
        }
        return $url;
    }

    /**
     * this function is used to build a sub query string
     * of all of the query string vars to save the
     * state of the DBItemList.  This is used for pages
     * that want to come back to the list at the same state
     *
     * @param int - the offset for the link
     * @param boolean - add the expandrows value to the url
     * @param int - the expandrows value to use if the flag is on
     * @return string - name=value& pairs
     */
    function build_state_vars_query_string($offset, $expandrows_flag=FALSE,
                                           $expandrows_value=0) {
        $str = "";

        $str .= $this->_vars["offsetVar"]."=".urlencode($offset);
        $str .= "&".$this->_vars["orderbyVar"]."=".urlencode($this->orderby());
        $str .= "&".$this->_vars["reverseorderVar"]."=".urlencode($this->reverseorder());
        $str .= "&".$this->_vars["search_fieldVar"]."=".urlencode($this->search_field());
        $str .= "&".$this->_vars["search_valueVar"]."=".urlencode($this->search_value());
        $str .= "&".$this->_vars["simple_search_modifierVar"]."=".urlencode($this->simple_search_modifier_value());
        $str .= "&".$this->_vars["search_typeVar"]."=".urlencode($this->search_type());
        if ( $expandrows_flag ) {
            $str .= "&".$this->_vars["expandrowsVar"]."=".urlencode($expandrows_value);
        }

        return htmlentities($str);
    }

    /**
     * This function stores the url for each of the tool
     * urls, so we can push these out for mozilla.
     * Mozilla has a nice navigation bar feature that
     * lets you program first, prev, next, last links
     *
     * @param string - which tool link
     * @param string - the url for that link
     */
    function _save_mozilla_nav_link($which, $url) {
        $this->_mozilla_nav_links[$which] = $url;
    }


    /**
     * This function returns the path to the
     * images used in this class
     *
     * @return string
     */
    function get_image_path() {
        return $this->_image_path;
    }

    /**
     * This function returns the path to the
     * images used in this class
     *
     * @return string
     */
    function set_image_path($path) {
        return $this->_image_path = $path;
    }

    /**
     * This function returns the current
     * page that the item list is on.
     *
     * @return int
     */
    function get_current_page() {
        return((int) ($this->offset() / $this->numrows())) + 1;
    }

    /**
     * This function returns the #
     * of pages that are available
     * for this list of items.
     *
     * @return int
     */
    function get_num_pages() {
        $this->_check_datasource("get_num_pages");
        $total_rows = $this->_datasource->get_total_rows();

        if ($this->get_showall() && $this->expandrows()) {
            return 1;
        }

        $cnt = (int)($total_rows / $this->numrows());
        if ( (($total_rows % $this->numrows()) != 0) || ($total_rows == 0) ) {
            $cnt++;
        }
        return $cnt;
    }

    /**
     * This calculates the last page #
     * for this list of items
     *
     * @return int
     */
    function get_last_page() {
        return $this->get_num_pages();
    }

    /**
     * This function builds the string
     * that describes the current page
     * out of n pages the list is showing
     *
     * @return string (ie. 1 to 10 of 25)
     */
    function get_page_info() {
        $offset = $this->offset();
        //hack fix to fix a corner case.
        if ($offset > $this->_datasource->get_total_rows() ) {
            $this->set_offset(0);
        }

        $cur_page = $this->get_current_page();
        $low_range = $this->offset() + 1;
        $num_pages = $this->get_num_pages();

        $this->_check_datasource("get_page_info");
        $total_rows = $this->_datasource->get_total_rows();

        if ($this->get_showall() && $this->expandrows()) {
            $num_rows_per_page = $total_rows;
        } else {
            $num_rows_per_page = $this->numrows();
        }

        $high_range = $low_range + ($num_rows_per_page - 1);
        if ( $high_range > $total_rows ) {
            $high_range = $total_rows;
        }

        if ( $total_rows == 0 ) {
            $str = "0 of 0";
        } else {
            $str  = $low_range . " to ". $high_range;
            $str .= " of ".$total_rows;
        }

        return $str;
    }



    /**
     * This builds a url for a particular
     * column header.
     *
     * @param string - $col_name
     * @return Atag object;
     */
    function build_column_url($col_name) {
        $orderby = $this->orderby();
        $reverseorder = $this->reverseorder();
        $search_value = $this->search_value();

        $order_value = $this->_columns[$col_name]["data_name"];
        $reverse_value = "false";
        if ( !$reverseorder ) {
            $reverseorder = 'false';
        }

        if ( $orderby == $order_value && $reverseorder === 'false' ) {
            $reverse_value = "true";
        } else if ($orderby != $order_value && $this->_default_reverseorder === 'true') {
            //This is the case where the user wants the default ordering for
            //columns to be reversed...DESCENDING instead of ASCENDING
            $reverse_value = 'true';
        }

        if ( $this->get_form_method() == "POST" ) {
            //we have to construct this url
            //specially.
            $form_name = $this->get_form_name();

            $url = "javascript: ";
            //set the offset correctly
            $url .= "document.".$form_name.".".$this->_vars["offsetVar"].".value='".$this->offset()."';";
            //set the orderby correctly.
            $url .= "document.".$form_name.".".$this->_vars["orderbyVar"].".value='".$order_value."';";
            //set the reverseorder
            $url .= "document.".$form_name.".".$this->_vars["reverseorderVar"].".value='".$reverse_value."';";

            $url .= "document.".$form_name.".submit();";
        } else {
            //handle the normal get.
            $url = $this->build_base_url();
            //Now add the orderby, reverseorder and offset vars
            $url .= $this->_vars["offsetVar"] ."=0&";
            //set the orderbyvar
            $url .= $this->_vars["orderbyVar"] ."=".$order_value."&";
            //set the reverseorder
            $url .= $this->_vars["reverseorderVar"] ."=".$reverse_value."&";
            //set the search value
            $url .= $this->_vars["search_valueVar"] ."=".$search_value;
        }

        return htmlentities($url);
    }

    /**
     * This does some magic filtering on the data
     * that we display in a column.  This helps
     * to prevent nast data that may have html
     * tags in it.
     *
     * @param string - the column data u want to filter
     * @return string the cleaned/filtered data
     */
    function filter_column_string($data) {
        return htmlspecialchars(trim($data));
    }



    /**
     * This function is used to make sure that the string we are
     * placing in a cell has been "cleaned"
     *
     * @param mixed - the cell object.  It can be a string.
     * @param string - the name of the column this object/string
     *                 will live
     *
     * @return mixed - the cleaned string or object
     */
    function _clean_string($obj, $col_name) {
        if ( is_string($obj) ) {
            if ( $this->_columns[$col_name]["maxtextlength"] ) {
                //looks like we need to make sure we
                //truncate the string to a max length
                if ( strlen($obj) > $this->_columns[$col_name]["maxtextlength"] ) {
                    //we need to truncate it and
                    //add a hover title attribute for the full
                    //object
                    $obj = new SPANtag(array("title"=>$this->_filter_column_string($obj)),
                                       $this->_filter_column_string(substr($obj, 0, $this->_columns[$col_name]["maxtextlength"]) . "..."));
                } else {
                    $obj = $this->_filter_column_string($obj);
                }
            } else {
                $obj = $this->_filter_column_string($obj);
            }
        }
        return $obj;
    }

    /********************************/
    /*      SEARCH RELATED          */
    /********************************/

    /**
     * This method gets the array of
     * searchable header fields (columns)
     *
     * @return array
     */
    function _get_searchable_fields() {
        $fields = array();
        foreach($this->_columns as $name => $header) {
            if ( $header["searchable"] == SORTABLE ||
                 $header["searchable"] == SORTABLE_ICASE ||
                 $header["searchable"] == SORTABLE_NUMERIC) {
                $fields[$name] = $header["data_name"];
            }
        }
        return $fields;
    }

    /**
     * This builds the simple search modifier
     * select box.
     *
     * @return INPUTtag object.
     */
    function _build_simple_search_modifier() {

        $options = array();

        $modifier = $this->get_simple_search_modifier();

        if ( $modifier & SEARCH_BEGINS_WITH ) {
            $options["beginning with"] = "BEGINS";
        }
        if ( $modifier & SEARCH_CONTAINS ) {
            $options["containing"] = "CONTAINS";
        }
        if ( $modifier & SEARCH_EXACT ) {
            $options["matching"] = "EXACT";
        }
        if ( $modifier & SEARCH_ENDS_WITH ) {
            $options["ending with"] = "ENDS";
        }

        $selected = $this->simple_search_modifier_value();
        //make the default Begins with
        if ( !$selected ) {
            $selected = "BEGINS";
        }

        return form_select($this->_vars["simple_search_modifierVar"], $options, $selected);
    }

    /**
     * This function is used to make safe
     * any query string value that is used
     *
     * @param string
     * @return string
     */
    function search_value_filter( $value ) {
        return stripslashes( trim($value) );
    }


    /**
     * This function is used to set the debug
     * level.
     *
     * @param mixed
     * @return none
     */
    function set_debug($level=FALSE) {
        $this->_debug = $level;
        //make sure the datasource is set
        $this->_check_datasource('set_debug');
        $this->_datasource->set_debug($level);
    }
}
?>
