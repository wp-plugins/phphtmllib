<?php

/**
 * This file builds a VERY simple version of the DataList
 * with no sortable columns, or searchablility.
 *
 *
 * $Id: SimpleGUIDataList.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib 
 */ 

require_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/DataList.inc");

class SimpleGUIDataList extends DataList {

    /**
     * Initialize the gui layout
     * 
     */
    function gui_init() {
        //disable searching
        $this->search_disable();
        $this->_data_table = html_table($this->get_width(),0,0,0,
                                        $this->_align);
		$this->_data_table->set_class("datalist_border");

        //add the header tr reference
		//it will get populated later
		$this->_header_tr = new TRtag;

        //initialize the first date row
		$this->_data_row = new TRtag;

        $this->_data_table->add_reference( $this->_header_tr );
    }

	function child_get_gui() {
        return container( $this->_data_table );
	}

	function child_build_column_header($name, $col, $cnt) {
        $td = $this->build_column_header($name, $col, $cnt);
        $this->_header_tr->add( $td );
	}


	function child_add_row_cell($obj, $col_name, $last_in_row_flag, $row_data) {
        //show the normal data 
        $td = $this->wrap_column_item($obj, $col_name);
        $this->_data_row->add( $td );
		
		if ($last_in_row_flag) {
			$this->_data_table->add_row( $this->_data_row );
			$this->_data_row = new TRtag;
		}
	}

    /**
     * This function builds the object/text
     * to be used for a column header. It can
     * either be an href because its sortable,
     * or it can just be text, because its not
     * sortable.
     *
     * @param string $col_name - the column name
     *                           to build from
     *                           the headers.
     * @param array $col_data - the column's data.
     * @param int the column # we are working on.
     * @return mixed - either an Atag object or
     *                 raw text.
     */
    function build_column_header($col_name, $col_data, $col_num) {

        $td = new TDtag(array("class"=>"datalist_col_head",
                              "width" => $col_data["size"]));

        $td->push($col_name);
        $td->set_tag_attribute("style", "padding-left:5px;padding-right:5px;white-space:nowrap;");

        return $td;
    }


     /**
     * This function ensures that the data we place
     * in a column is aligned according to what the
     * user wants.
     *
     * @param mixed - $obj - the data for the td.
     * @param string - $col_name - the name of the column header
     *                             for this row to render.
     * @param int - $odd_row - tells us if this cell lives in
     *                         an odd # row (for alternating row colors)
     * @param int - the column # we are working on.
     * @return TDtag object
     */
    function wrap_column_item($obj, $col_name) {

        //make sure its set to something.
        if ($obj == '') {
            $obj = "&nbsp;";
        }

        //make sure we don't put a right border on the last
        //column we are working on.

		if ($this->_columns[$col_name]["data_name"] == $this->orderby()) {
            $style = "background-color: #f4f4f4;";
        } else {
			$style = "background-color: #ffffff;";
		}

        $align = $this->_columns[$col_name]["align"];
        $td = new TDtag(array("align" => $align,
                              "style" => $style,
							  "class" => "datalist_data_cell"));

        if (is_object($obj) && $obj->_tag == "td") {
			return $obj;
		} else {
			$td->add( $obj );
		}
        return $td;
    }
}

?>
