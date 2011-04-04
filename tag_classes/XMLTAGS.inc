<?php

/**
 * This file contains all of the default
 * support xml tags by phpHtmlLib.
 *
 * $Id: XMLTAGS.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */


/**
 * xml tag class
 * @package phpHtmlLib
 */
class XMLtag extends XMLTagClass {
    var $_tag = "xml";
    var $_tag_prefix = "<?";
    var $_tag_postfix = " ?>";

    function XMLtag( $attributes=array() ) {
		$this->XMLTagClass( $this->get_tag_name(),
							$attributes);

		$num_args = func_num_args();
        for ($i=1;$i<$num_args;$i++) {
            $this->add(func_get_arg($i));
        }
        $this->_set_flags();
    }
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
        $this->_flags |= _ALWAYS_LOWERCASE | _NOFINISHSLASHXHTML;
    }
} // XMLtag

/**
 * xml-stylesheet tag class
 * @package phpHtmlLib
 */
class XMLSTYLESHEETtag extends XMLtag {
    var $_tag = "xml-stylesheet";
} // XMLSTYLESHEETtag


/**
 * A simple wrapper for standard XML
 * CDATA section data
 * @package phpHtmlLib
 */
class CDATAtag extends XMLtag {
    var $_tag = "CDATA[";
    var $_tag_prefix = "<![";
    var $_tag_postfix = "]]>";

	function CDATAtag() {
		$this->XMLTagClass($this->get_tag_name());

		$num_args = func_num_args();
        for ($i=0;$i<$num_args;$i++) {
            $this->add(func_get_arg($i));
		}
        $this->_set_flags();
	}

    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~_CLOSETAGREQUIRED;
        $this->_flags |= _NOFINISHSLASHXHTML;
    }


	function _render_open_tag( $indent_level, $finish_slash=FALSE ) {
		//get the indent level
		$indent = $this->_render_indent( $indent_level );

		$xml = $indent . $this->_tag_prefix . $this->_tag;

		if ($this->_flags & _NEWLINEAFTEROPENTAG) {
			$xml .= "\n";
		}
		return $xml;
	}

	function _render_close_tag($indent_level) {
		$indent = "";
		if (($this->_flags & _INDENT) && ($this->_flags & _NEWLINEAFTEROPENTAG)) {
			$indent = $this->_render_indent($indent_level);
		}		
		$str = $indent .$this->_tag_postfix;
		
		if ($this->_flags & _NEWLINEAFTERCLOSETAG) {
			$str .= "\n";
		}
		return $str;
	}
}

?>
