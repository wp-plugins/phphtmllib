<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 *
 * $Id: CalendarTable.inc,v 1.1.1.1 2005/10/10 20:28:30 mike Exp $
 *
 * CalendarTable - class for constructing and rendering calendars.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @author David Wilkinson <davidw@cascade.org.uk>
 * @package phpHtmlLib
 * @subpackage calendar
 * @version $Revision: 1.1.1.1 $
 *
 * This class is a new implementation of the PHP Calendar Class
 * found at:   http://www.cascade.org.uk/software/php/calendar/
 *
 * This implementation constructs the calendars in a format
 * which is compatible with phpHtmlLib.  The class has also
 * been extended to allow the application to better control
 * how the calendar is constructed and presented.
 *
 */

/*  --- Original Header --- */

// PHP Calendar Class Version 1.4 (5th March 2001)
//  
// Copyright David Wilkinson 2000 - 2001. All Rights reserved.
// 
// This software may be used, modified and distributed freely
// providing this copyright notice remains intact at the head 
// of the file.
//
// This software is freeware. The author accepts no liability for
// any loss or damages whatsoever incurred directly or indirectly 
// from the use of this script. The author of this software makes 
// no claims as to its fitness for any purpose whatsoever. If you 
// wish to use this software you should first satisfy yourself that 
// it meets your requirements.
//
// URL:   http://www.cascade.org.uk/software/php/calendar/
// Email: davidw@cascade.org.uk


/*  --- End of Original Header --- */

if (!defined('PHPHTMLLIB_WIDGET_IMAGEPATH'))
    define('PHPHTMLLIB_WIDGET_IMAGEPATH', PHPHTMLLIB_RELPATH . '/images/widgets') ;

/**
 * This is a widget class that can build and
 * render calendar data in a nicely formated table.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @author David Wilkinson <davidw@cascade.org.uk>
 * @package phpHtmlLib
 */

class CalendarTable extends BaseWidget
{
    /**
     * This stores the base path to where the
     * tool link images live.  This lets you
     * specify a new path to where your images
     * live.
     */
    var $_image_path = PHPHTMLLIB_WIDGET_IMAGEPATH ;

    /**
     * Name of "Previous" button
     */
    var $_prevImage = "prev_group_button.gif" ;

    /**
     * Name of "Next" button
     */
    var $_nextImage = "next_group_button.gif" ;

    /**
     * Path to "Previous" text
     */
    var $_prevText = "&#171;" ;

    /**
     * Path to "Next" button
     */
    var $_nextText = "&#187;" ;

    /**
     * Use buttons or test links to previous and next
     */
    var $_useButtons = true ;

    /**
     * The constructor
     */
    function CalendarTable()
    {
    }
    
    /**
     * Use buttons for previous and next links
     */
    function useButtonNav()
    {
        $this->_useButtons = true ;
    }
    
    /**
     * Use buttons for previous and next links
     */
    function useTextNav()
    {
        $this->_useButtons = false ;
    }

    /**
     * Set the image path
     *
     * @param string - path to the next and previous images.
     */
    function set_image_path($path = PHPHTMLLIB_WIDGET_IMAGEPATH)
    {
        $this->_image_path = $path ;
    }
    
    /**
     * Set the previous image name
     *
     * @param string - name of previous image
     */
    function set_prev_image_name($name = "prev_group_button.gif")
    {
        $this->_nextImage = $path ;
    }
    
    /**
     * Set the next image name
     *
     * @param string - name of next image
     */
    function set_next_image_name($name = "next_group_button.gif")
    {
        $this->_prevImage = $name ;
    }
    
    /**
     *  Construct the "previous" link
     */
    function getPrevLink()
    {
        if ($this->_useButtons)
            $prevLink = html_img($this->_image_path . "/" .
                $this->_prevImage, "", "", 0, "Previous", null, null, "top") ;
        else
            $prevLink = html_span("link", $this->_prevText) ;

        return $prevLink ;
    }

    /**
     *  Construct the "next" link
     */
    function getNextLink()
    {
        if ($this->_useButtons)
            $nextLink = html_img($this->_image_path . "/" .
                $this->_nextImage, "", "", 0, "Next", null, null, "top") ;
        else
            $nextLink = html_span("link", $this->_nextText) ;

        return $nextLink ;
    }

    /**
     * Get the array of strings used to label the days of the week.
     * This array contains seven elements, one for each day of the week.
     * The first entry in this array represents Sunday. 
     *
     * @return array - array of strings representing weekday names
     */
    function getDayNames()
    {
        return $this->dayNames;
    }
    

    /**
     * Set the array of strings used to label the days of the week.
     * This array must contain seven elements, one for each day of the
     * week. The first entry in this array represents Sunday. 
     *
     * @param array - array of names for the days of the week.
     */
    function setDayNames($names)
    {
        $this->dayNames = $names;
    }
    
    /**
     * Get the array of strings used to label the months of the year.
     * This array contains twelve elements, one for each month of the
     * year. The first entry in this array represents January. 
     *
     * @return array - array of strings representing month names
     */
    function getMonthNames()
    {
        return $this->monthNames;
    }
    
    /**
     * Set the array of strings used to label the months of the year.
     * This array must contain twelve elements, one for each month of
     * the year. The first entry in this array represents January. 
     *
     * @param array - array of names for the months of the year.
     */
    function setMonthNames($names)
    {
        $this->monthNames = $names;
    }
    
    
    /**
     * Gets the start day of the week. This is the day that appears in
     * the first column of the calendar. Sunday = 0.
     *
     * @return int - day of week (0-6) which is the column of the calendar
     */
    function getStartDay()
    {
        return $this->startDay;
    }
    
    /**
     * Sets the start day of the week. This is the day that appears in the
     * first column of the calendar. Sunday = 0.
     *
     * @param int - day of week (0-6) which is the column of the calendar
     */
    function setStartDay($day)
    {
        $this->startDay = $day;
    }
    
    
    /**
     * Gets the start month of the year. This is the month that appears
     * first in the year view. January = 1.
     *
     * @return int - month of year (1-12) which is the first month displayed
     */
    function getStartMonth()
    {
        return $this->startMonth;
    }
    
    /**
     * Sets the start month of the year. This is the month that appears
     * first in the year view. January = 1.
     *
     * @param int - month of year (1-12) which is the first month displayed
     */
    function setStartMonth($month)
    {
        $this->startMonth = $month;
    }
    
    /**
     * Sets the numbers of months to show per row in the year view.
     *
     * @param int - numbers of months to show in a row (1, 2, 3, 4, 6, 12)
     */
    function setMonthsPerRow($months)
    {
        switch ($months)
        {
            case 1:
            case 2:
            case 3:
            case 4:
            case 6:
            case 12:
                $this->monthsPerRow = $months ;
                break ;

            default:
                break ;
        }
    }
    
    /**
     * Return the URL to link to in order to display a calendar for a
     * given month/year.  You must override this method if you want to
     * activate the "forward" and "back" feature of the calendar.
     *
     * Note: If you return an empty string from this function, no
     * navigation link will be displayed. This is the default behaviour.
     *
     * If the calendar is being displayed in "year" view, $month will be
     * set to zero.
     *
     * @param int - month of year (1-12)
     * @param int - year
     * @return string - constructed URL
     */
    function getCalendarLink($month, $year)
    {
        return "";
    }
    
    /**
     * Return the URL to link to  for a given date.  You must override
     * this method if you want to activate the date linking feature of
     * the calendar.
     *
     * Note: If you return an empty string from this function, no
     * navigation link will be displayed. This is the default behaviour.
     *
     * @param int - day of month (1-31)
     * @param int - month of year (1-12)
     * @param int - year
     * @return string - constructed URL
     */
    function getDateLink($day, $month, $year)
    {
        return "";
    }


    /**
     * Return the current month view.
     *
     * @return Container
     */
    function getCurrentMonthView()
    {
        $d = getdate(time());
        return $this->getMonthView($d["mon"], $d["year"]);
    }
    

    /**
     * Return the current year view.
     *
     * @return Container
     */
    function getCurrentYearView()
    {
        $d = getdate(time());
        return $this->getYearView($d["year"]);
    }
    
    
    /**
     * Return a specified month view
     *
     * @param int - month of year (1-12)
     * @param int - year
     * @return Container
     */
    function getMonthView($month, $year)
    {
        return $this->getMonth($month, $year);
    }
    

    /**
     * Return a specified year view.
     *
     * @param int - year
     * @return Container
     */
    function getYearView($year)
    {
        return $this->getYear($year);
    }
    
    /**
     * The rest are private methods. No user-servicable parts inside.
     * You shouldn't need to call any of these functions directly.
     *   
     */

    /**
     * Calculate the number of days in a month, taking into account
     * leap years.
     *
     * @param int - month of year (1-12)
     * @param int - year
     */
    function getDaysInMonth($month, $year)
    {
        if ($month < 1 || $month > 12)
        {
            return 0;
        }
   
        $d = $this->daysInMonth[$month - 1];
   
        if ($month == 2)
        {
            // Check for leap year
            // Forget the 4000 rule, I doubt I'll be around then...
        
            if ($year%4 == 0)
            {
                if ($year%100 == 0)
                {
                    if ($year%400 == 0)
                    {
                        $d = 29;
                    }
                }
                else
                {
                    $d = 29;
                }
            }
        }
    
        return $d;
    }


    /**
     * Generate the Container for a given month
     *
     * @param int - month of year (1-12)
     * @param int - year
     * @param boolean - year display on/off
     * @return Container
     */
    function getMonth($m, $y, $showYear = true)
    {
        $a = $this->adjustDate($m, $y);
        $month = $a[0];
        $year = $a[1];        
        
    	$daysInMonth = $this->getDaysInMonth($month, $year);
    	$date = getdate(mktime(12, 0, 0, $month, 1, $year));
    	
    	$first = $date["wday"];
    	$monthName = $this->monthNames[$month - 1];
    	
    	$prev = $this->adjustDate($month - 1, $year);
    	$next = $this->adjustDate($month + 1, $year);
    	
    	if ($showYear)
    	{
    	    $prevMonth = $this->getCalendarLink($prev[0], $prev[1]);
    	    $nextMonth = $this->getCalendarLink($next[0], $next[1]);
    	}
    	else
    	{
    	    $prevMonth = "";
    	    $nextMonth = "";
    	}
    	
    	$header = $monthName . (($showYear) ? " " . $year : "");

        $table = html_table("", "0") ;
        $table->set_class("calendartable") ;
        $thead = html_thead() ;
        $tbody = html_tbody() ;

        $tr = html_tr() ;

        $prevLink = (($prevMonth == "") ? "&nbsp;" : html_a($prevMonth, $this->getPrevLink(), "link")) ;
        $nextLink = (($nextMonth == "") ? "&nbsp;" : html_a($nextMonth, $this->getNextLink(), "link")) ;

        //  Month

        $td = html_td("header") ;
        $td->set_tag_attributes(array("align" => "center", "valign" => "top")) ;
        $td->set_colspan(7) ;
        $td->add($prevLink, $header, $nextLink) ;
        $tr->add($td) ;
    	
        $thead->add($tr) ;

        $tr = html_tr() ;

        for ($i = 0 ; $i < 7 ; $i++)
        {
            $td = html_td("weekday") ;
            $td->set_tag_attributes(array("align" => "center", "valign" => "top")) ;
            $td->add($this->dayNames[($this->startDay + $i)%7]) ;
            $tr->add($td) ;
        }

        $thead->add($tr) ;

    	// We need to work out what date to start at so that
        // the first appears in the correct column
    	$d = $this->startDay + 1 - $first;
    	while ($d > 1)
    	{
    	    $d -= 7;
    	}

        // Make sure we know when today is, so that we can use
        // a different CSS style
        $today = getdate(time());
    	
    	while ($d <= $daysInMonth)
    	{
            $tr = html_tr() ;
    	    
    	    for ($i = 0; $i < 7; $i++)
    	    {
        	    $class = ($year == $today["year"] && $month == $today["mon"] && $d == $today["mday"]) ? "today" : "nottoday";
                $td = html_td($class) ;
                $td->set_tag_attributes(array("align" => "right", "valign" => "top")) ;

    	        if ($d > 0 && $d <= $daysInMonth)
    	        {
    	            $link = $this->getDateLink($d, $month, $year);
                    $td->add(($link == "") ? $d : html_a($link, $d, "link")) ;
    	        }
    	        else
    	        {
                    $td->add("&nbsp;") ;
    	        }
        	    $d++;

                $tr->add($td) ;
    	    }

            $tbody->add($tr) ;
    	}
    	
        $table->add($thead, $tbody) ;

    	return $table ;  	
    }
    
    
    /**
     * Generate the Container for a given year
     *
     * @param int - year
     * @return Container
     */
    function getYear($year)
    {
    	$prev = $this->getCalendarLink(0, $year - 1);
    	$next = $this->getCalendarLink(0, $year + 1);
        
        $table = html_table("", "0", "10", "0") ;
        $table->set_class("calendartable") ;
        $table->set_style("border: 1px solid #999999;") ;
        $thead = html_thead() ;
        $tbody = html_tbody() ;

        //  Header

        $tr = html_tr() ;

        $prevLink = (($prev == "") ? "&nbsp;" : html_a($prev, $this->getPrevLink(), "link")) ;
        $nextLink = (($prev == "") ? "&nbsp;" : html_a($next, $this->getNextLink(), "link")) ;

        //  Year

        $td = html_td("header") ;
        $td->set_tag_attributes(array("align" => "center", "valign" => "top")) ;
        $td->set_colspan($this->monthsPerRow) ;
        $td->add($prevLink, (($this->startMonth > 1) ? $year . " - " . ($year + 1) : $year), $nextLink) ;
        $tr->add($td) ;
    	
        $thead->add($tr) ;

        //  Build rows of months, number of months per row can be set

        for ($i = 0 ; $i < 12 ; $i = $i + $this->monthsPerRow)
        {
            $tr = html_tr() ;

            for ($j = $i ; $j < $i + $this->monthsPerRow ; $j++)
            {
                $td = html_td("calendartable") ;
                $td->set_tag_attribute("valign", "top") ;
                $td->add($this->getMonth($j + $this->startMonth, $year, false)) ;
                $tr->add($td) ;
            }

            $tbody->add($tr) ;
        }

        $table->add($thead, $tbody) ;

        return $table ;
    }

    /**
     * Adjust dates to allow months > 12 and < 0. Just adjust the years
     * appropriately.  e.g. Month 14 of the year 2001 is actually month
     * 2 of year 2002.
     *
     * @param int - month of year (1-12)
     * @param int - year
     * @return array - adjusted month and year
     */
    function adjustDate($month, $year)
    {
        $a = array();  
        $a[0] = $month;
        $a[1] = $year;
        
        while ($a[0] > 12)
        {
            $a[0] -= 12;
            $a[1]++;
        }
        
        while ($a[0] <= 0)
        {
            $a[0] += 12;
            $a[1]--;
        }
        
        return $a;
    }

    /**
     * Number of months per row in the year view.  Legal values
     * are 1, 2, 3, 4, 6, and 12.
     */
    var $monthsPerRow = 3 ;

    /**
     * The start day of the week. This is the day that appears
     * in the first column of the calendar. Sunday = 0.
     */
    var $startDay = 0;

    /**
     * The start month of the year. This is the month that appears
     * in the first slot of the calendar in the year view. January = 1.
     */
    var $startMonth = 1;

    /**
     * The labels to display for the days of the week. The first entry
     * in this array represents Sunday.
     */
    var $dayNames = array("S", "M", "T", "W", "T", "F", "S");
    
    /**
     * The labels to display for the months of the year. The first entry
     * in this array represents January.
     */
    var $monthNames = array("January", "February", "March", "April",
        "May", "June", "July", "August", "September", "October", "November",
        "December");
                            
                            
    /**
     * The number of days in each month. You're unlikely to want to
     * change this...  The first entry in this array represents January.
     */
    var $daysInMonth = array(31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
    
}

/**
 * This class defines the css used by the 
 * CalendarTable Object.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib 
 */

class CalendarTableCSS extends CSSBuilder {

    function user_setup() {
        $this->add_entry(".calendartable", null,
                         array("margin" => "0px 0px 0px 0px",
                               "font-family" => "arial, helvetica, sans-serif",
                               "font-size" => "8pt")) ;

        $this->add_entry(".calendartable", "td.header",
                         array("font-size" => "10pt",
                               "font-weight" => "bold",
                               "padding" => "2px 5px 2px 5px",
                               "color" => "#FFFFFF",
                               "background-color" => "#D4D0C8",
                               "border-top" => "2px solid #999999",
                               "border-bottom" => "2px solid #999999")) ;

        $this->add_entry(".calendartable", "td.today",
                         array("font-weight" => "normal",
                               "padding" => "2px 2px 2px 2px",
                               "color" => "#FFFFFF",
                               "background-color" => "#D4D0C8",
                               "border" => "1px solid #999999")) ;

        $this->add_entry(".calendartable", "td.nottoday",
                         array("font-weight" => "normal",
                               "padding" => "2px 2px 2px 2px")) ;

        $this->add_entry(".calendartable", "td.weekday",
                         array("font-weight" => "bold",
                               "padding" => "2px 2px 2px 2px")) ;

        $this->add_entry(".calendartable", "span.link",
                         array("font-weight" => "bold",
                               "font-size" => "12pt",
                               "padding" => "2px 2px 2px 2px")) ;

        $this->add_entry(".calendartable", "a.link",
                         array("text-decoration" => "none")) ;
    }   
}
?>
