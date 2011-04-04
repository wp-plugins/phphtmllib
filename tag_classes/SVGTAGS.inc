<?php
/**
 * This file contains all of the default
 * support svg tags by phpHtmlLib.
 *
 * $Id: SVGTAGS.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @link http://phphtmllib.newsblob.com
 */

/**
 * This overrides the WMLTagClass to 
 * define some methods that set 
 * some commonly used SVG tag attributes.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * @link http://phphtmllib.newsblob.com 
 * @link http://www.w3.org/TR/SVG
 * @link http://www.w3.org/TR/SVG/eltindex.html
 */ 
class SVGTagClass extends XMLTagClass {

	/**
	 * The SVGTagClass constructor
	 *
	 * @param array - the tag's attributes
	 * @param mixed - any N number of params for
	 *                content for the tag
	 */
	function SVGTagClass( $attributes=array() ) {
		$this->set_tag_attributes( $attributes );
        $num_args = func_num_args();
        for ($i=1;$i<$num_args;$i++) {
            $this->add(func_get_arg($i));
        }
        $this->_set_flags();
	}

	/**
	 * Attributes common to ALL SVG tags
	 */

    /**
     * This function is a shorthand helper
     * to setting the id attribute on a
     * tag.
     *
     * @param string - the class value.
	 * @link http://www.w3.org/TR/SVG/struct.html#StdAttrs
     */
    function set_id( $value ) {
        $this->set_tag_attribute("id", $value);
    }

	/**
	 * This method is used for setting the
	 * SVG common tag attribute of
	 * xml:base
	 *
	 * @param string - the 'xml:base' attribute
	 * @link http://www.w3.org/TR/SVG/struct.html#StdAttrs
	 */
	function set_xmlbase( $xmlbase ) {
		$this->set_tag_attribute( "xml:base", $xmlbase );
	}

	/**
	 * some often used SVG tags attributes
	 */

	/**
	 * This method is used for setting the
	 * SVG common tag attribute of
	 * xml:lang
	 *
	 * @param string - the 'xml:lang' attribute
	 * @link http://www.w3.org/TR/SVG/struct.html#StdAttrs
	 */
	function set_xmllang( $xmllang ) {
		$this->set_tag_attribute( "xml:lang", $xmlbase );
	}

	/**
	 * This method is used for setting the
	 * SVG common tag attribute of
	 * xml:space
	 *
	 * @param string - the 'xml:space' attribute
	 * @link http://www.w3.org/TR/SVG/struct.html#StdAttrs
	 */
	function set_xmlspace( $xmlspace ) {
		$this->set_tag_attribute( "xml:space", $xmlbase );
	}

    /**
     * This function is a shorthand helper
     * to setting the 'class' attribute on a
     * tag.
     *
     * @param string - the class value.
     */
    function set_class( $value ) {
        $this->set_tag_attribute("class", $value);
    }

    /**
     * This function is a shorthand helper
     * to setting the 'style' attribute on a
     * tag.
     *
     * @param string - the class value.
     */
    function set_style( $value ) {
        $this->set_tag_attribute("style", $value);
    }

	/**
	 * This function is used to set the
	 * 'transform' attribute of a tag.
	 *
	 * @param string - the 'transform' attribute
	 */
	function set_transform( $value ) {
		$this->set_tag_attribute("transform", $value );
	}

	/**
	 * we override this method
	 * to automatically check to 
	 * see if the tag has content.
	 * if it doesn't then we
	 * don't need to render the
	 * close tag.
	 */
	function _prepare_flags() {
        if ($this->count_content() == 0) {
            $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
		}
	}
}

/**
 * <a> SVG tag
 * @link http://www.w3.org/TR/SVG/linking.html#AElement
 * @package phpHtmlLib
 */
class Asvgtag extends SVGTagClass {
	var $_tag = "a";
} // Asvgtag

/**
 * <altGlyph> SVG tag
 * @link http://www.w3.org/TR/SVG/text.html#AlternateGlyphs
 * @package phpHtmlLib
 */
class ALTGLYGHsvgtag extends SVGTagClass {
    var $_tag = "altGlyph";
} // ALTGLYGHsvgtag

/**
 * <altGlyphDef> SVG tag
 * @link http://www.w3.org/TR/SVG/text.html#AlternateGlyphs
 * @package phpHtmlLib
 */
class ALTGLYGHDEFsvgtag extends SVGTagClass {
    var $_tag = "altGlyphDef";
} // ALTGLYGHDEFsvgtag

/**
 * <altGlyphItem> SVG tag
 * @link http://www.w3.org/TR/SVG/text.html#AltGlyphItemElement
 * @package phpHtmlLib
 */
class ALTGLYGHITEMsvgtag extends SVGTagClass {
    var $_tag = "altGlyphItem";
} // ALTGLYGHITEMsvgtag

/**
 * <animate> SVG tag
 * @link http://www.w3.org/TR/SVG/animate.html#AnimateElement
 * @package phpHtmlLib
 */
class ANIMATEsvgtag extends SVGTagClass {
    var $_tag = "animate";
} // ANIMATEsvgtag

/**
 * <animateColor> SVG tag
 * @link http://www.w3.org/TR/SVG/animate.html#AnimateColorElement
 * @package phpHtmlLib
 */
class ANIMATECOLORsvgtag extends SVGTagClass {
    var $_tag = "animateColor";
} // ANIMATECOLORsvgtag

/**
 * <animateMotion> SVG tag
 * @link http://www.w3.org/TR/SVG/animate.html#AnimateMotionElement
 * @package phpHtmlLib
 */
class ANIMATEMOTIONsvgtag extends SVGTagClass {
    var $_tag = "animateMotion";
} // ANIMATEMOTIONsvgtag

/**
 * <animateTransform> SVG tag
 * @link http://www.w3.org/TR/SVG/animate.html#AnimateTransformElement
 * @package phpHtmlLib
 */
class ANIMATETTRANSFORMsvgtag extends SVGTagClass {
    var $_tag = "animateTransform";
} // ANIMATETTRANSFORMsvgtag

/**
 * <circle> SVG tag
 * @link http://www.w3.org/TR/SVG/shapes.html
 * @package phpHtmlLib
 */
class CIRCLEsvgtag extends SVGTagClass {
    var $_tag = "circle";
} // CIRCLEsvgtag

/**
 * <clipPath> SVG tag
 * @link http://www.w3.org/TR/SVG/masking.html#ClipPathElement
 * @package phpHtmlLib
 */
class CLIPPATHsvgtag extends SVGTagClass {
    var $_tag = "clipPath";
} // CLIPPATHsvgtag

/**
 * <color-profile> SVG tag
 * @link http://www.w3.org/TR/SVG/color.html#ColorProfileElement
 * @package phpHtmlLib
 */
class COLORPROFILEsvgtag extends SVGTagClass {
    var $_tag = "color-profile";
} // COLORPROFILEsvgtag

/**
 * <cursor> SVG tag
 * @link http://www.w3.org/TR/SVG/interact.html#CursorElement
 * @package phpHtmlLib
 */
class CURSORsvgtag extends SVGTagClass {
    var $_tag = "cursor";
} // CIRCLEsvgtag

/**
 * <defs> SVG tag
 * @link http://www.w3.org/TR/SVG/struct.html#DefsElement
 * @package phpHtmlLib
 */
class DEFSsvgtag extends SVGTagClass {
    var $_tag = "defs";
} // DEFSsvgtag

/**
 * <desc> SVG tag
 * @link http://www.w3.org/TR/SVG/struct.html#DefsElement
 * @package phpHtmlLib
 */
class DESCsvgtag extends SVGTagClass {
    var $_tag = "desc";
} // DESCsvgtag

/**
 * <definition-src> SVG tag
 * @link http://www.w3.org/TR/SVG/fonts.html#DefinitionSrcElement
 * @package phpHtmlLib
 */
class DEFINITIONSRCsvgtag extends SVGTagClass {
    var $_tag = "definition-src";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }
} // DEFINITIONSRCsvgtag

/**
 * <ellipse> SVG tag
 * @link http://www.w3.org/TR/SVG/shapes.html
 * @package phpHtmlLib
 */
class ELLIPSEsvgtag extends SVGTagClass {
    var $_tag = "ellipse";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }
} // ELLIPSEsvgtag

/**
 * <feBlend> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feBlendElement
 * @package phpHtmlLib
 */
class FEBLENDsvgtag extends SVGTagClass {
    var $_tag = "feBlend";
} // FEBLENDsvgtag

/**
 * <feColorMatrix> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feColorMatrixElement
 * @package phpHtmlLib
 */
class FECOLORMATRIXsvgtag extends SVGTagClass {
    var $_tag = "feColorMatrix";
} // FECOLORMATRIXsvgtag

/**
 * <feComponentTransfer> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feComponentTransferElement
 * @package phpHtmlLib
 */
class FECOMPONENTTANSFERsvgtag extends SVGTagClass {
    var $_tag = "feComponentTransfer";
} // FECOMPONENTTANSFERsvgtag

/**
 * <feComposite> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feCompositeElement
 * @package phpHtmlLib
 */
class FECOMPOSITEsvgtag extends SVGTagClass {
    var $_tag = "feComposite";
} // FECOMPOSITEsvgtag

/**
 * <feConvolveMatrix> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feConvolveMatrixElement
 * @package phpHtmlLib
 */
class FECONVOLVEMATRIXsvgtag extends SVGTagClass {
    var $_tag = "feConvolveMatrix";
} // FECONVOLVEMATRIXsvgtag

/**
 * <feDiffuseLighting> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feDiffuseLightingElement
 * @package phpHtmlLib
 */
class FEDIFFUSELIGHTINGsvgtag extends SVGTagClass {
    var $_tag = "feDiffuseLighting";
} // FEDIFFUSELIGHTINGsvgtag

/**
 * <feDisplacementMap> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feDisplacementMapElement
 * @package phpHtmlLib
 */
class FEDISPLACEMENTMAPsvgtag extends SVGTagClass {
    var $_tag = "feDisplacementMap";
} // FEDISPLACEMENTMAPsvgtag

/**
 * <feDistantLight> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feDistantLightElement
 * @package phpHtmlLib
 */
class FEDISTANTLIGHTsvgtag extends SVGTagClass {
    var $_tag = "feDistantLight";
} // FEDISTANTLIGHTsvgtag

/**
 * <feFlood> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feFloodElement
 * @package phpHtmlLib
 */
class FEFLOODsvgtag extends SVGTagClass {
    var $_tag = "feFlood";
} // FEFLOODsvgtag

/**
 * <feFuncA> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feFuncAElement
 * @package phpHtmlLib
 */
class FEFUNCAsvgtag extends SVGTagClass {
    var $_tag = "feFuncA";
} // FEFUNCAsvgtag

/**
 * <feFuncB> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feFuncBElement
 * @package phpHtmlLib
 */
class FEFUNCBsvgtag extends SVGTagClass {
    var $_tag = "feFuncB";
} // FEFUNCBsvgtag

/**
 * <feFuncG> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feFuncGElement
 * @package phpHtmlLib
 */
class FEFUNCGsvgtag extends SVGTagClass {
    var $_tag = "feFuncG";
} // FEFUNCGsvgtag

/**
 * <feFuncR> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feFuncRElement
 * @package phpHtmlLib
 */
class FEFUNCRsvgtag extends SVGTagClass {
    var $_tag = "feFuncR";
} // FEFUNCRsvgtag

/**
 * <feGaussianBlur> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feGaussianBlurElement
 * @package phpHtmlLib
 */
class FEGAUSSIANBLURsvgtag extends SVGTagClass {
    var $_tag = "feGaussianBlur";
} // FEGAUSSIANBLURsvgtag

/**
 * <feImage> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feImageElement
 * @package phpHtmlLib
 */
class FEIMAGEsvgtag extends SVGTagClass {
    var $_tag = "feImage";
} // FEIMAGEsvgtag

/**
 * <feMerge> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feMergeElement
 * @package phpHtmlLib
 */
class FEMERGEsvgtag extends SVGTagClass {
    var $_tag = "feMerge";
} // FEMERGEsvgtag

/**
 * <feMergeNode> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feMergeNodeElement
 * @package phpHtmlLib
 */
class FEMERGENODEsvgtag extends SVGTagClass {
    var $_tag = "feMergeNode";
} // FEMERGENODEsvgtag

/**
 * <feMorphology> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feMorphologyElement
 * @package phpHtmlLib
 */
class FEMORPHOLOGYsvgtag extends SVGTagClass {
    var $_tag = "feMorphology";
} // FEMORPHOLOGYsvgtag

/**
 * <feOffset> SVG svgtag
 * @link http://www.w3.org/TR/SVG/filters.html#feOffsetElement
 * @package phpHtmlLib
 */
class FEOFFSETsvgtag extends SVGTagClass {
    var $_tag = "feOffset";
} // FEOFFSETsvgtag

/**
 * <fePointLight> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#fePointLightElement
 * @package phpHtmlLib
 */
class FEPOINTLIGHTsvgtag extends SVGTagClass {
    var $_tag = "fePointLight";
} // FEPOINTLIGHTsvgtag

/**
 * <feSpecularLighting> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feSpecularLightingElement
 * @package phpHtmlLib
 */
class FESPECTACULARLIGHTINGsvgtag extends SVGTagClass {
    var $_tag = "feSpecularLighting";
} // FESPECTACULARLIGHTINGsvgtag

/**
 * <feSpotLight> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feSpotLightElement
 * @package phpHtmlLib
 */
class FESPOTLIGHTsvgtag extends SVGTagClass {
    var $_tag = "feSpotLight";
} // FESPOTLIGHTsvgtag

/**
 * <feTile> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feTileElement
 * @package phpHtmlLib
 */
class FETILEsvgtag extends SVGTagClass {
    var $_tag = "feTile";
} // FETILEsvgtag

/**
 * <feTurbulence> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#feTurbulenceElement
 * @package phpHtmlLib
 */
class FETURBULENCEsvgtag extends SVGTagClass {
    var $_tag = "feTurbulence";
} // FETURBULENCEsvgtag

/**
 * <filter> SVG tag
 * @link http://www.w3.org/TR/SVG/filters.html#FilterElement
 * @package phpHtmlLib
 */
class FILTERsvgtag extends SVGTagClass {
    var $_tag = "filter";
} // FILTERsvgtag

/**
 * <font> SVG tag
 * @link http://www.w3.org/TR/SVG/fonts.html#FontElement
 * @package phpHtmlLib
 */
class FONTsvgtag extends SVGTagClass {
    var $_tag = "font";
} // FONTsvgtag

/**
 * <font-face> SVG tag
 * @link http://www.w3.org/TR/SVG/fonts.html#FontFaceElement
 * @package phpHtmlLib
 */
class FONTFACEsvgtag extends SVGTagClass {
    var $_tag = "font-face";
} // FONTFACEsvgtag

/**
 * <font-face-format> SVG tag
 * @link http://www.w3.org/TR/SVG/fonts.html#FontFaceNameElement
 * @package phpHtmlLib
 */
class FONTFACEFORMATsvgtag extends SVGTagClass {
    var $_tag = "font-face-format";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }
} // FONTFACEFORMATsvgtag

/**
 * <font-face-name> SVG tag
 * @link http://www.w3.org/TR/SVG/fonts.html#FontFaceNameElement
 * @package phpHtmlLib
 */
class FONTFACENAMEsvgtag extends SVGTagClass {
    var $_tag = "font-face-name";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }
} // FONTFACEFORMATsvgtag

/**
 * <font-face-src> SVG tag
 * @link http://www.w3.org/TR/SVG/fonts.html#FontFaceSrcElement
 * @package phpHtmlLib
 */
class FONTFACESRCsvgtag extends SVGTagClass {
    var $_tag = "font-face-src";
} // FONTFACESRCsvgtag

/**
 * <font-face-uri> SVG tag
 * @link http://www.w3.org/TR/SVG/fonts.html#FontFaceNameElement
 * @package phpHtmlLib
 */
class FONTFACEURIsvgtag extends SVGTagClass {
    var $_tag = "font-face-uri";
} // FONTFACEURIsvgtag

/**
 * <foreignObject> SVG tag
 * @link http://www.w3.org/TR/SVG/extend.html#ForeignObjectElement
 * @package phpHtmlLib
 */
class FOREIGNOBJECTsvgtag extends SVGTagClass {
    var $_tag = "foreignObject";
} // FOREIGNOBJECTsvgtag

/**
 * <g> SVG tag
 * @link http://www.w3.org/TR/SVG/struct.html#GElement
 * @package phpHtmlLib
 */
class Gsvgtag extends SVGTagClass {
    var $_tag = "g";
} // Gsvgtag

/**
 * <glyph> SVG tag
 * @link http://www.w3.org/TR/SVG/fonts.html#GlyphElement
 * @package phpHtmlLib
 */
class GLYPHsvgtag extends SVGTagClass {
    var $_tag = "glyph";
} // GLYPHsvgtag

/**
 * <glyphRef> SVG tag
 * @link http://www.w3.org/TR/SVG/text.html#AlternateGlyphs
 * @package phpHtmlLib
 */
class GLYPHREFsvgtag extends SVGTagClass {
    var $_tag = "glyphRef";
} // GLYPHREFsvgtag

/**
 * <hkern> SVG tag
 * @link http://www.w3.org/TR/SVG/fonts.html#HKernElement
 * @package phpHtmlLib
 */
class HKERNsvgtag extends SVGTagClass {
    var $_tag = "hkern";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }
} // HKERNsvgtag

/**
 * <image> SVG tag
 * @link http://www.w3.org/TR/SVG/struct.html#ImageElement
 * @package phpHtmlLib
 */
class IMAGEsvgtag extends SVGTagClass {
    var $_tag = "image";
} // IMAGEsvgtag

/**
 * <line> SVG tag
 * @link http://www.w3.org/TR/SVG/shapes.html
 * @package phpHtmlLib
 */
class LINEsvgtag extends SVGTagClass {
    var $_tag = "line";
} // LINEsvgtag

/**
 * <linearGradient> SVG tag
 * @link http://www.w3.org/TR/SVG/pservers.html#LinearGradientElement
 * @package phpHtmlLib
 */
class LINEARGRADIENTsvgtag extends SVGTagClass {
    var $_tag = "linearGradient";
} // LINEARGRADIENTsvgtag

/**
 * <maker> SVG tag
 * @link http://www.w3.org/TR/SVG/painting.html#MarkerElement
 * @package phpHtmlLib
 */
class MARKERsvgtag extends SVGTagClass {
    var $_tag = "marker";
} // MARKERsvgtag

/**
 * <mask> SVG tag
 * @link http://www.w3.org/TR/SVG/masking.html#MaskElement
 * @package phpHtmlLib
 */
class MASKsvgtag extends SVGTagClass {
    var $_tag = "mask";
} // MASKsvgtag

/**
 * <metadata> SVG tag
 * @link http://www.w3.org/TR/SVG/metadata.html#MetadataElement
 * @package phpHtmlLib
 */
class METADATAsvgtag extends SVGTagClass {
    var $_tag = "metadata";
} // METADATAsvgtag

/**
 * <missing-glyph> SVG tag
 * @link http://www.w3.org/TR/SVG/fonts.html#MissingGlyphElement
 * @package phpHtmlLib
 */
class MISSINGGLYPHsvgtag extends SVGTagClass {
    var $_tag = "missing-glyph";
} // MISSINGGLYPHsvgtag

/**
 * <mpath> SVG tag
 * @link http://www.w3.org/TR/SVG/animate.html#mpathElement
 * @package phpHtmlLib
 */
class MPATHsvgtag extends SVGTagClass {
    var $_tag = "mpath";
} // MPATHsvgtag

/**
 * <path> SVG tag
 * @link http://www.w3.org/TR/SVG/paths.html#PathElement
 * @package phpHtmlLib
 */
class PATHsvgtag extends SVGTagClass {
    var $_tag = "path";
} // PATHsvgtag

/**
 * <pattern> SVG tag
 * @link http://www.w3.org/TR/SVG/pservers.html#PatternElement
 * @package phpHtmlLib
 */
class PATTERNsvgtag extends SVGTagClass {
    var $_tag = "pattern";
} // PATTERNsvgtag

/**
 * <polygon> SVG tag
 * @link http://www.w3.org/TR/SVG/shapes.html#PolygonElement
 * @package phpHtmlLib
 */
class POLYGONsvgtag extends SVGTagClass {
    var $_tag = "polygon";
} // POLYGONsvgtag

/**
 * <polyline> SVG tag
 * @link http://www.w3.org/TR/SVG/shapes.html#PolylineElement
 * @package phpHtmlLib
 */
class POLYLINEsvgtag extends SVGTagClass {
    var $_tag = "polyline";
} // POLYLINEsvgtag

/**
 * <radialGradient> SVG tag
 * @link http://www.w3.org/TR/SVG/pservers.html#RadialGradientElement 
 * @package phpHtmlLib
 */
class RADIALGRADIENTsvgtag extends SVGTagClass {
    var $_tag = "radialGradient";
} // RADIALGRADIENTsvgtag

/**
 * <rect> SVG tag
 * @link http://www.w3.org/TR/SVG/shapes.html#RectElement
 * @package phpHtmlLib
 */
class RECTsvgtag extends SVGTagClass {
    var $_tag = "rect";
} // RECTsvgtag

/**
 * <script> SVG tag
 * @link http://www.w3.org/TR/SVG/script.html#ScriptElement
 * @package phpHtmlLib
 */
class SCRIPTsvgtag extends SVGTagClass {
	var $_tag = "script";
    function _set_flags() {
        HTMLTagClass::_set_flags();
        $this->_flags |= _CDATACONTENTWRAP;
    }
} // SCRIPTsvgtag

/**
 * <set> SVG tag
 * @link http://www.w3.org/TR/SVG/animate.html#SetElement
 * @package phpHtmlLib
 */
class SETsvgtag extends SVGTagClass {
	var $_tag = "set";
} // SETsvgtag

/**
 * <stop> SVG tag
 * @link http://www.w3.org/TR/SVG/pservers.html#StopElement
 * @package phpHtmlLib
 */
class STOPsvgtag extends SVGTagClass {
	var $_tag = "stop";
} // STOPsvgtag

/**
 * <style> SVG tag
 * @link http://www.w3.org/TR/SVG/styling.html#StyleElement
 * @package phpHtmlLib
 */
class STYLEsvgtag extends SVGTagClass {
	var $_tag = "style";
    function _set_flags() {
        HTMLTagClass::_set_flags();
        $this->_flags |= _CDATACONTENTWRAP;
    }
} // STYLEsvgtag

/**
 * <svg> SVG tag
 * @link http://www.w3.org/TR/SVG/struct.html#SVGElement
 * @package phpHtmlLib
 */
class SVGsvgtag extends SVGTagClass {
	var $_tag = "svg";
} // SVGsvgtag

/**
 * <switch> SVG tag
 * @link http://www.w3.org/TR/SVG/struct.html#SwitchElement 
 * @package phpHtmlLib
 */
class SWITCHsvgtag extends SVGTagClass {
	var $_tag = "switch";
} // SWITCHsvgtag

/**
 * <symbol> SVG tag
 * @link http://www.w3.org/TR/SVG/struct.html#SymbolElement
 * @package phpHtmlLib
 */
class SYMBOLsvgtag extends SVGTagClass {
	var $_tag = "symbol";
} // SYMBOLsvgtag

/**
 * <text> SVG tag
 * @link http://www.w3.org/TR/SVG/text.html
 * @package phpHtmlLib
 */
class TEXTsvgtag extends SVGTagClass {
    var $_tag = "text";
} // TEXTsvgtag

/**
 * <textpath> SVG tag
 * @link http://www.w3.org/TR/SVG/text.html#TextPathElement
 * @package phpHtmlLib
 */
class TEXTPATHsvgtag extends SVGTagClass {
    var $_tag = "text";
} // TEXTsvgtag

/**
 * <title> SVG tag
 * @link http://www.w3.org/TR/SVG/struct.html#TitleElement
 * @package phpHtmlLib
 */
class TITLEsvgtag extends SVGTagClass {
    var $_tag = "title";
} // TITLEsvgtag

/**
 * <tref> SVG tag
 * @link http://www.w3.org/TR/SVG/text.html
 * @package phpHtmlLib
 */
class TREFsvgtag extends SVGTagClass {
    var $_tag = "tref";
} // TEXTsvgtag

/**
 * <tspan> SVG tag
 * @link http://www.w3.org/TR/SVG/text.html
 * @package phpHtmlLib
 */
class TSPANsvgtag extends SVGTagClass {
    var $_tag = "tspan";
} // TEXTsvgtag

/**
 * <use> SVG tag
 * @link http://www.w3.org/TR/SVG/struct.html#UseElement
 * @package phpHtmlLib
 */
class USEsvgtag extends SVGTagClass {
    var $_tag = "use";
} // USEsvgtag

/**
 * <view> SVG tag
 * @link http://www.w3.org/TR/SVG/linking.html#ViewElement
 * @package phpHtmlLib
 */
class VIEWsvgtag extends SVGTagClass {
    var $_tag = "view";
} // VIEWsvgtag

/**
 * <vkern> SVG tag
 * @link 
 * @package phpHtmlLib
 */
class VKERNsvgtag extends SVGTagClass {
    var $_tag = "vkern";
    function _set_flags() {
        parent::_set_flags();
        $this->_flags &= ~(_CONTENTREQUIRED | _CLOSETAGREQUIRED);
    }
} // VKERNsvgtag
?>
