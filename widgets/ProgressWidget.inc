<?php
/**
 * $Id: ProgressWidget.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * This contains the file that holds the
 * Progress Widget to show a realtime
 * progress bar
 *
 * @author Walter A. Boring IV
 */

/**
 * This widget will display a progress bar
 * without requiring a page turn to get the updated
 * status from the web server.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 */
class ProgressWidget extends BaseWidget {

    /**
     * Flag to tell us if they
     * want to show the % text in the
     * progress.
     */
    var $_show_percent=TRUE;


    /**
     * The current value of the 
     * percentage complete
     */
    var $_percent = 0;

    /**
     * The current value of the 
     * percentage complete in pixels
     */
    var $_percent_pixels = 0;


    /**
     * Has the object been rendered yet?
     * This usually means that is has been
     * dumped to the browser.
     */
    var $_rendered = FALSE;

    /**
     * The Constructor
     *
     * @param integer the width of the bar
     * @param boolean show the percentage complete
     *                inside the bar?
     */
    function ProgressWidget($width=300, $show_percent_flag=TRUE) {
        $this->set_width($width);
        $this->set_show_percent($show_percent_flag);
    }


    /**
     * This sets the show percent text flag
     *
     * @param boolean TRUE = show
     * @return none
     */
    function set_show_percent($flag) {
        $this->_show_percent = $flag;
    }

    /**
     * this function updates the progress bar
     * @param float percentage
     */
    function update($percent) {
        $width = $this->get_width();
        $progress = round($percent*$width/100);

        if ( $progress > $width ) $progress = $width;
        if ( $progress < 0 ) $progress = 0;

        if ( !$this->_show_percent ) {
            $percent = -1;
        }

        if ( $this->_rendered ) {
            print ("<script>pwu(".$progress.",".$percent.");</script>");
            flush();
        }

        $this->_percent_width = $progress;
        $this->_percent = $percent;
        return TRUE;
    }

    /**
     * Render the main layout of the bar.
     * You have to call update periodically to get
     * the bar to 'grow'
     *
     * @param integer the indent level of the html output
     * @param integer the debug flag.
     */
    function render($indent_level=1, $output_debug=0) {

        $width = $this->get_width();

        $wrapper_div = new DIVtag(array("style"=>"background-color: #efefef;width:" . $width . "px;".
                                        "height:15px;border: 1px inset;text-align:left;"));

        $progressbar = new DIVtag(array("id"=>"progressbar"));

        $js = new SCRIPTtag(array('type' => 'text/javascript'),
                            "function pwu(w,p) { pb = document.getElementById('progressbar');\n pb.style.width = w + 'px';");

        if ( !strstr($_SERVER["HTTP_USER_AGENT"],"MSIE") ) {
            $progressbar->add(new DIVtag( array('id' => 'progresspercent',
                                                'align' => 'center',
                                                'style' => 'width:'.$width.';')));

            $js->add("pp = document.getElementById('progresspercent');".
                     "if ( p != -1 ) pp.innerHTML = p + '%';\n".
                     //we hard code the color to white after 48%
                     //need a better way to hack this
                     "if ( p > 48 ) pp.style.color = '#FFFFFF'; }\n");

            $wrapper_div->add( $progressbar, $progresspercent);
        } else {
            $js->add("}");
            $wrapper_div->add( $progressbar );
        }

        $this->_rendered = TRUE;
        $c = container( $wrapper_div, $js );
        if ( $this->_percent ) {
            $c->add("<script>pwu(".$this->_percent_width.",".$this->_percent.");</script>");
        }
        return $c->render($indent_level, $output_debug);
    }


    /**
     * This method is used to set the
     * color of the progress bar itself
     *
     * @param string
     */
    function set_color($color=NULL) {
        if ( $color !== NULL ) {
            $this->_color = $color;
        }
    }

    /**
     * set the rendered flag
     * 
     * @param boolean
     */
    function set_rendered_flag($flag) {
        $this->_rendered = $flag;
    }
}


/**
 * This class builds a nice box that
 * contains a title a ProgressWidget
 * and some description text for each
 * progress percentage.
 *
 * By default it is hidden, so you can build
 * the box, and call set_visible() when you want
 * to display it, then call set_hidden() when
 * you want it to disapear when it reaches 100%
 *
 *
 * @author Walter A. Boring IV
 */
class ProgressBoxWidget extends BaseWidget {

    /**
     * Holds the progress bar object
     *
     */
    var $_progress = NULL;

    /**
     * Holds value of the last comment
     *
     */
    var $last_comment = NULL;


    /**
     * The constructor
     *
     * @param string the title of the box.
     * @param integer the width to use for the outer box.
     */
    function ProgressBoxWidget($title = NULL, $width=300, $show_percent_flag=TRUE) {
        $this->_progress = new ProgressWidget($width, $show_percent_flag);
        $this->set_title($title);
        $this->set_width($width);
        $this->display();
    }


    /**
     * Render the box.
     * This should get called before calling update()
     *
     * @param integer indent level
     * @param integer output_debug
     */
    function render($indent_level=0, $output_debug=0) {

        //set the style so we can make sure it looks
        //ok based on the width of the outer object.
        //the rest of the style is in the CSS object.
        $div = new DIVtag(array("id"=>"progressbox",
                                "style"=> "width:".($this->get_width()+10)),
                          new DIVtag(array("id"=>"progressboxtitle"), $this->title),
                          $this->_progress,
                          new DIVtag(array("id"=>"progressboxtext"), _HTML_SPACE));

        //because php makes a copy when added 
        //to the DIVtag
        $this->_progress->set_rendered_flag(TRUE);

        return $div->render($indent_level, $output_debug);
    }

    /**
     * This function outputs the html
     * and places it in the middle of the page
     */
    function display() {
        print $this->render();

        $js = "<script language=\"javaScript\">\n".
              "pbox = document.getElementById('progressbox');";

        //because IE sucks
        if ( strstr($_SERVER["HTTP_USER_AGENT"],"MSIE") ) {
            $js .= "pbox.style.left = Math.round(document.body.offsetWidth/2)-150;".
                   "pbox.style.top = Math.round(document.body.offsetHeight/3)-50;";
        } else {
            $js .= "pbox.style.left = Math.round(window.innerWidth/2)-150;".
                   "pbox.style.top = Math.round(window.innerHeight/3)-50;";
        }

        $js .= "\nfunction pbwuc(c) { document.getElementById('progressboxtext').innerHTML = c; }\n" .
               "function sv() { document.getElementById('progressbox').style.visibility = 'visible'; }\n".
               "function sh() { document.getElementById('progressbox').style.visibility = 'hidden'; }\n".
               "</script>\n";

        print($js);
        flush();
    }


    /**
     * This function shows the progress window
     */
    function set_visible() {
        print("<script language=\"javaScript\">sv();</script>");
        flush();
    }

    /**
     * This function hides the progress window
     */
    function set_hidden() {
        print("<script language=\"javaScript\">sh();</script>");
        flush();
    }


    /**
     * this function updates the progress bar
     *
     * @param integer percentage as an integer
     *                0 < x < 100
     * @param string comment
     */
    function update($percent, $comment = NULL) {
        $this->_progress->update($percent);
        if ( $comment != NULL ) {
            $this->update_comment($comment);
        }
    }

    /**
     * this function updates the progress bar
     *
     * @param string the comment to update.
     * @return none
     */
    function update_comment($comment) {
        //no need to update the comment?
        if ( $comment == $this->last_comment ) {
            return;
        }

        print("<script>pbwuc('" . $comment . "');</script>");
        flush();
        $this->last_comment = $comment;
    }
}


/**
 * This class defines the css used by the
 * FooterNav Object.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class ProgressBoxWidgetCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry("#progressbox", NULL,
                         array("font-family" => "arial,verdana,helvetica",
                               "border" => "1px solid #aaaaaa",
                               "background-color" => "#fafafa",
                               "padding" => "10px",
                               "position" =>  "absolute",
                               "top" => "100px",
                               "left" => "100px",
                               "visibility" => "hidden",
                               "height" => "50px") );

        $this->add_entry("#progressbox", "#progressboxtitle",
                         array("font-size" => "10pt",
                               "font-weight" => "bold",
                               "color" => "#000000",
                               "padding" => "2px;") );

        $this->add_entry("#progressbox", "#progressboxtext",
                         array("font-size" => "10pt",
                               "color" => "#000000",
                               "padding" => "2px;"));

        $this->add_entry("#progressbox", "#progressbar",
                         array("font-size" => "10pt",
                               "text-align" => "left",
                               "color" => "#999999",
                               "background-color" => "#999999",
                               "width" => "0px",
                               "height" => "15px"));

        $this->add_entry("#progressbar", "#progresspercent",
                         array("font-size" => "10pt",
                               "font-weight" => "bold",
                               "text-align" => "center",
                               "color" => "#000000"));
    }
}


/**
 * This class defines the css used by the
 * FooterNav Object.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class ProgressWidgetCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry("#progressbar", "",
                         array("font-size" => "10pt",
                               //"text-align" => "left",
                               "color" => "#999999",
                               "background-color" => "#999999",
                               "width" => "0px",
                               "height" => "15px"));

        $this->add_entry("#progresspercent", "",
                         array("font-size" => "10pt",
                               "font-weight" => "bold",
                               "text-align" => "center",
                               "color" => "#000000"));
    }
}

?>
