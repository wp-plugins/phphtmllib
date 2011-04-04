<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Another example of how to build a
 * parent PageWidget object to provide
 * a base class for building a consistent
 * look/feel accross a web application.
 *
 *
 * $Id$
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 * @subpackage examples
 * @version 2.0.0
 * @since 2.6.0
 *
 */ 

/**
 * Include the phphtmllib libraries
 */
include_once("includes.inc");
include_once(PHPHTMLLIB_ABSPATH . "/version.inc");

//Some applications want to provide a 
//consistent layout with some common
//elements that always live on each
//page.  
//  An easy way to do that is to
//build a child class to the 
//PageWidget object that defines the
//layout in logical blocks named as 
//methods.  

//For example,  A common layout is
//to have a header block at the top,
//followed by a content block, which
//contains a left block, and right block.
//followed by a footer block.

// --------------------------------
// |         header block         |
// --------------------------------	
// |       |                      |	<- Main
// | left  |    right block       |	<- block
// | block |                      |	<- 
// |       |                      |	<- 
// --------------------------------	
// |         footer block         |
// --------------------------------

//You would then define 6 methods in
//the child to PageWidget named
//body_content() - contains the outer most
//                 layout
//
//header_block() - builds the content for
//                 the header block, which
//                 stays the same among
//                 many pages.
//
//main_block()   - which builds the left
//                 block (typically used for
//                 navigation), and the
//                 main content block
//left_block()   - contains the left 
//                 navigational elements
//content_block() - the main content for any
//                  page's specific data.
//
//footer_block() - which contains any 
//                 footer information that
//                 remains the same on all
//                 pages.

//The nice thing about this approach is,
//on each page of your application,
//you only have to override the methods
//for the content blocks that are different
//or specific to that page.  The other content
//blocks and layout is automatically built
//from the parent class.  

//most of the time your page will only 
//override the content_block() method, which
//is the right block content that changes 
//from page to page.

//This is exactly how this website is built.

//enable the automatic detection of debugging
define("DEBUG", TRUE);

class MyLayoutPage extends PageWidget
{
    /**
     * get the source from a php file, and
     * run it thru php's function to generate
     * color coded pretty output.
     * We turn on output buferreing here and
     * capture the output of show_source(),
     * then we destroy the output buffer,
     * and return the pretty output in a Btag object.
     *
     * @param   string -$source file on disk
     * @param   boolean - $include_flag - flag to turn
     *                    on/off the ability to show
     *                    the include/require lines
     * @param   boolean - $lib_file_flag allow the function
     *                    to highlight a .inc file.
     * @return  Btag object from the phphtmllib
     */
    function show_php_source($source_file,
        $include_flag = FALSE, $lib_file_flag = FALSE)
    {
        if ( strstr($source_file, ".inc") && !$lib_file_flag )
        {
            $buffer = "<?php\n";
            $buffer .= "//access denied\n";
            $buffer .= "//cannot highlight .inc files\n";
            $buffer .= "//file may not even exist, but we don't allow\n";
            $buffer .= "//it anyways....loser!\n";
            $buffer .= "// ( ".$source_file." )\n";
            $buffer .= "?>\n";
            return html_span("", highlight_string( $buffer, TRUE ) );
        }
 
        $file = file(realpath($source_file));

        if (!$file)
        {
            return _HTML_SPACE;
        }

        //xmp_var_dump( $file );
        //we want to not show includes
        $buffer = "";
        foreach( $file as $line )
        {
            if ( $include_flag )
            {
                $buffer .= $line;
            }
            else
            {
                if ( !strstr($line, "include(") &&
                     !strstr($line, "include_once(") &&
                     !strstr($line, "require(") &&
                     !strstr($line, "require_once(") )
                {
                    $buffer .= $line;
                }
                else
                {
                    $buffer .= "//include hidden\n";
                }
            }
        }
 
        return html_span("", highlight_string( $buffer, TRUE ));
    }
    
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
    function content_block()
    {
		$container = container("CONTENT BLOCK", html_br(2),
            html_a($_SERVER["PHP_SELF"]."?debug=1", "Show Debug source")) ;
 
        if (!empty($_GET['source']))
        {
            $container->add(html_br(2),
                html_a("index.php", "Back to Examples"), html_br(2)) ;

            $container->add(html_h4(sprintf("phpHtmlLib v%s Examples:  %s",
                phphtmllib_get_version(), $_GET['source']))) ;

            $container->add($this->show_php_source($_GET['source'], true)) ;
        }
        else
        {
        //  This script constucts a list of links to the various examples
        //  by reading the directory contents and building a list from the
        //  .php files.

        $f = __FILE__ ;
        $d = dirname($f) ;

        //  Read the contents of the examples directory and add them to a list

        $t = new InfoTable("Examples", "400") ;

        $files = array() ;

        if ($handle = opendir($d))
        {
            $container->add(html_h2(sprintf("phpHtmlLib v%s Examples",
                phphtmllib_get_version()))) ;

            // This is the correct way to loop over the directory.

            while (false !== ($file = readdir($handle)))
            {
                //  Only add the ".php" files to the list
                if (preg_match('/\.php$/', $file))
                    $files[] = $file ;
            }

            closedir($handle);

            sort($files, SORT_REGULAR) ;

            foreach ($files as $file)
            {
                $s = sprintf("%s?source=%s", $_SERVER['PHP_SELF'], $file) ;
                $t->add_row(html_a($file, $file),
                    html_a($s, "view source")) ;
            }
        }
		
        $container->add($t, html_br(3)) ;
        }

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


$page = new MyLayoutPage(sprintf("phpHtmlLib v%s Examples",
    phphtmllib_get_version()));


//this will render the entire page
print $page->render();
?>
