<?php

/**
 * Holds the Container class.
 *
 * $Id: ContainerClass.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 *
 * @copyright LGPL - See LICENCE
 *
 */
 
 
/**
 * This class is nothing more then a 
 * container widget.  It lets you
 * push data into it, and it will
 * render each item indented properly
 * so it works with the rest of the libs.
 *
 * This is helpfull when you have a function
 * that wants to return multiple Tag Objects
 * or widgets.  Just wrap them in this container
 * and they will all get rendered with the 
 * current indentation level.
 *
 * Base Class for phpHtmlLib
 *
 * @link http://phphtmllib.sourceforge.net 
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @tutorial Container.cls
 *
 */

class Container {


    /**
     * Tag content as a stack
     * ie <span> content here </span>
     * @var  array
     * @access   private
     */
    var $_content = array();

	/**
     * This keeps track of how much content
     * data has been pushed into the content
     * portion of the tag.
     *
     * @var int
     * @access private
     */
    var $_data_count = 0;

    /**
     * The flags that tell us
     * how to render the tag
     * its contents, and the close
     * @access private
     */
    var $_flags = _NEWLINEAFTERCONTENT;


	/**
	 * The constructor. 
	 * 
	 * This lets you pass in data
	 * that you want automatically
	 * added to the container.  This
	 * works in the same manner as 
	 * the push() method.
     * 
     * {@source }
     * 
     * @tutorial Container.cls#constructor
	 */
	function Container() {
        //We do the adding to the content var
        //here instead of calling $this->push()
        //to save some cpu cycles.
        $num = func_num_args();
        for ($i=0;$i<$num;$i++) {
            $arg = func_get_arg($i);
            array_push($this->_content, $arg);
        }
        $this->_data_count += $num;

        //set the flag bitmask
        $this->_set_flags();
    }


	/**
	 * This function is compatible with the
	 * rest of the phpHtmllib API spec.
	 * It just walks through each of the 
	 * class' data and renders it with the 
	 * appropriate indentation.
     * 
     * {@source }
	 *
	 * @param int - the indentation level for 
	 *              the container.
	 * @param int - the output debug flag to 
	 *              maintain compatibility w/ the API.
	 *
	 * @return string the raw html output.
	 */
	function render($indent_level=0, $output_debug=0) {
		$html = '';
        
        for ($x=0; $x<=$this->_data_count-1; $x++) {
            $item = &$this->_content[$x];
			if (method_exists($item, "render") ) {
				if (($this->_flags & _COLLAPSE) && method_exists($item, "set_collapse")) {
					$item->set_collapse(TRUE, FALSE);
				}
				$html .= $item->render($indent_level, $output_debug);
			} else {
                if ($this->_flags & _COLLAPSE) {
                    $html .= $item;                    
                } else {
                    $indent = $this->_render_indent($indent_level, $output_debug);
                    $html .= $indent.$item;
                    if ($this->_flags & _NEWLINEAFTERCONTENT) {
                        $html .= "\n";
                    }
                }                
			}
		}
        if ($this->_flags & _COLLAPSE) {
            $indent = $this->_render_indent($indent_level, $output_debug);
            if ($this->_flags & _NEWLINEAFTERCONTENT) {
				if ($output_debug) {
					$html = $indent . $html . "<br>\n";					
				} else {
					$html = $indent . $html . "\n";
				}                
            } else {
                $html = $indent . $html;
            }
			
        }
		return $html;
	}

	/***************************/
	/* DATA specific functions */
	/***************************/

    /**
     * Same as add().
     * NOTE: only exists for 1.1.x compatibility
     * 
     * {@source }
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
     * add content onto content stack
     *
     * adds content to tag as a FIFO.
     * You can have n number of parameters.
     * each one will get added in succession to the content.
     * 
     * {@source }
     * 
     * @tutorial Container.cls#add
     * 
     * @param   mixed   $content - either string, or tag object.
     * @access  public
     */
    function add(  ) {
		$args = func_get_args();
		$num = 0;
		foreach( $args as $arg ) {
			$this->_content[] = $arg;
			$num++;
		}
		//keep track of how much data we have added.
		$this->_data_count += $num;
    }


    /**
     * Same as add_reference
     * NOTE : only exists for compatibility with 1.1.x
     *
     * {@source }
     * @deprecated
     * 
     * @access  public
	 * @param   mixed - a reference to some variable.
     */
    function push_reference( &$content ) {
        $this->add_reference( $content );
    }

    /**  
     * Add content onto content stack
     * so you can change the item later.
     *
     * adds content to tag as a FIFO
     * You can only add 1 element at a time, and
     * it will be added as a reference.  So you can't do
     * push_reference("something");, since "something" is a
     * static.
     *
	 * @access  public
     *
     * @param   mixed   $content - either string, or tag object.
     *                             the tag object gets stored as a
     *                             reference to the original, so you
     *                             can push it, then modify it later.     
     */
    function add_reference( &$content ) {
        $this->_content[] = &$content;
		$this->_data_count++;
    }


    /**
     * destroy existing content and start with new content.
     * 
     * {@source }
	 *
	 * @access  public
     * @param   mixed   $content    can be tag object, or raw (string).
     */
    function reset_content( ) {
        $this->_content = array();
		$this->_data_count = 0;
		$args = func_get_args();
        call_user_func_array( array(&$this, "add"), $args);
    }

    /**
     * counts the number of content objects
	 *
     * {@source }
	 * @access  public
     * @return  int
     */
    function count_content( ) {
        return $this->_data_count;
    }


    /**
     * get the nth element from content array
     * 
     * {@source }
     * 
     * @param   int   $cell   the cell to get
     * @return  mixed
     */
    function &get_element( $cell ) {
        return $this->_content[$cell];
    }

     
    /**
     * This method is used to set the bitmask
     * flags for this tag.  It tells the 
     * class how to render the tag.
     *
     * NOTE: the child class can override this
     *       to set the options
     * 
     * {@source }
     * @access private
     * 
     */
    function _set_flags() {
        $this->_flags = _NEWLINEAFTERCONTENT | _INDENT;
    }


    /**
     * function to set the indent flag
     * 
     * {@source }
	 *
	 * @access  public
     * @param   boolean     $flag  TRUE or FALSE
     */
    function set_indent_flag( $flag ) {
        if ($flag) {
            $this->_flags |= _INDENT;
        } else {
            $this->_flags &= ~_INDENT;
        }
    }


	/**
	 * This flag gets the current value
	 * of the indent flag
	 *
	 * {@source }
	 *
	 * @return boolean
	 */
	function get_indent_flag() {
		return $this->_flags & _INDENT;
	}


	/**
	 * This function turns on the collapse flag
	 *
	 * {@source }
     * 
     * @tutorial Container.cls#collapse
	 *
	 * @param boolean - the collapse flag
	 * @param boolean - the indent flag
	 *                  DEFAULT: TRUE;
	 */
	function set_collapse($collapse=TRUE, $indent=TRUE) {
        if ($collapse) {
            $this->_flags |= _COLLAPSE;
        } else {
            $this->_flags &= ~_COLLAPSE;
        }
		
        if (!$indent) {
            $this->set_indent_flag($indent);
            $this->_flags &= ~_NEWLINEAFTERCONTENT;
        }		
	}



	/**
	 * returns leading indent for tag
	 *
     * {@source }
	 * @access  private
	 *
	 * @param   int		the indentation level for this tag.
	 * @return  string	 
	 */
	function _render_indent($indent_level, $debug_flag=0) {
		$indent = "";
		if ( $debug_flag && $indent_level > 0) {
			$indent_level *=2;
		}
		if ( ($this->_flags & _INDENT) && $indent_level > 0) {
			$indent = str_repeat(_INDENT_STR, $indent_level);
		}
		if ( $debug_flag && $indent_level > 0) {
			$indent = str_replace(_INDENT_STR, "&nbsp;", $indent);
		}
		return $indent;
	}
}
?>
