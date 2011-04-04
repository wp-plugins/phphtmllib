<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the use of the 
 * FEUrl widget, the DefaultGUIDataList widget
 * and some post processing.
 *
 * This example was derived from form2.php,
 * widget7.php, and example3.php supplied with
 * the phpHtmlLib distribution.
 *
 *
 * $Id: form7.php,v 1.1.1.1 2005/10/10 20:28:30 mike Exp $
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
 * Include Data List objects
 *
 */

include_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/includes.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/data_list/ArrayDataListSource.inc");


//  Use the class defined in Example 3.
include_once("MyLayoutPage.inc");

//  Define the session variables used to
//  keep data persistent between page views.

define('FORM7_SESSION_DATA', 'Form7SessionData') ;
define('FORM7_SESSION_HEADER', 'Form7SessionHeader') ;
define('FORM7_SESSION_INFO', 'Form7SessionInfo') ;

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
class Form7Page extends MyLayoutPage {

    function content_block() {
	//  Add the InfoTableCSS so the tables look right
	$this->add_head_css(new InfoTableCSS) ;
	    
        //  Build the FormProcessor, and add the form content
        //  object that the FormProcessor will use.
        //
        //  This uses the StandardFormContent object to build
        //  and render the look/feel of the form.  It has a built
        //  in mechanism for doing the form submit buttons, including
        //  the Cancel action.  
	//
        //  The title of this form is 'Testing Form 7'.
        //  The cancel url to go to is this same page (PHP_SELF)
        //  The width of the form is 600

	$container = container() ;

	//  Create the form
        $form = new Form7Content("Form 7", $_SERVER['PHP_SELF'], 600) ;

	//  Create the form processor
        $fp = new FormProcessor($form) ;

	//  Display the form again even if processing was successful.

	$fp->set_render_form_after_success(false) ;

	//  If the Form Processor was succesful, display
	//  some statistics about the uploaded file.

	if ($fp->is_action_successful())
	{
	    //  Add the summary table
	    $container->add($form->get_url_info_table()) ;

	    //  Get header and record data
	    $csvHeader = $form->get_CSV_header() ;
	    $csvData = $form->get_CSV_data() ;

	    //  build the csv file data list object.
            $csvlist = new CSVGUIDataList("CSV Data List", 600, $csvHeader[0]) ;
	    $csvlist->set_align("left") ;

            //$csvlist = new CSVGUIDataList("CSV Data List", 600, 0) ;

	    $csvlist->set_headers($csvHeader) ;
	    $csvlist->set_data_source_array($csvData) ;

	    $container->add(html_br(2), $csvlist) ;

	    //  Add the CSS to support the display of the datalist

	    $this->add_head_css(new DefaultGUIDataListCSS) ;

	    //  Add the Form Processor to the container.

	    $container->add(html_br(2), $fp) ;

        }
	else if (!empty($_POST['_action']) && ($_POST['_action'] == 'Reset'))
	{
	    $location =  "http://" . $_SERVER['SERVER_NAME'] . $_SERVER['PHP_SELF'] ;
	    header("Location:  " . $location) ;
	    exit ;
	}
	else if (!empty($_POST['_action']) && ($_POST['_action'] == 'Export CSV'))
	{
	    $filter = !empty($_POST['checkbox']) ? $_POST['checkbox'] : null ;

	    //  Load the CSV processed previously

	    $form->load_CSV_header_from_session() ;
	    $form->load_CSV_data_from_session() ;

	    $csvHeader = $form->get_CSV_header() ;
	    $csvData = $form->get_CSV_data() ;

	    //  build the csv file data list object.

            $csvlist = new CSVGUIDataList("CSV Data List", 600, $csvHeader[0]) ;
	    $csvlist->set_align("left") ;

	    //  Initialize the headers and data source
	    $csvlist->set_headers($csvHeader) ;

	    $csvlist->set_data_source_array($csvData) ;

	    $this->exportCSV($csvHeader, $csvData, $filter) ;

	    $location =  "http://" . $_SERVER['SERVER_NAME'] . $_SERVER['PHP_SELF'] ;
	    header("Location:  " . $location) ;
	    exit ;
	}
	else if (!empty($_POST))  //  Some action on the DefaultGUIDataList
	{
	    $form->load_InfoTable_from_session() ;
            $container->add($form->get_url_info_table()) ;

	    //  Load the CSV processed previously

	    $form->load_CSV_header_from_session() ;
	    $form->load_CSV_data_from_session() ;

	    $csvHeader = $form->get_CSV_header() ;
	    $csvData = $form->get_CSV_data() ;

	    //  build the csv file data list object.

            $csvlist = new CSVGUIDataList("CSV Data List", 600, $csvHeader[0]) ;
	    $csvlist->set_align("left") ;

	    //  Initialize the headers and data source
	    $csvlist->set_headers($csvHeader) ;

	    $csvlist->set_data_source_array($csvData) ;

	    //  Add the widget to the container

	    $container->add(html_br(2), $csvlist) ;

	    //  Add the CSS to support the display of the datalist

	    $this->add_head_css(new DefaultGUIDataListCSS) ;
        }
	else
	{
	    //  Add the Form Processor to the container.

	    $container->add($fp) ;
	}

	return $container ;
    }

    function exportCSV($csvHeader, $csvData, $filter = null)
    {
	$csvStream = "" ;

	//  Add CSV Header

	if (is_array($csvHeader))
	{
	    foreach ($csvHeader as $header)
	        $csvStream .= sprintf("%s, ", $header) ;

	    //  Remove trailing comma and add newline
	    $csvStream = substr($csvStream, 0, strlen($csvStream) - 2) . "\n" ;
	}

	//  Add the data to the CSV stream
    
        foreach ($csvData as $csvDataRow)
        {
	    //  Filter records if directed

	    $keys = array_keys($csvDataRow) ;
	    $lastField = $csvDataRow[$keys[count($keys) - 1]] ;

	    if (is_null($filter) || in_array($lastField, $filter))
	    {
                foreach ($csvDataRow as $csvDataCell)
                    $csvStream .= sprintf("%s, ", trim($csvDataCell)) ;

	        $csvStream = substr($csvStream, 0, strlen($csvStream) - 2) . "\n" ;
	    }
        }

        header("Content-type: application/vnd.ms-excel") ;
        header("Content-disposition:  attachment; filename=CSVData." .  date("Y-m-d").".csv") ;
    
        print $csvStream ;

	exit() ;
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
class Form7Content extends StandardFormContent {

    //  Property to hold CSV data
    var $__csvData ;

    //  Property to hold CSV header
    var $__csvHeader ;

    //  Property to hold information about the url
    var $__urlInfoTable ;

    /**
     * This method returns the InfoTable widget.
     */
    function get_url_info_table() {
	return $this->__urlInfoTable ;
    }

    /**
     * This method creates an InfoTable widget which
     * is used to display information regarding the 
     * supplied url (remote file).
     */
    function set_url_info_table($url) {

	//  Clean up old session data

	if (session_is_registered(FORM7_SESSION_INFO))
	    session_unregister(FORM7_SESSION_INFO) ;

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
	    $it->add_row("Lines", count($lines)) ;
	    $it->add_row("Characters", $chars) ;

	    unset($lines) ;
	}
	else
	{
	    $it->add_row("URL", $url) ;
	    $it->add_row("Error", "Unable to open URL for reading.") ;
	}

	$this->__urlInfoTable = &$it ;
	$this->save_InfoTable_to_session() ;
    }

    /**
     * This method retrieves the InfoTable
     * from the session so it can be used
     * across multiple page views.
     */
    function load_InfoTable_from_session()
    {
        $this->__urlInfoTable = session_is_registered(FORM7_SESSION_INFO) ? $_SESSION[FORM7_SESSION_INFO] : null ;
    }

    /**
     * This method saves the InfoTable to
     * the session so it can be used across
     * multiple page views.
     */
    function save_InfoTable_to_session()
    {
	session_register(FORM7_SESSION_INFO) ;
	$_SESSION[FORM7_SESSION_INFO] = $this->__urlInfoTable ;
    }

    /**
     * This method returns the CSV data.
     */
    function get_CSV_data() {
	return $this->__csvData ;
    }

    /**
     * This method returns the CSV header.
     */
    function get_CSV_header() {
	return $this->__csvHeader ;
    }

    /**
     * This method reads the CSV data and stores it
     * in a property so it can be used later to seed
     * the the DataList widget.
     */
    function read_CSV_data($url, $header = true, $comment1 = true, $comment2 = true, $blank = true) {

	$this->__csvData = array() ;
	$this->__csvHeader = array() ;

	//  Clean up old session data

	if (session_is_registered(FORM7_SESSION_HEADER))
	    session_unregister(FORM7_SESSION_HEADER) ;

	if (session_is_registered(FORM7_SESSION_DATA))
	    session_unregister(FORM7_SESSION_DATA) ;

	//  Open the URL and read the lines from it.

	if ($fh = @fopen($url, "r"))
	{
	    $readHeader = !$header ;

	    while (!feof($fh))
	    {
		$line = trim(fgets($fh, 1048576)) ;

		//  Skip blank lines?
		if (empty($line) && $blank) continue ;

		//  Skip comment1 (#) lines?
		if ((strncmp('#', $line, 1) == 0) && $comment1) continue ;

		//  Skip comment1 (#) lines?
		if ((strncmp('//', $line, 2) == 0) && $comment2) continue ;

		//  Process the header is specified and not done yet

		$line = explode(",", $line) ;

		if ($readHeader)
		{
		    //  Should be as many fields as columns of data

		    $csv = array();
		    foreach($this->__csvHeader as $hdr => $name )
			$csv[$name] = $line[$hdr];

		    //  Add the csv data to the in-memory array.
		    $this->__csvData[] = $csv ;
		}
		else
		{
		    $readHeader = true ;

		    $this->__csvHeader = array() ;

		    foreach($line as $hdr )
		        $this->__csvHeader[] = $hdr ;
		}

	    }

            fclose ($fh) ;
	}

	$this->save_CSV_data_to_session() ;
	$this->save_CSV_header_to_session() ;
    }

    function load_CSV_data_from_session()
    {
        $this->__csvData = session_is_registered(FORM7_SESSION_DATA) ? $_SESSION[FORM7_SESSION_DATA] : null ;
    }

    function save_CSV_data_to_session()
    {
	session_register(FORM7_SESSION_DATA) ;
	$_SESSION[FORM7_SESSION_DATA] = $this->__csvData ;
    }

    function load_CSV_header_from_session()
    {
        $this->__csvHeader = session_is_registered(FORM7_SESSION_HEADER) ? $_SESSION[FORM7_SESSION_HEADER] : null ;
    }

    function save_CSV_header_to_session()
    {
	session_register(FORM7_SESSION_HEADER) ;
	$_SESSION[FORM7_SESSION_HEADER] = $this->__csvHeader ;
    }

    /**
     * This method gets called EVERY time the object is
     * created
     */
    function form_init_elements() {

        //  We want an confirmation page for this form

        $this->set_confirm(false);

	//  Use a 'dagger' character to denote required fields.

	$this->set_required_marker('&#134;');

        //  Now start to add the Form Elements that will be used in this form.

        //  Build the Upload File Widget.  It is a required field.
        //  It will automatically get validated as an Upload File.

	$url = new FEUrl("URL", TRUE, "400px") ;
	//$url->set_disabled(true) ;
	$url->set_colon_flag(true) ;

        $this->add_element($url) ;

	$this->add_element( new FECheckBox ("Header", "First Line Header") );
	$this->add_element( new FECheckBox ("Blank", "Skip Blank Lines") );
	$this->add_element( new FECheckBox ("Comment1", "Skip \"#\" Comment Lines") );
	$this->add_element( new FECheckBox ("Comment2", "Skip \"//\" Comment Lines") );
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

	//  Default the "Options" checkboxes to on.
	$this->set_element_value("Header", 1) ;
	$this->set_element_value("Comment1", 1) ;
	$this->set_element_value("Comment2", 1) ;
	$this->set_element_value("Blank", 1) ;
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

        $table->add_row(html_td(null, "right", $this->element_label("URL")), 
                        html_td(null, null, $this->element_form("URL")));

	$table->add_row(html_br()) ;

	$table->add_row(html_td(null, "right", "Options:"),
       	    html_td(null, null,
                $this->element_form("Header")
	       ,html_br()
               ,$this->element_form("Comment1")
	       ,html_br()
               ,$this->element_form("Comment2")
	       ,html_br()
               ,$this->element_form("Blank")
	    )
	) ;

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

	//  Retrive the options to control processing the file.
	$header = (bool)$this->get_element_value("Header") ;
	$comment1 = (bool)$this->get_element_value("Comment1") ;
	$comment2 = (bool)$this->get_element_value("Comment2") ;
	$blank = (bool)$this->get_element_value("Blank") ;

	$this->set_url_info_table($url) ;
	$this->read_CSV_data($url, $header, $comment1, $comment2, $blank) ;

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

/**
 * This class shows how to use the data coming
 * from a CSV Formatted file.  This is derived
 * from the class used in widget7.php.
 *
 */
class CSVGUIDataList extends DefaultGUIDataList {

    //  Property to store headers for data list.
    var $__headers ;

    //  Property to store the data source.
    var $__data_source ;

    /*
     * Retrieve the CSV headers from the
     * session variable storage.
     *
     */
    function do_action()
    {
        $csvHeader = session_is_registered(FORM7_SESSION_HEADER) ? $_SESSION[FORM7_SESSION_HEADER] : null ;
	$this->set_headers($csvHeader) ;
    }

    /*
     * Set the data list headers.
     *
     * This function accept either a single string
     * argument or an array of strings.
     */
    function set_headers($headers = null)
    {
        if (is_array($headers))
	{
	    $this->__headers = array() ;
	    foreach ($headers as $header)
	        $this->__headers["$header"] = $header ;
	}
	else if (!is_null($headers))
	{
	    $this->__headers = array() ;
	    $this->__headers[$headers] = $headers ;
	}
	else
	    $this->__headers = array() ;
    }

    /*
     * Set the source data array
     *
     */
    function set_data_source_array(&$sa)
    {
	$this->__data_source = $sa ;
    }

    /*
     * Get the source data array
     *
     */
    function get_data_source()
    {
	$ds = new ArrayDataListSource($this->__data_source) ;
	$this->set_data_source($ds) ;
    }

    function user_setup() {

	//  Add the headers to the GUIDataList - default sort column
	//  is the first header.

	foreach ($this->__headers as $header)
            $this->add_header_item($header, "200", $header, SORTABLE, SEARCHABLE, "left");

        //  turn on the 'collapsable' search block.
        //  The word 'Search' in the output will be clickable,
        //  and hide/show the search box.

        $this->_collapsable_search = TRUE;

        //  lets add an action column of checkboxes,
        //  and allow us to save the checked items between pages.
	//  Use the last field for the check box action.

	$keys = array_keys($this->__headers) ;
	$lastField = $this->__headers[$keys[count($keys) - 1]] ;
	$this->add_action_column('checkbox', 'FIRST', $lastField) ;

        //$this->add_action_column('checkbox', 'FIRST', 0);

        //  we have to be in POST mode, or we could run out
        //  of space in the http request with the saved
        //  checkbox items
        $this->set_form_method('POST');

        //  set the flag to save the checked items
        //  between pages.
        $this->save_checked_items(TRUE);
    }

    function actionbar_cell() {
	//  Add action buttons to export the CSV data
	//  and reset the application.

	$container = container() ;

        $exportCSV = $this->action_button('Export CSV', $_SERVER['PHP_SELF']) ;
        $exportCSV->set_tag_attribute("type", "submit") ;
	
        $reset = $this->action_button('Reset', $_SERVER['PHP_SELF']) ;
        $reset->set_tag_attribute("type", "submit") ;
	
	$container->add($exportCSV, "&nbsp;", $reset) ;

	return $container ;
    }
}

session_start() ;
$page = new Form7Page("Form Example 7") ;

print $page->render() ;
?>
