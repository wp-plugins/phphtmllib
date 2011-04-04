<?php
/**
 * This file contains the ActiveTab class
 *
 * $Id: ActiveTab.inc 1694 2006-04-12 04:44:52Z hemna $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 *
 */

/**
 * This class is used for creating a tab panel of content
 * where the tabs can be switched on the fly w/ JS, thereby
 * eliminating a page turn to see the other tab's content.
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 */
class ActiveTab extends BaseWidget {


    /**
     * We have to code these here instead of
     * the css because JS is used to change
     * the colors.  JS can't change a color
     * that is defined in a css class.  It only
     * works on an inline style
     */

    /**
     * The active tab's background color
     *
     */
    var $_selected_background = "#eeeeee";

    /**
     * The hidden tab's background color
     */
    var $_hidden_background = "#e0e0e0";

    /**
     * Random string for function prefix
     * allows having multiple controls on same page
     */
    var $_funct_prefix = null;
    
    /**
     * The default selected tab
     * this is a tab name
     *
     * ActiveTab::name("Title of Tab");
     */
    var $_selected_tab = null;


    /**
     * This is the constructor for the ActiveTab
     * object.
     *
     * @param string - the width table
     * @param string - the height of the tab's contents
     * @param string - the selected tab name.
     *                 NOTE: this is set with
     *                       ActiveTab::name("Title of Tab");
     *                       add_tab() can override this.
     */
    function ActiveTab($width="100%", $height="300px", $selected_tab=null) {
        $this->set_width( $width );
        $this->_height = $height;
        $this->_selected_tab = $selected_tab;
        $this->_funct_prefix = rand();
    }


    function render($indent_level=1, $output_debug=0) {
        $tabs = $this->build_tabs();

        $span = 2 + (count($this->_data) *2 );

        $td = new TDtag(array("colspan" => $span), $this->build_content() );
        $tabs->add_row( $td );
        $div = html_div("activetab", $tabs);
        $div->set_style("width:".$this->get_width());
        return $div->render($indent_level, $output_debug);
    }

    /**
     * This function MUST be called AFTER ALL content
     * has been added, in order for the js to work properly
     *
     * @return string
     */
    function get_javascript() {
        $function = "function show_activetab_".$this->_funct_prefix."(tab) {\n";

        $function .= "     var tabs = new Array();\n";

        foreach( $this->_data as $tab ) {
            $function .= "     tabs['".$this->name($tab["title"])."'] = 1;\n";
        }

        $function .= "     for (title in tabs ) {\n";
        $function .= "        obj = document.getElementById('div_'+title).style.display = 'none';\n";
        $function .= "        obj = document.getElementById('tab_'+title).style.borderBottom = '1px solid #a1a1a1';\n";
        $function .= "        obj = document.getElementById('tab_'+title).style.fontWeight = '';\n";
        $function .= "        obj = document.getElementById('tab_'+title).style.backgroundColor = '".$this->_hidden_background."';\n";
        $function .= "     }\n";

        $function .= "     // show the content of ips\n";
        $function .= "     obj = document.getElementById('div_'+tab).style.display = 'block';\n";

        $function .= "     // draw the tab separator line\n";
        $function .= "     obj = document.getElementById('tab_'+tab).style.borderBottom = 'none';\n";
        $function .= "     obj = document.getElementById('tab_'+tab).style.fontWeight = 'bold';\n";
        $function .= "     obj = document.getElementById('tab_'+tab).style.backgroundColor = '".$this->_selected_background."';\n";

        $function .= "     // save the last viewed div in a hidden variable (if it's there)\n";
        $function .= "     obj = document.getElementsByName('div_selected');\n";
        $function .= "     if (obj[0] != null && obj[0].value) obj[0].value = tab;\n";
        $function .= "}\n";
        return $function;
    }

    /**
     * Add a tab
     *
     * @param string - the title of the tab
     * @param mixed - the conetnts for the tab
     * @param boolean - should this tab be
     *                  the default selected tab?
     *
     *                  Note: This will override the
     *                        selected tab parameter
     *                        in the constructor.
     *
     * @param int   - the width of the tab in pixels
     *                defaults to 60
     *
     */
    function add_tab( $title, $content, $selected=FALSE, $width=NULL) {
        $this->_data[] = array("title" => $title,
                               "selected" => $selected,
                               "width" => $width,
                               "content" => $content
                               );
        if ($selected) {
            $this->_selected_tab = $this->name($title);
        }
    }


    function build_tabs() {
        $table = html_table($this->get_width(), 0,0,0, "center");

        $tr = new TRtag;

        //make sure that we have at least the
        //first tab selected if there is non selected
        if ($this->_selected_tab === null || strcasecmp($this->_selected_tab, "0") == 0) {
            $this->_selected_tab = $this->name($this->_data[0]["title"]);
        }

        $tr->add( $this->_spacer_td() );
        foreach( $this->_data as $tab) {
            $selected = FALSE;
            if (strcasecmp($this->name($tab["title"]),$this->_selected_tab) == 0 ||
                $tab["selected"] == TRUE) {
                $selected = TRUE;
            }
            $tr->add( $this->_build_tab_td( $tab["title"],
                                            $selected,
                                            $tab["width"]) );
            $tr->add( $this->_spacer_td() );
        }
        $tr->add( $this->_end_td() );

        $table->add( $tr );
        return $table;
    }

    function build_content() {
        $div = html_div("content");
        $div->set_style( "height:" . $this->_height . ";");
        
        foreach ( $this->_data as $tab ) {
            if ( strcasecmp($this->_tab_name($tab["title"]), $this->_selected_tab) == 0 ) {
                $class = "content_visible";
            } else {
                $class = "content_hidden";
            }
            $tab1_div = html_div(null, $tab["content"]);
            $tab_div = html_div($class);
            $tab_div->set_id( "div_".$this->_tab_name( $tab["title"] ) );
            //HACK!!!! to fix a LAME BUG IN SAFARI
            $tab_div->set_style('width:99%');
            $tab_div->add($tab1_div);
            $div->add( $tab_div );
        }

        $toplevel_table = html_table();
        $toplevel_table->add_row($div);
        return $toplevel_table;
    }

    function _spacer_td() {
        return html_td("spacer", NULL, "&nbsp;");
    }

    function _end_td() {
        return html_td("end", NULL, "&nbsp;");
    }


    function _build_tab_td($title, $selected, $width) {
        $td_class = "tab";
        $link_class = "link";

        if ( $width == NULL ) {
            $width = "60px";
        }

        if ( !strstr($width, "px") ) {
            $width .= "px";
        }

        if ( $selected ) {
            $td_class .= "selected";
        } else {
            $td_class .= "hidden";
        }
        $func = "show_activetab_".$this->_funct_prefix."('".$this->name($title)."');";
        $link = html_a("javascript: ".$func, $title, "link");

        $link_div = new DIVtag(array("style"=>"white-space:nowrap"), $link);

        $td = html_td($td_class, "", $link_div);
        $td->set_id("tab_".$this->name($title));
        $td->set_tag_attribute("onclick", "javascript: ".$func);
        if ( $selected ) {
            $style = "font-weight: bold;background-color: ".$this->_selected_background.";";
        } else {
            $style = "background-color: ".$this->_hidden_background.";";
        }
        $td->set_style($style."width:".$width);
        return $td;
    }

    /**
     * Thie method is used to change the selected tab's
     * background color
     */
    function selected_background( $color ) {
        $this->_selected_background = $color;
    }

    /**
     * Thie method is used to change the hidden tab's
     * background color
     */
    function hidden_background( $color ) {
        $this->_hidden_background = $color;
    }

    /**
     * Build the 'name' of the tab.  This can be
     * called in a static way to set the default
     * selected tab.
     *
     * {@source }
     * @param string
     * @return strint
     */
    function name($title) {
        return str_replace(" ", "_", strtolower($title));
    }

    function _tab_name( $title ) {
        return $this->name($title);
    }

}

/**
 * The CSSBuilder object for the ActiveTab widget
 *
 * @package phpHtmlLib
 */
class ActiveTabCSS extends CSSBuilder {
    function user_setup() {
        $this->add_entry(".activetab", "",
                         array() );

        $this->add_entry(".activetab", ".spacer",
                         array("width" => "5px",
                               "border-bottom" => "1px solid #a1a1a1"));
        $this->add_entry(".activetab", ".end",
                         array("border-bottom" => "1px solid #a1a1a1"));

        $this->add_entry(".activetab", ".link:active,.link:hover,.link:link,.link:visited",
                         array("text-decoration" => "none",
                               "color" => "#000000"));

        $this->add_entry(".activetab", ".tabhidden",
                         array("border" => "1px solid #999999",
                               "padding-left" => "5px",
                               "padding-right" => "5px",
                               "background-color" => "#eeeeee",
                               "text-align" => "center",
                               "white-space" => "nowrap",
                               "font-family" => "arial",
                               "font-size" => "10pt"));

        $this->add_entry(".activetab", ".tabselected",
                         array("border-left" => "1px solid #999999",
                               "border-top" => "1px solid #999999",
                               "border-right" => "1px solid #999999",
                               "padding-left" => "5px",
                               "padding-right" => "5px",
                               "text-align" => "center",
                               "white-space" => "nowrap",
                               "font-family" => "arial",
                               "font-size" => "10pt"));

        $this->add_entry(".activetab", ".content",
                         array("border-left" => "1px solid #a1a1a1",
                               "border-right" => "1px solid #a1a1a1",
                               "border-bottom" => "1px solid #a1a1a1",
                               "position" => "relative",
                               "z-index" => "100"));

        $this->add_entry(".activetab", ".content_visible",
                         array("left" => "0px",
                               "top" => "0px",
                               "position" => "absolute",
                               "display" => "block",
                               "z-index" => "50",
                               "padding" => "5px 5px 5px 5px"));

        $this->add_entry(".activetab", ".content_hidden",
                         array("left" => "0px",
                               "top" => "0px",
                               "position" => "absolute",
                               "display" => "none",
                               "z-index" => "50",
                               "padding" => "5px 5px 5px 5px"));
    }

}

?>
