<?php

include_once("localinc.php");

/**
 * This function parses the input string and
 * replaces all occurences of a \n character
 * with a BRtag object.  Then it wraps the entire
 * new string with a DIVtag object with a
 * class reference of $class.
 *
 * @param   string  $raw_string - the input string.
 * @param   string  $class - the css class to give
 *                           to the wrapper DIVtag
 * @return  DIVtag object.
 */
function my_nl2br($raw_string, $class=NULL) {

    $attributes = array();
    if ($class) {
        $attributes = array ("class" => $class );
    }
    $div = new DIVtag( $attributes );

    //Ok now lets walk through the string
    //and find each \n char.
    $lines = explode( chr(13), $raw_string);
    $index=0;
    while( $lines[$index] ) {
        $div->add( $lines[$index], html_br() );
        $index++;
    }
    return $div;
}

$page = new HTMLPageClass("test.php");
$page->set_text_debug( $debug );

$form = new FORMtag(array("name"=> "testform",
                          "method" => "POST",
                          "action" => $_SERVER["PHP_SELF"]));


$textarea = form_textarea("text", "this is a lame test" );
$textarea->set_tag_attributes( array("cols" => "60",
                                     "rows" => "40") );

$form->add( html_br(), $textarea, html_br() );

$form->add( form_submit("what", "Submit") );
$form->add( form_submit("debug", "Debug") );

$page->add( $form, html_br(), html_br() );

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    //Ok lets process the input.
    $div = my_nl2br( $_POST["text"] );
    $page->add( $div );
}

print $page->render();
?>
