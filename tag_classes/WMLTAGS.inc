<?php
/**
 * This file contains all of the default
 * support wml tags by phpHtmlLib.
 *
 * This file only defines the WML tags that are
 * not part of the HTML/XHTML tag sets.  There are
 * several 'WML' tags that are identical to HTML tags
 * such as <a>, <head>, <select>, etc etc.
 *
 * $Id: WMLTAGS.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */

/**
 * Base class for all WML Tag classes.
 * WML tags are just XML tags. Since we
 * have a defined set of WML tags, we have
 * no need for the XMLTagClass' constructor
 * param for name.  This class also provides
 * nice methods for setting the class attribute
 * and the id attribute.
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @link http://phphtmllib.newsblob.com 
 * @link http://www.wapforum.org/what/technical.htm
 */
class WMLTagClass extends XMLTagClass {

	function WMLTagClass( $attributes=array() ) {
		$this->set_tag_attributes( $attributes );
        $num_args = func_num_args();
        for ($i=1;$i<$num_args;$i++) {
            $this->add(func_get_arg($i));
        }
        $this->_set_flags();
	}

    /**
     * This function is a shorthand helper
     * to setting the class attribute on a
     * tag.
     *
     * @param string - the class value.
     */
    function set_class( $value ) {
        $this->set_tag_attribute("class", $value);
    }

    /**
     * This function is a shorthand helper
     * to setting the id attribute on a
     * tag.
     *
     * @param string - the class value.
     */
    function set_id( $value ) {
        $this->set_tag_attribute("id", $value);
    }
}


/**
 * <ACCESS> tag class
 * @package phpHtmlLib
 */
class ACCESStag extends WMLTagClass {
    var $_tag = "access";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }
} // ACCESStag

/**
 * <ANCHOR> tag class
 * @package phpHtmlLib
 *
 */
class ANCHORtag extends WMLTagClass {
    var $_tag = "anchor";
} // ANCHORtag


/**
 * <CARD> tag class
 * @package phpHtmlLib
 */
class CARDtag extends WMLTagClass {
    var $_tag = "card";
} // CARDtag


/**
 * <DO> tag class
 * @package phpHtmlLib
 */
class DOtag extends WMLTagClass {
    var $_tag = "do";
} // DOtag


/**
 * <GO> tag class
 * @package phpHtmlLib
 */
class GOtag extends WMLTagClass {
    var $_tag = "go";

	/**
	 * we override this method
	 * to automatically check to 
	 * see if the tag has content.
	 * if it doesn't then we
	 * don't need to render the
	 * close tag.
	 */
	function _prepare_flags() {
		if ($this->count_content() == 0) {
			$this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
		}
	}

} // GOtag


/**
 * <NOOP> tag class
 * @package phpHtmlLib
 */
class NOOPtag extends WMLTagClass {
    var $_tag = "noop";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }
} // NOOPtag

/**
 * <ONEVENT> tag class
 * @package phpHtmlLib
 */
class ONEVENTtag extends WMLTagClass {
    var $_tag = "onevent";
} // ONEVENTtag

/**
 * <POSTFIELD> tag class
 * @package phpHtmlLib
 */
class POSTFIELDtag extends WMLTagClass {
    var $_tag = "postfield";
} // POSTFIELDtag

/**
 * <PREV> tag class
 * @package phpHtmlLib
 */
class PREVtag extends GOtag {
    var $_tag = "prev";
} // PREVtag

/**
 * <REFRESH> tag class
 * @package phpHtmlLib
 */
class REFRESHtag extends WMLTagClass {
    var $_tag = "refresh";
} // REFRESHtag

/**
 * <SETVAR> tag class
 * @package phpHtmlLib
 */
class SETVARtag extends WMLTagClass {
    var $_tag = "setvar";
} // SETVARtag



/**
 * <TEMPLATE> tag class
 * @package phpHtmlLib
 */
class TEMPLATEtag extends WMLTagClass {
    var $_tag = "template";
} // TEMPLATEtag

/**
 * <TIMER> tag class
 * @package phpHtmlLib
 */
class TIMERtag extends WMLTagClass {
    var $_tag = "timer";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }
} // TIMERtag


/**
 * <WML> tag class
 * The root tag for all
 * WML documents
 * @package phpHtmlLib
 */
class WMLtag extends WMLTagClass {
    var $_tag = "wml";
} // WMLtag

?>
