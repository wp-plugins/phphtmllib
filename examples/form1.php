<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the basics of the
 * FormProcessing engine for phphtmllib.
 *
 *
 * $Id: form1.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage form-examples
 * @version 2.2.0
 *
 */ 

/**
 * Include the phphtmllib libraries
 *
 */
include("includes.inc");

/**
 * Include the Form Processing objects
 *
 */
include_once(PHPHTMLLIB_ABSPATH . "/form/includes.inc");


//use the class we defined from 
//Example 3.
include_once("MyLayoutPage.inc");

/**
 * A simple Page Layout object child.
 * this came from Example 3.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage form-examples 
 */
class Form1Page extends MyLayoutPage {

    function content_block() {
        //build the FormProcessor, and add the
        //Form content object that the FormProcessor 
        //will use.  Make the width of the form 600
        return new FormProcessor( new AccountForm(600));
    }
}


/**
 * This is the Class that handles the building
 * of the Form itself.  It creates the Form Elements
 * inside the form_init_elements() method.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage form-examples  
 */
class AccountForm extends FormContent {

    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements() {
        //we want an confirmation page for this form.
        $this->set_confirm();

        //now start to add the Form Elements that will 
        //be used in this form.

        //Build the First Name Form Element.  It is just
        //a simple Text field.  It is not required for
        //the user to enter data for this field.
        $this->add_element( new FEText("First Name", FALSE, "200px") );

        //Build the Email address Field.  It is a required field
        //It will automatically get validated as an Email address
        //it can accept either foo@bar.net or Joe Blow <foo@bar.net>
        $this->add_element( new FEEmail("Email Address", TRUE, "200px") );


        //now we need to build the password and confirm password
        //fields.  
        $password = new FEPassword("Password", TRUE, "200px");
        $this->add_element( $password );

        $confirm = new FEConfirmPassword("Confirm Password", TRUE, "200px");
        //add the password FormElement to the ConfirmPassword
        //FormElement so we can make sure they match.
        $confirm->password( $password );

        //add it to this form.
        $this->add_element( $confirm );

        //lets add a hidden form field
        $this->add_hidden_element("id");
    }

    /**
     * This method is called only the first time the form
     * page is hit.  This enables u to query a DB and 
     * pre populate the FormElement objects with data.
     *
     */
    function form_init_data() {
        //Pull some valies from the DB
        //and set the initial values of some of the
        //form fields.
        //
        //In this example we just hard code some
        //initial values

        $this->set_element_value("Email Address", "foo@bar.net");
        $this->set_hidden_element_value("id", "hemna");
    }


    /**
     * This is the method that builds the layout of where the
     * FormElements will live.  You can lay it out any way
     * you like.
     *
     */
    function form() {
        $table = html_table($this->_width,0,4);
        $table->set_style("border: 1px solid");

        $table->add_row($this->element_label("First Name"), 
                        $this->element_form("First Name"));

        $table->add_row($this->element_label("Email Address"), 
                        $this->element_form("Email Address"));

        $table->add_row($this->element_label("Password"), 
                        $this->element_form("Password"));

        $table->add_row($this->element_label("Confirm Password"), 
                        $this->element_form("Confirm Password"));

        $table->add_row(_HTML_SPACE, $this->add_action("Submit"));

        return $table;
    }

    /**
     * This method gets called after the FormElement data has
     * passed the validation.  This enables you to validate the
     * data against some backend mechanism, say a DB.
     *
     */
    function form_backend_validation() {
        //$this->add_error("Ass", "some bogus error happened");
        //return FALSE;
        return TRUE;
    }

    /**
     * This method is called ONLY after ALL validation has
     * passed.  This is the method that allows you to 
     * do something with the data, say insert/update records
     * in the DB.
     */
    function form_action() {
        $this->set_action_message("WOO!");
        //$this->add_error("Ass", "some bogus error happened");
        //$this->add_error("First Name", "Duplicate!!  You suck!");

        //var_dump( $this->get_element_value("First Name") );
        return TRUE;
    }
}


$page = new Form1Page("Form Example 1");
print $page->render();
?>
