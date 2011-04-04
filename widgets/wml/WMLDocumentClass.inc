<?php

/**
 * This contains the WMLDocumentClass
 *
 * $Id: WMLDocumentClass.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */


/**
 *
 * This class lets you build a complete
 * WML document and render it
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib 
 */
class WMLDocumentClass extends XMLDocumentClass {

	function WMLDocumentClass() {
		$this->set_doctype_source("PUBLIC");
		XMLDocumentClass::XMLDocumentClass("wml",
										   "-//WAPFORUM//DTD WML 1.1//EN");
		$this->set_doctype_link("http://www.wapforum.org/DTD/wml_1.1.xml");

		//by default we want to output the
		//http Content-type header
		$this->show_http_header(TRUE);

		//set the correct content-type
		$this->set_http_content_type( "text/vnd.wap.wml" );
	}
}
?>
