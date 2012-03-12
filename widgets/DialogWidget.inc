<?php
/**
 * This contains the TextNav widget
 *
 * $Id: DialogWidget.inc 3556 2012-03-11 11:26:12Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */


require_once(PHPHTMLLIB_ABSPATH . "/widgets/InfoTable.inc");
require_once(PHPHTMLLIB_ABSPATH . "/widgets/ButtonPanel.inc");


/**
 * This is a base class for building generic 
 * Dialogs with messages and buttons.
 * 
 */ 
class DialogWidget extends BaseWidget {

    /**
     * Holds the list of buttons
     * for this widget dialog
     *
     */
    var $_buttons = array();

    /**
     * Show or not to show the cancel button?
     *
     */
    var $_show_cancel_button = FALSE;

    /**
     * Holds the cancel action
     *
     */
    var $_cancel_url = NULL;


    /**
     * The constructor
     * 
     * @param string the title
     * @param string the width
     * @return none
     */
    function DialogWidget($title = NULL, $width="100%", $align=NULL) {
        $this->set_title($title);
        $this->set_width($width);
        $this->set_align($align);
    }

    /**
     * Creates a container with title,
     * data and the buttons
     *
     */
    function render($indent_level=0, $output_debug=0) {

        $table = html_table($this->get_width(), 0, 0, 0, $this->get_align());
       
        $box = $this->_build_message_container();
        $table->add_row( $box );

        // add the buttons
        $buttons = $this->_build_buttons() ;
        if ($buttons != null) {
            $table->add_row( _HTML_SPACE );
            $table->add_row($buttons);
        }
            
        return $table->render( $indent_level, $output_debug );
    }

    /**
     * Pushes a content into the data object
     *
     * @param mixed - either string, or tag object.
     * @access public
     */
    function add() {
        $args = func_get_args();

        foreach($args as $content) {
            $this->_data[] = $content;
        }
    }


    /**
     * Adds a single button to the dialog
     * that will be display at the bottom
     * of the widget
     *
     * @param string - button title
     * @param string - button action, if NULL, then submit button is created
     * @access public
     */
    function add_button($button) {
        $this->_buttons[] = $button;
    }


    /**
     * Sets the flag to show or not to show
     * the cancel button
     *
     * @param bool - flag
     */
    function show_cancel_button($flag) {
        $this->_show_cancel_button = $flag;
    }

    /**
     * Sets the cancel action
     *
     * @param string - action
     */
    function set_cancel_url($url) {
        $this->_cancel_url = $url;
    }


    /**
     * Create a DIV that holds the buttons
     *
     * @return a DIVtag
     * @access private
     */
    function _build_buttons() {

        if (empty($this->_buttons) && !$this->_show_cancel_button) {
            return null;
        } 

        $buttons = new ButtonPanel($this->get_width(), "center");

        foreach ($this->_buttons as $button) {
            $buttons->add($button);
        }

        if ($this->_show_cancel_button) {
            // build cancel buttons
            $this->_build_cancel_url();            

            $buttons->add(form_button("cancel","Cancel",
                                      array("type"=>"button",
                                            "style"=>"width:90px;",
                                            "onclick"=>"javascript:window.location='" . $this->_cancel_url . "'")));
        }

        return $buttons;
    }


    /**
     * Build the cancel url
     * 
     * @return string
     */
    function _build_cancel_url() {
        if ($this->_cancel_url == NULL) {
            $this->set_cancel_url("index.php");
        }
    }



    /**
     * This method is used to add the message blocks
     * to the appropriate container
     * 
     * @return object - the container object with the messages.
     */
    function &_build_message_container() {
        $box = new InfoTable($this->get_title());

        //don't show the cell borders
        $box->set_show_cellborders(false);

        // add each block
        foreach ($this->_data as $message) {

            // we have a block with the title
            $box->add_row($message);
        }

        return $box;
    }
}
?>
