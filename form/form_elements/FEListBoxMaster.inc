<?php
/**
 * This file contains the FEListBoxMaster
 *
 * $Id: FEListBoxMaster.inc 3556 2012-03-11 11:26:12Z mpwalsh8 $
 *
 * @author Sumedh Thakar <sumedh_thakar@yahoo.com>
 * @package phpHtmlLib
 * @subpackage FormProcessing
 *
 * @copyright LGPL - See LICENCE
 *
 */

/**
 * This element builds the master datalist that will control one slave datalist
 * to change the value of the slave datalist when master changes in JS. It will also set
 * the valid list for the slave depending on the value of the master.
 * 
 * Please use regular FEListBox element for non-master lists.
 * 
 * please examples area.
 * 
 * @author Sumedh Thakar
 */
class FEListBoxMaster extends FEListBox {
    
    var $mdata = array();
    /**
     * This function sets the array of data
     * to be used in the data list
     *
     * @param array data_list - list of data elements (name=>value)
     */
    function set_list_data($data =array()) {
        
        $this->_mdata = $data;
        
        $tmp = array();
        foreach($this->_mdata as $master => $rec){
            $tmp[$master] = isset($rec["code"])? $rec["code"] : $master;
        }
        
        $this->_data_list = $tmp;
    }

    /**
     * This function will set the
     * data the parent wants to set for the slave
     *
     * @param the slave
     */
    function set_slave_data(&$slave, $value) {
        
        $flipped_array = array_flip($this->_data_list);
        if (isset($flipped_array[$value])) $value = $flipped_array[$value];
               
        if (isset($value) && isset($this->_mdata[$value]["slave"])) {
            $slave->set_list_data($this->_mdata[$value]["slave"]);
        }else{
            $slave->set_list_data(array("None"=>"None"));
        }
    }

    /**
     * This method is used for adding any javascript
     * that is used by this element.  This will automatically
     * get called and added to the page by the FormProcessor
     *
     * @return string - raw js
     */
    function javascript() {
        $slaves = $this->get_slave_elements();
        $master_name = $this->get_element_name();
        $slave = $slaves[0];
        $slave_name = $slave->get_element_name();
        $gFlagName = $master_name."_".$slave_name."_defined";

        
        global $$gFlagName;
        
        if (!isset($$gFlagName)) {
            $$gFlagName = true;
            //Create the JS array that will be used to populate the slave when master value changes
            $js_array = "slave_".$slave_name." = new Array();\n";
            foreach($this->_mdata as $master => $rec){

                if(isset($rec['slave']) && is_array($rec['slave'])){                    
                    $js_array .= "slave_".$slave_name."[\"".$rec['code']."\"] = new Array();\n";
                    foreach($rec['slave'] as $slave => $slave_rec){
                        $js_array .= "slave_".$slave_name."[\"".$rec['code']."\"][\"".$slave_rec."\"] = '".$slave."';\n";
                    }
                }
            }
        }else{
            $js_array = "";
        }

        global $FEListBoxMaster_js;

        if (!isset($FEListBoxMaster_js)) {
            
            $FEListBoxMaster_js = true;

            $js_str = <<<JSEND
                function change_slave(master, slave, data) {
                    _name = master;
                    len = document.forms[0].elements[_name].length;
                    for (i=0;i<len;i++)
                        if (document.forms[0].elements[_name].options[i].selected)
                            break;
                    val = document.forms[0].elements[_name].options[i].value;
                
                    _name = slave;
                    i=0;
                    if (data[val] == null) {
                        nn = new Option("None");
                        document.forms[0].elements[_name].options[0] = nn;
                        document.forms[0].elements[_name].options[0].value = "None";
                        i++;
                    }
                    else {
                        for (var n in data[val]) {
                            nn = new Option(data[val][n]);
                            document.forms[0].elements[_name].options[i] = nn;
                            document.forms[0].elements[_name].options[i].value = n;
                            i++;
                        }
                    }
                
                    len = document.forms[0].elements[_name].length;
                    for (j=i;j<len;j++)
                        document.forms[0].elements[_name].options[i] = null;
                }

JSEND;
            
        }else{
            $js_str = "";
        }
        return $js_array.$js_str;
    }
    /**
     * this function retuns the javaScript code for
     * an onChange event
     *
     * @return string - javascript code
     */
    function onChange() {
        $master_name = $this->get_element_name();
        $slaves = $this->get_slave_elements();
        $slave = $slaves[0];
        $slave_name = $slave->get_element_name();

        return "change_slave('".$master_name."','".$slave_name."',slave_".$slave_name.")";
    }


}
?>
