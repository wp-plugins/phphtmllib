<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the use of the 
 * GoogleMap widget class.  This widget will
 * display a Google Map via the Google Maps API.
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version 2.0
 * @since 2.6.0
 *
 */ 

/**
 * Include the phphtmllib libraries
 *
 */
include_once("includes.inc");
include_once("db_defines.inc");
include_once("MyLayoutPage.inc");

include_once(PHPHTMLLIB_ABSPATH . "/widgets/GoogleMap.inc");

class Widget24LayoutPage extends MyLayoutPage
{
    function content_block()
    {
        $container = container() ;

        //  Create a GoogleMapDIVtag

        $gm1 = new GoogleMapDIVtag() ;

        $gm1->set_id("map_canvas_1") ;
        $gm1->set_style("border: 3px solid #afb5ff") ;
        $gm1->setAddress("1600 Pennsylvania Ave, Washington DC, 20006") ;
        $gm1->setShowControls(true) ;
        $gm1->setInfoWindowType(PHL_GMAPS_INFO_WINDOW_PLAIN) ;
        $gm1->setZoomLevel(10) ;

        //  Get Google Maps key from URI

        if (isset($_GET['key']))
            $gm1->setAPIKey($_GET['key']) ;
        else
            $gm1->setAPIKey(null) ;

        //  Need to add the Javascript library link
        //  to the document head but only do it once

        $this->add_js_link($gm1->getHeadJSLink()) ;
        $this->add_head_js($gm1->getHeadJSCode()) ;

        $gm1->generateMap() ;

        $address = join($gm1->getAddress(), "<br>") ;

        $container->add(html_h4("Map Controls:  On", html_br(),
            "Info Window:  On - Plain", html_br(), "Zoom Level: 10", html_br(),
            "Map Type: Off", html_br(), sprintf("Address: %s", $address))) ;

        $container->add($gm1) ;

        //  Create a GoogleMapDIVtag

        $gm2 = new GoogleMapDIVtag() ;

        $gm2->set_id("map_canvas_2") ;
        $gm2->set_style("border: 5px solid #eeeeee") ;
        $gm2->setAddress("Buckingham Palace London SW1A 1, United Kingdom") ;
        $gm2->setShowType(true) ;
        $gm2->setShowControls(false) ;
        $gm1->setInfoWindowType(PHL_GMAPS_INFO_WINDOW_NONE) ;
        $gm2->setZoomLevel(15) ;

        //  Get Google Maps key from URI

        if (isset($_GET['key']))
            $gm2->setAPIKey($_GET['key']) ;
        else
            $gm2->setAPIKey(null) ;

        $gm2->generateMap() ;

        $gm2->generateMap() ;

        $address = join($gm2->getAddress(), "<br>") ;

        $container->add(html_h4("Map Controls:  Off", html_br(),
            "Info Window:  Off", html_br(), "Zoom Level: 15", html_br(),
            "Map Type: On", html_br(), sprintf("Address: %s", $address))) ;

        $container->add($gm2) ;

        //  Create a GoogleMapDIVtag

        $gm3 = new GoogleMapDIVtag() ;

        $gm3->set_id("map_canvas_3") ;
        $gm3->set_style("border: 5px solid #eeeeee") ;
        $gm3->setAddress("1600 Pennsylvania Ave, Washington DC, 20006") ;
        $gm3->setAddress("Buckingham Palace London SW1A 1, United Kingdom") ;
        $gm3->setShowControls(true) ;
        $gm1->setInfoWindowType(PHL_GMAPS_INFO_WINDOW_HTML) ;
        $gm3->setZoomLevel(2) ;

        //  Get Google Maps key from URI

        if (isset($_GET['key']))
            $gm3->setAPIKey($_GET['key']) ;
        else
            $gm3->setAPIKey(null) ;

        $address = join($gm3->getAddress(), "<br>") ;

        $gm3->generateMap() ;
        $container->add(html_h4("Map Controls:  Off", html_br(),
            "Info Window:  On - HTML", html_br(), "Zoom Level: 2", html_br(),
            "Map Type: Off", html_br(), sprintf("Address: %s", $address))) ;

        $container->add($gm3) ;

	    return $container ;
    }
}

//create the page object
$page = new Widget24LayoutPage("phpHtmlLib Widgets - Google Maps Example");

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}

print $page->render();
?>
