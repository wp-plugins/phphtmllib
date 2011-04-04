<?php

/**
 * This file contains the Form Element child classes
 * that deal primarily with numbers.
 *
 * $Id: FENumbers.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markosyan <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

require_once(PHPHTMLLIB_ABSPATH . "/form/form_elements/FEText.inc");

/**
 * This is the FormElement which builds a
 * text input field that validates
 * It validates as is_number().
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FENumber extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_number().
     * @param FormValidation object.
     */
    function validate(&$_FormValidation) {
        if (!$_FormValidation->is_number($this->get_value())) {
            $this->set_error_message( $_FormValidation->get_error_message() );
            return FALSE;
        }
        return TRUE;
    }
}

/**
 * This is the float FormElement which builds a
 * text input field.
 * It validates as is_float().
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FENumberFloat extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_float().
     * @param FormValidation object.
     */
    function validate(&$_FormValidation) {
        if (!$_FormValidation->is_float($this->get_value())) {
            $this->set_error_message( $_FormValidation->get_error_message() );
            return FALSE;
        }
        return TRUE;
    }
}

/**
 * This is the Price FormElement which builds a
 * text input field.
 * It validates as is_price().
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FENumberPrice extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_price().
     * @param FormValidation object.
     */
    function validate(&$_FormValidation) {
        if (!$_FormValidation->is_price($this->get_value())) {
            $this->set_error_message( $_FormValidation->get_error_message() );
            return FALSE;
        }
        return TRUE;
    }
}

/**
 * This is the Number Range FormElement which builds a
 * text input field.
 * It validates as is_within_rage().
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FENumberInRange extends FEText {

    /**
     * The minimum #
     */
    var $_min = 0;
    /**
     * The maximum #
     */
    var $_max = 100;

    /**
     * Add the range to the label automatically?
     */
    var $_label_flag = TRUE;

    /**
     * The 'Range' text
     */
    var $_range_text = "Range";

    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param bool required - is this a required element
     * @param int required - element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int maximum number of chars allowed to type in the field
     * @param int the minimum value allowable
     * @param int the maximum value allowable
     * @param boolean - add the range to the label automatically?
     *
     */
    function FENumberInRange($label, $required = TRUE, $width = NULL,
                           $maxlength = NULL, $min=0, $max=100, $label_flag=TRUE) {
        $this->FEText($label, $required, $width, $maxlength);
        $this->_min = $min;
        $this->_max = $max;
        $this->_label_flag = $label_flag;
    }

    /**
     * This function builds and returns a
     * label object based on the label text
     * and error conditions
     *
     * @param FormContent object that holds the
     *        required field marker
     * @param string this string allows us to use this
     *        method and wrap any string as a FormElement
     *        label.
     * @return object SPANtag
     */
    function get_label($form_content=NULL, $label='', $indent_flag=TRUE) {

        $label = $this->get_label_text();

        if ($this->_label_flag) {
            $label .= " ".$this->get_range_string();
        }

        if ($this->_label_colon_flag) {
            $label .= ':';        	
        }

        if ($this->is_required()) {
            $text = ($form_content ? $form_content->_required_field_marker :
                     $this->get_required_symbol()). ' '.$label;
        } else {
            if ($indent_flag) {
                $text = '&nbsp;&nbsp;'.$label;            	
            } else {
                $text = $label;
            }
        }

        $span = html_span("formlabel", $text);

        if ($this->has_error()) {
            $span->set_tag_attribute("style","color:red;");
        }

        return $span;
    }



    /**
     * This function builds a string for the range display
     *
     * @return string
     */
    function get_range_string($include_range=TRUE) {
        if ($include_range) {
            $str = $this->_range_text.": ";
        } else {
            $str = '';
        }

        return "(".$str.$this->_min."-".$this->_max.")";
    }

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_price().
     * @param FormValidation object.
     */
    function validate(&$_FormValidation) {
        if (!$_FormValidation->is_range($this->get_value(), NULL, $this->_min, $this->_max)) {
            $this->set_error_message( $_FormValidation->get_error_message() );
            return FALSE;
        }
        return TRUE;
    }
}

?>
