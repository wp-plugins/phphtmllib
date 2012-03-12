<?php

/**
 * This contains the XMLDocumentClass
 *
 * $Id: XMLDocumentClass.inc 3556 2012-03-11 11:26:12Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */


/**
 *
 * This class lets you build a complete
 * xml document and render it.
 *
 * It automatically creates the root xml tag
 * that will contain all of the content.
 * The name of the tag is the first parameter to
 * the constructor.  You can add/change the attributes
 * to the root tag via the set_root_attributes() or
 * the set_root_attribute() methods.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib 
 */ 
class XMLDocumentClass extends Container {


	/**
	 * holds the xml tag object that
	 * all content will be wrapped in
	 *
	 */
	var $_xml_obj = NULL;

	/**
     * character set to be used in this
     * page.  This gets automatically
     * placed in the <?xml encoding="" ?>
     * @var  string
     * @access   private
     */
    var $_charset = "iso-8859-1";

	/**
	 * This flag tells if we should
	 * output the header content type.
	 * this is usefull for folks using
	 * this class for output not destined
	 * for a browser.
	 */
	var $_show_http_header = FALSE;

	/**
	 * this is a hack to show the
	 * character encoding or not.
	 * DEFAULT: on
	 *
	 * @var boolean
	 */
	var $_show_char_encoding = TRUE;

    /**
     * Holds the url of dtd
     */
    var $dtd = NULL;

    /**
     * Holds the name of the root xml
	 * element as well as the DOCTYPE
	 * document_element attribute
     */
    var $root_name = NULL;

	/**
	 * The root xml tag for all data
	 *
	 * @var XMLTagClass object
	 */
	var $_root_tag = NULL;

    /**
     * DOCTYPEag object that sets the document
     * type.  This gets rendered prior to <html>
     * @var  object
     * @access   private
     */
    var $_doctype = NULL;

	/**
	 * the DOCTYPE source attribute
	 *
	 * @var string
	 */
	var $_doctype_source = "SYSTEM";

	/**
	 * This contains the doctype links
	 * attributes.  There can be a maximum
	 * of 2 according to the XML spec
	 */
	var $_doctype_links = array();

	/**
	 * The http content-type
	 *
	 */
	var $_http_content_type = "application/xml";

	/**
	 * The container for all the
	 * xml-stylesheet tags
	 *
	 * @var object
	 */
	var $_xml_stylesheet_container = NULL;


	/**
	 * The constructor
	 *
	 * @param string - the root xml tag's name
	 * @param string - the link path to the DTD (if any)
	 * @param array - the root tag's attributes
	 *
	 */
	function XMLDocumentClass($root_name, $dtd = NULL, $root_attributes = array()) {
		$this->_create_xml_obj();
        $this->set_root_name($root_name);
		$this->set_doctype_link( $dtd );
		$this->set_root_attributes( $root_attributes );
		$this->_build_root_tag();
		$this->_build_xml_stylesheet_container();

        //we should always render in 
        $GLOBALS["HTML_RENDER_TYPE"] = XHTML_STRICT;
	}
	
	/**
	 * function that will render the XML Document header
	 * portion upto the root tag.
	 *
	 * @return string the raw html output.
	 */	
	function _render_header(){
	
		//dump out the content type		
		$this->dump_http_header();

		//set the encoding type
		if ($this->_show_char_encoding) {
			$this->_xml_obj->set_tag_attribute("encoding", $this->get_encoding() );
		}

		//add the xml tag
		$output = $this->_xml_obj->render(0);

		//add any stylesheet links
		if ($this->_xml_stylesheet_container->count_content() > 0) {
			$output .= $this->_xml_stylesheet_container->render(0);
		}		

		//build the doctype if needed.
		$this->_build_doctype();

		if ($this->_doctype != NULL) {
			$output .= $this->_doctype->render();
		}

		return $output;
	}
	/**
	 * function that will render the XML Document.
	 *
	 * @param int - the indentation level for 
	 *              the container.
	 * @param int - the output debug flag to 
	 *              maintain compatibility w/ the API.
	 *
	 * @return string the raw html output.
	 */
	function render( $indent_level = 0, $output_debug=0) {

	    //render the http header and xml header
	    $output = $this->_render_header();
	    
		//set the root tag's attributes
		$this->_root_tag->set_tag_attributes( $this->get_root_attributes() );

		//render the root tag's content
		$output .= $this->_root_tag->render($indent_level, 0);
		return $output;
	}

	/**
	 * we override this class to make sure
	 * we push all content inside the 
	 * local _xml_obj tag
	 *
     * push content onto content stack
     * adds content to tag as a FIFO.
     * You can have n number of parameters.
     * each one will get added in succession to the content.
     * @param   mixed   $content - either string, or tag object.
     * @access  public
	 */
	function add() {
		if ($this->_root_tag == NULL) {
			$this->_build_root_tag();
		}
		$args = func_get_args();
		$num = func_num_args();
		foreach( $args as $content) {
			$this->_root_tag->push( $content );
		}
	}

    /**
     * Same as add().
     * NOTE: only exists for 1.1.x compatibility
     * 
     * @deprecated
     * @param   mixed   $content - either string, or tag object.
     * @access  public
     */
    function push(  ) {
        $args = func_get_args();
        call_user_func_array( array(&$this, "add"), $args);
    }


	/**
	 * we override this class to make sure
	 * we push all content inside the 
	 * local _xml_obj tag
	 *
     * push content onto content stack
     * adds content to tag as a FIFO
     * You can only add 1 element at a time, and
     * it will be added as a reference.  So you can't do
     * push_reference("something");, since "something" is a
     * static.
     * @param   mixed   $content - either string, or tag object.
     *                             the tag object gets stored as a
     *                             reference to the original, so you
     *                             can push it, then modify it later.
     * @access  public
	 */
	function add_reference( &$content ) {
		if ($this->_root_tag == NULL) {
			$this->_build_root_tag();
		}
		$this->_root_tag->add_reference( $content );
	}

    /**
     * Same as add_reference
     * NOTE : only exists for compatibility with 1.1.x
     *
     * @deprecated
     * 
     * @access  public
	 * @param   mixed - a reference to some variable.
     */
    function push_reference( &$content ) {
        $this->add_reference( $content );
    }

	/**
	 * This function is used to add a new
	 * xml-stylesheet tag to the top 
	 * portion of the document.
	 * This will automatically get added 
	 * after the xml tag and before the
	 * <!DOCTYPE > tag
	 *
	 * @param string - the href for the stylesheet link
	 */
	function add_xml_stylesheet_link( $href ) {
		$this->_xml_stylesheet_container->add( xml_stylesheet($href) );
	}

	/**
	 * This function builds the _xml_stylesheet_container
	 *
	 */
	function _build_xml_stylesheet_container() {
		$this->_xml_stylesheet_container = container();
	}


	/**
	 * we override this class to make sure
	 * we push all content inside the 
	 * local _xml_obj tag
	 *
     * destroy existing content and start with new content.
     * @param   mixed   $content    can be tag object, or raw (string).
     * @access  public
     */
    function reset_content( ) {
        $this->_build_root_tag();
    }


	/**
	 * This function builds the local
	 * xml container object that holds
	 * all xml tags that are pushed into
	 * this class
	 *
	 * @return XMLtag object
	 */
	function _create_xml_obj() {
		$this->_xml_obj = new XMLtag( array("version" => "1.0") );
	}

	/**
	 * This function builds the root xml
	 * tag that will contain all of the Document's
	 * xml tags
	 *
	 */
	function _build_root_tag() {
		$this->_root_tag = xml_tag($this->_root_name);
	}

	/**
     * set the character set
     * @param string  $charset - the charset for the meta tag
     *
     */
    function set_encoding( $charset ) {
      $this->_charset = $charset;
    }

	/**
	 * This function gets the current encoding type
	 *
	 * @return string - the current encoding type
	 *                  for the xml
	 */
	function get_encoding() {
		return $this->_charset;
	}

    /**
     * Set the document name
	 * and the root tag's name.
     * @param string  $doc_name
     *
     */
    function set_root_name($root_name) {
        $this->_root_name = $root_name;
    }

     /**
     * This function gets the document name
     *
     * @return string - the current document name
     *                  for the xml
     */
    function get_root_name() {
        return $this->_root_name;
    }

	/**
	 * This function is used to set the
	 * root xml tag's attributes
	 *
	 * @param array
	 */
	function set_root_attributes( $attributes ) {
        $this->_root_attributes = $attributes;
	}

	/**
	 * This sets 1 root tag attribute value pair
	 *
	 * @param string - the attribute name
	 * @param string - the attribute value
	 */
	function set_root_attribute( $name, $value ) {
		$this->_root_attributes[$name] = $value;
	}

	/**
	 * This function is used to get the
	 * root xml tag's attributes
	 *
	 * @return array
	 */
	function get_root_attributes() {
		return $this->_root_attributes;
	}

	/**
	 * This method is used to set the link attributes
	 * for the DOCTYPE tag
	 *
	 */
	function set_doctype_link( $link ) {
		if ($link != NULL) {
			$this->_doctype_links[] = $link;
		}		
	}

	/**
	 * method to update the flag that lets us know
	 * to show/render the character encoding string
	 * in the xml tag or not
	 *
	 * @param boolean
	 */
	function show_character_encoding( $flag=TRUE) {
		$this->_show_char_encoding = $flag;
	}

    /**
     * this function is used to set the flag
     * that tells this class to automatically
     * output the content type in the http header
     *
     * @param boolean
     */
    function show_http_header( $flag=TRUE ) {
        $this->_show_http_header = $flag;
    }

	/**
	 * This function is used to set the 
	 * http header content-type for output to browsers
	 *
	 * @param string 
	 */
	function set_http_content_type( $type="application/xml") {
		$this->_http_content_type = $type;
	}

	/**
	 * This function returns the current 
	 * value of the http header content type
	 *
	 * @return string
	 */
	function get_http_content_type() {
		return $this->_http_content_type;
	}

	/**
	 * This function is used to output the http
	 * header for this document.
	 * It makes a call to php's Header() to 
	 * set the Content-type
	 *
	 */
	function dump_http_header() {
		if ($this->_show_http_header) {
			Header("Content-type: ".$this->_http_content_type);
		}
	}

	/**
	 * this function is used to change the 
	 * DOCTYPE tag's source attribute.  By 
	 * default it is set to SYSTEM.
	 * (ie <!DOCTYPE html SYSTEM > )
	 *                    ^^^^^^
	 *
	 * NOTE: only 2 valid values 'SYSTEM', 'PUBLIC'
	 *
	 * @param string - the new source attribute
	 */
	function set_doctype_source($source) {
		if (strcmp("PUBLIC", $source) != 0 &&
			strcmp("SYSTEM", $source) != 0) {
			//user tried to set it to an invalid
			//value.
			trigger_error("XMLDocumentClass::set_doctype_source() ".
						  "invalid source type of (".$source.") set. ",
						  E_USER_WARNING);
		} else {
			$this->_doctype_source = $source;
		}
	}

	/**
	 * This function returns the current
	 * DOCTYPE tag's source attribute
	 *
	 * @return string
	 */
	function get_doctype_source() {
		return $this->_doctype_source;
	}


	/**
	 * This method builds the DOCTYPE tag for the document
	 *
	 */
	function _build_doctype() {
		if (count($this->_doctype_links) > 0) {
			$this->_doctype = xml_doctype($this->get_root_name(),
										  $this->get_doctype_source(),
										  $this->_doctype_links[0],
										  count($this->_doctype_links) > 1 ? $this->_doctype_links[1] : NULL);
		}
	}
}
?>
