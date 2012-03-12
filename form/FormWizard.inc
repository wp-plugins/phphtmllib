<?php
/**
 * This file contains the FormWizard class.
 *
 * $Id: FormWizard.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@buildabetterweb.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 * @todo Finish this.  It doesn't work now.
 *
 */

define("WIZARD_VISITED", "_wizard_visited");
define("WIZARD_STEP", "_wizard_step");
define("WIZARD_TO_STEP", "_wizard_to_step");
define("WIZARD_ID", "_wizard_id");
define("WIZARD_ACTION", "_wizard_action");

define("WIZARD_NEXT", "NEXT");
define("WIZARD_PREV", "PREV");
define("WIZARD_JUMP", "JUMP");
define("WIZARD_FINAL", "FINAL");


/**
 * This is a magic container that allows you
 * to chain together multiple FormContent objects
 * to automatically create a Wizard process.
 *
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @todo Finish this.  It doesn't work now.
 */
class FormWizard extends FormProcessor {

    /**
     * This holds the array of
     * step objects for the
     * wizard
     */
    var $_steps = array();


    /**
     * Holds a bunch of state
     * variables
     */
    var $_vars = array("to_step" => 0,
                       "num_steps" => 0,
                       "on_confirm" => FALSE,
                       WIZARD_ID => NULL );


	/**
	 * Flag to tell us to enable confirmation or not
	 */
	var $_has_confirm = FALSE;


	/**
	 * Last step text.
	 * By default it is 'Finish'
	 */
	var $_last_step_text = 'Finish';

	/**
	 * The CSS class for the buttons
	 */
	var $_button_class = '';


    /**
	 * The image path prefix.
	 * If an image lives on the server in 
	 * /images/foo/blah.jpg
	 * then this prefix should be
	 * /images/foo
	 */
	var $_image_prefix ;


    /**
     * The constructor
     *
     */
    function FormWizard() {
	$this->_image_prefix = PHPHTMLLIB_RELPATH . '/images/wizard';
        //user_error(__CLASS__."::".__FUNCTION__." - this class isn't done yet.");
        $this->_session_test();
        $this->set_form_name( "form_wizard" );
        $this->set_form_action( $_SERVER["PHP_SELF"] );

		//init our vars
        $this->_init();

        //let the child class add the steps
        $this->user_setup();

        $this->_init_forms();

        //Set up the Validation object
        //and the FormErrors object to
        //be used by this form.
        $this->setup_validation();

        //set the current step
        $this->_set_step();

        //now process the form
        $this->_process_form();
         
        //now we need to process the current step.
    }

    /**
     * This function is used to setup
     * the validation object and the
     * form errors object that is to be
     * used by this form.
     *
     * You can override this method to
     * use a different FormErrors object
     * for localization.
     */
    function setup_validation() {
        $this->_FormValidation =& FormValidation::singleton();
        //$this->_form_content->_set_validation_object($this->_FormValidation);
    }

	/**
	 * This sets the $this->_has_confirmation
	 * flag.  to let the object know it has
	 * a required confirmation page, which
	 * should get called after the validation
	 * is successfull, and before the action is
	 * handled on the back-end.
	 *
	 * @param boolean - the flag value TRUE/FALSE
	 */
	function set_confirm( $flag = TRUE ) {
		$this->_has_confirm = $flag;
	}

	/**
	 * This gets the value of the confirmation flag.
	 * which tells the caller that this object
	 * has/doesn't have a required confirmation
	 * page.
	 *
	 * @return boolean
	 */
	function has_confirm() {
		return $this->_has_confirm;
	}


	/**
	 * Get the wizard session id
	 * 
	 * @return string
	 */
	function get_wizard_id() {
		return $_SESSION[$this->_vars[WIZARD_ID]];
	}

	/**
	 * This method sets the text to be used
	 * for the last/final step prior to the
	 * action being taken.
	 */
	function set_last_step_text($text) {
		$this->_last_step_text = $text;
	}

	/**
	 * This method sets the button CSS class
	 */
	function set_button_class($class) {
		$this->_button_class = $class;
	}


    /**
     * This function renders the
     * FormWizard
     *
     */
    function render($indent_level=0, $output_debug=0) {
        $container = container();
        $this->_form_content->_allow_actions = FALSE;

        if ($this->_has_errors) {
            //we need to render the form errors
            //and then the form
            $container->add( $this->render_error($indent_level, $output_debug) );
        } else {
            //there are no errors!
            //debug( $_REQUEST );
            if (isset($_REQUEST[$this->_form_attributes['name'].FORM_VISITED]) && 
                $_REQUEST[$this->_form_attributes['name'].FORM_VISITED] == 1) {
                //looks like the form has been processed?

				//see if this is the FINAL step?
				if (@$_REQUEST[WIZARD_ACTION] == WIZARD_FINAL) {
					//this is the last step. they want to perform the action
					$success = $this->_form_content->form_success();
                    if ($this->_form_success_render) {
                        $container->add( $this->render_form($indent_level, $output_debug, $success) );
					} else {
                        if (method_exists($success,"render")) {
                            //looks like this is an object.
                            //we'll assume it has a render function.
                            $container->add( $success->render($indent_level, $output_debug) );
                        } else {
                            //since its not an object,
                            //lets just display it.
                            $container->add( $success );
                        }
                    }
				} else if ($this->_has_confirm && !$this->_confirmed && $this->_vars["on_confirm"]) {
                    $container->add( $this->render_confirm($indent_level, $output_debug) );
                } else {
					$container->add( $this->render_form($indent_level, $output_debug) );
                }
            } else {
                $container->add( $this->render_form($indent_level, $output_debug) );
            }
        }

        return $container->render($indent_level, $output_debug);
    }


    /**
     * This method does the logic of
     * doing the form processing
     */
    function _process_form() {
        if (!$this->_is_step_visited($this->_current_step()) &&
            $this->_current_step() <= $this->_vars["num_steps"]) {
            $this->_form_content->form_init_data();
        }

        //we only need to process the form
        //if it has been visited. Otherwise
        //it just gets rendered.
        if (@$_REQUEST[$this->_form_attributes['name'].FORM_VISITED] == 1) {
            //ddd($this->_form_content);
            //$this->_form_content->set_action($_REQUEST[FORM_ACTION]);

            //let see if this was a confirmation page.
            if ( @$_REQUEST[WIZARD_ACTION] == WIZARD_FINAL ) {
                //looks like this was a submit on a
                //confirmation page.  we don't need
                //to do form field validation.
                $this->_confirmed = TRUE;
                for ($i=0; $i<=$this->_vars["num_steps"]-1; $i++) {
					$this->_form_content =& $this->_steps[$i]["form"];
					$this->_form_content->set_action("Confirm");
                    $this->_has_errors = !$this->_form_content->form_action();
					$this->_set_step($i+1);
					//if we found an error, lets bail now.
					if ($this->_has_errors) {
						break;
					}
                }
            } else {
                //we haven't been confirmed, so we
                //need to validate the form.
                if ($this->can_validate()) {
                    //looks like we should do validation
                    if ($_REQUEST[WIZARD_ACTION] != WIZARD_PREV) {
                        //we don't need to validate if we haven't
                        //finished this step yet.
                        $this->do_validation();
                    }
                }
                if (!$this->_has_errors) {
                    //no errors were found
                    //make sure we don't have any backend errors
                    $this->_has_errors = !$this->_form_content->form_backend_validation();
                    if (!$this->_has_errors) {
                        //ok this step validated.  lets display the next.
                        //mark this step as visited
                        $current_step = $this->_current_step();

                        switch ($_REQUEST[WIZARD_ACTION]) {
                        case WIZARD_NEXT:
                            if ($current_step == $this->_vars["num_steps"]) {
                                //we need to show the confirmation
                                //don't process
                                $this->_vars["on_confirm"] = TRUE;
                                $this->_step_visited( $current_step );
                                $this->_set_current_step($current_step+1);
                            } else {
                                $this->_step_visited( $current_step );
                                $this->_set_current_step($current_step+1);
                                unset($_REQUEST[FORM_VISITED]);
                                $this->_form_content = &$this->_steps[$this->_current_step()-1]["form"];
								if (!$this->_is_step_visited($this->_current_step())) {
									$this->_form_content->form_init_data();
								}
                            }
                            break;

                        case WIZARD_PREV:
                            $this->_set_current_step($current_step-1);
                            unset($_REQUEST[$this->_form_attributes['name'].FORM_VISITED]);
                            $this->_form_content = &$this->_steps[$this->_current_step()-1]["form"];
                            break;
                        }
                    }
                }
            }
        }
    }


    /**
     * This function renders the confirmation
     * page.  This page sits in between the
     * front end form, and the action handler.
     * This only gets called after a form
     * and its data has been successfully
     * validated.
     *
     * @param int - $indent_level
     * @param int - $output_debug
     *
     * @return string - the raw html
     */
    function render_confirm( $indent_level, $output_debug ) {
        //build the $this->_form object.
        $this->_build_form_tag();

        //add the confirm object/html
        for($i=0; $i<=$this->_vars["num_steps"]-1; $i++) {
            $title = "Step ".($i+1)." : ".$this->_steps[$i]["title"];
            $this->_form->add( $this->_steps[$i]["form"]->form_confirm($title, FALSE),
                               html_br(2));
        }
        //$confirm = &$this->_form_content->form_confirm( $this->data );
        //$this->_form->add_reference( $confirm );

        //ok add all of the submitted data as hidden form fields
        $this->_add_confirm_data();

        //Ok lets add our hidden vars
        $this->__hidden_fields();

        return $this->_form->render($indent_level, $output_debug);
    }



	/**
	 * Override this so that we can place the 
	 * toolbar first inside the form tag.  We also
	 * have to make sure the onsubmit stuff is working properly.
	 * 
	 */
	function _build_form_tag() {
		//we should do the onsubmit if we aren't on a confirmation
		if (!$this->_has_confirm || !($current_step == $this->_vars["num_steps"]+1)) {
			$this->set_onsubmit( $this->get_onsubmit().$this->_form_content->_form_on_submit.$this->_form_content->_form_action_elements_on_submit );
		}

        $form_attrs = array();
        foreach( $this->_form_attributes as $name => $value) {
            if ($value) {
                $form_attrs[$name] = $value;
            }
        }
        $this->_form = new FORMtag( $form_attrs );

		$this->_form->add( $this->_build_js() );
        $this->_form->add( $this->_build_toolbar(), html_br(2) );
	}

    /**
     * A subclass can override this function
     * to setup the class variables after
     * the constructor.  The constructor
     * automatically calls this function.
     *
     */
    function user_setup() {
        trigger_error("FormWizard::user_setup() - ".
                      "child class must override this method ".
                      "to add the wizard steps");
    }


    /**
     * This adds a step to the wizard
     *
     * @param string - the title for the step
     * @param string - the description for the step
     * @param string - the help url for the step (if any)
     * @param FormContent - the form content object
     *                      that is the step.
     */
    function add_step( $title, $desc, $help, &$step ) {
        $this->_steps[] = array("title" => $title,
                                "desc" => $desc,
                                "help" => $help,
                                "form" => &$step);
        $this->_vars["num_steps"]++;
    }


    /**
     * This function initializes all of the fields we
     * need to keep track of for the internal state
     * of the wizard.  It also walks each of the
     * step FormContent objects and initializes them.
     *
     * We save some of the state of the wizard in
     * the session.
     */
    function _init() {
        if (!isset($_REQUEST[WIZARD_VISITED])) {

            $this->_vars[WIZARD_ID] = uniqid("wizard_");

            $this->_init_session();
            $this->_vars["to_step"] = 2;
        } else {
            $this->_vars[WIZARD_ID] = $_REQUEST[WIZARD_ID];
            $current_step = $this->_current_step();
			//mark it as visited.
			$this->_step_visited($current_step);
            $this->_vars["to_step"] = $current_step++;
        }        
    }


	/**
	 * This is used to initialize all of the form content
	 * children classes
	 * 
	 */
	function _init_forms() {
		//initialize all of the Forms
        //so they retain their data.
        for ($i=0; $i<=$this->_vars["num_steps"]-1; $i++) {
            $this->_steps[$i]["form"]->form_init_elements();
			$this->_steps[$i]["form"]->set_wizard_id($this->get_wizard_id());
        }
	}

    /**
     * This function sets the _form_content
     * object for the current step we are operating on.
     * The parent FormProcessor needs this object set
     * in order to process the step correctly.
     *
     */
    function _set_step($step=null) {
        //ddd($this->_steps);
		if (is_null($step)) {
			$current_step = $this->_current_step();
			if ($current_step == $this->_vars['num_steps']+1 &&
				$_REQUEST[WIZARD_ACTION] == WIZARD_PREV) {
				$step = $this->_vars['num_steps']-1;
			} else if ($current_step == $this->_vars['num_steps']+1 &&
					   $_REQUEST[WIZARD_ACTION] == WIZARD_FINAL) {
				$step = $this->_vars['num_steps']-1;
			} else {
				$step = $current_step-1;
			}
		} else {			
			$_SESSION[$this->_vars[WIZARD_ID]]["current_step"] = $step;
			if ($step != 0) {
				$step--;
			}
		}

        $this->_form_content = &$this->_steps[$step]["form"];
		$this->_form_content->_allow_actions = FALSE;
    }


    function __hidden_fields() {

        //add all of the other steps fields
        //we need to add all the previous visted steps
        //fields so we save em.
        $step_count = 1;
		$form_content = $this->_form_content;
		
        foreach( $this->_steps as $step ) {
            if ($step_count != $this->_current_step()) {
                $this->_form_content = &$step["form"];
                $this->_add_confirm_data();
            }
            $step_count++;
        }
		$this->_form_content = $form_content;	
		

        /*if (isset($_REQUEST[WIZARD_ACTION]) &&
            $_REQUEST[WIZARD_ACTION] == WIZARD_FINAL ) {
            $this->_set_step();
        }*/

        parent::__hidden_fields();

        //$this->_form->add( form_hidden(WIZARD_STEP, $this->_vars["current_step"]) );
        $this->_form->add( form_hidden(WIZARD_TO_STEP, $this->_vars["to_step"]) );
        $this->_form->add( form_hidden(WIZARD_ID, $this->_vars[WIZARD_ID]) );
        $this->_form->add( form_hidden(WIZARD_ACTION, WIZARD_NEXT) );
        $this->_form->add( form_hidden(WIZARD_VISITED, 1) );
    }


    /**
     * This builds the javascript needed for the
     * navigation of the wizard
     *
     * @return string
     */
    function _build_js() {
        $name = $this->_form_attributes["name"];
		$submit = $this->get_onsubmit();
        $js = "
        function wizard_cancel_confirm(butname, txt) {
            if (confirm(txt)){
                document.$name.".WIZARD_ACTION.".value = butname;
                document.$name.submit();
            }
        }
        function wizard_submit(txt, step) {
            document.$name.".WIZARD_ACTION.".value = txt;
            document.$name.".WIZARD_TO_STEP.".value = step;
			$submit
            document.$name.submit();			
        }";

        $script = html_script();
        $script->add( $js );
        return $script;
    }



    /**
     * This renders the toolbar/step table
     * for the navigation of the wizard
     */
    function _build_toolbar() {
        $current_step = $this->_current_step();
        if ($current_step == $this->_vars["num_steps"]+1) {
            //$current_step++;
            $step_title = "Confirmation";
        } else {
            $step_title = $this->_steps[$current_step - 1]["title"];
        }

        $title = "Step ".$current_step." : ". $step_title;
        $table = new InfoTable($title, 500);

        //build the table of steps.
        $c = container();
        $c->set_collapse();
        $step_num = 1;
        foreach( $this->_steps as $step ) {
            $c->add( $this->_build_step_image( $step_num, $step["title"] ) );

            if ($step_num != $this->_vars["num_steps"]) {
                if ($step_num == $current_step - 1) {
                    $arrow = html_img($this->_image_prefix."/arrow_orange.gif");
                } else {
                    $arrow = html_img($this->_image_prefix."/arrow_gray.gif");
                }
                $arrow->set_style("vertical-align:super");
                $c->add( $arrow );
            }

            $step_num++;
        }

        //add the confirmation step
		if ($this->_has_confirm) {
			$c->add( $arrow );
			$c->add( $this->_build_step_image( $step_num, "Confirmation" ) );
		}

        $tr = html_tr("", $c );
        $tr->set_style("text-align: center");
        $table->add_row( $tr );

        //now show the description
        if ($this->_vars["on_confirm"] == true) {
            $desc = "Confirmation";
        } else {
            $desc = $this->_steps[$current_step - 1]["desc"];
        }
        $tr = html_tr("", $desc );
        $tr->set_style("text-align: center");
        $table->add_row( $tr );

        //now add the controls
        $c = html_div();
        $c->set_style("padding-top: 5px;");
        if ($current_step != 1) {
            $link = $this->_step_control('previous', $current_step-1);
            $c->add( $link );
        }

        if (($this->_has_confirm && ($current_step == $this->_vars["num_steps"]+1)) ||
			(!$this->_has_confirm && ($current_step == $this->_vars['num_steps']))) {
            $link = $this->_step_control('finish', $current_step);
            $c->add( _HTML_SPACE, _HTML_SPACE, $link);
        } else {
            $link = $this->_step_control('next', $current_step+1);
            $c->add( $link );
        }


        $tr = html_tr("", $c );
        $tr->set_style("text-align: center;");
        $table->add_row( $tr );

        return $table;
    }


    function _step_control($type, $step) {

        $js = "javascript:wizard_submit(";

        switch ($type) {
        case 'previous':
             $param = WIZARD_PREV;
			 $text = 'Previous';
             break;

        case 'next':
            $param = WIZARD_NEXT;
			$text = 'Next';
            break;

        case 'finish':
            $param = WIZARD_FINAL;
			$text = $this->_last_step_text;
            break;
        }

        $js .= "'".$param."', ".$step.");";

        $attributes = array('onclick'=>$js);
        
        if ($this->_button_class) {
        	$attributes['class'] = $this->_button_class;
        }

        $button = html_input('button', $text, $text, $attributes);
        return $button;
    }


    /**
     * This function builds an image for a step #
     *
     * @param string - the step # to build
     * @return Atag object
     */
    function &_build_step_image( $step_num, $step_title ) {
        $title = "Step ".$step_num." ";

        $current_step = $this->_current_step();
        //if ($this->_vars["on_confirm"]) {
            //$current_step++;
        //}

        if ($step_num == $current_step) {
            $title .= " (Current) : ".$step_title;
            $img = html_img($this->_image_prefix."/step_".$step_num."_process.gif", 21, 21, 0,
                            $title, NULL, $title);

        } else if ($this->_is_step_visited($step_num) ||
                   $current_step == $this->_vars["num_steps"]+1) {
            $title .= " (Completed) : ".$step_title;
            $img =  html_img($this->_image_prefix."/step_".$step_num."_complete.gif", 21, 21 ,0,
                             $title, NULL, $title);

        } else {
            $title .= " (Not Completed) : ".$step_title;
            $img = html_img($this->_image_prefix."/step_".$step_num."_notyet.gif", 21,21,0,
                            $title, NULL, $title);
        }

        return $img;
    }



    /*****************************************/
    /*        SESSION RELATED METHODS        */
    /*****************************************/

    /**
     * This method initializes the session
     * variable that we use
     *
     */
    function _init_session() {
        //create a unique id for this wizard
        //so we can have multple wizards
        //running per session.
        $_SESSION[$this->_vars[WIZARD_ID]] = array();
        $_SESSION[$this->_vars[WIZARD_ID]];
        $this->_set_current_step(1);

        //mark all steps as NOT visited
        for ($i=0; $i<=$this->_vars["num_steps"]-1; $i++) {
            $this->_step_visited($i, FALSE);
        }
    }

    /**
     * This returns the current step id
     * from the session
     *
     */
    function _current_step() {
        return $_SESSION[$this->_vars[WIZARD_ID]]["current_step"];
    }

    /**
     * This sets the current step id
     *
     * @param int - the new step #
     */
    function _set_current_step($step) {
        $_SESSION[$this->_vars[WIZARD_ID]]["current_step"] = $step;
    }


    /**
     * This sets the state variable for the
     * step to let us know it has been visited or not
     *
     * @param int - the step to mark
     * @param boolean - TRUE = visited
     */
    function _step_visited($step_num, $visited=TRUE) {
        $_SESSION[$this->_vars[WIZARD_ID]]["visited_steps"][$step_num] = $visited;
    }

    /**
     * This tests to see if the step has been visited or not.
     *
     * @param int - the step to mark
     * @return boolean - TRUE = visited
     */
    function _is_step_visited($step_num) {
        if (isset($_SESSION[$this->_vars[WIZARD_ID]]["visited_steps"][$step_num])) {
            return $_SESSION[$this->_vars[WIZARD_ID]]["visited_steps"][$step_num];
        } else {
            return FALSE;
        }
    }

    /**
     * This function cleans up the saved Session state
     * for the wizard.  This gets called when we have
     * completed the wizard w/o errors.
     *
     */
    function _clean() {
        unset($_SESSION[$this->_vars[WIZARD_ID]]);
    }

    /**
     * This ensures that we have sessions started
     *
     */
    function _session_test() {
        if (!session_id()) {
            //we have to have sessions started.
            session_start();
        }
    }



	/**
	 * This is used to save a wizard variable
	 * associated with a particular wizard instance
	 * 
	 * @param key
	 * @param value
	 */
	function set_wizard_variable($key, &$value) {
		$_SESSION[$this->_vars[WIZARD_ID]][$key] =& $value;
	}

	/**
	 * This gets a saved wizard variable
	 * 
	 * @param key
	 * @return value
	 */
	function &get_wizard_variable($key) {
		if (isset($_SESSION[$this->_vars[WIZARD_ID]][$key])) {
			return $_SESSION[$this->_vars[WIZARD_ID]][$key];
		} else {
			return NULL;
		}		
	}
}
?>
