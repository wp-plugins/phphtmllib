<?php
/**
 * $Id: XMLDataListDocument.inc 1444 2005-05-12 01:24:05Z hemna $
 * 
 * This file builds a complete XMLDocumentPage
 * from a DataListSource class.
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
require_once($GLOBALS['phphtmllib'].'/widgets/xml/XMLDocumentClass.inc');


/**
 * This class is for generating a complete XML document
 * based off of a DataListSource child class.
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class XMLDataListDocument {

    /**
     * The root xml node name
     */
    var $root_name = 'list';

    /**
     * The xml document class
     * 
     */
    var $xml = NULL;

    /**
     * The name we want for the
     * xml tag for each row we fetch
     * from the DB.
     */
    var $row_name = 'row';

    /**
     * The column we want to orderby in
     * the DataListSource
     */
    var $orderby = NULL;


    /**
     * The datalist source we will use
     */
    var $data_source = NULL;


    /**
     * The constructor
     * 
     * @param string the root xml tag's name
     * @param string the name of the xml tag for each
     *               row pulled from the DataListSource
     * @param string the column to sort by in the DataListSource
     */
    function XMLDataListDocument($root_name, $row_name, $sort_column=NULL) {
        $this->root_name = $root_name;
        $this->row_name = $row_name;
        $this->orderby = $sort_column;

        //so you can later set stuff in it
        $this->build_xml_document();
    }



    function render() {
        //get the datasource
        $this->get_data_source();

        //execute the query
        $this->data_prefetch();

        $this->build_rows();

        return $this->xml->render();
    }

    /**
     * You can override this to call set_data_source()
     * that this class will use.  This method gets
     * called from within render().
     * 
     * @return none
     */
    function get_data_source() {
    }

    /**
     * This function is used to set the
     * DataListSource object for this instance
     *
     * @param DataListSource object
     */
    function set_data_source(&$datasource) {
        $this->data_source =& $datasource;
    }


    /**
     * This method builds the XMLDocumentClass
     * that is used to render the output.
     * 
     * @return none
     */
    function build_xml_document() {
        $this->xml = new XMLDocumentClass($this->root_name, 
                                          $this->dtd,
                                          $this->root_attributes);
    }


    /**
     * This method calls the DataListSource's query to execute the
     * query, just as the DataList class does
     */
    function data_prefetch() {
        $this->data_source->query(0, -1,$this->orderby, FALSE, 
                                  null, null, null, null);
    }


    /**
     * This method is used to pull each row from the DataListSource
     * and then create the xml tags based upon the columns returned
     * and their values
     * 
     * @return none
     */
    function build_rows() {
        while ($row = $this->data_source->get_next_data_row() ) {
            $xml = xml_tag($this->row_name);
            foreach( $row as $column => $value ) {
                $xml->add( xml_tag($column, array(), $value));
            }
            $this->xml->add( $xml );
        }
    }
}
?>
