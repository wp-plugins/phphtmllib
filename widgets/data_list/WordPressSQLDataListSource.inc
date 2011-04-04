<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This file contains the SQLDataListSource child class
 * that uses the WordPress DB object to talk to the DB.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 */

/**
 * Must have WordPress config and database class.
 *
 * ABSPATH must be defined, it is defined by WordPress.
 */
require_once(ABSPATH . "/wp-config.php");
require_once(ABSPATH . "/wp-includes/wp-db.php");

/**
 * This class requires the SQLDataListSource parent class
 *
 */
include_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/SQLDataListSource.inc");

/**
 * This SQLDataListSource child class interacts with
 * with the specific DB via the php WordPress DB abstraction
 * objects.
 *
 * How to use?
 * in the DataList child's get_data_source() method
 * you pass in the already connected WordPress DB object
 * in to the constructor.  WordPressSQLDataListSource
 * takes care of the rest.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 */
class WordPressSQLDataListSource extends SQLDataListSource
{
	/**
	 * This var holds the Database object
	 * that is used to do the sql queries
	 * It is assumed that the db is already
	 * connected to, and the object provides
	 * 2 methods:
	 * query() - execute a sql query
	 */
	var $_db = NULL ;

	/**
	 * this holds the query result from the wpdb->query() call
	 *
	 */
	var $_result = NULL ;

	/**
	 * this holds the index into the query result array
	 *
	 */
	var $_resultIndex = 0 ;

	/**
	 * The constructor is used to pass in the
	 * WordPress DB object that has already been
	 * created and connected to the db.
	 *
	 * @param wpdb object - MUST BE CONNECTED
	 */
	function WordPressSQLDataListSource( &$db ) {
		$this->set_db_object( $db );
	}
	
	/**
     * Set the DB object we will use
     * to talk to the DB.
     *
     * @param  object - $db the babw_db object.
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
    function do_query()
    {
		$this->_result = $this->_db->get_results($this->_query, ARRAY_A) ;

        //if (!$this->_result)
        if ($this->_db->last_error != '')
        {
            $query = $this->_query;
			user_error("WordPressSQLDataListSource::do_query($query) - query failed.") ;
            return false ;
        }
        else
        {
            $this->_resultIndex = 0 ;

            return true ;
        }
	}

	

	/**
	 * This function gets the next data row
	 * from the query()
	 *
	 * @return array()
	 */
    function get_next_data_row()
    {
        $ndr = null ;

        if (isset($this->_result[$this->_resultIndex]))
        {
            $ndr = $this->_result[$this->_resultIndex++] ;
        }

        return $ndr ;
	}

	/**
     * This function builds the limit
     * clause portion of a DB query.
     *
     * @return string - the limit portion of
     *                  the query.
     */
    function build_limit_clause($offset, $limit)
    {
        if ($this->get_limit() != -1 )
        {
            if ($offset == '' || $offset == "none")
            {
				$offset = 0 ;
			}

            switch(get_class($this->_db))
            {
			    case "db_mysql":
				    $clause = " LIMIT $offset, $limit " ;
				    break ;

			    default:
				    $clause = " LIMIT $offset, $limit " ;
				    break ;
			}

            return $clause ;
        }
        else
        {
            return null ;
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
    function count($tables, $where_clause='', $count_clause='*')
    {
        $query = "SELECT COUNT(".$count_clause.") 
            AS xxCOUNTxx FROM ".$tables." ".$where_clause;

        $result = $this->_db->get_var($query) ;

        if (is_null($result))
        {
			user_error("WordPressSQLDataListSource::count() - query failed.") ;
            return 0 ;
        }
        else
        {
            return $result ;
        }		
    }
}

?>
