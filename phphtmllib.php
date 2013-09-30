<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * Plugin Name: phpHtmlLib
 * Plugin URI: http://michaelwalsh.org/wordpress-stuff/wordpress-plugins/phphtmllib/
 * Description: WordPress plugin to bind the phpHtmlLib library to WordPress.  The phpHtmlLib library contains a set of PHP classes and library functions to help facilitate building, debugging, and rendering of XML, HTML, XHTML, WAP/WML Documents, and SVG (Scalable Vector Graphics) images as well as complex html Widgets.  These classes, library functions and widgets can be used to build other WordPress plugins.
 *
 * 
 * Version: 2.6.7.3576
 * Last Modified: 2013/09/30 15:58:27
 * Author: Mike Walsh
 * Author URI: http://www.michaelwalsh.org/
 * License: GPL
 * 
 *
 * $Id$
 *
 * (c) 2008 by Mike Walsh
 *
 * @author Mike Walsh <mike@walshcrew.com>
 * @package phpHtmlLib
 * @subpackage WordPress
 * @version $Rev$
 * @lastmodified $Date$
 * @lastmodifiedby $LastChangedBy$
 * @since 2.6.0
 *
 */

//  Initialize the library

define("PHPHTMLLIB_ABSPATH", dirname(__FILE__)) ;
define("PHPHTMLLIB_RELPATH", get_bloginfo('url') .
    "/" . PLUGINDIR . "/" . basename(dirname(__FILE__))) ;

require_once(PHPHTMLLIB_ABSPATH . "/version.inc") ;

/**
 * Add wp_head action
 *
 * This function adds the CSS link and Javascript
 * references required by the phpHtmlLib plugin.
 *
 */
function phphtmllib_wp_head()
{
    phphtmllib_head_css() ;
}

/**
 * Add admin_head action
 *
 * This function adds the CSS link and Javascript
 * references required by the phpHtmlLib plugin.
 *
 */
function phphtmllib_admin_head()
{
    phphtmllib_head_css() ;
}

/**
 * phphtmllib_plugin_installed()
 *
 * @return - boolean
 */
function phphtmllib_plugin_installed()
{
    return true ;
}

/**
 * phphtmllib_install - set up when the plugin is activated
 *
 * Store the absolute and relative paths to phpHtmlLib
 * in the options table so other plugins can use them.
 *
 */
function phphtmllib_install()
{
    update_option('PHPHTMLLIB_ABSPATH', PHPHTMLLIB_ABSPATH) ;
    update_option('PHPHTMLLIB_RELPATH', PHPHTMLLIB_RELPATH) ;
    update_option('PHPHTMLLIB_VERSION', PHPHTMLLIB_VERSION) ;
}

/**
 * phphtmllib_uninstall - clean up when the plugin is deactivated
 *
 */
function phphtmllib_uninstall()
{
    delete_option('PHPHTMLLIB_ABSPATH') ;
    delete_option('PHPHTMLLIB_RELPATH') ;
    delete_option('PHPHTMLLIB_VERSION') ;
}

/**
 * Hook for adding CSS links and other HEAD stuff
 */
//add_action('wp_head', 'phphtmllib_wp_head');
//add_action('admin_head', 'phphtmllib_admin_head');


/**
 *  Activate the plugin initialization function
 */
register_activation_hook(plugin_basename(__FILE__), 'phphtmllib_install') ;
register_deactivation_hook(plugin_basename(__FILE__), 'phphtmllib_uninstall') ;

?>
