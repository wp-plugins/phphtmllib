=== phpHtmlLib ===
Contributors: mpwalsh8
Donate link: http://sourceforge.net/project/project_donations.php?group_id=32790
Tags: HTML, Forms, XHTML, XML, Widgets
Requires at least: 3.1
Tested up to: 3.5.1
Stable tag: trunk

The phpHtmlLib library contains a set of PHP classes and library functions to help
facilitate building, debugging, and rendering of XML, HTML, XHTML, WAP/WML Documents,
and SVG (Scalable Vector Graphics) images as well as complex html Widgets.  These
classes, library functions and widgets can be used to build other WordPress plugins.

== Description ==

phpHtmllib is a set of PHP classes and library functions to help facilitate building, debugging,
and rendering of XML, HTML, XHTML, WAP/WML Documents, and SVG (Scalable Vector Graphics) images
as well as complex html 'widgets'.  It provides a mechanism to output perfectly indented/readable
tags, and a programmatic API to generating tags on the fly.


More information can be found on the [phpHtmlLib](http://michaelwalsh.org/wordpress/wordpress-plugins/phphtmllib/)
plugin page.

== Installation ==

1. Use the WordPress plugin installer from the Dashboard or Unzip and Upload the phpHtmlLib content to your /wp-content/plugins/ directory.
1. Activate the plugin through the 'Plugins' menu in WordPress.
1. Refer to the official plugin page for documentation, usage and tips.


== Frequently Asked Questions ==

1. What does the phpHtmlLib plugin do?  The plugin doesn't provide any new functionality within WordPress.  The plugin provides a library of Classes and Widgets that other plugins can build on top of.  In particular, phpHtmlLib has a very strong set of Classes for Form Processng which allows forms to be quickly created and processed with a consistent look and feel.
2. Do you plan to support phpHtmlLib 3. as a plugin?  No.  The phpHtmlLib 3.x thread was a complete re-write of phpHtmlLib for PHP5 and while it takes advantage of a lot of PHP5 functionality, the widget library isn't as robust.  The re-write also includes a complete MVC framework which is of no value as a WordPress plugin.  The 2.x thread is being maintained for the purposes of proving a WordPress plugin.

== Changelog ==

The [phpHtmlLib page](http://michaelwalsh.org/wordpress/wordpress-plugins/phphtmllib/) provides
full details on changes, bugs, enhancesments, future developments and much more and is the definitive
source for the Change Log.

= 2.6.6 =
* Fixed compatibility problem with PHP method_exists() function which caused PHP to crash with some versions of PHP 5.3.x on certain platforms (e.g. PHP 5.3.13 on Linux).

= 2.6.5 =
* Fixed recently added child constructors which addressed PHP5.3 compatibility issues so they play nice with PHP5.2.x as well.

= 2.6.4 =
* Added child constructors which are needed by some versions of PHP (e.g. 5.3.1) to allow proper constructor chain calling.  A missing constructor in the middle of a grandchild->child->parent class results in a PHP error in SOME PHP releases.

= 2.6.3 =
* Fixed numerous deprecated notices and warnings which result when running under PHP5.
* Fixed problem with missing image on Action Bar when displaying empty the action bar on an empty GUIDataList widget.

= 2.6.2 =
* First release under the WordPress plugin respository.
