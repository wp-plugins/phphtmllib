<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/** 
 * This is an unrealistic example form that uses all available form elements.
 * No items have explicitly been marked as required, enabling you to test
 * individual elements by entering good data or garbage and seeing the result.
 *
 * $Id: form3.php 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @package phpHtmlLib 
 * @subpackage form-examples 
 * @version 1.0.0
 *
 */

function xxx($var) { echo "<xmp>"; var_dump($var); echo "</xmp>"; }

// Include the phphtmllib libraries
include_once("includes.inc");
include_once(PHPHTMLLIB_ABSPATH . "/includes.inc");

// Include the Form Processing objects
include_once(PHPHTMLLIB_ABSPATH . "/form/includes.inc");


//use the class we defined from 
//Example 3.
include_once(PHPHTMLLIB_ABSPATH . "/examples/MyLayoutPage.inc");

/**
 * A simple Page Layout object child.  this came from Example 3.
 *
 * @author Culley Harrelson <culley@fastmail.fm>
 * @package phpHtmlLib 
 * @subpackage form-examples 
 *
 */
class Form3Page extends MyLayoutPage {

    function content_block() {
        //build the FormProcessor, and add the
        //Form content object that the FormProcessor 
        //will use.  Make the width of the form 95%
        return new FormProcessor(new SampleForm(800));
    }
}


/**
 * This is the Class that handles the building of the Form itself.  It creates
 * the Form Elements inside the form_init_elements() method.
 *
 * @author Culley Harrelson <culley@fastmail.fm> 
 * @package phpHtmlLib 
 * @subpackage form-examples 
 *
 */

class SampleForm extends FormContent { // {{{

    /**
     * constructor-- set up form
     *
     */
    function SampleForm($width=600) {
        parent::FormContent($width);
        $this->set_stripslashes();
    }

    /** 
     * This method gets called EVERY time the object is created.  It is used to
     * build all of the FormElement objects used in this Form.
     *
     */
    function form_init_elements() {

        // we want an confirmation page for this form.
        $this->set_confirm();

        // we want an confirmation page for this form.
        $this->set_required_marker(html_span('red', '*'));

        // now start to add the Form Elements that will be used in this form.

        // FEButton  (label $label, string $value, [string $action = NULL],
        // [int $width = NULL], [int $height = NULL])
        $this->add_element(new FEButton("FEButton Label", 'button-value', 'javascript-action'));

        // FECheckBox  (label $label, string $text)
        $this->add_element(new FECheckBox("FECheckBox Label", 'checkbox-text'));

        // FEDataList  (string $label, [boolean $required = TRUE], [int $width
        // = NULL], [int $height = NULL], [array $data_list = array()])
        $list =  new FECheckBoxList("FECheckBoxList label", FALSE,
                                    "200px", "80px",
                                    array("Testing 123" => "foo",
                                          "my value is bar" => "bar",
                                          "Somone's test" => "blah",
                                          "Slerm" => "slerm",
                                          "my value is hat" => "hat",
                                          "my value is not hat" => 3,
                                          "One" => 1));
        $list->disable_item("Testing 123");
        $this->add_element($list);

        // FEComboListBox  (string $label, [boolean $required = TRUE], [int
        // $width = "200px"], [int $height = "100px"], [array $from_data_list =
        // array()], [array $to_data_list = array()])
        $combo_list = new FEComboListBox("FEComboListBox Label", false, '200px', 
                        '100px', array('one' => 1, 'two' => 2), array('three' => 3, 'four' => 4));
        $combo_list->set_to_label('this is the to label');
        $combo_list->set_from_label('this is the from label');
        $this->add_element($combo_list);

        // FEConfirmActionButton  (mixed $label, mixed $value, [mixed $message
        // = NULL], [mixed $width = NULL], [mixed $height = NULL])
        $this->add_element(new FEConfirmActionButton("FEConfirmActionButton label", 
                    'click me for a javascript confirmation', 'Are you sure?'));

        // the constructor for FEPassword and FEConfirmPassword are the same as FEText
        $password = new FEPassword("FEPassword label", false, "200px");
        $this->add_element($password);

        $confirm = new FEConfirmPassword("FEConfirmPassword label", false, "200px");

        // add the password FormElement to the ConfirmPassword FormElement so
        // we can make sure they match.
        $confirm->password($password);
        $this->add_element($confirm);

        // These elements have the same constructor as FEText
        $this->add_element(new FEDomainName("FEDomainName label", false, "200px"));
        $this->add_element(new FEEmail("FEEmail label", false, "200px"));
        $this->add_element(new FEEmailMany("FEEmailMany label (comma separated)", false, "400px"));

        // file upload
//        $file = new FEFile("FEFile label", false, "200px");
//        $file->add_valid_type('image/gif');
//        $file->add_valid_type('image/jpeg');
//        $file->set_max_size(1024 * 2);
//        $this->add_element($file);

        // FEHidden  (mixed $label, [mixed $value = NULL])
        $this->add_element(new FEHidden("FEHidden label", 'the hidden value'));

        // FEHostNameWithPort  (label $label, [bool $required = TRUE], [int
        // $width = NULL], [int $maxlength = NULL], [bool $seperate_port =
        // FALSE])
        $this->add_element(new FEHostNameWithPort("FEHostNameWithPort label", false));

        // Same constructor as FEText
        $this->add_element(new FEIPAddress("FEIPAddress label", false, "200px"));

        // Same constructor as FEHostNameWithPort
        $this->add_element(new FEIPAddressWithPort("FEIPAddressWithPort label", false));

        // your standard drop down select list
        $list_box_collapsed = new FEListBox('FEListBoxCollapsed label', false, '200px');
        $list_box_collapsed->set_list_data(array('one' => 1, 'two' => 2, 'three' => 3, 'four' => 4));
        $this->add_element($list_box_collapsed);

        // same as the above select list but with a height setting
        $list_box = new FEListBox('FEListBox label', false, '200px', '100px');
        $list_box->set_list_data(array('one' => 1, 'two' => 2, 'three' => 3, 'four' => 4));
        $this->add_element($list_box);

        // FEMonths($label, $required = TRUE, $width = NULL, $height = NULL, $locale = 'en', $format = 'long') {
        $this->add_element(new FEMonths("FEMonths label", false));

        // FEYears($label, $required = TRUE, $width = NULL, $height = NULL, $min_year = 2000, $max_year = 2010) {
        $this->add_element(new FEYears("FEYears label", false, null, null, date('Y'), date('Y') + 10));

        // FEDays($label, $required = TRUE, $width = NULL, $height = NULL) {
        $this->add_element(new FEDays("FEDays label", false));

        // set the locale to dutch
        setlocale(LC_TIME, 'nl_NL');

        // TODO: document this
        $date_element = new FEDate("FEDate label", false, null, null, 'Fdy', 1970, 1975);
//        $date_element->set_short_months();
//        $date_element->set_min_year(1970);
//        $date_element->set_max_year(1975);
//        $date_element->set_format('Fdy');
        $date_element->set_text_format("%s %s, %s");
//        $date_element->set_text_format("%04d-%02d-%02d");
        $this->add_element($date_element);

        // a list box that allows you to select multiple items
        $m_list_box = new FEMultiListBox('FEMultiListBox label', false, '200px', '100px');
        $m_list_box->set_list_data(array('one' => 1, 'two' => 2, 'three' => 3, 'four' => 4));
        $this->add_element($m_list_box);

        // Same constructor as FEText
        $this->add_element(new FEName("FEName label", false, "200px"));

        $nested_list_box = new FENestedListBox('FENestedListBox label', false, '200px', '100px');
        $data = array("Test" => 1, "Foo" => array("value" => 2, "items" => array("Blah" => 3, "php" => 4)), "Bar" => array("value" => 5, "items" => array("testing" => array("value" => 6, "items" => array("ugh" => 7)), "again" => 8)));
        $nested_list_box->set_list_data($data);
        $this->add_element($nested_list_box);

        // Same constructor as FEText
        $this->add_element(new FENumber("FENumber label", false, "200px"));
        $this->add_element(new FENumberFloat("FENumberFloat label", false, "200px"));
        $this->add_element(new FENumberFloat("FENumberFloat label", false, "200px"));

        // FENumberInRange  (label $label, [bool $required = TRUE], [int $width
        // = NULL], [int $maxlength = NULL], int $min, [int $max = 100],
        // [boolean $label_flag = TRUE])
        $this->add_element(new FENumberInRange("FENumberInRange label", false, "200px", null, 1, 10));


        // Same constructor as FEText
        $this->add_element(new FENumberPrice("FENumberPrice label", false, "200px"));

        // FERadioGroup  (label $label, [array $data_list = array()]) 
        $this->add_element(new FERadioGroup("FERadioGroup label", 
                    array('one' => 1, 'two' => 2, 'three' => 3, 'four' => 4)));

        // this is the same as the above radio group but it is handled
        // differently in the display method below
        $vertical_group = new FERadioGroup("FERadioGroup vertical label", 
                                           array('one' => 1, 'two' => 2, 'three' => 3, 'four' => 4));
        $vertical_group->set_br_flag(TRUE);
        $this->add_element( $vertical_group );

        // add constructor label here.
        $this->add_element( new FERegEx("FERegEx label", false, '200px', 3, 
                    '/^1[a-z]T$/', 'This field must equal 1[a-z]T') );

        $this->add_element(new FEText("FEText label", false, "200px"));

        // FETextArea  (label $label, [bool $required = TRUE], int $rows, int
        // $cols, [int $width = NULL], [int $height = NULL], [int
        // $limit_char_count = -1])
        $this->add_element(new FETextArea("FETextArea label", false, 10, 50, null, 300));

        // FEUnitedStates  (string $label, [boolean $required = TRUE], [int
        // $width = NULL], [int $height = NULL], array 4)
        $this->add_element(new FEUnitedStates("FEUnitedStates label", false));

        // Same constructor as FEText
        $this->add_element(new FEUrl("FEUrl label", false, "200px"));
        $this->add_element(new FEUrlStrict("FEUrlStrict label", false, "200px"));

        // FEYesNoListBox  (label $label, [bool $required = TRUE], [array
        // $width = NULL], [int $height = NULL], [string $yes_value = "yes"],
        // [string $no_value = "no"])
        $this->add_element(new FEYesNoListBox("FEYesNoListBox label", false));

        // FEYesNoRadioGroup  (label $label, [bool $required = TRUE], [string
        // $yes_value = "yes"], [string $no_value = "no"]) 
        $this->add_element(new FEYesNoRadioGroup("FEYesNoRadioGroup label", false));

        // FEZipcode  (label $label, [bool $required = false], [int $width =
        // NULL], [int $maxlength = 5])
        $this->add_element(new FEZipcode("FEZipcode label", false));

        // FESubmitButton  (label $label, string $value, [int $width = NULL],
        // [int $height = NULL])
        $this->add_element(new FESubmitButton("FESubmitButton label", 'submit button value'));

    }

    /**
     * This method is called only the first time the form page is hit.  This
     * enables u to query a DB and pre populate the FormElement objects with
     * data.
     *
     */
    function form_init_data() {

        $this->set_element_value('FECheckBoxList label', 'bar');
        $this->set_element_value('FECheckBoxList label', 'blah');
        $this->set_element_value('FECheckBoxList label', 3);

        //this sets the value to the FERadioGroup first value to 3 or 'three'
        $this->set_element_value('FERadioGroup label', 3);

        //this sets the value to the FERadioGroup vertical to 2 or 'two'
        $this->set_element_value('FERadioGroup vertical label', 2);

        //this sets the default value of the FEYesNoRadioGroup to no
        $this->set_element_value('FEYesNoRadioGroup label', 'no');

        //the default values for check boxes take a boolean
        $this->set_element_value('FECheckBox Label', true);

        //the default values for FEDate elements should be an ISO 8601 date string
        $this->set_element_value('FEDate label', '1974-10-07');
    }


    /**
     * This is the method that builds the layout of where the FormElements will
     * live.  You can lay it out any way you like.
     *
     */
    function form() {

        $table = html_table($this->_width,0,0,8);

        // add each element to the form as it was included above
        $x=1;
        foreach(array_keys($this->_elements) as $label) {
            if ($x == 1) {
                $table->add_row(new TDtag(array('width' => '300'),
                                          $this->element_label($label)),
                                $this->element_form($label));
                $x=2;
            } else {
                $table->add_row($this->element_label($label), $this->element_form($label));
            }
        }

        return $table;
    }

    /**
     * This method gets called after the FormElement data has passed the
     * validation.  This enables you to validate the data against some backend
     * mechanism, say a DB.
     *
     */
    function form_backend_validation() {
        //$this->add_error("uh oh", "some bogus error happened");
        //return FALSE;
        return TRUE;
    }

    /**
     * This method is called ONLY after ALL validation has passed.  This is the
     * method that allows you to do something with the data, say insert/update
     * records in the DB.
     *
     */
    function form_action() {
        //$this->add_error("uh oh", "some bogus error happened");
        //return FALSE;
        $this->set_action_message("WOO!");
        $dump = html_xmp();
        foreach( $this->_elements as $label => $element ) {
            $dump->add( $label."  = ".print_r($element->get_value(),true) );
        }

        print $dump->render();
        exit;
        return TRUE;
    }
} //}}}


$page = new Form3Page("Form Example 3");
print $page->render();

?>
