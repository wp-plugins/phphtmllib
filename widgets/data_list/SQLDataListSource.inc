<?php
/**
 * This file holds the DataListSource child that can
 * handle working with SQL databases.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */

/**
 * We require the DataListSource
 */
require_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/DataListSource.inc");

/**
 *
 */
class SQLDataListSource extends DataListSource {

	/**
	 * this holds all of the options
	 * that make up the sql query
	 *
	 */
	var $_db_options = array("values" => "",
							 "tables" => "",
							 "where_clause" => "",
							 "groupby_clause" => "",
							 "count_column" => "*");

	/**
	 * The entire query built by
	 * build_query()
	 */
	var $_query = "";


    /**
     * The flag that tells us to use
     * case sensitive order by as a default.
     *
     * NOTE: we are case sensitive by default
     *
     */
    var $_default_order_sensitivity = TRUE;


    /**
     * The flag to make the simple search where
     * clause case insensitive for the search column.
     *
     * NOTE: we are case insensitive by default
     */
    var $_simple_search_case_insensitive = TRUE;


    /**
     * Set which DB options
     * to use for this list.
     *
     * @param string - $values - the values you
     *                           want to select
     *                           from the db table(s)
     * @param string - $tables - The tables you want
     *                           to select on.
     * @param string - $where_clause - portion of the where
     *                                 clause.
     *                                 This expects name=value
     *                                 pairs only.
     * @param string - $groupby_clause - the groupby portion of the
     *                                   query.  same format as where_clause
     *
     */
    function setup_db_options( $values, $tables, $where_clause='',
                               $groupby_clause='' ) {
        $this->set_db_values( $values );
        $this->set_db_tables( $tables );
        $this->set_db_where_clause( $where_clause );
        $this->set_db_groupby_clause( $groupby_clause );
    }

    /**
     * Set the values we want to select
     * from the db.
     *
     * @param string - $values
     */
    function set_db_values( $values ) {
        $this->_db_options["values"] = $values;
    }

	/**
	 * This function returns the
	 * values we need to search for
	 * in the sql query
	 *
	 * @return string
	 */
	function get_db_values() {
		return $this->_db_options["values"];
	}

    /**
     * Set the tables from the DB you
     * want to select on.
     *
     * @param   string - $tables
     */
    function set_db_tables( $tables ) {
        $this->_db_options["tables"] = $tables;
    }

	/**
	 * returns the table(s) used in the query
	 *
	 * @return string
	 */
	function get_db_tables() {
		return $this->_db_options["tables"];
	}

    /**
     * Set the user portion of the where
     * clause.
     * @param string - name value pairs
     */
    function set_db_where_clause( $where_clause ) {
        $this->_db_options["where_clause"] = $where_clause;
    }

    /**
     * Sets the groupby clause for the query
     *
     * @param string name value pairs
     */
    function set_db_groupby_clause( $clause ) {
        $this->_db_options["groupby_clause"] = $clause;
    }

    /**
     * This function changes the counted column.
     * By default, we use count(1)
     * But sometime you need count(distinct KEY) for example
     *
     */
    function set_count_column($var) {
        $this->_db_options["count_column"] = $var;
    }

	/**
	 * this returns the current count column
	 *
	 * @return string
	 */
	function get_count_column() {
		return $this->_db_options["count_column"];
	}

    // This functions joins an arbitrary number of clauses using the
    // specified connector. It can be used in one of the following two
    // ways:
    //      join($connector, $clause_1, $clause_2, ...);
    //      join($connector, $clauses_array);
    //
    function join_clauses() {
        $num_args = func_num_args();
        $args = func_get_args();

        $connector = $args[0];
        $clauses = array();

        if (is_array($args[1])) {
            $arr = $args[1];
        } else {
            $arr = $args;
            array_shift($arr);
        }
        $count = sizeof($arr);

        for ($i = 0; $i < $count; ++$i) {
            if ($arr[$i]) {
                array_push($clauses, $arr[$i]);
            }
        }

        // Now the array "$clauses" contains all non null clauses.
        $num_clauses = sizeof($clauses);
        if ($num_clauses = 0) {
            return "";
        }
        return join(" $connector ", $clauses);
    }

    /**
     * this builds the search clause
     *
     * @return string
     */
    function simple_search_where_clause() {
        $search_field = $this->get_searchby();
        $search_value = $this->search_value_filter($this->get_searchby_value());

        if (($search_field == '') || ($search_value == ''))
            return '';

        $where_clause = "lower(".$search_field.")";

        //see if the simple search modifier is turned on
        //and then use it for the like clause
        if ($this->get_simplesearch_modifier()) {
            $search_value = strtolower($search_value);
            //its on.  lets see if it has a value.
            $modifier = $this->get_simplesearch_modifier();
            switch ($modifier) {
            case "BEGINS":
                $like_clause = " like '".$search_value."%' ";
                break;
            case "ENDS":
                $like_clause = " like '%".$search_value."' ";
                break;
            case "EXACT":
                $like_clause = " like '".$search_value."' ";
                break;

            case "CONTAINS":
            default:
                $like_clause = " like '%".$search_value."%' ";
                break;
            }
        }
        else {
            $like_clause = " like '%".$search_value."%'";
        }

		$where_clause .= $like_clause;
        return $where_clause;
    }

    /**
     * This function is responsible for
     * building the portion of the where clause
     * for doing an advanced search.
     * NOTE: the child class MUST override this
     *       method
     * @return string - portion of the where clause
     */
    function advanced_search_where_clause() {
        return "";
    }

    /**
     * This function does the variable cleaning
     * that is required to use a search value
     * in a sql query
     *
     * @param string - the origina string from the user
     * @return string - the "cleaned" string
     */
    function search_value_filter( $value ) {
        $value = $this->sql_varchar_filter( strip_tags(stripslashes(trim($value))) );
        $value = str_replace('%', '\%', $value);
        $value = str_replace('_', '\_', $value);
        return $value;
    }

	/**
	 * Clean up the string so it can work in a db
	 *
	 * @param string
	 * @return string
	 */
	function sql_varchar_filter( $value ) {
		return str_replace("'","''",$value);
	}

    /**
     * This builds the where clause for
     * the query
     *
     * @return string the where clause.
     */
    function build_where_clause() {
        $where_clause = $this->_db_options["where_clause"];
        if ($where_clause) {
            $where_clause = "( $where_clause ) ";
        }

        $search_clause = $this->build_search_clause();
        if ($search_clause) {
            $search_clause = " ( $search_clause ) ";
        }

        $where_clause = trim($this->join_clauses("AND",
                                                 $where_clause,
                                                 $search_clause));
        if ($where_clause) {
            $where_clause = " WHERE $where_clause";
        }
        return $where_clause;
    }

    /**
     * This method builds the where clause.
     *
     * @return string
     */
    function build_search_clause() {
        if ($this->get_search_type() == "advanced") {
            return $this->advanced_search_where_clause();
        } else {
            return $this->simple_search_where_clause();
        }
    }

    /**
     * This function builds the orderby clause
     * for the DB query.
     *
     * @param string - DB table field to order by
     * @param string - order assension value.
     * @param boolean - case insensitive sort?
     *
     * @return string.
     */
    function setup_order($orderby, $reverseorder, $icase_sort=FALSE) {
        if ($icase_sort) {
            $orderby = "lower(".$orderby.")";
        }

        $secondary = $this->get_secondary_orderby();

        if (count($secondary) > 0) {
            $orderby .= ",".implode(",", $secondary);
        }

        if ($reverseorder == "true") {
            return "order by ".$orderby." DESC";
        }
        else {
            return "order by ".$orderby." ASC";
        }
    }

    /**
     * This builds the db query ORDER BY
     * clause used to sort the data from the DB.
     *
     * @return string - the order by clause
     */
    function build_order_clause() {

        //Set up reverseorder correctly
        $icase_sort = !$this->get_default_order_case_sensitive();
        $orderby = $this->get_orderby();
        foreach( $this->_columns as $col_name => $data ) {
            if (($data["data_name"] == $orderby) &&
                ($data["reverseorder"] == "true") &&
				!isset( ${$this->reverseorderVar})) {
                $this->set_reverseorder( $data["reverseorder"] );
            }
            if ($data["data_name"] == $orderby &&
                $data["sortable"] == SORTABLE_ICASE) {
                $icase_sort = TRUE;
            } else {
                $icase_sort = FALSE;
            }
        }

        $orderClause = $this->setup_order($orderby,
                                          $this->get_reverseorder(),
                                          $icase_sort );
        return $orderClause;
    }

    /**
     * this builds the groupby clause of the query
     *
     * @return string
     */
    function build_groupby_clause() {
        $groupby = $this->_db_options["groupby_clause"];
        if ($groupby) {
            $groupby = " GROUP BY $groupby ";
        }

        return $groupby;
    }

    /**
     * build the entire DB query
     *
     * @param boolean - build the limit clause or not/
     * @return string - the full query string to the DB.
     */
    function build_query($limit_flag=TRUE) {

        $where_clause = $this->build_where_clause();
        $order_clause = $this->build_order_clause();
        $groupby_clause = $this->build_groupby_clause();
		if ($limit_flag) {
			$limit_clause = $this->build_limit_clause($this->get_offset(), $this->get_limit());
		}

        $query = "select ".$this->get_db_values()." from ".$this->get_db_tables()." " .
                 $where_clause." ".$groupby_clause." ".$order_clause .
			     " ".$limit_clause;

        return $query;
    }


	function do_prequery() {
		//ok now count the total # of rows so
        //we can calculate the # of pages.
		//count rows
        //ok now count the total # of rows so
        //we can calculate the # of pages.
		$this->set_total_rows( $this->count( $this->get_db_tables(),
											 $this->build_where_clause(),
											 $this->get_count_column() ) );

		$this->_query = $this->build_query();
	}


	/************************************************/
	/*            DB Specific Routines              */
	/*          ------------------------            */
	/*  These must be extended by the child class   */
	/* This gives you the power to do the specific  */
	/* DB interactions as you see fit.  Some folks  */
	/* use the low level php db API's, some use the */
	/* PEAR db abstraction objects, and others roll */
	/* their own DB objects.  Extend the functions  */
	/* to provide:                                  */
	/*                                              */
	/* do_query() - this function's purpose is to   */
    /*              execute the sql query that is   */
	/*              available in $this->_query by   */
	/*              the time do_query() is called.  */
	/*                                              */
	/* get_next_data_row() - This function returns  */
	/*              an associative array of the     */
	/*              next row of data from the query.*/
	/*                                              */
	/* build_limit_clause() - This function builds  */
	/*              and returns the "limit clause"  */
	/*              portion of a sql query.  Each   */
	/*              DB implementation is different  */
	/*              on how it deals with limiting   */
	/*              the amount of data you want     */
	/*				back from the query.  Oracle    */
	/*				has no limit clause, so it has  */
	/*				to do this in very tricky/nasty */
	/*				ways.  							*/
	/*                                              */
	/* count() - this function simply returns the   */
	/*           number of rows (to be) found in    */
	/*           sql query.                         */
	/*                                              */
	/************************************************/

    /**
     * Do the query to the DB and pull in all of
     * the records locally.
     *
     * @return boolean - the query passed/failed.
     */
    function do_query() {
		//execute the sql query.
		//we don't actually get the results of
		//the query here, when just execute it.
		user_error("SQLDataListSource::do_query() - Child must override");
        return false;
    }

	/**
	 * This function gets the next data row
	 * from the query()
	 *
	 * @return array()
	 */
	function get_next_data_row() {
	   user_error("SQLDataListSource::get_next_data_row() - Child must override");
       return array();
	}	

    /**
     * This function builds the limit
     * clause portion of a DB query.
	 * This is specific to the particular
	 * DB implementation.
     *
     * @return string - the limit portion of
     *                  the query.
     */
    function build_limit_clause($offset, $limit) {
		user_error("SQLDataListSource::build_limit_clause() - Child must override");
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
		user_error("SQLDataListSource::count() - Child must override");
    }

    /**
     * This function is used to set the flag for the
     * ability to sort/order by case sensitive or not.
     *
     * @param boolean - TRUE = case sensitive by default
     * @return none
     */
    function set_default_order_case_sensitive($flag=TRUE) {
        $this->_default_order_sensitivity = $flag;
    }

    /**
     * This function is used to get the flag for the
     * ability to sort/order by case sensitive or not.
     *
     * @param boolean - TRUE = case sensitive by default
     * @return none
     */
    function get_default_order_case_sensitive() {
        return $this->_default_order_sensitivity;
    }

    /**
     * This function is used to set the flag that tells
     * the simple search clause method to enable the
     * lower() function which will make the search case insensitive.
     *
     * @param boolean - TRUE - case insensitive
     */
    function set_simple_search_case_insensitive($flag=TRUE) {
        $this->_simple_search_case_insensitive = $flag;
    }

    /**
     * This function is used to get the flag that tells
     * the simple search clause method to enable the
     * lower() function which will make the search case insensitive.
     *
     * @return boolean - TRUE - case insensitive
     */
    function get_simple_search_case_insensitive() {
        return $this->_simple_search_case_insensitive;
    }
}

?>
