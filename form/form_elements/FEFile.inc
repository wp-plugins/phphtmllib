<?php
/**
 * This file contains the FileUpload FormElement class.
 *
 * $Id: FEFile.inc 1562 2005-09-15 00:00:23Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Dave Brondsema <dave@brondsema.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This is the FileUpload FormElement which builds a
 * input field of type="file".  This automagically
 * handles the case of a confirmation page.
 *
 * @author Dave Brondsema <dave@brondsema.net>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEFile extends FEText {


    /**
     * The $_FILES information about
     * the submitted file.
     */
    var $_files_info = array('name' => '',
                             'type' => '',
                             'size' => '',
                             'tmp_name' => '');

    /**
     * The place where we temporarily save
     * the file during confirmation
     */
    var $_temp_dir = "/tmp";

    /**
     * Array listing mime types to check for 
     * during validation
     */
    var $_valid_types = array();

    /**
     * max size in bytes determined by user
     * 
     */
    var $_max_size;

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    function get_element() {
        $attributes = $this->_build_element_attributes();
        $attributes["type"] = "file";

        if (($value = $this->get_value()) != NULL)
            $attributes["value"] = $value;

        $tag = new INPUTtag($attributes);

        return $tag;
    }

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates file size and partial uploads..
     * @param FormValidation object.
     */
    function validate(&$_FormValidation) {
    	
    	if ((isset($_REQUEST[FORM_CONFIRM]) &&
            $_REQUEST[FORM_CONFIRM] == 1) &&
            $this->is_required()) {
    		//looks like we are in confirmation
    		//we should have a populated array already.
    		if ($this->_files_info['name']) {
    			//we are ok
    			return TRUE;    			
    		} else {
    			//something bogus happened here.
    			$this->set_error_message("The uploaded file was unexpectedly empty.");
                return FALSE;    			
    		}
    	}

        switch ($_FILES[$this->get_element_name()]['error']) {
        case 0:
            if ($_FILES[$this->get_element_name()]['size'] == 0 && 
                $this->is_required()) {
                $this->set_error_message("The uploaded file was empty.");
                return FALSE;
            }
            break;
        case 1:
            $this->set_error_message("The uploaded file exceeds the maximum file size, " . 
                                     ini_get("upload_max_filesize"));
            return FALSE;
            break;
        case 2:
            $this->set_error_message("The uploaded file exceeds the maximum file size, " . 
                                     $_REQUEST['MAX_FILE_SIZE'] . " bytes, specified for this form.");
            return FALSE;
            break;
        case 3:
            $this->set_error_message("The uploaded file was only partially uploaded.");
            return FALSE;
            break;
        case 4:
            //make sure that we are required to have a result
            if ($this->is_required()) {
                $this->set_error_message("No file was uploaded.");
                return FALSE;
            } else {
                //we aren't required,
                //and we don't have a value.
                //this is a special case of 
                //parent::do_validation
                return TRUE;
            }
            break;

        case 5:
            $this->set_error_message("The uploaded file was empty.");
            return FALSE;
            break;
        }

        if (!empty($this->_valid_types)) {
            if (!in_array($_FILES[$this->get_element_name()]['type'], $this->_valid_types)) {
                $this->set_error_message('Not a valid file type.');
                return FALSE;
            }
        }

        if (!empty($this->_max_size)) {
            if ($_FILES[$this->get_element_name()]['size'] > $this->_max_size) {
                $this->set_error_message('File can be no larger than ' . $this->_max_size . ' bytes');
                return FALSE;
            }
        }

        return TRUE;
    }

    /**
     * This function will return the
     * elements value
     *
     * @return mixed
     */
    function get_value() {
        //do we need to repopulate 
        //the file_info?
        if (isset($_REQUEST[FORM_CONFIRM])) {
            if (empty($this->_files_info['name'])) {
                $this->_populate_file_info();
            }
            
            //let the FormContent do what they want.
            return $this->_files_info;
        } else {
            if (isset($_FILES[$this->get_element_name()]['name'])) {
                return $_FILES[$this->get_element_name()]['name'];
            } else {
                return '';
            }
        }        
    }

    /**
     * 
     * @param mixed - the value to look up
     * @return string - the text associated
     */
    function get_value_text() {
        if (empty($this->_files_info['name'])) {
            return '';
        } else {
            return $this->_files_info['name']." (".
                $this->_files_info['type'].") ".
                $this->_files_info['size']." bytes";
        }        
    }

    /**
     * This is so we can save the file information
     * in a hidden form field during confirmation
     * page.
     * 
     * @return string
     */
    function get_pre_confirm_value() {
        return urlencode(serialize($this->_files_info));
    }



    /**
     * This function will return this file's portion of the $_FILES array
     *
     * @return array
     */
    function get_file_info() {
        return @$_FILES[$this->get_element_name()];
    }

    /**
     * This is so the user can set the temp directory
     * where the file will be saved during confirmation
     * (if any)
     * 
     * @param string the new temp dir.
     */
    function set_temp_dir($dir) {
        $this->_temp_dir = $dir;
    }

    /**
     * This is so the user can get the temp directory
     * where the file was saved during confirmation
     * (if any)
     * 
     * @return string the new temp dir.
     */
    function get_temp_dir() {
        return $this->_temp_dir;
    }


    /**
     * The function that allows us to save the 
     * temp file someplace we can use it after
     * a confirmation has been accepted.
     * 
     * NOTE: if the user doesn't confirm, then
     *       this could leave files in /tmp
     *
     */
    function _pre_confirm() {
        $name = $this->get_element_name();
        if (!empty($_FILES[$name]['name'])) {
            //ok we need to move the file so that the web
            //server doesn't nuke it once the request is done.
            $this->_files_info['name'] = $_FILES[$name]["name"];
            $this->_files_info['type'] = $_FILES[$name]['type'];
            $this->_files_info['size'] = $_FILES[$name]['size'];

            $tempname = tempnam($this->_temp_dir, get_class($this));
            $this->_files_info['tmp_name'] = str_replace($this->_temp_dir, '', $tempname);
            rename($_FILES[$name]['tmp_name'], $tempname);
        }

        return TRUE;
    }

    /**
     * This method re-populates the $this->_files_info
     * because the form had a confirmation page,
     * and the user accepted the confirmation.
     * 
     * This is so we can re populate the local private var
     * so we can get access at the file data on disk.
     * 
     */
    function _populate_file_info() {
        $this->_files_info = unserialize(urldecode($this->_value));
        $this->_value = $this->_files_info['name'];
        $this->_files_info['tmp_name'] = $this->_temp_dir.$this->_files_info['tmp_name'];
    }


    /**
     * This method returns the hidden version of this
     * element for a confirmation page.  
     * 
     * NOTE: This is called by the FormProcessor only.  
     * It shouldn't be called manually.
     * 
     * @return INPUTtag of type hidden
     */
    function get_confirm_element() {
        return form_hidden($this->get_element_name(), 
                           $this->get_pre_confirm_value());
    }

    /**
     * This is so the user can create a list of mime types
     * to allow
     * 
     * @param string a mime type to check for
     */
    function add_valid_type($mime_type) {
        $this->_valid_types[] = $mime_type;
    }

    /**
     * This allows the user to set the max size of the file
     * 
     * @param integer max size in bytes
     */
    function set_max_size($max_size) {
        $this->_max_size = $max_size;
    }

    /**
     * This allows the user to get the max size of the file
     * (if any has been set)
     * 
     * @return integer value of $_max_size if any
     */
    function get_max_size($max_size) {
        return $this->_max_size;
    }
}
?>
