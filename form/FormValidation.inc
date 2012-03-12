<?php

/**
 * $Id: FormValidation.inc 1477 2005-08-23 17:33:00Z hemna $
 *
 * This class handles the validation of form fields
 * This is used in conjunction with the FormProcessing
 * class, and the FormContent Class.  In the FormContent
 * class, you create an array of fields that you want
 * checked in the validate() method.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */

define("VALIDATE_MAXSIZE", 40);
define("VALIDATE_EMAIL_LENGTH", 256);
define("VALIDATE_MAX_HOSTNAME_LENGTH", 255);
define("SXVALIDATE_MAX_HOSTNAME_ELEMENT_LENGTH", 63);
define("VALID", TRUE);

/**
 * This is the base validation class that
 * contains some basic FormElement validation
 * methods.
 *
 * @package phpHtmlLib
 * @subpackage FormProcessing
 */
class FormValidation {

    /**
     * This holds the last error code found
     */
    var $_error_code = '';

    /**
     * This holds the last error message
     */
    var $_error_message = '';

    /**
     * This is the FormErrors object
     */
    var $_FormErrors = NULL;


    /**
     * The constructor used to set the
     * form errors object used by this class
     * to do error text lookups
     *
     * @param FormErrors object
     */
    function FormValidation(&$error_obj) {
        $this->_FormErrors = &$error_obj;
    }


	/**
	 * A singleton method for only
	 * creating one instance of this
	 * per request.
	 * 
	 * @return FormValidation object
	 */
	function &singleton() {
		static $obj=NULL;

		if (is_null($obj)) {
			$obj = new FormValidation(new FormErrors);
		}

		return $obj;
	}



    /**
     * This method checks to make sure an array doesn't have
     * an empty element.
     *
     */
    function array_hasempty($a) {
        if ( is_array($a) ) {
            foreach ( $a as $key => $value ) {
                if ( $value == '' ) {
                    return TRUE;
                }
            }
            return FALSE;
        } else {
            return $a == '';
        }
    }


    /**
     * A wrapper method to set the error message and
     * error code before returning FALSE
     *
     * @param string - error code
     * @return FALSE
     */
    function _error($code, $message=NULL) {
        $this->_error_code = $code;
        if ($message == NULL) {
            $this->_error_message = $this->_FormErrors->get_error_msg($code);
            unset( $err );
        } else {
            $this->_error_message = $message;
        }

        return FALSE;
    }


    /**
     * This method returns the error code from the
     * last validation error found.
     *
     * @return string
     */
    function get_error_code() {
        return $this->_error_code;
    }

    /**
     * This method returns the error
     * message from the last validation
     * error found.
     *
     * @return string
     */
    function get_error_message() {
        return $this->_error_message;
    }


    /**
     * This function makes sure the
     * data is not empty
     *
     * @param mixed
     * @return TRUE = not empty
     */
    function is_notempty($value) {
        if ( $this->array_hasempty($value) ) {
            return $this->_error("EMPTY_FIELD");
        }
        return TRUE;
    }

    /**
     * This function checks if the given string contains
     * alphabetical characters or numbers.
     * It also checks for the allowed additional characters.
     *
     * @param string - the string to check
     * @param string - list of individual characters to allow
     *                 besides a-zA-Z
     *
     * @return boolean FALSE - if any other extraneous
     *                         characters are found
     *                 TRUE upon succes.
     */
    function is_alphanum($str, $from = "") {

        // If the given string is only white spaces, return false
        if ( ereg("^[[:space:]]*$", $str) ) {
            return FALSE;
        }

        $to = "";
        $len = strlen($from);
        for ( $i = 0; $i < $len; ++$i ) {
            $to .= "a";
        }
        $str = strtr($str, $from, $to);
        $substr = eregi_replace("[a-z0-9]+", "", $str);
        if ( !$this->array_hasempty($substr) ) {
            return FALSE;
        }
        return TRUE;
    }


    /**
     * This function checks if the given string contains
     * numerical digit characters.
     * It also checks for the allowed additional characters.
     *
     * @param string - the string to check
     * @param string - list of individual characters to allow
     *                 besides a-zA-Z
     *
     * @return boolean FALSE - if any other extraneous
     *                         characters are found
     *                 TRUE upon succes.
     */
    function is_num($str, $from = "") {

        // If the given string is only white spaces, return false
        if ( ereg("^[[:space:]]*$", $str) ) {
            return FALSE;
        }

        //now do another simple check
        if ($from == '' && !is_numeric($str)) {
            return FALSE;
        }

        $to = "";
        $len = strlen($from);
        for ( $i = 0; $i < $len; ++$i ) {
            $to .= "0";
        }
        $str = strtr($str, $from, $to);
        $substr = eregi_replace("[-0-9]+", "", $str);
        if ( !$this->array_hasempty($substr) ) {
            return FALSE;
        }
        return TRUE;
    }


    /**
     * is_range
     *
     * This is the range check that the can be used in checks_array.
     * Valarray should be:
     *    array('val'  => $val,
     *          'size' => $size  OPTIONAL
     *          'min'  => $min,
     *          'max'  => $max,
     *          )
     */
    function is_range($value, $size, $min, $max) {
        return $this->is_within_range($value, $size,
                                      $min, $max);
    }

    /**
     * This method makes sure a value lies within
     * a given range of values.
     * The error message can be customized by passing in
     * a customer error code
     *
     * @param mixed - the value u want to check
     * @param int - the size
     * @param mixed - the lower bound value
     * @param mixed - the upper bound value
     * @param string - the error code if any
     * @return TRUE = succes  FALSE = failed
     *
     */
    function is_within_range($value, $size, $start, $end, $error=FALSE) {
        if ( ($value == '') || !$this->is_num($value) ) {
            if ( $error ) return $this->_error(NULL, $error);
            else return $this->_error("INVALID_NUMBER");
        }

        if ( $size ) {
            if ( strlen($value) != $size ) {
                if ( $error ) return $this->_error(NULL, $error);
                else return $this->_error(NULL,"Number too large (".$size." digits max)");
            }
        }

        if ( (($start != NULL) && ($value < $start)) ||
             (($end != NULL)   && ($value > $end)) ) {
            if ( $error ) return $this->_error(NULL, $error);
            else return $this->_error(NULL, "Value out of range (".$start."-".$end.")");
        }
        return TRUE;
    }

    /**
     * This method validates a string as containing
     * only letters and numbers
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_alphanumstring( $str ) {
        if ( !$this->is_alphanum($str) ) {
            return $this->_error("INVALID_ALPHANUM_CHARACTERS");
        }
        return TRUE;
    }


    /**
     * this method tests to see if this is a valid
     * hostname value minus the domain name portion.
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_standalone_hostname ($name) {

        // letters, digits and "-" only
        if ( !$this->is_alphanum($name, "-") ) {
            return $this->_error("INVALID_STANDALONE_HOST_NAME");
        }

        $len = strlen($name);
        if ( $len > VALIDATE_MAX_HOSTNAME_ELEMENT_LENGTH ) {
            return $this->_error("INVALID_LENGTH");
        }

        // Error if it doesn't start with an alphabet or digit
        if ( !eregi("^[a-z0-9]", $name) ) {
            return $this->_error("INVALID_HOST_NAME");
        }

        // Error if it contains no alphabets
        if ( !eregi("[a-z]", $name) ) {
            return $this->_error("INVALID_HOST_NAME");
        }

        return TRUE;
    }

    /**
     * This method validates a string for a valid
     * hostname for a machine.
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_domainname ($name, $forbid_www=FALSE) {
        if (!ereg( "^(([a-z0-9]{1,63}|".
               "([a-z0-9][a-z0-9\-]{1,61}[a-z0-9]))\.)+".
               "[a-z]{2,63}$", $name )) {
            return $this->_error("INVALID_HOST_NAME");
        } else if ($forbid_www && ereg( "^www\.", $name )) {
            return $this->_error("INVALID_HOST_NAME");
        }
        return TRUE;
    }

    /**
     * This method validates a string for a valid
     * partial hostname for a machine.
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_partial_domainname($name) {

        // letters, digits and ".-" only
        if ( !$this->is_alphanum($name, ".-") ) {
            return $this->_error("INVALID_HOST_NAME");
        }

        $len = strlen($name);
        if ( $len > VALIDATE_MAX_HOSTNAME_LENGTH ) {
            return $this->_error("INVALID_LENGTH");
        }

        // Error if it contains no alphabets
        if ( !eregi("[a-z]", $name) ) {
            return $this->_error("INVALID_HOST_NAME");
        }
        return TRUE;
    }


    /**
     * This is just a wrapper for is_domainname
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_hostname ($name) {
        return $this->is_domainname($name);
    }


    /**
     * This validates a string as an IP address
     * This should work with either IPv4 or IPv6
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_ip ($ip) {

        if ( !$this->is_num($ip, ".") ) {
            return $this->_error("INVALID_IP");
        }

        if ( $ip == "0.0.0.0" ) {
            return $this->_error("INVALID_IP");
        }

        $regs = split("\.", $ip);
        $num = sizeof($regs);

        // Allow IPv4 and IPv6
        if ( $num != 4 && $num != 8 ) {
            return $this->_error("INVALID_IP");
        }

        for ( $i = 0; $i < $num; ++$i ) {
            if ( (!$this->is_num($regs[$i])) || ($regs[$i] >= 256) ||
                 ($regs[$i] == "") ) {
                return $this->_error("INVALID_IP");
            }
        }
        return TRUE;
    }

    /**
     * This validates a string as a portion
     * of an  IP address.
     * This should work with either IPv4 or IPv6
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_partial_ip($ip) {
        if ( !$this->is_num($ip, ".") ) {
            return $this->_error("INVALID_IP");
        }

        $regs = split("\.", $ip);
        $num = sizeof($regs);

        // Allow IPv4 and IPv6
        if ( $num > 8 ) {
            return $this->_error("INVALID_IP");
        }

        for ( $i = 0; $i < $num; ++$i ) {
            if ( (!$this->is_num($regs[$i] + 0)) || ($regs[$i] >= 256) ) {
                return $this->_error("INVALID_IP");
            }
        }
        return TRUE;
    }


    /**
     * This method tries to validate a string
     * as a valid IP address or a hostname
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_hostip($hostip) {

        // If it looks like a number, check if it is a valid ip, else
        // check if it is a valid name.
        if ( $this->is_num($hostip, ".") ) {
            return $this->is_ip($hostip);
        } else {
            return $this->is_hostname($hostip);
        }
    }

    /**
     * This tests a string to make sure it is a
     * valid number.
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_number($value) {
        if ( !$this->is_num($value) ) {
            return $this->_error("INVALID_NUMBER");
        }
        return TRUE;
    }


    /**
     * This method tests a string to make sure it is
     * in a valid money format.
     * either $x or $x.cents
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_money($money) {

        if ( !$this->is_num($money, ".") ) {
            return $this->_error("INVALID_MONEY");
        }

        // Check for dollar.cent pattern
        if ( ereg("^[0-9]*\.[0-9][0-9]?$", $money) ) {
            return TRUE;
        }

        // Or It can be just dollars
        if ( ereg("^[0-9]+$", $money) ) {
            return TRUE;
        }

        return $this->_error("INVALID_MONEY");
    }

    /**
     * This method tries to validate a string as
     * a valid price.  It can't be zero (a la free!)
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_price($price) {
        $ret = $this->is_money($price);
        if ( $ret != TRUE ) {
            return $ret;
        }

        // Should be more than just 0s and .s
        if ( ereg("^0*\.*0*$", $price) ) {
            return $this->_error("INVALID_PRICE");
        }

        return TRUE;
    }


    /**
     * This method validates a string as a valid
     * float formatted number.  x.xx
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_float($number) {

        if ( !$this->is_num($number, ".") ) {
            return $this->_error("INVALID_FLOAT");
        }

        // Number of the form x.y
        if ( ereg("^[0-9]*\.[0-9]+$", $number) ) {
            return TRUE;
        }

        // Number of the form x
        if ( ereg("^[0-9]+$", $number) ) {
            return TRUE;
        }

        return $this->_error("INVALID_FLOAT");
    }


    /**
     * This validates a string as a valid number
     * between 0 and 100
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_zero_onehundred($value) {

        if ( !$this->is_num($value) ) {
            return $this->_error("INVALID_NUMBER");
        }

        if ( !($value > 0 && $value <= 100) ) {
            return $this->_error("INVALID_ZERO_HUNDRED_NUMBER");
        }

        return TRUE;
    }


    /**
     * This method validates a string as a number
     * greater then 0.
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_higherzeronumber($value) {
        if ( !$this->is_num($value) ) {
            return $this->_error("INVALID_NUMBER");
        }
        if ( $value > 0 ) {
            return TRUE;
        }
        return $this->_error("INVALID_NUMBER");
    }

    /**
     * This method validates a string as a
     * path to a file.
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_path ($path) {
        //DOS related checks are also needed
        if ( !$this->is_alphanum($path, "-_/:.,") ) {
            return $this->_error("INVALID_PATH_CHARACTERS");
        }
        return TRUE;
    }


    /**
     * This method validates a string as a valid
     * url path to a file
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_urlpath ($path) {
        //	 DOS related checks are also needed
        if ( !$this->is_alphanum($path, "-_/:.,%?&=") ) {
            return $this->_error("INVALID_PATH_CHARACTERS");
        }
        return TRUE;
    }


    /**
     * This validates a string as a valid proper name.
     * The string can't be longer then VALIDATE_MAXSIZE in
     * length, and it can only contain letters and numbers
     *
     * @param string - the value to validate
	 * @param int - the maximum allowable length
	 *              DEFAULT : VALIDATE_MAXSIZE
     * @return TRUE = succes  FALSE = failed
     */
    function is_name ($name, $maxsize=VALIDATE_MAXSIZE) {
        //letters & numbers only
        if ( !$this->is_alphanum($name, ".- 'ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖÙÚÛÜÝßàáâãäåçèéêëìíîïðñòóôõöùúûüýÿŠšŸ") ) {
            return $this->_error("INVALID_NAME_CHARACTERS");
        }
        // VALIDATE_MAXSIZE
        $len = strlen($name);
        if ( $len > $maxsize ) {
            return $this->_error("INVALID_LENGTH_40");
        }
        return TRUE;
    }


    /**
     * This validates a string as a valid Company name.
     * It is the same as is_name, with the exception
     * of allowing .
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_companyname($name) {
        $name = eregi_replace("[\. @\&,_]+","",$name);
        return $this->is_name($name);
    }


    /**
     * This method tests to see if a string value
     * is a valid 'account' name.  The string can't
     * be larger then VALIDATE_MAXSIZE, and can only
     * contain alphanum characters
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_username ($username) {

        if ( !$this->is_alphanum($username, "_") ) {
            return $this->_error("INVALID_LOGIN_NAME_CHARACTERS");
        }

        // VALIDATE_MAXSIZE
        $len = strlen($username);
        if ( $len > VALIDATE_MAXSIZE ) {
            return $this->_error("INVALID_LOGIN_NAME_LENGTH");
        }
        return TRUE;
    }


    /**
     * This tries to validate a string as a password
     * It can't be empty and has to be less then
     * VALIDATE_MAXSIZE characters in length
     *
     * NOTE: password is case sensitive, and spaces are
     *       ignored.
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_password ($password) {
        $len = strlen($password);
        if ( $len > VALIDATE_MAXSIZE ) {
            return $this->_error("INVALID_PASSWORD_LENGTH");
        }
        return TRUE;
    }


    /**
     * This makes sure that 2 password strings are exactly alike.
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_confirm_password ($confirmpassword, $password) {
        //confirm pswd value must match pswd value
        if ( strcmp($password, $confirmpassword) != 0 ) {
            return $this->_error("PASSWORD_CONFIRM_NO_MATCH");
        }
        return TRUE;
    }


    /**
     * This method tests a string as a valid
     * hostname value or a valid email string
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_hostemail($name) {
        if ( strchr($name, "@") ) {
            return $this->is_email($name);
        } else {
            return $this->is_hostname($name);
        }
    }


    /**
     * This function validates a single email address.
     * It supports email addresses in the format of
     * jane@blah.com or "Jane Doe <jane@blah.com>"
     *
     * @param string - the value to validate
     * @param bool - allows long email name format
     * @return TRUE = succes  FALSE = failed
     */
    function is_email ($email, $allow_name = true) {

        //no quotes allowed
        if ( strstr($email, '"') || strstr($email, "'") ) {
            return $this->_error("INVALID_EMAIL");
        }

        //lets see if the email is in the form of
        //"Foo Bar <foo@bar.com>"
        $name = explode(" ", $email);
        if ( count($name) > 1 ) {

            if (!$allow_name) {
                return $this->_error("INVALID_EMAIL");
            }

            //it looks like they gave us an email
            //with a leading name such as Foo Bar <foo@bar.com>
            //find the email address inside <>
            $found_email = FALSE;
            foreach( $name as $key => $val ) {
                if ( strstr($val, "@") ) {
                    $found_email = TRUE;
                    if ( (substr($val, 0, 1) == "<") && (substr($val, strlen($val)-1, 1) == ">") ) {
                        $email = substr($val, 1, strlen($val)-2 );
                    } else {
                        //invalid email address
                        //it must have a <
                        return $this->_error("INVALID_EMAIL_MISSING_BRACKETS");
                    }
                }
            }
            if ( !$found_email ) {
                //we couldn't find an email address
                //in the text.
                return $this->_error("INVALID_EMAIL");
            }
        }

        if ( !$this->is_alphanum($email, "@.-_/:") ) {
            return $this->_error("INVALID_EMAIL");
        }

        // "@.", ".@.", "_@.", .com, .net, .edu, .blah
        if ( !ereg("^( )*([a-zA-Z0-9_/:]|\\-|\\.)+@(([a-zA-Z0-9_]|\\-)+\\.)+[a-zA-Z]{2,4}$", $email, $arr) ) {
            return $this->_error("INVALID_EMAIL");
        }

        $len = strlen($email);
        if ( $len > VALIDATE_EMAIL_LENGTH ) {
            return $this->_error("INVALID_LENGTH_256");
        }

        // email cannot end with a dot
        if ( ereg("\.$", $email) ) {
            return $this->_error("INVALID_EMAIL");
        }

        // no space
        if ( ereg(" ", $email, $arr) ) {
            return $this->_error("INVALID_EMAIL");
        }
        return TRUE;
    }

    /**
     * This function tests a string that may
     * contain many email addresses seperated by
     * commas
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_manyemails( $emails ) {
        //first lets get the list of emails

        $email_arr = explode(",", $emails);
        foreach( $email_arr as $key => $email) {
            $res = $this->is_email(trim($email));
            if ( $res !== TRUE ) {
                return $res;
            }
        }
        return TRUE;
    }


    /**
     * This method validates a string as a
     * leap year.
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_leapyear($yyyy) {
        if (!($yyyy%4 == 0 && ($yyyy%100 != 0 || $yyyy%400 == 0))) {
            return $this->_error("NOT_LEAPYEAR");
        }
        return TRUE;
    }


    /**
     * This validates a atring as a valid date format
     * You can provide a seperator string that seperates
     * the fields
     *
     * NOTE: date is in YYYY-MO-DY format
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_date($value, $split_by="-") {

        $x = explode($split_by, $value);
        $year = $x[0];
        $month = $x[1];
        $day = $x[2];

        $retval = $this->is_datemonth($month);
        if ( $retval != VALID ) {
            return $retval;
        }

        $retval = $this->is_dateday($day);
        if ( $retval != VALID ) {
            return $retval;
        }

        $retval = $this->is_dateyear($year);
        if ( $retval != VALID ) {
            return $retval;
        }

        // Check the overall validity of the date
        if ( !checkdate($month, $day, $year) ) {
            return $this->_error("INVALID_FIELD");
        }

        return TRUE;

    }


    /**
     * This validates a string as a valid day of a month
     * It has to be greater then 0 and less then 31
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_dateday($day) {
        return $this->is_within_range($day, 0, 1, 31, "INVALID_DAY");
    }


    /**
     * This validates a string as a valid month of the year
     * between 1 and 12 inclusive
     * is_datemonth - checks whether its a proper month
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_datemonth($month) {
        return $this->is_within_range($month, 0, 1, 12, "INVALID_MONTH");
    }


    /**
     * See if the year is within
     * 1800 and 3000
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_dateyear($year) {
        return $this->is_within_range($year, 0, 1800, 3000, "INVALID_YEAR");
    }


    /**
     * This validates an array of values as a
     * valid date time
     *
     * NOTE: array must contain
     *       array(
     *             "month" => VALUE,
     *             "day" => VALUE,
     *             "year" => VALUE,
     *             "hour" => VALUE,
     *             "minutes" => VALUE,
     *             "seconds" => VALUE);
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_datetime($value) {
        $month=$value["month"];
        $day=$value["day"];
        $year=$value["year"];

        $time[hour]=$value["hour"];
        $time[minutes]=$value["minutes"];
        $time[seconds]=$value["seconds"];

        $date = $year."-".$month."-".$day;
        $retval = $this->is_date($date);
        if ( $retval != VALID ) {
            return $retval;
        }

        $retval = $this->is_time($time);
        return $retval;
    }

    /**
     * This validates an array of fields as a
     * valid time of the day
     *
     * NOTE: array must contain
     *       array(
     *             "hour" => VALUE,
     *             "minutes" => VALUE,
     *             "seconds" => VALUE);
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_time($value) {

        $hour=$value["hour"];
        $minutes=$value["minutes"];
        $seconds=$value["seconds"];

        $retval = $this->is_within_range($hour, 0, 0, 23, "INVALID_HOUR");
        if ( $retval != VALID ) {
            return $retval;
        }

        $retval = $this->is_within_range($minutes, 0, 0, 59, "INVALID_MINUTES");
        if ( $retval != VALID ) {
            return $retval;
        }

        $retval = $this->is_within_range($seconds, 0, 0, 59, "INVALID_SECONDS");
        return $retval;
    }


    /**
     * This is just a wrapper for
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_firstname ($firstname) {
        return $this->is_name($firstname);
    }


    /**
     * This is just a wrapper for
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_lastname ($lastname) {
        return $this->is_name($lastname);
    }


    /**
     * This validates a string as a valid zipcode
     *
     * numbers, whitespace allowed
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_zip ($zip) {
        if ( !$this->is_alphanum($zip, "- ") ) {
            return $this->_error("INVALID_ZIP");
        }
        return TRUE;
    }

    /**
     * This tests a string as a valid
     * credit card expiration date.
     * You can pass in an optional date delimiter
     * string.  The default is -
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_ccexp($value, $split_by="-") {

        $ret = $this->is_date($value, $split_by);
        if ( $ret != 1 ) {
            return $ret;
        }

        $x = explode($split_by, $value);
        $year = $x[0];
        $month = $x[1];
        $day = $x[2];

        $d = explode(",",date("Y,m,d"));
        $today = $d[0] * 10000 + $d[1];
        $exp = $year * 10000 + $month;
        if ( $exp <  $today ) {
            return $this->_error("CCEXP");
        }
        if ( $year - $d[0] > 30 ) {
            return $this->_error("CCEXP_TOO_FAR");
        }
        return TRUE;
    }

    /**
     * This validates a string as a valid "country code"
     * which is a 2 alphanumerical character string
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_countrycode($value) {
        if ( (!$this->is_alphanum($value)) || ((strlen($value) != 2)) ) {
            return $this->_error("INVALID_FIELD");
        }
        return TRUE;
    }

    /**
     * This method validates a string as a valid url
     * It inclues the prefix, hostname/ip, port number
     * and path.
     *
     * NOTE: format is in
     *       [http://] hostip [:port number] [path]
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_url($url) {
        // The first few characters could be http://. If so, remove them
        $url = ereg_replace("^http(s)?:\/\/", "", $url);

        // Get the location of first : or '/'
        $len = strcspn($url, ":\/");
        $host = substr($url, 0, $len);
        $validate = $this->is_hostip($host);
        if ( $validate != 1 ) {
            return $validate;
        }

        $rest = substr($url, $len);

        // Extract and verify the port number, if specified.
        if ( ereg("^(:)([^\/]*)(.*)", $rest, $regs) ) {
            $port_num = $regs[2];
            if ( !$this->is_num($port_num) ) {
                return $this->_error("INVALID_PORT_NUM");
            }
            $rest = $regs[3];
        }

        // The path field may be null
        if ( ereg("^[[:space:]]*$", $rest) ) {
            return TRUE;
        }

        return $this->is_urlpath($rest);
    }

    /**
     * This method validates a strict url.
     * It is the same as is_url, except that it requires
     * the prefix http://
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_strict_url($url) {

        $decoded_url = parse_url( $url );
        if ( !$decoded_url["scheme"] ) {
            //looks like they didn't provide the scheme
            return $this->_error("INVALID_URL");
        }
        return $this->is_url($url);
    }


    /**
     * Validate if the string is a good candidate
     * to become an Title
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_title($name) {
        if ( !$this->is_alphanum($name," ") )
            return "Only alpha-numeric characters are allowed";
        return TRUE;
    }



    /**
     * Validate domain
     * Will check if a domain is valid
     *
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_valid_domain($domain_value, $allow_www=false) {

        // we allow 'none' as empty domain
        if ( $domain_value=='none' ) return TRUE;

        // allow uppercase domains
        $domain_value = strtolower($domain_value);

        if ( !ereg( "^(([a-z0-9]{1,63}|([a-z0-9][a-z0-9\-]{1,61}[a-z0-9]))\.)+[a-z]{2,4}$", $domain_value) ) {
            return $domain_value . " is not RFC compliant";
        } else if ( !$allow_www && ereg( "^www\.", $domain_value) ) {
            return $domain_value . " is invalid.";
        }
        return TRUE;
    }

    /**
     * no comment
     *
     */
    function is_host($host) {
        return $this->is_valid_domain($host, TRUE);
    }

    /**
     * no comment
     *
     */
    function is_hostlist($hostlist) {
        $a = explode(",", str_replace(" ", "", $hostlist));
        foreach ($a as $host) {
            $r = $this->is_valid_domain($host, TRUE);
            if ( $r !== TRUE )
                return $r;
        }
        return TRUE;
    }

    /**
     * Validate if the string matches a regex
     *
     * @param string - the regex string
     * @param string - the value to validate
     * @return TRUE = succes  FALSE = failed
     */
    function is_regex($regex, $str) {
        if (preg_match($regex, $str)) {
            return TRUE;
        } else {
            return FALSE;
        }
    }

}
?>
