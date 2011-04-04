<?php
/**
 * $Id: PEARDB_DataObjectDataListSource.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
  * DB_DataObjectDataListSource.php - contains the
  * {@link DB_DataObjectDataListSource} class
  * @author     Daniel I. Robert    <robert@osuosl.org>
  * @package    phpHtmlLib
  */

/**
  * Require the parent class
  */
require_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/SQLDataListSource.inc");

/**
  * This class provides DB abstraction for phpHtmlLib datalists
  * using DB_DataObjects as the interface
  *
  * @package    phpHtmlLib
  */
class PEARDB_DataObjectDataListSource extends SQLDataListSource {
    /** The DB_DataObject used for this source */
    var $_dbdo;

    /** List of variables to return in get_next_data_row() */
    var $_vars;
    var $count = 0;


    /**
      * Constructor
      *
      * @param  DB_DataObject source for the datalist
      */
    function PEARDB_DataObjectDataListSource( &$db ) {
        $this->_dbdo = $db;
        $this->_vars = array();
    }


    /* Overloads from DataListSource */

    /**
      * Add a column of data to manage
      *
      * @param  string  title of this column
      * @param  string  name of the associated column in the database table
      * @param  boolean is the column sortable? default: FALSE
      * @param  boolean is the column searchable? default: FALSE
      * @param  string  the sort order (ASC, DESC) default: ASC
      */
    function add_column($title, $data_name, $sortable=FALSE,
                        $searchable=FALSE, $sortorder="ASC") {
        $this->_vars[] = $data_name;

        parent::add_column($title, $data_name, $sortable=FALSE,
                           $searchable=FALSE, $sortorder="ASC");
    }

    /* Required Overloads */

    /**
      * Perform the query on the database (executes DB_DataObject's ->find() method)
      *
      * @return int number of rows in result set
      */
    function do_query() {
        //DB_DataObject::debugLevel(3);
        return $this->_dbdo->find();
    }


    /**
      * Return the next row of the matching result set as an array.
      * This method relies on DB_DataObject's ->toArray() method, which
      * calls ->getVarname() on each relevant variable.
      *
      * @return array   array of varname=>display_string representing a db row
      */
    function get_next_data_row() {
        if ( $this->_dbdo->fetch() )
            return $this->_dbdo->toArray();
        else
            return array();
    }


    /* Overloads from SQLDataSource */


    /**
      * Although technically overloading setup_db_functions from
      * SQLDataListSource, we're using this function to set DB_DataObject
      * values using the native ->setFrom() method
      *
      * @param  array   array of values
      */
    function setup_db_options($opts) {
        $this->_dbdo->setFrom($opts);
    }


    /**
      * Calls a bunch of helper functions to setup the internal
      * DB_DataObject for the desired query.
      *
      * @param  boolean set a limit on the result size?  default: TRUE
      */
    function build_query($limit_flag=TRUE) {
        $this->build_where_clause();
        $this->build_order_clause();
        $this->build_groupby_clause();

        // now, get the total rows before we add the limit
        $this->set_total_rows($this->count());

        if ( $limit_flag )
            $this->build_limit_clause($this->get_offset(), $this->get_limit());

        // for compatibility
        return 'query';
    }

    /**
      * Add an SQL WHERE condition to the query.  This is done using DB_DAtaObject's
      * ->whereAdd() method
      */
    function build_where_clause() {
        // build the where clause
        $where_clause = $this->_db_options['where_clause'];
        if ( $where_clause )
            $this->_dbdo->whereAdd($where_clause);

        // build the search clause
        $search_clause = $this->build_search_clause();
        if ( $search_clause )
            $this->_dbdo->whereAdd($search_clause);
    }


    /**
      * Set the order of the results.  This is done using DB_DataObject's
      * ->orderBy() method
      */
    function build_order_clause() {
        // clear the previous order
        $this->_dbdo->orderBy();

        // set up the order
        $order_clause = parent::build_order_clause();

        if ( $order_clause )
            $this->_dbdo->orderBy($order_clause);
    }


    /**
      * Helper function for build_order_clause
      *
      * @access private
      * @param  string  database column to order by
      * @param  string  'true' for DESC order
      * @param  boolean ignore case for orderBy clause? default: FALSE
      * @return string  clause to go inside ->orderBy()
      */
    function setup_order($orderby, $reverseorder, $icase_sort=FALSE) {
        if ( $icase_sort )
            $orderby_clause = "lower($orderby)";
        else
            $orderby_clause = $orderby;

        $orderby_clause .= ($reverseorder == 'true') ? ' DESC' : ' ASC';

        $secondary = $this->get_secondary_orderby();

        if ( count($secondary) > 0 )
            $oderby_clause .= ','.implode(',', $secondary);

        return $orderby_clause;
    }


    /**
      * Build a groupBy clause.  This uses DB_DataObject's ->groupBy() method
      */
    function build_groupby_clause() {
        // clear the previous groupby
        $this->_dbdo->groupBy();

        if ( $this->_db_options['groupby_clause'] )
            $this->_dbdo->groupBy($this->_db_options['groupby_clause']);

    }


    /**
      * Build a limit on the number of results.  Uses DB_DataObject's ->limit()
      */
    function build_limit_clause($offset, $limit) {
        // clear the previous
        $this->_dbdo->limit();

        if ( !$offset )
            $offset = 0;

        $limit_clause = $offset;

        if ( $limit )
            $this->_dbdo->limit($offset, $limit);
        else
            $this->_dbdo->limit($offset);

    }


    /**
      * Count the number of matching rows in the database.  This simply returns
      * the result of a DB_DataObject ->find() command operating on a clone of
      * the internal DB_DataObject (this->_dbdo)
      *
      * @return int number of matching results
      */
    function count() {
        // make a copy of the DBDO, but reset the limits
        // clone works because it is defined in DB_DataObject
        $copy = clone($this->_dbdo);
        //$copy->limit();
        $count = $copy->find();
        unset($copy);
        return $count;
    }


    /* Getters */

    /**
     *  Returns the DBDO object
     *
     *  @return DB_DataObject   $_dbdo  The stored DB_Dataobject
     */
    function get_dbdo() {
        return $this->_dbdo;
    }
}
?>
