<?php
/**
 * This file contains the base FormElement class.
 *
 * $Id: FormElement.inc 1687 2006-04-12 04:13:18Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosyan <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This is the base FormElement object.  It can be
 * single form field such as a text input field,
 * or a complex object.
 *
 * Usefull Functions
 *
 * get_value() - This gets the current
 *   'value' of the FormElement.
 *   NOTE: This can be a 'complex' FormElement
 *         in which it may return an array of
 *         values.
 *
 * set_value() - Set the current value
 *   for this FormElement.
 *
 * get_label() - returns the label for this
 *   FormElement.
 *
 *
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FormElement {

    /**
     * Holds the elements label text
     *
     */
    var $_label_text = NULL;

    /**
     * Holds the elements initial value
     *
     */
    var $_value = NULL;

    /**
     * Indicates whether this elements
     * final value is required and cannot
     * be empty
     */
    var $_is_required = TRUE;

    /**
     * holds the array of errors
     * for this element.
     */
    var $_errors = array();

    /**
     * Holds the error message text
     * for validation errors, if any
     *
     */
    var $_error_message = NULL;

    /**
     * Holds the state of the last validation
     * Sets to true in case of a validation error
     *
     */
    var $_has_error = FALSE;

    /**
     * Holds the name of the element
     * as it appears in the form html tag
     *
     */
    var $_element_name = NULL;

    /**
     * Holds additional attributes for
     * the elements html tag
     *
     */
    var $_attributes;

    /**
     * Holds additional style attributes for
     * the elements html tag
     *
     */
    var $_style_attributes;

    /**
     * Indicates a disabled element
     *
     */
    var $_is_disabled = FALSE;

	/**
	 * Indicates this element is
	 * read only.  The get_element()
	 * will return the get_value_text()
	 * instead of the form.
	 */
	var $_is_readonly = FALSE;

    /**
     * Flag to tell us to enable
     * validation or not
     */
    var $_validation_enabled = TRUE;

    /**
     * automatically strip slashes from
     * form values?
     */
    var $_stripslashes = FALSE;


    /**
     * This holds the name of the form
     * for js that needs it
     */
    var $_form_name;

    /**
     * This Form Element needs to
     * propogate some js to the
     * Form tag's onsubmit attribute
     *
     * @var string
     */
    var $_has_form_on_submit = false;

    /**
     * This holds an array of FormElement objects
     * that are slaves of this element
     */
    var $_slave_elements;

    /**
     * The required field string
     *
     */
    var $_required_field_marker = "*";

    /**
     * The form Element's flag to add the :
     * character at the end of the label.
     */
    var $_label_colon_flag = FALSE;
	
	/**
	 * variable to store JS onclick
	 */
	var $onClickJS = NULL;
	
	/**
	 * variable to store JS onclick
	 */
	var $onFocusJS = NULL;
	
	/**
	 * variable to store JS onclick
	 */
	var $onChangeJS = NULL;
	
	/**
	 * variable to store JS onclick
	 */
	var $onSubmitJS = NULL;
	
	/**
	 * variable to store JS onclick
	 */
	var $onBlurJS = NULL;

    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param bool required - is this a required element
     */
    function FormElement($label, $required = TRUE) {

        $this->set_label_text($label);
        $this->set_required($required);

        // create a unique name to be used in the html form
        $this->create_element_name();

        //This sets the initial value of the element
        $this->set_value( $this->get_init_value() );
    }

    /**
     * This function will return the
     * slaves of this element
     *
     * @return array of slave elements
     */
    function &get_slave_elements() {
        return $this->_slave_elements;
    }

    /**
     * This function will set the
     * slaves of this element
     *
     * @param array of slave elements (element references &)
     */
    function set_slave_elements($slaveElements) {
        $this->_slave_elements = $slaveElements;
        $this->set_data_all_slaves( $this->get_value() );
    }


    /**
     * This function will set the
     * data the parent wants to set for the slave
     *
     * @param the slave
     * @param the value being set for the parent
     */
    function set_slave_data(&$slave, $parentValue) {
        ; //override to set the data for the slave
    }

    /**
     * This function will return the
     * elements label text
     *
     * @return string
     */
    function get_label_text() {
        return $this->_label_text;
    }

    /**
     * This function will set the
     * label for the element
     *
     * @param label string
     */
    function set_label_text($label) {
        $this->_label_text = $label;
    }

    /**
     * This method sets the flag to have ALL of the
     * FormElement's labels be appended with a :
     * character.  Some folks like this for some
     * completely unexplained reason.
     */
    function set_colon_flag($flag=TRUE) {
        $this->_label_colon_flag = $flag;
    }

    /**
     * This function will return the
     * elements value
     *
     * @return mixed
     */
    function get_value() {

        if ($this->_stripslashes) {
            if (is_array($this->_value)) {
                return array_map('stripslashes', array_map('trim', $this->_value));
            } else {
                return stripslashes(trim($this->_value));
            }
        } else {
            if (is_array($this->_value)) {
                if (is_string($this->_value)) {
                    return array_map('trim', $this->_value);
                } else {
                    return $this->_value;
                }
            } else {
                if (is_string($this->_value)) {
                    return trim($this->_value);
                } else {
                    return $this->_value;
                }
            }
        }
    }


    /**
     * This function will set the
     * initial value for the element
     *
     * @param value mixed
     */
    function set_value($value) {
        $this->_value = $value;
        $this->set_data_all_slaves($value);
    }

    /**
     * This function will call set_slave_data for all slaves
     * should be called when value of parent changes
     *
     * @param string - the current value of parent
     */
    function set_data_all_slaves($parentValue){
        $slaves = &$this->get_slave_elements();
        $num_slaves = count($slaves);
        if ($num_slaves) {
            for($i=0; $i < $num_slaves; $i++){
                $this->set_slave_data($slaves[$i], $parentValue);
            }

        }
    }

    /**
     * in case anyone in JS land
     * needs the name of the form that
     * this element lives in
     *
     * @param string - the form name
     */
    function set_form_name($name) {
        $this->_form_name = $name;
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
     * @param mixed the value to look up
     * @return string - the text associated
     */
    function get_value_text() {
        return $this->get_value();
    }


    /**
     * This function set the elements
     * required state
     *
     * @param bool required
     */
    function set_required($required) {
        $this->_is_required = $required;
    }

    /**
     * Returns whether this elements
     * final value cannot be empty
     *
     * @return bool requried
     */
    function is_required() {
        return $this->_is_required;
    }


    /**
     * This returns the initial value of
     * the element
     *
     * @return mixed
     */
    function get_init_value() {
        return @$_REQUEST[str_replace("[]","",$this->get_element_name())];
    }


    /**
     * Sets the disabled element flag
     *
     * @param bool disabled
     */
    function set_disabled($flag) {
        $this->_is_disabled = $flag;
        if ($flag) {
            //we should make sure there was no
            //value posted in the request, or
            //someone tried to hack us.
            if (isset($_REQUEST[str_replace("[]","",$this->get_element_name())])) {
                //HACK ATTEMPT!
                $this->_has_error = TRUE;
                $this->_errors[] = array('label' => $this->get_label_text(),
                                         'message' => 'Hack attempt discovered.  Disabled Element has been submitted');
            }
        }
    }

    /**
     * Returns the elements disabled
     * state
     *
     * @return bool disabled
     */
    function is_disabled() {
        return $this->_is_disabled;
    }


	/**
	 * This sets the readonly flag.
	 * When this flag is set, the FormContent
	 * gets back the get_value_text() instead
	 * of get_element().
	 * 
	 * @param bool TRUE = readonly 
	 */
	function set_readonly($flag=TRUE) {
		$this->_is_readonly = $flag;
	}

	/**
	 * Is this element in read only mode?
	 * 
	 * @return bool
	 */
	function is_readonly() {
		return $this->_is_readonly;
	}


	/**
	 * This sets the stripslashes flag for
	 * this object.
	 *
	 * @param boolean
	 */
	function set_stripslashes( $flag = TRUE ) {
		$this->_stripslashes = $flag;
	}


    /********* Tag attributes methods *********/


    /**
     * add a single attribute (name="value")
     *
     * @param   string  $name   attribute name
     * @param   mixed   $value  the value
     *
     */
    function set_attribute($name, $value = NULL) {
        if ($value == NULL) {
            $this->_attributes[] = $name;
        }
        else {
            $this->_attributes[$name] = $value;
        }
    }

    /**
     * return a single attribute
     *
     * @param   string  $name   attribute name
     * @return  mixed   $value  the value
     *
     */
    function get_attribute($name) {
        return $this->_attributes[$name];
    }

    /**
     * Sets elements title text
     *
     * @param string title
     */
    function set_title($title) {
        $this->set_attribute("title", $title);
    }

    /**
     * Sets elements css attribute
     *
     * @param   string  $name   attribute name
     * @param   mixed   $value  the value
     */
    function set_style_attribute($name, $value) {
        $this->_style_attributes[$name] = $value;
    }

    /**
     * Sets the element's tab index
     *
     * @param int the # for the tabindex
     */
    function set_tabindex($index) {
        $this->set_attribute('tabindex', $index);
    }

    /**
     * Gets the current tab index if any
     *
     * @return int returns 0 if there is none set.
     */
    function get_tabindex() {
        if (isset($this->_attributes['tabindex'])) {
            return $this->_attributes['tabindex'];
        } else {
            return 0;
        }
    }


    /********* Error handling methods *********/

    /**
     * Defines error message text and
     * sets the error flag to true
     *
     * @param mesage text - error message
     * @param label text - a label to provide
     *                     for the error.  This is
     *                     only needed for a complex
     *                     element that has multiple
     *                     'hidden/magic' fields.
     */
    function set_error_message($message, $label=NULL) {
        if ($label == NULL) {
            $label = $this->get_label_text();
        }
        $this->_errors[] = array("label" => $label,
                                 "message" => $message);
        $this->_has_error = TRUE;
    }

    /**
     * This returns the array of errors
     * for this element
     *
     * @param array of errors
     */
    function get_errors() {
        return $this->_errors;
    }


    /**
     * Returns the current error message
     * if any
     *
     * @return mesage text - error message
     */
    function get_error_message() {
        return $this->_error_message;
    }

    /**
     * Returns the current error state
     *
     *
     * @return bool error state
     */
    function has_error($label=NULL) {
        if ($label==NULL) {
            return $this->_has_error;
        } else {
            //they are looking for a specific error
            foreach( $this->_errors as $error) {

                if ($error['label'] == $label) {
                    return TRUE;
                }
            }
            return FALSE;
        }
    }


    /********* Element name handling methods *********/

    /**
     * This function creates element name
     * used in the form based on the text label
     * or any other parameters
     *
     */
    function create_element_name() {
        $this->set_element_name($this->_sanitize_string($this->get_label_text()));
    }


    /**
     * This private method sanitizes a string for
     * putting in a form element attribute value
     *
     * @param string the string to sanitize
     * @return string
     */
    function _sanitize_string($name) {
        $len = strlen($name);
        for ($i=0; $i<$len;$i++) {
            if ((ord($name[$i])<97 || ord($name[$i])>122) && 
				(ord($name[$i])<48 || ord($name[$i])>57) &&
				(ord($name[$i])<65 || ord($name[$i])>90))
                $name[$i] = "_";
        }

        return $name;
    }

    /**
     * This allows you to force the element
     * name to whatever you like, so you
     * don't have to use the default name, which is
     * generated based on the label.
     *
     * @param string the form element's name
     * @return none
     */
    function set_element_name($name) {
        $this->_element_name = $name;
    }

    /**
     * Returns the element name
     * to be used in the form
     *
	 * @param string.  If you pass in a string
	 *                It will generate the name and return
	 *                that instead of the locally created name.
     * @return string form element name
     */
    function get_element_name($string=NULL) {
		if (!is_null($string)) {
			return self::_sanitize_string($string);
		}
        return $this->_element_name;
    }


    /********* Validation methods *********/

    /**
     * This method sets a flag to enable/disable
     * validation for the Element.
     *
     * @param boolean TRUE = enable validation
     */
    function enable_validation($flag=TRUE) {
        $this->_validation_enabled = $flag;
    }


    /**
     * This function performs the actual validation
     * It is called only if the validation is required by
     * this element
     *
     * This function is responsible for performing complete
     * validation and setting the appropriate error message
     * in case of a failed validation
     *
     * @param FormValidation object.
     */
    function validate(&$_FormValidation) {
        return TRUE;
    }


    /**
     * This function checks if the validation
     * is nesseccary and calls the validate method
     *
     * @param FormValidation object.
     */
    function _do_validation(&$_FormValidation) {
        $value = $this->get_value();
        $has_value = FALSE;
        if (is_array($value)) {
            foreach($value as $entry) {
                if ($entry != NULL) {
                    $has_value = TRUE;
                }
            }
        } else {
            if ($value != NULL) {
                $has_value = TRUE;
            }
        }

        if ($has_value && !$this->is_disabled()  && $this->_validation_enabled) {
            return $this->validate($_FormValidation);
        } else if ($this->is_required()) {
            $this->set_error_message("This field cannot be empty");
            return FALSE;
        } else {
            return TRUE;
        }
    }


    /********* JavaScript event methods *********/

    /**
     * This method is used for adding any javascript
     * that is used by this element.  This will automatically
     * get called and added to the page by the FormProcessor
     *
     * @return string - raw js
     */
    function javascript() {
        return NULL;
    }

	/**
	 * This method sets the onclick javascript
	 * @param string - js code
	 */
	function set_onClick($js){
		$this->onClickJS = $js;
	}
	

    /**
     * This function return the javaScript code for
     * an onClick event
     * Note: if you override this function be sure to use
     * 		 the appropriate $this->onClickJS and append your
     *		 JS to it before returning
     * @return string - javascript code
     */
    function onClick() {
        return $this->onClickJS;
    }

	/**
	 * This method sets the onfocus javascript
	 * @param string - js code
	 */
	function set_onFocus($js){
		$this->onFocusJS = $js;
	}
	
    /**
     * This function return the javaScript code for
     * an onFocus event
     * Note: if you override this function be sure to use
     * 		 the appropriate $this->onClickJS and append your
     *		 JS to it before returning
     * @return string - javascript code
     */
    function onFocus() {
        return $this->onFocusJS;
    }

	/**
	 * This method sets the onSubmit javascript
	 * @param string - js code
	 */
	function set_onSubmit($js){
		$this->onSubmitJS = $js;
	}
	
    /**
     * This function return the javaScript code for
     * an onSubmit event
     * Note: if you override this function be sure to use
     * 		 the appropriate $this->onClickJS and append your
     *		 JS to it before returning
     * @return string - javascript code
     */
    function onSubmit() {
        return $this->onSubmitJS;
    }

	/**
	 * This method sets the onblur javascript
	 * @param string - js code
	 */
	function set_onBlur($js){
		$this->onBlurJS = $js;
	}
	
    /**
     * This function return the javaScript code for
     * an onBlur event
     * Note: if you override this function be sure to use
     * 		 the appropriate $this->onClickJS and append your
     *		 JS to it before returning
     * @return string - javascript code
     */
    function onBlur() {
        return $this->onBlurJS;
    }

	/**
	 * This method sets the onChange javascript
	 * @param string - js code
	 */
	function set_onChange($js){
		$this->onChangeJS = $js;
	}
	
    /**
     * this function retuns the javaScript code for
     * an onChange event
     * Note: if you override this function be sure to use
     * 		 the appropriate $this->onClickJS and append your
     *		 JS to it before returning
     * @return string - javascript code
     */
    function onChange() {
        return $this->onChangeJS;
    }

    /**
     * This function builds the complete javaScript events code
     * for the element
     *
     * @return array - attributes
     */
    function _build_javascript() {

        $javascript = array();

        if (($js=$this->onClick()) != NULL) {
            $javascript[] = "onclick=\"" . $js . "\"";
        }

        if (($js=$this->onFocus()) != NULL) {
            $javascript[] = "onfocus=\"" . $js . "\"";
        }

        if (($js=$this->onSubmit()) != NULL) {
            $javascript[] = "onsubmit=\"" . $js . "\"";
        }

        if (($js=$this->onBlur()) != NULL) {
            $javascript[] = "onblur=\"" . $js . "\"";
        }

        if (($js=$this->onChange()) != NULL) {
            $javascript[] = "onchange=\"" . $js . "\"";
        }

        if (count($javascript)>0) {
            return $javascript;
        }
        else {
            return NULL;
        }
    }


    /**
     * This is a method for getting the JS needed
     * for the form tag's onsubmit attribute.
     *
     * @return string
     */
    function form_tag_onsubmit() {
        return '';
    }


    /********* rendering methods *********/


    /**
     * This function return the symbol used to
     * denote a required field
     *
     * @return string - required symbol
     */
    function get_required_symbol() {
         if (is_object($this->_required_field_marker)) {
             return $this->_required_field_marker->render();
         } else {
             return $this->_required_field_marker;
         }
    }

    /**
     * This allows you to customize the
     * require string marker
     *
     * @param string
     */
    function set_required_symbol($symbol) {
        $this->_required_field_marker;
    }

    /**
     * This function builds the element form attributes
     *
     * @return array attributes
     */
    function _build_element_attributes() {

        $attributes = $this->_attributes;

        if ($this->_style_attributes) {
            // build the css styles
            foreach ($this->_style_attributes as $name=>$value) {
                $style[] = $name . ":" . $value . ";";
            }
            $attributes["style"] = implode("", $style);
        }

        // set the element tag name
        $attributes["name"] = $this->get_element_name();

        if (($js = $this->_build_javascript()) != NULL) {
            // build javaScript attributes
            $attributes = array_merge($attributes, $js);
        }

        //see if its disabled
        if ($this->is_disabled()) {
            $attributes[] = "disabled";
        }

        //build the ID
        $attributes['id'] = $this->build_id_name();

        return $attributes;
    }



    /**
     * This private method is used to
     * build the id attribute value string
     *
	 * @param string an index to append to 
	 *               the end of the generated ID string.
	 *               This is usefull for complex FormElements
     * @return string
     */
    function build_id_name($index=NULL) {
		if (!is_null($index)) {
			$index = '_'.$index;
		}
        return $this->_form_name.'_'.$this->get_element_name().$index;
    }


    /**
     * This function builds and returns a
     * label object based on the label text
     * and error conditions
     *
     * @param FormContent object that holds the
     *        required field marker
     * @param string this string allows us to use this
     *        method and wrap any string as a FormElement
     *        label.
     * @return object SPANtag
     */
    function get_label($form_content=NULL, $label='', $indent_flag=TRUE) {

        if ($label == '') {
            $label = $this->get_label_text();        	
        }

		//check to see if the form content
		//is read only.
		if (!is_null( $form_content )) {
			if ($form_content->is_readonly()) {
				
				$this->set_readonly(TRUE);
			}
		}

        if ($this->is_required() && !$this->is_readonly()) {
            $text = ($form_content ? $form_content->get_required_marker() :
                     $this->get_required_symbol()). ' '.$label;
        } else {
            if ($indent_flag) {
                $text = '&nbsp;&nbsp;'.$label;            	
            } else {
                $text = $label;
            }
        }

        if ($this->_label_colon_flag) {
            $text .= ':';        	
        }

        $span = html_span("formlabel", $text);

        if ($this->has_error($label)) {
            $span->set_tag_attribute("style","color:red;");
        }

        return $span;
    }

	/**
	 * This method checks to see if
	 * this element is readonly and returns
	 * the get_value_text() or returns get_element()
	 * if it isn't readonly
	 *
	 * @param bool force readonly?
	 * @return mixed
	 */
	function get_form_element($force_readonly=FALSE) {
		if ($force_readonly) {
			$this->set_readonly(TRUE);
		}

		if ($this->is_readonly()) {
			return container($this->get_value_text(),$this->get_confirm_element());
		} else {
			return $this->get_element();
		}
	}


    /**
     * This function builds and returns the
     * form element object.   This method 
	 * ignores the readonly flag.
     *
     * @return object
     */
    function get_element() {

        $span = new SPANtag($this->_build_element_attributes(), $this->get_value());

        return $span;
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
    function get_confirm_element() {
        $values = $this->get_value();
        $name = $this->get_element_name();

        if (is_array($values)) {
            $c = container();
            foreach ( $values as $value ) {
                $c->add( form_hidden($name, $value ) );
            }
            return $c;
        } else {
            return form_hidden($name, $this->get_value() );
        }
    }

} // FormElement
?>
