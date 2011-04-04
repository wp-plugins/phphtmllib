<?php

/**
 * This file contains the SQLDataListSource child class
 * that uses PHP PostgreSQL functions. Quick hack of PEARDataListSource.inc
 *
 * @author  Aris Basic <aris.basic@silencesoftware.com>
 * @author  Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */

/**
 * This requires the SQLDataListSource
 * parent class
 *
 */
include_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/SQLDataListSource.inc");

/**
 * This SQLDataListSource child class interacts with
 * with a PostgreSQL Database using built in pg_*
 * calls.  This assumes  that you have PostgreSQL 
 * support compiled into PHP
 *
 * How to use?
 * in the DataList child's get_data_source() method
 * you pass in the result of the pg_connect() call
 * to the constructor.
 *
 * @author  Aris Basic <aris.basic@silencesoftware.com>
 * @author  Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class PGSQLDataListSource extends SQLDataListSource {

    /**
     * This var holds the Database connection reference
     * that is used to do the sql queries
     * It is assumed that the db is already
     * connected to and is valid postgresi connection reference
     */
    var $_db = NULL;

    /**
     *  Result of pg_query()
     */
    var $_result = NULL;


    /**
     * The constructor is used to pass in the
     * postgres connection reference
     *
     * @param result of pg_connect() 
     */
    function PGSQLDataListSource( $db ) {
        $this->set_db_object( $db );
    }

    /**
     * Set the DB object we will use
     * to talk to the DB.
     *
     * @param   object - $db the babw_db object.
     *
     */
    function set_db_object( $db ) {
        $this->_db = $db;
    }

    function do_query() {
        $this->_result = pg_query($this->_db,$this->_query);
        if ( pg_result_status($this->_result)>4 ) {
            $msg = pg_result_error($this->_result);
            user_error("PGSQLDataListSource::pg_query() - query failed : ".$msg);
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
        return pg_fetch_assoc($this->_result);
    }

    /**
     * This function builds the limit
     * clause portion of a DB query.
     *
     * @return string - the limit portion of 
     *                  the query.
     */
    function build_limit_clause($offset, $limit) {
        if ( $this->get_limit() != -1 ) {
            if ( $offset == '' || $offset == "none" ) {
                $offset = 0;
            }
            $clause = " LIMIT $limit OFFSET $offset ";
            return $clause;
        } else {
            return NULL;
        }
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
        $query = "select count(".$count_clause.") as \"COUNT\" from ".$tables." ".$where_clause;
        $result = pg_query($this->_db,$query);
        if ( pg_result_error($result)>4 ) {
            $msg = pg_result_error($result);
            user_error("PGSQLDataListSource::count() - query failed : ".$msg);
        }
        $value = pg_fetch_assoc($result);
        return($value ? (int)$value["COUNT"] : NULL);
    }

}

?>
