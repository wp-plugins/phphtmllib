<?php
/**
 * This file holds the babw Standard Form Content
 * which is a child of the FormContent object.
 * This provides a "standard" look for the outer
 * wrapper for all forms.  
 * All forms have a Save and Cancel button, as well
 * as a Confirmation of the Form.
 *
 *
 * $Id: StandardFormContent.inc 1690 2006-04-12 04:29:54Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */ 

/**
 * This is a child of the FormContent class to 
 * provide a 'standard' look and feel for forms.
 * It also enables a confirmation 'page' by default.
 *
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class StandardFormContent extends FormContent {


    /**
     * The title used in the wrapping table
     *
     */
    var $_form_title = "";

    /**
     * the InfoTable wrapper that holds
     * all fields.
     */
    var $_infotable = NULL;

    /**
     * Allow the default buttons to be shown?
     */
    var $_allow_actions = TRUE;

    /**
     * The label for the Action
     */
    var $action_label = "Save";

    /**
     * The label for the Cancel action
     */
    var $cancel_label = "Cancel";


	/**
	 * The wizard id associated with this content
	 * if we are being used inside a wizard
	 */
	var $_wizard_id = NULL;


    function StandardFormContent($title, $cancel_action=NULL,
                                 $width="100%") {
        $this->FormContent($width, $cancel_action);
        $this->set_form_title( $title );
        //each form has a confirmation
        $this->set_confirm(TRUE);
    }

    /**
     * this method sets the form title
     * which is used to wrap the entire form
     *
     * @param string - the form title
     */
    function set_form_title($title) {
        $this->_form_title = $title;
    }

    /**
     * This method is used to change the 'Save' button label.
     * 
     * @param string - the string to use
     */
    function set_action_label($label) { 
        $this->action_label = $label; 
    }

    /**
     * This method is used to change the 'Cancel' button label
     *
     * @param string - the cancel string
     */
    function set_cancel_label($label) { 
        $this->cancel_label = $label; 
    }

    /**
     * this builds the main wrapper for the 
     * form fields and ads the Save and Cancel buttons
     *
     * @param array - the form data
     * @param array - the form error fields (if any)
     * @return InfoTable widget object
     */
    function form() {
        $title = $this->_form_title._HTML_SPACE;
        $title .="( ".$this->_required_field_marker." ".$this->_required_field_text." )";
        $this->_infotable = new InfoTable($title, $this->_width);
        $this->_infotable->set_cellpadding(0);

        //ok call the Child class to add the 
        //form fields inside of form blocks
        $this->form_content();

        if ($this->_allow_actions) {
            $this->_infotable->add_row( $this->form_content_buttons() );
        }
        
        return $this->_infotable;
    }    


    /**
     * Child class MUST override this
     * to provide the form fields
     *
     * @return object
     */
    function form_content() {
        user_error("StandardFormContent::form_content() - CHILD MUST OVERRIDE ");
        return NULL;
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
        $title = $title._HTML_SPACE;

		//only show this if we aren't readonly
		//if we are in read only mode...required doesn't make sense
		if (!$this->is_readonly()) {
			$title .="( ".$this->_required_field_marker." ".$this->_required_field_text." )";
		}
        
        $table = new InfoTable($title, $this->_width);

        $this->build_confirm_table( $table );

        //now add the confirmation button
        $td = new TDtag(array("colspan" => 2,
                              "class" => "contentnovertical",
                              "align" => "center"),
                        $this->add_action("Confirm"),
                        _HTML_SPACE,
                        $this->add_action("Edit"));

        if ($this->_cancel_action) {
            $td->add(_HTML_SPACE, $this->add_cancel());
        }

        if ($show_buttons) {
            $table->add_row( $td );
        }

        return $table;
	}


    /**
     * This method handles the form action.
     * 
     * @return boolean TRUE = success
     *                 FALSE = failed.
     */
    function form_action() {
        switch ($this->get_action()) {
        case "Edit":
            return FALSE;
            break;

        case "Save":
        case "Confirm":
            return $this->confirm_action();
            break;
        }
    }

    /**
     * This method is responsible for handling the
     * confirmation page's Confirm action.
     */
    function confirm_action() {
        user_error("FormContent::confirm_action() - Child class must override");
        return FALSE;
    }


    /**
     * This function is used to build the standard
     * buttons for a form.
     *
     * @return ButtonPanel
     */
    function form_content_buttons() {
        $div = new DIVtag( array("style" => "background-color: #eeeeee;".
                                            "padding-top:5px;padding-bottom:5px",
                                 "align"=>"center", "nowrap"),
                           $this->add_action($this->action_label),
                           _HTML_SPACE,
                           $this->add_cancel($this->cancel_label) );
        return $div;
    }


    /**
     * This function is used to add a block of
     * form fields inside a table to this form.
     * This table will automatically get wrapped
     * inside a fieldset with a legend tag
     * to label the block
     *
     * @param string - the title for the fieldset
     * @param TABLEtag - the form fields inside a table
     */
    function add_form_block( $title=NULL, &$table ) {
        $this->_infotable->add_row( $this->build_form_block( $title, $table ) );
    }


    /**
     * this builds a fieldset and legend and adds the
     * form table to it.
     *
     * @param string - the legend string
     * @param TABLEtag - the form fields in a table
     * @return FIELDSETtag
     */
    function &build_form_block( $title=NULL, &$content ) {
        $div = &$this->_div_wrapper( );

        if ($title != NULL) {
            $fs = html_fieldset( $title );
            $fs->add_reference( $content );
            $div->add_reference( $fs );
        } else {
            $div->add_reference( $content );
        }
        return $div;
    }

    function &_div_wrapper() {
        $div = html_div();
        $div->set_style("background-color: #eeeeee;padding:5px;");
        return $div;
    }

    function _form_content_table($width="100%", $border=0, $cellspacing=0,
                                 $cellpadding=3) {
        $table = html_table($width,$border,$cellspacing,$cellpadding);
        return $table;
    }

	/**
	 * This method sets the wizard id.
	 * This is called from the FormWizard class
	 * 
	 * @param string
	 */
	function set_wizard_id($id) {
		$this->_wizard_id = $id;
	}

	/**
	 * This method gets the wizard id.
	 *  
	 * @return string
	 */
	function get_wizard_id() {
		return $this->_wizard_id;
	}
}
?>
