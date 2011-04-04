<?php
/**
 * This file holds the base Graph class for doing
 * SVG graphs
 *
 * $Id: SVGGraph.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage SVG
 */ 

/**
 * This is the base Graph class for doing
 * SVG graphs
 *
 * $Id: SVGGraph.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage SVG
 */
class SVGGraph extends BaseWidget {


    /**
     * This array holds various
     * config options for this graph
     */
    var $_options = array("title" => "",
                          "title_style" => "font-size:20px;font-weight:bold;font-family: geneva, trebuchet ms",
                          "width" => 100,
                          "height" => 100,
                          "left_margin" => 5,
                          "right_margin" => 0,
                          "top_margin" => 20,
                          "bottom_margin" => 0,
                          "title_font_width" => 10,
                          "title_font_height" => 20,
                          "axis_font_width" => 5,
                          "axis_font_height" => 8,
                          "axis_label_font_width" => 12,
                          "axis_label_font_height" => 12);


    /**
     * Various calculated image properties
     *
     */
    var $_draw = array();


    function SVGGraph($title, $width, $height) {
        $this->set_title($title);
        $this->set_width($width);
        $this->set_height($height);
    }


    function render($indent_level=0, $output_debug=0) {
        //do any data parsing/munging/calculating
        $this->_prepare_data();

        $container = container();
        $container->add( $this->_build_titles() );
        $container->add( $this->_build_graph() );
        return $container->render($indent_level, $output_debug);
    }

    /**
     * This is a stub meant to provide a means
     * for doing any data parsing/munging
     * prior to actually building the svg
     * for the graph output.
     *
     */
    function _prepare_data() {
        return NULL;
    }


    /**
     * This is a stub for building the title(s)
     * for the graph
     *
     * @return Container
     */
    function _build_titles() {
        return $this->_build_title();
    }

    /**
     * This is a stub that the child class
     * must override to build the actual
     * graph
     *
     * @return Container
     */
    function _build_graph() {
        return NULL;
    }


    /****************************/
    /*    options functions     */
    /****************************/


    /**
     * This function is used to set
     * a particular option for the
     * graph
     *
     * @param string - the option name
     * @param mixed - the value
     */
    function set_option( $name, $value ) {
        $this->_options[$name] = $value;
    }

    /**
     * This function retuns the value
     * of 1 option
     *
     * @param string - the option name
     * @return mixed - the value
     */
    function get_option($name) {
        return $this->_options[$name];
    }

    /**
     * This returns the array of ALL
     * of the options for this graph
     *
     * @return array
     */
    function get_options() {
        return $this->_options;
    }


    /**
     * This method sets the title for
     * the graph
     *
     * @param string - the graph's title     
     */
    function set_title($title) {
        $this->_options["title"] = $title;
    }

    /**
     * This method sets the title for
     * the graph
     *
     * @param string - the graph's title     
     */
    function set_title_style($style) {
        $this->_options["title_style"] = $style;
    }

    /**
     * This method sets the width
     * of the graph
     *
     * @param int - the width
     */
    function set_width($width) {
        $this->_options["width"] = $width;
    }

    /**
     * This method sets the height
     * of the graph
     *
     * @param int - the height
     */
    function set_height($height) {
        $this->_options["height"] = $height;
    }
    
    /**
     * This method sets the width
     * of font in pixels for the 
     * Graph Title.   
     *
     * @param int - the width
     */
    function set_title_font_width($width) {
        $this->_options["title_font_width"] = $width;
    }

    /**
     * This method sets the height
     * of font in pixels for the 
     * Graph Title. 
     *
     * @param int - the height
     */
    function set_title_font_height($height) {
        $this->_options["title_font_height"] = $height;
    }


    /**
     * This method sets the width
     * of font used in calculating
     * the x and y axis point fonts.
     *
     * @param int - the width
     */
    function set_axis_font_width($width) {
        $this->_options["axis_font_width"] = $width;
    }

    /**
     * This method sets the height
     * of font used in calculating
     * the x and y axis point fonts.
     *
     * @param int - the height
     */
    function set_axis_font_height($height) {
        $this->_options["axis_font_height"] = $height;
    }


    /**
     * This function will format the axis label
     *
     * @param string - the number
     * @return string - the formated #
     */
    function format_label($number) {
        return sprintf("%.2f",$number);
    }


    /**
     * This method builds the text title area
     * that lives on top of the graph
     *
     * @return TEXTsvgtag
     */
    function _build_title() {
        $x = ($this->_draw["x2"] - $this->_draw["x1"])/2 -
            ((strlen($this->_options["title"])*$this->_options["title_font_width"])/4);
        $text = svg_text($x,20);
        $text->set_style($this->_options["title_style"]);
        $text->add( $this->_options["title"] );
        $text->set_collapse();
        return $text;
    }    
}
?>
