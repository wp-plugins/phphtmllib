<?php

/**
 * This file contains the BaseWidget class
 *
 * $Id: BaseWidget.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */

if (!defined('PHPHTMLLIB_WIGDET_IMAGEPATH'))
    define('PHPHTMLLIB_WIGDET_IMAGEPATH', PHPHTMLLIB_RELPATH . '/images/widgets') ;

/**
 * this is the base widget class, that all widgets
 * are based off of.  It provides some basic 
 * members and methods
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class BaseWidget extends Container {

	/**
	 * the indent level
	 * @access private
	 * @var int
	 */
	var $_indent_level=1;

	/**
	 * The title of the table.
	 * @access public
	 * @var string
	 */
	var $title='';

	/**
	 * the width of the widget
	 * @access public
	 * @var string
	 */
	var $width="100%";

	/**
	 * The widget wide alignment
	 * value.
	 * @access private
	 * @var string
	 */
	var $_align = NULL;

	/**
	 * hold the data for this
	 * widget.  can be anything,
	 * depends on the child class.
	 * defaults to an array.
	 * @access private
	 * @var array
	 */
	var $data = array();


	/**
	 * The image path prefix.
	 * If an image lives on the server in 
	 * /images/foo/blah.jpg
	 * then this prefix should be
	 * /images/foo
	 */
	var $_image_prefix = PHPHTMLLIB_WIGDET_IMAGEPATH ;

	
	/**
	 * Function for returning the raw javascript
	 * that is required for this widget.
	 *
	 * @return string - the raw javascript
	 */
	function get_javascript() {
		return NULL;
	}

	/**
	 * This function provides the 
	 * mechanism to build and return 
	 * the css needed by this widget
	 *
	 * @return string the raw css
	 */
	function get_css() {
		return NULL;
	}

	/**
	 * Set the title for the widget.
	 * this is just a generic title string
	 * that can be used however the child class
	 * wants to use it.
	 *
	 * @param string - $title
	 */
	function set_title( $title ) {
		$this->title = $title;
	}

	/**
	 * Function for accessing the 
	 * title of this widget
	 *
	 * @return string - the title
	 */
	function get_title() {
		return $this->title;
	}


	/**
	 * Set the width for the widget.
	 * this is meant to be the overall
	 * width expected to be used to
	 * control the generated html.
	 *
	 * @param string - $width (ie. 80, 100%)
	 */
	function set_width( $width ) {
		$this->width = $width;
	}

	/**
	 * Function for getting the current
	 * widget width setting.
	 *
	 * @return string - the width
	 */
	function get_width() {
		return $this->width;
	}

	/**
	 * This function sets the align attribute
	 * for the outer table.
	 *
	 * @param string - $align - the align value
	 */
	function set_align( $align ) {
		$this->_align = $align;
	}

	/**
	 * This gets the alignment value 
	 * for the outer table
	 *
	 * @return string - the alignment
	 */
	function get_align() {
		return $this->_align;
	}


	/**
	 * This function is used to set the 
	 * image path prefix.
	 * 
	 * @param string
	 */
	function set_image_path_prefix($path) {
		$this->_image_prefix = $path;
	}
}
?>
