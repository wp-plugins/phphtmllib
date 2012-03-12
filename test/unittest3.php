<?php
/**
 * This is a Unit Test script for the
 * HTMLTagClass class.  It is used to make sure
 * everything works from build to build.
 * 
 * 
 * $Id: unittest3.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */

require_once(PHPHTMLLIB_ABSPATH . "/includes.inc");
/**
 * You have to have PEAR's PHPUnit installed
 * 
 * pear install PHPUnit
 */
require_once("PHPUnit.php");


/**
 * Test the Container class
 */
class HTMLTagClassTest extends PHPUnit_TestCase {

    function HTMLTagClassTest($name) {
        $this->PHPUnit_TestCase($name);
    }

    function test_Constructor() {
        $tag = new HTMLTagClass(array("src" => "http://www.slashdot.org"));
        $tag->set_tag_name("a");
        $this->assertEquals("a", $tag->_tag, "Test tag name");
        $this->assertEquals(0, $tag->count_content(), "Test content count");
        $this->assertEquals("http://www.slashdot.org", 
                            $tag->_attributes["src"], "Test tag attribute");
    }

    function test_set_style() {
        $tag = new DIVtag();
        $str = "color:blue;";
        $tag->set_style($str);
        $this->assertEquals($str, $tag->_attributes["style"], "Test style attribute");
    }

    function test_set_class() {
        $tag = new DIVtag();
        $str = "foo";
        $tag->set_class($str);
        $this->assertEquals($str, $tag->_attributes["class"], "Test class attribute");
    }

    function test_set_id() {
        $tag = new DIVtag();
        $str = "foo";
        $tag->set_id($str);
        $this->assertEquals($str, $tag->_attributes["id"], "Test id attribute");
    }
}

$suite = new PHPUnit_TestSuite('HTMLTagClassTest');
$result = PHPUnit::run($suite);
if (isset($_SERVER["PHP_SELF"]) && strlen($_SERVER["PHP_SELF"]) > 0) {
    echo $result->toHTML();
} else {
    echo $result->toString();
}
?>
