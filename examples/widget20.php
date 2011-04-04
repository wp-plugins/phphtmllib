<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the use of the 
 * CalendarTable widget.
 *
 *
 * $Id: widget20.php,v 1.1.1.1 2005/10/10 20:28:30 mike Exp $
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 * @subpackage widget-examples
 * @version $Revision: 1.1.1.1 $
 *
 */ 

/**
 * Include the phphtmllib libraries
 *
 */
include_once("includes.inc");

/**
 * Include the CalendarTable widget
 */
include_once(PHPHTMLLIB_ABSPATH . "/widgets/CalendarTable.inc") ;

//  Extend the calendar class to include navigation and date linking

class MyCalendarTable extends CalendarTable
{
    function getCalendarLink($month, $year)
    {
        // Redisplay the current page, but with some parameters
        // to set the new month and year
        $s = $_SERVER['PHP_SELF'] ;
        return "$s?month=$month&year=$year";
    }

    function getDateLink($day, $month, $year)
    {
        $d = getdate(time()) ;
        return (($day == 1) || ($day == $d['mday'])) ? $_SERVER['PHP_SELF'] : "" ;
    }
}



//create the page object
$page = new HTMLPageClass("phpHtmlLib Widgets - CalendarTable", 
						  XHTML_TRANSITIONAL);

//enable output debugging.
if (isset($_GET['debug'])) {
    $page->set_text_debug( TRUE );
}

//  If no month/year set, use current month/year

$d = getdate(time()) ;

// month set?
if (isset($_GET['month']))
    $month = $_GET['month'] ;
else
    $month = $d['mon'] ;

// year set?
if (isset($_GET['year']))
    $year = $_GET['year'] ;
else
    $year = $d['year'] ;

//add the css link to the default theme which will
//automatically generate the css classes used 
$page->add_css_link( "/css/defaulttheme.php" );

$page->add_head_css(new CalendarTableCSS) ;

$div = html_div_center() ;

$calendar = new MyCalendarTable() ;
//Set the number of months to show on each
//row in the year view of the calendar
$calendar->setMonthsPerRow(6) ;

$div->add(html_h3("Dynamic Month Calendar with Button Navigation")) ;
$div->add($calendar->getMonthView($month, $year)) ;
$div->add(html_h3("Dynamic Month Calendar with &quot;Text&quot; Navigation")) ;
$calendar->useTextNav() ;
$div->add($calendar->getMonthView($month, $year)) ;
$calendar->useButtonNav() ;
$div->add(html_h3("Dynamic Year Calendar")) ;
$div->add($calendar->getYearView($year)) ;
$div->add(html_br()) ;

//Build a French Calendar
$frenchMonths = array("Janvier", "F&eacute;vrier", "Mars", "Avril",
                      "Mai", "Juin", "Juillet", "Ao&ucirc;t", "Septembre",
                      "Octobre", "Novembre", "D&eacute;cembre");

// Then an array of day names, starting with Sunday
$frenchDays = array ("D", "L", "M", "M", "J", "V", "S");

$frCalendar = new CalendarTable() ;
//Set the number of months to show on each
//row in the year view of the calendar
$frCalendar->setMonthsPerRow(4) ;

$frCalendar->setMonthNames($frenchMonths);
$frCalendar->setDayNames($frenchDays);
//  Start the Calendar in April
$frCalendar->setStartMonth(4) ;

$div->add(html_h3("Static Year Calendar - French Version")) ;
// Show the calendar for 1999
$yearView = $frCalendar->getYearView(1999) ;
// Override the default CSS and surround the calendar with a red border
$yearView->set_style("border: 5px solid red;") ;

$div->add($yearView) ;

// Add the div to the page
$page->add($div) ;

//this will render the entire page
//with the content you have added
//wrapped inside all the required
//elements for a complete HTML/XHTML page.
//NOTE: all the objects in phphtmllib have
//      the render() method.  So you can call
//      render on any phphtmlib object.

print $page->render();
?>
