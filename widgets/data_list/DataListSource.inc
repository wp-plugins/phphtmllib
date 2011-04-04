<?php

/**
 * This file contains the Base DataListSource
 * class which abstracts the data fetching/sorting
 * from the DataList.
 *
 *
 * $Id: DataListSource.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */



/**
 *
 *  This is the base class for managing data for
 * the DataList class.  This abstracts away the
 * underlying data layer from the DataList, so
 * the data can come from multiple sources.
 * Most of the time the data will come from a
 * data base such as Mysql or Oracle.  This
 * abstraction enables the data to also come from
 * a tab delimited file, xml, php array
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class DataListSource {

    /**
     * The column descriptions
     * for the data we are working on
     *
     * @var array
     */
    var $_columns = array();


    /**
     * This holds various parameters relating
     * to the query of the data
     *
     */
    var $_query_params = array("num_total_rows" => 0,
                               "offset" => 0,
                               "limit" => -1,
                               "orderby" => '',
                               "secondaryorderby" => array(),
                               "reverseorder" => '',
                               "searchby" => '',
                               "searchvalue" => '',
                               "searchmodifier" => '',
                               "searchtype" => 'simple');

    /**
     * Holds the index into the array of data
     * so we can keep track of where we are
     * when we are walking the array
     * (only usefull for non DB children)
     *
     */
    var $_data_index = 0;

    /**
     * A placeholder for data that is read/built
     * and stored locally.  Not all data sources
     * have to use this.
     * Each entry in the array corresponds to 1 row
     * of data.
     */
    var $_data = array();

    /**
     * debugging flag for debugging queries.
     *
     */
    var $_debug = FALSE;

    /**
     *
     * The constructor
     */
    function DataListSource() {

    }

    /**
     * The main external API methods
     * that are used by the DataList
     * Class
     *
     */

    /**
     * Add a column of data to manage
     *
     * @param string - the title of the column
     * @param string - the data value name
     * @param boolean - is the column sortable?
     *                  default: FALSE
     * @param boolean - is the column searchable
     *                  default: FALSE
     * @param string - the sort order (ASC, DESC)
     *                 default: ASC
     */
    function add_column( $title, $data_name, $sortable=FALSE,
                          $searchable=FALSE, $sortorder="ASC") {
        $col = array();
        $col["data_name"] = $data_name;
        $col["sortable"] = $sortable;
        $col["searchable"] = $searchable;
        $col["sortorder"] = $sortorder;
        $col["reverseorder"] = false;

        $this->_columns[$title] = $col;
    }


    /**
     * The main Query function.
     * This function is responsible for doing
     * any data prefetching from a db,file
     * and doing any sorting and searching
     * on it depending on the values passed
     * in from the DataList object
     *
     * @param int - the offset into the data set
     * @param int - the # of rows to get
     * @param string - the column to order the data by
     * @param string - order in asc or reverse?
     * @param string - the column in the dataset
     *                 to search by
     * @param string - the value to look for
     * @param string - the simple search modifier.
     *
     */
    function query($offset, $limit, $orderby, $reverseorder,
                   $searchby, $searchby_value,
                   $simplesearch_modifier, $search_type ) {
        $this->set_offset($offset);
        $this->set_limit($limit);
        $this->set_orderby($orderby);
        $this->set_reverseorder($reverseorder);
        $this->set_searchby($searchby);
        $this->set_searchby_value($searchby_value);
        $this->set_simplesearch_modifier( $simplesearch_modifier );
        $this->set_search_type( $search_type );

        //now call child methods

        //do any pre query setup
        //This depends on the source of the data
        //but an example would be to build a
        //sql query string if the source is a database
        //or to validate/open a file from disk if the
        //source is a file.
        //or to do any checks on a memory cache
        //if the data source is a sysvshm segment.
        $this->do_prequery();

        //do the actual data fetching/sorting
        return $this->do_query();
    }

    /**
     * This function gets the next data row
     * from the query()
     *
     * @return array()
     */
    function get_next_data_row() {
       user_error("DataListSource::get_next_data_row() - Child must override");
    }

    /**
     * This is called by the DataList object to allow
     * us a chance to run the next row through a filter
     *
     * @param array - the row to run through the filter
     * @return boolean - TRUE = allow the row. FALSE = drop it.
     */
    function row_filter(&$row_data) {
        return TRUE;
    }


    /**
     * This is a method that should be defined by the
     * child class to do any pre-query type of things.
     * Such as building a sql query string for a DB,
     * or checking to make sure the file on disk exists
     * if the source is a file on disk.
     *
     */
    function do_prequery() {
        user_error("DataListSource::do_prequery() - Child must override");
    }


    /**
     * This is the function that does the data fetching,
     * and sorting if needed.
     * If the source is a sql database, this is where the
     * query gets called.  This function doesn't actually read the
     * data from the DB yet.  That is what get_next_data_row()
     * does.
     *
     * @return boolean - the query passed/failed.
     */
    function do_query() {
        user_error("DataListSource::do_query() - Child must override");
        return false;
    }

    /**
     * A generic method API that can be used at the bottom
     * half of the do_query() method to sort data that is
     * stored locally.  This is only needed when the source
     * is a non database.
     *
     * It should operate on the $this->_data array
     */
    function sort() {
    }


    /**
     * This returns the total number of rows
     * in our entire data set
     *
     * @return int
     */
    function get_total_rows() {
        return $this->_query_params["num_total_rows"];
    }

    /**
     * This is used to set the total # of
     * rows we have in our data set
     *
     * @param int
     */
    function set_total_rows($num) {
        $this->_query_params["num_total_rows"] = $num;
    }


    /**
     * This sets the offset value
     * and resets the index into the data
     * array (in non DB children)
     *
     * @param int offset
     */
    function set_offset($offset) {
        $this->_query_params["offset"] = $offset;
        $this->_data_index = $offset;
    }

    /**
     * This function returns the value of the
     * offset
     *
     * @return int
     */
    function get_offset() {
        return $this->_query_params["offset"];
    }

    /**
     * This sets the orderby column name.
     * This corresponds to the column
     * that wants to be sorted/ordered, but
     * not the actual direction (asc, desc)
     *
     * @param int offset
     */
    function set_orderby($orderby) {
        $this->_query_params["orderby"] = $orderby;
    }

    /**
     * This function returns the value of the
     * orderby
     *
     * @return int
     */
    function get_orderby() {
        return $this->_query_params["orderby"];
    }

    /**
     * This sets the flag that tells us the
     * direction in which to order the orderby
     * column.
     *
     * @param int offset
     */
    function set_reverseorder($order) {
        $this->_query_params["reverseorder"] = $order;
    }

    /**
     * This function returns the value of the
     * reverseorder
     *
     * @return int
     */
    function get_reverseorder() {
        return $this->_query_params["reverseorder"];
    }

    /**
     * This sets the column that we want to search
     * from.
     *
     * @param int offset
     */
    function set_searchby($search_col) {
        $this->_query_params["searchby"] = $search_col;
    }

    /**
     * This function returns the value of the
     * searchby
     *
     * @return int
     */
    function get_searchby() {
        return $this->_query_params["searchby"];
    }

    /**
     * This sets the data that we want to search
     * for.
     *
     * @param int offset
     */
    function set_searchby_value($search_value) {
        $this->_query_params["searchvalue"] = $search_value;
    }

    /**
     * This function returns the value of the
     * search value
     *
     * @return int
     */
    function get_searchby_value() {
        return $this->_query_params["searchvalue"];
    }

    /**
     * This sets the simple search modifier
     *
     *
     * @param int offset
     */
    function set_simplesearch_modifier($search_modifier) {
        $this->_query_params["searchmodifier"] = $search_modifier;
    }

    /**
     * This function returns the value of the
     * search value
     *
     * @return int
     */
    function get_simplesearch_modifier() {
        return $this->_query_params["searchmodifier"];
    }

    /**
     * This function is used to set
     * the limit value, which limits
     * the # of rows of data to allow
     * to return
     */
    function set_limit( $limit ) {
        $this->_query_params["limit"] = $limit;
    }

    /**
     * This function gets the current
     * value of the limit value
     *
     * @return int
     */
    function get_limit() {
        return $this->_query_params["limit"];
    }


    /**
     * This function sets the search type
     * (simple or advanced)
     *
     * @param string
     */
    function set_search_type( $search_type ) {
        $this->_query_params["searchtype"] = $search_type;
    }

    /**
     * this function returns the current search type
     * for the DataList query
     *
     * @return string
     */
    function get_search_type() {
        return $this->_query_params["searchtype"];
    }

    /**
     * This method is used to set a secondary
     * list of columns to order/sort by.
     *
     * @param mixed - n numbers of column names
     *                to order by
     */
    function set_secondary_orderby() {
        $this->_query_params["secondaryorderby"] = func_get_args();
    }

    /**
     * This gets the list of secondary order by
     * columns.
     *
     * @return array
     */
    function get_secondary_orderby() {
        return $this->_query_params["secondaryorderby"];
    }

    /**
     * This function returns the
     * data_index value and increments it
     *
     * @return int
     */
    function get_data_index() {
        $this->_data_index++;
        return $this->_data_index-1;
    }

    /**
     * This function determines if the column
     * associated w/ a data_name is sortable
     * or not
     *
     * @param string - the data_name filed in the
     *                 _columns array to look for
     * @return boolean - is that column sortable?
     */
    function _is_column_sortable( $data_name ) {
        foreach( $this->_columns as $name => $data ) {
            if ($data["data_name"] == $data_name &&
                ($data["sortable"] == SORTABLE ||
                 $data["sortable"] == SORTABLE_ICASE ||
                 $data["sortable"] == SORTABLE_NUMERIC)) {
                return TRUE;
            }
        }
        return FALSE;
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
    }
}
?>
