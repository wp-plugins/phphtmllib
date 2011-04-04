<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the use of the 
 * permissions checking mechanism built into the
 * PageWidget object.
 *
 *
 * $Id: widget14.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version 2.4.0
 *
 */ 

/**
 * Include the phphtmllib libraries
 *
 */
include_once("includes.inc");

require_once(PHPHTMLLIB_ABSPATH . "/widgets/TabWidget.inc");

class FirstTab extends TabWidget {
    function FirstTab($title='First Tab Title') {
        $this->TabWidget($title);
    }

    function content() {
        return 'testing 123';
    }
}

class FooTab extends TabWidget {
    function FooTab() {
        $this->TabWidget('Foo');
    }

    function content() {
        $dialog = new MessageBoxWidget("Some title", "400",
                                       container("This is a message",
                                                 html_br(2),
                                                 "Want to see a permissions error?",
                                                 html_br(),
                                                 html_a($_SERVER["PHP_SELF"]."?failed=1",
                                                        "Click Here"))
                                                 );
        return container(html_br(),$dialog, html_br());
    }
}

class test extends TabWidget {
    function content() {
        return "test ".$this->get_title();
    }
}

class WidgetListPage extends PageWidget {


    function WidgetListPage($title) {
        $this->PageWidget($title, HTML);        

        //we need this for the css defined for the InfoTable
        //for the DialogWidget.  The DialogWidget uses InfoTable.
        $this->add_css_link(PHPHTMLLIB_RELPATH . "/css/defaulttheme.php");
    }

    /**
     * This will only get called if we have permissions to 
     * build and render the content for this page object.
     * 
     * @return object
     */
    function body_content() {
        $tablist = new TabList("Scan");
        $tablist->add( new FirstTab );
        $tablist->add( new FooTab );
        $tablist->add( new FirstTab('Third tab!') );

        $subtab = new TabList("list");
        $subtab->add( new test("sub 1") );
        $subtab->add( new test("sub 2") );
        $subtab->add( new test("sub 3") );
        $subtab->add( new test("sub 4") );

        $tablist->add( $subtab );
        

        $div = html_div('', $tablist);
        $div->set_style('width: 600px');
        return $div;
    }
}

//build the Page object and try and
//render it's content.
//the permissions checking happens at
//'constructor' time.
$page = new WidgetListPage("testing");

//the render method will not call the
//content building methods if the permissions
//fail.
print $page->render();
?>
