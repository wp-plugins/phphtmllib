<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the use of the 
 * FEFile widget and some post processing.
 *
 *
 * $Id: form5.php,v 1.1.1.1 2005/10/10 20:28:30 mike Exp $
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
 * is an extension of form2.php.
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 * @subpackage form-examples 
 */
class Form5Page extends MyLayoutPage {

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
        //  The title of this form is 'Testing Form 5'.
        //  The cancel url to go to is this same page (PHP_SELF)
        //  The width of the form is 600

	$container = container() ;

	//  Create the form
        $form = new Form5Content("Testing Form 5", $_SERVER['PHP_SELF'], 600) ;

	//  Create the form processor
        $fp = new FormProcessor($form) ;

	//  Don't display the form again if processing was successful.

	$fp->set_render_form_after_success(false) ;

	//  Add the Form Processor to the container.

	$container->add($fp) ;

	//  If the Form Processor was succesful, display
	//  some statistics about the uploaded file.

	if ($fp->is_action_successful())
	{
	    $container->add($form->get_file_info_table()) ;
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
class Form5Content extends StandardFormContent {

    var $__fileInfoTable ;

    /**
     * This method returns the InfoTable widget.
     */
    function get_file_info_table() {
	return $this->__fileInfoTable ;
    }

    /**
     * This method creates an InfoTable widget which
     * is used to display information regarding the 
     * uploaded file.
     */
    function set_file_info_table($fileInfo) {
        $it = new InfoTable("File Upload Summary", 400) ;

	$lines = file($fileInfo['tmp_name']) ;

	$it->add_row("Filename", $fileInfo['name']) ;
	$it->add_row("Temporary Filename", $fileInfo['tmp_name']) ;
	$it->add_row("File Size", filesize($fileInfo['tmp_name'])) ;
	$it->add_row("Lines", count($lines)) ;

	unset($lines) ;

	$this->__fileInfoTable = &$it ;
    }

    /**
     * This method gets called EVERY time the object is
     * created
     */
    function form_init_elements() {
        //  We want an confirmation page for this form but doing so
	//  results in an error (phpHtmlLib bug?).  For now, turn confirm
	//  off.

        $this->set_confirm(false);

	//  Use a 'dagger' character to denote required fields.

	$this->set_required_marker('&#134;');

        //  Now start to add the Form Elements that will be used in this form.

        //  Build the Upload File Widget.  It is a required field.
        //  It will automatically get validated as an Upload File.

	$file = new FEFile("CSV Filename", TRUE, "400px") ;
	$file->set_colon_flag(true) ;
	$file->set_max_size(10240000000) ;
	$file->set_temp_dir(ini_get('upload_tmp_dir')) ;
	//$file->add_valid_type("application/vnd.ms-excel") ;

        $this->add_element($file) ;
    }

    /**
     * This method is called only the first time the form
     * page is hit.
     */
    function form_init_data() {
	//  This seems to have no effect on a FEFile widget.
	$this->set_element_value("CSV Filename", "Upload a CSV File");
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

        $table->add_row($this->element_label("CSV Filename"), 
                        $this->element_form("CSV Filename"));

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
        //var_dump( $this->has_confirm() );
        //HARD CODE an error here to show how to show an error
        //and that it will prevent the confirm_action() method
        //from being called
        //$this->add_error("First Name", "Duplicate!!  You suck!");

        return TRUE;
    }

    function form_action() {
	//  Note that file was uploaded successfully.

        $this->set_action_message(html_h4("File \"" .
            $this->get_element_value("CSV Filename") . "\" successfully uploaded.")) ;
	$file = $this->get_element("CSV Filename") ;
	$fileInfo = $file->get_file_info() ;

	$this->set_file_info_table($fileInfo) ;

	//  Delete the file so we don't keep a lot of stuff around.

	if (!unlink($fileInfo['tmp_name']))
            $this->add_error("CSV Filename", "Unable to remove uploaded file.");

	return true ;
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


$page = new Form5Page("Form Example 5");

print $page->render();
?>
