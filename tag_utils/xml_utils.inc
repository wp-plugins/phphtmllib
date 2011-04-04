<?php

/**
 * This file holds helper functions
 * for things related to XMLTagClass
 * objects/data
 *
 * $Id: xml_utils.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */
 


/**
 * This is a simple wrapper function
 * for building XMLTagClass objects
 * 
 * @tutorial XMLTagClass.cls#helper
 *
 * @param string - the xml tag name
 * @param array - the name="value" pairs of
 *                tag attributes
 * @param mixed - any content that lives in the
 *                PCDATA portion of the XML tag
 *
 * @return XMLTagClass object
 */
function &xml_tag($name, $attributes=array()) {
	$tag = new XMLTagClass($name, $attributes);
    $num_args = func_num_args();
	for ($i=2;$i<$num_args;$i++) {
		$tag->add(func_get_arg($i));
	}
	return $tag;
}

/**
 * This builds an xml tag, just as xml_tag() does,
 * but turns on the auto wrapping of CDATA for the
 * content for the tag.
 * 
 * @param string - the xml tag name
 * @param array - the name="value" pairs of
 *                tag attributes
 * @param mixed - any content that lives in the
 *                PCDATA portion of the XML tag
 *
 * @return XMLTagClass object
 */
function &xml_ctag($name, $attributes=array()) {
    $args = func_get_args();
    $tag =& call_user_func_array("xml_tag", $args);
    $tag->set_cdata_flag(TRUE);
    return $tag;
}


/**
 * This function is used to build a 
 * DOCTYPE tag 
 *
 * @param string - the document element name (ie. 'HTML')
 * @param string - the source (ie. 'PUBLIC')
 * @param string - link 1 (ie. '-//W3C//DTD XHTML 1.0 Transitional//EN' )
 * @param string - link 2 (ie. 'DTD/xhtml1-transitional.dtd' )
 *
 * @return DOCTYPEtag object
 */
function xml_doctype($doc_element, $source="PUBLIC", $link1=NULL, $link2=NULL) {

	$attributes = array($doc_element, $source);

	if ($link1 != NULL) {
		array_push($attributes,  "\"". $link1."\"");
	}

	if ($link2 != NULL) {
		array_push($attributes,  "\"". $link2."\"");
	}

	return new DOCTYPEtag( $attributes );
}

/**
 * This function is used to build an 
 * xml-stylesheet tag
 *
 * @param string - the href attribute
 * @param string - the type attribute
 *
 * @return XMLSTYLESHEETtag object
 */
function xml_stylesheet( $href, $type="text/css" ) {
	return new XMLSTYLESHEETtag( array("href" => $href,
									   "type" => $type));
}



/**
 * This function converts an array to 
 * an xml document.
 *
 * @param array
 * @param string
 */
function array_to_xml_tree( $arr ) {

	$xml = container();

	foreach( $arr as $name => $value) {
		if (is_array($value)) {
			$xml->push(xml_tag($name, array(), array_to_xml_tree( $value )));
		} else {
			$xml->push(xml_tag( $name, array(), $value ));
		}
	}
	return $xml;
}


?>
