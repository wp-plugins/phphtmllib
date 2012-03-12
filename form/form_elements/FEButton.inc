<?php
/**
 * This file contains the FEButton, FESubmitButton classes
 *
 * $Id: FEButton.inc 1444 2005-05-12 01:24:05Z hemna $
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
 * This is the button FormElement which builds a 
 * input field of type="button". It has no validation method.
 * 
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEButton extends FEBoxElement {

    /**
     * Holds the button action
     *
     *
     */
    var $_action = NULL;

    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param string value - button text
     * @param string action - action to perform
     * @param int required - element width in pixels (px), percentage (%) or elements (em)
     * @param int required - element height in pixels (px), percentage (%) or elements (em)
     */
    function FEButton($label, $value, $action = NULL, $width = NULL, $height = NULL) {
        $this->FEBoxElement($label, false);

        $this->set_value($value);

        $this->_action = $action;
    }

    /**
     * This function return the javaScript code for
     * an onClick event
     *
     * @return string - javascript code
     */
    function onClick() {
        if ($this->_action != NULL) {
            return "javascript:" . str_replace("javascript:", "", $this->_action);
        }
        else {
            return NULL;
        }
    }

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    function get_element() {

        $attributes = $this->_build_element_attributes();
        $attributes["type"] = "button";

        $attributes["value"] = $this->get_value();

        $tag = new INPUTtag($attributes);

        return $tag;
    }

}

/**
 * This is the SubmitButton FormElement which builds a 
 * input field of type="submit". It has no validation method.
 * 
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FESubmitButton extends FEButton {

    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param string value - button text
     * @param int required - element width in pixels (px), percentage (%) or elements (em)
     * @param int required - element height in pixels (px), percentage (%) or elements (em)
     */
    function FESubmitButton($label, $value, $width = NULL, $height = NULL) {
        $this->FEButton($label, $value, 'submit()');
    }

    /**
     * This function return the javaScript code for
     * an onSubmit event
     *
     * @return string - javascript code
     */
    function onClick() {
        return $this->get_element_name() . ".disabled=true;";
    }

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    function get_element() {

        $attributes = $this->_build_element_attributes();
        $attributes["type"] = "submit";

        $attributes["value"] = $this->get_value();

        $tag = new INPUTtag($attributes);

        return $tag;
    }
}


/**
 * This builds a button that will do a JS popup
 * question, asking for yes/no.  if yes, it submits
 * the form.
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEConfirmActionButton extends FEButton {

    function FEConfirmActionButton($label, $value, $message = NULL, $width = NULL, $height = NULL) {
        $action = "if (confirm('".$message."')) {this.form.".FORM_ACTION.".value='".$value."'; submit();}";
        $this->FEButton($label, $value, $action, $width, $height);
    }
}
?>
