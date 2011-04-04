<?php
/**
 * This contains the TreeNav widget
 *
 * $Id: TreeNav.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */

/**
 * must have the BaseWidget
 */
require_once(PHPHTMLLIB_ABSPATH . "/widgets/BaseWidget.inc");

/**
 * This class tries to build a tree 
 * navigational widget.
 * definetly not done.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib 
 */
class TreeNav extends BaseWidget {

  /**
   * Constructor for this class
   * It just sets the width for the
   * widget.
   *
   * @param int $width - the width of the widget
   */
  function TreeNav( $width = 760 ) {
      $this->set_width( $width );
  }


  //functions for adding/updating data

  function push($url, $text, $selected=FALSE) {
    array_push($this->data, array("type"=>"url", "url"=>$url,
                                 "text"=>$text, "selected" => $selected));
  }

  function push_blank( $num=1 ) {
    for ($x=1; $x<=$num; $x++)
       array_push($this->data, array( "type"=>"blank" ));
  }

  function push_text( $text, $selected=FALSE ) {
      array_push($this->data, array( "type"=>"text", "text"=>$text,
                                     "selected" => $selected ));
  }

  /**
   * Set this text as the selected
   * item
   *
   * @param string $text - the text item selected.
   */
  function set_selected( $text ) {
      //ok find the
  }

  /**
   * build the image seperator td
   *
   */
  function build_img_td() {

      $td = new TDtag;
      $td->newline_after_opentag = FALSE;
      $img =  html_img(PHPHTMLLIB_RELPATH . "/widgets/images/arrow.gif", 9, 9);
      $img->set_tag_attributes( array("vspace"=>5, "hspace"=>3));
      $img->indent_flag = FALSE;
      $img->newline_after_opentag = FALSE;
      $td->push( $img );
      return $td;
  }

  /**
   * build the link td.
   *
   */
  function build_link_td( $nav ) {
      $span = html_span();
      $span->indent_flag = FALSE;
      $span->newline_after_opentag = FALSE;
      $span->newline_after_closetag = FALSE;

      $a = html_a($nav["url"], $nav["text"], "treenavnormal");

      $td = new TDtag( array("width" => "100%"), $a );

      return $td;
  }

  /**
   * build a spacer td.
   *
   */
  function build_spacer_td() {

      $attributes = array("colspan" => 3,
                          "class" => "treenavspacer");
      $td = new TDtag( $attributes );
      $td->newline_after_opentag = FALSE;
      $img =  html_img(PHPHTMLLIB_RELPATH . "/widgets/images/spacer.gif", 1, 1);
      $img->indent_flag = FALSE;
      $img->newline_after_opentag = FALSE;
      $td->push( $img );
      return $td;
  }


  /**
   * build all of the idividual nav elements.
   *
   */
  function build_innertable() {

      $attributes = array( "width" => $this->width,
                           "cellspacing" => 0,
                           "cellpadding" => 0,
                           "border"=>0,
                           "class" => "treenavinnertable");
      $table = new TABLEtag( $attributes );

      foreach( $this->data as $nav) {
          $img_td = $this->build_img_td();
          $link_td = $this->build_link_td( $nav );

          $table->push_row( $img_td, $link_td, "&nbsp;");

          $spacer_td = $this->build_spacer_td();
          $table->push_row( $spacer_td );
      }

      return $table;
  }



  /**
   * function that will render the widget.
   *
   * @param int - the indentation level for 
   *              the container.
   * @param int - the output debug flag to 
   *              maintain compatibility w/ the API.
   *
   * @return string the raw html output.
   *
   */
  function render( $indent_level=1, $output_debug=0) {
      $attributes = array( "border" => 0, "width" => $this->width,
                           "cellpadding" => 0, "cellspacing" => 1,
                           "class" => "treenavwrapper" );
      $table = new TABLEtag( $attributes );
      $tr = new TRtag;

      //Ok now build the content.

      $tr->push( $this->build_innertable() );

      $table->push( $tr );

      return $table->render( $indent_level, $output_debug );
  }
}
?>
