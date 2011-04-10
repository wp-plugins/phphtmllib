<?php

/**
 * A simple Page Layout object child.
 * this came from Example 3.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage form-examples 
 */
class Step1 extends StandardFormContent {

    /**
     * This method gets called EVERY time the object is
     * created
     */
    function form_init_elements() {
        $this->add_element( new FEText("First Name", TRUE, 20) );

        $password = new FEPassword("Password", TRUE);
        $this->add_element( $password );

        $confirm = new FEConfirmPassword("Confirm Password", TRUE);
        $confirm->password( $password );
        $this->add_element( $confirm );

        $this->add_element( new FEEmail("Email Address", TRUE, "200px") ); 
    }

    /**
     * This method is called only the first time the form
     * page is hit.
     */
    function form_init_data() {
        //Pull some valies from the DB
        //and set the initial values of some of the
        //form fields.
        //
        //In this example we just hard code some
        //initial values
        $this->set_element_value("First Name", "testing");
    }

    /**
     * This method is called by the StandardFormContent object
     * to allow you to build the 'blocks' of fields you want to
     * display.  Each form block will live inside a fieldset tag
     * with the a title. 
     *
     * In this example we have 2 form 'blocks'.
     */
    function form_content() {
        $this->add_form_block("User Info", $this->_user_info() );
    }

    /**
     * This private method builds the table that holds
     * the 'user' form fields'
     *
     */
    function &_user_info() {
        $table = html_table($this->_width,0,2);
        $table->add_row($this->element_label("First Name"), 
                        $this->element_form("First Name"));

        $table->add_row($this->element_label("Email Address"), 
                        $this->element_form("Email Address"));

        $table->add_row($this->element_label("Password"), 
                        $this->element_form("Password"));

        $table->add_row($this->element_label("Confirm Password"), 
                        $this->element_form("Confirm Password"));

        return $table;
    }

    /**
     * This method gets called after the FormElement data has
     * passed the validation, and has been confirmed. This 
     * enables you to validate the data against some backend 
     * mechanism, say a DB.
     *
     */
    function form_backend_validation() {
        //HARD CODE an error here to show how to show an error
        //and that it will prevent the confirm_action() method
        //from being called
        //$this->add_error("First Name", "Duplicate!!  You suck!");
        return TRUE;
    }

    /**
     * This method will get called after all validation has 
     * passed, and the confirmation has been accepted.
     *
     * This is where u save the info to the DB.
     */
    function confirm_action() {
        //$this->set_action_message("WOO!");
        return TRUE;
    }
}


class Step2 extends StandardFormContent {

    /**
     * This method gets called EVERY time the object is
     * created
     */
    function form_init_elements() {

        //This will build a scrollable list of checkboxes.
        $this->add_element( new FECheckBoxList("List", FALSE,
                                               "200px", "80px",
                                               array("Testing 123" => "foo",
                                                     "What is this?" => "bar",
                                                     "Somone's test" => "blah",
                                                     "Slerm" => "slerm",
                                                     "Flem" => "flom",
                                                     "One" => 1)));

        $this->add_element( new FEListBox("Anrede", FALSE, "100px", NULL,array("Frau"=>0,"Herr"=>1)) );

        //build a large textarea 
        $this->add_element( new FETextArea("Comment", TRUE, 20,10,"400px", "100px" ) );

        $this->add_hidden_element( "foo" );
        
        $this->add_element( new FECheckBox ("Patient Contact1", "Daytime Phone") );
        $this->add_element( new FECheckBox ("Patient Contact2", "Evening Phone") );
        $this->add_element( new FECheckBox ("Patient Contact3", "Email") ); 

    }

    /**
     * This method is called only the first time the form
     * page is hit.
     */
    function form_init_data() {
        //Pull some valies from the DB
        //and set the initial values of some of the
        //form fields.
        //
        //set a few of the checkboxlist items as checked.
        $this->set_element_value("List", array("bar","slerm",1));

        //change the value of the hidden form field
        $this->set_hidden_element_value("foo", "hemna");
    }

    /**
     * This method is called by the StandardFormContent object
     * to allow you to build the 'blocks' of fields you want to
     * display.  Each form block will live inside a fieldset tag
     * with the a title. 
     *
     * In this example we have 2 form 'blocks'.
     */
    function form_content() {
        $this->add_form_block("Optional", $this->_optional_info() );
    }


    /**
     * This private method builds the table that holds
     * the 'optional' form fields'
     *
     */
    function &_optional_info() {
        $table = html_table($this->_width,0,2);

        $table->add_row($this->element_label("Anrede"), 
                        $this->element_form("Anrede"));

        $table->add_row($this->element_label("List"), 
                        $this->element_form("List"));

        $table->add_row($this->element_label("Comment"), 
                        $this->element_form("Comment"));

        $td = new TDtag( array("colspan" => 2),
                         $this->element_form("Patient Contact1"),
                         $this->element_form("Patient Contact2"),
                         $this->element_form("Patient Contact3") );

        $table->add_row( $td );

        return $table;
    }

    /**
     * This method will get called after all validation has 
     * passed, and the confirmation has been accepted.
     *
     * This is where u save the info to the DB.
     */
    function confirm_action() {
        //$this->set_action_message("WOO!");
        return TRUE;
    }
}


class Step3 extends StandardFormContent {

    /**
     * This method gets called EVERY time the object is
     * created
     */
    function form_init_elements() {

        $this->add_element( new FEIPAddress ("My IP", TRUE) );
        $this->add_element( new FEUrl("Home Page") );
        $this->add_element( new FENumberPrice("Dollar Amount") );

    }

    /**
     * This method is called only the first time the form
     * page is hit.
     */
    function form_init_data() {
        //Pull some valies from the DB
        //and set the initial values of some of the
        //form fields.
        //
        //set a few of the checkboxlist items as checked.
        $this->set_element_value("Home Page", "http://www.cnn.com");
    }

    /**
     * This method is called by the StandardFormContent object
     * to allow you to build the 'blocks' of fields you want to
     * display.  Each form block will live inside a fieldset tag
     * with the a title. 
     *
     * In this example we have 2 form 'blocks'.
     */
    function form_content() {
        $this->add_form_block("Settings", $this->_optional_info() );
    }


    /**
     * This private method builds the table that holds
     * the 'optional' form fields'
     *
     */
    function &_optional_info() {
        $table = html_table($this->_width,0,2);

        $table->add_row($this->element_label("My IP"), 
                        $this->element_form("My IP"));

        $table->add_row($this->element_label("Home Page"), 
                        $this->element_form("Home Page"));

        $table->add_row($this->element_label("Dollar Amount"), 
                        $this->element_form("Dollar Amount"));

        return $table;
    }

    /**
     * This method will get called after all validation has 
     * passed, and the confirmation has been accepted.
     *
     * This is where u save the info to the DB.
     */
    function confirm_action() {
        //$this->set_action_message("WOO!");
        return TRUE;
    }
}

?>