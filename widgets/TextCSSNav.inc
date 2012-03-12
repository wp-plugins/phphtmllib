<?php

/**
 * This contains the TextNav widget
 *
 * $Id: TextCSSNav.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
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
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 */
class TextCSSNav extends BaseWidget {

    /**
     * Flag to tell us that we can
     * highlight (css) the selected
     * link.
     *
     * This is off by default
     */
    var $_highlight_selected = FALSE;

    /**
     * Holds which one is auto selected
     *
     */
    var $_selected = 0;

    /**
     * the prefix for the query string var
     * so we can have multiple widgets
     * on the same page and have them 
     * operate independantly
     */
    var $_query_prefix = "";


    /**
     * Constructor for this class
     * It just sets the width for the
     * widget.
     * 
     * @param int $width - the width of the widget
     */
    function TextCSSNav($highlight_selected=FALSE) {
        $this->_highlight_selected = $highlight_selected;       
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
        $this->_selected = @$_REQUEST[$this->_query_prefix."textcssnavselected"];
        $div = html_div("textnav", $this->_build_links());
        return $div->render( $indent_level, $output_debug );
    }


    /**
     * This method is used to set the prefix for
     * the widget so someone can have multiple
     * widgets on the same page and have them 
     * operate independantly
     *
     * @param string - the prefix for the query var
     */
    function set_prefix( $prefix ) {
        $this->_query_prefix = $prefix;
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
    function add($url, $text, $title="", $target="", $selected=FALSE) {
        array_push($this->data, array("type"=>"url", "url"=>$url, 
                                      "text"=>$text, "title"=>$title,
                                      "target"=>$target,
                                      "selected"=> $selected));
    }

    /**
     * depricated version of add()
     *
     * @deprecated - use add() instead
     */
    function push($url, $text, $title="", $target="") {
        $this->add($url, $text, $title);
    }

    /**
     * This lets you add a blank entry
     * between 2 links
     *
     * @param int - the # of blank lines to insert
     */
    function add_blank( $num = 1 ) {
        for ( $x=1; $x<=$num; $x++ )
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
     * This function is used to build the links
     * to click on
     *
     * @return Container
     */
    function _build_links() {
        $container = container();
        $container->set_collapse();

        $is_first = TRUE;
        $cnt = 1;
        foreach( $this->data as $nav ) {
            switch ( $nav["type"] ) {
            case 'url':

                $is_selected = $this->_highlight_selected && ($this->_selected == $cnt || $nav["selected"]);
                $class = $is_selected ? "selected" : "";
                if ( $is_first ) {
                    $class .= "first";
                }
                if ( !$is_selected && !$is_first ) {
                    $class = NULL;
                }

                $obj = $this->_build_link( $nav, $class, $cnt );
                $is_first = FALSE;
                $cnt++;
                break;

            case "blank":
                $obj = "&nbsp;";
                break;

            case 'text':
                $obj = $nav['text'];
                break;
            }



            $container->push( $obj );
        }

        return $container;
    }


    /**
     * This method actually builds an individual link
     * 
     * @param array the link information
     * @param the css class to use
     * @return Atag object
     */
    function _build_link( $nav, $class, $cnt ) {
        $url = $nav["url"];
        if ( $this->_highlight_selected ) {
            if ( !strstr($url, "?") ) {
                $url .= "?";
            }

            $url .= "&".$this->_query_prefix."textcssnavselected=".$cnt;
        }
        $link = html_a(htmlentities($url), $nav["text"], "normal", $nav["target"], $nav["title"]);
        if ( !is_null($class) ) {
            $link->set_class( $class );
        }

        return $link;
    }
}

/**
 * This class defines the css used by the 
 * FooterNav Object.
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib 
 */
class TextCSSNavCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry(".textnav", "",
                         array(
                              "margin" => "0px 0px 0px 0px",
                              "padding" => "3px 0px 0px 0px",
                              "height" => "16px",
                              "color" => "#FFFFFF",
                              "font-family" => "sans-serif",
                              "font-size" => "11px",
                              "font-weight" => "bold",
                              ) );

        $this->add_entry(".textnav", "a.normal,a.normal:visited,a.normal:active",
                         array("font-family" => "sans-serif",
                               "text-decoration" => "none",
                               "color" => "#FFFFFF",
                               "background-color" => "#999999",
                               "padding" => "2px 4px 2px 4px",
                               "border-right" => "1px solid #828282",
                               "border-top" => "1px solid #828282",
                               "border-bottom" => "1px solid #828282"
                              ) );

        $this->add_entry(".textnav", "a.first,a.first:visited",
                         array("font-family" => "sans-serif",
                               "text-decoration" => "none",
                               "color" => "#FFFFFF",
                               "background-color" => "#999999",
                               "padding" => "2px 4px 2px 4px",
                               "border-left" => "1px solid #828282",
                               "border-right" => "1px solid #828282",
                               "border-top" => "1px solid #828282",
                               "border-bottom" => "1px solid #828282") );

        $this->add_entry(".textnav", "a.normal:hover,a.first:hover",
                         array("color" => "#000000",
                               "background-color" => "#EEEEEE",
                               "text-decoration" => "none"));

        $this->add_entry(".textnav", "a.selected,a.selected:visited",
                         array("font-family" => "sans-serif",
                               "text-decoration" => "none",
                               "color" => "#828282",
                               "background-color" => "#EEEEEE",
                               "padding" => "2px 4px 2px 4px",
                               "border-right" => "1px solid #828282",
                               "border-top" => "1px solid #828282",
                               "border-bottom" => "1px solid #828282"
                              ) );

        $this->add_entry(".textnav", "a.selectedfirst,a.selectedfirst:visited",
                         array("font-family" => "sans-serif",
                               //"font-size" => "12px",
                               "font-weight" => "bold",
                               "text-decoration" => "none",
                               "color" => "#828282",
                               "background-color" => "#EEEEEE",
                               "padding" => "2px 4px 2px 4px",
                               "border-left" => "1px solid #828282",
                               "border-top" => "1px solid #828282",
                               "border-bottom" => "1px solid #828282") );
    }   
}
?>
