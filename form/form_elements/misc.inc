<?php
/**
 * This file contains the base FormElement class.
 *
 * $Id: misc.inc 1471 2005-07-29 00:51:45Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */
 
/**
 * This is the Hidden FormElement which builds a 
 * input field of type="hidden". It has no validation method.
 * 
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEHidden extends FormElement {

    function FEHidden($label, $value=NULL) {
        $this->FormElement($label);
        if ($value != NULL) {
            $this->set_value( $value );
        }        
    }

    function get_element() {
		$attributes = $this->_build_element_attributes();
        $attributes["type"] = "hidden";

        if (($value = $this->get_value()) !== NULL)
            $attributes["value"] = $value;

        return new INPUTtag($attributes);

        //return form_hidden($this->get_element_name(),
        //                   $this->get_value() );
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
        return $this->get_element();
    }
}

/**
 * This is a way of providing an Error to the FormProcessor.
 * It can be used at any time during FormContent to create
 * a specialized error field and message.
 * 
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEError extends FormElement {   

    /**
     * The constructor
     *
     * @param string the error label
     * @param string the error message
     */
    function FEError( $label, $message ) {
        $this->set_label_text($label);
        $this->set_error_message($message);
    }

}
?>
