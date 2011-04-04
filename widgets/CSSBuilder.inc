<?php
/**
 * This file contains the CSSBuilder class
 *
 * $Id: CSSBuilder.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */



/**
 *  This class is a widget for constructing and
 *  rendering css.  It exports API's for adding
 *  classes, ids and their attributes.
 *  It can render as either a stand alone 
 *  foo.css type of file, with the appropriate
 *  httpd header, or as part of a <style> tag's 
 *  content that lives as part of an html document.
 *
 *  This class lets you create classes in the format
 *
 *   name extends_list {
 *       property: value;
 *   }
 *
 * 
 *  ie.
 *  #foo div, span {
 *     font-family: arial, helvetica;
 *     font-size: 10pt;
 *  }
 *
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 *  
 */
class CSSBuilder {


	/**
	 * This holds the entries for the css
	 *
	 * @var array
	 */
	var $_entries = array();


	/**
	 * Flag to let us know if we should
	 * output a header content-type value
	 * header("Content-Type: text/css");
	 *
	 * @var boolean
	 */
	var $_header_flag = FALSE;


	/**
	 * String to use as indent string.
	 * can be any char.  defaulted to 1 space
	 * @var  string
	 * @access   private
	 */
	var $_indent_str = "  ";

	/**
	 * Flag for pretty (indented) output
	 * @var  boolean
	 * @access   public
	 */
	var $indent_flag = TRUE;


	/**
	 * The CSSBuilder constructor
	 *
	 * @param boolean - output the http header
	 *                  content type mime type
	 *                  or not. 
	 *
	 */
	function CSSBuilder($header_flag=FALSE) {
		$this->set_header_flag( $header_flag );
		$this->user_setup();
	}


	/**
	 * The render method for compatibility
	 * with the rest of the phphtmllib api
	 *
	 * @param int - the indentation level for 
	 *              the container.
	 * @param int - the output debug flag to 
	 *              maintain compatibility w/ the API.
	 *
	 * @return string the raw html output.
	 */
	function render($indent_level=1, $output_debug=0) {
		if ($this->_header_flag) {
			header("Content-Type: text/css");			
		}

		$indent = $this->_render_indent( $indent_level );
		
		$css = "";
		foreach( $this->_entries as $class => $properties ) {
			$css .= $indent.$this->_build_name( $class );
			$css .= $this->_build_properties( $properties, $indent );
			$css .= "\n";
		}

		return $css;
	}


	/**
	 * This is used to set/update the header
	 * flag.
	 *
	 * @param boolean
	 */
	function set_header_flag( $flag ) {
		$this->_header_flag = $flag;
	}

	/**
	 * Call the child class' setup function 
	 * to build the actual css classes and their
	 * attributes
	 */
	function user_setup() {

	}



	/*******************************************/
	/* functions for building/updating entries */
	/*******************************************/

	/**
	 * This function is used to construct the css name
	 * declaration string.
	 * ie #foo div,span {
	 * 
	 * @param string the name-extends string
	 * @return the css name declaration
	 */
	function _build_name( $class ) {
		$temp = explode('-', $class);

		$css = $temp[0]." ".$temp[1]." {\n";
		return $css;
	}

	/**
	 * This function is used to construct the
	 * property: value strings for the class
	 *
	 * @param array - the properties
	 * @param array - the indent string.
	 * @return string
	 */
	function _build_properties( $properties, $indent_str ) {
		$css = "";
		foreach( $properties as $property => $value ) {
			$css .= $indent_str."	".$property.": ".$value.";\n";
		}
		$css .= $indent_str."}\n";
		return $css;
	}


	/**
	 * This function adds a new class entry
	 *
	 * @param string - class/id name
	 * @param string - the list of extends
	 *                 ie #foo div, a { }
	 *                 where "div, a" are the extends
	 *                    
	 * @param array - the attributes
	 */
	function add_entry($name, $extends, $attributes) {
		$this->_entries[$name."-".$extends] = $attributes;
	}


	/**
	 * This function updates a css property value
	 * for a specific class/id
	 *
	 * @param string - the class/id name
	 * @param string - the list of extends
	 *                 ie #foo div, a { }
	 *                 where "div, a" are the extends
	 * @param string - the property to adjust
	 * @param string - the value for the property
	 */
	function update_property($name, $extends, $property, $value ) {
		$this->_entries[$name."-".$extends][$property] = $value;	
	}

	/**
	 * This function updates a css property value
	 * for a specific class/id
	 *
	 * @param string - the class/id name
	 * @param string - the list of extends
	 *                 ie #foo div, a { }
	 *                 where "div, a" are the extends
	 * @param array - the array of array(property => value ) pairs.
     */
	function update_properties($name, $extends, $properties) {

		foreach ( $properties as $property => $value ) {
			$this->_entries[$name."-".$extends][$property] = $value;

		}
	}

	/**
	 * This function is a macro for walking the entire 
	 * list of classes, looking for particular property
	 * in each class.  It then tries to match
	 * the current value of that property and then
	 * replaces the value with the new value.
	 * 
	 * NOTE: this is a way of templating themes.
	 *       you create the original css w/ a value
	 *       of something like _DARK_COLOR_
	 *       and use this function to replace all occurrences
	 *       with #dbdbdb
	 *       
	 * @param string - the property that the search lives in
	 * @param string - the original value to find
	 * @param string - the new value
	 */
	function update_all_values( $property, $search, $value ) {

		array_walk( $this->_entries, array($this, "_replace_value"),
			       array("property" => $property,
					     "search" => $search,
					     "value" => $value ) );

	}


	/**
	 * This function does the main work for update_all_values
	 *
	 */
	function _replace_value( &$item, $key, $blah ) {
		if (@strcasecmp($item[$blah["property"]], $blah["search"]) == 0) {
			$item[$blah["property"]] = $blah["value"]; 		
		}
	}




	/**
	 * returns leading indent for tag
	 *
	 * @access  private
	 *
	 * @param   int		the indentation level for this tag.
	 * @return  string	 
	 */
	function _render_indent($indent_level) {
		$indent = "";
		if ( $this->indent_flag && $indent_level > 0) {
			$indent = str_repeat($this->_indent_str, $indent_level);
		}
		return $indent;
	}

}


?>
