<?php
/**
 * This file holds the ListAction object, which
 * can be used to handle an action from a post
 * of the checkbox data from the DefaultGUIDataList
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */

/**
 * A class for showing a list of items
 * to preform an action on
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */ 
class ListAction extends DataList {
    
    /**
     * The string that describes
     * the action 
     * ie. 'delete'
     */
    var $_action_name = 'delete';


    /**
     * name/description of the type of
     * data we are working on
     * ie 'users', 'files'
     */
    var $_item_name = '';
     
    /**
     * The overall alignment 
     *
     * DEFAULT: "center"
     */
    var $_align = "center";


    /**
     * A flag to tell us to save all
     * vars passed
     */
    var $_save_all_vars = TRUE;

    /**
     * This sets the url for the
     * cancel action to post to
     */
    var $_cancel_url = "index.php";


    /**
     * The name of the array variable
     * that the data was posted to us
     *
     */
    var $_data_post_name = "checkbox";


    /****************************************/
    /*  The required DataList child methods */
    /****************************************/

    /**
     * Initialize the gui layout
     * 
     */
    function gui_init() {

        $this->set_form_render(TRUE);
        $this->search_disable();

        $this->_data_table = html_table($this->get_width(),0,0,0,
                                        $this->_align);
		$this->_data_table->set_class("datalist_border");

        //add the header tr reference
		//it will get populated later
		$this->_header_tr = new TRtag;

        //initialize the first date row
		$this->_data_row = new TRtag;

        if (!is_array($_REQUEST[$this->_data_post_name]) ||
             $data_post_count <= 0) {
            // The user didn't select anything to delete.
            $err_string = "Please select at least one ". $this->_item_name. " to delete.";
            $dialog = messagebox_ok("Error", $err_string, "index.php?tab_selected=$tab_selected&showall=$showall",
                                    array(), "50%");
            return $dialog;
        }
    }

	function child_get_gui() {
        $this->_build_hidden_vars();
        $wrapper = $this->_build_delete_confirm();
        $wrapper->add($this->_data_table);
        return $wrapper;
        //return container( $this->_data_table );
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
     * This builds the hidden form fields
     * of the data that was originally sent
     * to us
     *
     * @return Container
     */
    function _build_hidden_vars() {
        $save_vars = array();
        $x=0;
        if ($_REQUEST[$this->_data_post_name]) {
            foreach ( $_REQUEST[$this->_data_post_name] as $value ) {
                $save_vars[$this->_data_post_name."[".$x."]"] = $value;
                $x++;
            }
            $this->set_save_vars( $save_vars );
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

        if ($this->_columns[$col_name]["sortable"]) {
            $col_url = $this->build_column_url($col_name);

            $td->set_tag_attribute("title","Sort By ".$col_name);

            $td->push(html_a($col_url, $col_name,"form_link"));

            if ($this->_columns[$col_name]["data_name"] == $this->orderby()) {

                if ($this->reverseorder() == "false") {
					$alt_title = "Sorted in Ascending Order";
                    $img = html_img($this->get_image_path()."/picto_down.gif",11,11,'',$alt_title);
                    $img->set_tag_attribute("style", "padding-left: 5px;margin-left:5px;vertical-align:middle;");
                    $td->push($img);
                } else {
					$alt_title = "Sorted in Descending Order";
                    $img = html_img($this->get_image_path()."/picto_up.gif",11,11,'',$alt_title);
                    $img->set_tag_attribute("style", "padding-left: 5px;margin-left:5px;vertical-align:middle;");
                    $td->push($img);
                }
            }

            // we want to highlight the td on mouse over
            $td->set_tag_attribute("onMouseOver",
                                   "javascript:style.cursor='pointer';this.className='datalist_col_head_hover';");
            $td->set_tag_attribute("onMouseOut",
                                   "javascript:this.className='datalist_col_head'");
            $td->set_tag_attribute("onMouseDown",
                                   "javascript:this.className='datalist_col_head_clicked'");


            if ($this->get_form_method() == "POST") {
                $td->set_tag_attribute("onclick", $col_url);
            }
            else {
                $td->set_tag_attribute("onclick", "javascript:document.location='".$col_url."';");
            }
        } else {
            $td->push($col_name);
            $td->set_tag_attribute("style", $style."padding-left:5px;padding-right:5px;white-space:nowrap;");
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
    function wrap_column_item($obj, $col_name) {

        //make sure its set to something.
        if ($obj == '') {
            $obj = "&nbsp;";
        }

        //make sure we don't put a right border on the last
        //column we are working on.
        //$style = "padding-left: 3px;padding-right:3px;border-top: 1px solid #dddddd;";
        

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



    /****************************************/
    /*  The Methods specific to the logic   */
    /*  of handling the action.             */
    /****************************************/



    /**
     * Build any additional custom options
     * such as checkboxes, radiobuttons
     * for special options for the action.
     */
    function build_options() {
        return NULL;
    }


    /**
     * This method is used to build the portion 
     * of the DB query that limits the list of
     * items to show based on what was submitted
     * from the original DataList action
     *
     * @param string - the field 
     * @return string
     */
    function build_in_clause($field) {

        if (!$_REQUEST[$this->_data_post_name]) {
            return NULL;
        } else {
            $clause = $field." in (";
            foreach ($_REQUEST[$this->_data_post_name] as $value ) {
                $query .= "'".$value."',";
            }
            
            $query = substr($query, 0, strlen($query)-1);
            $clause .= $query .") ";
            return $clause;
        }
    }


    /**
    * This function builds the actual form
    */
    function _build_delete_confirm() {

        $showall = $_REQUEST["showall"];
        $data_post_count = count($_REQUEST[$this->_data_post_name]);

        $container = container();

        

        // handle plural case
        if ($data_post_count > 1) $plural = "s";
        else $plural = "";

        $table = new InfoTable(ucfirst($this->_action_name) . " Confirmation", $this->get_width());

        $content = html_table("100%");
        //$content->set_default_col_attributes(array("class"=>"f10-1"));

        $td = new TDTag(array("class"=>"f10-1","align"=>"center"));
        $td->push(html_br(),
                  html_b("Are you sure you want to ".$this->_action_name." the following " . $this->_item_name . $plural . "?"),
                  html_br(),html_br());

        $content->add_row($td);

        // add any additional options
        if ($options = $this->build_options()) $content->add_row($options);

        // buttons
        $buttons = new ButtonPanel(1, "center");
        $buttons->add(form_button("yes","Yes", array("type"=>"submit","style"=>"width: 90px;")));

        $cancel_url = $this->get_cancel_url();
        $form_name = $this->get_form_name();
        $cancel_action = "document.".$form_name.".action='".$cancel_url."'; document.".$form_name.".method='POST'; document.".$form_name.".submit();";

        $buttons->add(form_button("no","No",
                                         array("type"=>"button",
                                               "style"=>"width: 90px;",
                                               "onclick"=>$cancel_action)));
        $content->push_row($buttons);

        $td = new TDTag(array("class"=>"f10-1","align"=>"center","style"=>_CSS_BORDER_TOP));
        $td->add(_HTML_SPACE);
        $content->add_row($td);

        $content->add_row(_HTML_SPACE);

        $table->add_row($content);

        $container->add( $table );

        $container->add(form_hidden("confirmed", "yes"));

        //do this hack to make the cancel button not bust
        //the next page.
        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            unset($_POST["checkbox"]);
        } else {
            unset($_GET["checkbox"]);
        }

        return $container;
    }



    /****************************************/
    /*      The utility/param methods       */
    /****************************************/



    /**
     * this function is used to set the overall alignment
     * of the widget
     *
     * @param string - the align value
     */
    function set_align($align) {
        $this->_align = $align;
    }


    /**
     * Set the name of the deleted items
     * used for display purposes only
     */
    function set_item_name($item) {
        $this->_item_name = $item;
    }

    /**
     * Set the name of the action
     * used for display purposes only
     */
    function set_action_name($item) {
        $this->_action_name = $item;
    }

    /**
     * This method sets the flag that
     * tells us to automatically add
     * hidden form fields for all
     * the GET/POST vars passed in to us.
     *
     */
    function set_save_vars_Flag($flag=TRUE) {
        $this->_save_all_vars = TRUE;
    }

    /**
     * This sets the url to post to
     * when a cancel/no action is clicked
     *
     * @param string - the url
     */
    function set_cancel_url( $url ) {
        $this->_cancel_url = $url;
    }

    /**
     * this returns the current cancel url
     *
     * @return string - the url
     */
    function get_cancel_url() {
        return $this->_cancel_url;
    }



}
?>
