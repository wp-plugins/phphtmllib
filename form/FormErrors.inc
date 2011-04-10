<?php
/**
 * 
 * This file holds the error codes and error messages
 * associated with those codes for English
 *
 * $Id: FormErrors.inc 3546 2011-04-10 02:49:37Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 */

class FormErrors {

    /**
     * error array from the FormValidation
     * class.
     */
    var $error_array = array(
         "ERR_OK" => 0,
         "ERR_EMPTY" => "This field cannot be empty",

         "INVALID_IP" => "The IP address you have entered is not in a valid format",
         "INVALID_LOGIN_NAME_LENGTH" => "The User Name must be less than 40 characters.",
         "INVALID_LOGIN_NAME_EMPTY" => "The User Name field must not be blank.",
         "INVALID_LOGIN_NAME_CHARACTERS"  => "The User Name field may contain only letters and numbers.",
         "INVALID_PASSWORD_EMPTY" => "The Password field must not be blank.",
         "INVALID_PASSWORD_LENGTH" => "The Password field should be less than 40 characters.",
         "INVALID_PASSWORD_CHARACTERS" => "The Password field contains invalid characters",
         "PASSWORD_CONFIRM_NO_MATCH" => "The password and confirmation password you have typed do not match. Please try again.",

         "INVALID_PATH_LENGTH" => "The path field does not meet the requirements. It must be less than 40 characters.",
         "INVALID_PATH_EMPTY" => "The path field must not be blank.",
         "INVALID_PATH_CHARACTERS" => "The path field may contain only letters and numbers.",

         "INVALID_NUMBER" => "This field must contain a valid number.",
         "INVALID_LENGTH" => "Entry has exceeded allowed length.",
         "INVALID_LENGTH_N" => "This field must not exceed XX_MAX characters in length.  The character count is XX_LENGTH",
         "INVALID_LENGTH_40" => "This field must not exceed 40 characters in length.",
         "INVALID_LENGTH_256" => "This field must not exceed 256 characters in length.",
         "INVALID_NAME_EMPTY" => "The name must not be empty.",
         "INVALID_NAME_CHARACTERS" => "The name may contain only letters and numbers.",

         "EMPTY_FIELD" => "This field can not be empty",
         "INVALID_DOMAIN_NAME" => "This domain name you have entered is not valid.",
         "INVALID_HOST_NAME" => "The host name you have entered is not valid.",
         "INVALID_IP_EMPTY" => "The IP Address must not be empty.",
         "INVALID_EMAIL_EMPTY" => "The email address can not be empty.",
         "INVALID_EMAIL" => "The email address is not properly formatted.",         
         "INVALID_PHONE" => "The phone number you have entered is not properly formatted.",
         
         "ONLY_DIGITS" => "Only numeric digits are allowed in this field.",
         "INVALID_MONTH" => "You have entered an invalid month.",
         "INVALID_DAY" => "You have entered an invalid day.",
         "INVALID_YEAR" => "You have entered an invalid year.",
         "INVALID_HOUR" => "You have entered an invalid hour.",
         "INVALID_MINUTES" => "You have entered invalid mintues.",
         "INVALID_SECONDS" => "You have entered invalid seconds.",
         "INVALID_LEAP_DAY" => "The year you have entered is not a leap year. February only has 28 days.",
         "INVALID_30_DAY" => "There are only 30 days in this month.",
         "INVALID_ZERO_HUNDRED_NUMBER" => "This number must be between 0 and 100.",
         "INVALID_MONEY" => "This must be a valid amount in dollars and cents.",
         "INVALID_FLOAT" => "This must be a valid floating point number.",
         "INVALID_EMAIL_MISSING_BRACKETS" => "The long form email address must contain the < > characters, such as \"Foo Bar &lt;foo@bar.com&gt;\".",

         "INVALID_EMPTY" => "This field cannot be empty.",
         "INVALID_STATE" => "You must specify a 2 letter state code (ie. 'CA' for California).",
         "INVALID_ZIP" => "Invalid zip code",
         "INVALID_FIELD" => "This field's value is invalid.",
         "INVALID_TIME_FORMAT" => "You have entred an invalid date/time format.",
         "INVALID_YEAR_DATE_1990_3000" => "The year must be between 1990 and 3000",

         "INVALID_PRICE" => "Price must be a valid, non-zero amount in dollars and cents.",

         "CCEXP" => "Credit card expired already",
         "CCEXP_TOO_FAR" => "Credit card expires in more than 30 years?",
         "NOT_IN_RANGE" => "Value not in range.",
         "INVALID_URL" => "URL must be in the form of http[s]://hostip [:port number] [path]",         
         "INVALID_STANDALONE_HOST_NAME" => "You have entered an invalid host name. Please enter a Hostname without the domainname.",

         "INVALID_ALPHANUM_CHARACTERS" => "This field may contain only numbers and letters.",
         "NOT_LEAPYEAR" => "The year is not a leapyear"
         );

    /**
     * This returns the appropriate error message
     * based on the error #.
     *
     * @param string - the error code
     * @return string - the error string.
     *
     */
    function get_error_msg($err) {
        return $this->error_array[$err];
    }
}
?>
