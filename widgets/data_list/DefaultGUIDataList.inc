<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 *
 * This file contains the Default DataList child
 * that has its specific GUI layout/look/feel
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 *
 */

if (!defined('PHPHTMLLIB_WIGDET_IMAGEPATH'))
    define('PHPHTMLLIB_WIGDET_IMAGEPATH', PHPHTMLLIB_RELPATH . '/images/widgets') ;

/**
 * Need to make sure we have the DataList object
 */
require_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/DataList.inc");

/**
 * This class is the Default phpHtmlLib GUI interface
 * child of the DataList class.  This child simply does
 * the job of rendering the html/layout for a DataList.
 * You can use this as an example of how to build your
 * own look/feel for your DataList.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 *
 */
class DefaultGUIDatalist extends DataList {


    /**
     * The overall alignment
     *
     * DEFAULT: "center"
     */
    var $_align = "center";

    /**
     * This holds the action column
     * settings if any.
     */
    var $_action_column = array();

    /**
     * holds the cntr for the action
     * checkbox name
     */
    var $_action_count = 0;

    /**
     * This array holds the list of
     * hidden checkbox[] items.
     *
     */
    var $_hidden_checkbox_items = array();

    /**
     * this array keeps track of the list
     * of rendered visible checkbox[]
     * items.  So we can not render the
     * hidden version of it.
     */
    var $_visible_checkbox_items = array();

    /**
     * this flag tells us to save the
     * checked items between pages
     * By default this is off.
     */
    var $_save_checked_items_flag = FALSE;

    /**
     * This variable holds the array of default
     * selected items.  This is populated
     * inside the user_setup() function
     * to pre-populate the list of selected
     * items for a the checkbox action column.
     *
     */
    var $_default_checked_items = array();


    /**
     * Do we show action bar row?
     */
    var $_show_actionbar = TRUE;

    /**
     * Do we show action bar row when the data list is empty?
     */
    var $_show_empty_datalist_actionbar = FALSE;

    /**
     * This variable tells us whether to display
     * select all checkbox
     */
    var $_allow_select_all = TRUE;


    /**
     * this array holds some strings for the
     * search functionality.  This enables
     * some level of localization for other
     * languages.
     *
     */
    var $_search_text = array("title" => "Search",
                              "find" => "Find",
                              "button" => "Search");

    /**
     * If true, allows search block to be
     * collapsed/expanded.
     *
     * NOTE: This doesn't stay collapsed between
     *       pages, when using GET as the form method.
     *
     */
    var $_collapsable_search = FALSE;

    /**
     * Initial state of the search tree
     *
     */
    var $_search_tree_open = TRUE;

    /**
     * for a reference so the row_filter
     * affects the paging information.
     */
    var $__page_info = "";


    var $_cur_col_cntr = 0;

    /**
     * Flag to enable simple search modifyer.
     * IF enabled it will add a select that adds
     * the "beings with", "contains" options for
     * a simple search.
     */
    var $_simple_search_modifier = SEARCH_ALL;

    /**
     * do we show the title string?
     */
    var $_display_title_flag = TRUE;

	/**
     * Flag to let us know that search
     * is enabled.  Default this to TRUE
	 * but you can still disable it
     *
     */
    var $_search_flag = TRUE;

	/**
     * Do we want to alternate the row colors?
     * This helps to see each row easier.
     */
    var $alternating_row_colors = TRUE;


    /**
     * This function sets a prefix for all
     * variables that are used in the item list
     * table on a page.  This allows you to have
     * multiple itemlists on a single html page.
     *
     * @param string $prefix - the prefix for all vars.
     */
    function set_global_prefix($prefix) {
        $this->_vars["radioVar"] = "radio";
        $this->_vars["checkboxVar"] = "checkbox";
        DataList::set_global_prefix($prefix);
    }


    /**
     * This sets the flag to turn on/off the
     * ability to collapse the search box.
     *
     * @param bool
     */
    function set_search_collapse($flag=TRUE) {
        $this->_collapsable_search = $flag;
    }


    /**
     * This sets the flag to turn on/off the
     * the action bar when the datalist is empty.
     *
     * @param bool
     */
    function set_show_empty_datalist_actionbar($flag=TRUE) {
        $this->_show_empty_datalist_actionbar = $flag;
    }


    /**
     * This function builds the base layout
     * of what the overall DataList will look like
     * 
     */
    function gui_init() {
        $container = container();
        if (!$this->get_showall()) {
            $container->add( $this->build_tool_link("first"),
                             $this->build_tool_link("prev"));

            $container->add_reference( $this->__page_info );

            $container->add($this->build_tool_link("next"),
                            $this->build_tool_link("last"),
                            $this->build_tool_link("expand") );
        }

        $this->_data_table = html_table($this->get_width());
        $this->_data_table->set_class("datalist_border");

        $table = html_table("", 0, 0, 0);
        $table->set_collapse();

        $td = new TDtag(array("style"=>"color: black;background-color: #eeeeee;".
                              "padding-left: 2px; padding-right: 2px; border:1px inset #cccccc;"));
        $td->add_reference($this->__page_info);
        $div = html_div("", _HTML_SPACE);
        $div->set_style("font-size: 1px; line-height: 1px; height:3px;");
        $table->add_row( new TDtag(array(), $div));

        $image_path = $this->get_image_path();
        $table->add_row(

                       $this->build_tool_link("first"), _HTML_SPACE,
                       $this->build_tool_link("prev"), _HTML_SPACE,

                       $td,

                       _HTML_SPACE,

                       $this->build_tool_link("next"),_HTML_SPACE,
                       $this->build_tool_link("last"), _HTML_SPACE,
                       $this->build_tool_link("expand"),

                       new TDtag(array("style"=>"font-size: 1px; line-height: 1px; width:10px;"), _HTML_SPACE)
                       );

        $table->add_row( new TDtag(array(),$div));
        $this->_tool_td = html_td('datalist_title', "right", $table);


        //calculate the # of columns depending on if they
        //have added action columns.
        $cols = count($this->_columns);
        if ($this->_has_action_column("FIRST")) $cols++;
        if ($this->_has_action_column("LAST")) $cols++;

        $title_table = html_table("100%");

        $title = new TDtag(array("align" => "left",
                                 "class" => "datalist_title",
                                 "style" => "padding-left: 5px;"),
                           $this->get_title() );

        $title_table->add( new TRtag( array(), $title,
                                      $this->_tool_td) );


        //add the header tr reference
        //it will get populated later
        $this->_header_tr = new TRtag;
        $this->_data_table->add_row( new TDtag(array("colspan" => $cols),
                                               $title_table) );
        $this->_data_table->add_reference($this->_header_tr);

        //initialize the first date row
        $this->_data_row = new TRtag;
    }

    /**
     * this function is used to set the overall alignment
     * of the widget
     *
     * @param string - the align value
     */
    function set_align($align) {
        $this->_align = $align;
    }

    function child_build_column_header($name, $col, $cnt) {
        if (!$this->_cur_col_cntr) {
            $this->_cur_col_cntr = 1;
            //lets see if we need to add an action column
            //as the first column.
            if ($this->_has_action_column("FIRST")) {
                //looks like we have a FIRST column actionbar
                //lets add it
                $td = $this->_build_action_column("FIRST", TRUE);
                $this->_header_tr->add( $td );
            }
            $td = $this->build_column_header($name, $col, $cnt);
            $this->_header_tr->add( $td );
        } else {
            $td = $this->build_column_header($name, $col, $cnt);
            $this->_header_tr->add( $td );
        }

        if ($this->_cur_col_cntr == $cnt) {
            //lets see if we need to add an action column
            //as the first column.
            if ($this->_has_action_column("LAST")) {
                //looks like we have a FIRST column actionbar
                //lets add it
                $td = $this->_build_action_column("LAST", TRUE);
                $this->_header_tr->add( $td );
            }
            $this->_cur_col_cntr = 0;
        } else {
            $this->_cur_col_cntr++;
        }
    }

    function child_add_row_cell($obj, $col_name, $last_in_row_flag, $row_data, $even_row) {
        if (!$this->_cur_col_cntr) {
            $this->_cur_col_cntr = 1;
            //lets see if we need to add an action column
            //as the first column.
            if ($this->_has_action_column("FIRST")) {
                //looks like we have a FIRST column actionbar
                //lets add it
                $this->_data_row->add($this->_build_action_column("FIRST", FALSE, $row_data));
            }
            $td = $this->wrap_column_item($obj, $col_name, $even_row);
            $this->_data_row->add( $td );
        } else {
            //show the normal data
            $td = $this->wrap_column_item($obj, $col_name, $even_row);
            $this->_data_row->add( $td );
        }


        if ($last_in_row_flag) {
            //lets see if we need to add an action column
            //as the first column.
            if ($this->_has_action_column("LAST")) {
                //looks like we have a LAST column actionbar
                //lets add it
                $this->_data_row->add($this->_build_action_column("LAST", FALSE, $row_data));
            }


            //manually render here to drastically cut down
            //on the memory useage for HUGE...HUGE lists
            $this->_data_table->add( $this->_data_row->render(0,0) );
            $this->_data_row = new TRtag;
            $this->_cur_col_cntr = 0;
        } else {
            $this->_cur_col_cntr++;
        }
    }

    /**
     * Override the parent's method so we can wrap
     * everything in a div to hold it all together
     * when we change the alignment
     *
     * @return DIVtag object
     */
    function build_gui() {
        $div = html_div("", DataList::build_gui() );
        $div->set_tag_attribute("align", $this->_align );
        return $div;
    }

    function child_get_gui() {
        $this->__page_info = $this->get_page_info();
		if (!$this->_datasource->get_total_rows()) {
            // no data was found - display a message

            //calculate the # of columns depending on if they
            //have added action columns.
            $cols = count($this->_columns);
            if ($this->_has_action_column("FIRST")) $cols++;
            if ($this->_has_action_column("LAST")) $cols++;

            $this->_data_table->add_row(new TDtag(array("colspan"=>$cols,
                                                        "class"=>"dialog",
                                                        "style"=>"height:40px;text-align:center"),
                                                  $this->get_not_found_message()));
        }

        return container( $this->_data_table,
                          $this->_build_actionbar() );
    }

    function _build_default_vars() {
        $c = parent::_build_default_vars();

        if ($this->_save_checked_items_enabled()) {
            foreach( $this->_hidden_checkbox_items as $key => $value ) {
                if (!isset($this->_visible_checkbox_items[$key])) {
                    $c->add( form_hidden($this->_vars["checkboxVar"].'[]', $key ) );
                }
            }
        }

        return $c;
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

        if ($this->_columns[$col_name]["sortable"]) {
            $col_url = $this->build_column_url($col_name);

            $td->set_tag_attribute("title","Sort By ".$col_name);

            $td->add(html_a($col_url, $col_name,"head_link"));

            if ($this->_columns[$col_name]["data_name"] == $this->orderby()) {

                if ($this->reverseorder() == "false") {
                    $alt_title = "Sorted in Ascending Order";
                    $img = html_img($this->get_image_path()."/picto_down.gif",11,11,'',$alt_title);
                    $img->set_tag_attribute("style", "padding-left: 5px;margin-left:5px;vertical-align:middle;");
                    $td->add($img);
                } else {
                    $alt_title = "Sorted in Descending Order";
                    $img = html_img($this->get_image_path()."/picto_up.gif",11,11,'',$alt_title);
                    $img->set_tag_attribute("style", "padding-left: 5px;margin-left:5px;vertical-align:middle;");
                    $td->add($img);
                }
            }

            // we want to highlight the td on mouse over
            $td->set_tag_attribute("onmouseover",
                                   "javascript:style.cursor='pointer';this.className='datalist_col_head_hover';");
            $td->set_tag_attribute("onmouseout",
                                   "javascript:this.className='datalist_col_head'");
            $td->set_tag_attribute("onmousedown",
                                   "javascript:this.className='datalist_col_head_clicked'");


            if ($this->get_form_method() == "POST") {
                $td->set_tag_attribute("onclick", $col_url);
            } else {
                $td->set_tag_attribute("onclick", "javascript:document.location='".$col_url."';");
            }
        } else {
            $td->add($col_name);
            $td->set_tag_attribute("style", "padding-left:5px;padding-right:5px;white-space:nowrap;");
        }

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
    function wrap_column_item($obj, $col_name, $even_flag) {

        //make sure its set to something.
        if ($obj == '') {
            $obj = "&nbsp;";
        }

		if ($this->alternating_row_colors && !$even_flag) {
		    if ($this->_columns[$col_name]["data_name"] == $this->orderby()) {
				$class = "datalist_data_cell_odd_selected";
			} else {
				$class = "datalist_data_cell_odd";
            }
		} else {
			if ($this->_columns[$col_name]["data_name"] == $this->orderby()) {
				$class = "datalist_data_cell_selected";
			} else {
				$class = "datalist_data_cell";
            }
		}

        $align = $this->_columns[$col_name]["align"];
        $td = new TDtag(array("align" => $align,
							  "class" => $class));

        if (is_object($obj) && @$obj->_tag == "td") {
			return $obj;
		} else {
			$td->add( $obj );
		}
        return $td;
    }

    /**
     * This builds the table that holds the search
     * capability.
     *
     * @return TABLEtag object.
     */
    function child_build_search_table() {
        //the search capability is enabled.
        //lets try and build the table.
        $td_attributes = array("style" => "padding-left: 5px;padding-bottom:4px;".
                               "padding-right:40px;padding-top:4px;".
                               "background-color: #eeeeee;",
                               "align" => "left",
                               "class" => "font10");

        $table = html_table($this->get_width());

        if (isset($_REQUEST["_search_tree_open"])) {
            // set the search tree state
            $this->_search_tree_open = $_REQUEST["_search_tree_open"];
        }

        //test to see if they want to render the outer borders
        $table->set_tag_attribute("style", "border-left: 1px solid #a1a1a1;".
                                  "border-right: 1px solid #a1a1a1;");

        $td = new TDtag($td_attributes);

        if ($this->search_type() == "advanced") {
            $td->add($this->_build_advanced_search_form());
        } else {
            $td->add($this->_build_simple_search_form());
        }
        $table->add_row($td);

        if ($this->_collapsable_search) {
            $div = new DIVtag(array("id"=>"search"), $table);
            if (!$this->_search_tree_open) {
                // hide search if tree is closed
                $div->set_tag_attribute("style", "visibility:hidden;height:1px;");
            }

            $this->set_save_vars(array("_search_tree_open" =>
                                       (int)$this->_search_tree_open));


            return container($this->_build_search_title(), $div);
        } else {
            return container($this->_build_search_title(), $table);
        }
    }


    /**
     * This function is used to allow the child class
     * to override the values of text that is used for the
     * search area
     * 
     * @param string the title of the search area
     * @param string The find string
     * @param string the button submit string
     */
    function set_search_strings($title=null, $find=null, $button=null) {
        if ($title !== null) {
            $this->_search_text['title'] = $title;
        }
        if ($find !== null) {
            $this->_search_text['find'] = $find;
        }
        if ($button !== null) {
            $this->_search_text['button'] = $button;
        }
    }

    /**
     * This function builds the search title table
     *
     * @return TABLEtag object
     */
    function _build_search_title() {
        //build the title stacked table
        $title = html_table($this->get_width());

        if ($this->_collapsable_search) {
            // build link for collapsable search

            if ($this->_search_tree_open) $img_source = "tree_open.gif";
            else $img_source = "tree_closed.gif";

            $img = html_img(PHPHTMLLIB_WIGDET_IMAGEPATH . "/" . $img_source, 10, 10);
            $img->set_tag_attribute("id", "isearch");

            $img = html_a("javascript:toggle_tree('search')", $img);

            $link = html_a("javascript:toggle_tree('search')", $this->_search_text["title"], "head_link");
            $link->set_tag_attribute("id", "lsearch");

            $c = container(_HTML_SPACE, $img, $link);
        } else {
            $c = container(_HTML_SPACE . $this->_search_text["title"]);
        }


        //test to see if they want to render the outer borders
        $title->set_tag_attribute("style","border: 1px solid #a1a1a1;");
        $title->add_row(new TDtag(array("class" => "datalist_title",
                                        "align" => "left"), $c));

        return $title;
    }


    /**
     * This function builds the simple search TD
     *
     * @return ContainerWidget
     */
    function _build_simple_search_form() {

        //if there is only 1 item enabled for search
        //then the search looks simple.
        $fields = $this->_get_searchable_fields();
        $cnt = count($fields);
        if ($cnt == 0) {
            return NULL;
        }

        $container = new ContainerWidget;

        if ($cnt == 1) {
            //user only has 1 field to show.
            list($name, $field) = each($fields);
            $container->add($this->_search_text["find"]." ".$name."&nbsp;&nbsp;");
        } else {
            //user has many fields to show.
            $container->add($this->_search_text["find"]." ",
                            form_select($this->_vars["search_fieldVar"], $fields, $this->search_field(),
                                        FALSE, array('style' => 'vertical-align:middle;')));
        }

        if ($this->get_simple_search_modifier()) {
            //the user wants the search modifier turned on.
            $select =$this->_build_simple_search_modifier();
            $select->set_tag_attribute('style', 'vertical-align:middle;');
            $container->add($select);
        }

        $container->add(form_text($this->_vars["search_valueVar"], $this->search_value_filter($this->search_value()), "20", "100", array("style"=>"vertical-align:middle;")),
                        form_submit($this->get_form_name(),
                                    $this->_search_text["button"], array("style"=>"vertical-align:middle;")));

        if ($this->is_advanced_search_enabled()) {
            $span = html_span(html_a("#","Advanced Search", "title"));
            $container->add("&nbsp;", $span);
        }

        if ($cnt == 1) {
            $container->add(form_hidden($this->_vars["search_fieldVar"], $field));
        }

        return $container;
    }


    /**
     * This function builds the table that holds the
     * Advanced search form fields
     *
     * @return Container object
     */
    function _build_advanced_search_form(){
        return container($this->advanced_search_form(),
                         form_hidden("search_typeVar", "advanced"));
    }


    /**
     * This function adds an action column.  This
     * adds a column of either checkboxes or radio
     * buttons.
     *
     * @param string - type of column
     *                 'checkbox' or 'radio'
     * @param string - which column it lives in
     *                 'FIRST' or 'LAST'
     * @param string - which db field is associated
     *                 with this.
     * @param string - the title to use for the column.
     *                 NOTE: if this is set, then there
     *                       will NOT be a global checkbox
     *                       that can be used to select/deslect
     *                       all at once.
     *
     */
    function add_action_column($type, $col, $db_field, $title=NULL) {
        $action = array("type" => $type,
                        "dbfield" => $db_field,
                        "title" => $title);
        $this->_action_column[$col] = $action;
        //force the rendering of the form tag when an
        //action column has been set.
        $this->set_form_render(TRUE);
    }

    /**
     * This function is used to set the default list
     * of selected checkbox items.  This is used so
     * the user can pre-populate the list of
     * checked items in the checkbox action column
     *
     * @param array - the array of checked items
     */
    function set_default_checked_items($items) {
        $this->_default_checked_items = $items;
    }

    /**
     * This function returns the array of default
     * checked items to be marked as checked in
     * the checkbox action column
     *
     * @return array
     */
    function get_default_checked_items() {
        return $this->_default_checked_items;
    }

    /**
     * set the flag to tell the object to
     * save the checked items
     *
     * NOTE: this only works if we are in POST mode.
     *       GET can easily fail because of too many
     *       items saved on the query string.
     *
     * @param boolean TRUE = enable
     */
    function save_checked_items($flag=TRUE) {
        if ($this->get_form_method() == 'POST') {
            $this->_save_checked_items_flag = $flag;
        } else {
            user_error(__CLASS__."::".__FUNCTION__."() - Cannot be used while form method is GET.  ".
                       "You should call DataList::set_form_method('POST') first.<br>", E_USER_ERROR);
        }
    }

    /**
     * This tests the object flag to
     * see if the child class wants to
     * automatically save the checked
     * items
     *
     * @return boolean
     */
    function _save_checked_items_enabled() {
        return $this->_save_checked_items_flag;
    }

    /**
     * This function tests to see if the child
     * wants to render an action column
     *
     * @param string - the column to test for
     *                 FIRST or LAST
     * @return boolean
     */
    function _has_action_column($col) {
        if (isset($this->_action_column[$col])) {
            return TRUE;
        } else {
            return FALSE;
        }
    }

    /**
     * This allows the caller to
     * turn on/off the rendering of
     * the bottom action bar row
     *
     * @param boolean - TRUE = on FALSE = off
     */
    function set_actionbar($flag = TRUE) {
        $this->_show_actionbar = $flag;
    }

    /**
     * This function gets the current value
     * of the show actionbar flag setting.
     *
     * @return boolean
     */
    function show_actionbar() {
        return $this->_show_actionbar;
    }

    /**
    * Sets the flag for rendering the select all checkbox
    *
    * @param bool flag
    */
    function allow_select_all($flag) {
        $this->_allow_select_all = $flag;
    }
    /**
     * This function enables/disables the displaying
     * of the title string
     * 
     * @param boolean TRUE = allow title to be shown
     */
    function set_title_enable($flag) {
        $this->_display_title_flag = $flag;
    }


    /**
     * Check to see if we should show the title
     * 
     * @return string
     */
    function get_title() {
        if ($this->_display_title_flag) {
            return parent::get_title();
        } else {
            return _HTML_SPACE;
        }
    }

	/**
	 * This method is used to set the
	 * flag that allows us to do 
	 * alternating row colors or not
	 * 
	 * @param boolean
	 */
	function set_alternating_row_colors($flag = TRUE) {
		$this->alternating_row_colors = $flag;
	}


    /**
     * This builds an action column cell
     *
     * @param string - the column to test for
     *                 FIRST or LAST
     * @param boolean - lets us know this is for
     *                  the header or a cell.
     * @param array   - the row's data.
     * @return HTMLTag object
     */
    function _build_action_column($col, $header_flag=FALSE, $row_data=NULL) {

        $attributes = array("width" => "1%",
                            "align" => "center");

        if ($header_flag) $attributes["class"] = "datalist_col_head";
        else $attributes["class"] = "datalist_actionbar_data_cell";

        $td = new TDtag($attributes);
        $form_value = '';
        if ($header_flag) {
            //this is for a header item.
            $form_value = "";
        } else {
            $form_value = $row_data[$this->_action_column[$col]["dbfield"]];
        }

        switch ($this->_action_column[$col]["type"]) {
        case "radio":
            if ($header_flag) {
                //we don't put a header button for radio
                if ($this->_action_column[$col]["title"])
                    $obj = $this->_action_column[$col]["title"];
                else $obj = _HTML_SPACE;
            } else {
                $name = $this->_vars["radioVar"]."[".$this->_action_count."]";
                $obj = form_radio($name, $form_value);

                //see if the checkbox should be disabled
                if (!$this->is_action_enabled($form_value, $row_data)) {
                    $obj->set_tag_attribute("DISABLED");
                    $obj->set_tag_attribute("value","");
                }
            }

            break;
        case "checkbox":
            if ($header_flag) {
                //see if the child wants a title instead
                //of the global check/uncheck checkbox
                if ($this->_action_column[$col]["title"]) {
                    $obj = $this->_action_column[$col]["title"];
                    break;
                } else {
                    $name = $this->_vars["checkboxVar"];
                }
            } else {
                $name = $this->_vars["checkboxVar"]."[".$this->_action_count."]";
            }

            $this->_action_count++;
            $obj = form_checkbox($name, $form_value);
            if ($header_flag) {
                if ($this->_allow_select_all) {
                    $obj->set_tag_attribute("onclick", "javascript:mass(this.form)");
                } else {
                    $obj = _HTML_SPACE;
                }
            }

            //see if the checkbox should be checked
            if ($this->_is_col_checked($form_value, $row_data)) {
                $obj->set_tag_attribute("CHECKED");
            }

            //see if the checkbox should be disabled
            if (!$header_flag && !$this->is_action_enabled($form_value, $row_data)) {
                $obj->set_tag_attribute("DISABLED");
                $obj->set_tag_attribute("value","");
            }

            //save which items we have rendered visibly.
            //so we can filter those out in the hidden
            //items
            $this->_visible_checkbox_items[$form_value] = TRUE;
            break;
        }
        $td->add($obj);
        $td->set_collapse();
        return $td;
    }

    /**
     * This method checks to see if a
     * particular row has been checked
     * in the action column
     *
     * @param string - the item to look for
     * @param array   - the row's data.
     * @return boolean.
     */
    function _is_col_checked($value, $row_data) {
        if (count($this->_hidden_checkbox_items) == 0) {
            if (isset($_REQUEST[$this->_vars["checkboxVar"]]) && is_array($_REQUEST[$this->_vars["checkboxVar"]])) {
                $this->_hidden_checkbox_items = array_flip($_REQUEST[$this->_vars["checkboxVar"]]);
            }
        }

        //call the child function to see if item should
        //be checked
        $user_flag = $this->is_action_checked($value, $row_data);
        $hidden_flag = isset($this->_hidden_checkbox_items[$value]);

        return($user_flag || $hidden_flag);

        if (isset($this->_hidden_checkbox_items[$value])) {
            return TRUE;
        } else {
            return FALSE;
        }
    }

    /**
     * This function is provided to give the child class
     * the ability to precheck/select a particular
     * column.
     *
     * @param string - the item to look for.
     * @param array   - the row's data.
     * @return boolean
     */
    function is_action_checked($value, $row_data) {
        return FALSE;
    }

    /**
     * This function is provided to give the child
     * class the ability to enable/disable a particular
     * checkbox.
     *
     * @param string - the item to look for.
     * @param array   - the row's data.
     * @return boolean
     */
    function is_action_enabled($value, $row_data) {
        return TRUE;
    }

    /**
     * This function renders the action bar at the bottom
     * of the data list.
     *
     * @return TABLEtag object
     */
    function _build_actionbar() {

        if ($this->show_actionbar()) {

            $table = html_table($this->get_width());
            $table->set_class("datalist_actionbar");
            /*if ($this->show_outer_border()) {
                $table->set_tag_attribute("style", _CSS_BORDER_LEFT.
                                          _CSS_BORDER_RIGHT.
                                          _CSS_BORDER_BOTTOM);
            }
            else {
                $table->set_tag_attribute("style", _CSS_BORDER_TOP);
            }*/

            $td = new TDtag(array("class"=>"datalist_bottom_seperator",
                                  "colspan" => 3),
                            _HTML_SPACE);
            $table->add_row( $td );

            $table->add_row($this->_build_actionbar_arrow_cell("FIRST"),
                            $this->_build_actionbar_data_cell(),
                            $this->_build_actionbar_arrow_cell("LAST") );

            return $table;
        } else return NULL;
    }

    /**
     * This function builds a TD with the
     * appropriate action arrow.
     *
     * @param string - FIRST or LAST
     * @return TDtag
     */
    function _build_actionbar_arrow_cell($col) {
        $td = new TDtag(array("class" => "datalist_title",
                              "style" => "padding-left:14px;padding-right:14px;".
                              "padding-top:5px;",
                              "width" => "5%")
                       );

        if ($col == "FIRST") {
            $td->set_tag_attribute("align", "left");
            if ($this->_has_action_column("FIRST") &&
                ($this->_datasource->get_total_rows() ||
                $this->_show_empty_datalist_actionbar)) {
                $td->add(html_img($this->get_image_path()."/arrow_right.gif"));
            } else {
                $td->add("&nbsp;");
            }
        } else {
            $td->set_tag_attribute("align", "right");
            if ($this->_has_action_column("LAST") &&
                ($this->_datasource->get_total_rows() ||
                $this->_show_empty_datalist_actionbar)) {
                $td->add(html_img($this->get_image_path()."/arrow_left.gif"));
            } else {
                $td->add("&nbsp;");
            }
        }
        return $td;
    }

    /**
     * This function builds the user's data cell
     *
     * @return TDtag;
     */
    function _build_actionbar_data_cell() {
        $td = new TDtag(array("class" => "datalist_title",
                              "style" => "padding-left:5px;padding-right:5px;".
                              "padding-top:5px;padding-bottom:5px")
                       );

        $flag = FALSE;
        if ($this->_has_action_column("FIRST")) {
            $flag = TRUE;
            $td->set_tag_attribute("align", "left");
        } else if ($this->_has_action_column("LAST")) {
            $flag = TRUE;
            $td->set_tag_attribute("align", "right");
        }

        if ($flag && $this->_datasource->get_total_rows()) {
            $td->add($this->actionbar_cell());
	} else if ($this->_show_empty_datalist_actionbar && $this->_datasource->get_total_rows() == 0) {
            $td->add($this->empty_datalist_actionbar_cell());
        } else {
            $td->add("&nbsp;");
        }

        return $td;
    }

    /**
     * this is the method that builds
     * the contents for the middle actionbar
     * td cell.
     * NOTE this function is meant to be overriden
     *      by the child class.
     *
     * @return ContainerWidget object
     */
    function actionbar_cell() {
        return _HTML_SPACE;
    }

    /**
     * this is the method that builds
     * the contents for the middle actionbar
     * td cell.
     * NOTE this function is meant to be overriden
     *      by the child class.
     *
     * @return ContainerWidget object
     */
    function empty_datalist_actionbar_cell() {
        return _HTML_SPACE;
    }

    /**
     * This function builds an action button that will
     * modify the form action, to post to a different
     * script to handle the data
     *
     * @param string - the button name
     * @param string - the script that gets called.
     * @param string - extra js to put prior to the submit();
     * @return INPUTtag object
     */
    function action_button($name, $action = "", $javascript = "")
    {
        $submit = form_submit("_action", $name);

        // here we make sure that all standard buttons look the same
        if (strlen($name)<10) $submit->set_tag_attribute("style","width: 80px;");

        $form_name = $this->get_form_name();

        $onclick = "javascript: ";
		if ($action != "") {
			$onclick  .= "document.".$form_name.".action='".$action."';";
		}
			
		if ($javascript != "") {
			$onclick .= $javascript . ";";
		}
			
		$onclick .= "document.".$form_name.".submit();";


        if ($action != '' || $javascript != '') {
            $submit->set_tag_attribute("onclick", $onclick);
        }

        return $submit;
    }

    /**
     * This function builds an action select box that will
     * be passed when a form action button is executed.
     *
     * @param string - the select name
     * @param mixed - the select options
     * @param mixed - selected - string for one, array for multiple
     * @param boolean - multiple select
     * @param mixed - additional attributes
     * @return INPUTtag object
     */
    function action_select($name, $options = array(),
        $selected = "", $multiple_flag = false, $attribs = false,
        $action = "", $javascript = "") 
    {
	    $options = array_merge(array("Select Action" => "Select Action"), $options) ;

        $select = form_select($name, $options, $selected, $multiple_flag, $attribs)  ;

        $form_name = $this->get_form_name();

        $onchange = "javascript: ";
		if ($action != "") {
			$onchange  .= "document.".$form_name.".action='".$action."';";
		}
			
		if ($javascript != "") {
			$onchange .= $javascript . ";";
		}
			
		$onchange .= "document.".$form_name.".submit();";

        if ($action != '' || $javascript != '') {
            $select->set_tag_attribute("onchange", $onchange);
        }

        return $select;
    }

    /**
     * This function returns any Javascript required
     * for this widget
     *
     * @return mixed
     */
    function _javascript() {
        $js = '';

        if ($this->_collapsable_search) {
            $js .= $this->_search_javascript();
        }


        if ($this->_has_action_column("FIRST") || $this->_has_action_column("LAST")) {
            $last = isset($this->_action_column["LAST"]["type"]) ? $this->_action_column["LAST"]["type"] : '';
            $first = isset($this->_action_column["FIRST"]["type"]) ? $this->_action_column["FIRST"]["type"] : '';
            if ($last == "checkbox" || $first == "checkbox") {
                $js .= $this->_checkbox_javascript();
            }
        }

        if (strlen($js) > 0) {
            $script = new SCRIPTtag(array('language' => 'Javascript', 'type' =>'text/javascript'));
            $script->add($js);
            return $script;
        } else {
            return NULL;
        }
    }

    /**
     * This function builds the JS needed for the checkbox
     * action column
     *
     * @return SCRIPTtag
     */
    function _checkbox_javascript() {
        $var_name = $this->_vars["checkboxVar"];

        $js  = "function mass(form) {\n";
        $js .= "  var i=0;\n";
        $js .= "  var value=0;\n\n";
        $js .= "  if (form.".$var_name.".checked) {\n";
        $js .= "    value=1;\n";
        $js .= "  } else {\n";
        $js .= "    value=0;\n";
        $js .= "  }\n\n";
        $js .= "  for (i = 0; i < form.length; i++) {\n";
        $js .= "    if (form.elements[i].name.substring(0, ".strlen($var_name).") == '".$var_name."' && !form.elements[i].disabled) {\n";
        $js .= "      form.elements[i].checked = value;\n";
        $js .= "    }\n";
        $js .= "  }\n";
        $js .= "}\n";

        return $js;
    }

    /**
     * This function builds the JS needed for
     * collapsable search
     *
     * @return string - js code
     */
    function _search_javascript() {
        $js = "var tree_open = new Image();\n".
              "tree_open.src = '" . PHPHTMLLIB_WIGDET_IMAGEPATH . "/tree_open.gif';\n".
              "var tree_closed = new Image();\n".
              "tree_closed.src = '" . PHPHTMLLIB_WIGDET_IMAGEPATH . "/tree_closed.gif';\n".

              "function toggle_tree(id) {\n".
              "element = document.getElementById(id);\n".
              "img = document.getElementById('i'+id);\n".
              "if (!element) return;\n".

              "if (element.style.visibility=='visible' || element.style.visibility=='') {\n".
              "    element.style.visibility = 'hidden';\n".
              "    element.style.overflow = 'hidden';\n".
              "    element.style.height='1px';\n".
              "    img.src = tree_closed.src;\n".

              "document.forms['" . $this->get_form_name() . "']._search_tree_open.value=0;\n".
              "}\n".
              "else {\n".
              "    element.style.visibility = 'visible';\n".
              "    element.style.overflow = 'visible';\n".
              "    element.style.height='';\n".
              "    img.src = tree_open.src;\n".
              "document.forms['" . $this->get_form_name() . "']._search_tree_open.value=1;\n".
              "}\n".
              "document.getElementById('l'+id).blur();\n".
              "}";

        return $js;
    }

    /**
     * Constructor - needed for early PHP 5.3.x compatibility
     *
     * @param Parent Constructor
     * @param array of Constructor Arguments
     */
    function DefaultGUIDataList() {
	    call_user_func_array('parent::DataList', func_get_args()) ;
    }
}

/**
 * This class defines the css used by the
 * FooterNav Object.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class DefaultGUIDataListCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry(".datalist_col_head", "",
                         array("font-family" => "arial, helvetica, sans-serif",
                               "font-size" => "10pt",
                               "font-weight" => "bold",
                               "color" => "#000000",
                               "background-color" => "#CCCCCC",
                               "text-align" => "left",
                               "white-space" => "nowrap",
                               "height" => "20px",
                               "vertical-align" => "middle",
                               "border-left" => "1px solid white",
                               "border-top" => "1px solid white",
                               "border-right" => "1px solid gray",
                               "border-bottom" => "1px solid gray",
                               "padding-left" => "3px",
                               "padding-right" => "3px") );

        $this->add_entry(".datalist_col_head", "a.head_link:active,a.head_link:visited,a.head_link:link",
                         array("color" => "#000000",
                               "font-family" => "arial, helvetica, sans-serif",
                               "font-size" => "10pt",
                               "font-weight" => "bold",
                               "text-decoration" => "none"));

        $this->add_entry(".datalist_col_head_hover", "",
                         array("font-family" => "arial, helvetica, sans-serif",
                               "font-size" => "10pt",
                               "font-weight" => "bold",
                               "color" => "#000000",
                               "background-color" => "#dcdcdc",
                               "text-align" => "left",
                               "white-space" => "nowrap",
                               "height" => "20px",
                               "vertical-align" => "middle",
                               "border-left" => "1px solid white",
                               "border-top" => "1px solid white",
                               "border-right" => "1px solid gray",
                               "border-bottom" => "1px solid gray",
                               "padding-left" => "3px",
                               "padding-right" => "3px") );

        $this->add_entry(".datalist_col_head_clicked", "",
                         array("font-family" => "arial, helvetica, sans-serif",
                               "font-size" => "10pt",
                               "font-weight" => "bold",
                               "color" => "#000000",
                               "background-color" => "#dddddd",
                               "text-align" => "left",
                               "white-space" => "nowrap",
                               "height" => "20px",
                               "vertical-align" => "middle",
                               "border-left" => "1px solid white",
                               "border-top" => "1px solid white",
                               "border-right" => "1px solid gray",
                               "border-bottom" => "1px solid gray",
                               "padding-left" => "3px",
                               "padding-right" => "3px") );

        $this->add_entry( ".datalist_border", "",
                          array("border" => "1px solid #999999"));

        $this->add_entry( ".datalist_title", "",
                          array("font-family" => "arial",
                                "font-size" => "10pt",
                                "font-weight" => "bold",
                                "color" => "#FFFFFF",
                                "background-color" => "#999999",
                                "white-space" =>"nowrap"));

        $this->add_entry( ".datalist_data_cell", "",
                          array(
                               "font-family" => "arial",
                               "font-size" => "10pt",
							   "background-color" => "#ffffff",
                               "padding-left" => "3px",
                               "padding-right" => "3px",
                               "border-top" => "1px solid #dddddd"));

        $this->add_entry( ".datalist_data_cell_selected", "",
                          array(
                               "font-family" => "arial",
                               "font-size" => "10pt",
                               "background-color" => "#f7f7f7",
                               "padding-left" => "3px",
                               "padding-right" => "3px",
                               "border-top" => "1px solid #dddddd"));

		$this->add_entry( ".datalist_data_cell_odd", "",
                          array(
                               "font-family" => "arial",
                               "font-size" => "10pt",
							   "background-color" => "#fafafa",
                               "padding-left" => "3px",
                               "padding-right" => "3px",
                               "border-top" => "1px solid #dddddd"));

        $this->add_entry( ".datalist_data_cell_odd_selected", "",
                          array(
                               "font-family" => "arial",
                               "font-size" => "10pt",
                               "background-color" => "#f7f7f7",
                               "padding-left" => "3px",
                               "padding-right" => "3px",
                               "border-top" => "1px solid #dddddd"));

        $this->add_entry( ".datalist_actionbar", "",
                          array(
                               "border" => "1px solid #999999") );

        $this->add_entry( ".datalist_actionbar_data_cell", "",
                          array(
                               "font-family" => "arial",
                               "font-size" => "10pt",
                               "background" => "#CCCCCC",
                               "padding-left" => "3px",
                               "padding-right" => "3px",
                               "border-top" => "1px solid #dddddd"));

        $this->add_entry( ".datalist_bottom_seperator", "",
                          array(
                               "font-size" => "5px",
                               "line-height" =>  "5px",
                               "background" => "#CCCCCC",
                               "text-align" => "left",
                               "white-space" => "nowrap",
                               "height" => "5px",
                               "border-left" => "1px solid #FFFFFF",
                               "border-top" => "1px solid #FFFFFF",
                               "border-right" => "1px solid #dddddd",
                               "border-bottom" => "1px solid #dddddd",
                               "padding-left" =>  "3px",
                               "padding-right" => "3px"));
    }   
}
?>
