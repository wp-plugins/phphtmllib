<?php

/**
 * This file contains all of the default
 * support html tags by phpHtmlLib.
 *
 * $Id: ALLTAGS.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 *
 */


/**
 * <A> tag class
 * @tutorial HTMLTagClass.cls#constructor
 * @package phpHtmlLib
 */
class Atag extends HTMLTagClass {
    var $_tag = "a";
    var $_debug_link_attributes = array("href");
    var $_htmlentities_attributes = array("href");

    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~_NEWLINEAFTEROPENTAG;
    }
} // Atag


/**
 * <ABBR> tag class
 * @package phpHtmlLib
 */
class ABBRtag extends HTMLTagClass {
    var $_tag = "abbr";
} // ABBRtag


/**
 * <ACRONYM> tag class
 * @package phpHtmlLib
 */
class ACRONYMtag extends HTMLTagClass {
    var $_tag = "acronym";
} // ACRONYMtag


/**
 * <ADDRESS> tag class
 * @package phpHtmlLib
 */
class ADDRESStag extends HTMLTagClass {
    var $_tag = "address";
} // ADDRESStag

/**
 * <APPLET> tag class
 * @package phpHtmlLib
 *
 * @deprecated
 */
class APPLETtag extends HTMLTagClass {
    var $_tag = "applet";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags |= _DEPRICATED;
    }
} // APPLETtag

/**
 * <AREA> tag class
 * @package phpHtmlLib
 */
class AREAtag extends HTMLTagClass {
    var $_tag = "area";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }
} // AREAtag


/**
 * <B> tag class
 * @package phpHtmlLib
 */
class Btag extends HTMLTagClass {
    var $_tag = "b";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~_NEWLINEAFTEROPENTAG;
    }
} // Btag


/**
 * <BASE> tag class
 * @package phpHtmlLib
 */
class BASEtag extends HTMLTagClass {
    var $_tag = "base";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }
} // BASEtag


/**
 * <BDO> tag class
 *
 * The bdo element overrides the default
 * text direction.
 *
 * REQUIRED ATTRIBUTE
 *  dir : url
 * @package phpHtmlLib
 *
 */
class BDOtag extends HTMLTagClass {
    var $_tag = "bdo";
} // BDOtag


/**
 * <BIG> tag class
 *
 * renders as 'bigger' text.
 * @package phpHtmlLib
 */
class BIGtag extends HTMLTagClass {
    var $_tag = "big";
} // BIGtag

/**
 * <BLOCKQUOTE> tag class
 *
 * This tag defines a long
 * quotation block
 *
 * @package phpHtmlLib
 */
class BLOCKQUOTEtag extends HTMLTagClass {
    var $_tag = "blockquote";
} // BLOCKQUOTEtag

/**
 * <BODY> tag class
 *
 * Defines the documents' body.
 *
 * OPTIONAL ATTRIBUTES (all depricated)
 *   alink => color : DEPRICATED
 *   background => filename : DEPRICATED
 *   bgcolor => color : DEPRICATED
 *   link => color : DEPRICATED
 * 	 text => color : DEPRICATED
 *   vlink => color : DEPRICATED
 *
 * @package phpHtmlLib
 */
class BODYtag extends HTMLTagClass {
    var $_tag = "body";
} // BODYtag


/**
 * <BR> tag class
 *
 * This tag inserts a single line break;
 *
 * @package phpHtmlLib
 */
class BRtag extends HTMLTagClass {
    var $_tag = "br";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }
} // BRtag


/**
 * <BUTTON> tag class
 *
 *  Defines a push button.
 *
 * @package phpHtmlLib
 */
class BUTTONtag extends HTMLTagClass {
    var $_tag = "button";
} // BUTTONtag


/**
 * <CAPTION> tag class
 *  This element defines a table caption.
 *  The <caption> tag must be inserted immediately
 *  after the <table> tag. You can specify only one
 *  caption per table.
 *
 * OPTIONAL ATTRIBUTES
 *  align  - top, bottom   DEPRICATED
 *
 * @package phpHtmlLib
 */
class CAPTIONtag extends HTMLTagClass {
    var $_tag = "caption";
} // CAPTIONtag


/**
 * <CENTER> tag class.
 * this is a depricated html tag, but
 * browsers still support it
 *
 * @deprecated
 * @package phpHtmlLib
 */
class CENTERtag extends HTMLTagClass {
    var $_tag = "center";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags |= _DEPRICATED;
    }
} // CENTERtag


/**
 * <CITE> tag class
 *
 * Defines a citation
 *
 * @package phpHtmlLib
 */
class CITEtag extends HTMLTagClass {
    var $_tag = "cite";
} // CITEtag


/**
 * <CODE> tag class
 *
 * Defines computer code text.
 *
 * @package phpHtmlLib
 */
class CODEtag extends HTMLTagClass {
    var $_tag = "code";
} // CODEtag


/**
 * <COL> tag class
 *
 *  Defines the attribute values for
 *  one or more columns in a table. You
 *  can only use this element inside a
 *  colgroup.
 *
 * @package phpHtmlLib
 */
class COLtag extends HTMLTagClass {
    var $_tag = "col";
} // COLtag


/**
 * <COLGROUP> tag class
 *
 * Defines groups of table columns.
 *  This element is only valid
 * inside the <table> tag.
 *
 * NOTE: The colgroup element is an empty
 *       element that contains attributes
 *       only. To create columns, you must
 *       specify td elements within a tr
 *       element.
 *
 * @package phpHtmlLib
 */
class COLGROUPtag extends HTMLTagClass {
    var $_tag = "colgroup";
} // COLGROUPtag



/**
 * <DD> tag class
 *
 *  The <dd> tag defines the description
 *  of the term in a definition list.
 *
 * @package phpHtmlLib
 */
class DDtag extends HTMLTagClass {
    var $_tag = "dd";
} // DDtag


/**
 * <DEL> tag class
 *
 * Defines text that has been deleted in
 * a document.
 *
 * @package phpHtmlLib
 */
class DELtag extends HTMLTagClass {
    var $_tag = "del";
} // DELtag

/**
 * <DFN> tag class
 *
 *  Defines a definition term
 *
 * @package phpHtmlLib
 */
class DFNtag extends HTMLTagClass {
    var $_tag = "dfn";
} // DFNtag


/**
 * <DIV> tag class
 *
 * The <div> tag defines the start of a
 * division/section in a document.
 *
 * NOTE: Browsers usually place a line break
 *       before the <div> tag.
 *
 * @package phpHtmlLib
 */
class DIVtag extends HTMLTagClass {
    var $_tag = "div";
} // DIVtag


/**
 * <DL> tag class
 *
 * The <dl> tag defines the start of a
 * definition list.
 *
 * @package phpHtmlLib
 */
class DLtag extends HTMLTagClass {
    var $_tag = "dl";
} // DLtag

/**
 * <!DOCTYPE> tag class
 * @package phpHtmlLib
 */
class DOCTYPEtag extends HTMLTagClass {
    var $_tag = "!DOCTYPE";

    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
        $this->_flags |= _ALWAYS_UPPERCASE | _NOFINISHSLASHXHTML;
    }
} //!DOCTYPEtag

/**
 * <DT> tag class
 *
 * The <dt> tag defines the start of a
 * definition list.
 *
 * @package phpHtmlLib
 */
class DTtag extends HTMLTagClass {
    var $_tag = "dt";
} // DLtag


/**
 * <EM> tag class
 *
 *  Renders as emphasized text
 *
 * @package phpHtmlLib
 */
class EMtag extends HTMLTagClass {
    var $_tag = "em";
} // EMtag


/**
 * <FIELDSET> tag class
 *
 *  The fieldset element draws a box
 *  around the text and other elements
 *  it contains.
 *
 * @package phpHtmlLib
 */
class FIELDSETtag extends HTMLTagClass {
    var $_tag = "fieldset";
} // FIELDSETtag



/**
 * <FONT> tag class
 *
 * @deprecated use styles instead
 *
 * @package phpHtmlLib
 */
class FONTtag extends HTMLTagClass {
    var $_tag = "font";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags |= _DEPRICATED;
    }
} // FONTtag



/**
 * FORMtag  <FORM> tag
 *
 * The form element creates a form
 * for user input.
 *
 * REQUIRED ATTRIBUTES
 *   action : url
 *            Specifies where to send the
 *            data when the user pushes the
 *            submit button in a form.
 *
 * @package phpHtmlLib
 */
class FORMtag extends HTMLTagClass {
    var $_tag = "form";
    var $_xhtml_strict_attributes = array("name", "target");
} // FORMtag



/**
 * <FRAME> tag class
 *
 * Defines a sub window (a frame).
 *
 * @package phpHtmlLib
 */
class FRAMEtag extends HTMLTagClass {
    var $_tag = "frame";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }
} // FRAMEtag

/**
 * <FRAMESET> tag class
 *
 * The frameset element defines a
 * frameset.
 *
 * @package phpHtmlLib
 */
class FRAMESETtag extends HTMLTagClass {
    var $_tag = "frameset";
} // FRAMESETtag


/**
 * <H1> tag class
 *
 * Defines a header
 *
 * @package phpHtmlLib
 */
class H1tag extends HTMLTagClass {
    var $_tag = "h1";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~_NEWLINEAFTEROPENTAG;
    }
} // H1tag


/**
 * <H2> tag class
 *
 * Defines a header
 *
 * @package phpHtmlLib
 */
class H2tag extends HTMLTagClass {
    var $_tag = "h2";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~_NEWLINEAFTEROPENTAG;
    }
} // H2tag


/**
 * <H3> tag class
 *
 * Defines a header
 *
 * @package phpHtmlLib
 */
class H3tag extends HTMLTagClass {
    var $_tag = "h3";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~_NEWLINEAFTEROPENTAG;
    }
} // H3tag


/**
 * <H4> tag class
 *
 * Defines a header
 *
 * @package phpHtmlLib
 */
class H4tag extends HTMLTagClass {
    var $_tag = "h4";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~_NEWLINEAFTEROPENTAG;
    }
} // H4tag


/**
 * <H5> tag class
 *
 * Defines a header
 *
 * @package phpHtmlLib
 */
class H5tag extends HTMLTagClass {
    var $_tag = "h5";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~_NEWLINEAFTEROPENTAG;
    }
} // H5tag


/**
 * <H6> tag class
 *
 * Defines a header
 *
 * @package phpHtmlLib
 */
class H6tag extends HTMLTagClass {
    var $_tag = "h6";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~_NEWLINEAFTEROPENTAG;
    }
} //H6tag


/**
 *  <HEAD> tag class
 *
 * The head element can contain information
 * about the document.
 *
 * @package phpHtmlLib
 */
class HEADtag extends HTMLTagClass {
    var $_tag = "head";
} // HEADtag



/**
 * <HR> tag class
 *
 * inserts a horizontal rule.
 *
 * NOTE: All the "presentation attributes"
 *       of the hr element have been
 *       deprecated, in favor of style sheets.
 *
 * @package phpHtmlLib
 */
class HRtag extends HTMLTagClass {
    var $_tag = "hr";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_NEWLINEAFTEROPENTAG | _CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }
} // HRtag



/**
 * <HTML> tag class.
 *
 * @package phpHtmlLib
 */
class HTMLtag extends HTMLTagClass {
    var $_tag = "html";
} // HTMLtag


/**
 * <I> tag class
 *
 * Renders as italic text
 *
 * @package phpHtmlLib
 */
class Itag extends HTMLTagClass {
    var $_tag = "i";
} // Itag


/**
 * <IFRAME> tag class
 *
 * The iframe element creates an inline
 * frame that contains another document.
 *
 * @package phpHtmlLib
 */
class IFRAMEtag extends HTMLTagClass {
    var $_tag = "iframe";
} // IFRAMEtag


/**
 * <IMG> tag class
 *
 * This element inserts an image.
 *
 * REQUIRED ATTRIBUTES
 *  src : url
 *        The address of the image you want
 *        to insert
 *  alt : text
 *        A short description of the image.
 *        Use it for text-only browsers
 *
 * @package phpHtmlLib
 */
class IMGtag extends HTMLTagClass {
    var $_tag = "img";
    var $_debug_link_attributes = array("src");
    var $_xhtml_strict_attributes = array("border");
    var $_htmlentities_attributes = array("src");
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }

} // IMGtag

/**
 * INPUTtag     <INPUT> tag
 *
 * The <input> tag defines the start of an input
 * field where the user can enter data.
 *
 * @package phpHtmlLib
 */
class INPUTtag extends HTMLTagClass {
    var $_tag = "input";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }


    /**
     * add a single attribute (name="value")
     *
     * We override this to prevent the value from
     * being injected javascript.
     *
     * {@source }
     *
     * @param   string  $name   attribute name
     * @param   mixed   $value  the value.
     * @return none
     */
    function set_tag_attribute( $name, $value=NULL ) {
        if (stristr('value', $name)) {
            $value = htmlspecialchars($value, ENT_QUOTES);
        }
        $this->_attributes[$name] = $value;
    }

    /**
     * add multiple attributes (name="value")
     *
     * We override this to prevent the value from
     * being injected javascript.
     *
     * {@source }
     *
     * @param   array   $attributes Associative array of name="value" pairs of
     *                              tag atributes.
     *                              ie array("border"=>"0", "class"=>"hover");
     * @return none
     */
    function set_tag_attributes( $attributes=array() ) {
        if (isset($attributes['value'])) {
            $attributes['value'] = htmlspecialchars($attributes['value'], ENT_QUOTES);
        }
        $this->_attributes = array_merge($this->_attributes, $attributes);
    }

} // INPUTtag

/**
 * <INS> tag class
 *
 * Defines inserted text.
 *
 * @package phpHtmlLib
 */
class INStag extends HTMLTagClass {
    var $_tag = "ins";
} // INStag

/**
 * <KBD> tag class
 *
 * Defines keyboard text
 *
 * @package phpHtmlLib
 */
class KBDtag extends HTMLTagClass {
    var $_tag = "kbd";
} // KBDtag


/**
 * <LABEL> tag class
 *
 * Defines a label to a control. If you
 * click the text within the label element,
 * it is supposed to toggle the control.
 *
 * NOTE: The "for" attribute binds a label
 *       to another element. Set the value
 *       of the "for" attribute equal to the
 *       value of the "id" attribute of the
 *       related element.
 *
 * @package phpHtmlLib
 */
class LABELtag extends HTMLTagClass {
    var $_tag = "label";
} // LABELtag


/**
 * <LEGEND> tag class
 *
 * The legend element defines a caption
 * for a fieldset.
 *
 * @package phpHtmlLib
 */
class LEGENDtag extends HTMLTagClass {
    var $_tag = "legend";
} // LEGENDtag


/**
 * <LI> tag class
 *
 * The <li> tag defines the start of a list
 * item. The <li> tag is used in both ordered
 * (<ol>) and unordered lists (<ul>).
 *
 * OPTIONAL ATTRIBUTES
 *   type : 1, A, a, I, i  DEPRICATED
 *
 * @package phpHtmlLib
 */
class LItag extends HTMLTagClass {
    var $_tag = "li";
} // LItag



/**
 * <LINK> tag class
 *
 * This element defines the relationship between
 * two linked documents.
 *
 * NOTE:  This element goes only in the head section,
 *        but it can appear any number of times.
 *
 * @package phpHtmlLib
 */
class LINKtag extends HTMLTagClass {
    var $_tag = "link";
    var $_debug_link_attributes = array("href");
    var $_htmlentities_attributes = array("href");
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }
} // LINKtag



/**
 * <MAP> tag class
 *
 *  Defines an image map. An image map is an
 *  image with clickable regions.
 *
 * @package phpHtmlLib
 */
class MAPtag extends HTMLTagClass {
    var $_tag = "map";
} // MAPtag

/**
 * <META> tag class
 *
 * The <meta> element provides meta-information
 * about your page, such as descriptions and
 * keywords for search engines.
 *
 * NOTE: The <meta> tag always goes inside the head element.
 *
 * REQUIRED ATTRIBUTES
 *  content : text
 *            Sets meta information to be associated
 *            with http-equiv or name.
 *
 * @package phpHtmlLib
 */
class METAtag extends HTMLTagClass {
    var $_tag = "meta";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }
} // METAtag


/**
 * <NOBR> tag class
 *
 * NOTE: This tag doesn't really
 *       exist in the HTML spec
 *       NOT WISE TO USE IT.
 * @deprecated
 * @package phpHtmlLib
 */
class NOBRtag extends HTMLTagClass {
    var $_tag = "nobr";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags |= _DEPRICATED;
    }
} // NOBRtag


/**
 * <NOFRAMES> tag class
 *
 *  The noframes element displays text for
 *  browsers that do not handle frames. The
 *  noframes element goes inside the frameset
 *  element.
 *
 * @package phpHtmlLib
 */
class NOFRAMEStag extends HTMLTagClass {
    var $_tag = "noframes";
} // NOFRAMEtag



/**
 * <NOSCRIPT> tag class
 *
 *  The noscript element is used to define
 *  an alternate content (text) if a script
 *  is NOT executed.
 *
 *  NO ATTRIBUTES
 *
 * @package phpHtmlLib
 */
class NOSCRIPTtag extends HTMLTagClass {
    var $_tag = "noscript";
} // NOSCRIPTtag

/**
 * <OBJECT> tag class
 *
 * Defines an embedded object. Use this element
 * to insert  multimedia into your page.
 *
 * @package phpHtmlLib
 */
class OBJECTtag extends HTMLTagClass {
    var $_tag = "object";
} // OBJECTtag

/**
 * <OL> tag class
 *
 * The <ol> tag defines the start of an ordered list.
 *
 * OPTIONAL ATTRIBUTES
 *   type : 1,A,a,I,i  DEPRICATED DO NOT USE
 *
 * @package phpHtmlLib
 */
class OLtag extends HTMLTagClass {
    var $_tag = "ol";
    /**
     * add content onto content stack
     * adds content to tag as a FIFO.
     * You can have n number of parameters.
     * each one will get added in succession to the content.
     *
     * we override this from the parent so we can auto detect if
     * the user is adding raw strings instead of objects.
     * If they are trying to add raw strings, then we wrap that in
     * an LItag object, since you can't add anything other then an <LI>
     * @param   mixed   $content - either string, or tag object.
     * @access  public
     */
    function add() {
        $args = func_get_args();

        foreach( $args as $content) {
			
            if (!is_object($content) || (@$content->_tag != "li") ) {
                //$content is raw (string)
                //lets wrap it in a <LI> object
                $li = new LItag;
                $li->add( $content );
                HTMLTagClass::add( $li );
            } else {
                //looks like this is some object
                //let the user do it.
                //should we only let them push a
                //<LI> object?
                HTMLTagClass::add( $content );
            }
        }
    }

    /**
     * push content onto content stack
     * adds content to tag as a FIFO
     * You can only add 1 element at a time, and
     * it will be added as a reference.  So you can't do
     * push_reference("something");, since "something" is a
     * static.
     *
     * we override this from the parent so we can auto detect if
     * the user is adding raw strings instead of objects.
     * If they are trying to add raw strings, then we wrap that in
     * an LItag object, since you can't add anything other then an <LI>
     * @param   mixed   $content - either string, or tag object.
     *                             the tag object gets stored as a
     *                             reference to the original, so you
     *                             can push it, then modify it later.
     * @access  public
     */
    function add_reference( &$content ) {
        if (!is_object($content) || (@$content->_tag != "li") ) {
            //$content is raw (string)
            //lets wrap it in a <LI> object
            $li = new LItag;
            $li->add_reference( $content );
            HTMLTagClass::add_reference( $li );
        } else {
            //looks like this is some object
            //let the user do it.
            //should we only let them push a
            //<LI> object?
            HTMLTagClass::add_reference( $content );
        }
    }
} // OLtag


/**
 * <OPTGROUP> tag class
 *
 *  Defines an option group. This element allows
 *  you to group choices. When you have a long list
 *  of options, groups of related choices are easier
 *  to handle.
 *
 * @package phpHtmlLib
 */
class OPTGROUPtag extends HTMLTagClass {
    var $_tag = "optgroup";
} // OPTGROUPtag


/**
 * <OPTION> tag class
 *
 *  The option element defines an option in the
 *  drop-down box.
 *
 * @package phpHtmlLib
 */
class OPTIONtag extends HTMLTagClass {
    var $_tag = "option";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~_NEWLINEAFTEROPENTAG;
    }

} // OPTIONtag



/**
 * <P> tag class
 *
 * The <p> tag defines a paragraph.
 *
 * OPTIONAL ATTRIBUTES
 *  align : left, center, right DEPRICATED DO NOT USE
 *
 * @package phpHtmlLib
 */
class Ptag extends HTMLTagClass {
    var $_tag = "p";
} // Ptag


/**
 * <PARAM> tag class
 *
 *  The param element allows you to specify
 *  the run-time settings for an object inserted
 *  into HTML documents.
 *
 *  REQUIRED ATTRIBUTES
 *   name : the name of the param
 *
 * @package phpHtmlLib
 */
class PARAMtag extends HTMLTagClass {
    var $_tag = "param";
} // PARAMtag

/**
 * <PRE> tag class
 *
 * The pre element defines preformatted text.
 * The text enclosed in the pre element usually
 * preserves spaces and line breaks. The text
 * renders in a fixed-pitch font.
 *
 * @package phpHtmlLib
 */
class PREtag extends HTMLTagClass {
    var $_tag = "pre";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~_INDENT;
    }
} // PREtag



/**
 * <Q> tag class
 *
 *  The <q> tag defines the start of a short quotation.
 *
 *  NOTE: The q element does not render as anything
 *        special, you have to use styles to format
 *        the text.
 *
 * @package phpHtmlLib
 */
class Qtag extends HTMLTagClass {
    var $_tag = "q";
} // Qtag


/**
 * <S> tag class
 *
 * @deprecated USE <del> instead
 *
 * @package phpHtmlLib
 */
class Stag extends HTMLTagClass {
    var $_tag = "s";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags |= _DEPRICATED;
    }
} // Stag


/**
 * <SAMP> tag class
 *
 * Defines sample computer code.
 *
 * @package phpHtmlLib
 */
class SAMPtag extends HTMLTagClass {
    var $_tag = "samp";
} // SAMPtag


/**
 * <SCRIPT> tag class
 *
 * Defines a script, such as JavaScript.
 *
 * REQUIRED ATTRIBUTES
 *  type : text/ecmascript, text/javascript,
 *         text/jscript, text/vbscript,
 *         text/vbs, text/xml
 *         The MIME type of the script.
 *
 * OPTIONAL ATTRIBUTES
 *  language : javascript, livescript, vbscript
 *             other   DEPRICATED DO NOT USE
 *
 * @package phpHtmlLib
 */
class SCRIPTtag extends HTMLTagClass {
    var $_tag = "script";
    var $_debug_link_attributes = array("src");
    var $_htmlentities_attributes = array("src");
} // SCRIPTtag


/**
 * <SELECT> tag class
 *
 *  The select element creates a drop-down box.
 *
 * @package phpHtmlLib
 */
class SELECTtag extends HTMLTagClass {
    var $_tag = "select";
} // SELECTtag



/**
 * <SMALL> tag class
 *
 * Renders as smaller text
 *
 * @package phpHtmlLib
 */
class SMALLtag extends HTMLTagClass {
    var $_tag = "small";
} // SMALLtag


/**
 * <SPAN> tag class
 *
 * The <span> tag defines a section in a document.
 *
 * NOTE: Browsers do not place a line break before
 *       or after the <span> tag.
 *
 * @package phpHtmlLib
 */
class SPANtag extends HTMLTagClass {
    var $_tag = "span";
} // SPANtag


/**
 * <STRONG> tag class
 *
 * Renders as strong emphasized text
 * @package phpHtmlLib
 *
 */
class STRONGtag extends HTMLTagClass {
    var $_tag = "strong";
} // STRONGtag


/**
 * <STYLE> tag class
 *
 * Defines a style in a document. The style
 * element goes in the head section. If you
 * want to include a style sheet in your page,
 * you should define the style sheet externally,
 * and link to it using <link>.
 *
 * REQUIRED ATTRIBUTES
 *  type : text/css, text/javascript
 * @package phpHtmlLib
 */
class STYLEtag extends HTMLTagClass {
    var $_tag = "style";
} // STYLEtag


/**
 * <SUB> tag class
 *
 * defines a subscript text
 *
 * @package phpHtmlLib
 */
class SUBtag extends HTMLTagClass {
    var $_tag = "sub";
} // SUBtag


/**
 * <SUP> tag class
 *
 * defines a superscript text
 *
 * @package phpHtmlLib
 */
class SUPtag extends HTMLTagClass {
    var $_tag = "sup";
} // SUPtag


/**
 * <TABLE> tag class
 *
 * The <table> tag defines the start of a table.
 * Inside a table row you can put table headers,
 * table rows, and table cells.
 * @package phpHtmlLib
 *
 */
class TABLEtag extends HTMLTagClass {
    var $_tag = "table";


    /**
     * Holds the default attributes for all <tr>'s
     * @var array
     * @private
     */
    var $_default_row_attributes = array();

    /**
     * Holds the default attributes for all <td>'s
     * @var array
     * @private
     */
    var $_default_col_attributes = array();



    //****************************************************************
    // Table specific routines.
    //****************************************************************



    /**
     * push 1 row (tr) of content.
     * Content can be raw strings, or tag objects.
     * Can push 1 item, or multiple items in call.  Each item
     * will be its own td.  should call push() to push a
     * <TR> object, but we detect it here anyway.
     * This function does not save the content by reference.
     * It copies the content and pushes it into the table.
     * If you want to save a reference use push() instead.
     * @param   mixed    $args    The <td>'s to push for next row
     * @return  string
     * @public
     */

    function add_row() {
        $args = func_get_args();
        $tr = new TRtag( $this->_default_row_attributes );
        $tr->set_default_td_attributes( $this->_default_col_attributes );

        for ($x=0; $x <= func_num_args()-1; $x++) {
            if (is_object($args[$x])) {
                if (isset($args[$x]->_tag) && $args[$x]->_tag == "td") {
                    $tr->add( $args[$x] );
                } else if (isset($args[$x]->_tag) && $args[$x]->_tag == "tr") {
                    //the user is trying to use this
                    //to add a TR object.
                    if ($tr->count_content() >= 1) {
                        //there is already content in
                        //the current tr.  This is an
                        //error, since it doesn't make
                        //sense to add data and a row
                        //inside a row.
                        return -1;
                    } else {
                        //user is using this to add
                        //a row. We'll only add it then
                        //bail.
                        $tr = $args[$x];
                        break;
                    }
                } else {
                    //we need to wrap this in its own td.
                    $tr->add( $args[$x] );
                }
            } else {
                //user is adding raw string.
                //lets wrap it in a <tr><td>content</td></tr>
                $tr->add( $args[$x] );
            }

        }
        $this->add( $tr );
    }

    /**
     * Same ass add_row()
     *
     *  NOTE: only exists for compatibility with 1.x
     *
     * @deprecated - use add()
     */
    function push_row( ) {
        $args = func_get_args();
        call_user_func_array( array(&$this, "add_row"), $args);
    }

    /**
     * Sets the default attributes for <tr>'s
     * that are added to the table.  If there are
     * any attributes set for the <tr> it won't use
     * the defaults.
     *
     * {@source }
     * @param array $attributes - the default attributes
     * @return none
     */
    function set_default_row_attributes( $attributes ) {

        $this->_default_row_attributes = $attributes;
    }

    /**
     * Sets the default attributes for <td>'s
     * that are added to the table.  If there are
     * any attributes set for the <td> it won't use
     * the defaults.
     *
     * {@source }
     * @param array $attributes - the default attributes
     * @return none
     */
    function set_default_col_attributes( $attributes ) {

        $this->_default_col_attributes = $attributes;
    }



    /**
     * update the attributes of a particular element or td.
     *
     * {@source }
     * @param int $row    row # of the table to edit
     * @param int $col    column # of the table to edit
     * @param array   $attributes array of name=>value pairs
     * @return none
     */
    function set_cell_attributes( $row, $col, $attributes=array() ) {

        if (is_object($this->_content[$row])) {
            if (is_object($this->_content[$row]->_content[$col])) {
                $this->_content[$row]->_content[$col]->set_tag_attributes( $attributes);
            }
        }
    }

    /**
     * update the attributes of a particular row or tr.
     *
     * {@source }
     * @param int $row    row # of the table to edit
     * @param int $col    column # of the table to edit
     * @param array   $attributes array of name=>value pairs
     * @return mixed -1 if the row doesn't exist already
     */
    function set_row_attributes( $row, $attributes ) {
        if ($this->_content[$row]) {
            $this->_content[$row]->set_tag_attributes( $attributes );
        } else {
            return -1;
        }
    }

    /**
     * This method sets/resets the content for a specific
     * cell in the table
     *
     * {@source }
     * @param int the row number
     * @param int the column number
     * @param mixed the cell content
     * @return mixed -1 if the cell doesn't exist already
     */
    function set_cell_content( $row, $col, $content) {

        $item = &$this->_get_element($row);
        if ( is_object($item) ) {
            $item = &$item->_get_element($col);
            if (is_object($item)) {
                $item->reset_content( $content );
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    }

    /**
     * This method is used to set a summary
     * attribute on the table for speech-synthesizing
     * non-visual browsers
     *
     * {@source }
     * @param string the summary
     * @return none
     */
    function set_summary($summary) {
        $this->set_tag_attribute("summary", $summary);
    }

} // TABLEtag

/**
 * <TBODY> class.
 *
 * Defines a table body.
 *
 * @package phpHtmlLib
 */
class TBODYtag extends TABLEtag {

    /**
     * Tag definition for class.
     * @var  string
     * @private
     */
    var $_tag = "tbody";

}// TBODYtag




/**
 * <TEXTAREA> tag class
 *
 * Defines a text-area (a multi-line text
 *  input control).
 *  The default font in the text-area is fixed pitch.
 *
 * REQUIRED ATTRIBUTES
 *  cols : number
 *         The width of the textarea, in characters.
 *
 *  rows : number
 *         The height of  the textarea, in rows
 *
 * OPTIONAL ATTRIBUTES
 *  wrap : soft, hard, off  DEPRICATED DO NOT USE
 *
 * @package phpHtmlLib
 */
class TEXTAREAtag extends HTMLTagClass {
    var $_tag = "textarea";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_INDENT | _NEWLINEAFTEROPENTAG);
    }
} // TEXTAREAtag



/**
 * <TFOOT> tag class
 *
 * @package phpHtmlLib
 */
class TFOOTtag extends TABLEtag {
    var $_tag = "tfoot";
} // TFOOTtag



/**
 * Table Header <TH> class.
 *
 * Defines a header cell in a table.
 * Very much the same as a data cell,
 * but rendered in bold and with a default
 * center alignment.
 *
 * OPTIONAL ATTRIBUTES
 * same as TDtag
 *
 * STANDARD ATTRIBUTES
 *  same as TDtag
 *
 * EVENT ATTRIBUTES
 *   same as TDtag
 *
 * @package phpHtmlLib
 */
class THtag extends HTMLTagClass {
    var $_tag = "th";

    /**
     * This is a helper for setting the colspan
     * attribute
     *
     * @param int - the colspan value
     */
    function set_colspan($colspan) {
        $this->set_tag_attribute('colspan', (int)$colspan);
    }

    /**
     * This is a helper for setting the rowspan
     * attribute
     *
     * @param int - the rowspan value
     */
    function set_rowspan($rowspan) {
        $this->set_tag_attribute('rowspan', (int)$rowspan);
    }
} // <TH>

/**
 * Table data <TD> class.
 *
 * Defines a cell in a table.
 *
 * OPTIONAL ATTRIBUTES
 *  bgcolor : color DEPRICATED DO NOT USE
 *  height : pixels, %  DEPRICATED DO NOT USE
 *  width : pixels, %  DEPRICATED
 *          use styles instead like this <td style="width:100px;">
 *
 * @package phpHtmlLib
 */
class TDtag extends THtag {
    var $_tag = "td";
}// TDtag

/**
 * Table Header <THEAD> class.
 *
 * defines a table header
 *
 * @package phpHtmlLib
 */
class THEADtag extends TABLEtag {
    var $_tag = "thead";
} // <TH>


/**
 * <TITLE> tag class
 *
 * @package phpHtmlLib
 */
class TITLEtag extends HTMLTagClass {
    var $_tag = "title";
} // TITLEtag


/**
 * Table Row <TR> class.
 * @package phpHtmlLib
 */
class TRtag extends HTMLTagClass {
    var $_tag = "tr";

    /**
     * Holds the default attributes for all <td>'s
     * @var array
     * @private
     */
    var $_default_td_attributes = array();

    //****************************************************************
    // TR specific routines.
    //****************************************************************

    /**
     * Sets the default attributes for <td>'s
     * that are added to the table.  If there are
     * any attributes set for the <td> it won't use
     * the defaults.
     *
     * @param array $attributes - the default attributes
     */
    function set_default_td_attributes( $attributes ) {
        $this->_default_td_attributes = $attributes;
    }

    /**
     * add content onto content stack
     * adds content to tag as a FIFO.
     * You can have n number of parameters.
     * each one will get added in succession to the content.
     *
     * we override this from the parent so we can auto detect if
     * the user is adding raw strings instead of objects.
     * If they are trying to add raw strings, then we wrap that in
     * a TDtag object, since you can't add anything other then a <TD> or
     * <TH> to a <TR>.
     * @param   mixed   $content - either string, or tag object.
     * @access  public
     */
    function add() {
        $args = func_get_args();

        foreach( $args as $content) {
            if (!is_object($content) || (@$content->_tag != "td" &&
                                         @$content->_tag != "th") ) {
                //$content is raw (string)
                //lets wrap it in a <td> object
                $td = new TDtag( $this->_default_td_attributes );
                $td->add( $content );
                HTMLTagClass::add( $td );
            } else {
                //looks like this is some object
                //let the user do it.
                //should we only let them add a
                //<TD> object?
                HTMLTagClass::add( $content );
            }
        }
    }

    /**
     * add content onto content stack
     * adds content to tag as a FIFO
     * You can only add 1 element at a time, and
     * it will be added as a reference.  So you can't do
     * add_reference("something");, since "something" is a
     * static.
     *
     * we override this from the parent so we can auto detect if
     * the user is adding raw strings instead of objects.
     * If they are trying to add raw strings, then we wrap that in
     * a TDtag object, since you can't add anything other then a <TD> or
     * <TH> to a <TR>.
     * @param   mixed   $content - either string, or tag object.
     *                             the tag object gets stored as a
     *                             reference to the original, so you
     *                             can add it, then modify it later.
     * @access  public
     */
    function add_reference( &$content ) {
        if (!is_object($content) || (@$content->_tag != "td" &&
                                     @$content->_tag != "th") ) {
            //$content is raw (string)
            //lets wrap it in a <td> object
            $td = new TDtag;
            $td->add_reference( $content );
            HTMLTagClass::add_reference( $td );
        } else {
            //looks like this is some object
            //let the user do it.
            //should we only let them add a
            //<TD> object?
            HTMLTagClass::add_reference( $content );
        }
    }

    /**
     * Same ass add()
     *
     *  NOTE: only exists for compatibility with 1.x
     *
     * @deprecated - use add()
     */
    function push() {
        $args = func_get_args();
        call_user_func_array( array(&$this, "add"), $args);
    }

    /**
     * Same ass add_reference()
     *
     *  NOTE: only exists for compatibility with 1.x
     *
     * @deprecated - use add()
     */
    function push_reference( &$content ) {
        $this->add_reference( $content );

    }

} // TRtag

/**
 * <TT> tag class
 * @package phpHtmlLib
 */
class TTtag extends HTMLTagClass {
    var $_tag = "tt";
} // TTtag

/**
 * <U> tag class
 * @package phpHtmlLib
 */
class Utag extends HTMLTagClass {
    var $_tag = "u";
} // Utag


/**
 * <UL> tag class
 * @package phpHtmlLib
 */
class ULtag extends OLtag {
    var $_tag = "ul";
} // ULtag

/**
 * <VAR> tag class
 * @package phpHtmlLib
 */
class VARtag extends HTMLTagClass {
    var $_tag = "var";
} // VARtag


/**
 * <XMP> tag class
 * @package phpHtmlLib
 */
class XMPtag extends HTMLTagClass {
    var $_tag = "xmp";
} // XMPtag

?>
