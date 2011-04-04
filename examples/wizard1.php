<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the basics of the
 * FormProcessing engine for phphtmllib.
 *
 *
 * $Id: wizard1.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
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
include_once(PHPHTMLLIB_ABSPATH . "/form/FormWizard.inc");

include_once("_steps.inc");

function debug( $var ) {
    echo "<xmp>\n";
    var_dump( $var );
    echo "</xmp>\n";
}


//use the class we defined from 
//Example 3.
include_once("MyLayoutPage.inc");

//session_start();

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
        return new MyWizard();
    }
}

class MyWizard extends FormWizard {
    function user_setup() {
        $this->add_step( "Hemna", "This is a long description of ".
                         "what the user should do.  Like do this step ".
                         "you goofball!  Just fill out the form!",
                         "", new Step1("Hemna", "", 600) );
        $this->add_step( "Dude", "This is some dude step", "", 
                         new Step2("Dude", "", 600) );
        $this->add_step( "Settings", "Use this step to configure your settings.", "", 
                         new Step3("My Settings", "", 600) );
    }
}



$page = new Form1Page("Form Example 1");
print $page->render();


?>
