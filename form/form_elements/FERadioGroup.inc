<?php
/**
 * This file contains the Text FormElement class.
 *
 * $Id: FERadioGroup.inc 3251 2009-07-18 12:56:01Z mpwalsh8 $
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
 * This is the Radio Button Group FormElement which builds a
 * List of Radio buttons that can be used in any
 * style of layout.
 *
 * It has no validation method.
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FERadioGroup extends FormElement {

    /**
     * Holds the list of available
     * data elements
     *
     */
    var $_data_list = array();

    /**
     * the br flag
     */
    var $_br_flag=FALSE;

    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param array - the name => value pairs of the radio
     *                buttons text => value
     * @param boolean - required flag
     */
    function FERadioGroup($label, $data_list=array(), $required=true) {
        $this->FormElement($label, $required);
        foreach ($data_list as $name=>$value) {
            $this->_data_list[] = array($name=>$value);
        }
    }

    /**
     * This provides a method
     * for the FormContent
     * to get access to the
     * text associated with a
     * field.  This is only available
     * on FormElements that have text
     * associated with a field.
     * It is used during Confirmation
     *
     * @param mixed - the value to look up
     * @return string - the text associated
     */
    function get_value_text() {
        $value = $this->get_value();
        foreach( $this->_data_list as $arr) {
            $flip = array_flip($arr);
            if (isset($flip[$value])) {
                return $flip[$value];
            }
        }
        return NULL;
    }


    /**
     * This function is used to set the br flag
     * that will automatically add a BR tag after
     * each radio button
     *
     * @param boolean
     */
    function set_br_flag($flag=TRUE) {
        $this->_br_flag = $flag;
    }


    /**
     * This function builds and returns the
     * form element object
     *
     * @param int the index to get
     * @param boolean the br flag.
     *        NOTE: the class's br flag takes precedence.
     * @return object
     */
    function get_element($index=NULL, $br_flag=FALSE) {
        $container = container();

        if ($br_flag != $this->_br_flag) {
            $br_flag = $this->_br_flag;
        }

        if ($index === NULL) {
            $count = count( $this->_data_list );
            for ($x=0;$x<=$count-1;$x++) {
                if ($br_flag) {
                    $container->add( $this->_get_index_element($x),
                                     html_br());
                } else {
                    $container->add( $this->_get_index_element($x));
                }

            }
        } else {
            $container->add( $this->_get_index_element($index));
        }

        return $container;
    }


    /**
     * This method builds an individual Radio button
     * with its associated text
     *
     * @param int - the index
     * @return INPUTtag of type radio
     */
    function _get_index_element($index) {
        $attributes = $this->_build_element_attributes();
        $attributes["type"] = "radio";

        list($name, $value) = each($this->_data_list[$index]);
        $attributes["value"] = $value;

        $id_name = $this->get_element_name().'_'.$index;
        $attributes['id'] = $id_name;

        $attr_onclick = isset($attributes["onclick"])?$attributes["onclick"]:"";

        if (($value == $this->get_value()))
            $attributes[] = "checked";

        $tag = new INPUTtag($attributes);

        //now build the href so we can click on it.
        $attr["class"] ="form_link";
        $attr["href"] = "javascript:void(0)";

        $js = "e=document.getElementById('".$id_name."'); e.click();";
        $attr["onclick"] = $js.$attr_onclick;

        $href = new Atag($attr, $name);

        $c = container($tag, $href);
        $c->set_collapse();
        return $c;
    }
}



/**
 * This is the Yes/No Radio Button Group FormElement.
 * It builds a FERadioGroup with 2 radio buttons labeled
 * "Yes" and "No".
 *
 * It has no validation method.
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEYesNoRadioGroup extends FERadioGroup {

    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param bool required - is this a required element
     * @param string - the value to use for the 'yes' radio
     *                 NOTE: default is 'yes'
     * @param string - the value to use for the 'no' radio
     *                 NOTE: default is 'no'
     */
    function FEYesNoRadioGroup($label, $required = TRUE,
                               $yes_value="yes", $no_value="no") {
        $this->FormElement($label, $required);
        $this->_data_list[] = array("Yes" => $yes_value);
        $this->_data_list[] = array("No" => $no_value);
    }
}


/**
 * This is a special FERadioButtonGroup form element
 * that allows each of the radio buttons to show/hide
 * a div on the fly.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEActiveDIVRadioButtonGroup extends FERadioGroup {


    function javascript() {
        $name = $this->get_element_name();

        $js  = 'function '.$this->_form_name.'_'.$name."_activate(id) {\n";
        $js .= "   var e,o;\n";
        $js .= "    e = document.getElementById(id);\n";

        foreach ($this->_data_list as $button) {
            list($name, $value) = each( $button );
            $js .= "    o = document.getElementById('".$this->_id_name($name)."');\n";
            $js .= "    o.style.visibility = 'hidden';\n";
            $js .= "    o.style.display = 'none';\n";
        }

        $js .= "    e.style.visibility = 'visible';\n";
        $js .= "    e.style.display = 'block';\n}\n\n";

        return $js;
    }


    /**
     * This method builds an individual Radio button
     * with its associated text
     *
     * @param int - the index
     * @return INPUTtag of type radio
     */
    function _get_index_element($index) {
        $element_name = $this->get_element_name();

        $attributes = $this->_build_element_attributes();
        $attributes["type"] = "radio";

	reset($this->_data_list[$index]) ;
        list($name, $value) = each($this->_data_list[$index]);
        $attributes["value"] = $value;

        $id_name = $this->get_element_name().'_'.$index;
        $attributes['id'] = $id_name;

        $attributes['onclick'] = 'javascript:'.$this->_form_name.'_'.$element_name.
                                 "_activate('".$this->_id_name($name)."');";

        if (($value == $this->get_value()))
            $attributes['checked'] = "checked";

        $tag = new INPUTtag($attributes);

        //now build the href so we can click on it.
        $attr["class"] ="form_link";
        $attr["href"] = "javascript:void(0)";
        $js = "javascript: function check(item){item.click();} ".
              "check(".$element_name.".item($index));";

        $js = "e=document.getElementById('".$id_name."'); e.click();";
        $attr["onclick"] = $js;

        $href = new Atag($attr, $name);

        $c = container($tag, $href);
        $c->set_collapse();
        return $c;
    }


    /**
     * This builds the magic div
     *
     * @param int the index
     * @return DIVtag object
     */
    function build_div($index) {
        //which one is selected?

        reset($this->_data_list[$index]);
        list($name, $value) = each($this->_data_list[$index]);

        if ($value == $this->get_value()) {
            //ok this item is selected!
            //it needs to be visible first.
            $style = 'position:relative; visibility:visible; display:block;';
        } else {
            $style = 'visibility:hidden; display:none;';
        }

        return new DIVtag(array('id' => $this->_id_name($name),
                                'style' => $style));
    }

    function _id_name($name) {
        return $this->_form_name.'_'.$this->get_element_name().
               '_'.$this->_sanitize_string($name);
    }

}
?>
