<?php

/**
 * this file includes all of the widgets
 * that live in this dir.
 * If you add a new widget, you should add it here.
 *
 * $Id: includes.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */ 

/**
 * do the includes
 *
 * commented widgets are not really ready for 
 * prime time.
 *
 */
include_once(PHPHTMLLIB_ABSPATH . "/widgets/BaseWidget.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/ContainerWidget.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/CSSContainer.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/CSSBuilder.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/HTMLPageClass.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/HTMLRedirectPage.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/PageWidget.inc");


include_once(PHPHTMLLIB_ABSPATH . "/widgets/ActiveTab.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/ButtonPanel.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/DialogWidget.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/FooterNav.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/InfoTable.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/ImageThumbnailWidget.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/MessageBoxWidget.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/NavTable.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/RoundTitleTable.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/StandardDialogWidget.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/TabWidget.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/TextNav.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/TextCSSNav.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/VerticalCSSNavTable.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/TabControlWidget.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/ProgressWidget.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/ErrorBoxWidget.inc");


include_once(PHPHTMLLIB_ABSPATH . "/widgets/xml/XMLDocumentClass.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/wml/WMLDocumentClass.inc");
include_once(PHPHTMLLIB_ABSPATH . "/widgets/svg/SVGDocumentClass.inc");

//not fully baked
//include_once(PHPHTMLLIB_ABSPATH . "/widgets/TreeNav.inc");

?>
