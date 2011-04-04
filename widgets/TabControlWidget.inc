<?php
/**
 * This file contains the TabControlWidget class
 *
 * $Id: TabControlWidget.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Culley Harrelson <culley@fastmail.fm> 
 * @package phpHtmlLib
 * 
 */

/**
 * This class is used for creating a tab control panel.
 *
 * the tab buttons are generated with overlapping background images that grow
 * and shrink depending on the length of text.
 *
 * @author Culley Harrelson <culley@fastmail.fm> 
 * @package phpHtmlLib
 * @link http://alistapart.com/articles/slidingdoors/
 * @link http://alistapart.com/articles/slidingdoors2/
 * @todo figure out a way to hook in a css tab that joins the tab control.  I was having trouble making it work and gave up after a few hours.
 */

class TabControlWidget extends BaseWidget {

    var $_tabs = array();
    var $_align;
    var $_title;

    /**
     * This is the constructor for the TabControlWidget object.
     *
     * @param string - a title string displayed on the opposite side
     * @param string - right or left-- how to align the tab control
     * @todo figure out center alignment
     */
    function TabControlWidget($title=NULL, $align='left') {
        $this->_title = $title;
        $this->_align = $align;
        if (!$this->_align == 'right') {
        }
    }

    /**
     * add a tab.
     *
     * @param ATag - an anchor tag object used for the tab link
     * @param boolean whether or not the tab is the selected tab
     */
    function add_tab($href, $selected=FALSE) {
        $this->_tabs[] = array("href" => $href,
                               "selected" => $selected
                               );
    }

    /**
     * render the widget
     *
     */
    function render($indent_level=1, $output_debug=0) {
        $ul = html_ul();
        if ($this->_align == 'right') {
            $ul->set_style('float: right;');
            $tabs = array_reverse($this->_tabs);
            $tabs = $this->_tabs;
        }

        foreach ($this->_tabs as $tab) {
            $li = html_li($tab['href']);
            if ($tab['selected']) {
                $li->set_class('current');
            }

            $id = strtolower(preg_replace('/\W/', '_', $tab['href']->_content[0])) . '_tab';
            $li->set_id($id);
            $ul->add($li);

        }

        $div = html_div('tabs', $ul);

        if (!is_null($this->_title)) {
            $div->add(_HTML_SPACE);
            $div->add($this->_title);
        }
        return $div->render($indent_level, $output_debug);

    }
}

/**
 * CSS for the tab control
 *
 * @package phpHtmlLib
 */
class TabControlCSS extends CSSBuilder {
    function user_setup() {

        $this->add_entry('.tabs', '',
                         array(
                             'float' => 'left',
                             'width' => '100%',
                             'background' => "#fff url('" . PHPHTMLLIB_RELPATH . "/images/widgets/tabs_bg.gif') repeat-x bottom",
                             'font-size' => '1.0em',
                             'line-height' => 'normal',
                             'font-family' => 'Veranda, Arial, Helvetica, sans-serif',
                             'font-weight' => 'normal',
                             'font-size' => '12px',
                             'margin-top' => '10px',
                             'margin-bottom' => '10px'
                             )
                         );
        $this->add_entry('.tabs', 'ul',
                         array(
                             'margin' => '0',
                             'padding' => '3px 5px 0',
                             'list-style' => 'none'
                             )
                         );
        $this->add_entry('.tabs', 'li',
                         array(
                             'float' => 'left',
                             'background' => "url('" . PHPHTMLLIB_RELPATH . "/images/widgets/tab_left.gif') no-repeat left top",
                             'margin' => '0',
                             'padding' => '0 0 0 6px',
                             'border-bottom' => '1px solid #666'
                             )
                         );
        $this->add_entry('.tabs', 'a',
                         array(
                             'float' => 'left',
                             'display' => 'block',
                             'width' => '.1em',
                             'background' => "url('" . PHPHTMLLIB_RELPATH . "/images/widgets/tab_right.gif') no-repeat right top",
                             'padding' => '5px 6px 4px 2px',
                             'text-decoration' => 'none',
                             'font-weight' => 'bold',
                             'color' => '#666'
                             )
                         );
        $this->add_entry('.tabs', 'ul a', array('width' => 'auto'));
        $this->add_entry('.tabs', 'a:hover', array('color' => '#333'));
        $this->add_entry('.tabs', '.current', array('background-position' => '0 -150px', 'border-width' => '0'));
        $this->add_entry('.tabs', '.current a', array('background-position' => '100% -150px', 'padding-bottom' => '5px', 'color' => '#333'));
        $this->add_entry('.tabs', 'li:hover, .header li:hover a', array('background-position' => '0 -150px', 'color' => '#333'));
        $this->add_entry('.tabs', 'li:hover a', array('background-position' => '100% -150px'));
    }
}


?>
