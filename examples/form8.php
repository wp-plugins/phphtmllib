<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the use of the 
 * ActiveTab widget in conjunction with the
 * Form Processor.
 *
 *
 * $Id: form8.php,v 1.1.1.1 2005/10/10 20:28:30 mike Exp $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 * @subpackage form-examples
 * @since 2.5.5
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

/**
 * Include the ActiveTab objects
 *
 */
include_once(PHPHTMLLIB_ABSPATH . "/widgets/ActiveTab.inc");

//use the class we defined from Example 3.
include_once("MyLayoutPage.inc");

/**
 * A simple Page Layout object child.
 * this came from Example 3.
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 * @subpackage form-examples 
 */
class Form8Page extends MyLayoutPage
{
    function content_block() {
	//  Add the InfoTableCSS so the tables look right
	    $this->add_head_css(new InfoTableCSS) ;
	    $this->add_head_css(new ActiveTabCSS) ;
	    
        //build the FormProcessor, and add the
        //Form content object that the FormProcessor 
        //will use.
        //
        //This uses the StandardFormContent object to build
        //and render the look/feel of the form.  It has a built
        //in mechanism for doing the form submit buttons, including
        //the Cancel action.  
        //The title of this form is 'Testing'.
        //the cancel url to go to is http://www.newsblob.com
        //and the width of the form is 600

        return new FormProcessor( new StandardAccountForm("Testing",
            phl_request_uri(),
                                                          //$_SERVER['REQUEST_URI'],
                                                          600));
    }
}

/**
 * A simple Page Layout object child.
 * this came from Example 3.
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Mike Walsh <mike_walsg@mindspring.com>
 * @package phpHtmlLib
 * @subpackage form-examples 
 */
class StandardAccountForm extends StandardFormContent {

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

        //This will build a scrollable list of checkboxes.
        $list =  new FECheckBoxList("List", FALSE,
                                    "200px", "80px",
                                    array("Testing 123" => "foo",
                                          "What is this?" => "bar",
                                          "Somone's test" => "blah",
                                          "Slerm" => "slerm",
                                          "Flem" => "flom",
                                          "One" => 1));
        $list->disable_item("Testing 123");
        $this->add_element( $list );
        

        $this->add_element( new FEListBox("Anrede", FALSE, "100px", NULL,array("Frau"=>0,"Herr"=>1)) );

        //build a large textarea 
        $this->add_element( new FETextArea("Comment", TRUE, 20, 10,"400px", "100px" ) );

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
        //In this example we just hard code some
        //initial values
        $this->set_element_value("First Name", "testing");

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

	    $tabs = new ActiveTab( '100%', '400px' );
	    $tabs->add_tab( "User Info", $this->_user_info() );
	    $tabs->add_tab( "Optional Info", $this->_optional_info() );

        //  In order to get the ActiveTab to work on a form, the
        //  Javascript must be manually added (this is a bug).

        $script = html_script() ;
        $script->add($tabs->get_javascript()) ;

        //  Add the ActiveTab widget and its Javascript to a table.

        $table = html_table($this->_width, 0, 4) ;

        $table->add_row($tabs, $script) ;

	    $this->add_form_block(null, $table) ;
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
     * This method gets called after the FormElement data has
     * passed the validation, and has been confirmed. This 
     * enables you to validate the data against some backend 
     * mechanism, say a DB.
     *
     */
    function form_backend_validation() {
        //var_dump( $this->has_confirm() );
        //HARD CODE an error here to show how to show an error
        //and that it will prevent the confirm_action() method
        //from being called
        $this->add_error("First Name", "Duplicate - the name already exists!!!");
        return FALSE;
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

$page = new Form8Page("Form Example 8");
print $page->render();
?>
