<?php
/**
 * This is a Unit Test script for the
 * Container class.  It is used to make sure
 * everything works from build to build.
 * 
 * 
 * $Id: unittest1.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
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
class ContainerTest extends PHPUnit_TestCase {

    function ContainerTest($name) {
        $this->PHPUnit_TestCase($name);
    }

    function test_Constructor() {
        $container = new Container("foo", 1, new StdClass);
        $this->assertEquals($container->count_content(),3, "Test content count");
        $this->assertTrue(is_object($container->_content[2]) &&
                          strcasecmp(get_class($container->_content[2]),"stdClass") == 0, 
                          "Test stdClass");
    }

    function test_add() {
        $container = new Container();
        $container->add("foo");
        $this->assertEquals($container->count_content(),1, "Test content count");
        $foo = $container->get_element(0);
        $this->assertEquals($foo, "foo", "Test");
    }

    function test_get_element() {
        $container = new Container();
        $test = "foo";
        $container->add($test);
        $foo =& $container->get_element(0);
        $this->assertEquals($foo,"foo", "Test adding 'foo'");
    }


    function test_reset_Content() {
        $container = new Container();
        $container->reset_content();
        $this->assertEquals(0,$container->count_content(), "Test reset to empty");
        $container->reset_content("foo");
        $foo =& $container->get_element(0);
        $this->assertEquals("foo",$foo, "Test adding 'foo'");
    }

    function test_set_collapse() {
        $container = new Container();
        $container->set_collapse(TRUE);
        $this->assertEquals(_COLLAPSE, $container->_flags & _COLLAPSE, 
                            "Test the collapse flag bitfield");
        $this->assertEquals(_INDENT, $container->_flags & _INDENT, 
                            "Test the indent flag bitfield");
        $container->set_collapse(FALSE, FALSE);
        $this->assertEquals(0, $container->_flags & _COLLAPSE, 
                            "Test the collapse flag bitfield");
        $this->assertEquals(0, $container->_flags & _INDENT, 
                            "Test the indent flag bitfield");
    }

    function test_render() {
        $container = new Container();
        $container->add("foo", "bar");
        $this->assertEquals("foo\nbar\n",
                            $container->render(0), 
                            "Test render with indent level 0");
        $this->assertEquals(_INDENT_STR."foo\n"._INDENT_STR."bar\n",
                            $container->render(1), 
                            "Test render with indent level 1");

        $container->set_collapse(TRUE, FALSE);
        $this->assertEquals("foobar",
                            $container->render(1),  "Test render with collapse");

    }
}

$suite = new PHPUnit_TestSuite('ContainerTest');
$result = PHPUnit::run($suite);
if (isset($_SERVER["PHP_SELF"]) && strlen($_SERVER["PHP_SELF"]) > 0) {
    echo $result->toHTML();
} else {
    echo $result->toString();
}
?>
