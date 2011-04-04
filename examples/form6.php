<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the use of the 
 * FEUrl widget and some post processing.
 *
 *
 * $Id: form6.php,v 1.1.1.1 2005/10/10 20:28:30 mike Exp $
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


//use the class we defined from 
//Example 3.
include_once("MyLayoutPage.inc");

/**
 * A simple Page Layout object child.
 * this came from Example 3.  The example
 * is an extension of form5.php.
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 * @subpackage form-examples 
 */
class Form6Page extends MyLayoutPage {

    function content_block() {
	//  Add the InfoTableCSS so the tables look right
	$this->add_head_css(new InfoTableCSS) ;
	    
        //  Build the FormProcessor, and add the
        //  form content object that the FormProcessor 
        //  will use.
        //
        //  This uses the StandardFormContent object to build
        //  and render the look/feel of the form.  It has a built
        //  in mechanism for doing the form submit buttons, including
        //  the Cancel action.  
	//
        //  The title of this form is 'Testing Form 6'.
        //  The cancel url to go to is this same page (PHP_SELF)
        //  The width of the form is 600

	$container = container() ;

	//  Create the form
        $form = new Form6Content("Testing Form 6", $_SERVER['PHP_SELF'], 600) ;

	//  Create the form processor
        $fp = new FormProcessor($form) ;

	//  Display the form again even if processing was successful.

	$fp->set_render_form_after_success(true) ;

	//  Add the Form Processor to the container.

	//  If the Form Processor was succesful, display
	//  some statistics about the uploaded file.

	if ($fp->is_action_successful())
	{
	    $container->add($form->get_file_info_table()) ;
	    $container->add(html_br(2), $fp) ;
	}
	else
	{
	    $container->add($fp) ;
	}

	return $container ;
    }
}

/**
 * A simple Page Layout object child.
 * this came from Example 3.
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 * @subpackage form-examples 
 */
class Form6Content extends StandardFormContent {

    var $urlInfoTable ;

    /**
     * This method returns the InfoTable widget.
     */
    function get_file_info_table() {
	return $this->urlInfoTable ;
    }

    /**
     * This method creates an InfoTable widget which
     * is used to display information regarding the 
     * uploaded file.
     */
    function set_url_info_table($url) {

        $it = new InfoTable("URL Summary", 400) ;

	//  Open the URL and read the lines from it.

	if ($fh = @fopen($url, "r"))
	{
	    $lines = array() ;

	    while (!feof($fh))
		$lines[] = fgets($fh, 1048576) ;

            fclose ($fh) ;

	    $chars = 0 ;

	    foreach ($lines as $line)
	        $chars += strlen($line) ;

	    $it->add_row("URL", $url) ;
	    //$it->add_row("File Size", filesize($fileInfo['tmp_name'])) ;
	    $it->add_row("Lines", count($lines)) ;
	    $it->add_row("Characters", $chars) ;

	    unset($lines) ;
	}
	else
	{
	    $it->add_row("URL", $url) ;
	    $it->add_row("Error", "Unable to open URL for reading.") ;
	}

	$this->urlInfoTable = &$it ;
    }

    /**
     * This method gets called EVERY time the object is
     * created
     */
    function form_init_elements() {
        //  We want an confirmation page for this form

        $this->set_confirm(true);

	//  Use a 'dagger' character to denote required fields.

	$this->set_required_marker('&#134;');

        //  Now start to add the Form Elements that will be used in this form.

        //  Build the Upload File Widget.  It is a required field.
        //  It will automatically get validated as an Upload File.

	$url = new FEUrl("URL", TRUE, "400px") ;
	$url->set_colon_flag(true) ;

        $this->add_element($url) ;
    }

    /**
     * This method is called only the first time the form
     * page is hit.
     */
    function form_init_data() {
	//  Set the URL to the test.csv file used for widget7.php.
	//  Since the FEUrl validation doesn't like 'localhost' in
	//  the URL, map it to the loopback address.

	$this->set_element_value("URL", "http://" .
	    preg_replace("/^localhost$/", "127.0.0.1", $_SERVER['SERVER_NAME'])
       	    . PHPHTMLLIB_RELPATH . "/examples/test.csv");
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
        $table = html_table($this->_width,0,4);

        $table->add_row($this->element_label("URL"), 
                        $this->element_form("URL"));

	$this->add_form_block(null, $table) ;
    }

    /**
     * This method gets called after the FormElement data has
     * passed the validation, and has been confirmed. This 
     * enables you to validate the data against some backend 
     * mechanism, say a DB.
     *
     */
    function form_backend_validation() {
	//  Make sure the provided URL can actually be opened for reading.

	$url = $this->get_element_value("URL") ;

	if ($fh = @fopen($url, "r"))
        {
	    @fclose($fh) ;
	    return true ;
	}
	else
	{
	    $this->add_error("URL", "Unable to open URL.") ;
            return false ;
	}
    }

    function form_action() {
	//  URL is known good, process it.
	$url = $this->get_element_value("URL") ;
	$this->set_url_info_table($url) ;

	return true ;
    }

    /**
     * This method will get called after all validation has 
     * passed, and the confirmation has been accepted.
     *
     * This is where u save the info to the DB.
     */
    function confirm_action() {
        $this->set_action_message("URL Validated.");
        return TRUE ;
    }

}

$page = new Form6Page("Form Example 6") ;

print $page->render() ;
?>
