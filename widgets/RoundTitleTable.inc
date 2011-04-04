<?php
/**
 * This contains the RoundTitleTable widget
 *
 * $Id: RoundTitleTable.inc 3139 2008-08-18 20:22:54Z mpwalsh8 $
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
 * This builds a table
 * widget that has a nice rounded title,
 * a subtitle area and any amount of data.
 * 
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class RoundTitleTable extends BaseWidget {


  /**
   * the constructor for this class.
   * @param string  $title - the title for the widget.
   * @param string  $subtitle - the subtitle if any.
   * @param mixed   $width - the width of the widget.
   *                         can be a % or an int.
   */
  function RoundTitleTable( $title, $subtitle=NULL, $width="100%") {

    $this->set_title( $title );
    $this->set_subtitle( $subtitle );
    $this->set_width( $width );
  }


  function set_subtitle( $subtitle ) {
      $this->subtitle = $subtitle;
  }


  //******************************************
  //*   rendering area
  //******************************************


  /**
   * renders a title table for the widget.
   * @access private
   */
  function render_title_table() {
      $table = html_table($this->width,0 ,0 ,0);
      
      //ok lets render the title table.
      $img = html_img(PHPHTMLLIB_RELPATH . "/widgets/images/spacer.gif", 10, 15);

	  $td = html_td("barleft", "left", $img );
	  $td->set_collapse();
	  $td2 = html_td("title", "", $this->title);
	  $td2->set_collapse();
	  $td3 = html_td("barright", "right", $img);
	  $td3->set_collapse();

      $table->add_row( $td, $td2, $td3 );
      return $table;
  }

  /**
   * this function builds the subtitle td
   * to hold the...subtitle!
   *
   * @return TDtag object
   */
  function _build_subtitle() {
	  $td = html_td("subtitle", "", $this->subtitle);
	  $td->set_tag_attribute("colspan", 2);
	  $td->set_collapse();
	  return $td;
  }


  /**
   * Render the Navtable and its content.
   *
   * @param int - the indentation level for 
   *              the container.
   * @param int - the output debug flag to 
   *              maintain compatibility w/ the API.
   *
   * @return string the raw html output.
   */
  function render( $indent_level=1, $output_debug=0 ) {

	  $span = html_div();
	  $span->set_class("roundtitletable");	  
      
      $html = "";

      //render the title area first.
      $title = $this->render_title_table();
	  $span->add( $title );
      
	  $table = html_table($this->width, 0, 0, 2);
	  $table->set_class("content");
      
	  if ($this->subtitle) {
		  $table->add_row( $this->_build_subtitle() );
	  }

	  //build the containing TD
	  $container_td = html_td();

	  foreach ($this->_content as $val) {
		  $container_td->add( $val );
      }
	  $table->add_row( $container_td );

	  $span->add( $table );

	  return $span->render( $indent_level, $output_debug);
  }
}

/**
 * This class defines the css used by the 
 * RoundTitleTable Object.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib 
 */
class RoundTitleTableCSS extends CSSBuilder {

	function user_setup() {
		$this->add_entry(".roundtitletable", NULL, 
						 array("font-family" => "arial,verdana,helvetica") );

		$this->add_entry(".roundtitletable", ".title",
						 array("font-size" => "10pt",
							   "font-weight" => "bold",
							   "text-align" => "center",
							   "color" => "#FFFFFF",
							   "background-color" => "#999999",
							   "width" => "98%") );

		$this->add_entry(".roundtitletable", ".barleft",
						 array("background-image" => "url(" . PHPHTMLLIB_RELPATH . "/widgets/images/top-left-corner.gif)",
							   "background-repeat" => "no-repeat",
							   "background-color" => "#999999",
							   "width" => "1%"));

		$this->add_entry(".roundtitletable", ".barright",
						 array("background-image" => "url(" . PHPHTMLLIB_RELPATH . "/widgets/images/top-right-corner.gif)",
							   "background-repeat" => "no-repeat",
							   "background-color" => "#999999",
							   "width" => "1%"));

		$this->add_entry(".roundtitletable", ".content",
						 array("border" => "1px solid #777777;",
							   "background-color" => "#FFFFFF") );

		$this->add_entry(".roundtitletable", ".subtitle",
						 array("font-size" => "8pt",
							   "font-weight" => "bold",
							   "text-align" => "center",
							   "color" => "#777777",
							   "background-color" => "#eeeeee") );
	}	
}

?>
