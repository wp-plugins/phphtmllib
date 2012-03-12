<?php

/**
 * Holds the XMLTagClass
 *
 * $Id: XMLTagClass.inc 3556 2012-03-11 11:26:12Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * make sure we include the parent class
 */
require_once(PHPHTMLLIB_ABSPATH . "/ContainerClass.inc" );


/**
 *
 * This class is used for building and rendering
 * an XML tag.
 *
 * This class is the base class for the
 * HTMLTagClass.
 *
 * This is part of the phphtmllib libraries
 * released under the LGPL license.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class XMLTagClass extends Container {


    /**
     * Tag definition for class.
     * subclass defines this value.
     * ie var $tag = "<TABLE>";
     * @var  string
     * @access   private
     */
    var $_tag = "";

    /**
     * Tag attributes as an array
     * of name value pairs.
     * ie $attributes["cellspacing"]=2;
     * @var  array
     * @access   private
     */
    var $_attributes = array();


	/**
	 * The constructor
     *
     * {@source }
     *
     * @tutorial XMLTagClass.cls#example
	 *
	 * @param string - the tag name
	 * @param array - the attributes array
	 *                can be in name => value
	 *                or just value
	 * @param mixed - n items of content to add
	 *
	 */
	function XMLTagClass($name, $attributes=array() ) {
		$this->set_tag_name( $name );
		$this->set_tag_attributes( $attributes );

        $num_args = func_num_args();
        for ($i=2;$i<$num_args;$i++) {
            $this->add(func_get_arg($i));
        }

        $this->_set_flags();
	}


	/**
	 * This function is responsible
	 * for rendering the tag and
	 * its contents
     	 *
     	 * {@source }
	 *
	 * @param int - the current indentation
	 *              level for the tag
	 */
	function render( $indent_level=0, $output_debug=0 ) {
		
		//try and guess the indentation flags
		//based on the data
		$this->_prepare_flags();

		//return $xml;
        return $this->_render_open_tag( $indent_level ) .
               $this->_render_content( $indent_level ) .
               $this->_render_close_tag( $indent_level );
	}


	/****************************************/
	/* Some helper routines for building	*/
	/* pieces of the xml tag, its     	  	*/
	/* attributes and PCDATA				*/
	/****************************************/

    /**
     * This method is used to set the bitmask
     * flags for this tag.  It tells the
     * class how to render the tag.
     *
     * @access private
     *
     * NOTE: the child class can override this
     *       to set the options
     */
    function _set_flags() {
        parent::_set_flags();
        $this->_flags |= _NEWLINEAFTEROPENTAG | _NEWLINEAFTERCLOSETAG |
            _CONTENTREQUIRED | _CLOSETAGREQUIRED;
    }

	/**
	 * This method sets the name of the tag
     *
     * {@source }
	 *
	 * @param string - the tag name
	 */
	function set_tag_name( $name ) {
		$this->_tag = $name;
	}

	/**
	 * This method gets the name of the tag
     *
     * {@source }
	 *
	 * @return string - the tag name
	 */
	function get_tag_name() {
		return $this->_tag;
	}

	/**
	 * This returns the tag declared for this class.
	 * This should be used in favor of
	 * accessing the $this->_tag directly.
     *
     * {@source }
	 *
	 * @return string - the _tag var for this class.
	 */
	function get_tag() {
		//for compatibility only
		return $this->get_tag_name();
	}

    /**
     * add a single attribute (name="value")
     *
     * {@source }
     *
     * @param   string  $name   attribute name
     * @param   mixed   $value  the value.
     * @return none
     */
    function set_tag_attribute( $name, $value=NULL ) {
        if (!$value) {
            $value = $name;
        }
        $this->_attributes[$name] = $value;
    }

    /**
     * add multiple attributes (name="value")
     *
     * {@source }
     *
     * @param   array   $attributes Associative array of name="value" pairs of
     *                              tag atributes.
     *                              ie array("border"=>"0", "class"=>"hover");
     * @return none
     */
    function set_tag_attributes( $attributes=array() ) {
        $this->_attributes = array_merge($this->_attributes, $attributes);
    }

    /**
     * This method allows you to get the value for
     * a tag attribute.
     * 
     * @param string the attribute you want to find
     * @return mixed.  FALSE if there is no attribute set.
     */
    function get_tag_attribute($attribute) {
        if (!array_key_exists($attribute, $this->_attributes)) {
            return FALSE;
        } else {
            return $this->_attributes[$attribute];
        }        
    }

    /**
     * clear all attributes and start with new attributes
     *
     * {@source }
     *
     * @param   array   Associative array of name="value" pairs of
     *                  tag atributes.
     *                  ie array("border"=>"0", "class"=>"hover");
     * @return none
     */
    function reset_attributes( $attributes=array() ) {
        $this->_attributes = array();
        $this->set_tag_attributes( $attributes );
    }

    /**
     * get the nth element from content array
     *
     * NOTE:
     *    This has been made public in the Container
     *
     * {@source }
     * @access private
     *
     * @param   int   $cell   the cell to get
     * @return  mixed
     */
    function &_get_element( $cell ) {
        return $this->get_element($cell);
    }



    //****************************************************************
    // Misc functions
    //****************************************************************

    /**
     * set the newline_after_opentag flag
     *
     * {@source }
     *
     * @param   boolean TRUE or FALSE
     * @return none
     */
    function set_newline_after_opentag( $flag ) {
        if ($flag) {
            $this->_flags |= _NEWLINEAFTEROPENTAG;
        } else{
            $this->_flags &= ~_NEWLINEAFTEROPENTAG;
        }
    }

    /**
     * set the newline_after_content flag
     *
     * {@source }
     *
     * @param   boolean TRUE or FALSE
     * @return none
     */
    function set_newline_after_closetag( $flag ) {
        if ($flag) {
            $this->_flags |= _NEWLINEAFTERCLOSETAG;
        } else{
            $this->_flags &= ~_NEWLINEAFTERCLOSETAG;
        }
    }

    /**
     * This method turns on the automatic wrapping
     * of the tag's content inside the CDATA wrapper
     * for XML
     *
     * {@source }
     * @param   boolean     $flag   TRUE or FALSE
     * @return none
     */
    function set_cdata_flag($flag) {
        if ($flag) {
            $this->_flags |= _CDATACONTENTWRAP;
            $this->set_collapse(TRUE);
        } else{
            $this->_flags &= ~_CDATACONTENTWRAP;
        }
    }

	/**
	 * This function turns on the collapse flag
     *
     * {@source }
	 *
	 * @param boolean - the collapse flag
	 * @param boolean - the indent flag
	 *                  DEFAULT: TRUE;
     * @return none
	 */
	function set_collapse($collapse=TRUE, $indent=TRUE) {
        if ($collapse) {
            $this->_flags |= _COLLAPSE;
        } else {
            $this->_flags &= ~_COLLAPSE;
        }

		$this->set_newline_after_opentag(FALSE);
		$this->set_indent_flag($indent);
		if ($indent) {
			$this->set_newline_after_closetag(TRUE);
		} else {
			$this->set_newline_after_closetag(FALSE);
        }
	}

    /**
     * This function checks to see if
     * there is only 1 content data, and
     * its not an object, then it auto
     * sets some of the indentation flags
     *
     * {@source }
     * @access private
     * @return none
     */
    function _prepare_flags() {
		if ($this->_flags & _CONTENTREQUIRED) {
			if ($this->count_content() == 1) {
				if (!is_object($this->_content[0])) {
					//ok looks like this object has only
					//1 data for content and its a string.
					if ( !strstr($this->_content[0], "\n") ) {
						$this->_flags &= ~_NEWLINEAFTEROPENTAG;
					}
				}
			} else if ($this->count_content() == 0) {
                $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
            }
		}
    }


	/****************************************/
	/* Some helper methods for rendering 	*/
	/* the output xml tree.					*/
	/****************************************/

	/**
	 * this function is responsible for
	 * rendering the open tag.
     *
     * {@source }
     * @access private
	 *
	 * @param int - the indent level
	 * @param boolean - do we add the finish / if we have no
	 *                  close tag and no content?
     * @return string
	 */
	function _render_open_tag( $indent_level, $finish_slash=TRUE ) {
		//get the indent level
		$indent = $this->_render_indent( $indent_level );

		//build the tag
		if ($this->_flags & _ALWAYS_LOWERCASE) {
			$this->_tag = strtolower($this->_tag);
		} else if ($this->_flags & _ALWAYS_UPPERCASE) {
			$this->_tag = strtoupper($this->_tag);
		}
        //save on mem
        $xml = $indent . ((isset($this->_tag_prefix) && $this->_tag_prefix) ? $this->_tag_prefix : _TAG_PREFIX) . $this->_tag;
		
		foreach( $this->_attributes as $name => $value) {
			$xml .= $this->_build_attribute_string($name, $value);
		}

		if ( !($this->_flags & _CLOSETAGREQUIRED) && !($this->_flags & _NOFINISHSLASHXHTML)
			 && $finish_slash ) {
			$xml .= " /".(isset($this->_tag_postfix) ? $this->_tag_postfix : _TAG_SUFFIX);
		} else {
			$xml .= (isset($this->_tag_postfix) ? $this->_tag_postfix : _TAG_SUFFIX);
		}
		
		if ($this->_flags & _NEWLINEAFTEROPENTAG) {
			$xml .= "\n";
		}

		return $xml;
	}


	/**
	 * this function is reponsible for
	 * rendering the pcdata, or content
	 * of the tag (if any)
	 *
     * {@source }
     * @access private
     *
	 * @param int - the indent level
     * @return string
	 */
	function _render_content( $indent_level, $output_debug=0 ) {		
		
		//walk through the content
		$xml = '';
        for ($x=0; $x<=$this->_data_count-1; $x++) {
            $item = &$this->_content[$x];
			if (is_object($item) && method_exists($item, "render")) {
				if (($this->_flags & _COLLAPSE) && method_exists($item, "set_collapse")) {
					$item->set_collapse(TRUE, FALSE);
				}
				if ($indent_level == INDENT_LEFT_JUSTIFY) {
					$indent = INDENT_LEFT_JUSTIFY;
				} else {
					$indent = $indent_level + 1;
				}
				$xml .= $item->render($indent, $output_debug);
			} else {
				if ($this->_flags & _COLLAPSE) {
					$xml .= $item;
				} else {
					if ($indent_level == INDENT_LEFT_JUSTIFY) {
						$indent = INDENT_LEFT_JUSTIFY;
					} else {
						$indent = $indent_level + 1;
					}
					$indent = $this->_render_indent($indent);
					if ($this->_flags & _NEWLINEAFTEROPENTAG) {
						$item = str_replace("\n", "\n" . $indent, $item);
						$xml .= $indent . $item . "\n";
					} else {
						$item = str_replace("\n", "\n" . $indent, $item);
						$xml .= $item;
					}
				}				
			}
		}
		if ($this->_flags & _CDATACONTENTWRAP) {
			if ($this->_flags & _COLLAPSE) {
				$xml = "<![CDATA[".$xml."]]>";
			} else {
				$indent = $this->_render_indent($indent+1);
				$indent1 = $this->_render_indent($indent+2);
				$indent2 = $this->_render_indent($indent+3);
				$xml = "\n".$indent1."<![CDATA[\n".$xml."\n".$indent1."]]>\n".$indent;
			}
			
		}
		return $xml;
	}


	/**
	 * this function is reposnsible for
	 * rendering the closing tag (if any)
	 *
     * {@source }
     * @access private
     *
	 * @param int - the indent level
     * @return string
	 */
	function _render_close_tag( $indent_level ) {
		if (!($this->_flags & _CLOSETAGREQUIRED)) {
			return '';
		}

		$indent = "";
		if (($this->_flags & _INDENT) && ($this->_flags & _NEWLINEAFTEROPENTAG)) {
			$indent = $this->_render_indent($indent_level);
		}		
		$str = $indent ."</".$this->_tag.">";
		
		if ($this->_flags & _NEWLINEAFTERCLOSETAG) {
			$str .= "\n";
		}
		
		return $str;
	}

    /**
     * this builds an attribute for an XML tag.
     * XML attributes MUST have a name AND a
	 * value.
     *
     * {@source }
     * @access private
     *
     * @param   string - $name attribute name
     * @param   mixed - $value attribute value
     * @return  the tag attribute name=value pair.
     *          to be added to the tag.
     */
    function _build_attribute_string($name, $value) {
        return " ".$name."=\"".$value."\"";
    }
}
?>
