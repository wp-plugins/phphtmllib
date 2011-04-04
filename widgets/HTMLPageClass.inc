<?php

/**
 * This contains the HTMLPageClass widget
 *
 * $Id: HTMLPageClass.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 *
 */

/**
 * Get all the required files for this class
 */
require_once(PHPHTMLLIB_ABSPATH . "/HTMLTagClass.inc");


/**
 * class the constructs and renders an entire
 * HTML/XHTML document.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class HTMLPageClass {

    /**
     * HEADtag object that holds all content
     * for the head.
     * @var  object
     * @access   private
     */
    var $_head = NULL;

    /**
     * TITLEtag object that holds the title
     * of the page.
     * @var  object
     * @access   private
     */
    var $_title = NULL;

    /**
     * SCRIPTtag object that holds javascript
     * code for the head tag.
     * @var  object
     * @access   private
     */
    var $_head_js = NULL;

    /**
     * STYLEtag object that holds css code
     * for the head.
     * @var  object
     * @access   private
     */
    var $_head_style = NULL;

    /**
     * character set to be used in this
     * page.  This gets automatically
     * placed in the Content-Type
     * META tag.
     * @var  string
     * @access   private
     */
    var $_charset = "iso-8859-1";


    /**
     * The encoding of the XHTML
     * XML tag
     */
    var $_xml_encoding = "UTF-8";

    /**
     * BODYtag object that holds all content
     * for the body tag.
     * @var  object
     * @access   private
     */
    var $_body = NULL;

    /**
     * DOCTYPEag object that sets the document
     * type.  This gets rendered prior to <html>
     * @var  object
     * @access   private
     */
    var $_doctype = NULL;

    /**
     * flag to tell the class to try and
     * change the http headers to output
     * document of type text, instead of
     * html.  This is helpfull for debugging.
     * @var boolean
     * @access private
     */
    var $_text_debug = FALSE;

    /**
     * This holds a FRAMESETtag object.
     * This is used if the person is trying
     * to render a frameset page.
     *
     * @var FRAMESETtag object.
     * @access private
     */
    var $_frameset = NULL;


    /**
     * This holds the text used to display
     * a body content when a browser doesn't
     * support framesets
     *
     * @var string
     * @access private
     */
    var $_noframes_text = "Sorry, your browser does not support frames";


    /**
     * This holds the attributes for the
     * <html> tag.
     *
     * @var array
     */
    var $_html_attributes = array();

	/**
	 * keeps track of which widgets we have
	 * automatically pulled in css for
	 *
	 * @var array
	 */
	var $_widget_css_auto = array();

	/**
	 * keeps track of which widgets we have
	 * automatically pulled in js for
	 *
	 * @var array
	 */
	var $_widget_js_auto = array();


	/**
	 * Holds the value of the indent
	 * style the user wants to render
	 * the page w/
	 *
	 * @var int
	 */
	var $_indent_style = 0;

    /**
     * keeps track of the html
     * render type.
     *
     * @var string
     */
    var $_html_render_type = HTML;

    /**
     * The favicon params
     * @var array
     */
    var $_favicon = array("href" => "/favicon.ico",
                          "type" => "images/x-ico",
                          "enabled" => FALSE);



    /**
     * Class Constructor
     * @param   mixed  - $title Title string or TITLEtag object for the page.
     * @param   string - one of 3 types of html to render.  Setting this will
     *                   make the object declare the gobal define which tells
     *                   all of the tag objects what type of html tags to render.
     *                   some tags support special features.  such as the <IMG>
     *                   tag.  If xhtml is selected, the the IMGtag object and all
     *                   utility functions will not render "border=0" as a default
     *                   attribute, since this is not proper xhtml.
     *                   "html" - HTML 4.0 (default)
     *                   "xhtml_transitional" - render xhtml instead of html
     *                                        - doctype is XHTML transitional.
     *                   "xhtml_strict" - render xhtml instead of html 4.0.
     *                                  - doctype is XHTML strict.
	 * @param   int   - one of 2 types.  INDENT_NICE or INDENT_LEFT_JUSTIFY
	 *                  This tells the page how to render the indenting of the
	 *                  output.  By default it is set to INDENT_NICE, which nicely
	 *                  indents each nested tag.  You can have all tags rendered
	 *                  left justified (smaller size in output) by using
	 *                  INDENT_LEFT_JUSTIFY
     *
     * @access   public
     */
    function HTMLPageClass($title=NULL, $html_type=HTML, $indent_style=INDENT_NICE) {

        switch ($html_type) {
		case HTML:
		default:
            $this->build_doctype("-//W3C//DTD HTML 4.01 Transitional//EN",
                                 "http://www.w3.org/TR/html4/loose.dtd");
            $this->_html_render_type = $GLOBALS["HTML_RENDER_TYPE"] = HTML;
            break;

        case XHTML_STRICT:
            $this->build_doctype("-//W3C//DTD XHTML 1.0 Strict//EN",
								 "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd");
            $this->_html_render_type = $GLOBALS["HTML_RENDER_TYPE"] = XHTML_STRICT;
            $this->set_html_attributes( array( "xmlns" => "http://www.w3.org/1999/xhtml",
                                               "xml:lang" => "en",
                                               "lang" => "en") );
            break;

        case XHTML:
        case XHTML_TRANSITIONAL:
            $this->build_doctype("-//W3C//DTD XHTML 1.0 Transitional//EN",
								 "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd");
            $this->_html_render_type = $GLOBALS["HTML_RENDER_TYPE"] = XHTML;
            $this->set_html_attributes( array( "xmlns" => "http://www.w3.org/1999/xhtml",
                                               "xml:lang" => "en",
                                               "lang" => "en") );
            break;

            //What else needs to be done to properly support
            //XHTML frameset?  TODO LIST for 1.1
        case XHTML_FRAMESET:
			$this->build_doctype("-//W3C//DTD XHTML 1.0 Frameset//EN",
								 "http://www.w3.org/TR/xhtml1/DTD/xhtml1-frameset.dtd");
            $this->_html_render_type = $GLOBALS["HTML_RENDER_TYPE"] = XHTML_FRAMESET;
            break;
        }

        $this->_head = new HEADtag;
        $this->_head_js = html_script();
        $this->_head_style = html_style();
        $this->_create_body();
        if ($title != NULL) {
            $this->set_title( $title );
        }

		$this->_indent_style = $indent_style;
    }

    //**************************************************
    //* HEAD tag related functions
    //**************************************************


    /**
     * this adds content to the head tag
     * of the page
     *
     * @param mixed - any content to add
     */
    function add_head_content( ) {
		$num_args = func_num_args();
		for ($i=0;$i<$num_args;$i++) {
			$this->_head->add(func_get_arg($i));
		}
    }

    /**
     * Same ass add_head_content()
     *
     * @deprecated - use add_head_content();
     */
    function push_head_content( ) {
		$args = func_get_args();
        call_user_func_array( array(&$this, "add_head_content"), $args);
    }


    /**
     * adds raw javascript to the head which
     * will automatically get wrapped in a
     * <script language="JavaScript"> tag.
     * @param mixed $content - raw javascript code to add to the head
     */
    function add_head_js( $content ) {
        $this->_head_js->add( $content );
    }

    /**
     * Same ass add_head_js()
     *
     * @deprecated - use add_head_js();
     */
    function push_head_js( $content ) {
        $this->add_head_js( $content );
    }

	/**
	 * this function adds raw css to the
	 * <head> tag.  It will automatically
	 * be wrapped in a <style type="text/css">
	 *
	 * @param string - the raw css
	 */
	function add_head_css( $css ) {
		$this->_head_style->add( $css );
	}

    /**
     *  set the title of the page output.
     *  @param  mixed  $title - the title of the html page
     *                          can be TITLEtag object.
     *
     */
    function set_title( $title ) {
        if (is_object($title)) {
            if ($title->_tag == "title") {
                $this->_title = $title;
            } else {
                //they did something funky here.
                return -1;
            }
        } else {
            $this->_title = html_title( $title );
        }
    }

    /**
     * pushes a css external reference to the head area
     * @param mixed  $link - link tag object or $url for a css.
     * @param string the media attribute (if any)
     */
    function add_css_link( $link, $media=FALSE ) {
        if (is_object($link)) {
            $css = $link;
        } else {
            $css = html_link($link, "stylesheet", "text/css");
            if ($media) {
                $css->set_tag_attribute('media', $media);
            }
        }
		$this->_head->add($css);
    }

    /**
     * Same ass add_css_link()
     *
     * @deprecated - use add_css_link();
     */
    function push_css_link( $link ) {
        $this->add_css_link( $link );

    }

    /**
     * This adds a link to an external Javascript
     * file, which will get rendered in the head.
     *
     * @param  mixed $link - script tag object or $url of .js file.
     */
    function add_js_link( $link ) {
        if (is_object($link)) {
            $js = $link;
        } else {
            $js = html_script($link);
        }
		$this->_head->add($js);
    }

    /**
     * same as add_js_link()
     *
     * @deprecated
     */
    function push_js_link( $link ) {
        $this->add_js_link( $link );
    }

    /**
     * Automatically set a page meta tag refresh
     * @param int     $time - time in seconds to refresh
     * @param string  $url - the url to go to.
     */
    function set_refresh( $time, $url=NULL ) {
        if ($url) {
            $time .= ";url=$url";
        }
        $this->add_head_content( html_meta($time, "refresh") );
    }

    /**
     * set the character set
     * @param string  $charset - the charset for the meta tag
     *
     */
    function set_charset( $charset ) {
        $this->_charset = $charset;
    }

    /**
     * This sets the encoding type for
     * XHTML documents
     *
     * @param string - the encoding parameter
     */
    function set_encoding( $encoding ) {
        $this->_xml_encoding = $encoding;
    }

    /**
     * This method sets the lang, and xml:lang
     * setting in the HTML tag.
     *
     * @param string - the language
     */
    function set_language( $language ) {
        $this->_html_attributes["xml:lang"] = $language;
        $this->_html_attributes["lang"] = $language;
    }

    /**
     * This function is used to set the FRAMSETtag
     * object for this page.  This automatically
     * sets the output for this page object to
     * be a frameset.
     *
     * @param FRAMESETtag object - $frameset
     */
    function set_frameset( $frameset ) {
        if (is_object($frameset)) {
            if ($frameset->get_tag() == "frameset") {
                $this->_frameset = $frameset;
            }
        }
    }


    /**
     * This function returns the
     * attributes to be used for the
     * <html> tag.
     *
     * @return array();
     */
    function get_html_attributes() {
        return $this->_html_attributes;
    }

    /**
     * This function sets the attributes
     * for the <html> tag
     *
     * @param array - the name=>value
     *                pair for the
     *               attributes
     */
    function set_html_attributes( $attributes ) {
        $this->_html_attributes = $attributes;
    }


    /**
     * this builds the content type meta tag.
     *
     */
    function _build_content_type_tag() {
        $content_type = "text/html; charset=" . $this->_charset;
        return html_meta($content_type, "Content-Type");
    }

    /**
     * This is used to enable the ability to add the
     * favicon link in the head of the document.
     * By default it is off.
     *
     * @param boolean TRUE = enable
     */
    function set_favicon_flag($flag=TRUE) {
        $this->_favicon["enabled"] = $flag;
    }

    /**
     * This allows you to change the default url/path
     * for where the favicon.ico lives.
     * NOTE: calling this method automatically enables the
     *       link in the head to be created.
     *
     * @param string the url to the favicon.ico file
     * @param string the type of the image.
     *               NOTE: Default is image/x-ico
     */
    function set_favicon($path, $type="image/x-ico") {
        $this->_favicon["href"] = $path;
        $this->_favicon["type"] = $type;
        $this->set_favicon_flag( TRUE );
    }

    //**************************************************
    //* BODY tag related functions
    //**************************************************


    /**
     * This function adds content to the <body>
     * area of the page.
     *
     * @param mixed - any # of parameters
     */
    function add() {
        $num_args = func_num_args();
        for ($i=0;$i<$num_args;$i++) {
			$arg = func_get_arg($i);
			//see if the arg is an object
			//and a child of BaseWidget.
			if (is_object($arg) && is_subclass_of( $arg, "basewidget")) {
				//see if they have an js they need to include
				$js = "";
				$js = $arg->get_javascript();
				$class_name = get_class($arg);
				if ($js != "" && !isset($this->_widget_js_auto[$class_name])) {
					$this->add_head_js( str_replace(chr(9),'', $js) );
					$this->_widget_js_auto[$class_name] = TRUE;
				}
			}
            $this->_body->add(func_get_arg($i));
        }
    }

    /**
     * Same as add()
     *
     * @deprecated - use add()
     *
     */
    function push( ) {
        $args = func_get_args();
        call_user_func_array( array(&$this, "add"), $args);
    }

    /**
     * Adds the content reference to the <body>
     * tag for later use.
     *
     * @param   mixed   $content - content to add
     */
    function add_reference( &$content ) {
        $this->_body->push_reference( $content );
    }

    /**
     * Same as add()
     *
     * @deprecated - use add()
     *
     */
    function push_reference( &$content ) {
        $this->add_reference( $content );
    }

    /**
     * This is responsible for creating the
     * BODYtag object.  We only will
     * create a new $this->_body if it doesn't
     * already exist.
     *
     */
    function _create_body() {
        if ($this->_body == NULL) {
            $this->_body = new BODYtag;
            //$this->_body->add( " " );
        }
    }

    /**
     * set attributes of body tag
     * @param array $attributes the name=>value pairs
     *
     */
    function set_body_attributes( $attributes ) {
        if (!is_object( $this->_body )) {
            $this->_create_body();
        }
        $this->_body->set_tag_attributes( $attributes );
    }

	/**
	 * This function is used to build the DOCTYPE
	 * tag for the page.  It will automatically
	 * create a DOCTYPE with a document_element of "html"
	 * and a source of "PUBLIC"
	 *
	 * @param string - link1
	 * @param string - link2
	 */
	function build_doctype($link1, $link2=NULL) {
		$this->_doctype = xml_doctype("html", "PUBLIC", $link1, $link2);
	}

    //**************************************************
    //* General functions
    //**************************************************

    /**
     * set the $_text_debug flag
     * @param   $flag - boolean.
     */
    function set_text_debug( $flag ) {
        $this->_text_debug = $flag;
    }


    //**************************************************
    //* RENDERING of content related functions
    //**************************************************

    /**
     *  builds the head object and its content.
     *
     */
    function _build_head() {
        $this->_head->add( $this->_build_content_type_tag() );

        if ($this->_title) {
            $this->_head->add( $this->_title );
        }

        if ($this->_favicon["enabled"]) {
            $this->_head->add( html_link($this->_favicon["href"],
                                         "shortcut icon",
                                         $this->_favicon["type"]));
        }

        if ( $this->_head_style->count_content() ) {
            $this->_head->add( $this->_head_style );
        }

        if ( $this->_head_js->count_content() ) {
            $this->_head->add( $this->_head_js );
        }
    }

    /**
     * This builds a frameset body tag
     * wrapped in a <noframes> tag.
     *
     * @return NOFRAMEStag object.
     */
    function _frameset_wrap_body() {
        $noframes = new NOFRAMEStag;
        $body = new BODYtag;
        $body->add( $this->_noframes_text );
        $noframes->add( $body );
        return $noframes;
    }

    /**
     * render the page.
	 *
	 *
	 * @return string the raw html output.
     */
    function render() {

        //make sure the render type is correctly
        //set
        $GLOBALS["HTML_RENDER_TYPE"] = $this->_html_render_type;

        //lets use ourself to render the debug page!
        if ($this->_text_debug) {
            $page = new HTMLPageClass;
            $page->add_css_link("/phphtmllib/css/HTMLPageClass.css");
        }

        $newline = " ";
        $attributes = $this->get_html_attributes();
        $html = new HTMLtag( $attributes );
        $html->add( $newline );
        $this->_build_head();
        $html->add( $this->_head );

        //Check to see if we are rendering
        //a frameset page.
        if ($this->_frameset != NULL) {
            //Looks like they have set the frameset
            //member, so we are rendering a frameset
            //we will automatically wrap the <body>
            $html->add( $newline );
            $html->add( $this->_frameset );
            $html->add( $newline );
            $html->add( $this->_frameset_wrap_body() );
        } else {
            $html->add( $newline );
            //$this->_body->add( $newline );
            $html->add( $this->_body );
        }

        $html-> add( $newline );

        if ($this->_text_debug) {
            if ($GLOBALS["HTML_RENDER_TYPE"] == XHTML_STRICT) {
                $xml = new XMLtag(array("version" => "1.0",
                                        "encoding"=>$this->_xml_encoding));
                $page->add( $xml->render(0,1) );
            }
            $page->add( $this->_doctype->render(0,1) );
            $page->add( $html->render($this->_indent_style,1) );
            return $page->render();
        } else {
            $output = '';
            if ($GLOBALS["HTML_RENDER_TYPE"] == XHTML_STRICT) {
                $xml = new XMLtag(array("version" => "1.0",
                                        "encoding"=>$this->_xml_encoding));
                $output = $xml->render(0);
            }
            $output .= $this->_doctype->render();			
            $output .= $html->render($this->_indent_style);
            return $output;
        }
    }
}


?>
