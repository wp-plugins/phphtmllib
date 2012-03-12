<?php
/**
 * This file contains the Password FormElement class.
 *
 * $Id: FEPassword.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosyan <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This is the Password FormElement which builds a 
 * input field of type="password".  It validates
 * the data as is_password().
 *
 * NOTE: this is used in conjunction with the 
 *       FEConfirmPassword object to ensure the
 *       user's input is what they wanted.
 * 
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEPassword extends FEText {

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    function get_element() {
        $attributes = $this->_build_element_attributes();
        $attributes["type"] = "password";
        $attributes["value"] = '';
        return new INPUTtag($attributes);
    }


    /**
     * return a string to the user for the
     * confirmation page
     * 
     * @return string
     */
    function get_value_text() {
        return str_repeat('*', strlen($this->get_value()));
    }


    /**
     * This function performs the actual validation
     * It is called only if the validation is required by
     * this element
     *
     * This function is responsible for performing complete
     * validation and setting the appropriate error message
     * in case of a failed validation
     *
     * @param FormValidation object
     */
    function validate(&$_FormValidation) {
        if (!$_FormValidation->is_password($this->get_value())) {
            $this->set_error_message( $_FormValidation->get_error_message() );
            return FALSE;
        }
        return TRUE;
    }    
}

/**
 * This is the ConfirmPassword FormElement which builds a 
 * input field of type="password".  It requires the caller
 * to add a FEPassword object to this class to have something
 * to compare during validation time. 
 * It first validates that the value is_password(), and then
 * makes sure it matches exactly what the value is in
 * the FEPassword.
 *
 * USE: after u create the FEConfirmPassword, you MUST call
 * password() method which adds a reference to the FEPassword
 * object, so it can validate against.
 * 
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEConfirmPassword extends FEPassword {

    /**
     * This holds the FEPassword we are
     * trying to confirm
     */
    var $_fepassword = NULL;

    /**
     * use this function to add the
     * FEPassword object that we want
     * to confirm.
     *
     * @param FEPassword object
     */
    function password( &$fepassword ) {
        $this->_fepassword = &$fepassword;
    }


    /**
     * This function performs the actual validation
     * It is called only if the validation is required by
     * this element
     *
     * This function is responsible for performing complete
     * validation and setting the appropriate error message
     * in case of a failed validation
     *
     * @param FormValidation object
     */
    function validate(&$_FormValidation) {
        if (!$_FormValidation->is_password($this->get_value())) {
            $this->set_error_message( $_FormValidation->get_error_message() );
            return FALSE;
        }

        if ($this->_fepassword == NULL) {
            $this->set_error_message( "No Password to confirm.  ".
                                      "please use FEConfirmPassword::password() ".
                                      "to set the FEPassword you wish to ".
                                      "confirm");
            return FALSE;
        }

        //looks like we have an FEPassword to confirm against
        if (!$_FormValidation->is_confirm_password($this->get_value(),
                                                   $this->_fepassword->get_value())) {
            $this->set_error_message( $_FormValidation->get_error_message() );
            return FALSE;
        }

        return TRUE;
    }    
}
?>
