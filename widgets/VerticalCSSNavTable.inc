<?php

/**
 * This contains the VerticalCSSNavTable widget
 *
 * $Id: VerticalCSSNavTable.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */

/**
 * must have the BaseWidget
 */
require_once(PHPHTMLLIB_ABSPATH . "/widgets/BaseWidget.inc");

/**
 * This class builds a nice table 
 * that conains clickable cells. 
 *
 *  ---------------------
 *  |      TITLE        |
 *  ---------------------
 *  |     SUBTITLE      |
 *  ---------------------
 *  |    link 1         |
 *  ---------------------
 *  |    link 2         |
 *  ---------------------
 *
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class VerticalCSSNavTable extends BaseWidget {

	/**
	 * the subtitle if any
	 *
	 * @var string
	 */
	var $_subtitle = "";


	/**
	 * Holds the outer table object
	 *
	 * @var TABLEtag object
	 */
	var $_table = NULL;


    /**
     * Constructor for this class
     * It just sets the width for the
     * widget.
     * 
     * @param int $width - the width of the widget
     */
    function VerticalCSSNavTable($title, $subtitle="", $width="100%" ) {
		$this->set_title( $title );
		$this->set_subtitle( $subtitle );
		$this->set_width( $width );
    }

    /**
     * function that will render the widget.
	 *
	 * @param int - the indentation level for 
	 *              the container.
	 * @param int - the output debug flag to 
	 *              maintain compatibility w/ the API.
	 *
	 * @return string the raw html output.
     */
    function render( $indent_level=1, $output_debug=0) {

		$this->_table = html_table( $this->get_width() );
		$this->_table->set_class("verticalcssnav");

		$this->_build_title();		

		$this->_build_links();		
		
        return $this->_table->render( $indent_level, $output_debug );
    }


	/**
	 * This sets the subtitle
	 *
	 * @param string - the subtitle
	 */
	function set_subtitle( $subtitle ) {
		$this->_subtitle = $subtitle;
	}

	/**
	 * This function returns the current
	 * subtitle.
	 *
	 * @return string - the subtitle
	 */
	function get_subtitle() {
		return $this->_subtitle;
	}


    //functions for adding/updating data

    /**
     * this function adds a clickable link.
     * It automatically adds the link based on $url,
     * with $text as the viewable text.
     *
     * @param string - the url for the link
     * @param string - the link text
     * @param string - the title text
	 * @param string - the link target
     */
    function add($url, $text, $title="", $target="") {
        array_push($this->data, array("type"=>"url", "url"=>$url, 
                                      "text"=>$text, "title"=>$title,
									  "target"=>$target));
    }

    /**
     * this adds a text item in the nav
     * 
     * @param string - the text to display
     */
    function add_text( $text ) {
        array_push($this->data, array( "type"=>"text", "text"=>$text ));
    }


	/**
	 * This function builds the title tr
	 *
	 */
	function _build_title() {
		$caption = html_caption( $this->get_title() );
        $this->_table->add( $caption );
	}

	/**
	 * This function builds the subtitle
	 * if needed.
	 */
	function _build_subtitle() {

		$subtitle = $this->get_subtitle();
		if ($subtitle != "") {
			$div = html_div();
			$div->set_class( "subtitle" );
			$div->add( $this->get_subtitle() );
			return $div;
		} else {
			return NULL;
		}
    }


	/**
	 * This function is used to build the links
	 * to click on
	 *
	 * @return Container
	 */
	function _build_links() {
		$container = container();

		$container->push( $this->_build_subtitle() );
		
        foreach( $this->data as $nav ) {
			switch ($nav["type"]) {
			case 'url':
				$a = html_a($nav["url"], $nav["text"], "", $nav["target"], $nav["title"]);
				$a->set_class("navurl");
				$container->add( $a );
				break;
			case "text":
				$div = html_div("",$nav["text"]);
				
				$container->add($div);
				break;
			}
			
		}

		$this->_table->add_row( $container );
		
		return $container;
	}

}

/**
 * This class defines the css used by the 
 * VerticalCSSNavTable Object.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib 
 */
class VerticalCSSNavTableCSS extends CSSBuilder {

	function user_setup() {
		$this->add_entry(".verticalcssnav", NULL,
						 array("vertical-align" => "top",
							   "font-family" => "arial, helvetica, sans-serif") );

		$this->add_entry(".verticalcssnav", "caption",
						 array("font-size" => "10pt",
							   "font-weight" => "bold",
                               "color" => "#FFFFFF",
							   "background-color" => "#999999",
							   "border" => "1px solid #999999"));

		$this->add_entry(".verticalcssnav", "div",
						 array("font-size" => "8pt",
							   "color" => "#000000",
							   "padding" => "2px 4px 2px 4px",
							   "border-right" => "1px solid #999999",
							   "border-left" => "1px solid #999999",
							   "border-bottom" => "1px solid #999999"));

		$this->add_entry(".verticalcssnav", "div.subtitle",
						 array("font-size" => "10pt",
							   "font-weight" => "bold",
							   "color" => "#777777",
							   "background-color" => "#eeeeee",
                               "text-align" => "center"));

		$this->add_entry(".verticalcssnav", "a.navurl:active,a.navurl:link,a.navurl:visited",
						 array("display" => "block",
							   "font-family" => "arial, verdana, helvetica, sans-serif",
							   "font-size" => "10pt",
                               "padding" => "2px 4px 2px 4px",
							   "text-decoration" => "none",
							   "color" => "#000000",
							   "background-color" => "#FFFFFF",
							   "border-bottom" => "1px solid #999999",
							   "border-right" => "1px solid #999999",
							   "border-left" => "1px solid #999999"));

		$this->add_entry(".verticalcssnav", "a.navurl:hover",
						 array("color" => "#000000",
							   "background-color" => "#eeeeee"));

	
	}	
}
?>
