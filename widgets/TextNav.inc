<?php

/**
 * This contains the TextNav widget
 *
 * $Id: TextNav.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
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
 * This class builds a simple text navigational
 * widget.
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class TextNav extends BaseWidget {


    /**
     * Constructor for this class
     * It just sets the width for the
     * widget.
     * 
     * @param int $width - the width of the widget
     */
    function TextNav( $width = 760 ) {
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
     *
     */
    function render( $indent_level=1, $output_debug=0) {

        $table = html_table($this->width, 0, 0, 2);
        $table->set_style("border-top-color: #eeeeee;border-width: 1px;".
                          "border-left-color: #eeeeee;".
                          "border-right-color: #eeeeee;".
                          "border-bottom-color: #eeeeee;");
        $tr = new TRtag;

        $this->count = count($this->data);

        $cnt=1;
        foreach( $this->data as $nav) {
            $nav_td = $this->build_nav_td( $nav, $cnt );
            $cnt++;
            //$img_td = $this->build_img_td();
            $tr->add( $nav_td );
        }
        $table->add( $tr );

        return $table->render( $indent_level, $output_debug );
    }


    //functions for adding/updating data

    /**
     * this function adds a clickable link.
     * It automatically adds the link based on $url,
     * with $text as the viewable text.
     *
     * @param string - the url for the link
     * @param string - the link text
     * @param string - the width of the cell
	 * @param string - the target for the url
     */
    function add($url, $text, $width = 100, $target=NULL) {
        array_push($this->data, array("type"=>"url", "url"=>$url, 
                                      "text"=>$text, "width" => $width,
									  "target" => $target));
    }

    /**
     * depricated version of add()
     *
     * @deprecated - use add() instead
     */
    function push($url, $text, $width = 100) {
        $this->add($url, $text, $width);
    }

    /**
     * This lets you add a blank entry
     * between 2 links
     *
     * @param int - the # of blank lines to insert
     */
    function add_blank( $num = 1 ) {
        for ($x=1; $x<=$num; $x++)
            array_push($this->data, array( "type"=>"blank" ));
    }

    /**
     * depricated version of add_blank()
     *
     * @deprecated - use add_blank() instead
     */
    function push_blank( $num = 1 ) {
        $this->add_blank( $num );
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
     * depricated version of add_text()
     *
     * @deprecated - use add_text() instead
     */
    function push_text( $text ) {
        $this->add_text( $text );
    }


    /**
     * build a td for the link.
     *
     * @param array - the nav array entry
     * @param int - the column # this entry is
     *
     */
    function build_nav_td( $nav, $count ) {
        $td = html_td("textnavtd", "center");
        $style = "width: ".$nav["width"].";";
        
        if ($count != $this->count) {
            $style .= "border-right-color:#eeeeee;border-width:2px;";
        }
        $td->set_style( $style );
        $td->set_collapse();        

        switch ($nav['type']) {
        case 'url':
            $text = str_replace(' ', "&nbsp;", $nav['text'] );
            $content = html_a( $nav['url'], '&nbsp;' . $text . '&nbsp;', 
							   "textnavlist", $nav['target']);
            break;
        case 'blank':
            $content = "&nbsp;";
        }
        $td->add( $content );
        return $td;
    }

    /**
     * build the image seperator td
     *
     */
    function build_img_td() {

        $td = html_td("textnavdivider");
        $td->set_style("width: 1px;");
        $td->set_collapse();

        $img =  html_img(PHPHTMLLIB_RELPATH . "/widgets/images/dot_clear.gif", 1, 1, 0);
        $td->add( $img );
        return $td;
    }
}


/**
 * This class defines the css used by the 
 * TextNav Object.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib 
 */
class TextNavCSS extends CSSBuilder {

	function user_setup() {

		$this->add_entry("A.textnavlist:hover", "",
						 array("color" => "#FF0000") );

		$this->add_entry("A.textnavlist", "",
						 array("font-family" => "Arial, Helvetica, sans-serif",
							   "font-size" => "10pt",
							   "font-weight" => "bold",
							   "color" => "#FFFFFF",
							   "text-decoration" => "none"));

		$this->add_entry("TD.textnavdivider", "",
						 array("background-image" =>
							   "url('" . PHPHTMLLIB_RELPATH . "/widgets/images/dot_div_vert.gif')"));

		$this->add_entry("TD.textnavtd", "",
						 array("background-color" => "#999999"));
	
	}	
}
?>
