<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This is the example PageWidget child
 * for the examples pages.
 *
 *
 * $Id: MyLayoutPage.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage examples
 * @version 2.0.0
 *
 */

/**
 * This is an example Child of the PageWidget
 * class to show how to build a simple application
 * or system wide layout simple to manage and 
 * maintain
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage examples
 * @version 2.0.0 
 */
class MyLayoutPage extends PageWidget {


	/**
	 * This is the constructor.
	 *
	 * @param string - $title - the title for the page and the
	 *                 titlebar object.
	 * @param - string - The render type (HTML, XHTML, etc. )	 
     *
	 */
    function MyLayoutPage($title, $render_type = HTML) {

        $this->PageWidget( $title, $render_type );

		//add some css links
		//assuming that phphtmllib is installed in the doc root
		$this->add_css_link(PHPHTMLLIB_RELPATH . "/examples/css/main.css");
		$this->add_css_link(PHPHTMLLIB_RELPATH . "/css/fonts.css");
		$this->add_css_link(PHPHTMLLIB_RELPATH . "/css/colors.css");
		
		//add the phphtmllib widget css
		$this->add_css_link(PHPHTMLLIB_RELPATH . "/css/bluetheme.php" );
    }

	/**
	 * This builds the main content for the
	 * page.
	 *
	 */
	function body_content() {		
        
		//add the header area
		$this->add( html_comment( "HEADER BLOCK BEGIN") );
		$this->add( $this->header_block() );
		$this->add( html_comment( "HEADER BLOCK END") );		

		//add it to the page
		//build the outer wrapper div
		//that everything will live under
		$wrapper_div = html_div();
		$wrapper_div->set_id( "phphtmllib" );

		//add the main body
		$wrapper_div->add( html_comment( "MAIN BLOCK BEGIN") );
		$wrapper_div->add( $this->main_block() );
		$wrapper_div->add( html_comment( "MAIN BLOCK END") );

		$this->add( $wrapper_div );

		//add the footer area.
		$this->add( html_comment( "FOOTER BLOCK BEGIN") );
		$this->add( $this->footer_block() );
		$this->add( html_comment( "FOOTER BLOCK END") );        
		
	}


    /**
     * This function is responsible for building
     * the header block that lives at the top
     * of every page.
     *
     * @return HTMLtag object.
     */
    function header_block() {
        $header = html_div("pageheader");

		$header->add( "HEADER BLOCK AREA" );
        return $header;
    }


    /**
     * We override this method to automatically
     * break up the main block into a 
     * left block and a right block
     *
     * @param TABLEtag object.
     */
    function main_block() {

		$main = html_div();
		$main->set_id("maincontent");

		$table = html_table("100%",0);
		$left_div = html_div("leftblock", $this->left_block() );		

		$table->add_row( html_td("leftblock", "", $left_div ),
						 html_td("divider", "", "&nbsp;"),
						 html_td("rightblock", "", $this->content_block() ));
        $main->add( $table );

		return $main;
    }


    /**
     * this function returns the contents
     * of the left block.  It is already wrapped
     * in a TD
     *
     * @return HTMLTag object
     */
    function left_block() {
		$div = html_div();
		$div->set_style("padding-left: 6px;");

		$div->add( "LEFT BLOCK" );
        return $div;
    }



    /**
     * this function returns the contents
     * of the right block.  It is already wrapped
     * in a TD
     *
     * @return HTMLTag object
     */
    function content_block() {
		$container = container( "CONTENT BLOCK", html_br(2),
								html_a($_SERVER["PHP_SELF"]."?debug=1", 
									   "Show Debug source"),
								html_br(10));
		return $container;
    }


    /**
     * This function is responsible for building
     * the footer block for every page.
     *
     * @return HTMLtag object.
     */
    function footer_block() {

		$footer_div = html_div();
		$footer_div->set_tag_attribute("id", "footerblock");
		$footer_div->add("FOOTER BLOCK");
		
        return $footer_div;
    }
}
?>
