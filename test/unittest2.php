<?php
/**
 * This is a Unit Test script for the
 * XmlTagClass class.  It is used to make sure
 * everything works from build to build.
 * 
 * 
 * $Id: unittest2.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
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
class XMLTagClassTest extends PHPUnit_TestCase {

    function XMLTagClassTest($name) {
        $this->PHPUnit_TestCase($name);
    }

    function test_Constructor() {
        $tag = new XMLTagClass("foo",array("bar" => 1, "blah" => ""));
        $this->assertEquals("foo", $tag->_tag, "Test tag name");
        $this->assertEquals(0, $tag->count_content(), "Test content count");
        $this->assertEquals(1, $tag->_attributes["bar"], "Test tag attribute");
    }

    function test_add() {
        $tag = new XMLTagClass("foo");
        $tag->add("foo","bar", "blah");
        $this->assertEquals(3, $tag->count_content(), "Test content count");
        $foo = $tag->get_element(2);
        $this->assertEquals("blah", $foo, "Test content value");
    }

    function test_set_cdata_flag() {
        $tag = new XMLTagClass("foo");
        $tag->add("foo","bar", "blah");
        $tag->set_cdata_flag(TRUE);
        $this->assertEquals(_CDATACONTENTWRAP, $tag->_flags & _CDATACONTENTWRAP,
                            "Test the flag bitfield");
        $this->assertEquals("<foo><![CDATA[", 
                            substr($tag->render(), 0, 14),
                            "Test CDATA tag");
    }

    function test_render() {
        $tag = new XMLTagClass("foo");
        $tag->add("foo", "bar");
        $this->assertEquals("<foo>\n"._INDENT_STR."foo\n"._INDENT_STR."bar\n</foo>\n",
                            $tag->render(0), 
                            "Test render with indent level 0");
        $this->assertEquals(_INDENT_STR."<foo>\n"._INDENT_STR._INDENT_STR."foo\n".
                            _INDENT_STR._INDENT_STR."bar\n".
                            _INDENT_STR."</foo>\n",
                            $tag->render(1), 
                            "Test render with indent level 1");

        $tag->set_collapse(TRUE, FALSE);
        $this->assertEquals("<foo>foobar</foo>",
                            $tag->render(1),  "Test render with collapse");

    }
}

$suite = new PHPUnit_TestSuite('XMLTagClassTest');
$result = PHPUnit::run($suite);
if (isset($_SERVER["PHP_SELF"]) && strlen($_SERVER["PHP_SELF"]) > 0) {
    echo $result->toHTML();
} else {
    echo $result->toString();
}
?>
