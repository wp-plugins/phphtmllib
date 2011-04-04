<?php
/**
 * This file contains the FEText, FEName, FEEmail,
 * FEDomainName classes
 *
 * $Id: FEText.inc 1463 2005-07-12 21:52:07Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markosyan <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This is the Text FormElement which builds a 
 * text input field. It has no validation method.
 * 
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEText extends FormElement {

    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param bool required - is this a required element
     * @param int required - element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int required - maximum number of chars allowed to type in
     */
    function FEText($label, $required = FALSE, $width = NULL, $maxlength = NULL) {
        $this->FormElement($label, $required);

        if ($width != NULL) {
            if (is_numeric($width))
                $this->set_attribute("size", $width);
            else
                $this->set_style_attribute("width", $width);
        }

        if ($maxlength != NULL)
            $this->set_attribute("maxlength", $maxlength);
    }


    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    function get_element() {

        $attributes = $this->_build_element_attributes();
        $attributes["type"] = "text";

        if (($value = $this->get_value()) != NULL)
            $attributes["value"] = $value;

        return new INPUTtag($attributes);
    }
}

/**
 * This is the Name FormElement which builds a 
 * text input field, and validates against the
 * is_name() method.
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEName extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_name().
     * @param FormValidation object.
     */
    function validate(&$_FormValidation) {
        if (!$_FormValidation->is_name($this->get_value())) {
            $this->set_error_message( $_FormValidation->get_error_message() );
            return FALSE;
        }
        return TRUE;
    }
}

/**
 * This is the Email FormElement which builds a 
 * text input field. 
 * It validatest he data as is_email()
 * 
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEEmail extends FEText {
    
    /** Holds the flag to indicate
      * whether we allow email in
      * the long name format like
      * Foo Bar <email@email.com>
      */
    var $_allow_name = true;    

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_email().
     * @param FormValidation object.
     */
    function validate($_FormValidation) {
        if (!$_FormValidation->is_email($this->get_value(), $this->_allow_name)) {
            $this->set_error_message( $_FormValidation->get_error_message() );
            return FALSE;
        }
        return TRUE;
    }

    /**
     * Sets the flag to indicate
     * whether we allow email in
     * the long name format like
     * Foo Bar <email@email.com>
     *
     * @param bool
     */
    function set_allow_name($flag) {
        $this->_allow_name = $flag;
    }    
}

/**
 * This is the EmailMany FormElement which builds a 
 * text input field.  This allows for multiple email
 * addresses in 1 text input field seperated by commas.
 *
 * It validatest he data as is_manyemails()
 * 
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEEmailMany extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_manyemails().
     * @param FormValidation object.
     */
    function validate(&$_FormValidation) {
        if (!$_FormValidation->is_manyemails($this->get_value())) {
            $this->set_error_message( $_FormValidation->get_error_message() );
            return FALSE;
        }
        return TRUE;
    }
}

/**
 * This is the DomainName FormElement which builds a 
 * text input field.
 * It validates as is_domainname().
 * 
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEDomainName extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_domainname().
     * @param FormValidation object.
     */
    function validate(&$_FormValidation) {
        if (!$_FormValidation->is_domainname($this->get_value())) {
            $this->set_error_message( $_FormValidation->get_error_message() );
            return FALSE;
        }
        return TRUE;
    }
}

/**
 * This is the DomainName FormElement which builds a 
 * text input field. It also includes a port #
 * It validates as is_domainname().
 * 
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEHostNameWithPort extends FEText {

    /**
     * flag to tell us to seperate the port 
     * value into it's own field
     */
    var $_seperate_port_flag = FALSE;

    /**
     * The constructor
     *
     * @param label string - text label for the element
     * @param bool required - is this a required element
     * @param int required - element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int required - maximum number of chars allowed to type in
     * @param bool optional - seperate the port value into it's own textarea field
     */
    function FEHostNameWithPort($label, $required = TRUE, $width = NULL, $maxlength = NULL,
                                  $seperate_port=FALSE) {
        $this->FEText($label, $required, $width, $maxlength);
        $this->_seperate_port_flag = $seperate_port;
    }

    /**
     * This function builds and returns the
     * form element object
     *
     * @return object
     */
    function get_element() {
        $host_attributes = $this->_build_element_attributes();
        $host_attributes["type"] = "text";

        $element_name = $this->get_element_name();                
        $host_value = $this->get_value();

        if ($this->_seperate_port_flag) {
            $host_attributes["name"] = $element_name."[0]";
            if ($host_value != NULL && !is_array($host_value)) {
                $host_value = explode(":", $host_value );
                $host_attributes["value"] = $host_value[0];
            } else if (is_array($host_value)) {
                $host_attributes["value"] = $host_value[0];
            }

            $port_attributes = $host_attributes;
            $port_attributes["name"] = $element_name."[1]";
            $port_attributes["size"] = 10;
            $port_attributes["maxlenght"] = 5;
            if (@array_key_exists("0", $host_value)) {
                $port_attributes["value"] = $host_value[1];
            }

            $port_label = html_span("formlabel", "Port");
            if ($this->has_error("Port")) {
                $port_label->set_tag_attribute("style","color:red;");
            }            

            return container( new INPUTtag($host_attributes),
                              $port_label,
                              new INPUTtag($port_attributes));
        } else {
            if ($host_value != NULL) {
                $host_attributes["value"] = $host_value;
            }
            return new INPUTtag($host_attributes);
        }
    }

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_domainname().
     * @param FormValidation object.
     */
    function validate(&$_FormValidation) {
        $value = $this->get_value();
        if (!is_array($value)) {
            $value = explode(":", $value);
        }
        
        $valid = $this->_validate_hostname($_FormValidation, $value[0]);

        //now validate the port
        if ($value[1] != NULL) {
            if (!$_FormValidation->is_number($value[1])) {
                if ($this->_seperate_port_flag) {
                    $this->set_error_message($_FormValidation->get_error_message(), "Port");
                } else {
                    $this->set_error_message( $_FormValidation->get_error_message() );
                }
                $value = FALSE;
            }

            //make sure the hostname isn't null
            if ($value[0] == NULL) {
                //we have an error here because
                //they entered a port w/o a hostname
                $_FormValidation->_error("", "This field cannot be empty, if the Port is filled out");
                $this->set_error_message($_FormValidation->get_error_message());
            }
        }
        return $valid;
    }


    /**
     * this validates the hostname field only
     * 
     * @return bool TRUE = valid
     */
    function _validate_hostname(&$_FormValidation, $value) {
        $valid = TRUE;
        //validate the hostname        
        if ($value != NULL && !$_FormValidation->is_hostname($value)) {
            $this->set_error_message( $_FormValidation->get_error_message() );
            $valid = FALSE;
        }

        return $valid;
    }
}

/**
 * This is the Ip Address FormElement which builds a 
 * text input field.
 * It validates as is_ip().
 * 
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEIPAddress extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_ip().
     * @param FormValidation object.
     */
    function validate(&$_FormValidation) {
        if (!$_FormValidation->is_ip($this->get_value())) {
            $this->set_error_message( $_FormValidation->get_error_message() );
            return FALSE;
        }
        return TRUE;
    }
}

/**
 * This is the Ip Address FormElement which builds a 
 * text input field.
 * It validates as is_ip().
 * 
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEIPAddressWithPort extends FEHostNameWithPort {

    /**
     * this validates the hostname field only
     * 
     * @return bool TRUE = valid
     */
    function _validate_hostname(&$_FormValidation, $value) {
        $valid = TRUE;
        //validate the hostname        
        if ($value != NULL && !$_FormValidation->is_ip($value)) {
            $this->set_error_message( $_FormValidation->get_error_message() );
            $valid = FALSE;
        }
        return $valid;
    }
}



/**
 * This is the URL FormElement which builds a 
 * text input field.
 * It validates as is_url().
 * 
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEUrl extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_url().
     * @param FormValidation object.
     */
    function validate(&$_FormValidation) {
        if (!$_FormValidation->is_url($this->get_value())) {
            $this->set_error_message( $_FormValidation->get_error_message() );
            return FALSE;
        }
        return TRUE;
    }
}

/**
 * This is the URLStrict FormElement which builds a 
 * text input field.
 * This is the same as FEUrl, but it requires the http://
 * It validates as is_strict_url().
 * 
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @author Suren Markossian <suren@bcsweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FEUrlStrict extends FEText {

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_strict_url().
     * @param FormValidation object.
     */
    function validate(&$_FormValidation) {
        if (!$_FormValidation->is_strict_url($this->get_value())) {
            $this->set_error_message( $_FormValidation->get_error_message() );
            return FALSE;
        }
        return TRUE;
    }
}

/**
 * This is the FEZipcode class.
 * 
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 */
class FEZipcode extends FEText {
    /**
     * The constructor
     * 
     * @param label string - text label for the element
     * @param bool required - is this a required element
     * @param int required - element width in characters, pixels (px), percentage (%) or elements (em)
     * @param int required - maximum number of chars allowed to type in
     */
    function FEZipcode($label, $required=false, $width = NULL, $maxlength = 5) {
        $this->FEText($label, $required, $width, $maxlength);
    }


    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_name().
     * @param FormValidation object.
     */
    function validate(&$_FormValidation) {
        if (!$_FormValidation->is_zip($this->get_value())) {
            $this->set_error_message( $_FormValidation->get_error_message() );
            return FALSE;
        }
        return TRUE;
    }
}

/**
 * This is the RegEx FormElement which builds a text input field, and validates
 * against the is_regex() method.
 *
 * Example as it would appear in FormContent::form_init_elements():
 * <code>
 *      $this->add_element( new FERegEx("FERegEx label", false, '200px', 3, '/^pattern to match$/', 'error message when pattern does not match') );
 * </code>
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */
class FERegEx extends FEText {

    var $_regex;
    var $_error_message;

    /**
     * The constructor
     * 
     * @param label string - text label for the element
     * @param required bool- is this a required element
     * @param width int - element width in characters, pixels (px), percentage (%) or elements (em)
     * @param maxlength int- maximum number of chars allowed to type in
     * @param regex string - a valid regular expression i.e. '/[a-z]+$/i'
     * @param error_message string - error message for failure to match the regex
     */
    function FERegEx($label, $required=false, $width = NULL, $maxlength = NULL, $regex, $error_message) {
        $this->FEText($label, $required, $width, $maxlength);
        $this->_regex = $regex;
        $this->_error_message = $error_message;
    }

    /**
     * This method validates the data
     * for this Form Element.
     *
     * It validates as is_regex().
     * @param FormValidation object.
     * @return boolean
     */
    function validate(&$_FormValidation) {
        if (!$_FormValidation->is_regex($this->_regex, $this->get_value())) {
            $this->set_error_message( $this->_error_message );
            return FALSE;
        }
        return TRUE;
    }
}



/**
 * This Form Element is used as a DHTML color picker.
 * 
 * I used some of the JS code from
 * @link http://www.mattkruse.com/javascript/colorpicker
 * 
 * 
 * @author Walter A. Boring IV
 */
class FEColorPicker extends FEText {



	/**
	 * The javascript required for the layer to work
	 * 
	 */
	function javascript() {

		$id = 'cp'.str_replace('_', '', strtolower($this->build_id_name()));

		$js = <<< EOF
function getAnchorPosition(anchorname){var useWindow=false;var coordinates=new Object();var x=0,y=0;var use_gebi=false, use_css=false, use_layers=false;if(document.getElementById){use_gebi=true;}else if(document.all){use_css=true;}else if(document.layers){use_layers=true;}if(use_gebi && document.all){x=AnchorPosition_getPageOffsetLeft(document.all[anchorname]);y=AnchorPosition_getPageOffsetTop(document.all[anchorname]);}else if(use_gebi){var o=document.getElementById(anchorname);x=AnchorPosition_getPageOffsetLeft(o);y=AnchorPosition_getPageOffsetTop(o);}else if(use_css){x=AnchorPosition_getPageOffsetLeft(document.all[anchorname]);y=AnchorPosition_getPageOffsetTop(document.all[anchorname]);}else if(use_layers){var found=0;for(var i=0;i<document.anchors.length;i++){if(document.anchors[i].name==anchorname){found=1;break;}}if(found==0){coordinates.x=0;coordinates.y=0;return coordinates;}x=document.anchors[i].x;y=document.anchors[i].y;}else{coordinates.x=0;coordinates.y=0;return coordinates;}coordinates.x=x;coordinates.y=y;return coordinates;}
function getAnchorWindowPosition(anchorname){var coordinates=getAnchorPosition(anchorname);var x=0;var y=0;if(document.getElementById){if(isNaN(window.screenX)){x=coordinates.x-document.body.scrollLeft+window.screenLeft;y=coordinates.y-document.body.scrollTop+window.screenTop;}else{x=coordinates.x+window.screenX+(window.outerWidth-window.innerWidth)-window.pageXOffset;y=coordinates.y+window.screenY+(window.outerHeight-24-window.innerHeight)-window.pageYOffset;}}else if(document.all){x=coordinates.x-document.body.scrollLeft+window.screenLeft;y=coordinates.y-document.body.scrollTop+window.screenTop;}else if(document.layers){x=coordinates.x+window.screenX+(window.outerWidth-window.innerWidth)-window.pageXOffset;y=coordinates.y+window.screenY+(window.outerHeight-24-window.innerHeight)-window.pageYOffset;}coordinates.x=x;coordinates.y=y;return coordinates;}
function AnchorPosition_getPageOffsetLeft(el){var ol=el.offsetLeft;while((el=el.offsetParent) != null){ol += el.offsetLeft;}return ol;}
function AnchorPosition_getWindowOffsetLeft(el){return AnchorPosition_getPageOffsetLeft(el)-document.body.scrollLeft;}
function AnchorPosition_getPageOffsetTop(el){var ot=el.offsetTop;while((el=el.offsetParent) != null){ot += el.offsetTop;}return ot;}
function AnchorPosition_getWindowOffsetTop(el){return AnchorPosition_getPageOffsetTop(el)-document.body.scrollTop;}

/* SOURCE FILE: PopupWindow.js */
function PopupWindow_getXYPosition(anchorname){var coordinates;if(this.type == "WINDOW"){coordinates = getAnchorWindowPosition(anchorname);}else{coordinates = getAnchorPosition(anchorname);}this.x = coordinates.x;this.y = coordinates.y;}
function PopupWindow_setSize(width,height){this.width = width;this.height = height;}
function PopupWindow_populate(contents){this.contents = contents;this.populated = false;}
function PopupWindow_setUrl(url){this.url = url;}
function PopupWindow_setWindowProperties(props){this.windowProperties = props;}
function PopupWindow_refresh(){if(this.divName != null){if(this.use_gebi){document.getElementById(this.divName).innerHTML = this.contents;}else if(this.use_css){document.all[this.divName].innerHTML = this.contents;}else if(this.use_layers){var d = document.layers[this.divName];d.document.open();d.document.writeln(this.contents);d.document.close();}}else{if(this.popupWindow != null && !this.popupWindow.closed){if(this.url!=""){this.popupWindow.location.href=this.url;}else{this.popupWindow.document.open();this.popupWindow.document.writeln(this.contents);this.popupWindow.document.close();}this.popupWindow.focus();}}}
function PopupWindow_showPopup(anchorname){this.getXYPosition(anchorname);this.x += this.offsetX;this.y += this.offsetY;if(!this.populated &&(this.contents != "")){this.populated = true;this.refresh();}if(this.divName != null){if(this.use_gebi){document.getElementById(this.divName).style.left = this.x + "px";document.getElementById(this.divName).style.top = this.y;document.getElementById(this.divName).style.visibility = "visible";}else if(this.use_css){document.all[this.divName].style.left = this.x;document.all[this.divName].style.top = this.y;document.all[this.divName].style.visibility = "visible";}else if(this.use_layers){document.layers[this.divName].left = this.x;document.layers[this.divName].top = this.y;document.layers[this.divName].visibility = "visible";}}else{if(this.popupWindow == null || this.popupWindow.closed){if(this.x<0){this.x=0;}if(this.y<0){this.y=0;}if(screen && screen.availHeight){if((this.y + this.height) > screen.availHeight){this.y = screen.availHeight - this.height;}}if(screen && screen.availWidth){if((this.x + this.width) > screen.availWidth){this.x = screen.availWidth - this.width;}}var avoidAboutBlank = window.opera ||( document.layers && !navigator.mimeTypes['*']) || navigator.vendor == 'KDE' ||( document.childNodes && !document.all && !navigator.taintEnabled);this.popupWindow = window.open(avoidAboutBlank?"":"about:blank","window_"+anchorname,this.windowProperties+",width="+this.width+",height="+this.height+",screenX="+this.x+",left="+this.x+",screenY="+this.y+",top="+this.y+"");}this.refresh();}}
function PopupWindow_hidePopup(){if(this.divName != null){if(this.use_gebi){document.getElementById(this.divName).style.visibility = "hidden";}else if(this.use_css){document.all[this.divName].style.visibility = "hidden";}else if(this.use_layers){document.layers[this.divName].visibility = "hidden";}}else{if(this.popupWindow && !this.popupWindow.closed){this.popupWindow.close();this.popupWindow = null;}}}
function PopupWindow_isClicked(e){if(this.divName != null){if(this.use_layers){var clickX = e.pageX;var clickY = e.pageY;var t = document.layers[this.divName];if((clickX > t.left) &&(clickX < t.left+t.clip.width) &&(clickY > t.top) &&(clickY < t.top+t.clip.height)){return true;}else{return false;}}else if(document.all){var t = window.event.srcElement;while(t.parentElement != null){if(t.id==this.divName){return true;}t = t.parentElement;}return false;}else if(this.use_gebi && e){var t = e.originalTarget;while(t.parentNode != null){if(t.id==this.divName){return true;}t = t.parentNode;}return false;}return false;}return false;}
function PopupWindow_hideIfNotClicked(e){if(this.autoHideEnabled && !this.isClicked(e)){this.hidePopup();}}
function PopupWindow_autoHide(){this.autoHideEnabled = true;}
function PopupWindow_hidePopupWindows(e){for(var i=0;i<popupWindowObjects.length;i++){if(popupWindowObjects[i] != null){var p = popupWindowObjects[i];p.hideIfNotClicked(e);}}}
function PopupWindow_attachListener(){if(document.layers){document.captureEvents(Event.MOUSEUP);}window.popupWindowOldEventListener = document.onmouseup;if(window.popupWindowOldEventListener != null){document.onmouseup = new Function("window.popupWindowOldEventListener();PopupWindow_hidePopupWindows();");}else{document.onmouseup = PopupWindow_hidePopupWindows;}}
function PopupWindow(){if(!window.popupWindowIndex){window.popupWindowIndex = 0;}if(!window.popupWindowObjects){window.popupWindowObjects = new Array();}if(!window.listenerAttached){window.listenerAttached = true;PopupWindow_attachListener();}this.index = popupWindowIndex++;popupWindowObjects[this.index] = this;this.divName = null;this.popupWindow = null;this.width=0;this.height=0;this.populated = false;this.visible = false;this.autoHideEnabled = false;this.contents = "";this.url="";this.windowProperties="toolbar=no,location=no,status=no,menubar=no,scrollbars=auto,resizable,alwaysRaised,dependent,titlebar=no";if(arguments.length>0){this.type="DIV";this.divName = arguments[0];}else{this.type="WINDOW";}this.use_gebi = false;this.use_css = false;this.use_layers = false;if(document.getElementById){this.use_gebi = true;}else if(document.all){this.use_css = true;}else if(document.layers){this.use_layers = true;}else{this.type = "WINDOW";}this.offsetX = 0;this.offsetY = 0;this.getXYPosition = PopupWindow_getXYPosition;this.populate = PopupWindow_populate;this.setUrl = PopupWindow_setUrl;this.setWindowProperties = PopupWindow_setWindowProperties;this.refresh = PopupWindow_refresh;this.showPopup = PopupWindow_showPopup;this.hidePopup = PopupWindow_hidePopup;this.setSize = PopupWindow_setSize;this.isClicked = PopupWindow_isClicked;this.autoHide = PopupWindow_autoHide;this.hideIfNotClicked = PopupWindow_hideIfNotClicked;}


ColorPicker_targetInput = null;
function ColorPicker_writeDiv(){document.writeln('<DIV ID=\"colorPickerDiv\" STYLE=\"position:absolute;visibility:hidden;\"> </DIV>');}
function ColorPicker_show(anchorname){this.showPopup(anchorname);}
function ColorPicker_pickColor(color,obj){obj.hidePopup();pickColor(color);}
function pickColor(color){if(ColorPicker_targetInput==null){alert("Target Input is null, which means you either didn't use the 'select' function or you have no defined your own 'pickColor' function to handle the picked color!");return;}ColorPicker_targetInput.value = color;}
function ColorPicker_select(inputobj,linkname){if(inputobj.type!="text" && inputobj.type!="hidden" && inputobj.type!="textarea"){alert("colorpicker.select: Input object passed is not a valid form input object");window.ColorPicker_targetInput=null;return;}window.ColorPicker_targetInput = inputobj;this.show(linkname);}
function ColorPicker_highlightColor(c){var thedoc =(arguments.length>1)?arguments[1]:window.document;var d = thedoc.getElementById("colorPickerSelectedColor");d.style.backgroundColor = c;d = thedoc.getElementById("colorPickerSelectedColorValue");d.innerHTML = c;}
function ColorPicker(){var windowMode = false;if(arguments.length==0){var divname = "colorPickerDiv";}else if(arguments[0] == "window"){var divname = '';windowMode = true;}else{var divname = arguments[0];}if(divname != ""){var cp = new PopupWindow(divname);}else{var cp = new PopupWindow();cp.setSize(225,250);}cp.currentValue = "#FFFFFF";cp.writeDiv = ColorPicker_writeDiv;cp.highlightColor = ColorPicker_highlightColor;cp.show = ColorPicker_show;cp.select = ColorPicker_select;var colors = new Array("#000000","#000033","#000066","#000099","#0000CC","#0000FF","#330000","#330033","#330066","#330099","#3300CC",

"#3300FF","#660000","#660033","#660066","#660099","#6600CC","#6600FF","#990000","#990033","#990066","#990099",
"#9900CC","#9900FF","#CC0000","#CC0033","#CC0066","#CC0099","#CC00CC","#CC00FF","#FF0000","#FF0033","#FF0066",
"#FF0099","#FF00CC","#FF00FF","#003300","#003333","#003366","#003399","#0033CC","#0033FF","#333300","#333333",
"#333366","#333399","#3333CC","#3333FF","#663300","#663333","#663366","#663399","#6633CC","#6633FF","#993300",
"#993333","#993366","#993399","#9933CC","#9933FF","#CC3300","#CC3333","#CC3366","#CC3399","#CC33CC","#CC33FF",
"#FF3300","#FF3333","#FF3366","#FF3399","#FF33CC","#FF33FF","#006600","#006633","#006666","#006699","#0066CC",
"#0066FF","#336600","#336633","#336666","#336699","#3366CC","#3366FF","#666600","#666633","#666666","#666699",
"#6666CC","#6666FF","#996600","#996633","#996666","#996699","#9966CC","#9966FF","#CC6600","#CC6633","#CC6666",
"#CC6699","#CC66CC","#CC66FF","#FF6600","#FF6633","#FF6666","#FF6699","#FF66CC","#FF66FF","#009900","#009933",
"#009966","#009999","#0099CC","#0099FF","#339900","#339933","#339966","#339999","#3399CC","#3399FF","#669900",
"#669933","#669966","#669999","#6699CC","#6699FF","#999900","#999933","#999966","#999999","#9999CC","#9999FF",
"#CC9900","#CC9933","#CC9966","#CC9999","#CC99CC","#CC99FF","#FF9900","#FF9933","#FF9966","#FF9999","#FF99CC",
"#FF99FF","#00CC00","#00CC33","#00CC66","#00CC99","#00CCCC","#00CCFF","#33CC00","#33CC33","#33CC66","#33CC99",
"#33CCCC","#33CCFF","#66CC00","#66CC33","#66CC66","#66CC99","#66CCCC","#66CCFF","#99CC00","#99CC33","#99CC66",
"#99CC99","#99CCCC","#99CCFF","#CCCC00","#CCCC33","#CCCC66","#CCCC99","#CCCCCC","#CCCCFF","#FFCC00","#FFCC33",
"#FFCC66","#FFCC99","#FFCCCC","#FFCCFF","#00FF00","#00FF33","#00FF66","#00FF99","#00FFCC","#00FFFF","#33FF00",
"#33FF33","#33FF66","#33FF99","#33FFCC","#33FFFF","#66FF00","#66FF33","#66FF66","#66FF99","#66FFCC","#66FFFF",
"#99FF00","#99FF33","#99FF66","#99FF99","#99FFCC","#99FFFF","#CCFF00","#CCFF33","#CCFF66","#CCFF99","#CCFFCC",
"#CCFFFF","#FFFF00","#FFFF33","#FFFF66","#FFFF99","#FFFFCC","#FFFFFF");
var total = colors.length;var width = 18;var cp_contents = "";var windowRef =(windowMode)?"window.opener.":"";if(windowMode){cp_contents += "<HTML><HEAD><TITLE>Select Color</TITLE></HEAD>";cp_contents += "<BODY MARGINWIDTH=0 MARGINHEIGHT=0 LEFTMARGIN=0 TOPMARGIN=0><CENTER>";}cp_contents += "<table border=\"0\" cellspacing=\"0\" cellpadding=\"0\">";var use_highlight =(document.getElementById || document.all)?true:false;for(var i=0;i<total;i++){if((i % width) == 0){cp_contents += "<tr>";}if(use_highlight){var mo = 'onMouseOver="'+windowRef+'ColorPicker_highlightColor(\''+colors[i]+'\',window.document)"';}else{mo = "";}cp_contents += '<TD BGCOLOR="'+colors[i]+'"><FONT SIZE="-3"><A HREF="#" onClick="'+windowRef+'ColorPicker_pickColor(\''+colors[i]+'\','+windowRef+'window.popupWindowObjects['+cp.index+']);return false;" '+mo+' STYLE="text-decoration:none;">&nbsp;&nbsp;&nbsp;</A></FONT></TD>';if( ((i+1)>=total) ||(((i+1) % width) == 0)){cp_contents += "</tr>";}}if(document.getElementById){var width1 = Math.floor(width/2);var width2 = width = width1;cp_contents += "<TR><TD style=\"border:1px outset black;\" COLSPAN='"+width1+"' BGCOLOR='#ffffff' ID='colorPickerSelectedColor'>&nbsp;</TD><TD style=\"border-top:1px outset black;border-right:1px outset black; border-bottom:1px outset black;background-color:#FFFFFF;color:#000000;\" COLSPAN='"+width2+"' ALIGN='CENTER' ID='colorPickerSelectedColorValue'>#FFFFFF</TD></TR>";}cp_contents += "</TABLE>";if(windowMode){cp_contents += "</CENTER></BODY></HTML>";}cp.populate(cp_contents+"\\n");cp.offsetY = 25;cp.autoHide();return cp;}
var $id = new ColorPicker(); // DIV style
$id.writeDiv();

EOF;

		return $js;
	}


	/**
	 * This method validates to make sure it
	 * has a valid 6digit hex color
	 * 
	 * @param FormValidation object
	 * @return boolean
	 */
	function validate(&$_FormValidation) {
		$ret = TRUE;
		$value = $this->get_value();
        if (substr($value,0,1) != '#' || strlen($value) < 7) {
			$this->set_error_message('Color values must start with a #, then 6 hexedecimal digits. ex. #FF00FF');
			return FALSE;
		}

		if (!$_FormValidation->is_alphanum($value, '#')) {
			$this->set_error_message( $_FormValidation->get_error_message() );
			$ret = FALSE;
		}

		return $ret;
	}


	function get_element() {
		$input = parent::get_element();

		$id = $this->build_id_name();
		$id2 = $this->build_id_name(1);

		$obj_name = 'cp'.str_replace('_', '', strtolower($this->build_id_name()));

		//now build the picker link
		$link = new Atag(array('href' => '#',
							   'onclick' => "d=document.getElementById('".$id."');".$obj_name.".select(d,'".$id2."');return false;",
							   'name' => $id2, 'id' => $id2),
						 'Pick Color');			

		$c = container($input, $link);
		return $c;
	}
}
?>
