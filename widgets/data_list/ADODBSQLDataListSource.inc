<?php

/**
 * This file contains the SQLDataListSource child class
 * that uses the ADODB DB object to talk to the DB.
 *
 * you can check out ADODB from
 * http://php.weblogs.com/ADODB
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */

/**
 * This requires the SQLDataListSource
 * parent class
 *
 */
include_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/SQLDataListSource.inc");

/**
 * NOTE:
 * You'll need to include the base
 * ADODB include file prior to using this
 * file.
 * include_once( 'adodb.inc.php' );
 *
 */


/**
 * This SQLDataListSource child class interacts with
 * with the specific DB via the php ADODB DB abstraction
 * objects.
 *
 * How to use?
 * in the DataList child's get_data_source() method
 * you pass in the already connected PEAR DB object
 * in to the constructor.  PEARSQLDataListSource
 * takes care of the rest.
 *
 */
class ADODBSQLDataListSource extends SQLDataListSource {

	/**
	 * This var holds the Database object
	 * that is used to do the sql queries
	 * It is assumed that the db is already
	 * connected to, and the object provides
	 * 2 methods:
	 * query() - execute a sql query
	 */
	var $_db = NULL;

	/**
	 * this holds the query result from the
	 * PEAR::DB->query() call
	 *
	 */
	var $_result = NULL;


	/**
	 * The constructor is used to pass in the
	 * PEAR DB object that has already been
	 * created and connected to the db.
	 *
	 * @param ADONewConnection::Execute object - MUST BE CONNECTED
	 */
	function ADODBSQLDataListSource( &$db ) {
		$this->set_db_object( $db );
	}
	
	/**
     * Set the DB object we will use
     * to talk to the DB.
     *
     * @param   object - $db the babw_db object.
     *
     */
    function set_db_object( &$db ) {
        $this->_db = &$db;
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
		$this->_result = $this->_db->SelectLimit($this->_query,
												 $this->get_limit(),
												 $this->get_offset());
		if (!$this->_result) {
			$msg = $this->_db->ErrorMsg();
			user_error("ADODBSQLDataListSource::do_query() - query failed : ".$msg);
            return false;
		} else {
            return true;
        }
	}

	

	/**
	 * This function gets the next data row
	 * from the query()
	 *
	 * @return array()
	 */
	function get_next_data_row() {
		return $this->_result->FetchRow();
	}

	/**
     * This function builds the limit
     * clause portion of a DB query.
     *
     * @return string - the limit portion of
     *                  the query.
     */
    function build_limit_clause($offset, $limit) {
        return NULL;
    }

    /**
     * find the number of rows to be returned
     * from a query from a table and where clause
     *
     * @param string $table - the table to count from
     * @param string $where_clause - a where clause
     *
     * @return int the # of rows
     */
    function count($tables, $where_clause='', $count_clause='*') {
		$query = "select count(".$count_clause.") as XXCOUNTXX from ".$tables." ".$where_clause;
        $result = $this->_db->Execute($query);
		if (!$result) {
			$msg = $this->_db->ErrorMsg();
			user_error("ADODBSQLDataListSource::count() - query failed : ".$msg);
		}
		$value = $result->FetchRow();
        return ($value ? (int)$value["XXCOUNTXX"] : NULL);
    }

}

?>
