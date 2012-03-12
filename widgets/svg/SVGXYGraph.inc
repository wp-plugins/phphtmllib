<?php
/**
 * This file holds the base Graph class for doing
 * graphs on an XY coordinate system.
 *
 * $Id: SVGXYGraph.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage SVG
 */

/**
 * we need the SVGGraph class
 */
require_once(PHPHTMLLIB_ABSPATH . "/widgets/svg/SVGGraph.inc");

/**
 * This is the base Graph class for doing XY coordinate
 * system based graphs in SVG.
 *
 * $Id: SVGXYGraph.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage SVG
 */
class SVGXYGraph extends SVGGraph {

    /**
     * this holds the X axis data
     */
    var $_x_data = array();
    var $_min_x = 0;
    var $_max_x = 0;

    /**
     * this holds the Y axis data
     */
    var $_y_data = array();
    var $_min_y = 0;
    var $_max_y = 0;
    
    /**
     * holds the colors for each of 
     * the lines
     */
    var $_colors = array();


    function SVGXYGraph($title, $width, $height) {

        //set up the options.
        $this->_add_options();        

        $this->set_title($title);
        $this->set_width($width);
        $this->set_height($height);
    }


    /**
     * This is a stub for building the title(s)
     * for the graph
     *
     * @return Container
     */
    function _build_titles() {
        $container = container(
            $this->_build_title(),
            $this->_x_axis_title(),
            $this->_y_axis_title());

        return $container;
    }


    /**
     * This function does the work of
     * building the graph itself
     *
     * @return Container
     */
    function _build_graph() {
        $container = container();

        //now build the background gradient?
        $container->add( $this->_background() );

        //now render the lines
        $container->add( $this->_build_x_axis() );
        $container->add( $this->_build_y_axis() );

        $container->add( $this->graph_data() );
        return $container;
    }

    /**
     * this method adds our own options that
     * are different from the parent class
     */
    function _add_options() {

        //the style for the text for the
        //x/y/z axis titles
        $this->set_option("axis_title_style",
                          "font-size:12px;font-weight:bold;".
                          "font-family: geneva, trebuchet ms");

        $this->set_option("graph_background", "#EEEEEE");

        //the fill color for the axis grid lines
        $this->set_option("axis_grid_line_color", "#999999");
        $this->set_option("border_color", "#000000");

        //the title for the axis
        $this->set_option("x_title", "");
        $this->set_option("y_title", "");

        //the # of divisions/lines for the x axis
        $this->set_option("x_grid_lines", 0);
        $this->set_option("x_grid_lines_on", FALSE);
        $this->set_option("y_grid_lines", 0);
        $this->set_option("y_grid_lines_on", FALSE);
        
        $this->set_option("x_tickmark_length", 3);
        $this->set_option("y_tickmark_length", 3);

        $this->set_option("x1_margin", 0);
        $this->set_option("x2_margin", 0);
        $this->set_option("y1_margin", 5);
        $this->set_option("y2_margin", 0);
    }

    /**
     * This function is used to set the
     * title for the X Axis
     *
     * @param string - the title
     */
    function set_x_title( $title ) {
        $this->set_option("x_title", $title);
    }

    /**
     * This function is used to set the
     * title for the Y Axis
     *
     * @param string - the title
     */
    function set_y_title( $title ) {
        $this->set_option("y_title", $title);
    }

    /**
     * This function is used to add
     * a new set of x values for the graph.
     *
     * NOTE: this must be a comma delimited
     *       list of values.
     *
     * @param string - the values
     */
    function add_x_values($x_values) {
        $this->_x_data[] = $x_values;
    }

    /**
     * This function is used to add
     * a new set of y values for the graph.
     *
     * NOTE: this must be a comma delimited
     *       list of values.
     *
     * @param string - the values
     */
    function add_y_values($y_values) {
        $this->_y_data[] = $y_values;
    }


    /**
     * This enables/disables the rendering
     * of the grid lines for an axis
     *
     * @param string - the axis, x/y only
     * @param boolean - TRUE = Enabled
     */
    function set_grid_line_flag($axis, $flag=TRUE) {
        $axis = strtolower($axis);
        switch ($axis) {
        case "x":
        case "y":
            $this->set_option($axis."_grid_lines_on", $flag);
            break;
        default:
            break;
        }
    }

    /**
     * This is used to set how many grid lines
     * to draw for an axis
     *
     * @param string - the axis, x/y only
     * @param int - how many lines
     */
    function set_axis_grid_points($axis, $points) {
        $axis = strtolower($axis);
        switch ($axis) {
        case "x":
        case "y":
            $this->set_option($axis."_grid_lines",$points);
            break;
        default:
            break;
        }
    }

    /**
     * This allows you to set the color of the
     * axis grid lines
     *
     * @param string - the color name
     */
    function set_grid_line_color( $color ) {
        $this->set_option("axis_grid_line_color", $color);
    }
    
    /**
     * We need this to calculate the min,max values for
     * both all x points and all y data points, so we
     * can scale the graph correctly
     */
    function _prepare_data() {
        $_min_x = array();
        $_min_y = array();

        $_max_x = array();
        $_max_y = array();

        $num_datas = count($this->_x_data);

        for( $i=0; $i<=$num_datas-1; $i++) {
            $x_data = explode(",", $this->_x_data[$i] );
            $y_data = explode(",", $this->_y_data[$i] );
            $_min_x[] = min($x_data);
            $_min_y[] = min($y_data);
            $_max_x[] = max($x_data);
            $_max_y[] = max($y_data);
        }
        
        $this->_min_x = min($_min_x);
        $this->_min_y = min($_min_y);

        $this->_max_x = max($_max_x);
        $this->_max_y = max($_max_y);
        
        // calculate distance from the left border to the drawing area
        $longest_number = @max($this->y_data);

        $this->_draw["x1"] = 2*$this->_options["axis_label_font_height"] +
                             (strlen($this->format_label($this->_max_y))+3)*$this->_options["axis_font_width"];
        
        $this->_draw["x2"] = $this->_options["width"]-1;

        $this->_draw["y1"] = $this->_options["title_font_height"] + $this->_options["top_margin"];

        $this->_draw["y2"] = $this->_options["height"] - (2*$this->_options["title_font_height"] + $this->_options["top_margin"]) +
                             3*$this->_options["axis_font_height"];

        $this->_draw["draw_width"] = $this->_draw["x2"]  - $this->_draw["x1"];
        $this->_draw["draw_height"] = $this->_draw["y2"]  - $this->_draw["y1"];

        // how many ticks will fit
        if (!$this->_options["y_grid_lines"]) {
            $this->_options["y_grid_lines"] = round(($this->_draw["draw_height"])/($this->_options["axis_font_height"]+10));
        }

        if (!$this->_options["x_grid_lines"]) {
            $this->_options["x_grid_lines"] = round(($this->_draw["draw_width"])/($this->_options["axis_font_width"]+10));
        }
        

        //calculate the distance between lines
        $this->_draw["x_line_space"] = ($this->_draw["draw_width"]-2)/$this->_options["x_grid_lines"];
        $this->_draw["y_line_space"] = ($this->_draw["draw_height"]-2)/$this->_options["y_grid_lines"];

    }

    /**
     * This method builds the text title area
     * that lives in the X axis
     *
     * @return TEXTsvgtag
     */
    function _x_axis_title() {
        $x = $this->_draw["x2"] - (strlen($this->_options["x_title"])*$this->_options["axis_label_font_width"])/2;
        $y = $this->_options["height"]-$this->_options["bottom_margin"];

        $text = svg_text($x,$y);
        $text->set_style($this->_options["axis_title_style"]);
        $text->add( $this->_options["x_title"] );
        $text->set_collapse();
        return $text;
    }
    
    /**
     * This method builds the text title area
     * that lives in the X axis
     *
     * @return TEXTsvgtag
     */
    function _y_axis_title() {
        $x = 10+$this->_options["left_margin"];
        $y = $this->_draw["y1"] + (strlen($this->_options["y_title"])*$this->_options["axis_label_font_width"])/2;
        $text = svg_text($x,$y);
        $text->set_style($this->_options["axis_title_style"]);
        $text->set_tag_attribute("transform", "rotate(270,$x,$y)");
        $text->add( $this->_options["y_title"] );
        $text->set_collapse();
        return $text;
    }


    function _background() {
        
        $rect = svg_rect($this->_draw["x1"],$this->_draw["y1"],
                         $this->_draw["draw_width"],$this->_draw["draw_height"], 
                         $this->_options["graph_background"], "black", 2);
        $container = container( $rect );

        return $container;
    }

    /**
     * This function returns the pixel positions
     * of a data point
     *
     * @param float data point
     *
     * @return int position in pixels
     */
    function get_y_position($y) {
        $pos = ($this->_draw["y2"] - $this->_options["y2_margin"]) -  ($y - $this->_min_y) *
               $this->_draw["draw_height"] / ($this->_max_y - $this->_min_y);

        return $pos;
    }


    /**
     * This function returns the pixel positions
     * of a data point
     *
     * @param float data point
     *
     * @return int position in pixels
     */
    function get_x_position($x) {
        $pos = ($this->_draw["x1"] + $this->_options["x1_margin"]) + ($x - $this->_min_x) *
               $this->_draw["draw_width"] / ($this->_max_x - $this->_min_x);

        return $pos;
    }

    /**
     * This function builds the X axis
     * and its measurement lines/marks
     *
     * @return Container
     */
    function _build_x_axis() {

        // what is the tick step
        $tick_step = round(($this->_max_x - $this->_min_x)/$this->_options["x_grid_lines"]);
        if ($tick_step<1) $tick_step=1;

        $container = container();

        $x = $this->_min_x;
        while ($x <= $this->_max_x) {
            $x_pos = $this->get_x_position($x);
            $y_pos = $this->_draw["y2"] - $this->_options["x_tickmark_length"];

            if ($x > $this->_min_x) {
                $tick = svg_line($x_pos, $this->_draw["y2"]+1,
                                 $x_pos, $this->_draw["y2"] + $this->_options["x_tickmark_length"]+1,
                                 $this->_options["border_color"], 1);

                $line = svg_line($x_pos, $this->_draw["y2"]-1,
                                 $x_pos, $this->_draw["y1"]+1,
                                 $this->_options["axis_grid_line_color"], 1);

                $container->add( $tick, $line );

            }

            $value = $this->format_label($x);

            $text = svg_text($x_pos - (strlen($value)*$this->_options["axis_font_width"]/2),
                             $this->_draw["y2"] + $this->_options["x_tickmark_length"] +
                             $this->_options["axis_font_height"]*2);
            $text->set_collapse();
            $text->set_style( "font-size:9;font-family: arial, geneva, trebuchet ms" );
            $text->add( $value );

            $container->add( $text );
            
            $x += $tick_step;

        }

        $rect = svg_rect($this->_draw["x1"],$this->_draw["y1"],
                         $this->_draw["draw_width"],$this->_draw["draw_height"], 
                         "none", "black", 2);
        $container->add( $rect );

        return $container;
    }

    /**
     * This function builds the Y axis
     * and its measurement lines/marks
     *
     * @return Container
     */
    function _build_y_axis() {

        // what is the tick step
        $tick_step = round(($this->_max_y - $this->_min_y)/$this->_options["y_grid_lines"]);
        if ($tick_step<1) $tick_step=1;
        
        $container = container();

        $y = $this->_min_y;
        while( $y <= $this->_max_y ) {
            $y_pos = $this->get_y_position($y);
            $x_pos = $this->_draw["x1"] - $this->_options["y_tickmark_length"];
            
            if ($y > $this->_min_y) {
                $tick = svg_line($this->_draw["x1"] - $this->_options["y_tickmark_length"],
                                 $y_pos, $this->_draw["x1"] - 1, $y_pos,
                                 $this->_options["border_color"],1);

                $line = svg_line($this->_draw["x1"] + 1, $y_pos, 
                                 $this->_draw["x2"] - 1, $y_pos,
                                 $this->_options["axis_grid_line_color"],1);

                $container->add( $tick, $line );
            }

            $value = $this->format_label($y);

            $text = svg_text($x_pos - (strlen($value) * $this->_options["axis_font_width"]) - 2,
                             $y_pos + $this->_options["axis_font_height"]/2);
            $text->set_collapse();
            $text->set_style( "font-size:9;font-family: arial, geneva, trebuchet ms" );
            $text->add( $value );

            $container->add( $text );

            $y += $tick_step;
        }

        return $container;
    }

     
}
?>
