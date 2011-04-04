<?php
/**
 * $Id: ArrayDataListSource.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * This file contains the DataListSource class
 * that gets the data from an array
 *
 * @author Suren Markossian <suren_markossian@yahoo.com>
 * @package phpHtmlLib
 */

/**
 * We require the DataListSource
 */
require_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/DataListSource.inc");


/**
 *
 * This DataListSource child class gets the data from an
 * external array
 *
 * The array is a 2D array and each sub-array is a set of elements for
 * each row in the list
 *
 * @author Suren Markossian <suren_markossian@yahoo.com>
 * @package phpHtmlLib
 */
class ArrayDataListSource extends DataListSource {

    /**
     * internal class variable
     * to tell us which column to order
     * by.
     */
    var $_sorting_col = NULL;

    /**
     * Secondary sorting column, if any
     */
    var $_secondary_sorting_col = NULL;
    var $_secondary_is_numeric = FALSE;

    /**
     * Sorting in reverse order, to speed up things
     */
    var $_reverse_order = false;


    /**
     * The constructor.
     *
     * @param array data - an array of array elements for each row
     */
    function ArrayDataListSource(&$data) {
        $this->_data =& $data;
    }

    /**
     * This function does the query
     * and search/sort
     */
    function do_query() {

        // do data pre-processing if neccessary
        if ($this->get_searchby_value()) {
            $this->_prequery_filter();
        }

        $count = count($this->_data);

        if ($count > 0) {
            $this->set_total_rows($count);
            $this->sort();
            return true;
        } else {
            return false;
        }
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
        return NULL;
    }

    /**
     * This function returns the next row of
     * valid data.
     *
     */
    function get_next_data_row() {
        $index = $this->get_data_index();
        $limit = $this->get_limit();
        $offset = $this->get_offset();

        if ($limit == -1) {
            // don't limit the data
            if ($index > $this->get_total_rows()) {
                return NULL;
            } else {
                if (!isset($this->_data[$index])) {
                    return null;
                }
                else {
                    return $this->_data[$index];
                }
            }
        } else {
            // Check if we are still in the display range
            if (!is_null($index) && $index < $limit && isset($this->_data[$offset + $index])) {
                return $this->_data[$offset + $index];
            } else {
                return NULL;
            }
        }
    }

    /**
     * This is used to perform pre-query filtering
     * Gives us a chance to run the next row through a filter
     * before any processing has been done
     *
     * @param array - the row to run through the filter
     *
     * @return boolean - TRUE = allow the row. FALSE = drop it.
     */
    function prequery_row_filter(&$row_data) {
        return $this->_find_data($row_data);
    }

    /**
     * This is called to allow rebuilding the data array
     * to remove elements that have to be filtered
     *
     * This is done on pre-processing phase and used for
     * simple and advanced searches
     *
     */
    function _prequery_filter() {

        while (list($key,$row_data) = each($this->_data)) {
            if (!$this->prequery_row_filter($row_data)) {
                unset($this->_data[$key]);
            }
        }

        // re-index the array
        $this->_data = array_values($this->_data);
    }

    /**
     * This function returns the
     * data_index value and increments it
     *
     * @return int
     */
    function get_data_index() {
        $this->_data_index = key($this->_data);
        next($this->_data);
        return $this->_data_index;
    }

    /**
     * This method sorts our data array by the requested
     * column order by.  This could be expensive for HUGE
     * arrays.
     *
     * @return none
     */
    function sort() {
        $sortby = $this->get_orderby();

        $column_name = $this->_find_col_name($sortby);

        //set the sorting column
        //so the sort methods don't have
        //to call functions to get it over and over
        $this->_sorting_col = $sortby;

        //lets see if they have a secondary sort ordering
        $sec = $this->get_secondary_orderby();
        if (is_array($sec) && count($sec)) {
            $secondary = $sec[0];
            $secondary_column_name = $this->_find_col_name($secondary);
            if ($secondary_column_name != NULL && $this->_columns[$secondary_column_name]["sortable"] != NOT_SORTABLE) {
                $this->_secondary_sorting_col = $secondary;
                if ($this->_columns[$secondary_column_name]["sortable"] == SORTABLE_NUMERIC) {
                    $this->_secondary_is_numeric = true;
                } else {
                    $this->_secondary_is_numeric = false;
                }
            }
        }

        // are we using reverse order ?
        if ($this->get_reverseorder() == "true") {
            $this->_reverse_order = true;
        }

        //sort the data
        $this->_sort($column_name);
    }


    /**
     * This function gets the column name from the sortname
     *
     * @param string the sortorder name
     * @return the column name
     */
    function _find_col_name($sort_name) {
        //get the column name
        $column_name = NULL;

        // get the column name
        foreach($this->_columns as $name => $data) {
            if ($sort_name == $data["data_name"]) {
                $column_name = $name;
                break;
            }
        }

        return $column_name;
    }



    /**
     * This method actually calls the usort methods
     *
     * @param string
     */
    function _sort($column_name) {
        // we need to sort the data by the
        // column in the table
        if ($column_name != NULL && $this->_columns[$column_name]["sortable"] != NOT_SORTABLE) {
            // looks like we can sort this column
            if ($this->_columns[$column_name]["sortable"] == SORTABLE_NUMERIC) {
                usort($this->_data, array($this, "cmp_numeric"));
            } else {
                usort($this->_data, array($this, "cmp"));
            }
        }
    }

    /**
     * This method is used for comparing 2 string values
     *
     * @param string first entry to compare
     * @param string second entry to compare
     * @return natural compare results
     */
    function cmp($data1, $data2) {
        $ret = strnatcmp($data1[$this->_sorting_col],
                         $data2[$this->_sorting_col]);

        if (!$ret && $this->_secondary_sorting_col) {
            if ($this->_secondary_is_numeric) {
                if ($data1[$this->_secondary_sorting_col] == $data2[$this->_secondary_sorting_col]) {
                    $ret = 0;
                } else {
                    $ret = ($data1[$this->_secondary_sorting_col] < $data2[$this->_secondary_sorting_col]) ? -1 : 1;
                }
            } else {
                $ret = strnatcmp($data1[$this->_secondary_sorting_col],
                                 $data2[$this->_secondary_sorting_col]);
            }
        }

        if ($this->_reverse_order) {
            $ret *= -1;
        }
        return $ret;
    }

    /**
     * This method is used for comparing 2 numerical
     * values
     *
     * @param string first entry to compare
     * @param string second entry to compare
     * @return compare results
     */
    function cmp_numeric($data1, $data2) {

        if ($data1[$this->_sorting_col] == $data2[$this->_sorting_col]) {
            $ret = 0;
        } else {
            $ret = ($data1[$this->_sorting_col] < $data2[$this->_sorting_col]) ? -1 : 1;
        }

        if (!$ret && $this->_secondary_sorting_col) {
            if ($this->_secondary_is_numeric) {
                if ($data1[$this->_secondary_sorting_col] == $data2[$this->_secondary_sorting_col]) {
                    $ret = 0;
                } else {
                    $ret = ($data1[$this->_secondary_sorting_col] < $data2[$this->_secondary_sorting_col]) ? -1 : 1;
                }
            } else {
                $ret = strnatcmp($data1[$this->_secondary_sorting_col],
                                 $data2[$this->_secondary_sorting_col]);
            }
        }

        if ($this->_reverse_order) {
            $ret *= -1;
        }
        return $ret;
    }

    /**
     * This is used to do the default search
     * capability in the DataListSource parent class.
     * This is used so we can filter our results to
     * what the user searched for.
     *
     * @param array the row data entry.
     *              We will look for a specific column's
     *              value here to test against.
     * @return boolean found it or not
     */
    function _find_data( $row_data ) {
		//look for the 'needle' in the 'haystack'

		$needle = $this->get_searchby_value();
		$haystack = $row_data[$this->get_searchby()];

		switch ($this->get_simplesearch_modifier()) {
		case "BEGINS":
			if (strncasecmp($needle, $haystack, strlen($needle)) == 0) {
				return TRUE;
			} else {
				return FALSE;
			}
			break;

		case "CONTAINS":
			if (stristr($haystack, $needle)) {
				return TRUE;
			} else {
				return FALSE;
			}
			break;
		case "EXACT":
			if (strcasecmp($needle, $haystack) == 0) {
				return TRUE;
			} else {
				return FALSE;
			}
			break;
		case "ENDS":
			$needle_len = strlen( $needle );
			$haystack_len = strlen( $haystack );
			if ($needle_len > $haystack_len) {
				return FALSE;
			} else if ($needle_len == $haystack_len) {
				$tmp = $haystack;
			} else {
				$tmp = substr($haystack, $haystack_len - $needle_len);
			}
			if (strncasecmp($needle, $tmp, $needle_len) == 0) {
				return TRUE;
			} else {
				return FALSE;
			}
			break;
		}
	}

}
?>
