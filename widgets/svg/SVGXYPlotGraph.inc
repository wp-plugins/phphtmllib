<?php
/**
 * This file holds the base Graph class for doing
 * graphs on an XY coordinate system.
 *
 * $Id: SVGXYPlotGraph.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage SVG
 */

/**
 * we need the SVGGraph class
 */
require_once(PHPHTMLLIB_ABSPATH . "/widgets/svg/SVGXYGraph.inc");

/**
 * This is the base Graph class for doing XY coordinate
 * system based graphs in SVG.
 *
 * $Id: SVGXYPlotGraph.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage SVG
 */
class SVGXYPlotGraph extends SVGXYGraph {    

    function SVGXYPlotGraph($title, $width, $height) {

        //set up the options.
        $this->_add_options();

        //turn these on by default
        $this->set_grid_line_flag("x", TRUE);
        $this->set_grid_line_flag("y", TRUE);

        $this->set_title($title);
        $this->set_width($width);
        $this->set_height($height);
    }

    /**
     * This enables you to add another line 
     * to the graph
     *
     * @param string - the x coordinates
     * @param string - the y coordinates
     * @param string - the color for the line
     */
    function add_point($x, $y, $color="red") {
        $this->add_x_values($x);
        $this->add_y_values($y);
        $this->_colors[] = $color;
    }


    /**
     * This function does the work of
     * building the graph itself
     *
     * @return Container
     */
    function graph_data() {
        $container = container();

        $num_lines = count($this->_x_data);
        for( $i=0; $i<=$num_lines-1; $i++) {
            $container->add( $this->_build_point($this->_x_data[$i],
                                                 $this->_y_data[$i],
                                                 $this->_colors[$i]) );
        }        
        
        return $container;
    }


    function _build_point( $x, $y, $color ) {
        return svg_circle( $x, $y, 2, $color, $color);
    }
}
?>
