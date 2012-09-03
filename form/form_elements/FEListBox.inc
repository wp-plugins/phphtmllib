<?php
/**
 * This file contains the FEListBox, FEMultiListBox
 *
 * $Id: FEListBox.inc 3568 2012-09-03 13:47:40Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosyan <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This is the ListBox FormElement which builds a
 * select field with all of its options.
 * It has no validation method.
 *
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEListBox extends FEDataList {

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    function get_element() {

        $attributes = $this->_build_element_attributes();

        if ($this->_height) {
            $attributes["size"] = 5;
        }

        $selected_value = $this->get_value();

        $tag = new SELECTtag($attributes);

        foreach ($this->_data_list as $name=>$value) {

            $attributes = array("value"=>$value);
            if ($value == $selected_value) {
                $attributes['selected'] = "selected";
            }
            if (isset($this->_disabled_items[$name])) {
                $attributes['disabled'] = "disabled";
            }

            $tag->add(new OPTIONtag($attributes, htmlspecialchars($name)));
        }
        return $tag;
    }

    /**
     * Constructor - needed for early PHP 5.3.x compatibility
     *
     * @param Parent Constructor
     * @param array of Constructor Arguments
     */
    function FEListBox() {
	    $args = func_get_args() ;
	    call_user_func_array(array('FEDataList', 'FEDataList'), $args) ;
    }
}

/**
 * Build a Yes/No Select box
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEYesNoListBox extends FEListBox {

    /**
     * The Constructor
     *
     * @param label string - text label for the element
     * @param bool required - is this a required element
     * @param array data_list - list of data elements (name=>value)
     * @param int required - element width in characters, pixels (px), percentage (%) or elements (em)
     * @param string - the value to use for the 'yes' radio
     *                 NOTE: default is 'yes'
     * @param string - the value to use for the 'no' radio
     *                 NOTE: default is 'no'
     */
    function FEYesNoListBox($label, $required = TRUE, $width = NULL, $height = NULL,
                            $yes_value="yes", $no_value="no") {
        $options = array("Yes" => $yes_value, "No" => $no_value);
	parent::FEListBox($label, $required, $width, $height, $options);
    }
}


/**
 * This class builds a nested select box that
 * is used to select an entry from nested levels.
 *
 * NOTE: The data array must be in the format
 *       array("test" => "testvalue",
 *             "nestedtest" => array("value" => "nestedtestvalue",
 *                                   "items" => array( "foo" => "foovalue",
 *                                                     "bar" => "barvalue"));
 *
 * Example
 * $data = array("Test" => 1,
 *               "Foo" => array("value" => 2,
 *                              "items" => array("Blah" => 3,
 *                                               "php" => 4)),
 *               "Bar" => array("value" => 5,
 *                              "items" => array("testing" => array("value" => 6,
 *                                                                  "items" => array("ugh" => 7)),
 *                                               "again" => 8)));
 *
 * would result in
 *
 * <select >
 *  <option value="1">Test</option>
 *  <option value="2">Foo</option>
 *  <option value="3">&nbsp;&nbsp;Blah</option>
 *  <option value="4">&nbsp;&nbsp;php</option>
 *  <option value="5">Bar</option>
 *  <option value="6">&nbsp;&nbsp;testing</option>
 *  <option value="7">&nbsp;&nbsp;&nbsp;&nbsp;ugh</option>
 *  <option value="8">&nbsp;&nbsp;again</option>
 * </select>
 *
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FENestedListBox extends FEDataList {

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    function get_element() {

        $attributes = $this->_build_element_attributes();

        if ($this->_height) {
            $attributes["size"] = 5;
        }

        $tag = new SELECTtag($attributes);

        $this->_add_array($this->_data_list, 0, $tag);
        return $tag;
    }


    /**
     *
     * This function is responsible for performing complete
     * validation and setting the appropriate error message
     * in case of a failed validation
     *
     * @param FormValidation object
     */
    function validate(&$_FormValidation) {
        // we make sure that the value is in the data list
        $value = $this->get_value();

        if (!$this->_array_search_r($value, $this->_data_list, $temp)) {
        	$this->set_error_message("Invalid value");
            return FALSE;
        }
        return TRUE;
    }


    function _array_search_r($needle, $haystack, &$item) {
        //xxx($needle);
        $match = FALSE;

        foreach($haystack as $name=>$value) {
            if (is_array($value)) {
                if ($value["value"] == $needle) {
                    $item = $name;
                    $match = TRUE;
                } else {
                    $match = $this->_array_search_r($needle, $value["items"], $item);
                    $item = $name."::".$item;
                }
            } else if ($value==$needle) {
                $item = $name;
                $match = TRUE;
            }

            if ($match)
                return TRUE;
        }
        return $match;
    }


    /**
     * This provides a method
     * for the FormContent
     * to get access to the
     * text associated with a
     * field.  This is only available
     * on FormElements that have text
     * associated with a field.
     * It is used during Confirmation
     *
     * @return string - the text associated
     */
    function get_value_text() {
        $ret = $this->_array_search_r($this->get_value(),
                                      $this->_data_list, $item);
        return $item;
    }


    /**
     * This is a recursive function used to add
     * an array of layers to the select box.
     *
     * @param array - the next level of name=>value pairs
     * @param int - the level
     * @param SELECTtag - the SELECTtag object to add the options
     * @return none
     */
    function _add_array($layer_arr, $level, &$tag) {
        if (!is_array($layer_arr)) {
            return;
        }

        foreach( $layer_arr as $name=>$value) {
            if (is_array($value)) {
                $tag->add( $this->_build_option($name, $value["value"], $level));
                $this->_add_array($value["items"], $level+1, $tag);
            } else {

                $tag->add($this->_build_option($name, $value, $level));
            }
        }
    }

    /**
     * This method builds the actual OPTIONtag object
     *
     * @param string the name
     * @param string the value
     * @param int the level
     * @return OPTIONtag object
     */
    function _build_option($name, $value, $level) {
        $selected_value = $this->get_value();

        $attributes = array("value"=>$value);
        if ($value == $selected_value) {
            $attributes['selected'] = "selected";
        }

        if (isset($this->_disabled_items[$name])) {
            $attributes['disabled'] = "disabled";
        }

        return new OPTIONtag($attributes, $this->_layer_name($name, $level));
    }

    /**
     * This builds a layer's name
     *
     * @param string - original name
     * @param int the layer level
     * @return string the new name
     */
    function _layer_name($name, $level) {
        $newname = '';

        if ($level == 0) {
            return $name;
        } else {
            $newname .= str_repeat(_HTML_SPACE, $level*2).$name;
        }

        return $newname;
    }
}


/**
 * This is the MultiListBox FormElement which builds a
 * select field with all of its options.  It enables
 * the ability to have multiple selections.
 * It has no validation method.
 *
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEMultiListBox extends FEListBox {


    /**
     * This function creates element name
     * used in the form based on the text label
     * or any other parameters
     *
     * Overriding things function to make sure
     * an array is created instead of a single variable
     */
    function create_element_name() {

        parent::create_element_name();

        $this->_element_name .= "[]";
    }

    /**
     * build the string for the confirmation page
     *
     * @return string
     */
    function get_value_text() {
        $value = $this->get_value();
        if (empty($value)) {
            return '';
        }

        $data_flip = array_flip( $this->_data_list );
        foreach( $value as $val ) {
            $ret[] = $data_flip[$val];
        }
        return implode(", ", $ret);
    }

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    function get_element() {

        $attributes = $this->_build_element_attributes();

        $attributes['multiple'] = "multiple";

        if ($this->_height) {
            $attributes["size"] = 5;
        }

        $selected_values = $this->get_value();

        $tag = new SELECTtag($attributes);

        foreach ($this->_data_list as $name=>$value) {

            $attributes = array("value"=>$value);
            if (is_array($selected_values) && in_array($value, $selected_values)) {
                $attributes['selected'] = "selected";
            }
            if (isset($this->_disabled_items[$name])) {
                $attributes['disabled'] = "disabled";
            }

            $tag->add(new OPTIONtag($attributes, $name));
        }
        return $tag;
    }
}

/**
 * This class builds a FEDataList that shows
 * a select box for States of the U.S.A.
 *
 * @author Walter A. Boring IV
 */
class FEUnitedStates extends FEListBox {

    /**
     * The states array
     * @var array
     */
    var $_states = array("Select State" => "",
                         "Alabama" => "AL",
                         "Alaska" => "AK",
                         "Arizona" => "AZ",
                         "Arkansas" => "AR",
                         "California" => "CA",
                         "Colorado" => "CO",
                         "Connecticut" => "CT",
                         "Deleware" => "DE",
                         "District of Columbia" => "DC",
                         "Florida" => "FL",
                         "Georgia" => "GA",
                         "Hawaii" => "HI",
                         "Idaho" => "ID",
                         "Illinois" => "IL",
                         "Indiana" => "IN",
                         "Iowa" => "IA",
                         "Kansas" => "KS",
                         "Kentucky" => "KY",
                         "Louisiana" => "LA",
                         "Maine" => "ME",
                         "Maryland" => "MD",
                         "Massachusetts" => "MA",
                         "Michigan" => "MI",
                         "Minnesota" => "MN",
                         "Mississippi" => "MS",
                         "Missouri" => "MO",
                         "Montana" => "MT",
                         "Nebraska" => "NE",
                         "Nevada" => "NV",
                         "New Hampshire" => "NH",
                         "New Jersey" => "NJ",
                         "New Mexico" => "NM",
                         "New York" => "NY",
                         "North Carolina" => "NC",
                         "North Dakota" => "ND",
                         "Ohio" => "OH",
                         "Oklahoma" => "OK",
                         "Oregon" => "OR",
                         "Pennsylvania" => "PA",
                         "Rhode Island" => "RI",
                         "South Carolina" => "SC",
                         "South Dakota" => "SD",
                         "Tennessee" => "TN",
                         "Texas" => "TX",
                         "Utah" => "UT",
                         "Vermont" => "VT",
                         "Virginia" => "VA",
                         "Washington" => "WA",
                         "West Virginia" => "WV",
                         "Wisconsin" => "WI",
                         "Wyoming" => "WY",
                         "Puerto Rico" => "PR",
                         "Virgin Island" => "VI",
                         "Northern Mariana Islands" => "MP",
                         "Guam" => "GU",
                         "American Samoa" => "AS",
                         "Palau" => "PW",
                        );

    /**
     * The constructor
     *
     * @param string text label for the element
     * @param boolean is this a required element?
     * @param int element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int element height in px
     * @param array data_list - list of data elements (name=>value)
     */
    function FEUnitedStates($label, $required = TRUE, $width = NULL, $height = NULL) {
    	parent::FEListBox($label, $required, $width, $height, $this->_states);
    }
}

/**
 * This class builds a FEDataList that shows
 * a select box for states of the European Union.
 */
class FEEuropeanUnion extends FEListBox {
    /**
     * The states array
     * @var array
     */
    var $_states = array("Select Country" => "",
                         "Belgium" => "be",
                         "Denmark" => "dk",
                         "Germany" => "de",
                         "Greece" => "gr",
                         "Spain" => "es",
                         "France" => "fr",
                         "Ireland" => "ie",
                         "Italy" => "it",
                         "Luxembourg" => "lu",
                         "The Netherlands" => "nl",
                         "Austria" => "at",
                         "Portugal" => "pt",
                         "Finland" => "fi",
                         "Sweden" => "se",
                         "United Kingdom" => "uk",
                         "Czech Republic" => "cz",
                         "Estonia" => "ee",
                         "Cyprus" => "cy",
                         "Latvia" => "lv",
                         "Lithuania" => "lt",
                         "Hungary" => "hu",
                         "Malta" => "mt",
                         "Poland" => "pl",
                         "Slovenia" => "si",
                         "Slovakia" => "sk",
                        );

    /**
     * The constructor
     *
     * @param string text label for the element
     * @param boolean is this a required element?
     * @param int element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int element height in px
     * @param array data_list - list of data elements (name=>value)
     */
    function FEEuropeanUnion($label, $required = TRUE, $width = NULL, $height = NULL) {
    	parent::FEListBox($label, $required, $width, $height, $this->_states);
    }
}


/**
 * This builds a complex dual select box
 * with buttons to move entries from one
 * select box to another.
 *
 * <pre>
 * From      Actions    To
 * --------  Add >>     --------
 * |------|  Add All    |------|
 * |------|             |------|
 * |------|             |------|
 * |------|  << Remove  |------|
 * |------|  Remove All |------|
 * |------|             |------|
 * --------             --------
 * </pre>
 *
 * @author Walter A. Boring IV
 */
class FEComboListBox extends FEDataList {


    /**
     * Holds the list of available
     * data elements for the 'to'
     * box.
     *
     */
    var $_data_list_to = array();

    /**
     * The from field's label
     *
     * @var string
     */
    var $_from_label = 'Available';

    /**
     * The to field's label
     *
     * @var string
     */
    var $_to_label = 'Selected';

    /**
     * This Form Element needs to
     * propogate some js to the
     * Form tag's onsubmit attribute
     *
     * @var string
     */
    var $_has_form_on_submit = true;

	/**
	 * This flag turns on/off the
	 * ordering mechanism
	 */
	var $_ordering = TRUE;

	/**
	 * This is an array of all the required
	 * elements for the select list
	 */
	var $_required_values = array();
	

    /**
     * The constructor
     *
     * @param string text label for the element
     * @param boolean is this a required element?
     * @param int element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int element height in px
     * @param array list of 'from' field data elements (name=>value)
     * @param array list of 'to' field data elements (name=>value)
     */
    function FEComboListBox($label, $required = TRUE, $width="200px", $height="100px",
                            $from_data_list = array(), $to_data_list = array()) {
        $this->set_to_list_data($to_data_list);
        $this->FEDataList($label, $required, $width, $height, $from_data_list);
    }

    /**
     * This function sets the array of data
     * to be used in the data list
     *
     * @param array data_list - list of data elements (name=>value)
     */
    function set_to_list_data( $data_list = array() ) {
        $this->_data_list_to = $data_list;
    }

    /**
     * Use this method to set the label for the
     * 'from' field
     *
     * @param string
     * @return none
     */
    function set_from_label($label) {
        $this->_from_label = $label;
    }

    /**
     * Use this method to set the label for the
     * 'to' field
     *
     * @param string
     * @return none
     */
    function set_to_label($label) {
        $this->_to_label = $label;
    }

    /**
     * Use this method to set required select values
     *
     * @param array array of valid select list values
     * @return none
     */
    function set_required_values($required) {
        $this->_required_values = $required;
    }
    
    /**
     * This returns the initial value of
     * the element
     *
     * @return mixed
     */
    function get_init_value() {
		if (array_key_exists($this->_element_name, $_REQUEST)) {
            $all_list = array_merge( $this->_data_list, $this->_data_list_to);

            if (isset($_REQUEST[$this->_element_name])) {
                $diff = array_diff( $all_list, $_REQUEST[$this->_element_name]);
                $this->set_list_data( $diff );
                $to_list = array();

                if (is_array($_REQUEST[$this->_element_name])) {
                    foreach( $_REQUEST[$this->_element_name] as $value ) {
                        $key = array_search($value, $all_list);
                        if ($key) {
                            $to_list[$key] = $value;
                        }
                    }
                } else {
                    if (!empty($_REQUEST[$this->_element_name])) {
                        $to_list[array_search($_REQUEST[$this->_element_name], $all_list)] = $_REQUEST[$this->_element_name];
                    }
                }
                $this->set_to_list_data( $to_list );
            } else {
                //the assigned list is empty
                $this->set_list_data( $all_list );
                $this->set_to_list_data(array());
			}
		}
		return $this->_data_list_to;
    }


    /**
     * This function will set the
     * initial value for the element
     *
     * @param value mixed
     */
    function set_value($value) {
		//we need to diff what is available and what is
		//selected so that we don't show duplicated entries.            
		if (!is_array($value)) {
			//$this->set_list_data( $diff );
			$this->set_to_list_data(array());
		} else {
			$diff = array_diff( $this->_data_list, $value);
			$this->set_list_data( $diff );
			$this->set_to_list_data($value);
		}			
    }


	/**
	 * This method turns on the right select box's
	 * ability to show the ordering buttons.
	 * 
	 * @param bool
	 */
	function enable_ordering($flag=TRUE) {
		$this->_ordering = $flag;
	}



    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    function get_element() {
        $table = html_table();
        $table->add_row($this->_from_label, _HTML_SPACE,
                        $this->get_label(NULL,$this->_to_label, FALSE));

        $from_select = form_select($this->_element_name.'_available',
                                   $this->_data_list,'', TRUE);

        if ($this->onChangeJS != null) {
            $from_select->set_tag_attribute("onChange", $this->onChangeJS);
        }

		$from_select->set_tag_attribute('id', $this->build_id_name().'_from');

        $style = '';
        if ($this->_height) {
            $style .= "height: ".$this->_height.";";
        }
        if ($this->_width) {
            $style .= "width: ".$this->_width.";";
        }

        //build the buttons
        $button_style = 'width: 90px;';
        $f_name = $this->_element_name."_move_around";
        $add = form_button($this->_element_name.'_add', 'Add >>', array('style' => $button_style,
                                                                        'onclick' => $f_name."('right',false);"));
        $add_all = form_button($this->_element_name.'_add_all', 'Add All', array('style' => $button_style,
                                                                                 "onclick" => $f_name."('right', true);"));

        $remove = form_button($this->_element_name.'_remove', '<< Remove', array('style' => $button_style,
                                                                                 'onclick' => $f_name."('left', false);"));
        $remove_all = form_button($this->_element_name.'_remove_all', 'Remove All', array('style' => $button_style,
                                                                                          'onclick' => $f_name."('left', true);"));

        $to_select = form_select($this->_element_name.'[]',
                                 $this->_data_list_to, '', TRUE);

        if (strlen($style) > 0) {
            $from_select->set_style($style);
            $to_select->set_style($style);
        }

        //check to see if we are disabled
        if ($this->is_disabled()) {
            $from_select->set_tag_attribute('disabled');
            $add->set_tag_attribute('disabled');
            $add_all->set_tag_attribute('disabled');
            $remove->set_tag_attribute('disabled');
            $remove_all->set_tag_attribute('disabled');
            $to_select->set_tag_attribute('disabled');
        }

		$to_select->set_tag_attribute('id', $this->build_id_name().'_to');


        $button_td = new TDtag(array('align' => 'left'),
                                   $add, html_br(), $add_all, html_br(2),
                                   $remove, html_br(), $remove_all);

		$f_name = $this->_element_name."_order";

		$move_up = form_button('Move Up', 'Move Up', array('onclick' => "javascript: ".$f_name."(0)"));
		$move_down = form_button('Move Down', 'Move Down', array('onclick' => "javascript: ".$f_name."(1)"));

        //IE sucks.
        $button_td->set_collapse();

		$tr = html_tr();
		$tr->add( $from_select, 
				  $button_td,
				  $to_select);

		if ($this->_ordering) {
			$tr->add(container($move_up, $move_down));
		}
        $table->add_row( $tr );

        return $table;
    }

    /**
     *
     * This function is responsible for performing complete
     * validation and setting the appropriate error message
     * in case of a failed validation
     *
     * NOTE: This makes sure that the data submitted for both
     *       fields is in the original list.
     *
     * @param FormValidation object
     */
    function validate(&$_FormValidation) {
        //need to make sure we only allow
        //elements that the class has.
        $combined = array_flip(array_merge( $this->_data_list, $this->_data_list_to));
        
        if (isset($_REQUEST[$this->_element_name])) {
            if (is_array($_REQUEST[$this->_element_name])) {
                foreach( $_REQUEST[$this->_element_name] as $value ) {
                    if (!isset($combined[$value])) {
                        return FALSE;
                    }
                }
                return TRUE;
            } else {
                if (!isset($combined[$value])) {
                    return FALSE;
                } else {
                    return TRUE;
                }
            }
        } else {
            //empty value
            return TRUE;
        }

        return TRUE;
    }

    /**
     * This provides a method
     * for the FormContent
     * to get access to the
     * text associated with a
     * field.  This is only available
     * on FormElements that have text
     * associated with a field.
     * It is used during Confirmation
     *
     * @param mixed - the value to look up
     * @return string - the text associated
     */
    function get_value_text() {
        return implode( ", ", array_keys( $this->get_value() ) );
    }

    /**
     * This is a method for getting the JS needed
     * for the form tag's onsubmit attribute.
     *
     * @return string
     */
    function form_tag_onsubmit() {
        return $this->_element_name.'_check_submit();';
    }


    /**
     * This method builds the Javascript needed for this
     * element.
     *
     * @return string The javascript.
     */
    function javascript() {

		$from_id = $this->build_id_name().'_from';
		$to_id = $this->build_id_name().'_to';

        $js =  "function ".$this->_element_name."_move_around(direction, all) {\n".
               "  if (direction==\"right\") {\n".
               "    box1 = \"".$this->_element_name."_available\";\n".
               "    box2 = \"".$this->_element_name."[]\";\n".
               "  } else {\n".
               "    box1 = \"".$this->_element_name."[]\";\n".
               "    box2 = \"".$this->_element_name."_available\" + \"\";\n".
               "  }\n".

               "  for (var i=0;i<document.forms[0].elements[box1].length;i++) {\n";
               
        // Display a javascript error for any demographics that shouldn't be moved
        if (!empty($this->_required_values)) {
	        foreach ($this->_required_values as $required) {
				$required_list[] = "document.forms[0].elements[box1][i].value == $required";
			}
        	
			$required_list = join(" || ",$required_list);			
			
			$js .= "	if (direction==\"left\" && (document.forms[0].elements[box1][i].selected || all) && ".
				   "	(".$required_list . ")) {\n".
			       "		alert(document.forms[0].elements[box1][i].innerHTML + ' is required');\n".
			       "	}\n".
			       "	else if ((document.forms[0].elements[box1][i].selected || all)) {\n";
        } else {
        	$js .= "	if ((document.forms[0].elements[box1][i].selected || all)) {\n";	
        }
        
        $js .= "      // add to the other list box\n".
               "      document.forms[0].elements[box2].options[document.forms[0].elements[box2].length] =".
               "    new Option(document.forms[0].elements[box1].options[i].text, document.forms[0].elements[box1][i].value);\n".
               "      // remove from the current listbox\n".
               "      document.forms[0].elements[box1][i] = null;\n".
               "      i--;\n".
               "    }\n".
               "   }\n".
               "}\n";
               

        $js .= "\nfunction ".$this->_element_name."_check_submit() {\n".
               "  // select all items in the added ip list\n".
               "  // in order to include in the post data\n".
               "  box = \"".$this->_element_name."[]\";\n".
               "  if (document.forms[0].elements[box]) {\n".
               "    for (var i=0;i<document.forms[0].elements[box].length;i++) {\n".
               "      document.forms[0].elements[box][i].selected = true;\n".
               "    }\n".
               "  }\n".

               "  // disable the buttons\n".
               "  //document.forms[0]._form_action1.disabled = true;\n".
               "  //if (document.forms[0]._form_action2)\n".
               "  //    document.forms[0]._form_action2.disabled = true;\n".
               "  //document.forms[0].cancel.disabled = true;\n".
               "  return true;\n".
               "}\n";


		//the to select box ordering
		$js .=  "\nfunction ".$this->_element_name."_order(down) {\n".
                "  to = document.getElementById('".$to_id."'); \n".
				"  sl = to.selectedIndex; \n".
				"  if ((sl != -1) && (to.options[sl].value > '')) {\n".
				"    oText = to.options[sl].text;\n".
				"    oValue = to.options[sl].value;\n".
				"    if ((to.options[sl].value > '') && (sl > 0) && (down == 0)) {\n".
				"      to.options[sl].text = to.options[sl-1].text;\n".
				"      to.options[sl].value = to.options[sl-1].value;\n".
				"      to.options[sl-1].text = oText;\n".
				"      to.options[sl-1].value = oValue;\n".
				"      to.selectedIndex--;\n".
				"    } else if ((sl < to.length-1) && (to.options[sl+1].value > '') && (down == 1)) {\n".
				"      to.options[sl].text = to.options[sl+1].text;\n".
				"      to.options[sl].value = to.options[sl+1].value;\n".
				"      to.options[sl+1].text = oText;\n".
				"      to.options[sl+1].value = oValue;\n".
				"      to.selectedIndex++;\n".
				"    }\n".
				"  } else {\n".
				"    alert('Please select an entry to move');\n".
				"  }\n".
               "}\n";

        return trim($js);
    }

    /**
     * This function will return the
     * elements value
     *
     * @return mixed
     */
    function get_value(){
        return $this->_data_list_to;
    }


    /**
     * This method returns the hidden version of this
     * element for a confirmation page.
     *
     * NOTE: This is called by the FormProcessor only.
     * It shouldn't be called manually.
     *
     * @return INPUTtag of type hidden
     */
    function get_confirm_element(){
        $name = $this->get_element_name();

        $c = container();
        if (is_array( $_REQUEST[$name]) ) {
            foreach( $_REQUEST[$name] as $value ){
                $c->add(form_hidden( $name."[]", $value));
            }
        } else {
            $c->add(form_hidden($name."[]", $_REQUEST[$name] ));
        }

        return $c;
    }
}

/**
 * This class builds the FEComboList with buttons below each element
 *
 * @author Sumedh Thakar
 */
class FEComboListButtonsBox extends FEComboListBox {

    /**
     * This variable holds the button array
     */
    var $_button_info = array();
    /**
     * this function sets the array of buttons and related info
     * array is of format
     * array('left' => array(
     *                       array(
     *                        'name'=> 'expand',
     *                        'value' => 'Expand it",
     *                        'onclick'=> 'some_function()',
     *                        'js' => 'function some_function(){ alert('hi'); }'     *                        ),
     *                  )
     *       )
     * @author Sumedh Thakar
     * @param array of buttons and related info
     */
    function set_button_array($button_array){
        $this->_button_info = $button_array;
    }

    function javascript(){
        $js = parent::javascript();
        if(count($this->_button_info)){
            foreach ($this->_button_info as $side){
                foreach ($side as $button){
                    if(isset($button['js'])) $js .= " ".$button['js']." ";
                }
            }
        }
        return $js;
    }

    function get_element(){
        $table = parent::get_element();
        if(empty($this->_button_info)) return $table;
        if (isset($this->_button_info['left'])){
        	$lbuttons = new TDtag();
        	foreach($this->_button_info['left'] as $butt) {
        	
        	    $attributes = array();
        	    if (strlen($butt['value'])>12) $attributes["style"] = "padding-left:6px;padding-right:6px;";
                else $attributes["style"] = "width:100px;";
                $attributes["onClick"] = $butt['onclick'];

	        	$lbuttons->add(form_button(
	                                $butt['name'],
	                                $butt['value'],
	                                $attributes),
	                                _HTML_SPACE);
        	}
        }else{
        	$lbuttons = _HTML_SPACE;
        }
        if (isset($this->_button_info['right'])){
        	$rbuttons = new TDtag();
        	foreach($this->_button_info['right'] as $butt) {
        	
        	    $attributes = array();
        	    if (strlen($butt['value'])>12) $attributes["style"] = "padding-left:6px;padding-right:6px;";
                else $attributes["style"] = "width:100px;";
                $attributes["onClick"] = $butt['onclick'];

                $rbuttons->add(form_button(
	                                $butt['name'],
	                                $butt['value'],
	                                $attributes),
	                                _HTML_SPACE);
        	}
        }else{
        	$rbuttons = _HTML_SPACE;
        }
        $table->add_row($lbuttons,
                            _HTML_SPACE,
                        $rbuttons
                        );
        return $table;

    }


}

/**
 * This builds a complex dual select box
 * with buttons to move entries from one
 * select box to another.  The boxes are
 * stacked vertically instead of horizontally.
 *
 * <pre>
 * From
 * ------------------------
 * |----------------------|
 * |----------------------|
 * |----------------------|
 * |----------------------|  Add >>
 * |----------------------|  Add All
 * |----------------------|
 * |----------------------|
 * |----------------------|
 * ------------------------
 * To
 * ------------------------
 * |----------------------|
 * |----------------------|
 * |----------------------|
 * |----------------------|  << Remove
 * |----------------------|  Remove All
 * |----------------------|
 * |----------------------|
 * |----------------------|
 * ------------------------
 * </pre>
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @see FEComboListBox
 */
class FEComboListBoxVertical extends FEComboListBox
{
    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    function get_element() {
        $table = html_table();

        $from_select = form_select($this->_element_name.'_available',
                                   $this->_data_list,'', TRUE);

        if ($this->onChangeJS != null) {
            $from_select->set_tag_attribute("onChange", $this->onChangeJS);
        }

		$from_select->set_tag_attribute('id', $this->build_id_name().'_from');

        $style = '';
        if ($this->_height) {
            $style .= "height: ".$this->_height.";";
        }
        if ($this->_width) {
            $style .= "width: ".$this->_width.";";
        }

        //build the buttons
        $button_style = 'width: 90px;';
        $f_name = $this->_element_name."_move_around";
        $add = form_button($this->_element_name.'_add', 'Add >>', array('style' => $button_style,
                                                                        'onclick' => $f_name."('right',false);"));
        $add_all = form_button($this->_element_name.'_add_all', 'Add All', array('style' => $button_style,
                                                                                 "onclick" => $f_name."('right', true);"));

        $remove = form_button($this->_element_name.'_remove', '<< Remove', array('style' => $button_style,
                                                                                 'onclick' => $f_name."('left', false);"));
        $remove_all = form_button($this->_element_name.'_remove_all', 'Remove All', array('style' => $button_style,
                                                                                          'onclick' => $f_name."('left', true);"));

        $to_select = form_select($this->_element_name.'[]',
                                 $this->_data_list_to, '', TRUE);

        if (strlen($style) > 0) {
            $from_select->set_style($style);
            $to_select->set_style($style);
        }

        //check to see if we are disabled
        if ($this->is_disabled()) {
            $from_select->set_tag_attribute('disabled');
            $add->set_tag_attribute('disabled');
            $add_all->set_tag_attribute('disabled');
            $remove->set_tag_attribute('disabled');
            $remove_all->set_tag_attribute('disabled');
            $to_select->set_tag_attribute('disabled');
        }

		$to_select->set_tag_attribute('id', $this->build_id_name().'_to');


        $button_td = new TDtag(array('align' => 'left'),
                                   $add, html_br(), $add_all, html_br(2),
                                   $remove, html_br(), $remove_all);

		$f_name = $this->_element_name."_order";

		$move_up = form_button('Move Up', 'Move Up', array('onclick' => "javascript: ".$f_name."(0)"));
		$move_down = form_button('Move Down', 'Move Down', array('onclick' => "javascript: ".$f_name."(1)"));

        //IE sucks.

        $add_button_td = new TDtag(array('align' => 'left'),
                                   $add, html_br(), $add_all);
        $add_button_td->set_collapse();

        $remove_button_td = new TDtag(array('align' => 'left'),
                                   $remove, html_br(), $remove_all);
        $remove_button_td->set_collapse();


        $table->add_row($this->_from_label) ;
		$table->add_row($from_select, $add_button_td) ;
        $table->add_row($this->_to_label) ;
		$table->add_row($to_select, $remove_button_td) ;

		if ($this->_ordering) {
			$table->add_row(container($move_up, $move_down));
		}

        return $table;
    }
}

/**
 * This class builds a FEDataList that shows a select box for Months of the year
 *
 * You should use the built in php {@link http://www.php.net/manual/en/function.setlocale.php setlocale}
 * function to affect the language used for the month list.
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @see FEDate
 *
 */

class FEMonths extends FEListBox {

    /**
     * The constructor
     *
     * @param string text label for the element
     * @param boolean is this a required element?
     * @param int element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int element height in px
     * @param string format should be F m or M:  Full month name, digit, abbreviated month name
     *
     */
    function FEMonths($label, $required = TRUE, $width = NULL, $height = NULL, $format = 'F'){

        // $format should be M m or F.  Default to F if the user passes in garbage.
        switch ($format) {
        case 'M':
            $format = '%b';
            break;
        case 'm':
            $format = '%m';
            break;
        default:
            $format = '%B';
            break;
        }

        for ($i = 1; $i < 13; $i++) {
            $months[$i] = strftime($format, strtotime("$i/12/2004"));
        }

	parent::FEListBox($label, $required, $width, $height, array_flip($months));
    }
}

/**
 * This class builds a FEDataList that shows a select box listing a range of years
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @see FEDate
 *
 */

class FEYears extends FEListBox {

    /**
     * The constructor
     *
     * @param string text label for the element
     * @param boolean is this a required element?
     * @param int element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int element height in px
     * @param int min_year
     * @param int max_year
     */
    function FEYears($label, $required = TRUE, $width = NULL, $height = NULL, $min_year = 2000, $max_year = 2010){
        // this will be cleaner in php5 with array_combine()
        $list = range($min_year, $max_year);
        foreach ($list as $year){
            $years[$year] = $year;
        }
	parent::FEListBox($label, $required, $width, $height, $years);
    }
}

/**
 * This class builds a FEDataList that shows a select box listing the days of the month
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @see FEDate
 *
 */

class FEDays extends FEListBox {

    /**
     * The constructor
     *
     * @param string text label for the element
     * @param boolean is this a required element?
     * @param int element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int element height in px
     */

    function FEDays($label, $required = TRUE, $width = NULL, $height = NULL){

        // this will be cleaner in php5 with array_combine()
        $list = range(1, 31);
        foreach ($list as $day) {
            // pad the single digit days with zeros
            $new_day = sprintf('%02d', $day);
            $days[$new_day] = $day;
        }
	parent::FEListBox($label, $required, $width, $height, $days);


    }
}

/**
 * This class builds a widget that shows a group of select boxes (FEYears, FEMonths, FEDays) representing a date.
 *
 * FEDate will display three drop down lists representing a date.  You can set
 * the order in which these elements are displayed and the minimum and maximum
 * years displayed.
 *
 * Like in FEMonths you should use the built in php {@link http://www.php.net/manual/en/function.setlocale.php setlocale}
 * function to affect the language used for the month list.
 *
 * Example as it would appear in FormContent::form_init_elements():
 * <code>
 *      // set the locale to dutch
 *      setlocale(LC_TIME, 'nl_NL');
 *      $date_element = new FEDate("FEDate label", false, null, null, 'Fdy', 1970, 1975);
 * </code>
 *
 * the $format parameter conforms the the php {@link http://www.php.net/manual/en/function.setlocale.php date} function
 * format argument specification (for years, months and days only).
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @author Suren Markosian <suren@emicron.net>
 * @see FEMonths
 * @see FEDays
 * @see FEYears
 *
 */

class FEDate extends FEBoxElement {

    /**
     * The earliest year shown in the year list.
     * @var integer
     * @access private
     */
    var $_min_year;

    /**
     * The latest year shown in the year list.
     * @var string
     * @access private
     */
    var $_max_year;

    /**
     * The order in which to show the elements.  This variable must be 3
     * characters long and contain only one m only one d and only one y.
     *
     * @var string
     * @access private
     */
    var $_format = 'mdy';

    /**
     * A printf style format string used to add punctuation to the confirmation
     * display.  Defaults to space separated.  The placeholders are filled
     * according to the order set in $_format
     *
     * @var string
     * @access private
     */
    var $_text_format = '%s %s %s';

    /**
     * The year form element
     *
     * @var FEYears
     * @access private
     */
    var $_year;

    /**
     * The month form element
     *
     * @var FEMonths
     * @access private
     */
    var $_month;

    /**
     * The day form element
     *
     * @var FEDays
     * @access private
     */
    var $_day;

    /**
     * The constructor
     *
     * @param string text label for the element
     * @param boolean is this a required element?
     * @param int element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int element height in px
     * @param string date format string.  M m F Y y d D are valid. 3 characters max.
     * @param int min value for year drop down list
     * @param int max value for year drop down list
     * @see FEDate for an example
     * @todo we need to blow up somehow if the format string is bogus
     * @access public
     *
     */

    function FEDate($label, $required = TRUE, $width = NULL, $height = NULL,
                    $format = 'mdy', $min_year = 2000, $max_year = 2010){

        $this->_set_format($format);
        $this->_min_year = $min_year;
        $this->_max_year = $max_year;


        //call the parent constructor first
        //so the element_name is built.
        parent::FEBoxElement($label, $required, $width, $height);

        //now create the child elements.
        $this->_year = new FEYears($this->_element_name . '_years', $required, null, null, $min_year, $max_year);
        $this->_month = new FEMonths($this->_element_name . '_months', $required, null, null, preg_replace('/[dy]/i', '', $this->_format));
        $this->_day = new FEDays($this->_element_name . '_days', $required, null, null);
    }

    /**
     * We need to override this so we get
     * the form name set in the child elements
     * so the id attributes are set correctly.
     */
    function set_form_name($name) {
        $this->_form_name = $name;
        $this->_year->set_form_name($name);
        $this->_month->set_form_name($name);
        $this->_day->set_form_name($name);
    }

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     * @access public
     */
    function get_element(){

        $container = new Container();

        // add the elements in the order specified.
        $chars = preg_split('//', $this->_format, -1, PREG_SPLIT_NO_EMPTY);
        foreach ($chars as $char){
            switch ($char) {
            case 'y':
                $container->add($this->_year->get_element());
                break;
            case 'm':
            case 'F':
                $container->add($this->_month->get_element());
                break;
            case 'd':
                $container->add($this->_day->get_element());
                break;
            }
        }

        return $container;
    }

    /**
     * This function will return the elements value as an array or month, day and year
     *
     * @return array
     * @access public
     */
    function get_value(){
        $value= array("day"=>$this->_day->get_value(),
                      "month"=>$this->_month->get_value(),
                      "year"=>$this->_year->get_value());

        return $value;


    }

    /**
     * Set the value of the element
     *
     * This function sets the default values for the date element  The
     * parameter should be a string representation of the date in ISO 8601
     * format.
     *
     * @param string
     * @access public
    */
    function set_value($value){
        if ($value) {
            if (is_array($value)) {
                $this->_year->set_value($value['year']);
                $this->_month->set_value($value['month']);
                $this->_day->set_value($value['day']);
            } else {
                $date_parts = explode('-', $value);
                $this->_year->set_value($date_parts[0]);
                $this->_month->set_value($date_parts[1]);
                $this->_day->set_value($date_parts[2]);
            }
        }


    }

    /**
     * This returns a formatted string used for the confirmation display (and possibly elsewhere)
     *
     * @return string
     * @access public
     */
    function get_value_text(){

        // loop through the characters in $_format to properly set the placeholders
        // determined in $_text_format
        $chars = preg_split('//', $this->_format, -1, PREG_SPLIT_NO_EMPTY);
        $i = 1;
        foreach ($chars as $char){

            switch ($char) {
            case 'y':
                $value = $this->_year->get_value_text();
                break;
            case 'm':
            case 'F':
                $value = $this->_month->get_value_text();
                break;
            case 'd':
                $value = $this->_day->get_value_text();
                break;
            }

            switch ($i) {
            case 1:
                $one = $value;
                break;
            case 2:
                $two = $value;
                break;
            case 3:
                $three = $value;
                break;
            }

            $i++;
        }

        return sprintf($this->_text_format, $one, $two, $three);
    }

    /**
     *
     * This function is responsible for performing complete
     * validation and setting the appropriate error message
     * in case of a failed validation
     *
     * @param FormValidation
     * @access public
     * @return boolean success or failure
     */
    function validate(&$_FormValidation){
        $value = $this->get_value();

		//we make sure that the date is valid
        if (!checkdate($value["month"], $value["day"], $value["year"])) {
            $this->set_error_message("Invalid date");
            return FALSE;
        }
        return TRUE;
    }

    /**
     * this method sets the display order for the elements in the widget
     *
     * @param string
     * @return bool success or failure
     * @access private
     */
    function _set_format($format){

        // must be 2 or 3 characters
        if (strlen($format) != 3) {
            return FALSE;
        }

        // month can be represented by F m or M
        if (strstr($format, 'F')) {
            $month = 'f';
        } else {
            $month = 'm';
        }

        // compare the characters sent with the characters needed.  only set
        // the property if one of each is present
        $search_for = array ('y', $month, 'd');
        $chars = preg_split('//', strtolower($format), -1, PREG_SPLIT_NO_EMPTY);

        if (count(array_diff($search_for, $chars)) > 0) {
            return FALSE;
        }

        $this->_format = $format;
        return TRUE;


    }

    /**
     * Set the text format for confirmation
     *
     * this method sets the format string used in get_value_text().  Use this
     * method to set special punctuation for the confirmation display.  It is
     * fed through sprintf
     *
     * Examples:
     * <code>
     *  $date_element->set_text_format("%s %s, %s");
     *  $date_element->set_text_format("%04d-%02d-%02d");
     * </code>
     *
     * @param string
     * @access public
     * @link http://www.php.net/manual/en/function.sprintf.php
     *
     */
    function set_text_format($format){

        $this->_text_format = $format;
    }

    /**
     * This method returns the hidden version of this element for a confirmation page.
     *
     * NOTE: This is called by the FormProcessor only.
     * It shouldn't be called manually.
     *
     * @return container
     * @access public
     */
    function get_confirm_element(){
        $element_name = $this->get_element_name();

        $c = container();
		$c->add(form_hidden($this->_year->get_element_name(), $this->_year->get_value()));
		$c->add(form_hidden($this->_month->get_element_name(), $this->_month->get_value()));
		$c->add(form_hidden($this->_day->get_element_name(), $this->_day->get_value()));
        return $c;
    }


    /**
     * Sets the disabled element flag
     *
     * @param bool disabled
     */
    function set_disabled($flag) {
        $this->_is_disabled = $flag;
        $this->_year->set_disabled($flag);
        $this->_month->set_disabled($flag);
        $this->_day->set_disabled($flag);
    }

}

/**
 * This class builds a widget that shows a group of select boxes (FEMonths, FEDays) representing a date.
 *
 * FEDate will display two drop down lists representing a date.  You can set
 * the order in which these elements are displayed.
 *
 * Like in FEMonths you should use the built in php {@link http://www.php.net/manual/en/function.setlocale.php setlocale}
 * function to affect the language used for the month list.
 *
 * Example as it would appear in FormContent::form_init_elements():
 * <code>
 *      // set the locale to dutch
 *      setlocale(LC_TIME, 'nl_NL');
 *      $date_element = new FEDay("FEDay label", false, null, null, 'Fd');
 * </code>
 *
 * the $format parameter conforms the the php {@link http://www.php.net/manual/en/function.setlocale.php date} function
 * format argument specification (for years, months and days only).
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @author Suren Markosian <suren@emicron.net>
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @see FEMonths
 * @see FEDays
 *
 */

class FEDay extends FEBoxElement {

    /**
     * The order in which to show the elements.  This variable must be 3
     * characters long and contain only one m only one d and only one y.
     *
     * @var string
     * @access private
     */
    var $_format = 'md';

    /**
     * A printf style format string used to add punctuation to the confirmation
     * display.  Defaults to space separated.  The placeholders are filled
     * according to the order set in $_format
     *
     * @var string
     * @access private
     */
    var $_text_format = '%s %s';

    /**
     * The month form element
     *
     * @var FEMonths
     * @access private
     */
    var $_month;

    /**
     * The day form element
     *
     * @var FEDays
     * @access private
     */
    var $_day;

    /**
     * The constructor
     *
     * @param string text label for the element
     * @param boolean is this a required element?
     * @param int element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int element height in px
     * @param string date format string.  M m F d D are valid. 2 characters max.
     * @see FEDay for an example
     * @todo we need to blow up somehow if the format string is bogus
     * @access public
     *
     */

    function FEDay($label, $required = TRUE, $width = NULL, $height = NULL,
                    $format = 'md'){

        $this->_set_format($format);

        //call the parent constructor first
        //so the element_name is built.
        parent::FEBoxElement($label, $required, $width, $height);

        //now create the child elements.
        $this->_month = new FEMonths($this->_element_name . '_months', $required, null, null, preg_replace('/[d]/i', '', $this->_format));
        $this->_day = new FEDays($this->_element_name . '_days', $required, null, null);
    }

    /**
     * We need to override this so we get
     * the form name set in the child elements
     * so the id attributes are set correctly.
     */
    function set_form_name($name) {
        $this->_form_name = $name;
        $this->_month->set_form_name($name);
        $this->_day->set_form_name($name);
    }

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     * @access public
     */
    function get_element(){

        $container = new Container();

        // add the elements in the order specified.
        $chars = preg_split('//', $this->_format, -1, PREG_SPLIT_NO_EMPTY);
        foreach ($chars as $char){
            switch ($char) {
            case 'm':
            case 'F':
                $container->add($this->_month->get_element());
                break;
            case 'd':
                $container->add($this->_day->get_element());
                break;
            }
        }

        return $container;
    }

    /**
     * This function will return the elements value as an array or month, day and year
     *
     * @return array
     * @access public
     */
    function get_value(){
        $value= array("day"=>$this->_day->get_value(),
                      "month"=>$this->_month->get_value());

        return $value;


    }

    /**
     * Set the value of the element
     *
     * This function sets the default values for the date element  The
     * parameter should be a string representation of the date in ISO 8601
     * format.
     *
     * @param string
     * @access public
    */
    function set_value($value){
        if ($value) {
            if (is_array($value)) {
                $this->_month->set_value($value['month']);
                $this->_day->set_value($value['day']);
            } else {
                $date_parts = explode('-', $value);
                $this->_month->set_value($date_parts[1]);
                $this->_day->set_value($date_parts[2]);
            }
        }


    }

    /**
     * This returns a formatted string used for the confirmation display (and possibly elsewhere)
     *
     * @return string
     * @access public
     */
    function get_value_text(){

        // loop through the characters in $_format to properly set the placeholders
        // determined in $_text_format
        $chars = preg_split('//', $this->_format, -1, PREG_SPLIT_NO_EMPTY);
        $i = 1;
        foreach ($chars as $char){

            switch ($char) {
            case 'm':
            case 'F':
                $value = $this->_month->get_value_text();
                break;
            case 'd':
                $value = $this->_day->get_value_text();
                break;
            }

            switch ($i) {
            case 1:
                $one = $value;
                break;
            case 2:
                $two = $value;
                break;
            }

            $i++;
        }

        return sprintf($this->_text_format, $one, $two);
    }

    /**
     *
     * This function is responsible for performing complete
     * validation and setting the appropriate error message
     * in case of a failed validation
     *
     * @param FormValidation
     * @access public
     * @return boolean success or failure
     */
    function validate(&$_FormValidation){
        $value = $this->get_value();

	//we make sure that the date is valid, spoof the year
	//this may break on February 29th ....
        if (!checkdate($value["month"], $value["day"], date("Y"))) {
            $this->set_error_message("Invalid date");
            return FALSE;
        }
        return TRUE;
    }

    /**
     * this method sets the display order for the elements in the widget
     *
     * @param string
     * @return bool success or failure
     * @access private
     */
    function _set_format($format){

        // must be 2 or 3 characters
        if (strlen($format) != 2) {
            return FALSE;
        }

        // month can be represented by F m or M
        if (strstr($format, 'F')) {
            $month = 'f';
        } else {
            $month = 'm';
        }

        // compare the characters sent with the characters needed.  only set
        // the property if one of each is present
        $search_for = array ($month, 'd');
        $chars = preg_split('//', strtolower($format), -1, PREG_SPLIT_NO_EMPTY);

        if (count(array_diff($search_for, $chars)) > 0) {
            return FALSE;
        }

        $this->_format = $format;
        return TRUE;


    }

    /**
     * Set the text format for confirmation
     *
     * this method sets the format string used in get_value_text().  Use this
     * method to set special punctuation for the confirmation display.  It is
     * fed through sprintf
     *
     * Examples:
     * <code>
     *  $date_element->set_text_format("%s %s");
     *  $date_element->set_text_format("%02d-%02d");
     * </code>
     *
     * @param string
     * @access public
     * @link http://www.php.net/manual/en/function.sprintf.php
     *
     */
    function set_text_format($format){

        $this->_text_format = $format;
    }

    /**
     * This method returns the hidden version of this element for a confirmation page.
     *
     * NOTE: This is called by the FormProcessor only.
     * It shouldn't be called manually.
     *
     * @return container
     * @access public
     */
    function get_confirm_element(){
        $element_name = $this->get_element_name();

        $c = container();
		$c->add(form_hidden($this->_month->get_element_name(), $this->_month->get_value()));
		$c->add(form_hidden($this->_day->get_element_name(), $this->_day->get_value()));
        return $c;
    }


    /**
     * Sets the disabled element flag
     *
     * @param bool disabled
     */
    function set_disabled($flag) {
        $this->_is_disabled = $flag;
        $this->_month->set_disabled($flag);
        $this->_day->set_disabled($flag);
    }

}




/**
 * this class is used for building a listbox for
 * displaying Hours.
 *
 * @author Walter A. Boring IV
 */
class FEHoursListBox extends FEListBox {

    /**
     * Flag to tell us to use 12 or 24 hour format
     */
    var $_extended_hours = TRUE;

    /**
     * The constructor
     *
     * @param string the label
     * @param boolean required flag or not
     * @param boolean show 24 hour format?
     */
    function FEHoursListBox($label='Hours', $required=FALSE, $extended_hours=TRUE) {
        if ($extended_hours) {
            $hours = array('00'=>0, '01'=>1, '02'=>2, '03'=>3, '04'=>4, '05'=>5,
                           '06'=>6, '07'=>7, '08'=>8, '09'=>9, '10'=>10, '11'=>11,
                           '12'=>12, '13'=>13, '14'=>14, '15'=>15, '16'=>16, '17'=>17,
                           '18'=>18, '19'=>19, '20'=>20, '21'=>21, '22'=>22, '23'=>23);
        } else {
            $hours = array('00'=>0, '01'=>1, '02'=>2, '03'=>3, '04'=>4, '05'=>5,
                           '06'=>6, '07'=>7, '08'=>8, '09'=>9, '10'=>10, '11'=>11,
                           '12'=>12);
        }
        parent::FEListBox($label, $required, null, null, $hours);
    }
}

/**
 * this class is used for building a listbox for
 * displaying Minutes.
 *
 * @author Walter A. Boring IV
 */
class FEMinutesListBox extends FEListBox {

    /**
     * The constructor
     *
     * @param string the label (default = 'Minutes')
     * @param boolean required flag or not
     */
    function FEMinutesListBox($label='Minutes', $required=FALSE) {
        $minutes = array('00'=>0, '01'=>1, '02'=>2, '03'=>3, '04'=>4, '05'=>5,
                         '06'=>6, '07'=>7, '08'=>8, '09'=>9, '10'=>10);

        for($x=11;$x<=59;$x++) {
            $minutes[$x]=$x;
        }

        parent::FEListBox($label, $required, null, null, $minutes);
    }
}

/**
 * this class is used for building a listbox for
 * displaying Seconds.
 *
 * @author Walter A. Boring IV
 */
class FESecondsListBox extends FEMinutesListbox {

    /**
     * The constructor
     *
     * @param string the label (default = 'Seconds')
     * @param boolean required flag or not
     */
    function FESecondsListBox($label='Seconds', $required=FALSE) {
        parent::FEMinutesListBox($label, $required);
    }
}


/**
 * This class is used to build a ListBox for
 * GMT timezone selection
 *
 * @author Walter A. Boring IV
 */
class FEGMTTimeZoneListBox extends FEListBox {

    /**
     * The timezone selections
     */
    var $_zones=array("GMT -12 : Eniwetok, Kwajalein"=>-12,
                      "GMT -11 : Midway Islands, Samoa"=>-11,
                      "GMT -10 : Hawaii"=>-10,
                      "GMT -09 : Alaska"=>-9,
                      "GMT -08 : Pacific (USA, Canada), Tijuana"=>-8,
                      "GMT -07 : Arizona"=>-7,
                      "GMT -06 : Central (USA, Canada), Mexico"=>-6,
                      "GMT -05 : Bogota, Lima, Quito, East (USA, Canada)"=>-5,
                      "GMT -04 : Caracas, La Paz, Atlantic (Canada)"=>-4,
                      "GMT -03 : Terre Neuve, Brasilia, Georgetown"=>-3,
                      "GMT -02 : Atlantic Center"=>-2,
                      "GMT -01 : Azores"=>-1,
                      "GMT +00 : Casablanca, London, Dublin, Lisbon"=>0,
                      "GMT +01 : Paris, Amsterdam, Berlin, Rome, Vienna"=>1,
                      "GMT +02 : Athens, Bucharest, Riga, Cairo, Israel"=>2,
                      "GMT +03 : Nairobi, Moscow, Baghdad"=>3,
                      "GMT +04 : Abu Dhabi, Kabul"=>4,
                      "GMT +05 : Islamabad"=>5,
                      "GMT +06 : Colombo"=>6,
                      "GMT +07 : Bangkok, Hanoi, Jakarta"=>7,
                      "GMT +08 : Beijing, Hong Kong, Singapore, Taipei"=>8,
                      "GMT +09 : Tokyo, Seoul"=>9,
                      "GMT +10 : Sydney, Vladivostok"=>10,
                      "GMT +11 : New Caledonia"=>11,
                      "GMT +12 : Wellington"=>12);

    /**
     * The constructor
     *
     * @param string the label (default = 'Minutes')
     * @param boolean required flag or not
     */
    function FEGMTTimeZoneListBox($label='TimeZone', $required=FALSE) {
        parent::FEListBox($label, $required, null,null, $this->_zones);
    }
}

/**
 * This Form Element builds a list box of the days of the week.
 *
 * Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
 *
 * @author Walter A. Boring IV
 */
class FEWeekdaysListBox extends FEListBox {
    var $_weekdays = array('Sunday' => 0, 'Monday' => 1,
                           'Tuesday' => 2, 'Wednesday' => 3,
                           'Thursday' => 4, 'Friday' => 5,
                           'Saturday' => 6);

    function FEWeekdaysListBox($label='Weekdays', $required=FALSE) {
        parent::FEListBox($label, $required, null,null, $this->_weekdays);
    }
}

?>
