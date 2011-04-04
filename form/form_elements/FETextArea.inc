<?php
/**
 * This file contains the Text FormElement class.
 *
 * $Id: FETextArea.inc 1444 2005-05-12 01:24:05Z hemna $
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
 * This is the TextArea FormElement which builds a 
 * textarea field. It has no validation method.
 * 
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FETextArea extends FEBoxElement {


    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param bool required - is this a required element
     * @param int required - the rows attribute
     * @param int required - the cols attribute
     * @param int optional - element width in pixels (px), percentage (%) or elements (em)
     * @param int optional - element height in pixels (px), percentage (%) or elements (em)     
     * @param int optional - the number of characters to limit the value to.
     */
    function FETextArea($label, $required = TRUE, $rows, $cols, $width = NULL, $height = NULL,
                        $limit_char_count=-1 ) {        
        $this->_limit_char_count = $limit_char_count;
        $this->FEBoxElement($label, $required, $width, $height);
        $this->set_rows( $rows );
        $this->set_cols( $cols );
    }


    /**
     * This lets you limit the amount of data to 
     * accept in the field
     */
    var $_limit_char_count = -1;

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    function get_element() {

        $attributes = $this->_build_element_attributes();

        $tag = new TEXTAREAtag($attributes);

        if (($value = $this->get_value()) != NULL)
            $tag->add($value);

        return $tag;
    }


    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_name().
     * @param FormValidation object.
     */
    function validate(&$_FormValidation) {
        if ($this->_limit_char_count > 0) {
            $length = strlen($this->get_value());
            if ($length > $this->_limit_char_count) {
                $_FormValidation->_error("INVALID_LENGTH_N");
                $this->set_error_message( str_replace(array("XX_MAX", "XX_LENGTH"),
                                                      array($this->_limit_char_count, $length),
                                                      $_FormValidation->get_error_message() ));
                return FALSE;
            }
        }
        return TRUE;
    }


    /**
     * This method is used as a shortcut
     * to set the rows attribute
     *
     * @param int the rows attribute value
     */
    function set_rows( $rows ) {
        $this->set_attribute("rows", $rows);
    }

    /**
     * This method is used as a shortcut
     * to set the cols attribute
     *
     * @param int the cols attribute value
     */
    function set_cols( $cols ) {
        $this->set_attribute("cols", $cols);
    }

}
?>
