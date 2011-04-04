<?php
/**
 * 
 * $Id: InfoTable.inc 3073 2007-10-30 20:06:51Z mpwalsh8 $
 *
 * This renders a table with a title
 * optional column headers
 * and rows
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib 
 */


/**
 * This is a widget class that can build
 * and render data in a nicely formated table
 * with a title, column headers and data
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 */ 
class InfoTable extends BaseWidget {

    /**
     * this holds the column header
     * titles.
     */
    var $_headers = array();

    /**
     * this holds the default cellpadding
     */
    var $_cellpadding=2;

    /**
     * This holds the default cellspacing
     */
    var $_cellspacing=0;

    /**
     * The default class used for the
     * title 
     */
    var $_title_css_class = "title";

    /**
     * The default alignment for the 
     * title text in the caption.
     */
    var $_title_text_align = "left";

    /**
     * Flag to tell the class to render
     * the vertical cell border 
     */
    var $_show_vertical_cellborder = TRUE;


    /**
     * Show any internal borders?
     */
    var $_show_cellborders = TRUE;

    /**
     * Toggles whether to show alternate color
     */    
    var $_alt_color_flag = FALSE;

    /**
     * The constructor
     *
     * @param string - the title
     * @param string - the width of the table
     * @param string - the alignment
     */
    function InfoTable( $title, $width="100%", $align=NULL ) {
        $this->set_title($title);
        $this->set_width($width);
        $this->set_align($align);
    }

    /**
     * This function renders the object.
     *
     * @param int - the indentation level for 
     *              the container.
     * @param int - the output debug flag to 
     *              maintain compatibility w/ the API.
     *
     * @return string the raw html output.
     */
    function render($indent_level=1, $output_debug=0) {
        $table = html_table( $this->get_width(), 0,
                             $this->get_cellspacing(),
                             $this->get_cellpadding(),
                             $this->get_align());
        $table->set_class( "infotable" );
        
        if ($this->get_title() != NULL) {
        	$table->add( $this->_build_title() );
        }

        $row = $this->_build_header();
        if ( $row != NULL ) {
            $table->add_row( $row );
        }

        //now go thru the rows of data
        //and add them
        $row_count = 1;
        foreach( $this->data as $row ) {
            if ( (count($row) == 1) && is_object($row[0]) && (is_a($row[0], "TRtag") ||
                                                              is_a($row[0], "TDtag")) ) {
                $table->add_row( $row[0] );
            } else {
            	$row_count++;
                $tr = new TRtag($this->use_alt_colors($row_count));
                $cnt = count( $row );
                foreach( $row as $index => $data ) {
                    $td = $this->_build_td("", "", $index+1, $cnt );
                    $td->add( $data );
                    $tr->add( $td );
                }
                $table->add_row( $tr );
            }
        }
        return $table->render($indent_level, $output_debug);
    }


    /*****************/
    /*  Public APIs  */
    /*****************/

    /**
     * This function is used to set the column
     * header text for each column
     *
     * @param string - the title for the column
     * @param string - the alignment of the title
     */
    function add_column_header( $title, $width, $align="center") {
        $this->_headers[] = array("title" => $title,
                                  "width" => $width,
                                  "align" => $align);
    }

    /**
     * This function is used to set the column
     * header text for each column
     *
     * @param int - the position of the header
     * @param string - the title for the column
     * @param string - the alignment of the title
     */
    function set_column_header( $header, $title, $width, $align="center") {
        $this->_headers[$header] = array("title" => $title,
                                         "width" => $width,
                                         "align" => $align);
    }

    /**
     * This function is used to add a row to the table
     *
     * @param mixed - n number of items to push
     */
    function add_row() {
        $num_args = func_num_args();
        $arr = array();
        for ( $i=0;$i<$num_args;$i++ ) {
            $arr[] = func_get_arg($i);
        }
        $this->data[] = $arr;
    }


    /**
     * This sets the cellpadding attribute
     * for this object.
     *
     * @param int - the cellpadding value
     */
    function set_cellpadding( $pad=0 ) {
        $this->_cellpadding = $pad;
    }

    /**
     * This gets the current value of the
     * cellpadding
     *
     * @return int - the current cellpadding
     */
    function get_cellpadding() {
        return $this->_cellpadding;
    }

    /**
     * This sets the cellspacing attribute
     * for this object.
     *
     * @param int - the cellspacing value
     */
    function set_cellspacing( $spacing=0 ) {
        $this->_cellspacing = $spacing;
    }

    /**
     * This gets the current value of the
     * cellspacing
     *
     * @return int - the current cellspacing
     */
    function get_cellspacing() {
        return $this->_cellspacing;
    }

    /**
     * this function lets you change the
     * text alignment of the text in the title
     *
     * @param string - the alignment.
     */
    function set_title_text_align( $align="left" ) {
        $this->_title_text_align = $align;
    }

    /**
     * this function lets gets the
     * default css class for the title
     *
     * @return string - the css class to use
     */
    function get_title_text_align( ) {
        return $this->_title_text_align;
    }

    /**
     * this function sets the flag to tell
     * the object to render (or not) the 
     * vertical cell borders
     *
     * @param boolean 
     */
    function set_vertical_cellborder( $flag=TRUE ) {
        $this->_show_vertical_cellborder = $flag;
    }

    /**
     * this function lets gets the
     * default css class for the title
     *
     * @return string - the css class to use
     */
    function get_vertical_cellborder( ) {
        return $this->_show_vertical_cellborder;
    }


    /**
     * This method is used to set the flag to
     * allow showing of the internal borders or not.
     * 
     * @param boolean
     * @return none
     */
    function set_show_cellborders( $flag=true ) {
        $this->_show_cellborders = $flag;
    }
    
   /**
    * This function allows the user to alternate colors
    * on different rows
    *
    * @param int current row number
    * @return array/none Either returns array with attribute or nothing
    */ 
    function use_alt_colors($row) {
    	return (($row % 2) && 
    			($this->_alt_color_flag)) ? array('class'=>"altcolor") : '';	
    }

   /**
    * This function sets the alternate_color flag
    *
    * @param boolean
    */
   	function set_alt_color_flag( $flag=true) {
   		$this->_alt_color_flag = $flag;
   	}

    /**
     * This function sets css class of the title
     *
     * @param string - the css class to use
     */
    function set_title_css( $class) {
        $this->_title_css_class = $class;
    }
   	
    
    /******************/
    /*  Private APIs  */
    /******************/


    /**
     * This function builds the title
     * container
     *
     * @return CAPTIONtag object
     */
    function _build_title() {
        $caption =  new CAPTIONtag( array("style" => "text-align:".$this->get_title_text_align().";",
                                          "class" => "title"), 
                                    $this->title );
        return $caption;
    }

    /**
     * This function builds the table header
     *
     * @return TRtag object
     */
    function _build_header() {
        $tr = new TRtag;

        $cnt = count( $this->_headers );
        if ( $cnt > 0 ) {
            $cur_col = 1;
            foreach( $this->_headers as $header ) {
                $td = $this->_build_td( $header["width"], $header["align"], $cur_col, $cnt);
                if ( $cur_col == $cnt ) {
                    $class = "headerlast";              
                } else if ($this->_show_cellborders) {
                    $class = "header";
                } else {
                    $class = "headernovertical";
                }
                $td->set_class( $class );
                $td->push( $header["title"] );
                $tr->push( $td );
                $cur_col++;
            }
            return $tr;
        } else {
            return NULL;
        }
    }

    /**
     * this function builds a TD tag with the border styles 
     * set appropriatly
     *
     * @param int - the width
     * @param string - the alignment
     * @param int - the current col #
     * @param int - the max cols	 
     * @return TDtag object.
     */
    function _build_td( $width="", $align="", $col_num, $total_cols ) {
        //first we have to build the style string
        $style = "";

        if ( $width != "" ) {
            $style = "width:";
            if ( substr($width, -1) != "%" ) {
                $style .= $width."px;";     
            } else {
                $style .= $width.";";
            }
        }

        if ( $align != "" ) {
            //add the alignment
            $style .= "text-align:".$align.";";
        }

        //now determine the bordering
        if ($this->_show_cellborders) {
            if ( $col_num != $total_cols &&
                 $this->get_vertical_cellborder() ) {
                $class = "contentvertical";
            } else {
                $class = "contentnovertical";
            }
            $attributes = array("class" => $class, "style" => $style);
        } else if ($style != '') {
            $attributes = array("style" => $style);
	} else
            $attributes = array() ;
        
        return new TDtag( $attributes );
    }
}

/**
 * This class defines the css used by the 
 * FooterNav Object.
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib 
 */
class InfoTableCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry(".infotable", NULL,
                         array("margin" => "0px 0px 0px 0px",
                               "font-family" => "arial, helvetica, sans-serif",
                               "font-size" => "10pt",
                               "border-left" => "1px solid #999999",
                               "border-right" => "1px solid #999999",
                               "border-bottom" => "1px solid #999999") );

        $this->add_entry(".infotable", "caption.title",
                         array("font-size" => "10pt",
                               "font-weight" => "bold",
                               "padding" => "2px 5px 2px 5px",
                               "color" => "#FFFFFF",
                               "background-color" => "#999999",
                               "border-top" => "1px solid #999999",
                               "border-left" => "1px solid #999999",
                               "border-right" => "1px solid #999999"));

        $this->add_entry(".infotable", "td.header",
                         array("font-weight" => "bold",
                               "border-top" => "1px solid #999999",
                               "border-right" => "1px solid #999999"));

        $this->add_entry(".infotable", "td.headerlast",
                         array("font-weight" => "bold",
                               "border-top" => "1px solid #999999"));

        $this->add_entry(".infotable", "td.headernovertical",
                         array("font-weight" => "bold",
                               "border-top" => "1px solid #999999"));

        $this->add_entry(".infotable", "td.headerlast",
                         array("font-weight" => "bold",
                               "border-top" => "1px solid #999999"));

        $this->add_entry(".infotable", "td.contentnovertical",
                         array("border-top" => "1px solid #999999"));

        $this->add_entry(".infotable", "td.contentvertical",
                         array("border-top" => "1px solid #999999",
                               "border-right" => "1px solid #999999"));

		$this->add_entry(".infotable", "tr.altcolor",
                         array("background-color" => "#DDDDDD"));
    }   
}
?>
