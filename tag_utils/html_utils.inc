<?php

/**
 * This file contains some utility functions
 * to help build some Tag objects that are
 * commonly used in html.
 *
 * $Id: html_utils.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 *
 */


/**
 * build an href with content and attributes.
 *
 * @tutorial HTMLTagClass.cls#helper
 *
 * @author Walt A. Boring
 * @param   string $url - the url to go to.
 * @param   string $content - the visible link text.
 * @param   string $class - the css class to use.
 * @param   string $target - the target browser
 *                           window/frame for the url.
 * @param   string $title - the title attribute
 * @return  Atag object.
 */
function html_a($url, $content, $class=NULL, $target=NULL, $title=NULL) {

    $attributes = array("href" => $url);
    if ($class) {
        $attributes["class"] = $class;
    }
    if ($target) {
        $attributes["target"] = $target;
    }

	if ($title) {
		$attributes["title"] = $title;
	}

    $a = new Atag( $attributes, $content);
	$a->set_collapse();

    return $a;
}

/**
 * build an <ABBR> tag with content.
 *
 *  This is to build an abbreviation.
 *  normally its just
 *  <abbr title="foo bar">foo</abbr>
 *
 * @param string - the title attribute
 * @param mixed - the content for the tag
 * @return  ABBRtag object.
 */
function html_abbr($title, $content) {	
    $tag = new ABBRtag(array("title"=>$title));
	$tag->add( $content );
    return $tag;
}

/**
 * build an <ACRONYM> tag with content.
 *
 *  This is to build an acronym.
 *  normally its just
 *  <acronym title="foo bar">foo</abbr>
 *
 * @param string - the title attribute
 * @param mixed - the content for the tag
 * @return  ACRONYMtag object.
 */
function html_acronym($title, $content) {
    $tag = new ACRONYMtag( array("title" => $title));
	$tag->add( $content );
    return $tag;
}

/**
 * build an <ADDRESS> tag with content.
 *
 * @return  ADDRESStag object.
 */
function html_address() {
    $tag = new ADDRESStag;
	$num_args = func_num_args();
	for ($i=0;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
    return $tag;
}

/**
 * build an <APPLET> tag with content.
 *
 * @return  APPLETtag object.
 */
function html_applet() {
    $tag = new APPLETtag;
    $args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build an <AREA> tag with content.
 *
 * @param string - the href for the area
 * @param string - the coords value
 *                 circle x,y,radius
 *                 poly x1,y1,...xn,yn
 *                 left,top,right,bottom
 * @param string - the shape
 *                 DEFAULT: rect
 *                 circle, rect, poly, default
 * @param string - the alt text
 * @param string - the target
 *                 _blank, _parent, _self, _top
 * @param string - the title text
 *
 * @return  AREAtag object.
 */
function html_area($href, $coords, $shape="rect",
				   $alt="", $target="", $title="") {	

	$attributes = array("href" => $href,
						"coords" => $coords,
						"shape" => $shape);
	if ($alt != "") {
		$attributes["alt"] = $alt;
	}

	if ($target != "") {
		$attributes["target"] = $target;
	}

    if ($title != "") {
		$attributes["title"] = $title;
	}

    $tag = new AREAtag( $attributes );
    return $tag;
}

/**
 * build a bold <b> tag with content.
 *
 * @author Walt A. Boring
 * @return  BRtag object.
 */
function html_b() {
    $tag = new Btag;
    $args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <base> tag.
 * This tag MUST go in the <head>
 *
 * @param string - the href
 * @param string - the target
 *                 _blank, _parent, _self, _top
 * @return  BASEtag object.
 */
function html_base($href, $target="") {
	$attributes = array( "href" => $href);

	if ($target != "") {
		$attributes["target"] = $target;
	}

    $tag = new BASEtag( $attributes );
	return $tag;
}

/**
 * build a <bdo> tag.
 * dir attribute is required.
 *
 * @param string - the dir attribute
 *                ltr, rtl
 * @param mixed - any number of text
 *                content params.
 * @return BDOtag object.
 */
function html_bdo($dir) {
	$attributes = array( "dir" => $dir);

    $tag = new BDOtag( $attributes );

	$num_args = func_num_args();
	for ($i=1;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}

	return $tag;
}


/**
 * build a <big> tag with content.
 *
 * @author Walt A. Boring
 * @return BIGtag object.
 */
function html_big() {
    $tag = new BIGtag;
    $args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <blockquote> tag with content.
 *
 * @author Walt A. Boring
 * @return BLOCKQUOTEtag object.
 */
function html_blockquote() {
    $tag = new BLOCKQUOTEtag;
    $args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <body> tag with content.
 *
 * @author Walt A. Boring
 * @return BODYtag object.
 */
function html_body() {
    $tag = new BODYtag;
    $args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * builds n # of  <br> tags.
 *
 * @param int - the number of
 *              br tags you want
 *
 * @return  mixed - BRtag object.
 *                  or Container
 */
function html_br($num=1, $class=null) {

    if ($class !== null) {
        $attributes = array('class' => $class);
    } else {
        $attributes = array();
    }

	if ($num == 1){
		return new BRtag($attributes);
	} else if ($num > 1) {
		$obj = new Container;
		$obj->set_collapse();
		for ($i=0; $i<$num;$i++) {
			$obj->add( new BRtag($attributes) );
		}
        return $obj;
	} else if ($num <= 0) {
		return NULL;
	}
}

/**
 * build a <button> tag with content.
 *
 * @param string - the button type
 *                 button, reset, submit
 *                 DEFAULT : button
 * @param mixed - any number of items as
 *                content.
 * @return BUTTONtag object.
 */
function html_button($type="button") {
    $tag = new BUTTONtag( array("type"=> $type));
	$num_args = func_num_args();
	for ($i=1;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
    return $tag;
}

/**
 * build a <caption> tag with content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return CAPTIONtag object.
 */
function html_caption() {
    $tag = new CAPTIONtag;
    $args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <center> tag with some content.
 * DEPRICATED
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return CENTERtag object.
 */
function html_center( ) {
	$tag = new CENTERtag;
    $args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <cite> tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return CITEtag object.
 */
function html_cite( ) {
	$tag = new CITEtag;
    $args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <code> tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return CODEtag object.
 */
function html_code( ) {
	$tag = new CODEtag;
    $args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <col> tag
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return CODEtag object.
 */
function html_col($width='', $align='', $span='' ) {
	$attributes = array();
	if ($width != '') {
		$attributes["width"] = $width;
	}
	if ($align != '') {
		$attributes["align"] = $align;
	}
	if ($span != '') {
		$attributes["span"] = $span;
	}
	$tag = new COLtag( $attributes );
    return $tag;
}

/**
 * build a <colgroup> tag.
 *
 * NOTE: The colgroup element is an empty
 *       element that contains attributes
 *       only. To create columns, you must
 *       specify td elements within a tr
 *       element.
 *
 * @param array - tag attributes.
 * @return COLGROUPEtag object.
 */
function html_colgroup( $attributes ) {
    return new COLGROUPtag( $attributes );
}

/**
 * render an html comment string
 *
 * @param   string - the string to comment.
 * @return  string - the string wrapped in
 *                   the html comment block
 */
function html_comment( $string ) {
    return '<!-- ' . $string . ' //-->';
}

/**
 * build a <dd> tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return DDtag object.
 */
function html_dd( ) {
	$tag = new DDtag;
    $args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <del> tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return DELtag object.
 */
function html_del( ) {
	$tag = new DELtag;
    $args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}


/**
 * build a <dfn> tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return DFNtag object.
 */
function html_dfn( ) {
	$tag = new DFNtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * html_div() is defined in
 * divtag_utils.inc
 */

/**
 * build a <dl> tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return DLtag object.
 */
function html_dl( ) {
	$tag = new DLtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <dt> tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return DTtag object.
 */
function html_dt( ) {
	$tag = new DTtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <em> tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return EMtag object.
 */
function html_em( ) {
	$tag = new EMtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <fieldset> tag with some content.
 *
 * @param   mixed - The legend text, or the
 *                  LEGENDtag for the fieldset.
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return FIELDSETtag object.
 */
function html_fieldset($legend="") {
	$tag = new FIELDSETtag;

    //see if they passed in the legend
    if ($legend != "") {
        if (is_object($legend)) {
            $tag->add( $legend );
        } else {
            $tag->add( html_legend( $legend ) );
        }
    }

	$num_args = func_num_args();
	for ($i=1;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
    return $tag;
}

/**
 * html_form() is defined
 * in form_utils.inc
 */


/**
 * build an H1 tag object with content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  H1tag object.
 */
function html_h1( ) {
    $tag = new H1tag;
    $tag->set_collapse();
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build an H2 tag object with content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  H2tag object.
 */
function html_h2( ) {
    $tag = new H2tag;
    $tag->set_collapse();
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}


/**
 * build an H3 tag object with content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  H3tag object.
 */
function html_h3( ) {
    $tag = new H3tag;
    $tag->set_collapse();
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build an H4 tag object with content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  H4tag object.
 */
function html_h4( ) {
    $tag = new H4tag;
    $tag->set_collapse();
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build an H5 tag object with content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  H5tag object.
 */
function html_h5( ) {
    $tag = new H5tag;
    $tag->set_collapse();
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}


/**
 * build an H6 tag object with content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  H6tag object.
 */
function html_h6( ) {
    $tag = new H6tag;
    $tag->set_collapse();
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build an <head> tag object with content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  HEADtag object.
 */
function html_head( ) {
    $tag = new HEADtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build an <hr> tag object.
 *
 * @return  HRtag object.
 */
function html_hr( ) {
    return new HRtag;
}

/**
 * build an <html> tag object.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  HTMLtag object.
 */
function html_html( ) {
    $tag = new HTMLtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}


/**
 * build a <i> tag with some content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return Itag object.
 */
function html_i( ) {
    $tag = new Itag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <irame> tag with some content.
 *
 * @author Walt A. Boring
 * @param   src - the url for the iframe
 * @return Itag object.
 */
function html_iframe($src, $width="", $height="", $scrolling="") {
    $attributes = array("src" => $src);
    if ($width != "") {
        $attributes["width"] = $width;
    }
    if ($height != "") {
        $attributes["height"] = $height;
    }
    if ($width != "") {
        $attributes["scrolling"] = $scrolling;
    }
    return new IFRAMEtag( $attributes );
}


/**
 * Build an <img> tag.
 *  If width and or height are not provided
 *  we do not set them in the tag.
 *
 * @author Walter A. Boring IV
 * @param   string - $image - image src
 * @param   int    - $width - width of the image.
 * @param   int    - $heigth - height of the image
 * @param   int    - $border - border flag.
 * @param   string - $alt - alt tag for the image
 * @param   string - $usemap - the image map name
 * @param   string - $align - the align attribute
 * @param   string - $localfilename - the full path
 *                   to the filename.  If this is set
 *                   and $width == '' and $height == ''
 *                   then we will try and determine the
 *                   size attributes of the image.
 * @return  IMGtag object.
 */
function html_img( $image, $width='', $height='', $border=0,
				   $alt="", $usemap=NULL, $title=NULL,
                   $align=NULL, $filename=NULL ) {
    $attributes = array( "src" => $image,
                         "border" => $border,
                         "alt" => $alt);

    if ($height != '') {
        $attributes["height"] = $height;
    }
    if ($width != '') {
        $attributes["width"] = $width;
    }

    if ($height === '' && $width === ''
        && $filename !== NULL) {

        $img = getimagesize($filename);
        if ($img) {
            $attributes['width'] = $img[0];
            $attributes['height'] = $img[1];
        }
    }

    //only add usemap entry if its not NULL
    if ($usemap) {
        $attributes["usemap"] = $usemap;
    }

	if ($title) {
		$attributes["title"] = $title;
	}

    if ($align != NULL) {
        $attributes["align"] = $align;
    }

    return new IMGtag( $attributes );
}


/**
 * This method is a wrapper for html_img() that
 * allows us to automatically set the width, and
 * height based upon the discovered image attributes.
 *
 * NOTE: This assumes the $image includes a path which
 *       is on the local filesystem based off of the
 *       DOCUMENT_ROOT
 *
 *       So if DOCUMENT_ROOT = /www/mysite.com/html
 *       and $image = '/images/foo.jpg'
 *
 *       getimagesize will look in
 *       $_SERVER['DOCUMENT_ROOT'].$image
 *
 * @param   string - $image - image src
 * @param   int    - $border - border flag.
 * @param   string - $alt - alt tag for the image
 * @param   string - $usemap - the image map name
 * @param   string - $align - the align attribute
 * @return IMGtag object
 */
function html_img_local($image, $border=0, $alt='', $usemap=NULL,
                        $title=NULL, $align=NULL) {
    return html_img($image, '', '', $border, $alt, $usemap,
                    $title, $align, $_SERVER['DOCUMENT_ROOT'].$image);
}


/**
 * This method is similar to html_img_local, but it assumes the
 * image is on a remote server, so it won't prepent $_SERVER['DOCUMENT_ROOT']
 * to the getimagesize() call.  This is purely a wrapper for html_img()
 * eliminating the width, and height attributes.
 *
 * @param   string - $image - image src
 * @param   int    - $border - border flag.
 * @param   string - $alt - alt tag for the image
 * @param   string - $usemap - the image map name
 * @param   string - $align - the align attribute
 * @return IMGtag object
 */
function html_img_remote($image, $border=0, $alt='', $usemap=NULL,
                        $title=NULL, $align=NULL) {
    return html_img($image, '', '', $border, $alt, $usemap,
                    $title, $align, $image);
}


/**
 * build an hlink for an image.
 * this automatically turns off indenting
 * and newlines, so it formats well
 *
 * @param   string - $url - href for the <a>
 * @param   string - $image - src for the <img>
 * @param   int    - $width - width of the image
 * @param   int    - $height - height of the image
 * @param   int    - $border - for the <img>
 * @param   string - $alt - for the <img ALT="">
 * @param   string - $usemap - the image map name
 * @param   string - $target - the <a target="blah">
 * @param   string - $title - the title attribute
 * @param   string - $align - the align attribute
 * @return  Atag object with <img> as content
 *
 */
function html_img_href( $url, $image, $width='', $height='', $border=0,
						$alt="", $usemap=NULL, $target=NULL, $title=NULL, $align=NULL) {
    $img = html_img($image, $width, $height, $border, $alt, $usemap, $title, $align);
    $a = html_a($url, $img, NULL, $target);	
    return $a;
}


/**
 * This builds an <input> object
 * NOTE: This wrapper automatically
 *       calls htmlspecialchars() on
 *       the value attribute's data.
 *
 * @param string - the type attribute
 * @param string - the name attribute
 * @param string - the value attribute
 * @param array  - any other name=>value attributes
 *                 for the tag
 *
 * @return INPUTtag object.
 */
function html_input( $type, $name, $value='', $attributes=array() ) {
    $attrib = array( "type" => $type,"name" => $name,"value" => $value);
    $attributes = array_merge( $attrib, $attributes );
    return new INPUTtag( $attributes );
}

/**
 * build a <ins> tag with some content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return INStag object.
 */
function html_ins( ) {
    $tag = new INStag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <kbd> tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return KBDtag object.
 */
function html_kbd( ) {
    $tag = new KBDtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <label> tag with some content.
 *
 * @param   string - the id of the form
 *                   element to tie this
 *                   label to.
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return LABELtag object.
 */
function html_label($for="") {

	$attributes = array();
	if ($for != "") {
		$attributes["for"] = $for;
	}
    $tag = new LABELtag( $attributes );
	$num_args = func_num_args();
	for ($i=1;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
    return $tag;
}

/**
 * build a <legend> tag with some content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return LEGENDtag object.
 */
function html_legend( ) {
    $tag = new LEGENDtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}


/**
 * build a <LI> tag with some content..
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return LItag object.
 */
function html_li( ) {
    $tag = new LItag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);    return $tag;
}

/**
 * build a <LINK> tag with some content..
 *
 *
 * @param   string - the href link
 * @param   string - the rel attribute
 * @param   string - the type of content.
 * @return LINKtag object.
 */
function html_link($href, $rel, $type ) {	
    return new LINKtag( array("href" => $href,
							  "rel" => $rel,
							  "type" => $type) );
}

/**
 * build a <map> tag with some content.
 *
 * @param	string - the name of the map.
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return MAPtag object.
 */
function html_map( $name ) {
    $tag = new MAPtag(array("name"=>$name) );
	$num_args = func_num_args();
	for ($i=1;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
    return $tag;
}

/**
 * build a <meta> tag..
 *
 * @param	string - the content value.
 * @param	string - the http-equiv value
 * @param   string - the name
 *
 * @return METAtag object.
 */
function html_meta( $content, $http_equiv="", $name="" ) {
	$attributes = array("content" => $content);

	if ($http_equiv != "") {
		$attributes["http-equiv"] = $http_equiv;
	}
	if ($name != "") {
		$attributes["name"] = $name;
	}

    $tag = new METAtag( $attributes );
    return $tag;
}


/**
 * build a <noframes> tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return NOFRAMEStag object.
 */
function html_noframes( ) {
    $tag = new NOFRAMEStag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <noscript> tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return NOSCRIPTtag object.
 */
function html_noscript( ) {
    $tag = new NOSCRIPTtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <object> tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return OBJECTtag object.
 */
function html_object( ) {
    $tag = new OBJECTtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <OL> tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return OLtag object.
 */
function html_ol( ) {
    $tag = new OLtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <OPTGROUP> tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return OPTGROUPtag object.
 */
function html_optgroup($label) {
    $tag = new OPTGROUPtag( array("label" => $label));
    $num_args = func_num_args();
	for ($i=1;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
    return $tag;
}

/**
 * build a <OPTION> tag with some content..
 *
 * @param string - the value attribute
 * @param string - the content for the tag.
 *
 * @return OPTIONtag object.
 */
function html_option($value, $content, $selected=FALSE) {
    $tag = new OPTIONtag( array("value"=> $value) );
    if ($selected) {
        if ($GLOBALS["HTML_RENDER_TYPE"] == HTML) {
            $tag->set_tag_attribute("SELECTED");
        } else {
            $tag->set_tag_attribute("selected", "selected");
        }
    }

    $tag->add( $content );
    return $tag;
}


/**
 * build a <p> tag.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return Ptag object.
 */
function html_p( ) {
    $tag = new Ptag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <param> tag.
 *
 * @param	string - name of the tag
 * @return PARAMtag object.
 */
function html_param($name, $value="") {
	$attributes = array("name" => $name);
	if ($value != "") {
		$attributes["value"] = $value;
	}
    return new PARAMtag( $attributes );
}

/**
 * build a <pre> tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return PREtag object.
 */
function html_pre( ) {
    $tag = new PREtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <q> tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return Qtag object.
 */
function html_q( ) {
    $tag = new Qtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <samp> tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return SAMPtag object.
 */
function html_samp( ) {
    $tag = new SAMPtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <script> tag with some content..
 *
 * @param	src    - the src
 * @param   string - type of script
 * @return SCRIPTtag object.
 */
function html_script($src="", $type="text/javascript") {
    $attributes = array("type" => $type);
    if ($src != "") {
        $attributes["src"] = $src;
    }
    return new SCRIPTtag( $attributes );
}

/**
 * <select> tag is defined in
 * form_utils.inc as
 * form_select()
 *
 */

/**
 * build a small <small> tag with content.
 *
 * @author Suren Markossian
 * @return SMALLtag object.
 */
function html_small() {
    $tag = new SMALLtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}


/**
 * build a bold <span> tag with content.
 *
 * @param   string - the class for the
 *                   span.
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return SPANtag object.
 */
function html_span($class="") {
    $tag = new SPANtag;
    if ($class != "") {
        $tag->set_class( $class );
    }
	$num_args = func_num_args();
	for ($i=1;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
    return $tag;
}


/**
 * build a <strong> tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return STRONGtag object.
 */
function html_strong( ) {
    $tag = new STRONGtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <style> tag with some content.
 *
 * @param   string - the type
 *                   text/css (DEFAULT),
 *                   text/javasript
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return STYLEtag object.
 */
function html_style($type="text/css") {
    $tag = new STYLEtag( array("type" => $type) );
	$num_args = func_num_args();
	for ($i=1;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
    return $tag;
}

/**
 * build a <sub> tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return SUBtag object.
 */
function html_sub( ) {
    $tag = new SUBtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <sup> tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return SUPtag object.
 */
function html_sup( ) {
    $tag = new SUPtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * Build a TABLEtag object
 * with some of the attributes set
 *
 * @param mixed - width attribute
 *                default: 100%
 * @param mixed - border
 *                default: 0
 * @param mixed - cellspacing
 *                default: 0
 * @param mixed - cellpadding
 *                default: 0
 * @param string - align the align
 *                 attribute
 *                default: not set.
 * @return TABLEtag object.
 */
function html_table( $width="100%", $border="0",
					 $cellspacing="0",
					 $cellpadding="0",
					 $align=NULL) {
    $attributes = array( "width" => $width,
						 "border" => $border,
						 "cellspacing" => $cellspacing,
						 "cellpadding" => $cellpadding);

    if ($align != NULL) {
		$attributes["align"] = $align;
    }
    return new TABLEtag( $attributes );
}

/**
 * build a <tbody> tag with some content..
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return TBODYtag object.
 */
function html_tbody( ) {
    $tag = new TBODYtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}



/**
 * build an td tag object with content.
 *
 * @param   string - the class to use
 * @param   string - the alignment
 *                   left, right
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return  TDtag object.
 */
function html_td($class="", $align="") {
	$attributes = array();
	if ($class != "") {
		$attributes["class"] = $class;
	}
	if ($align != "") {
		$attributes["align"] = $align;
	}

    $tag = new TDtag( $attributes );
	$num_args = func_num_args();
	for ($i=2;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
    return $tag;
}

/**
 * build a <tfoot> tag with content.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return TFOOTtag object.
 */
function html_tfoot( ) {
    $tag = new TFOOTtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}


/**
 * build a <th>$header</th> tag.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return THtag object.
 */
function html_th( ) {
    $tag = new THtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <thhead> tag.
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return THEADtag object.
 */
function html_thead( ) {
    $tag = new THEADtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}


/**
 * build a <title> tag with some content.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return TITLEtag object.
 */
function html_title( ) {
    $tag = new TITLEtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <tr> tag and contents
 *
 * @param   string - class
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return TRtag object.
 */
function html_tr( $class="" ) {
    $tag = new TRtag;

    if ($class != "") {
        $tag->set_class( $class );
    }

	$num_args = func_num_args();
	for ($i=1;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
    return $tag;
}

/**
 * build a <tt> tag and contents
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return TTtag object.
 */
function html_tt() {
    $tag = new TTtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <u> tag and contents
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return Utag object.
 */
function html_u( ) {
    $tag = new Utag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}


/**
 * build a <UL> tag with content
 * wrapped in an <LI> tag.
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return ULtag object.
 */
function html_ul( ) {
    $tag = new ULtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a <var> tag and contents
 *
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return VARtag object.
 */
function html_var( ) {
    $tag = new VARtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}


/**
 * build a <xmp> tag with some content..
 *
 * @author Walt A. Boring
 * @param   mixed - n number of arguments
 *                  as content for the tag.
 * @return XMPtag object.
 */
function html_xmp( ) {
    $tag = new XMPtag;
	$args = func_get_args();
    call_user_func_array( array(&$tag, "add"), $args);
    return $tag;
}

/**
 * build a mailto url link .
 *
 * @author Walt A. Boring
 * @param   string $email - the email address
 *                          for the mailto
 * @param	string $subject - the subject for
 *                            the email
 * @param	string $body - the body conent
 *						   for the email
 * @param	string $cc = the cc email address.
 * @return CENTERtag object.
 */
function mailto($email, $subject=NULL, $body=NULL, $cc=NULL){

	$mailto = "mailto:".$email."?";
	if ($subject) {
		$mailto .= "subject=".rawurlencode($subject);
	}
    if ($body) {
		$mailto .= "&body=".rawurlencode($body);
	}
    if ($cc) {
		$mailto .= "&cc=".rawurlencode($cc);
	}

    return html_a($mailto, $email);
}

?>
