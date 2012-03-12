<?php
/**
 * This file contains the FormProcessor class.
 *
 * $Id: FormProcessor.inc 3075 2007-10-30 20:09:07Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@cbestwhat?>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

define("FORM_ACTION", "_form_action");
define("FORM_VISITED", "_form_visited");
define("FORM_CONFIRM", "_form_confirm");

/**
 * This is the main engine for the processing
 * of Forms.  It builds the form tag, and calls
 * the appropriate FormContent methods to build
 * the FormElement's and validation, as well as
 * backend processing to do the action after the
 * data has been validated.
 *
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FormProcessor extends Container {


    /**
     * This array holds the FORMtag
     * attributes for this form
     *
     */
    var $_form_attributes = array("method" => "post",
                                  "action" => "",
                                  "name" => "myform",
                                  "target" => "",
                                  "onsubmit" => "",
                                  "style" => "margin: 0px 0px 0px 0px;");

    /**
     * This holds the FormContent Object
     * that knows how to render the
     * form.
     */
    var $_form_content = NULL;


    /**
     * This flag lets us know there
     * were errors during processing or
     * validating the form.
     */
    var $_has_errors = FALSE;

    /**
     * Flag to let us know the form
     * has been confirmed.
     */
    var $_confirmed = FALSE;

    /**
     * Flag to let us know if we should
     * render the form after it was
     * successfully processed
     */
    var $_form_success_render = TRUE;

    /**
     * This is the FormValidation object
     * used to validate the form elements
     */
    var $_FormValidation = NULL;

    /**
     * The action that was taken
     * for the form
     */
    var $_form_submit_action = NULL;

    /**
     * The form was processed and passed
     * the confirmation if any, and
     * it was successfull ?
     */
    var $_confirmed_successful = FALSE;

    /**
     * This tells us to show or not to
     * show the form errors autmatically.
     * The user of the FormProcessor
     * may want to deal with errors manually
     */
    var $_auto_show_errors = TRUE;


    /**
     * The constructor for the FormProcessor
     *
     * @param FormContent object
     * @param string the form name
     */
    function FormProcessor(&$form_content, $form_name="myform",
                           $form_action=NULL) {

        $this->_form_content = &$form_content;
        $this->set_form_name( $form_name );
        $this->_form_content->set_form_name($form_name);

        if ($form_action != NULL) {
            $this->set_form_action( $form_action );
        } else {
            $this->set_form_action( $_SERVER["PHP_SELF"] );
        }

        //Set up the Validation object
        //and the FormErrors object to
        //be used by this form.
        $this->setup_validation();

        //now process the form
        $this->_process_form();
    }

    /**
     * This function is used to setup
     * the validation object and the
     * form errors object that is to be
     * used by this form.
     *
     * You can override this method to
     * use a different FormErrors object
     * for localization.
     */
    function setup_validation() {
        $this->_FormValidation =& FormValidation::singleton();
        $this->_form_content->_set_validation_object($this->_FormValidation);
    }

    /**
     * This method does the logic of
     * doing the form processing
     */
    function _process_form() {
        $this->_init_form_content();

        //we only need to process the form
        //if it has been visited. Otherwise
        //it just gets rendered.
        if (!empty($_REQUEST[$this->_form_attributes['name'].FORM_VISITED]) &&
            $_REQUEST[$this->_form_attributes['name'].FORM_VISITED] == 1) {
            $this->_set_action();

            //let see if this was a confirmation page.
            if ( !empty($_REQUEST[FORM_CONFIRM]) ) {
                if ($_REQUEST[FORM_CONFIRM] == 1) {
                    //looks like this was a submit on a
                    //confirmation page.  we don't need
                    //to do form field validation.
                    $this->_confirmed = TRUE;
                } else {
                    //looks like the confirmation was aborted.
                    xxx("aborted");
                }
            }

            if ($this->_form_content->has_confirm()) {
                    //the form content has a confirmation
                    //we need to process
                    $this->_has_errors = !$this->_pre_confirm();
            }

            //we haven't been confirmed, so we
            //need to validate the form.
            if ($this->can_validate()) {
                //looks like we should do validation
                $this->do_validation();
            }

            if (!$this->_has_errors) {
                //no errors were found
                //make sure we don't have any backend errors
                $this->_has_errors = !$this->_form_content->form_backend_validation();
                if (!$this->_has_errors && (($this->_form_content->has_confirm()
                                             && $this->_confirmed) || !$this->_form_content->has_confirm())) {
                    // process action only at the final stage
                    $this->_has_errors = !$this->_process_action();

                    if (!$this->_has_errors) {
                        $this->_set_confirmed_success(TRUE);
                    }
                }
            }
        }
    }


    /**
     * This function is responsible for
     * processing the form action
     * after validation, and form confirmation
     * happens.
     *
     */
    function _process_action() {
        //There were no validation errors.
        return $this->_form_content->form_action();
    }

    /**
     * This method calls the FormContent
     * to let it do any data munging before the
     * confirmation page is rendered
     */
    function _pre_confirm() {

        if ($this->_form_content->_has_file_element) {
            //we need to allow any/all of the file elements
            //save the temp files during a confirmation.
            //if we don't, then the web server may delete
            //them before confirmation has been accepted.
            $this->_form_content->_pre_confirm();
        }

        //call the user defineable FormContent pre_confirm.
        return $this->_form_content->pre_confirm();
    }


    /**
     * This method walks the FormContent's visible elements
     * and calls the validation function for the element
     *
     */
    function do_validation() {
        $keys = array_keys( $this->_form_content->_elements );
        foreach( $keys as $key ) {
            if (!$this->_form_content->_elements[$key]->is_disabled()) {
                $valid = $this->_form_content->_elements[$key]->_do_validation($this->_FormValidation);
                if (!$valid) {
                    $this->_has_errors = TRUE;
                }                           
            } else {
                //detect disabled field hack attempts
                if ($this->_form_content->_elements[$key]->has_error()) {
                    $this->_has_errors = TRUE;
                }
            }
        }
    }


    /**
     * This method is called to render the form's html
     *
     */
    function render($indent_level=0, $output_debug=0) {
        if ($this->_has_errors) {
            //we need to render the form errors
            //and then the form
            return $this->render_error($indent_level, $output_debug);
        } else {
            //there are no errors!
            if (@$_REQUEST[$this->_form_attributes['name'] . FORM_VISITED] == 1) {
                //looks like the form has been processed?
                if ($this->_form_content->has_confirm() && !$this->_confirmed) {
                    return $this->render_confirm($indent_level, $output_debug);
                } else {
                    //Looks like the action worked
                    $success = $this->_form_content->form_success();

                    if ($this->_form_success_render) {
                        return $this->render_form($indent_level, $output_debug,
                                                  $success);
                    } else {
                        if (method_exists($success,"render")) {
                            //looks like this is an object.
                            //we'll assume it has a render function.
                            return $success->render($indent_level, $output_debug);
                        } else {
                            //since its not an object,
                            //lets just display it.
                            return $success;
                        }
                    }
                }
            } else {
                return $this->render_form($indent_level, $output_debug);
            }
        }
    }


    /**
     * This renders the form
     *
     * @param the FormContent->form() object
     * @param int - $indent_level
     * @param int - $output_debug
     * @param object - the form errors object.
     * @return raw html
     */
    function render_form( $indent_level, $output_debug, $obj=NULL ) {

        //build the $this->_form object.
        $this->_build_form_tag();

        //check to see if the form_content
        //has any js, or any of the form elements
        //have js.
        $form_js = $this->_build_javascript();
        if (strlen($form_js) > 0) {
            $script = html_script();
            $script->add( $form_js );
            //$this->_form->add( $script );
        }

        if ($obj) {
            $this->_form->add_reference( $obj );
        }

        $form = $this->_form_content->form();
        $this->_form->add_reference( $form );

        //add the FormContent's hidden declared
        //hidden form fields.
        $this->_add_hidden_fields();

        //Ok lets add our hidden vars
        $this->__hidden_fields();

        if (isset($script)) {
            $c = container( $script, $this->_form );
            return $c->render($indent_level, $output_debug);
        } else {
            return $this->_form->render($indent_level, $output_debug);
        }

    }

    /**
     * This function renders the confirmation
     * page.  This page sits in between the
     * front end form, and the action handler.
     * This only gets called after a form
     * and its data has been successfully
     * validated.
     *
     * @param int - $indent_level
     * @param int - $output_debug
     *
     * @return string - the raw html
     */
    function render_confirm( $indent_level, $output_debug ) {
        //build the $this->_form object.
        $this->_build_form_tag();

        //add the confirm object/html
        $confirm = $this->_form_content->form_confirm( );
        $this->_form->add_reference( $confirm );

        //ok add all of the submitted data as hidden form fields
        $this->_add_confirm_data();

        //Ok lets add our hidden vars
        $this->__hidden_fields();

        return $this->_form->render($indent_level, $output_debug);
    }


    /**
     * This renders the error table
     * and then the form with the fields
     *
     * @param array - the form field vlues.
     * @param array - array of errors.
     * @param int - $indent_level
     * @param int - $output_debug
     *
     * @return raw html
     */
    function render_error( $indent_level, $output_debug) {

        if ($this->_auto_show_errors) {
            //Ok first lets build the error table
            $wrapper = new DIVtag;
            $errors = $this->_form_content->form_errors();
            if ($errors != NULL) $wrapper->add( $errors, html_br() );
        } else {
            $wrapper = NULL;
        }


        return $this->render_form( $indent_level, $output_debug, $wrapper);
    }




    //***********************************************//
    //*       utility functions for this class      *//
    //***********************************************//


    /**
     * This method lets us turn on/off the
     * ability to do validation for the form
     *
     * @return BOOLEAN
     */
    function can_validate() {
        return TRUE;
    }


    /**
     * This function turns on the ability to
     * render the form after the success
     * of the action.  Normally this feature
     * is off
     *
     */
    function set_render_form_after_success($flag=TRUE) {
        $this->_form_success_render = $flag;
    }

    /**
     * This is used to test to see if the form action
     * was processed succesfully.
     * This is usefull for external entities to determine
     * if the form was processed, and it was successful.
     *
     * @return boolean
     */
    function is_action_successful() {
        return $this->_confirmed_successful;
    }

    /**
     * This flag sets the flag that tells
     * if we successfully confirmed the form,
     * and processed the action
     *
     * @param boolean
     */
    function _set_confirmed_success($flag=TRUE) {
        $this->_confirmed_successful = $flag;
    }

    /**
     * This sets the flag that tells this class
     * to automatically call the form contents
     * form errors and display it or not
     *
     * @param boolean - show errors?
     */
    function set_auto_error_display($flag=TRUE) {
        $this->_auto_show_errors = $flag;
    }

    /**
     * This gets the current value of the flag
     * that tells us to show form errors automatically
     * or not.
     *
     * @return boolean
     */
    function get_auto_error_display() {
        return $this->_auto_show_errors;
    }


    /**
     * This method allows us to get access to the
     * errors display object that is generated by
     * the form content.  This is the display
     * object that is meant to be rendered directly.
     * If there are no errors. we will return NULL
     *
     * @return object
     */
    function &get_error_display_object() {
        if ($this->_has_errors) {
            return $this->_form_content->form_errors();
        } else {
            return NULL;
        }
    }


    /**
     * This method returns an array of errors that
     * happened in the form.
     *
     * @return array
     */
    function get_error_array() {
        return $this->_form_content->get_error_array();
    }

    /**
     * This returns the flag that tells us that
     * the form has errors during processing
     *
     * @return boolean
     */
    function has_errors() {
        return $this->_has_errors;
    }




    //************************************************//
    //*       FORMtag Attributes for this class      *//
    //************************************************//

    /**
     * This function is used to set the
     * form name
     *
     * @param string
     */
    function set_form_name($name) {
        $this->_form_attributes["name"] = $name;
    }

    /**
     * This function is used to get
     * the form name
     *
     * @return string
     */
    function get_form_name() {
        return $this->_form_attributes["name"];
    }

    /**
     * This function is used to set the
     * form target
     *
     * @param string
     */
    function set_form_target($target) {
        $this->_form_attributes["target"] = $target;
    }

    /**
     * This function is used to get
     * the form target
     *
     * @return string
     */
    function get_form_target() {
        return $this->_form_attributes["target"];
    }

    /**
     * This function is used to set the
     * form method
     *
     * @param string (POST or GET)
     */
    function set_form_method($method) {
        if ( strcasecmp($method,"GET") !=0 && strcasecmp($method,"POST") !=0 ) {
            user_error("FormProcessor::set_form_method() - INVALID Form method ".$method);
        } else {
            $this->_form_attributes["method"] = $method;
        }
    }

    /**
     * This function is used to get
     * the form method
     *
     * @return string (POST or GET)
     */
    function get_form_method() {
        return $this->_form_attributes["method"];
    }

    /**
     * Sets the form action
     *
     * @param string
     */
    function set_form_action($action) {
        $this->_form_attributes["action"] = $action;
    }

    /**
     * This function is used to get
     * the form action
     *
     * @return string (POST or GET)
     */
    function get_form_action() {
        return $this->_form_attributes["action"];
    }

    /**
     * Sets the form enctype
     *
     * @param string
     */
    function set_form_enctype($enctype) {
        $this->_form_attributes["enctype"] = $enctype;
    }

    /**
     * This function is used to get
     * the form enctype value
     *
     * @return string
     */
    function get_form_enctype() {
        return $this->_form_attributes["enctype"];
    }


    /**
     * This is used to set the action
     * submitted by the user
     *
     */
    function _set_action() {
        $this->_form_submit_action = $_REQUEST[FORM_ACTION];
        $this->_form_content->set_action($this->_form_submit_action);
    }

    /**
     * This is used to get the action that was
     * processed by the form
     *
     * @return string
     */
    function get_action() {
        return $this->_form_submit_action;
    }


    /**
     * Set the onsubmit attribute to the form
     * NOTE: The FormContent child can automatically
     * set this value depending on the FormElement
     * children it contains.
     *
     * @param string
     * @return none
     */
    function set_onsubmit($js) {
        $this->_form_attributes["onsubmit"] = $js;
    }

    /**
     * Gets the current value of the form tag's
     * onsubmit value
     *
     * @return string
     */
    function get_onsubmit() {
        return $this->_form_attributes["onsubmit"];
    }

    /**
     * Set a random attribute on the form tag.
     * You should know what you are doing as this
     * might invalidate the output html with the
     * W3C validator.
     *
     * @param string the key
     * @param string the value
     */
    function set_form_attribute($key, $value) {
        $this->_form_attributes[$key] = $value;
    }


    //************************************//
    //*       Some Private methods       *//
    //************************************//

    /**
     * This method initializes the FormContent
     * during processing.
     *
     * @return none
     */
    function _init_form_content() {
        //let the form build the FormElement objects
        //that will be used by the form
        $this->_form_content->form_init_elements();

        //first we need to
        if (!@$_REQUEST[$this->_form_attributes['name'] . FORM_VISITED]) {
            $this->_form_content->form_init_data();
        }

        //see if the form content has a child of the
        //FEFile element, so we can automatically
        //add the enctype to the form tag attribute
        if ($this->_form_content->_has_file_element) {
            $this->set_form_enctype("multipart/form-data");
        }
    }


    /**
     * this function builds the FORMtag object
     * and its attributes.
     *
     * @return FORMtag object.
     */
    function _build_form_tag() {
        //see if we need to add the onsubmit attribute to the form
        //this only needs to happen on the non-confirmation
        //portion of the forms.
        if (!isset($_REQUEST[$this->_form_attributes['name'] . FORM_VISITED])) {
            if (strlen($this->_form_content->_form_on_submit) > 0) {
                $set = TRUE;
                $this->set_onsubmit( $this->get_onsubmit().$this->_form_content->_form_on_submit.$this->_form_content->_form_action_elements_on_submit );
            }
        } else {
            //re-rendering the form and it has errors.
            //we need the onsubmit if they have it.
            if (isset($_REQUEST[$this->_form_attributes['name'] . FORM_VISITED]) && $this->_has_errors) {
                if (strlen($this->_form_content->_form_on_submit) > 0) {
                    $set = TRUE;
                    $this->set_onsubmit($this->get_onsubmit().$this->_form_content->_form_on_submit.$this->_form_content->_form_action_elements_on_submit );
                }
            } else if (isset($_REQUEST[FORM_CONFIRM]) && $_REQUEST[FORM_CONFIRM] == 1) {
                //form has been confirmed lets add it
                //in case we are showing the form again
                if (strlen($this->_form_content->_form_on_submit) > 0) {
                    $set = TRUE;
                    $this->set_onsubmit( $this->get_onsubmit().$this->_form_content->_form_on_submit.$this->_form_content->_form_action_elements_on_submit );
                }
            } else {
                $this->set_onsubmit($this->_form_content->_form_action_elements_on_submit);
            }
        }

        $form_attrs = array();
        foreach( $this->_form_attributes as $name => $value) {
            if ($value) {
                $form_attrs[$name] = $value;
            }
        }
        $this->_form = new FORMtag( $form_attrs );
    }

    /**
     * This adds all of the submitted data as
     * hidden form fields
     *
     */
    function _add_confirm_data() {
        $keys = array_keys( $this->_form_content->_elements );
        foreach( $keys as $key ) {
            //make sure the element isn't disabled.
            if (!$this->_form_content->_elements[$key]->is_disabled()) {
                $this->_form->add($this->_form_content->_elements[$key]->get_confirm_element());
            }
        }

        $keys = array_keys( $this->_form_content->_hidden_elements );
        foreach( $keys as $key ) {
            $this->_form->add( $this->_form_content->_hidden_elements[$key]->get_confirm_element() );
        }
    }


    /**
     * This function adds the form content's
     * hidden form fields to the
     * form automatically
     *
     */
    function _add_hidden_fields() {
        //Lets add the form's hidden vars it wants
        foreach ($this->_form_content->_hidden_elements as $element) {
            $this->_form->add( $element->get_element() );
        }
    }


    /**
     * This method adds the processor specific
     * hidden fields.
     *
     */
    function __hidden_fields() {
        $this->_form->add( form_hidden(FORM_ACTION, ''),
                           form_hidden($this->_form_attributes['name'] . FORM_VISITED,1) );

        if ($this->_form_content->has_confirm() && !$this->_confirmed) {
            if (@!$_REQUEST[$this->_form_attributes['name'] . FORM_VISITED] || $this->_has_errors) {
                $this->_form->add( form_hidden(FORM_CONFIRM, 0 ) );
            } else {
                $this->_form->add( form_hidden(FORM_CONFIRM, 1 ) );
            }
        } else if ($this->_form_content->has_confirm() && !$this->_confirmed) {
            //reset this so they can submit again
            $this->_form->add( form_hidden(FORM_CONFIRM, 0 ) );
        }
    }

    /**
     * This method is used to build any Javascript
     * that is used by the form and/or the form elements
     * used in the form.
     *
     * @return string
     */
    function _build_javascript() {
        $form_js = $this->_form_content->javascript();

        //now walk each form element and try to get any js
        foreach( $this->_form_content->_elements as $element ) {
            $form_js .= $element->javascript();
        }

        return $form_js;
    }
}
?>
