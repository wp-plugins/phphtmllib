<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 *
 * $Id$
 *
 * Google Map support - this class implements a Google Map widget in a 
 * style consistent with phpHtmlLib using Google's Maps API.  The widget
 * is implemented by extending the DIVtag class.
 *
 * (c) 2008 by Mike Walsh
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 * @subpackage GoogleMap
 * @version $Revision$
 * @lastmodified $Date$
 * @lastmodifiedby $Author$
 * @see http://code.google.com/apis/maps/
 *
 */

// Define info window types

define("PHL_GMAPS_INFO_WINDOW_NONE", "none") ;
define("PHL_GMAPS_INFO_WINDOW_PLAIN", "plain") ;
define("PHL_GMAPS_INFO_WINDOW_HTML", "html") ;


/**
 * Google Map class
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @access public
 * @see DIVTag
 */
class GoogleMapDIVtag extends DIVtag
{
    /**
     * Google Maps API key - need this for anything to work.
     */
    var $_apikey = null ;

    /**
     * Addresses to display
     */
    var $_address = array() ;

    /**
     * Info Text to display
     */
    var $_infotext = array() ;

    /**
     * Show Google Maps type, off by default
     */
    var $_show_type = false ;

    /**
     * Show Google Maps controls, on by default
     */
    var $_show_controls = true ;

    /**
     * Show Google Maps Info Window, on by default
     */
    var $_info_window_type = true ;

    /**
     * Google Map width in pixels, 450 by default
     */
    var $_map_width = 450 ;

    /**
     * Google Height width in pixels, 300 by default
     */
    var $_map_height = 300 ;

    /**
     * Google Map zoom level, 15 by default
     */
    var $_zoom_level = 15 ;

    /**
     * Google Map Javascript library - needed in document HEAD section
     */
    var $_head_js_link = "http://www.google.com/jsapi?key=%s" ;

    /**
     * Google Map Javascript code - needed in document HEAD section
     */
    var $_head_js_code = "
        google.load('maps', '2');

        function phl_gmap_load(zoom, type, control,
            infowindowtype, canvas, addresses, infowindowtext)
        { 
            if (google.maps.BrowserIsCompatible())
            { 
                var map = new google.maps.Map2(document.getElementById(canvas)); 

                //  Hide the info window?

                if (infowindowtype == '%s')
                {
                    map.disableInfoWindow();
                }

                //  Show the map controls?

                if (type)
                {
                    map.addControl(new google.maps.MapTypeControl());
                }

                //  Show the map controls?

                if (control)
                {
                    map.addControl(new google.maps.SmallMapControl());
                }

                //  Create the GeoCoder

                var geocoder = new google.maps.ClientGeocoder(); 

                //  Show the map

                for (var i = 0 ; i < addresses.length ; i++)
                {
                    phl_show_address(map, geocoder, addresses[i],
                        infowindowtext[i], zoom, infowindowtype) ;
                }
            } 
        } 

        function phl_show_address(map, geocoder,
            address, infowindowtext, zoom, infowindowtype)
        { 
            geocoder.getLatLng(address, 
                function(latlng)
                { 
                    if (!latlng)
                    { 
                        alert(address + ' not found'); 
                    }
                    else
                    { 
                        map.setCenter(latlng, zoom); 
                        var marker = new google.maps.Marker(latlng); 
                        map.addOverlay(marker); 
                        google.maps.Event.addListener(marker, \"click\",
                            function()
                            {
                                if (infowindowtype == '%s')
                                {
				                    marker.openInfoWindowHtml(infowindowtext);
                                }
                                else
                                {
				                    marker.openInfoWindow(infowindowtext);
                                }
                            });
                        //marker.openInfoWindow(address); 
                        map.checkResize();
                    } 
                } 
            ); 
        }" ;

    /**
     * Get the link to the Google Maps Javascript library
     *
     * @return string - address to display
     */
    function getHeadJSLink()
    {
        return sprintf($this->_head_js_link, $this->getAPIKey()) ;
    }

    /**
     * Get the Javascript code for the document header
     *
     * @return string - Javascript code to be included in document header
     */
    function getHeadJSCode()
    {
        return sprintf($this->_head_js_code,
            PHL_GMAPS_INFO_WINDOW_NONE, PHL_GMAPS_INFO_WINDOW_HTML) ;
    }

    /**
     * Set the Google Maps API key
     *
     * @param string - Google Maps API key
     */
    function setAPIKey($key)
    {
        $this->_apikey = $key ;
    }

    /**
     * Get the Google Maps API key
     *
     * @return string - Google Maps API key
     */
    function getAPIKey()
    {
        return $this->_apikey ;
    }

    /**
     * Set the address to display
     *
     * @param string - address to display
     */
    function setAddress($address)
    {
        $this->_address[] = $address ;
    }

    /**
     * Get the address to display
     *
     * @return string - address to display
     */
    function getAddress()
    {
        return $this->_address ;
    }

    /**
     * Set the info text to display
     *
     * @param string - info text to display
     */
    function setInfoText($infotext)
    {
        $this->_infotext[] = $infotext ;
    }

    /**
     * Get the info text to display
     *
     * @return mixed - info text to display
     */
    function getInfoText()
    {
        return $this->_infotext ;
    }

    /**
     * Set the width of the map
     *
     * @param int - width of the map
     */
    function setMapWidth($width)
    {
        $this->_map_width = $width ;
    }

    /**
     * Get the width of the map
     *
     * @return int - width of the map
     */
    function getMapWidth()
    {
        return $this->_map_width ;
    }

    /**
     * Set the height of the map
     *
     * @param int - height of the map
     */
    function setMapHeight($height)
    {
        $this->_map_height = $height ;
    }

    /**
     * Get the height of the map
     *
     * @return int - height of the map
     */
    function getMapHeight()
    {
        return $this->_map_height ;
    }

    /**
     * Set the zoom of the map
     *
     * @param int - zoom of the map
     */
    function setZoomLevel($zoom)
    {
        $this->_zoom_level = $zoom ;
    }

    /**
     * Get the zoom of the map
     *
     * @return int - zoom of the map
     */
    function getZoomLevel()
    {
        return $this->_zoom_level ;
    }

    /**
     * Set the show controls state of the map
     *
     * @param boolean - show controls state of the map
     */
    function setShowControls($show = true)
    {
        $this->_show_controls = $show ;
    }

    /**
     * Get the show type state of the map
     *
     * @return boolean - show type state of the map
     */
    function getShowType()
    {
        return $this->_show_type ;
    }

    /**
     * Set the show type state of the map
     *
     * @param boolean - show type state of the map
     */
    function setShowType($show = true)
    {
        $this->_show_type = $show ;
    }

    /**
     * Get the show controls state of the map
     *
     * @return boolean - show controls state of the map
     */
    function getShowControls()
    {
        return $this->_show_controls ;
    }

    /**
     * Set the show info window state of the map
     *
     * @param boolean - show info window state of the map
     */
    function setInfoWindowType($show = true)
    {
        $this->_info_window_type = $show ;
    }

    /**
     * Get the show info window state of the map
     *
     * @return boolean - show info window state of the map
     */
    function getInfoWindowType()
    {
        return $this->_info_window_type ;
    }

    /**
     * Get the id of the div container
     *
     * @return int - zoom of the map
     */
    function get_id()
    {
        return $this->get_tag_attribute("id") ;
    }

    /**
     * Get the style tag cintent of the div container
     *
     * @return string - style tag value of the div container
     */
    function get_style()
    {
        return $this->get_tag_attribute("style") ;
    }

    /**
     * Generate Javascript and display the map
     *
     * @return void
     */
    function generateMap()
    {
        //  No API key?  No point in doing anything further

        if (is_null($this->getAPIKey()))
        {
            $this->add("Google Maps API key is not set.") ;
            return ;
        }

        //  No DIV id?  Generate a random one

        if (is_null($this->get_id()) || $this->get_id() == "")
            $this->set_id(sprintf("map_canvas_%d", rand())) ;

        //  Use the style tag to set the height and width of the DIVtag

        $style = sprintf("width: %dpx; height: %dpx;",
            $this->getMapWidth(), $this->getMapHeight()) ;

        //  Make sure style is additive, append if a style exists.

        if (!$this->get_style())
            $this->set_style($style) ;
        else
            $this->set_style($this->get_style() . "; " . $style) ;

        //  Call Javascript for this DIV

        $addrarg = '[' ;
        $addresses= $this->getAddress() ;

        foreach ($addresses as $address)
            $addrarg .= "'" . $address . "'," ;

        $addrarg = substr($addrarg, 0, strlen($addrarg) - 1) . ']' ;

        $infotextarg = '[' ;
        $infotext= $this->getInfoText() ;

        foreach ($infotext as $it)
            $infotextarg .= "'" . $it . "'," ;

        $infotextarg = substr($infotextarg, 0, strlen($infotextarg) - 1) . ']' ;

        $js = html_script() ;
        $js->add(sprintf("phl_gmap_load(%d, %s, %s, '%s', '%s', %s, %s); ",
            $this->getZoomLevel(),
            $this->getShowType() ? "true" : "false",
            $this->getShowControls() ? "true" : "false",
            $this->getInfoWindowType(),
            $this->get_id(), $addrarg, $infotextarg)) ;

        $this->add($js) ;
    }
}
?>
