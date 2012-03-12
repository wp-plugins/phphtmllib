<?php
/**
 * This file holds the base Graph class for doing
 * graphs on an XY coordinate system.
 *
 * $Id: SVGXYLineGraph.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage SVG
 */

/**
 * we need the SVGGraph class
 */
require_once(PHPHTMLLIB_ABSPATH . "/widgets/svg/SVGXYPlotGraph.inc");

/**
 * This is the base Graph class for doing XY coordinate
 * system based graphs in SVG.
 *
 * $Id: SVGXYLineGraph.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage SVG
 */
class SVGXYLineGraph extends SVGXYPlotGraph {


    /**
     * holds the colors for each of 
     * the lines
     */
    var $_line_colors = array();

    /**
     * This enables you to add another line 
     * to the graph
     *
     * @param string - the x coordinates
     * @param string - the y coordinates
     * @param string - the color for the line
     */
    function add_line($x_values, $y_values, $color="red") {
        $this->add_x_values($x_values);
        $this->add_y_values($y_values);
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
            $container->add( $this->_build_line($this->_x_data[$i],
                                                $this->_y_data[$i],
                                                $this->_colors[$i]) );
        }
        return $container;
    }


    function _build_line($x_data, $y_data, $color) {
        $x_data = explode(",", $x_data);
        $y_data = explode(",", $y_data);
        $num_points = count($y_data);

        $container = container();
        $x0 = $this->_draw["x1"]; 
        $y0 = $this->_draw["y2"];

        for($i=0; $i<$num_points-1; $i++) {
            $x1=$x0+($x_data[$i]-$this->_min_x)*$this->_draw["draw_width"]/($this->_max_x-$this->_min_x);
            $x2=$x0+($x_data[$i+1]-$this->_min_x)*$this->_draw["draw_width"]/($this->_max_x-$this->_min_x);

            $y1=$y0-($y_data[$i]-$this->_min_y)*$this->_draw["draw_height"]/($this->_max_y-$this->_min_y);
            $y2=$y0-($y_data[$i+1]-$this->_min_y)*$this->_draw["draw_height"]/($this->_max_y-$this->_min_y);

            $container->add( svg_line($x1, $y1, $x2, $y2, $color, 2) );

            $container->add( $this->_build_point($x1, $y1, 2, $color, $color) );
            $container->add( $this->_build_point($x2, $y2, 2, $color, $color) );

        }

        return $container;
    }
     
}

?>
