<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the use of the 
 * permissions checking mechanism built into the
 * PageWidget object.
 *
 *
 * $Id: widget13.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version 2.4.0
 *
 */ 

/**
 * Include the phphtmllib libraries
 *
 */
include_once("includes.inc");

class PermissionsCheckTestPage extends PageWidget {


    function PermissionsCheckTestPage($title) {
        //turn on the ability to do a permissions check
        $this->allow_permissions_checks(TRUE);

        $this->PageWidget($title, HTML);        

        //we need this for the css defined for the InfoTable
        //for the DialogWidget.  The DialogWidget uses InfoTable.
        $this->add_css_link(PHPHTMLLIB_RELPATH . "/css/defaulttheme.php");
    }

    /**
     * This method is called during constructor time to check
     * to make sure the page is allowed to build and render
     * any content.
     * 
     * @return boolean FALSE = not allowed.
     */
    function permission() {
        //If you want to see a 'permissions' error
        //on this page then pass in the query string
        //variable 'failed=1' on the url to this script.
        if (isset($_REQUEST["failed"])) {
            //ok we 'failed'.  Lets set the specialized error message
            $this->set_permissions_message("You don't have permissions!") ;
            return false;
        }
        return true;
    }

    /**
     * This will only get called if we have permissions to 
     * build and render the content for this page object.
     * 
     * @return object
     */
    function body_content() {
        $dialog = new MessageBoxWidget("Some title", "400",
                                       container("This is a message",
                                                 html_br(2),
                                                 "Want to see a permissions error?",
                                                 html_br(),
                                                 html_a($_SERVER["PHP_SELF"]."?failed=1",
                                                        "Click Here"))
                                                 );

        return $dialog;
    }
}

//build the Page object and try and
//render it's content.
//the permissions checking happens at
//'constructor' time.
$page = new PermissionsCheckTestPage("testing");

//the render method will not call the
//content building methods if the permissions
//fail.
print $page->render();
?>
