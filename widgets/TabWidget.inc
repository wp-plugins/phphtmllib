<?php
/**
 * Holds the TabWidget and Tablist
 *
 * $Id: TabWidget.inc 3073 2007-10-30 20:06:51Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * Some defines
 */
define("TABLIST_SELECTED", "tab_selected");
define("TABLIST_SUB_SELECTED", "subtab_selected");


/**
 * This class implements the Qualys Tab object.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib
 */
class TabWidget extends BaseWidget {

    /**
     * Is this tab selected or not?
     */
    var $_selected = false;

    /**
     * The tab number in the list of tabs.
     */
    var $_number = 0;

    /**
     * The constructor
     *
     * {@source }
     *
     * @param string the title for the Tab
     */
    function TabWidget($title) {
        $this->set_title($title);
    }


    /**
     * This is the function where you
     * can build the content for the Tab itself.
     *
     * The alternative is to use the add() method.
     *
     * {@source }
     * @return Container object
     */
    function content() {
        return null;
    }

    /**
     * This method creates the name of the tab
     *
     * @param string - the tab display string
     * @return string - the tab name
     */
    function name($title) {
        $name = strtolower($title);
        $len = strlen($name);

        for ($i=0; $i<$len;$i++) {
            if ((ord($name[$i])<97 || ord($name[$i])>122) &&
                (ord($name[$i])<48 || ord($name[$i])>57))
                $name[$i] = "_";
        }
        return $name;
    }


    /**
     * This method builds the query string
     * 'tab_selected=<name>' for you
     * to place in a url
     *
     * @param string - the tab title
     * @param boolean - is this a subtab?
     * @return string - the query var assigned to tab name
     */
    function queryvar($title, $subtab_flag=false) {
        if ($subtab_flag) {
            $prefix = TABLIST_SUB_SELECTED."=";
        } else {
            $prefix = TABLIST_SELECTED."=";
        }
        return $prefix.TabWidget::name($title);
    }
}


/**
 * This class implements a set of multiple tabs holding
 * data objects
 *
 *
 * @author Suren Markossian
 * @author Walter A. Boring IV
 */
class TabList extends BaseWidget {

    /**
     * The number of tabs
     */
    var $_tab_num=0;

    /**
     * The selected tab
     * from the list
     */
    var $_tab_selected=null;

    /**
     * array of tabs that have been added
     */
    var $_tabs = array();

    /**
     * the TR object for the tabs
     */
    var $_tab_row = null;

    /**
     * This holds a list of
     * name=>value vars that the
     * caller/child wants to propogate
     * automatically.
     *
     */
    var $_save_vars = array();

    /**
     * Flag to let us know we are a subtab
     * list or not
     */
    var $_subtab_flag = false;


    /**
     * The outer wrapper for the ui.
     * So we can build top level and
     * sublevels
     */
    var $_ui_wrapper = null;

    /**
     * valid selected tab?
     */
    var $_valid_tab = false;

    /**
     * array of icons that have been added
     */
    var $_icons = array();

	/**
     * boolean to tell whether icons have been added
     */
    var $_icon_flag = false;

    /**
     * boolean to tell whether to display line after tab
     */
    var $_tab_line_flag = false;

    /**
     * The constructor.
     *
     * @param the title of the tablist.
     */
    function TabList($title) {
        $this->title = $title;
    }

    /**
     * The render method
     *
     * @param int the html indentation level
     * @param int the html debug level
     * @return string the output html
     */
    function render( $indent_level=0, $output_debug=0 ) {
        if ($this->_subtab_flag) {
            //we need to build a subtab list
            $this->_build_subtab_ui();
        } else {
            //ok build the outer UI for the top tabs
            $this->_build_top_tab_ui();
        }

        return $this->_ui_wrapper->render($indent_level, $output_debug=0);

  }

  	/**
  	 * Sets display line after tab
  	 *
  	 */
  	function setTabLine($display=false) {
  		$this->_tab_line_flag = $display;
  	}

    /**
     * This public method adds a new tab to the table
     * @param title string - tab title
     * @param data object - data container for this tab
     */
    function add(&$tab_obj) {

	// PHP4 and PHP5 return class names differently, PHP4 lower cases names.
	$v = phpversion() ;
	$tablist = $v[0] == "4" ? "tablist" : "TabList" ;
	$tabwidget = $v[0] == "4" ? "tabwidget" : "TabWidget" ;

        if (is_a($tab_obj, $tabwidget)) {
            //render a normal tab with its content.
            $this->_tabs[] =& $tab_obj;
        } else if (is_subclass_of($tab_obj, $tablist) ||
                   get_class($tab_obj) == $tablist) {
            $tab_obj->_set_subtab_flag(TRUE);
            $this->_tabs[] =& $tab_obj;
        } else {
            trigger_error(__CLASS__."::".__FUNCTION__."() - called with an invalid object (".
                          get_parent_class($tab_obj).
                          "). must be either a TabWidget or a TabList(subtab).",
                          E_USER_ERROR);
        }
    }

    /**
     * Alias for add_icon
     *
     * Note, this method name does not follow the standard method naming
     * convention and has been deprecated
     *
     * @deprecated
     * @param string $icon icon SRC to display
     * @param string $title link verbage
     * @param string $url link URL
     * @return void
     */
    function addicon($icon, $title, $url) {
    	return $this->add_icon($icon, $title, $url);
    }

    /**
     * This public method adds a new tab icon to the table
     *
     * @param string $icon icon SRC to display
     * @param string $title link verbage
     * @param string $url link URL
     * @param string $width width of icon image
     * @param string $height height of icon image
     * @param string $onclick onclick javascript event handler for a tag
     * @return void
     */
	function add_icon($icon, $title, $url, $width = '', $height = '', $onclick = '') {
		$this->_icons[] = array('icon' => $icon,
								'title' => $title,
								'url' => $url,
								'width' => $width,
								'height' => $height,
								'onclick' => $onclick);
		$this->_icon_flag = true;
	}

    /**
     * Return the title
     */
    function get_title() {
        return $this->title;
    }

    /**
     * This function sets the save variables
     * that the user/child wants to automatically
     * propogate
     *
     * @param array - name=>value pairs of the data
     *                that they want to propogate
     */
    function set_save_vars( $vars ) {
        $this->_save_vars = $vars;
    }

    /**
     * this function builds a partial
     * query string with the
     * $this->_save_vars
     *
     * @return string
     */
    function _build_save_vars() {
        $query_string = "";
        foreach( $this->_save_vars as $name => $value ) {
            $query_string .= $name."=".$value."&";
        }
        return $query_string;
    }


    /**
     * this private function builds the url
     * for the main tab script and adss the
     * needed query string params
     *
     * @param string - the tab name
     * @param string - the subtab name
     *
     * @return string url
     */
    function _build_url($tab_name, $subtab_name=null) {
        $url = $_SERVER["SCRIPT_NAME"]."?".TABLIST_SELECTED."=".$tab_name."&";
        if ($subtab_name !== null) {
            $url .= TABLIST_SUB_SELECTED."=".$subtab_name."&";
        }
        $url .= $this->_build_save_vars();
        return $url;
    }

    /**
     * This method is used to set the
     * subtab bit
     *
     * @param boolean
     */
    function  _set_subtab_flag($flag) {
        $this->_subtab_flag = $flag;
    }

    /**
     * This method creates the name of the tab
     *
     * @param string - the tab display string
     * @return string - the tab name
     */
    function name($title) {
        return TabWidget::name($title);
    }


    /**
     * This method builds the query string
     * 'tab_selected=<name>' for you
     * to place in a url
     *
     * @param string - the tab title
     * @return string - the query var assigned to tab name
     */
    function queryvar($title) {
        return TabWidget::queryvar($title);
    }


    /**
     * This method builds the outer wrapper UI
     * for the top level tab list.
     *
     * @return none
     */
    function _build_top_tab_ui() {
	// PHP4 and PHP5 return class names differently, PHP4 lower cases names.
	$v = phpversion() ;
	$tablist = $v[0] == "4" ? "tablist" : "TabList" ;
	$tabwidget = $v[0] == "4" ? "tabwidget" : "TabWidget" ;

        // initialize selected tab number
        if (isset($_REQUEST[TABLIST_SELECTED]))
            $this->_tab_selected = $_REQUEST[TABLIST_SELECTED];

        $this->_tab_row = new TRtag();

        $this->_ui_wrapper = html_table();
        $this->_ui_wrapper->set_class($tablist);

        $this->tab_num = count( $this->_tabs );
        // create data row and add data to it
        $tr = new TRtag();
        $colspan = 2*$this->tab_num+1;
        $data_td = new TDtag(array("class"=>"tab_data","colspan"=>$colspan));

        foreach( $this->_tabs as $tab_obj ) {
            $title = $tab_obj->get_title();
            $tab_name = $this->name($title);
            $this->_build_tab($title, $tab_name);

            // separator between two tabs
            $this->_add_tab_spacer();

            if ($tab_name==$this->_tab_selected) {
                if (is_subclass_of($tab_obj, $tablist) ||
                    get_class($tab_obj) == $tablist) {
                    $this->_valid_tab = TRUE;
                    $data_td->add_reference( $tab_obj );
                } else {
                    $this->_valid_tab = TRUE;
                    $data_td->add_reference( $tab_obj->content() );
                }
            }
        }

        if (!$this->_valid_tab) {
            //someone hacked the selected tab
            $data_td->add( $this->_invalid_tab() );
        }


        // Check whether to build icon td
        if ($this->_icon_flag)
        	$this->_build_icons();
        else
        	$this->_add_tab_spacer(TRUE);

        $this->_ui_wrapper->add_row($this->_tab_row);

        // Add line after tabs
	    $this->_add_line_spacing();

        $tr->add($data_td);
        $this->_ui_wrapper->add_row($tr);
    }


    /**
     * This method builds the outer wrapper UI
     * for the subtab
     *
     * @return none
     */
    function _build_subtab_ui() {

	// PHP4 and PHP5 return class names differently, PHP4 lower cases names.
	$v = phpversion() ;
	$tablist = $v[0] == "4" ? "tablist" : "TabList" ;
	$tabwidget = $v[0] == "4" ? "tabwidget" : "TabWidget" ;

        // initialize selected tab number
        if (isset($_REQUEST[TABLIST_SUB_SELECTED]))
            $this->_tab_selected = $_REQUEST[TABLIST_SUB_SELECTED];

        $this->_ui_wrapper = html_table("100%");

        $this->_tab_row = new TRtag();

        $tr = new TRtag();

        $tab_name = $this->name($this->get_title());
        $data_td = new TDtag(array("class"=>"subtab_data"));

        foreach( $this->_tabs as $tab_obj ) {
            $title = $tab_obj->get_title();
            $subtab_name = $this->name($title);
            $this->_build_subtab($title, $tab_name, $subtab_name);

            if ($subtab_name==$this->_tab_selected) {
                if (is_subclass_of($tab_obj, $tablist) ||
                    get_class($tab_obj) == $tablist) {
                    $this->_valid_tab = TRUE;
                    $data_td->add_reference( $tab_obj );
                } else {
                    $this->_valid_tab = TRUE;
                    $data_td->add_reference( $tab_obj->content() );
                }
            }
        }

        if (!$this->_valid_tab) {
            //someone hacked the selected tab
            $data_td->add( $this->_invalid_tab() );
        }

        //add last spacer to cram everything left.
        $this->_tab_row->add( new TDtag(array("width" => "95%",
                                              "class" => "subtab"), _HTML_SPACE));
        $this->_ui_wrapper->add_row($this->_tab_row);
        $tr->add($data_td);
        $this->_ui_wrapper->add_row($tr);
    }


    /**
     * This method is used to build a top level
     * tab
     *
     * @param string - the tab title
     *
     */
    function _build_tab($title, $tab_name) {

        if ($this->_tab_selected == null ||
            empty($this->_tab_selected)) {
            $this->_tab_selected = $tab_name;
        }

        if ($tab_name==$this->_tab_selected) {
            $class = "tab_selected";
            $link_class = "tab_link_selected";
        } else {
            $class = "tab_default";
            $link_class = "tab_link_default";
        }


        // create link for this tab pointing to the same page with the tab number
        $url = $this->_build_url($tab_name);

        // the actual tab
        $onclick = "window.location='" . $url."';return false;";
        $td = new TDtag(array(
                              "class"=>$class,
                              "valign" => "top",
                              "width"=>"10%",
                              "nowrap",
                              "onclick"=> $onclick));

        $td->push(html_a($url, $title, $link_class));
        $td->set_collapse();
        $this->_tab_row->add($td);
    }

    /**
     * This method builds a single subtab
     *
     * @param string the title
     * @param string the tab name
     */
    function _build_subtab($title, $tab_name, $subtab_name) {

        if ($this->_tab_selected == null ||
            empty($this->_tab_selected)) {
            $this->_tab_selected = $subtab_name;
        }

        if ($subtab_name==$this->_tab_selected) {
            $class = "subtab";
            $link_class = "subtab_link_selected";
        } else {
            $class = "subtab";
            $link_class = "subtab_link_default";
        }

        $url = $this->_build_url($tab_name, $subtab_name);

        $td = html_td($class);

        $td->set_collapse();
        $td->add( html_a($url, $title, $link_class));

        $this->_tab_row->add( $td );
    }


    /**
     * This method adds a new spacer in between
     * the tabs.
     *
     * @param boolean - is this the last spacer?
     */
    function _add_tab_spacer($last_spacer=false) {

        $attributes = array();

        if ($last_spacer) {
            $width = 100 - ($this->tab_num*10) . "%";

            $attributes["class"] = "tab_spacer_last";
            $attributes["align"] = "center";
            $attributes["width"] = $width;

        } else {
            $attributes["class"] = "tab_spacer";
            $attributes["align"] = "left";
        }


        $td = new TDtag($attributes);
        $td->add(_HTML_SPACE);
        $td->set_collapse();
        $this->_tab_row->add($td);
    }

    /**
     * This method builds a message for an invalid
     * selected tab/subtab
     *
     * @return Container
     */
    function _invalid_tab() {
        return "Invalid Selected Tab";
    }

    /**
     * This method builds the icons to the right of the tabs
     *
     */
    function _build_icons() {
    	$attributes = array();
    	
    	$width = 100 - ($this->tab_num*10) . "%";

    	$attributes["class"] = "tab_icon";
	    $attributes["align"] = "right";
	    $attributes["width"] = $width;
    	$td2 = new TDtag( $attributes);
    	
    	$spacing_div = new DIVtag(array("style" => "display: inline; padding:5px;"));
    	$spacing_div->add("&nbsp;");
    	
    	foreach ($this->_icons as $icontab) {
			$img = html_img(
				$icontab['icon'],
				$icontab['height'], $icontab['width'], 0,
				$icontab['title'], null, $icontab['title'],
				'top');
			$url = html_a(
				$icontab['url'],
				container($img->render(), _HTML_SPACE, _HTML_SPACE, $icontab['title']),
				'icon_data', '', '');
			$url->set_tag_attribute('onclick', $icontab['onclick']);
			$icontablist .= $spacing_div->render() . $url->render();
    	}

		$td2->add($icontablist);
		$this->_tab_row->add($td2);
    }

    /**
     * This method adds a new spacing between the tabs and the tab contents
     *
     */
    function _add_line_spacing() {

    	if (!$this->_subtab_flag &&
    		$this->_tab_line_flag) {
	    	$colspan = 2*$this->tab_num+1;
	    	
	        $spacing_td = new TDtag(array("class"=>"tab_spacing","colspan"=>$colspan));
	        $spacing_td->add("&nbsp;");
	        $spacing_tr = new TRtag();
	
	        $spacing_tr->add($spacing_td);
	
	    	$this->_ui_wrapper->add_row($spacing_tr);
    	}
    }

}


/**
 * This class defines the css used by the
 * FooterNav Object.
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 */
class TabListCSS extends CSSBuilder {

	function user_setup() {
		$this->add_entry(".tablist", "",
						 array(
                             "margin" => "0px",
                             "padding" => "0px",
                             "font-family" => "sans-serif",
                             "font-size" => "12px",
                             ) );

        $this->add_entry(".tablist", ".tab_selected",
						 array(
                             "font-weight" => "bold",
                             "padding" => "2px 4px 2px 4px",
                             "color" => "#FFFFFF",
                             "background-color" => "#999999",
                             "border-right" => "1px solid #828282",
                             "border-top" => "1px solid #828282"
                             ) );

        $this->add_entry(".tablist", ".tab_default",
                         array(
                             "padding" => "2px 4px 2px 4px",
                             "color" => "#FFFFFF",
                             "background-color" => "#e1e1e1",
                             "border-left" => "1px solid #828282",
                             "border-right" => "1px solid #828282",
                             "border-top" => "1px solid #828282",
                             "border-bottom" => "1px solid #828282"
                             ));

        $this->add_entry(".tablist", ".tab_spacer",
                         array(
                             "margin" => "0px",
                             "padding" => "0px",
                             "background-color" => "#ffffff",
                             "border-bottom" => "1px solid #828282",
                             ));

        $this->add_entry(".tablist", ".tab_spacer_last",
                         array(
                             "margin" => "0px",
                             "padding" => "0px",
                             "background-color" => "#ffffff",
                             "border-bottom" => "1px solid #828282"
                             ));


        $this->add_entry(".tablist", ".tab_data",
                         array(
                             "margin" => "0px",
                             "background-color" => "#ffffff",
                             "border-left" => "1px solid #828282",
                             "border-right" => "1px solid #828282",
                             "border-bottom" => "1px solid #828282"
                             ));


        $this->add_entry(".tablist", ".subtab",
                         array(
                             "margin" => "0px",
                             "padding" => "2px 10px 2px 2px",
                             "background-color" => "#999999",
                             "white-space" => "nowrap"
                             ));


        /**
         * The href links
         */
        $this->add_entry(".tablist", ".tab_link_selected",
                         array(
                             "text-decoration" => "none",
                             "color" => "#ffffff",
                             "font-weight" => "bold"
                             ));

        $this->add_entry(".tablist", ".tab_link_selected:hover",
                         array(
                             "text-decoration" => "none",
                             "color" => "#efefef",
                             "font-weight" => "bold"
                             ));

        $this->add_entry(".tablist", ".tab_link_default",
                         array(
                             "text-decoration" => "none",
                             "color" => "#828282",
                             ));
        $this->add_entry(".tablist", ".tab_link_default:hover",
                         array(
                             "text-decoration" => "none",
                             "color" => "#ffffff",
                             ));


        $this->add_entry(".tablist", ".subtab_link_selected",
                         array(
                             "text-decoration" => "none",
                             "color" => "#ffffff",
                             "font-weight" => "bold"
                             ));

        $this->add_entry(".tablist", ".subtab_link_selected:hover",
                         array(
                             "text-decoration" => "none",
                             "color" => "#efefef",
                             "font-weight" => "bold"
                             ));

        $this->add_entry(".tablist", ".subtab_link_default",
                         array(
                             "text-decoration" => "underline",
                             "color" => "#e1e1e1",
                             ));
        $this->add_entry(".tablist", ".subtab_link_default:hover",
                         array(
                             "text-decoration" => "none",
                             "color" => "#ffffff",
                             ));

	}	
}

?>
