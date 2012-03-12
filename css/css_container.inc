<?php
/**
 * This file builds the CSSContainer object
 * that will hold all of the CSSBuilder objects
 * for all of the phpHtmlLib widgets.
 *
 * This enables you to create themes for you
 * own websites.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 *
 * @copyright LGPL - See LICENCE
 *
 */
$css_container = new CSSContainer;
$css_container->add( new FooterNavCSS(TRUE) );
$css_container->add( new InfoTableCSS );
$css_container->add( new NavTableCSS );
$css_container->add( new TextCSSNavCSS );
$css_container->add( new TextNavCSS );
$css_container->add( new VerticalCSSNavTableCSS );
$css_container->add( new ImageThumbnailWidgetCSS );
$css_container->add( new ActiveTabCSS );
$css_container->add( new RoundTitleTableCSS );
$css_container->add( new ButtonPanelCSS );
$css_container->add( new TabListCSS );
$css_container->add( new TabControlCSS );
$css_container->add( new ErrorBoxWidgetCSS );
$css_container->add( new ProgressWidgetCSS );
?>
