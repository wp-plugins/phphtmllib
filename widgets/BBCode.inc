<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 *
 * $Id: BBCode.inc,v 1.2 2005/09/13 10:18:34 mike Exp $
 *
 * BBCode tag support - this class implements BBCode support in a 
 * style consistent with phpHtmlLib using PEAR's HTML/BBCodeParser
 * class.
 *
 * (c) 2005 by Mike Walsh
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 * @subpackage BBCode
 * @version $Revision: 1.2 $
 * @lastmodified $Date: 2005/09/13 10:18:34 $
 * @lastmodifiedby $Author: mike $
 * @see http://pear.php.net/package/HTML_BBCodeParser
 * @see http://www.usrportage.de/article/bbcode.class.php-an-advanced-implemention-of-bbcode.html
 *
 */

//  This code makes use of the PEAR BBCode Parser class

require_once("PEAR.php") ;
require_once("HTML/BBCodeParser.php") ;

/**
 * BBCodeTeatArea class widget.  A text area widget to
 * input and parse BBCode formatted text.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see FETextArea
 */
class FEBBCodeTextArea extends FETextArea
{
    /**
     *  Newline breaking property
     */
    var $_nl2br = false ;

    /**
     *  HTML tag stripping property
     */
    var $_strip_tags = true ;

    /**
     * CSS class to wrap parsed text in
     */
    var $_wrapper_class = null ;

    /**
     * Default header size
     *
     */
    var $_header_size = 3 ;

    /**
     * Set the flag for handling newlines
     *
     */
    function set_nl2br($nl2br = true)
    {
        $this->_nl2br = $nl2br ;
    }

    /**
     * Get the flag for handling newlines
     *
     * @return boolean - true to map newlines to BR tags
     */
    function get_nl2br()
    {
        return $this->_nl2br ;
    }

    /**
     * Set the flag for stripping HTML tags in the input
     *
     */
    function set_strip_tags($strip_tags = true)
    {
        $this->_strip_tags = $strip_tags ;
    }

    /**
     * Get the flag for stripping HTML tags in the input
     *
     * @return boolean - true to strip tags
     */
    function get_strip_tags()
    {
        return $this->_strip_tags ;
    }

    /**
     * Set the class for wrapping parsed text in
     *
     */
    function set_wrapper_class($wrapper_class = null)
    {
        $this->_wrapper_class = $wrapper_class ;
    }

    /**
     * Get the class for wrapping parsed text in
     *
     * @return string - name of the class
     */
    function get_wrapper_class()
    {
        return $this->_wrapper_class ;
    }

    /**
     * Sets the size of header text used by the [h] tag
     *
     * @author   Mike Walsh  <mike_walsh@mindspring.com>
     * @access   public
     * @param int - size of header (1-6)
     * @return   none
     */
    function set_header_size($size)
    {
        if (is_integer($size))
        {
            if (($size >= 1) && ($size <= 6))
            {
                $this->_header_size = $size ;
            }
        }
    }

    /**
     * Get the header size
     *
     * @return int - header size 1-6 (h1-h6)
     */
    function get_header_size()
    {
        return $this->_header_size ;
    }

    /**
     * This provides an overridden method for the FormContent
     * to get access to the text associated with a field.  This
     * is only available on FEBBCodeTextArea elements.
     * It is used during Confirmation and parses the BBCode so
     * the confirmation page displays the text as it will appear
     * when rendered as HTML.
     *
     * @param mixed the value to look up
     * @return string - the text associated
     */
    function get_value_text()
    {
        return html_div($this->get_wrapper_class(), $this->get_parsed_value()) ;
    }

    /**
     * This function will return the elements value
     *
     * @return mixed
     */

    function get_value()
    {
        //  Get value from the form element
        $value = parent::get_value() ;

        //  Strip HTML tags?
        if ($this->get_strip_tags())
            $value = strip_tags($value) ;

        return $value ;
    }

    /**
     * Parse the BBCode text value
     *
     * @return string - the parsed text
     */
    function get_parsed_value() {
        $bbcode = new BBCodeParser() ;
        $bbcode->setHeaderSize($this->get_header_size()) ;

        if ($this->get_strip_tags())
            $bbcode->setText(strip_tags($this->get_value())) ;
        else
            $bbcode->setText($this->get_value()) ;

        $bbcode->parse();
        $value = $bbcode->getParsed($this->get_nl2br());
        unset($bbcode) ;
        return $value ;
    }
}

/**
 * BBCodeParser class
 *
 * Ideally this class would be an extension of the PEAR
 * HTML_BBCodeParser class but the way the PEAR class is
 * implented, the constructor looks for filter modules.
 *
 * This class essentially implements a wrapper around the
 * PEAR class to provide control over the options.  This
 * class does not implement all of the methods exposed by
 * the PEAR class.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 * @subpackage BBCode
 */
class BBCodeParser
{
    /**  Class variables  **/

    /**
     * Default parser configutation options, include all filters
     *
     */

    var $_options = array(
        'quotestyle'    => 'single',
        'quotewhat'     => 'all',
        'open'          => '[',
        'close'         => ']',
        'xmlclose'      => true,
        'filters'       => 'Basic,Extended,Links,Images,Lists,Email'
    ) ;

    /**
     * Define additional tags not supplied by the PEAR class.
     * The [h] tags maps to <h2> but can be changed by the 
     * applications.  For some odd reason the PEAR class doesn't
     * recognize tags with numeric values.  :-(
     *
     */
    var $_extendedTags = array( 'p' => array(   'htmlopen'  => 'p',
                                                'htmlclose' => 'p',
                                                'allowed'   => 'all',
                                                'attributes'=> array()),
                                'br' => array(  'htmlopen'  => 'br',
                                                'htmlclose' => '',
                                                'allowed'   => 'none',
                                                'attributes'=> array()),
                                'hr' => array(  'htmlopen'  => 'hr',
                                                'htmlclose' => '',
                                                'allowed'   => 'none',
                                                'attributes'=> array()),
                                'h' => array(   'htmlopen'  => 'h',
                                                'htmlclose' => 'h',
                                                'allowed'   => 'all',
                                                'attributes'=> array())
                            );

    /**
     * Store the handle to the PEAR Parser
     *
     */
    var $_parser ;

    /**
     * Default header size
     *
     */
    var $_headerSize = 3 ;

    /**
     * The constructor
     *
     * @author   Mike Walsh  <mike_walsh@mindspring.com>
     * @access   public
     * @param array - BBCode parser options
     * @param boolean - flag to map "code" tags to "pre" tags
     */
    function BBCodeParser($options = array(), $mapCode2Pre = true, $extendedBasic = true)
    {
        //  If parser is construction without
        //  options, use the default options.

        if (empty($options))
            $options = $this->_options ;

        //  Create an instance of the PEAR HTML_BBCodeParser

        $this->_parser = new HTML_BBCodeParser($options) ;

        //  CSS for the <code> tags appears to be handled very
        //  strangely (both in IE and FireFox) so offer the option
        //  to map <code> tags to <pre> tags which are handled
        //  correctly.

        if ($mapCode2Pre)
        {
            $this->_parser->_definedTags["code"]["htmlopen"] = "pre" ;
            $this->_parser->_definedTags["code"]["htmlclose"] = "pre" ;
        }

        //  Extend the set of tags supported by 'Basic'?
        //  Added tags to the PEAR class is hokey as the author
        //  expected new 'filters' to be written and loaded into
        //  the PEAR repository installed on the web server.
        //  This is somewhat idealistic as the end application
        //  most likely can't modify PEAR.
        //
        //  Work-around the limitation by pre-loading the 'Basic'
        //  filter and adding additional tags to it.

        if ($extendedBasic)
        {
            $this->_parser->_definedTags =
                array_merge($this->_parser->_definedTags, $this->_extendedTags) ;
            $this->_parser->_filters['Basic']->_definedTags =
                array_merge($this->_parser->_filters['Basic']->_definedTags,
                $this->_extendedTags) ;

            $this->_parser->_definedTags["h"]["htmlopen"] .= $this->_headerSize;
            $this->_parser->_definedTags["h"]["htmlclose"] .= $this->_headerSize;
        }
    }

    /**
     * Sets the size of header text used by the [h] tag
     *
     * @author   Mike Walsh  <mike_walsh@mindspring.com>
     * @access   public
     * @param int - size of header (1-6)
     * @return   none
     */
    function setHeaderSize($size)
    {
        if (is_integer($size))
        {
            if (($size >= 1) && ($size <= 6))
            {
                $this->_headerSize = $size ;
                $this->_parser->_definedTags["h"]["htmlopen"] = "h" . $size ;
                $this->_parser->_definedTags["h"]["htmlclose"] = "h" . $size ;
            }
        }
    }

    /**
     * Sets text in the object to be parsed
     *
     * @author   Mike Walsh  <mike_walsh@mindspring.com>
     * @access   public
     * @param    string - the text to set in the object
     * @return   none
     */
    function setText($str)
    {
        $this->_parser->setText($str) ;
    }

    /**
     * Parses the text set in the object
     *
     * @author   Mike Walsh  <mike_walsh@mindspring.com>
     * @access   public
     * @return   none
     */
    function parse()
    {
        $this->_parser->parse() ;
    }

    /**
     * Gets the parsed text from the object
     *
     * @author   Mike Walsh  <mike_walsh@mindspring.com>
     * @access   public
     * @return   string - the parsed text set in the object
     */
    function getParsed($nl2br = false)
    {
        $parsed = $this->_parser->getParsed() ;

        //  insert line breaks?

        if ($nl2br) $parsed = nl2br($parsed) ;

        return $parsed ;
    }
}

/**
 * FEBBCodeTextAreaWidget class
 *
 * Implementation of a FETextArea widget with BBCode drop
 * down list controls to insert BBCode tags into the textarea
 * widget.
 * 
 * This functionality is implemented as a static class.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 * @subpackage BBCode
 * @static
 */
class FEBBCodeTextAreaWidget
{
    /**
     * The constructor
     *
     * @author   Mike Walsh  <mike_walsh@mindspring.com>
     * @access   public
     * @param string - name of the Form where the FETextArea lives
     * @param Object - the FETextArea form element
     * @param Object - the FETextArea element form 
     * @param boolean - add BBCode help
     */
    function FEBBCodeTextAreaWidget($FormName, $TextAreaElement, $FETextArea, $help = true)
    {
        //  Need the name of the FETextArea element

        $TextAreaName = $TextAreaElement->get_element_name() ;

        //  If the FETextArea is read-only then add bogus Javascript

        $readOnly = $TextAreaElement->is_readonly() ;

        //  Javascript string to call the insertAtCursor() function

        $jsList = "javascript:insertAtCursor(document.%s.%s, '['+document.%s.%s.options[this.selectedIndex].value+'][/'+document.%s.%s.options[this.selectedIndex].value+']');document.%s.%s.options[0].selected=true;" ;

        //  Build the Format Drop Listbox
        $format = FEBBCodeTextAreaWidget::BBCodeFormatListBox() ;
        $formatTag = $format->get_element() ;
        $FormatTagName = $format->get_element_name() ;

        $formatTag->set_tag_attribute("onchange", sprintf($jsList, $FormName,
            $TextAreaName, $FormName, $FormatTagName, $FormName, $FormatTagName,
            $FormName, $FormatTagName)) ;

        if ($readOnly)
            $formatTag->set_tag_attribute("onchange", "javascript:void(0);") ;

        //  Build the List Drop Listbox
        $list = FEBBCodeTextAreaWidget::BBCodeListListBox() ;
        $listTag = $list->get_element() ;
        $ListTagName = $list->get_element_name() ;

        $listTag->set_tag_attribute("onchange", sprintf($jsList, $FormName,
            $TextAreaName, $FormName, $ListTagName, $FormName, $ListTagName,
            $FormName, $ListTagName)) ;

        if ($readOnly)
            $listTag->set_tag_attribute("onchange", "javascript:void(0);") ;

        //  Javascript string to call the insertAtCursor() function
        
        $jsList = "javascript:insertAtCursor(document.%s.%s, '[%s='+document.%s.%s.options[this.selectedIndex].value+'][/%s]');document.%s.%s.options[0].selected=true;" ;

        //  Build the Align Drop Listbox
        $align = FEBBCodeTextAreaWidget::BBCodeAlignListBox() ;
        $alignTag = $align->get_element() ;
        $AlignTagName = $align->get_element_name() ;

        $alignTag->set_tag_attribute("onchange", sprintf($jsList, $FormName,
            $TextAreaName, "align", $FormName, $AlignTagName, "align",
            $FormName, $AlignTagName)) ;

        if ($readOnly)
            $alignTag->set_tag_attribute("onchange", "javascript:void(0);") ;

        //  Build the Font Drop Listbox
        $font = FEBBCodeTextAreaWidget::BBCodeFontListBox() ;
        $fontTag = $font->get_element() ;
        $FontTagName = $font->get_element_name() ;

        $fontTag->set_tag_attribute("onchange", sprintf($jsList, $FormName,
            $TextAreaName, "font", $FormName, $FontTagName, "font", $FormName,
            $FontTagName)) ;

        if ($readOnly)
            $fontTag->set_tag_attribute("onchange", "javascript:void(0);") ;

        //  Build the Size Drop Listbox
        $size = FEBBCodeTextAreaWidget::BBCodeSizeListBox() ;
        $sizeTag = $size->get_element() ;
        $SizeTagName = $size->get_element_name() ;

        $sizeTag->set_tag_attribute("onchange", sprintf($jsList, $FormName,
            $TextAreaName, "size", $FormName, $SizeTagName, "size", $FormName,
            $SizeTagName)) ;

        if ($readOnly)
            $sizeTag->set_tag_attribute("onchange", "javascript:void(0);") ;

        //  Build the Color Drop Listbox
        $color = FEBBCodeTextAreaWidget::BBCodeColorListBox() ;
        $colorTag = $color->get_element() ;
        $ColorTagName = $color->get_element_name() ;

        $colorTag->set_tag_attribute("onchange", sprintf($jsList, $FormName,
            $TextAreaName, "color", $FormName, $ColorTagName, "color",
            $FormName, $ColorTagName)) ;

        if ($readOnly)
            $colorTag->set_tag_attribute("onchange", "javascript:void(0);") ;

        //  Put all of the dropdown lists in a DIV,
        //  add a break, then add the original text area

        $div = html_div("bbcodetextarea") ;

        //  Add the Help option?

        if ($help)
        {
            $img = html_img(PHPHTMLLIB_RELPATH . "/images/widgets/tree_closed.gif") ;
            $img->set_id("i" . $FormName . "_" . "bbcodehelptext") ;

            $helpSpan = html_span("bbcodehelp",
                html_a("javascript:toggle_help('" .  $FormName . "_" .
                "bbcodehelptext');", $img), html_b("Help")) ;
            $helpDiv = FEBBCodeTextAreaWidget::BBCodeHelp($FormName) ;
        }
        else
        {
            $helpSpan = null ;
            $helpDiv = null ;
        }

        $div->add($formatTag->render(), $alignTag->render(),
            $sizeTag->render(), $colorTag->render(), $fontTag->render(),
            $listTag->render(), $helpSpan, html_br(), $FETextArea, $helpDiv) ;

        //  Put everything in a container and return it to the caller

        $container = container() ;

        $container->add($div) ;

        return $container ;
    }

    /**
     * Return a listbox containing BBCode tags.
     *
     * @author Mike Walsh  <mike_walsh@mindspring.com>
     * @access private
     * @return FEListBox - a listbox object containing the tags
     */
    function BBCodeFormatListBox()
    {
        $ListBox = new FEListBox("Tag", false, "100px", NULL,
            array(
                "Tag" => ""
               ,"Paragraph" => "p"
               ,"Bold" => "b"
               ,"Underline" => "u"
               ,"Italtic" => "i"
               ,"Strike Thru" => "s"
               ,"Subscript" => "sub"
               ,"Superscript" => "sup"
               ,"Code" => "code"
               ,"URL" => "url"
               ,"E-Mail" => "email"
               ,"Image" => "img"
               ,"Quote" => "quote"
               ,"Heading" => "h"
               ,"Separator" => "hr"
               ,"Break" => "br"
            )
        ) ;

        return $ListBox ;
    }

    /**
     * Return a listbox containing BBCode tags.
     *
     * @author Mike Walsh  <mike_walsh@mindspring.com>
     * @access private
     * @return FEListBox - a listbox object containing the tags
     */
    function BBCodeAlignListBox()
    {
        $ListBox = new FEListBox("Align", false, "75px", NULL,
            array(
                "Align"  => ""
               ,"Left"   => "left"
               ,"Center" => "center"
               ,"Right"  => "right"
            )
        ) ;

        return $ListBox ;
    }

    /**
     * Return a listbox containing BBCode tags.
     *
     * @author Mike Walsh  <mike_walsh@mindspring.com>
     * @access private
     * @return FEListBox - a listbox object containing the tags
     */
    function BBCodeSizeListBox()
    {
        $ListBox = new FEListBox("Size", false, "75px", NULL,
            array(
                "Size" => ""
               ,"6"    => "6"
               ,"8"    => "8"
               ,"9"    => "9"
               ,"10"    => "10"
               ,"12"    => "12"
               ,"16"    => "16"
               ,"18"    => "18"
               ,"24"    => "24"
               ,"32"    => "32"
            )
        ) ;

        return $ListBox ;
    }

    /**
     * Return a listbox containing BBCode tags.
     *
     * @author Mike Walsh  <mike_walsh@mindspring.com>
     * @access private
     * @return FEListBox - a listbox object containing the tags
     */
    function BBCodeFontListBox()
    {
        $ListBox = new FEListBox("Font", false, "75px", NULL,
            array(
                "Font"    => ""
               ,"Arial"   => "Arial"
               ,"Times"   => "Times"
               ,"Courier" => "Courier"
               ,"Century" => "Century"
               ,"Verdana" => "Verdana"
            )
        ) ;

        return $ListBox ;
    }

    /**
     * Return a listbox containing BBCode tags.
     *
     * @author Mike Walsh  <mike_walsh@mindspring.com>
     * @access private
     * @return FEListBox - a listbox object containing the tags
     */
    function BBCodeListListBox()
    {
        return new FEListBox("List", false, "75px", NULL,
            array(
                "List" => ""
               ,"Ordered" => "list"
               ,"Unordered" => "ulist"
               ,"List Item" => "li"
            )
        ) ;
    }

    /**
     * Return a listbox containing BBCode tags.
     *
     * @author Mike Walsh  <mike_walsh@mindspring.com>
     * @access private
     * @return FEListBox - a listbox object containing the tags
     */
    function BBCodeColorListBox()
    {
        return new FEListBox("Color", false, "100px", NULL,
            array(
                "Color" => ""
               ,"Sky Blue" => "skyblue"
               ,"Royal Blue" => "royalblue"
               ,"Blue" => "blue"
               ,"Dark Blue" => "darkblue"
               ,"Orange" => "orange"
               ,"Orange Red" => "orangered"
               ,"Crimson" => "crimson"
               ,"Red" => "red"
               ,"Firebrick" => "Firebrick"
               ,"Dark Red" => "darkred"
               ,"Green" => "green"
               ,"Lime Green" => "limegreen"
               ,"Sea Green" => "seagreen"
               ,"Deep Pink" => "deeppink"
               ,"Tomato" => "tomato"
               ,"Coral" => "coral"
               ,"Purple" => "purple"
               ,"Indigo" => "indigo"
               ,"Burly Wood" => "burlywood"
               ,"Sandy Brown" => "sandybrown"
               ,"Sienna" => "sienna"
               ,"Chocolate" => "chocolate"
               ,"Teal" => "teal"
               ,"Silver" => "silver"
            )
        ) ;
    }

    /**
     * Javascript code to allow insertion of text at the
     * cursor location of a text area.  This code is based
     * on the code found on Alex King's web site who stated
     * it originated with phpMyAdmin.  This code needs to be
     * added to the head of the document using the PageWidget's
     * add_head_js() method in order for the BBCode selectors
     * to work properly.
     *
     * @author Mike Walsh <mike_walsh@mindspring.com>
     * @see http://www.alexking.org/blog/2003/06/02/inserting-at-the-cursor-using-javascript/
     *
     */
    function BBCodeJavascript()
    {
        $lib = PHPHTMLLIB_RELPATH ;

        $js = "
            //<!--

            //  Expand Icon
            var help_open = new Image() ;
            help_open.src = '{$lib}/images/widgets/tree_open.gif' ;

            //  Collapse Icon
            var help_closed = new Image() ;
            help_closed.src = '{$lib}/images/widgets/tree_closed.gif' ;

            //  Toggle Help On/Off
            function toggle_help(id)
            {
                element = document.getElementById(id) ;

                if (!element) return ;

                img = document.getElementById('i' + id) ;

                if (element.style.display == 'none' || element.style.display == '')
                {
                    element.style.display = 'block' ;
                    img.src = help_open.src ;
                }
                else
                {
                    element.style.display = 'none' ;
                    img.src = help_closed.src ;
                }

                /*
                if (element.style.visibility=='visible' || element.style.visibility=='')
                {
                    element.style.visibility = 'hidden';
                    element.style.overflow = 'hidden';
                    element.style.height='1px';
                    img.src = help_closed.src;
                }
                else
                {
                    element.style.visibility = 'visible';
                    element.style.overflow = 'visible';
                    element.style.height='';
                    img.src = help_open.src;
                }
                */
            }
            
            //  Insert text at the cursor location

            function insertAtCursor(targetField, targetValue)
            {
                //  If the text area is disabled, don't even try

                if (targetField.disabled) return ;

                //  IE support
                if (document.selection)
                {
                    targetField.focus() ;
                    sel = document.selection.createRange() ;
                    sel.text = targetValue ;
                }
                //  MOZILLA/NETSCAPE support
                else if (targetField.selectionStart || targetField.selectionStart == '0')
                {
                    var startPos = targetField.selectionStart;
                    var endPos = targetField.selectionEnd;
                    targetField.value = targetField.value.substring(0, startPos)
                        + targetValue
                        + targetField.value.substring(endPos, targetField.value.length);
                }
                else
                {
                    targetField.value += targetValue;
                }
            }
            //-->
            " ;

        return $js ;
    }

    /**
     * Return a DIVTag containing the BBCode help text
     *
     * @author Mike Walsh  <mike_walsh@mindspring.com>
     * @access private
     * @return DIVTag - a DIV tag containing the BBCode help text
     */
    function BBCodeHelp($prefix = "")
    {
        $div = html_div("bbcodehelptext") ;
        $div->set_id($prefix . "_" . "bbcodehelptext") ;

        $tab = new ActiveTab("100%", "400px") ;
        
        $tags = array(
            "Bold" => "b"
           ,"Underline" => "u"
           ,"Italtic" => "i"
           ,"Strike Thru" => "s"
           ,"Subscript" => "sub"
           ,"Superscript" => "sup"
           ,"Paragraph" => "p"
           ,"Heading" => "h"
        ) ;

        $parser = new BBCodeParser() ;
        $text = "The quick brown fox jumped over the lazy dog." ;

        $thead = html_thead() ;
        $th1 = html_th("Effect") ;
        $th1->set_class("bbcodehelptext") ;

        $th2 = html_th("Tag") ;
        $th2->set_class("bbcodehelptext") ;

        $th3 = html_th("Example") ;
        $th3->set_class("bbcodehelptext") ;

        $thead->add_row($th1, $th2, $th3) ;

        //  Example format tags

        $table = html_table("100%", 0, 0, 2, "left") ;
        $table->set_class("bbcodehelptext") ;
        $table->add($thead) ;

        foreach ($tags as $tag => $key)
        {
            $td1 = html_td("bbcodehelptextbold", null, $tag) ;
            $td1->set_rowspan(2) ;
            $td1->set_style("border-left: 0px") ;
            $td2 = html_td("bbcodehelptextbold", null, $key) ;
            $td2->set_rowspan(2) ;
            $td3 = html_td("bbcodehelptext",
                null, sprintf("[%s]%s[/%s]", $key, $text, $key)) ;
            $parser->setText(sprintf("[%s]%s[/%s]", $key, $text, $key)) ;
            $parser->parse() ;
            $td4 = html_td("bbcodehelptext", null, $parser->getParsed()) ;

            $table->add_row($td1, $td2, $td3) ;
            $table->add_row($td4) ;
        }

        //  Add the format tags to the ActiveTab widget

        $tab->add_tab("Format Tags", $table) ;

        //  Example Font Sizes

        $table = html_table("100%", 0, 0, 2, "left") ;
        $table->set_class("bbcodehelptext") ;

        $table->add($thead) ;

        $sizes = array("6" => "6", "8" => "8", "9" => "9",
            "10" => "10", "12" => "12", "16" => "16", "18" => "18") ;

        $td1 = html_td("bbcodehelptextbold", null, "Font Size") ;
        $td1->set_rowspan(2 * count($sizes)) ;
        $td1->set_style("border-left: 0px") ;
        $td2 = html_td("bbcodehelptextbold", null, "size") ;
        $td2->set_rowspan(2 * count($sizes)) ;

        $firstRow = true ;

        foreach ($sizes as $size => $key)
        {
            $td3 = html_td("bbcodehelptext",
                null, sprintf("[size=%s]%s[/size]", $key, $text)) ;
            $parser->setText(sprintf("[size=%s]%s[/size]", $key, $text)) ;
            $parser->parse() ;
            $td4 = html_td("bbcodehelptext", null, $parser->getParsed()) ;

            if ($firstRow)
            {
                $table->add_row($td1, $td2, $td3) ;
                $firstRow = false ;
            }
            else
            {
                $table->add_row($td3) ;
            }

            $table->add_row($td4) ;
        }

        //  Add the format tags to the ActiveTab widget

        $tab->add_tab("Font Sizes", $table) ;

        //  Example Font Families

        $table = html_table("100%", 0, 0, 2, "left") ;
        $table->set_class("bbcodehelptext") ;

        $table->add($thead) ;

        $fonts = array("arial" => "Arial", "times" => "Times", 
            "courier" => "Courier", "century" => "Century",
            "verdana" => "Verdana") ;

        $td1 = html_td("bbcodehelptextbold", null, "Font Family") ;
        $td1->set_rowspan(2 * count($fonts)) ;
        $td1->set_style("border-left: 0px") ;
        $td2 = html_td("bbcodehelptextbold", null, "font") ;
        $td2->set_rowspan(2 * count($fonts)) ;

        $firstRow = true ;

        foreach ($fonts as $font => $key)
        {
            $td3 = html_td("bbcodehelptext",
                null, sprintf("[font=%s]%s[/font]", $key, $text)) ;
            $parser->setText(sprintf("[font=%s]%s[/font]", $key, $text)) ;
            $parser->parse() ;
            $td4 = html_td("bbcodehelptext", null, $parser->getParsed()) ;

            if ($firstRow)
            {
                $table->add_row($td1, $td2, $td3) ;
                $firstRow = false ;
            }
            else
            {
                $table->add_row($td3) ;
            }

            $table->add_row($td4) ;
        }

        $tab->add_tab("Font Families", $table) ;

        //  Example Color

        $table = html_table("100%", 0, 0, 2, "left") ;
        $table->set_class("bbcodehelptext") ;

        $table->add($thead) ;

        $colors = array("red" => "Red", "blue" => "Blue",
            "green" => "Green", "yellow" => "Yellow",
            "orange" => "Orange", "silver" => "Silver",
            "limegreen" => "LimeGreen", "purple" => "Purple") ;

        $td1 = html_td("bbcodehelptextbold", null, "Color") ;
        $td1->set_rowspan(2 * count($colors)) ;
        $td1->set_style("border-left: 0px") ;
        $td2 = html_td("bbcodehelptextbold", null, "color") ;
        $td2->set_rowspan(2 * count($colors)) ;

        $firstRow = true ;

        foreach ($colors as $color => $key)
        {
            $td3 = html_td("bbcodehelptext",
                null, sprintf("[color=%s]%s[/color]", $key, $text)) ;
            $parser->setText(sprintf("[color=%s]%s[/color]", $key, $text)) ;
            $parser->parse() ;
            $td4 = html_td("bbcodehelptext", null, $parser->getParsed()) ;

            if ($firstRow)
            {
                $table->add_row($td1, $td2, $td3) ;
                $firstRow = false ;
            }
            else
            {
                $table->add_row($td3) ;
            }

            $table->add_row($td4) ;
        }

        $tab->add_tab("Color", $table) ;

        //  Example Alignment

        $table = html_table("100%", 0, 0, 2, "left") ;
        $table->set_class("bbcodehelptext") ;

        $table->add($thead) ;

        $aligns = array("left" => "Left", "center" => "Center", "right" => "Right") ;

        $td1 = html_td("bbcodehelptextbold", null, "Alignment") ;
        $td1->set_rowspan(2 * count($aligns)) ;
        $td1->set_style("border-left: 0px") ;
        $td2 = html_td("bbcodehelptextbold", null, "align") ;
        $td2->set_rowspan(2 * count($aligns)) ;

        $firstRow = true ;

        foreach ($aligns as $align => $key)
        {
            $td3 = html_td("bbcodehelptext",
                null, sprintf("[align=%s]%s[/align]", $key, $text)) ;
            $parser->setText(sprintf("[align=%s]%s[/align]", $key, $text)) ;
            $parser->parse() ;
            $td4 = html_td("bbcodehelptext", null, $parser->getParsed()) ;

            if ($firstRow)
            {
                $table->add_row($td1, $td2, $td3) ;
                $firstRow = false ;
            }
            else
            {
                $table->add_row($td3) ;
            }

            $table->add_row($td4) ;
        }

        $tab->add_tab("Align", $table) ;

        //  Example URL

        $table = html_table("100%", 0, 0, 2, "left") ;
        $table->set_class("bbcodehelptext") ;

        $table->add($thead) ;

        $label = "Google" ;
        $text = "http://www.google.com" ;

        $td1 = html_td("bbcodehelptextbold", null, "URL") ;
        $td1->set_rowspan(4) ;
        $td1->set_style("border-left: 0px") ;
        $td2 = html_td("bbcodehelptextbold", null, "url") ;
        $td2->set_rowspan(4) ;
        $td3 = html_td("bbcodehelptext",
            null, sprintf("[url]%s[/url]", $text)) ;
        $parser->setText(sprintf("[url]%s[/url]", $text)) ;
        $parser->parse() ;
        $td4 = html_td("bbcodehelptext", null, $parser->getParsed()) ;

        $table->add_row($td1, $td2, $td3) ;
        $table->add_row($td4) ;

        $td3 = html_td("bbcodehelptext",
            null, sprintf("[url=%s]%s[/url]", $text, $label)) ;
        $parser->setText(sprintf("[url=%s]%s[/url]", $text, $label)) ;
        $parser->parse() ;
        $td4 = html_td("bbcodehelptext", null, $parser->getParsed()) ;

        $table->add_row($td3) ;
        $table->add_row($td4) ;

        //  Example E-mail

        $label = "Contact Me" ;
        $text = "nobody@nowhere.com" ;

        $td1 = html_td("bbcodehelptextbold", null, "E-Mail") ;
        $td1->set_rowspan(4) ;
        $td1->set_style("border-left: 0px") ;
        $td2 = html_td("bbcodehelptextbold", null, "email") ;
        $td2->set_rowspan(4) ;
        $td3 = html_td("bbcodehelptext",
            null, sprintf("[email]%s[/email]", $text)) ;
        $parser->setText(sprintf("[email]%s[/email]", $text)) ;
        $parser->parse() ;
        $td4 = html_td("bbcodehelptext", null, $parser->getParsed()) ;

        $table->add_row($td1, $td2, $td3) ;
        $table->add_row($td4) ;

        $td3 = html_td("bbcodehelptext",
            null, sprintf("[email=%s]%s[/email]", $text, $label)) ;
        $parser->setText(sprintf("[email=%s]%s[/email]", $text, $label)) ;
        $parser->parse() ;
        $td4 = html_td("bbcodehelptext", null, $parser->getParsed()) ;

        $table->add_row($td3) ;
        $table->add_row($td4) ;

        //  Example Image

        $img = "http://phphtmllib.newsblob.com/images/phphtmllib_logo.png" ;
        $attr = "w=88 h=31" ;

        $td1 = html_td("bbcodehelptextbold", null, "Image") ;
        $td1->set_rowspan(4) ;
        $td1->set_style("border-left: 0px") ;
        $td2 = html_td("bbcodehelptextbold", null, "img") ;
        $td2->set_rowspan(4) ;
        $td3 = html_td("bbcodehelptext",
            null, sprintf("[img]%s[/img]", $img)) ;
        $parser->setText(sprintf("[img]%s[/img]", $img)) ;
        $parser->parse() ;
        $td4 = html_td("bbcodehelptext", null, $parser->getParsed()) ;

        $table->add_row($td1, $td2, $td3) ;
        $table->add_row($td4) ;

        $td3 = html_td("bbcodehelptext",
            null, sprintf("[img=%s]%s[/img]", $attr, $img)) ;
        $parser->setText(sprintf("[img %s]%s[/img]", $attr, $img)) ;
        $parser->parse() ;
        $td4 = html_td("bbcodehelptext", null, $parser->getParsed()) ;

        $table->add_row($td3) ;
        $table->add_row($td4) ;

        $tab->add_tab("Links", $table) ;

        //  Example Unordered List

        $table = html_table("100%", 0, 0, 2, "left") ;
        $table->set_class("bbcodehelptext") ;

        $table->add(html_thead($th1, $th2, $th3, $th1, $th2, $th3)) ;

        $list = "[ulist]\n[*]Item 1\n[*]Item 2\n[*]Item 3\n[/ulist]" ;

        $td1 = html_td("bbcodehelptextbold", null, "Unordered", html_br(), "List") ;
        $td1->set_rowspan(4) ;
        $td1->set_style("border-left: 0px;") ;
        $td2 = html_td("bbcodehelptextbold", null, "ulist") ;
        $td2->set_rowspan(4) ;
        $td3 = html_td("bbcodehelptext",
            null, sprintf("%s", nl2br($list))) ;
        $parser->setText(sprintf("%s", $list)) ;
        $parser->parse() ;
        $td4 = html_td("bbcodehelptext", null, $parser->getParsed(false)) ;

        //$table->add_row($td1, $td2, $td3) ;
        //$table->add_row($td4) ;

        //  Example Ordered List

        $list = "[list=1]\n[*]Item 1\n[*]Item 2\n[*]Item 3\n[/list]" ;

        $td5 = html_td("bbcodehelptextbold", null, "Ordered", html_br(), "List") ;
        $td5->set_rowspan(4) ;
        $td6 = html_td("bbcodehelptextbold", null, "list") ;
        $td6->set_rowspan(4) ;

        $td7 = html_td("bbcodehelptext",
            null, sprintf("%s", nl2br($list))) ;
        $parser->setText(sprintf("%s", $list)) ;
        $parser->parse() ;
        $td8 = html_td("bbcodehelptext", null, $parser->getParsed(false)) ;

        $table->add_row($td1, $td2, $td3, $td5, $td6, $td7) ;
        $table->add_row($td4, $td8) ;

        $list = "[ulist]\n[li]unordered item 1\n[ulist]\n[li]nested item 1[/li]\n[li]nested item 2[/li]\n[/ulist][/li]\n[li]unordered item 2[/li]\n[/ulist]" ;

        $td3 = html_td("bbcodehelptext",
            null, sprintf("%s", nl2br($list))) ;
        $parser->setText(sprintf("%s", $list)) ;
        $parser->parse() ;
        $td4 = html_td("bbcodehelptext", null, $parser->getParsed(false)) ;

        $list = "[list=A s=3]\n[li]ordered item 1\n[list=I]\n[li]nested item 1[/li]\n[li]nested item 2[/li]\n[/list][/li]\n[li]ordered item 2[/li]\n[/list]" ;
        
        $td7 = html_td("bbcodehelptext",
            null, sprintf("%s", nl2br($list))) ;
        $parser->setText(sprintf("%s", $list)) ;
        $parser->parse() ;
        $td8 = html_td("bbcodehelptext", null, $parser->getParsed(false)) ;

        $table->add_row($td3, $td7) ;
        $table->add_row($td4, $td8) ;

        $tab->add_tab("Lists", $table) ;


        //  In order to get the ActiveTab to work on a form, the
        //  Javascript must be manually added (this is a bug).

        $script = html_script() ;
        $script->add($tab->get_javascript()) ;
        $div->add($script, html_br(), $tab) ;

        return $div ;
    }
}

/**
 * This class defines the css used by the bbCode Object.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib 
 */

class BBCodeCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry(".bbcodetextarea", null,
                         array("padding" => "3px",
                               "font-family" => "arial, helvetica, sans-serif",
                               "height" => "auto",
                               "border" => "1px solid #999999",
                               "font-size" => "10pt")) ;

        $this->add_entry(".bbcodetextarea", "pre",
                         array("font-size" => "8pt",
                               "font-weight" => "bold",
                               "font-family" => "verdana",
                               "color" => "blue",
                               "background-color" => "#FFFDF1",
                               "white-space" => "pre",
                               "padding" => "10px",
                               "border" => "1px dashed #000000")) ;

        $this->add_entry(".bbcodetextarea", "q",
                         array("font-size" => "10pt",
                               "margin" => "3px",
                               "padding" => "3px",
                               "background-color" => "#D4D0C8",
                               "border" => "1px solid #000000")) ;

        $this->add_entry(".bbcodetextarea", "hr",
                         array("color" => "#000000",
                               "width" => "90%",
                               "height" => "1px",
                               "align" => "center")) ;

        $this->add_entry(".bbcodetextarea", "h1,h2,h3,h4,h5,h6",
                         array("color" => "#000000",
                               "text-align" => "left",
                               "text-transform" => "capitalize")) ;

        $this->add_entry(".bbcodetextarea", "span.bbcodehelp",
                         array("font-size" => "10pt",
                               "font-weight" => "bold",
                               "color" => "black")) ;

        $this->add_entry(".bbcodetextarea", "table.bbcodehelptext",
                         array("border" => '2px solid #999999',
                               "margin" => '0px 5px 5px 0px')) ;

        $this->add_entry(".bbcodetextarea", "th.bbcodehelptext",
                         array("text-align" => 'left',
                               "font-size" => '10pt',
                               "border-bottom" => '1px',
                               "background-color" => '#999999',
                               "color" => 'white')) ;

        $this->add_entry(".bbcodetextarea", "td.bbcodehelptext",
                         array("text-align" => 'left',
                               "vertical-align" => 'top',
                               "border-top" => '1px solid #999999',
                               "border-left" => '1px solid #999999',
                               "font-size" => '9pt',
                               "color" => 'black')) ;

        $this->add_entry(".bbcodetextarea", "td.bbcodehelptextbold",
                         array("text-align" => 'left',
                               "vertical-align" => 'top',
                               "border-top" => '1px solid #999999',
                               "border-left" => '1px solid #999999',
                               "font-size" => '9pt',
                               "font-weight" => 'bold',
                               "color" => 'black')) ;

        $this->add_entry(".bbcodetextarea", "div.bbcodehelptext",
                         array("display" => "none")) ;

    }   
}
?>
