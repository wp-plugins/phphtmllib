<?php
/**
 * This file contains the FormContent class.
 *
 * $Id: FormContent.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@cbestwhat?>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * Make sure we include the Processor
 */
require_once(PHPHTMLLIB_ABSPATH . "/form/FormProcessor.inc");

/**
 * This class is used to build and render the form.
 * It builds a form by creating FormElement objects
 * which have automatic validation.  It leaves the
 * layout of the form up to the child class.  It has
 * a mechanism in place to automagically show a
 * confirmation 'page' after the data has been submitted
 * and validated.  It also provides a hook for any
 * 'back end' validation of data.  Finally, it provides
 * a function for handling the action of the form, which
 * only gets call after ALL validation has passed.
 *
 * Functions:
 *
 * form_init_elements() - This function is used to
 *   build the FormElement objects that will be used
 *   by the form.  This function is called EVERY time
 *   the FormContent class is instantiated.  After you
 *   create the FormElement, you call the
 *   FormContent::add_element() method, to add the
 *   FormElement object to the form.  You will then
 *   call the 2 methods FormContent::element_label() and
 *   FormContent::element_form() to get access to the
 *   FormElement's label and form field respectively.
 *
 * form_init_data() - This is called only the first time
 *   the form is encountered.  It Allows you to populate
 *   the FormElements with data from a DB for example.
 *   You would use FormContent::set_element_value() or
 *   FormContent::set_hidden_element_value() inside here.
 *
 * form() - This is the method that gets called to build
 *   the layout for your form.  Typically you use a table
 *   and add the label in the first <td> and the form field
 *   itself in the 2nd <td>.  So there are 2 methods in
 *   the FormContent object that allow u to get access to
 *   the FormElements label, and form field.
 *   FormContent::element_label() and
 *   FormContent::element_form().
 *
 *
 * form_backend_validation() - This method enables you to
 *   do any "back end" validation of data.  Such as, check
 *   for a duplicate in the DB on a create/new form.  This
 *   is called after the FormElement's validation methods have
 *   passed.
 *
 * form_action() - This method is called after ALL validation
 *   was successfull, including each FormElement object's
 *   validation methods, as well as the FormContent::form_backend_validation()
 *
 *
 *
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FormContent {

    /**
     * This holds the name of the form
     * for js that needs it
     */
    var $_form_name;


    /**
     * This holds the array of
     * hidden form elements
     * used in this form
     */
    var $_hidden_elements = array();

    /**
     * This holds the array of
     * non-hidden elements
     */
    var $_elements = array();


	/**
	 * This holds the default
	 * css class for form field
	 * label text.
	 *
	 */
	var $_default_label_css = "formlabel";

	/**
	 * This is the css class used
	 * for fields that have an error
	 *
	 */
	var $_error_label_css = "formlabelerror";

	/**
	 * flag to let the FormProcessor
	 * object know this form has a
	 * confirmation page that is required
	 */
	var $_has_confirm = FALSE;


	/**
	 * Holds the width to be used for the
	 * error table
	 * DEFAULT: 95%
	 *
	 */
	var $_width = "600";

    /**
     * Holds the width (if any) of the errors
     * table that will be rendered.  If the
     * value is null, the $this->_width value
     * is used instead.
     */
    var $_form_errors_width = null;


    /**
     * The form errors table title
     */
    var $_form_errors_title = "Form Errors";


    /**
     * The message that is set
     * during the form_action
     */
    var $_action_message = "";


    /**
     * The action to take opon clicking
     * the "Cancel" button
     */
    var $_cancel_action = NULL;


    /**
     * Text to show denoted required
     * fields for the form.
     *
     */
    var $_required_field_text = " - required field";

    /**
     * marker for the required field
     *
     */
    var $_required_field_marker = "*";

    /**
     * The form Element's flag to add the :
     * character at the end of the label.
     */
    var $_label_colon_flag = FALSE;

    /**
     * This holds how many actions we have
     * for this form content
     */
    var $_action_counter = 0;

    /**
     * Automatically strip slashes from
     * form values?
     */
    var $_stripslashes = FALSE;

    /**
     * Flag to mark this as having a
     * File Form Element (child of FEFile)
     */
    var $_has_file_element = FALSE;

    /**
     * index names of all of the file
     * form elements (if any).
     */
    var $_file_elements = array();


    /**
     * The onsubmit value for the form
     * tag.  FormElement childs can
     * automatically add to this
     * by implementing the
     * form_tag_onsubmit() method
     */
    var $_form_on_submit = '';
    
    /**
     * The onsubmit value for the form
     * tag. This is used by form action
     * elements to add disable on submit     
     */
    var $_form_action_elements_on_submit = '';

    /**
     * This is the FormValidation object
     * used to validate the form elements
     */
    var $_FormValidation = NULL;


	/**
	 * Indicates this entire FormContent
	 * is in readonly mode.  This forces
	 * all of the FormElement to be in
	 * readonly mode. 
	 * 
	 */
	var $_is_readonly = FALSE;


    function FormContent($width="100%", $cancel_action=NULL) {
        $this->set_form_width( $width );
        $this->set_cancel_action( $cancel_action );
    }

    /**
     * This method is what is called to
     * build the list of FormElements that
     * will be used by this form.
     *
     */
    function form_init_elements() {
        user_error("FormContent::form_init_elements() - Child class must override");
    }


    /**
     * This method is called by the
     * Form Processor to allow this
     * class to do any fetching of
     * data to prepopulate the
     * form field values.
     * You typically use this to
     * read data from a DB.
     *
     * This method is only called once
     * when the form is first hit.
     *
     * NOTE: you should build the data
     *       and save it in $this->_init_data
     */
    function form_init_data() {
        $this->_init_data = array();
    }


    /**
     * This method builds the html form.
     * It is up to the child class to define
     * the layout of the form and return it
     * in a phpHtmllib container.
     *
     * @return Container
     */
    function form() {
        user_error("FormContent::form() - Child class must override");
        return NULL;
    }

    /**
     * This method lets you provide any javascript
     * that is associated with the form content.
     * The FormProcessor will automatically call
     * this and wrap it in a script tag.
     *
     * @return string - raw js.
     */
    function javascript() {
        return NULL;
    }

    /**
     * This method allows this class to do any
     * data munging prior to the form_confirm
     * method being called @ render time.
     *
     * @return TRUE = success
     *         FALSE if u want to trigger an error
     */
    function pre_confirm() {
        return TRUE;
    }

    /**
     * This is a 'hidden' version of pre_confirm
     * to allow calling the form elements pre_confirm
     * methods.  This is needed for forms that have
     * a confirmation requirement and has file inputs.
     * If the file input FormElement doesn't save off
     * the uploaded file, then the confirmation page
     * will not get the file. apache may nuke the temp
     * file in /tmp.
     *
     */
    function _pre_confirm() {
        foreach( $this->_file_elements as $name ) {
            $this->_elements[$name]->_pre_confirm();
        }
    }


	/**
	 * This function is used to show an intermediary
	 * confirmation page.  Use this function to
	 * show a confirmation of the data that was
	 * submitted by the user.
	 * This will get called after all of the
	 * form data was successfully validated.
	 * All of the form data will automatically
	 * be created as hidden form fields. All you
	 * have to do is show the data, and a confirm
	 * submit button.
	 *
     * @param string - the title for the table
     * @param boolean - show the action buttons?
	 * @return mixed - either raw html, or some
	 *                 container HTMLTag object.
	 */
	function form_confirm( $title = "Form Confirmation", $show_buttons=TRUE ) {
        $table = new InfoTable($title, $this->_width);

        $this->build_confirm_table( $table );

        //now add the confirmation button
        $td = new TDtag(array("colspan" => 2,
                              "class" => "contentnovertical",
                              "align" => "center"),
                              $this->add_action("Confirm"));

        if ($this->_cancel_action) {
            $td->add(_HTML_SPACE, $this->add_cancel());
        }

        if ($show_buttons) {
            $table->add_row( $td );
        }

        return $table;
	}


    /**
     * This method allows the child to ovveride the
     * default confirm data.  By default the form_confirm()
     * will show ALL FormElements.  This is prolly not good
     * in case of a form where a password exists.
     *
     * @param InfoTable object
     */
    function build_confirm_table( &$table ) {
        foreach( $this->_elements as $label => $element) {
            $c = container(_HTML_SPACE, $element->get_value_text());
            $c->set_collapse();
            $div = html_div("", $element->get_label($this) );
            $div->set_style("white-space:nowrap;");
            $table->add_row( $div, $c);
        }
    }

    /**
     * This method is called after the FormElements
     * have all been validated, and the form_confirm
     * has been confirmed.  It enables the form to
     * validate any data against a DB or other backend
     * processing.  This will always get called
     * before the form_action method is called to ensure
     * that all form data is valid before form_action()
     * is called.
     *
     *
     * @return boolean TRUE if successfull
     *                 FALSE if errors were detected.
     */
    function form_backend_validation() {
        return TRUE;
    }


    /**
     * This method handles the
     * action (submit button) that
     * was submitted.  This method
     * only gets called AFTER all
     * data has been validated.
     * This includes the backend
     * validation.  If the form
     * has the confirmation on,
     * then this method will be
     * called after the confirmation
     * has been accepted.
     *
     * NOTE : return TRUE if the action
     *        was succesfully handled.
     *        If FALSE is returned, the
     *        form will be displayed again
     *        with the error message.
     *
     * @param array - array of errors if any
     * @return boolean TRUE = success
     *                 FALSE = failed.
     */
    function form_action() {
        user_error("FormContent::form_action() - Child class ".
                   "must override");
        return FALSE;
    }


    /**
     * This method is called when the form_action()
     * was successfull, and the form wants to render
     * some kind of message
     *
     * @return mixed
     */
    function form_success() {
        if ($this->_action_message != "") {
            return container($this->_action_message, html_br(2));
	} else {
	    return NULL;
	}
    }

	/**
	 * This function is used to render the error
	 * table for the form.  The error data comes
	 * from the FormProcessor or the FormValidation.
	 * NOTE: You can override this method to
	 *       show a customized error message(s)
	 *
	 * @return TABLEtag object.
	 */
	function form_errors() {
        $table = new ErrorBoxWidget($this->_form_errors_title,
									$this->get_form_errors_width());
        $errors = FALSE;

		//walk each visible form element and see if there is an error in it
		foreach( $this->_elements as $label => $element ) {
			if ($element->has_error()) {
				$e_errors = $element->get_errors();
				foreach( $e_errors as $err ) {
					$table->add($err['label'], $err['message']);
				}
				$errors = TRUE;
			}
		}
		if ($errors) {
			return $table;
		} else {
			return NULL;
		}
	}


    /**
     * This method returns an array of errors
     * for all the errors.
     *
     * @return array
     */
    function get_error_array() {
        $ret = array();
        //walk each visible form element and see if there is an error in it
        foreach( $this->_elements as $label => $element ) {
            if ($element->has_error()) {
                $errors = $element->get_errors();
                foreach ( $errors as $err ) {
                    $ret[$err['label']] = $err['message'];
                }
            }
        }
        return $ret;
    }


    /*****************************/
    /*     form element methods  */
    /*****************************/

    /**
     * This method is used to add a
     * form element
     *
     * @param FormElement object
     */
    function add_element( &$element ) {
        $element->set_stripslashes( $this->_stripslashes );
        //in case the element needs it for js
        $element->set_form_name( $this->_form_name );
        $name = $element->get_label_text();
        $this->_elements[$name] = &$element;

        //do we have a File form element?
        if (is_a($element, 'fefile')) {
            $this->_has_file_element = TRUE;
            $this->_file_elements[] = $name;
        }
        if ($element->_has_form_on_submit) {
            $this->_form_on_submit .= $element->form_tag_onsubmit();
        }

        if ($this->_label_colon_flag) {
            $element->set_colon_flag(TRUE);        	
        }
    }

    /**
     * This method is used to add a
     * hidden form field
     *
     * @param FormElement object
     */
    function add_hidden_element( $label, $value=NULL ) {
        $element = new FEHidden( $label, $value );
        $element->set_stripslashes( $this->_stripslashes );
        $element->set_form_name( $this->_form_name );
        $this->_hidden_elements[$label] = &$element;
    }
    
  	/**
	 * This function adds a form submit button
	 * with the appropriate action.
	 *
	 * @param string - the labe/action for the submit
	 *                 button.
	 * @param bool disable the button
     * @param string - the onSubmit function (if any)
     * @param boolean - disable opon submit?
	 * @return INPUTtag object
	 */
	function add_action_element($label, $disabled = false, $submit_function = false,
                                $disable_on_submit = TRUE) {

        $style="vertical-align:middle;";
		// here we mantain a fixed button size if a label length is reasonably small
		// i.e. OK or Cancel buttons or use padding otherwise
		if (strlen($label)<8)	$style .= "width:100px;";
		else $style	.= "padding-left:5px;padding-right:5px;";
		
		$button_name = FORM_ACTION . $this->_action_counter++;
		$button_id = $this->_form_name . "action_" . $button_name;

        $attributes = array("id" => $button_id,
                            "onclick" =>"this.form." . FORM_ACTION . ".value='".$label."';",
                            "style" => $style);

        if ($disabled) $attributes[] = "disabled";

        $this->_action_elements[$label] = form_submit($button_name, $label, $attributes);

        if ($disable_on_submit) {
            $this->_form_action_elements_on_submit .= "if (document.getElementById('" . $button_id . "')) document.getElementById('" . $button_id . "').disabled=true;";
        }
	}
	
	/**
	 * This function returns a submit action
	 * by label
	 *
	 * @param string label
	 *
	 * @return object
	 */
	function get_action_element($label) {
	    return $this->_action_elements[$label];
	}    

    /**
     * This method returns the label object
     * for a visible form element.
     *
     * @param string - the element's label
     * @return Object
     */
    function element_label($label) {
        $this->_test_element($label, "element_label");
        return $this->_elements[$label]->get_label($this);
    }

    /**
     * This method returns the label object
     * for a visible form element.
     *
     * @param string - the element's label
     * @return Object
     */
    function hidden_element_label($label) {
        $this->_test_element($label, "element_label", TRUE);
        return $this->_hidden_elements[$label]->get_label($this);
    }

    /**
     * This method returns the actual form
     * object that renders the form field.
     * Such as an INPUTtag object.
     *
     * @param string - the element's label
     * @return Object
     */
    function element_form($label) {
        $this->_test_element($label, "element_form");
        return $this->_elements[$label]->get_form_element($this->is_readonly());
    }

    /**
     * This method returns the FormElement
     * based on the label.
     *
     * @param string - the element's label
     * @return Object
     */
    function &get_element($label) {
        $this->_test_element($label, "get_element");
        return $this->_elements[$label];
    }

    /**
     * This method is used to set
     * the value for a non hidden
     * element
     *
     * @param string - the form label
     * @param value - the new value
     */
    function set_element_value($label, $value) {
        $this->_test_element($label, "set_element_value");
        $this->_elements[$label]->set_value($value);
    }

    /**
     * This method is used to get
     * the value for a non hidden
     * element
     *
     * @param string - the form label
     * @return value - the new value
     */
    function get_element_value($label) {
        $this->_test_element($label, "get_element_value");
        return $this->_elements[$label]->get_value();
    }

    /**
     * This method is used to set
     * the value for a hidden element
     *
     * @param string - the form label
     * @param value - the new value
     */
    function set_hidden_element_value($label, $value) {
        $this->_test_element($label, "set_hidden_element_value", TRUE);
        $this->_hidden_elements[$label]->set_value( $value );
    }

    /**
     * This method is used to get
     * the value for a hidden element
     *
     * @param string - the form label
     * @return value - the new value
     */
    function get_hidden_element_value($label) {
        $this->_test_element($label, "get_hidden_element_value", TRUE);
        return $this->_hidden_elements[$label]->get_value();
    }

    /**
     * This method is a helper method to set the
     * FormElement's tabindex.
     *
     * @param string - the form label
     * @param int - the FormElement's tabindex
     * @return none
     */
    function set_form_tabindex($label, $index) {
        $this->_test_element($label, "set_form_tabindex");
        $this->_elements[$label]->set_tabindex($index);
    }

    /**
     * This method is a helper method to get the
     * FormElement's tabindex.
     *
     * @param string - the form label
     * @param int - the FormElement's tabindex
     * @return the FormElement's current tabindex
     */
    function get_form_tabindex($label, $index) {
        $this->_test_element($label, "set_form_tabindex");
        return $this->_elements[$label]->get_tabindex();
    }

    /**
     * This method is used to test
     * if the element exists in a form
     *
     * @param string - the form label
     * @return bool
     */
    function element_exists($label) {
        return (isset($this->_elements[$label]) || isset($this->_hidden_elements[$label]));
    }

    /**
     * This method is used to create a new error element
     * during the call to form_action().  This enables us
     * to do error handling during a transaction into
     * a DB.
     *
     * @param string - the label
     * @param string - the error message
     */
    function add_error( $label, $message ) {
        if (isset($this->_elements[$label])) {
            $this->_elements[$label]->set_error_message($message);
        } else {
            $this->add_element( new FEError($label, $message) );
        }
    }


	/**
	 * This sets the readonly flag.
	 * When this flag is set, all of the
	 * FormElements will be set to readonly.
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


    /*****************************/
    /*       Util methods        */
    /*****************************/

    function set_form_name($name) {
        $this->_form_name = $name;
    }

	function get_form_name() {
		return $this->_form_name;
	}


	/**
	 * Save the action for the form
	 *
	 * @param string - the action from the post.
	 */
	function set_action($action) {
		$this->action = $action;
	}

	/**
	 * Get the current status of the
	 * action.
	 *
	 * @return string
	 */
	function get_action() {
		return $this->action;
	}

    /**
     * this method sets the form name
     *
     * @param string - the form name
     */
    function set_form_width($width) {
        $this->_width = $width;
    }


    /**
     * This method returns the width
     * of the form errors table.
     * By default it is supposed to be
     * the same width as the form itself.
     *
     * @return int
     */
    function get_form_errors_width() {
        if ($this->_form_errors_width == null) {
            return $this->_width;
        } else {
            return $this->_form_errors_width;
        }
    }

    /**
     * This method allows you to override
     * the width of the form errors table.
     * By default it uses the width of the
     * form as its size.
     *
     * @param string - the width
     */
    function set_form_errors_width($width) {
        $this->_form_errors_width = $width;
    }


    /**
     * This allows us to change the form errors
     * table title
     *
     * @param string - the new title
     */
    function set_form_errors_title($title) {
        $this->_form_errors_title = $title;
    }




	/**
	 * This function is used to set the
	 * default CSS class used on
	 * form field text when there is no
	 * error on that field
	 *
	 * @param string - the css class to use
	 */
	function set_default_css( $css ) {
		$this->_default_label_css = $css;
	}

	/**
	 * This function returns the
	 * default css class used for
	 * NON error text.
	 *
	 * @return string - the current default css
	 */
	function get_default_css() {
		return $this->_default_label_css;
	}


	/**
	 * This function is used to set the
	 * css class that is used on text
	 * when an error on that field is
	 * detected.
	 *
	 * @param string - the css class to use.
	 */
	function set_error_css( $css ) {
		$this->_err_label_css = $css;
	}


	/**
	 * This sets the $this->_has_confirmation
	 * flag.  to let the object know it has
	 * a required confirmation page, which
	 * should get called after the validation
	 * is successfull, and before the action is
	 * handled on the back-end.
	 *
	 * @param boolean - the flag value TRUE/FALSE
	 */
	function set_confirm( $flag = TRUE ) {
		$this->_has_confirm = $flag;
	}

	/**
	 * This gets the value of the confirmation flag.
	 * which tells the caller that this object
	 * has/doesn't have a required confirmation
	 * page.
	 *
	 * @return boolean
	 */
	function has_confirm() {
		return $this->_has_confirm;
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

    /**
     * This sets the action message.
     * This is called from withint the
     * form_action() method
     *
     * @param string - the action message
     */
    function set_action_message($message) {
        $this->_action_message = $message;
    }


    /**
     * This method sets the javasript action
     * to be taken when the cancel button
     * is clicked.  Calling this method
     * w/ a non NULL value automatically enables
     * the Cancel button.
     *
     * @param string - the javascript cancel action
     */
    function set_cancel_action($action) {
        $this->_cancel_action = $action;
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
	 * This function adds a form submit button
	 * with the appropriate action.
	 *
	 * @param string - the labe/action for the submit
	 *                 button.
	 * @param bool disable the button
     * @param string - the onSubmit function (if any)
     * @param boolean - disable opon submit?
	 * @return INPUTtag object
	 */
	function add_action( $label, $disabled = false, $submit_function = false,
                         $disable_on_submit = TRUE ) {
		$style="vertical-align:middle;";
		// here we mantain a fixed button size if a label length is reasonably small
		// i.e. OK or Cancel buttons or use padding otherwise
		if ( strlen($label)<8 )	$style .= "width: 90px;";
		else $style	.= "padding-left: 5px;padding-right:5px;";

		// Unique button label
        if (!$this->_action_counter) {
            $this->_action_counter = 1;
        }
        $blabel = FORM_ACTION.$this->_action_counter;
        $this->_action_counter++;

        // The onclick is responsible for:
        // -disabling the action button to discourage stupid users
        // -setting the action in the _form_action hidden variable
        // -calling the onSubmit function (if any), since form.submit() will not trigger
        //  the registered onSubmit function
        // -call the form.submit() function

        //build the action
        $onclick = "";
        if ($disable_on_submit) {
            $onclick .= "this.form.".$blabel.".disabled=true;";
        }
        $onclick .= "this.form.".FORM_ACTION.".value='".$label."';";
        if ($submit_function) {
            $onclick .= $submit_function.";";
        }

        if ($disable_on_submit) {
            $onclick .= "this.form.submit();";
        }

        $attrib = array("style" => $style,
                        "onclick" => $onclick);

        if ($disabled) $attrib[] = "disabled";
        return form_submit($blabel, $label, $attrib);
	}


	/**
	 * This function adds a submit button that
	 * can have any label.  It just makes the
	 * _form_action a hidden field.
	 * NOTE: you can only do this ONCE per form.
	 *
	 * @param string - the label of the button.
	 * @param string - the action value.
     * @param boolean - disable opon submit?
	 * @return ContainerWidget object
	 */
	function add_hidden_action( $label, $action, $disable_on_submit=TRUE) {
		$container = new ContainerWidget;
        // Unique button label
        if (!$this->_action_counter) {
            $this->_action_counter = 1;
        }
        $blabel = FORM_ACTION.$this->_action_counter;
        $this->_action_counter++;

        //build the action
        $onclick = "";
        if ($disable_on_submit) {
            $onclick .= "this.form.".$blabel.".disabled=true;";
        }
        $onclick .= "this.form.".FORM_ACTION.".value='".$action."';";
        $onclick .= "this.form.submit();";

        $style = "padding-left: 5px;padding-right:5px;";
        $attrib = array("style" => $style,
                        "onclick" => $onclick);

        $container->push(form_submit($blabel, $label,
                                     array("style" => $style,
                                           "onclick" => $onclick)));
        return $container;
	}

	/**
	 * This function adds an action as an image to
	 * submit the form.
	 *
	 * @param string - the image name path
	 * @param string - the action
     * @param boolean - disable opon submit?
	 *
	 * @return Atag object
	 */
	function add_image_action( $image_name, $action, $disable_on_submit=TRUE ) {
		// Unique button label
        if (!$this->_action_counter) {
            $this->_action_counter = 1;
        }
        $blabel = "_form_action".$this->_action_counter;
        $this->_action_counter++;

        $onclick = "document.".$this->_form_name."._form_action.value='".$action."';";
        $onclick .= "document.".$this->_form_name.".submit();";

        if ($disable_on_submit) {
            $click = "javascript:if (!window.global_cntr) {window.global_cntr = 1;} else {window.global_cntr++;} ";
            $click .= " if(window.global_cntr<2) {";
            $click .= $onclick."}";
        }

        $img = html_img($image_name);
        $img->set_tag_attribute("border", 0 );
        $img->set_tag_attribute("style", "cursor:hand;");

        $link = html_a("#", $img);
        $link->set_tag_attribute("onclick", $click);
        return $link;
	}


    /**
     * build a cancel button with a url
     * to go to
     *
     * @param string - 'Cancel' string
     * @return form button
     */
    function add_cancel($cancel = "Cancel") {

        $cancel_button = form_button("cancel",$cancel,
                                     array("type"=>"button",
                                           "style"=>"width: 90px;",
                                           "onclick"=>
                                           "javascript:document.location='".$this->_cancel_action."'"));
        $cancel_button->set_style("vertical-align:middle");
        return $cancel_button;
    }

    /**
     * This function is used to set the required field marker
     *
     * @param string - the marker
     */
     function set_required_marker($marker) {
         $this->_required_field_marker = $marker;
     }

    /**
     * This function is used to get the required field marker
     *
     * @return string - the marker
     */
     function get_required_marker() {
         if (is_object($this->_required_field_marker)) {
             return $this->_required_field_marker->render();
         } else {
             return $this->_required_field_marker;
         }
     }

     /**
      * This sets the required text
      *
      * @param string
      */
      function set_required_text($text) {
          $this->_required_field_text = $text;

      }


    /**
     * This method tests to see if we
     * have an element named $label,
     * so we can operate on it.
     *
     * @param string - the element's label
     * @param string - the name of the method that called us
     * @param boolean - test a hidden element?
     */
    function _test_element( $label, $method, $hidden=FALSE ) {
        if ($hidden) {
            if (!isset($this->_hidden_elements[$label])) {
                trigger_error("FormContent::".$method."() - '".$label."' element doesn't exist", E_USER_ERROR);
            }
        } else {
            if (!isset($this->_elements[$label])) {
                trigger_error("FormContent::".$method."() - '".$label."' element doesn't exist", E_USER_ERROR);
            }
        }
    }

    /**
     * return the values of all visible form elements as an array
     *
     * @access public
     * @return array
     *
     */
    function get_all_element_values()
    {

        foreach ($this->_elements as $element) {
            $data[$element->get_element_name()] = $element->get_value();
        }

        return $data;

    }

    /**
     * This method is used to keep a local reference
     * of the FormProcessor's FormValidation object
     *
     * @param FormValidation object
     */
    function _set_validation_object(&$FormValidation) {
        $this->_FormValidation =& $FormValidation;
    }

}
?>
