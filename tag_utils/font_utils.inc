<?php

/**
 * This file contains some utility functions
 * for building <span> and <div> objects
 * that have specific css classes.
 *
 * $Id: font_utils.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */


 /**  
  *
  * There are example css classes defined for all
  * of the css classes used in here in 
  * css/fonts.css
  * 
  */


 /**
  * Build a SPANtag object with
  * css class of .font8.
  *
  * @param mixed - any # of arguments to live
  *                inside the tag
  * @return SPANtag object
  */
 function span_font8(  ) {    
    $span = html_span("font8");
    $args = func_get_args();
    call_user_func_array( array(&$span, "add"), $args);
    return $span;
 }

 /**
  * Build a SPANtag object with
  * css class of .font8bold.
  *
  * @param mixed - any # of arguments to live
  *                inside the tag
  * @return SPANtag object
  */
 function span_font8bold(  ) {    
    $span = html_span("font8bold");
    $args = func_get_args();
    call_user_func_array( array(&$span, "add"), $args);
    return $span;
 }

 /**
  * Build a SPANtag object with
  * css class of .font10.
  *
  * @param mixed - any # of arguments to live
  *                inside the tag
  * @return SPANtag object
  */
 function span_font10(  ) {    
    $span = html_span("font10");
    $args = func_get_args();
    call_user_func_array( array(&$span, "add"), $args);
    return $span;
 }

 /**
  * Build a SPANtag object with
  * css class of .font10bold.
  *
  * @param mixed - any # of arguments to live
  *                inside the tag  
  * @return SPANtag object
  */
 function span_font10bold(  ) {    
    $span = html_span("font10bold");
    $args = func_get_args();
    call_user_func_array( array(&$span, "add"), $args);
    return $span;
 }

 /**
  * Build a SPANtag object with
  * css class of .font12.
  *
  * @param mixed - any # of arguments to live
  *                inside the tag  
  * @return SPANtag object
  */
 function span_font12(  ) {
    $span = html_span( "font12");
    $args = func_get_args();
    call_user_func_array( array(&$span, "add"), $args);
    return $span;
 }

 /**
  * Build a SPANtag object with
  * css class of .font12bold.
  *
  * @param mixed - any # of arguments to live
  *                inside the tag  
  * @return SPANtag object
  */
 function span_font12bold(  ) {    
    $span = html_span( "font12bold");
    $args = func_get_args();
    call_user_func_array( array(&$span, "add"), $args);
    return $span;
 }


 /**
  * Build a SPANtag object with
  * css class of .font14.
  *
  * @param mixed - any # of arguments to live
  *                inside the tag  
  * @return SPANtag object
  */
 function span_font14(  ) {        
    $span = html_span( "font14" );
    $args = func_get_args();
    call_user_func_array( array(&$span, "add"), $args);
    return $span;
 }

 /**
  * Build a SPANtag object with
  * css class of .font14bold.
  *
  * @param mixed - any # of arguments to live
  *                inside the tag  
  * @return SPANtag object
  */
 function span_font14bold(  ) {
    $span = html_span( "font14bold" );
    $args = func_get_args();
    call_user_func_array( array(&$span, "add"), $args);
    return $span;
 }



 /**************************************
  *  div_* functions that do the same 
  *
  **************************************/


 /**
  * Build a DIVtag object with
  * css class of .font8.
  *
  * @param mixed - any # of arguments to live
  *                inside the tag  
  * @return DIVtag object
  */
 function div_font8(  ) {    
    $div = html_div("font8");
    $args = func_get_args();
    call_user_func_array( array(&$div, "add"), $args);
    return $div;
 }

 /**
  * Build a DIVtag object with
  * css class of .font8bold.
  *
  * @param mixed - any # of arguments to live
  *                inside the tag  
  * @return DIVtag object
  */
 function div_font8bold(  ) {    
    $div = html_div("font8bold");
    $args = func_get_args();
    call_user_func_array( array(&$div, "add"), $args);
    return $div;
 }


 /**
  * Build a DIVtag object with
  * css class of .font10.
  *
  * @param mixed - any # of arguments to live
  *                inside the tag  
  * @return DIVtag object
  */
 function div_font10(  ) {    
    $div = html_div("font10");
    $args = func_get_args();
    call_user_func_array( array(&$div, "add"), $args);
    return $div;
 }

 /**
  * Build a DIVtag object with
  * css class of .font10bold.
  *
  * @param mixed - any # of arguments to live
  *                inside the tag  
  * @return DIVtag object
  */
 function div_font10bold(  ) {    
    $div = html_div("font10bold");
    $args = func_get_args();
    call_user_func_array( array(&$div, "add"), $args);
    return $div;
 }

 /**
  * Build a DIVtag object with
  * css class of .font12.
  *
  * @param mixed - any # of arguments to live
  *                inside the tag  
  * @return DIVtag object
  */
 function div_font12(  ) {
    $div = html_div( "font12");
    $args = func_get_args();
    call_user_func_array( array(&$div, "add"), $args);
    return $div;
 }

 /**
  * Build a DIVtag object with
  * css class of .font12bold.
  *
  * @param mixed - any # of arguments to live
  *                inside the tag  
  * @return DIVtag object
  */
 function div_font12bold(  ) {    
    $div = html_div( "font12bold");
    $args = func_get_args();
    call_user_func_array( array(&$div, "add"), $args);
    return $div;
 }


 /**
  * Build a DIVtag object with
  * css class of .font14.
  *
  * @param mixed - any # of arguments to live
  *                inside the tag  
  * @return DIVtag object
  */
 function div_font14(  ) {        
    $div = html_div( "font14" );
    $args = func_get_args();
    call_user_func_array( array(&$div, "add"), $args);
    return $div;
 }

 /**
  * Build a DIVtag object with
  * css class of .font14bold.
  *
  * @param mixed - any # of arguments to live
  *                inside the tag  
  * @return DIVtag object
  */
 function div_font14bold(  ) {
    $div = html_div( "font14bold" );
    $args = func_get_args();
    call_user_func_array( array(&$div, "add"), $args);
    return $div;
 }


?>
