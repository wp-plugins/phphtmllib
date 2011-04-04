<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This example illustrates the basics of the
 * BBCode Support for phphtmllib.
 *
 *
 * $Id$
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 * @subpackage form-examples
 * @since 2.5.5
 *
 */ 

/**
 * Include the phphtmllib libraries
 *
 */
include("includes.inc");

/**
 * Include the Form Processing objects
 *
 */
include_once(PHPHTMLLIB_ABSPATH . "/form/includes.inc");

/**
 * Include BBCode parser
 *
 */
include_once(PHPHTMLLIB_ABSPATH . "/widgets/BBCode.inc") ;

//use the class we defined from 
//Example 3.
include_once(PHPHTMLLIB_ABSPATH . "/examples/MyLayoutPage.inc");

/**
 * A simple Page Layout object child.
 * this came from Example 3.
 *
 * @author Mike Walsh <mike_walsh@mindspring.com>
 * @package phpHtmlLib
 * @subpackage form-examples 
 */
class Form10Page extends MyLayoutPage {

    function content_block() {

        $this->add_head_css(new InfoTableCSS) ;
        $this->add_head_css(new ActiveTabCSS) ;
        $this->add_head_css(new BBCodeCSS) ;
        $this->add_head_js(FEBBCodeTextAreaWidget::BBCodeJavascript()) ;

        //  build the FormProcessor, and add the
        //  Form content object that the FormProcessor 
        //  will use.  Make the width of the form 700

        $container = container() ;

        $form = new BBCodeForm("BBCode Parser", $_SERVER['PHP_SELF'], 700) ;

        //  If magic_quote_gpc is on, strip the slashes

        if (get_magic_quotes_gpc())
            $form->set_stripslashes() ;

       	//  Create the form processor
        $fp = new FormProcessor($form) ;

	    //  Display the form again even if processing was successful.

	    $fp->set_render_form_after_success(false) ;

	    //  If the Form Processor was succesful, parse
	    //  the BBCode and display it on the page.

	    if ($fp->is_action_successful())
	    {
            $bbcode = new BBCodeParser() ;
            $bbcode->setText($form->get_element_value("BBCode")) ;
            $nl2br = ($form->get_element_value("Break Newlines") != null) ;
            $bbcode->parse();
            $div = html_div("bbcodetextarea") ;
            $div->add($bbcode->getParsed($nl2br)) ;
            $div->add(html_br(2), html_a($_SERVER['PHP_SELF'], "Try again?")) ;
            $container->add($div,html_br(2)) ;
        }
        else
        {
	        //  Add the Form Processor to the container.

            $container->add($fp) ;
        }

        return $container ;
    }
}

define('WEBSERVER', $_SERVER['HTTP_HOST']) ;

/**
 * This is the Class that handles the building
 * of the Form itself.  It creates the Form Elements
 * inside the form_init_elements() method.
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage form-examples  
 */
class BBCodeForm extends StandardFormContent {

    /**
     * This method gets called EVERY time the object is
     * created.  It is used to build all of the 
     * FormElement objects used in this Form.
     *
     */
    function form_init_elements() {
        //  We want a confirmation page for this form.
        $this->set_confirm(true);

        //  Now start to add the Form Elements that will be used in this form.

        //  Build the BBCodeTextArea Form Element.  It is a complex
        //  widget wrapped around a text area.  When the element is
        //  constructed set the newline and strip tag handling.

        $TextArea = new FEBBCodeTextArea("BBCode", true, 20, 72) ;
        $TextArea->set_nl2br(false) ;
        $TextArea->set_strip_tags(true) ;
        $TextArea->set_wrapper_class("bbcodetextarea") ;
        //$TextArea->set_disabled(true) ;
        //$TextArea->set_readonly(true) ;

        $this->add_element($TextArea) ;

        //  Construct a single check box which to control newline breaking
        $CheckBox = new FECheckBox("Break Newlines", "Break Newlines") ;
        $this->add_element($CheckBox);
    }

    /**
     * This method is called only the first time the form
     * page is hit.  This enables u to query a DB and 
     * pre populate the FormElement objects with data.
     *
     */
    function form_init_data() {
        $server = &$_SERVER['HTTP_HOST'] ;
        $BBCodeSample = sprintf("
[b]bold[/b]
[i]italic[/i]
[u]underline[/u]
[s]strike[/s]
[sub]subscript[/sub]
[sup]superscript[/sup]
[color=blue]blue text[/color]
[size=18]the size of this text is 18pt[/size]
[font=verdana]different font type[/font]
[align=right]yes, you're right, this isn't on the left[/align]
[align=center]and this is in the center[/align]
he said: [quote=http://www.server.org/quote.html]i'm tony montana[/quote]
[code]
x = y + 6;
z = sqrt(x) ;
[/code]
http://%s
[url]http://%s[/url]
[url=http://%s]server[/url]
[url=http://%s target=_new]server[/url]
webmaster@%s
[email]webmaster@%s[/email]
[email=webmaster@%s]mail me[/email]
[img]http://phphtmllib.newsblob.com/images/phphtmllib_logo.png[/img]
[img w=111 h=26]http://phphtmllib.newsblob.com/images/logo.gif[/img]
[ulist]
[*]unordered item 1
[*]unordered item 2
[/ulist]
[list]
[*]unordered item 1
[*]unordered item 2
[/list]
[list=1]
[*]ordered item 1
[*]ordered item 2
[/list]
[list=i]
[*]ordered item 1 type i
[li=4]ordered item 4 type i[/li]
[/list]
[list=I]
[*]ordered item 1 type I
[/list]
[list=a s=5]
[li]ordered item 5 type a[/li]
[*]ordered item 6 type a
[/list]
[list=A]
[li]ordered item 1 type A[/li]
[li=12]ordered item 12 type A[/li]
[/list]
[list=A s=3]
[li]ordered item 1, nested list:
    [list=I]
    [li]nested item 1[/li]
    [li]nested item 2[/li]
    [/list][/li]
[li]ordered item 2[/li]
[/list]
", $server, $server, $server, $server, $server, $server, $server) ;

        //  In this example we just hard code some initial values

	    $this->set_element_value("BBCode", $BBCodeSample);
	    $this->set_element_value("Break Newlines", false);
    }


    /**
     * This is the method that builds the layout of where the
     * FormElements will live.  You can lay it out any way
     * you like.
     *
     */
    function form_content() {
        $table = html_table($this->_width,0,4);

        $BBCodeElement = $this->get_element("BBCode") ;

        //  Normally the form element would be added using the
        //  element_form() method but with the BBCode widget is
        //  constructed from the element and added instead.

        $table->add_row($this->element_label("BBCode"), 
            FEBBCodeTextAreaWidget::FEBBCodeTextAreaWidget($this->get_form_name(),
            $this->get_element("BBCode"), $this->element_form("BBCode"),
            true)) ;

        //  Add the check box
        $table->add_row(_HTML_SPACE, $this->element_form("Break Newlines"));

        //  Create a form block
        $this->add_form_block("BBCode", $table) ;
    }

    /**
     * This method gets called after the FormElement data has
     * passed the validation.  This enables you to validate the
     * data against some backend mechanism, say a DB.
     *
     */
    function form_backend_validation() {
        //$this->add_error("Ass", "some bogus error happened");
        //return FALSE;
        return TRUE;
    }

    /**
     * This method is called ONLY after ALL validation has
     * passed.  This is the method that allows you to 
     * do something with the data, say insert/update records
     * in the DB.
     */
    function confirm_action() {
        $this->set_action_message("WOO!");
        //$this->add_error("Ass", "some bogus error happened");
        //$this->add_error("First Name", "Duplicate!!  You suck!");

        //var_dump( $this->get_element_value("First Name") );
        return TRUE;
    }

    //  Overload form_action() due to a bug with form confirmation
    //  as "Save" isn't handled when form confirmation is turned off.

    /**
     * This method handles the form action.
     * 
     * @return boolean TRUE = success
     *                 FALSE = failed.
     */
    function form_action() {
        switch ($this->get_action()) {
        case "Edit":
            return FALSE;
            break;
            
        case "Save":
        case "Confirm":
            return $this->confirm_action();
            break;

        default:
            return FALSE;
            break;
        }
    }
}


$page = new Form10Page("Form Example 10 - BBCode Text Area");
print $page->render();
?>
