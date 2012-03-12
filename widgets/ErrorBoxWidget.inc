<?php
/**
 * 
 * $Id: ErrorBoxWidget.inc 3540 2011-01-27 21:38:19Z mpwalsh8 $
 * 
 * This file contains the ErrorBoxWidget object
 * that is used to display an 'error' display
 * widget in the UI.
 * 
 * @author Walter A. Boring IV
 */



/**
 * This class is for displaying a standardized
 * look and feel for an 'error' display.
 * 
 * @author Walter A. Boring IV
 */
class ErrorBoxWidget extends BaseWidget {

	/**
	 * This is the message that gets displayed
	 * underneath the image and before the
	 * list of errors
	 */
	var $_message = "Please review the following error(s) below.";

	/**
	 * The constructor
	 * 
	 * @param string the title used in the error box
	 *        Default = 'Errors'
	 * @param string the width of the entire object
	 */
	function ErrorBoxWidget($title="Error", $width="100%", $align=NULL) {
		$this->set_title($title);
		$this->set_width($width);
		$this->set_align($align);
	}

	/**
	 * This method is for changing the default
	 * message that gets displayed before the
	 * list of errors
	 * 
	 * @param string the message you want displayed
	 */
	function set_message($message) {
		$this->_message = $message;
	}


	/**
	 * This method is used to add individual 
	 * errors. 
	 * 
	 * @param string the label for the error
	 * @param string the actual error message
	 */
	function add($label, $message) {
		$this->data[] = array('label' => $label,
							  'message' => $message);
	}


	/**
	 * This is called to generate the resulting html
	 * output
	 * 
	 * @param int
	 * @param int
	 */
	function render($indent_level=0, $output_debug=0) {
		$table = html_table($this->get_width(),0,0,0, $this->get_align());
		$table->set_tag_attribute('class', 'errorbox');

		//build the big header and the generic message
		$td = new TDtag(array('colspan' => 2, 'class' => 'errorseparator'),
						html_img($this->_image_prefix.'/icon_alert_triangle.gif'),
						html_span('errortitle', $this->get_title()));

		//generic TEXT
		$td->add(html_div('errormessage',$this->_message));
		$table->add_row( $td );

		//walk each visible form element and see if there is an error in it
		foreach( $this->data as $error ) {
			$table->add_row(html_div( 'errorcell', $error['label'] ), 
							$error['message']);
		}

		return $table->render($indent_level, $output_debug);
	}
}


/**
 * This class defines the css used by the 
 * TextNav Object.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib 
 */
class ErrorBoxWidgetCSS extends CSSBuilder {

	function user_setup() {

		$this->add_entry('.errorbox', '',
						 array('border' => '1px outset #aaaaaa;',
							   'background-color' =>  '#efefef'));

		$this->add_entry('.errorbox', '.errortitle',
						 array('color' => '#FF0000'));

		$this->add_entry('.errorbox', '.errorseparator',
						 array('border-bottom' => '1px solid #afafaf',
							   'padding' => '5px'));

		$this->add_entry('.errorbox', '.errorcell',
						 array('font-family' => 'arial',
							   'size' => '10pt',
							   'padding' => '3px',
							   'white-space' => 'nowrap'));

		$this->add_entry('.errorbox', '.errormessage',
						 array('text-align' => 'center',
							   'padding-top' => '10px',
							   'padding-bottom' => '10px'));
	}	
}


?>
