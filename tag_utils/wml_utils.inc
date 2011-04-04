<?php

/**
 * This file contains some utility functions
 * to help build some Tag objects that are
 * commonly used in wml.
 *
 * This file only builds the helper functions that
 * build wml specific tags.  Some wml tags are identical
 * to their HTML counterparts.  You should use the html_*
 * functions for those.
 *
 * $Id: wml_utils.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */

/**
 * the list of html_* helper functions for HTML tags
 * that are valid for WML.
 *
 * html_head()
 * html_meta()
 * html_comment()
 * html_br()
 * html_p()
 * html_table()
 * html_td()
 * html_tr()
 * html_b()
 * html_big()
 * html_em()
 * html_i()
 * html_small()
 * html_strong()
 * html_u()
 * html_optgroup()
 * html_option()
 * 
 */ 


/**
 * build an href with content and attributes.
 *
 * @param   string $url - the href attribute.
 * @param   string $content - the visible link text.
 * @param   string $class - the css class to use.
 * @param   string $title - the title attribute
 * @return  Atag object.
 */
function wml_a($url, $content, $class=NULL, $title=NULL) {
	return html_a($url, $content, $class, NULL, $title);
}

/**
 * this builds an <anchor> tag
 *
 * @return ANCHORtag object
 */
function wml_anchor() {
    $tag = new ANCHORtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * this function builds a wml <access /> tag
 *
 * @param string - the domain attribute
 * @param string - the path attribute
 * @param string - the id attribute
 * @param string - the class attribute
 *
 * @return ACCESStag object
 */
function wml_access( $domain, $path=NULL, $id=NULL, $class=NULL ) {
	$attributes = array("domain" => $domain );

	if ($path != NULL) {
		$attributes["path"] = $path;
	}

	if ($id != NULL) {
		$attributes["id"] = $id;
	}

	if ($class != NULL) {
		$attributes["class"] = $class;
	}

	return new ACCESStag( $attributes );
}


/**
 * This function helps build a <card> tag
 *
 * @param string - the title attribute
 * @param string - the id attribute
 * @param string - the class attribute
 * @param mixed - any N number of params for
 *                content for the tag
 * @return CARDtag object
 */
function wml_card( $title, $id=NULL, $class=NULL ) {
	$attributes = array("title" => $title);

	if ($id != NULL) {
		$attributes["id"] = $id;
	}

	if ($class != NULL) {
		$attributes["class"] = $class;
	}

	$tag = new CARDtag( $attributes );
	$num_args = func_num_args();
	for ($i=3;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
    return $tag;
}


/**
 * This function builds the WML <do> tag
 *
 * @param string - the required 'type' attribute
 * @param mixed - any N number of params for
 *                content for the tag 
 * @return DOtag object
 */
function wml_do($type) {
	$tag = new DOtag( array("type" => $type ) );
	$num_args = func_num_args();
	for ($i=1;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
    return $tag;
}


/**
 * This function builds an <fieldset> tag
 * for WML.
 *
 * @param mixed - any N number of params for
 *                content for the tag 
 * @return FIELDSETtag object
 */
function wml_fieldset() {
    $tag = new FIELDSETtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}


/**
 * This function builds the WML <go> tag
 *
 * @param string - the required 'href' attribute
 * @param string - the optional 'method' attribute
 * @param mixed - any N number of params for
 *                content for the tag 
 * @return GOtag object
 */
function wml_go($href, $method="get") {
	$tag = new GOtag(array("href" => $href,
						   "method" => $method));
	$num_args = func_num_args();
	for ($i=2;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
    return $tag;
}

/**
 * This function builds an <img> tag,
 * which refers to a .wbmp format image.
 *
 *
 * @return IMGtag object
 */
function wml_img( $src, $width=NULL, $height=NULL, $alt=NULL) {
	$attributes = array("src" => $src);

	if ($width != NULL) {
		$attributes["width"] = $width;
	}
	if ($height != NULL) {
		$attributes["height"] = $height;
	}
	if ($alt != NULL) {
		$attributes["alt"] = $alt;
	}

	return new IMGtag( $attributes );
}


/**
 * This function builds the WML <input> tag object
 *
 * @param string - the required 'name' attribute
 *
 * @return INPUTtag object
 */
function wml_input($name, $type="text", $value=NULL, $size=NULL ) {
	$attributes = array( "name" => $name,
						 "type" => $text );

	if ($value != NULL) {
		$attributes["value"] = $value;
	}
	if ($size != NULL) {
		$attributes["size"] = $size;
	}


	return new INPUTtag( $attributes );
}

/**
 * This function builds the WML <noop> tag
 *
 * @return NOOPtag object
 */
function wml_noop() {
	return new NOOPtag;
}


/**
 * This function builds a WML <onevent> tag
 *
 * @param string - the required 'type' attribute
 *
 * @return ONEVENTtag object
 */
function wml_onevent( $type ) {
	$tag = new ONEVENTtag( array("type" => $type ) );
	$num_args = func_num_args();
	for ($i=1;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
    return $tag;
}
 
/**
 * This function builds a WML <postfield> tag
 *
 * @param string - the required 'name' attribute
 * @param string - the required 'value' attribute
 *
 * @return POSTFIELDtag object
 */
function wml_postfield( $name, $value ) {
	return new POSTFIELDtag( array( "name" => $name,
									"value" => $value ));
}

/**
 * This function builds a WML <prev> tag object
 *
 * @param mixed - any N number of params for
 *                content for the tag
 * 
 * @return PREVtag object
 */
function wml_prev() {
    $tag = new PREVtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * This function builds a WML <refresh> tag object
 *
 * @param mixed - any N number of params for
 *                content for the tag
 * 
 * @return REFRESHtag object
 */
function wml_refresh() {
    $tag = new REFRESHtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * This function builds the WML <select> tag
 *
 * @param array - an array of name value pairs for
 *                the options.  the format is
 *                array( LABEL => VALUE );
 *                each <option value="VALUE">LABEL</option>
 *                ie
 *                array( "test" => "foo")  would give an option
 *                of <option value="foo">test</option>
 *
 * @return SELECTtag object
 */
function wml_select($options=array()) {
	$tag = new SELECTtag;
	foreach ( $options as $content => $value ) {
		$select->add( html_option($value, $content) );
	}
	return $select;

}

/**
 * This function builds the WML <setvar> tag
 *
 * @param string - the required 'name' attribute
 * @param string - the required 'value' attribute
 * @return SETVARtag object
 */
function wml_setvar($name, $value) {
	return new SETVARtag( array("name" => $name,
								"value" => $value));
}

/**
 * this function builds a <template> tag
 * and it's content
 *
 * @param mixed - any N number of params for
 *                content for the tag
 *
 * @return TEMPLATEtag object
 */
function wml_template() {
    $tag = new TEMPLATEtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * This function builds the WML <timer> tag
 * the time unit of the value is 1/10 of a second.
 *
 * @param string - the required 'value' attribute
 *
 * @return TIMERtag object
 */
function wml_timer( $value ) {
	return new TIMERtag( array("value" => $value ));
}


/**
 * This function builds a <wml> tag
 *
 * @param mixed - any N number of params for
 *                content for the tag
 *
 * @return WMLtag object
 */
function wml_tag( ) {
    $tag = new TEMPLATEtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

?>
