<?php
/**
 * $Id: ButtonPanel.inc 3556 2012-03-11 11:26:12Z mpwalsh8 $
 * 
 * a button panel for a dialog box window
 * 
 * @author Suren Markossian
 * @package phpHtmlLib
 */

/**
 * This class defines a bottom button panel for a dialog box window
 * It is a BaseWidget child with a specific css style class and border
 * This row is separated by vertical top line
 *
 * @author Suren Markosian
 * @package phpHtmlLib
 */
class ButtonPanel extends BaseWidget {

    /**
     *  Holds all the buttons
     *
     **/
    var $data;

    /**
     *
     * @param string the width of the button panel
     * @param string the alignment.
     * @return none.
     */
    function ButtonPanel($width = "100%", $align="center") {
        $this->set_align($align);
        $this->set_width($width);
    }

    /**
     * Push content onto the data object
     *
     * adds a button to the data
     * @param mixed $content - either string, or tag object.
     */
    function add() {
        $args = func_get_args();

        foreach($args as $content) {
            $this->_data[] = $content;
        }
    }


    /**
     * render the entire table.
     *
     */
    function render($indent_level=0, $output_debug=0) {

        $div =& $this->_build_wrapper();

        foreach ($this->_data as $button) {
            $div->add($button, _HTML_SPACE);
        }

        return $div->render($indent_level, $output_debug);
    }


    /**
     * Builds the outer wrapper for the panel
     * 
     * @return DIVtag object
     */
    function &_build_wrapper() {
        $div = new DIVtag(array("align"=>"center",
                                "width"=>$this->get_width(),
                                "class"=>"button_panel"
                               ));
        return $div;
    }
}


/**
 * This class defines the css used by the 
 * FooterNav Object.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib 
 */
class ButtonPanelCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry(".button_panel", NULL,
                         array("margin" => "12px 0px 10px 0px",
                               "padding" => "4px",
                               "border" => "1px solid #999999") );
    }
}
?>
