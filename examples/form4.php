<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the use of the master slave element
 *
 *
 * $Id: form4.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Sumedh Thakar <sumedh_thakar@yahoo.com>
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

include_once("MyLayoutPage.inc");


/**
 * A simple class to be the master. It contains a list of countries and the acceptable states for each county.
 *  
 * @author Sumedh Thakar <sumedh_thakar@yahoo.com>
 * @package phpHtmlLib
 * @subpackage form-examples 
 */

class FECountryListMaster extends FEListBoxMaster {
    /**
     * The states array format "United States" => array ("code" => "US",
     *                                                   "slave" => Array("California" => "CA")
     *                                                  )
     * if a seperate "code" value is not given then the array key (country name) is used
     *  
     * @var array
     */
    var $_countries = array("Select Country",
                         "Hungary" ,
                         "Iceland" ,
                         "India" => array("code" => "IN",
                                "slave" => array("Select State" => "",
                                                "Andhra Pradesh" => "Andhra Pradesh",
                                                "Andaman and Nicobar Islands" => "Andaman and Nicobar Islands",
                                                "Maharashtra" => "Maharashtra",
                                                "Manipur" => "Manipur",
                                                "Uttar Pradesh" => "Uttar Pradesh",
                                                "Uttaranchal" => "Uttaranchal",
                                                "West Bengal" => "West Bengal",
                                           )
                                ),
                         "Italy" ,
                         "Jamaica" ,
                         "Japan" ,
                         "Jersey, C.I." ,
                         "Jordan" ,
                         "Kazakhstan" ,
                         "Kenya" ,
                         "United Kingdom" ,
                         "United States of America" => array("code" => "US",
                             "slave" => array("Select State" => "",
                                             "Alabama" => "Alabama",
                                             "California" => "California",
                                             "Colorado" => "Colorado",
                                             "Guam" => "Guam",
                                             "American Samoa" => "American Samoa",
                                             "Palau" => "Palau",
                                            )
                                  ),
                         "Uruguay" ,
                         "Uzbekistan" ,
                         "Zimbabwe" 
                       );
     

    /**
     * The constructor
     * 
     * @param string text label for the element
     * @param boolean is this a required element?
     * @param int element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int element height in px
     * 
     */
    function FECountryListMaster($label, $required = TRUE, $width = NULL, $height = NULL) {

        //Get the data and put it in the format that FEListBoxMaster wants it.
        $tmp = array();
        foreach($this->_countries as $key => $country){
            if (!is_array($country)) {
                $tmp[$country] = array("code"=>$country);
            } else {
                $tmp[$key] = $country;
            }
        }
        $tmp['Select Country']["code"] = "";
       
        //Create the master.
        $this->FEListBoxMaster($label, $required, $width, $height);
        //Set the master-slave array
        $this->set_list_data($tmp);
    }

}
/**
 * This demonstrates the power of the master-slave relationship between two list elements
 * The control produces the javascript required to change the value of the slave when the
 * master changes. It also automatically does the verification to check if the given value
 * of the slave is in the list of values for the given master. This way your validation is
 * taken care of
 * 
 * @author Sumedh Thakar <sumedh_thakar@yahoo.com>
 * @package phpHtmlLib
 * @subpackage form-examples 
 */
class Form4Page extends MyLayoutPage {

    function content_block() {
        //build the FormProcessor, and add the
        //Form content object that the FormProcessor 
        //will use.  Make the width of the form 600
        return new FormProcessor( new MasterSlaveForm(600));
    }
}


/**
 * This is the Class that handles the building
 * of the Form itself.  It creates the Form Elements
 * inside the form_init_elements() method.
 *
 * @author Sumedh Thakar <sumedh_thakar@yahoo.com>
 * @package phpHtmlLib
 * @subpackage form-examples  
 */
class MasterSlaveForm extends FormContent {

    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements() {
        //we do not want any confirmation page for this form.
        $this->set_confirm(false);
        
        //Create the slave element, a simple dropdown
        $state = new FEListBox("State",true);
        
        $this->add_element($state);
        
        //Create the master element
        $country = new FECountryListMaster("Country");
        
        //Set the state as the slave of this. remember to pass an array of references
        $country->set_slave_elements(array(&$state));
        
        $this->add_element($country);

        //Create the slave element, a simple dropdown
        $state1 = new FEListBox("State1",true);
        
        $this->add_element($state1);
        
        //Create the master element
        $country1 = new FECountryListMaster("Country1");
        
        //Set the state as the slave of this. remember to pass an array of references
        $country1->set_slave_elements(array(&$state1));
        
        $this->add_element($country1);
        
    }

    /**
     * This method is called only the first time the form
     * page is hit.  This enables u to query a DB and 
     * pre populate the FormElement objects with data.
     *
     */
    function form_init_data() {
        
        //In this example we just hard code some
        //initial values
        $this->set_element_value("Country", "India");
        
        $this->set_element_value("State", "Maharashtra");

        $this->set_element_value("Country1", "United States of America");

        $this->set_element_value("State1", "California");

        
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

        $table->add_row($this->element_label("Country"), 
                        $this->element_form("Country"));

        $table->add_row($this->element_label("State"), 
                        $this->element_form("State"));

        $table->add_row($this->element_label("Country1"), 
                        $this->element_form("Country1"));

        $table->add_row($this->element_label("State1"), 
                        $this->element_form("State1"));


        $table->add_row(_HTML_SPACE, $this->add_action("Submit"));

        return $table;
    }

    
    /**
     * This method is called ONLY after ALL validation has
     * passed.  This is the method that allows you to 
     * do something with the data, say insert/update records
     * in the DB.
     */
    function form_action() {
        
        $this->set_action_message("Country :".$this->get_element_value("Country")." State ".$this->get_element_value("State")."Country1 :".$this->get_element_value("Country1")." State1 ".$this->get_element_value("State1"));
        
        return TRUE;
    }
}


$page = new Form4Page("Master-Slave list example");
print $page->render();
?>
