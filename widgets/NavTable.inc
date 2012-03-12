<?php
/**
 * This contains the InfoTable widget
 *
 * $Id: NavTable.inc 3130 2008-08-12 14:07:41Z mpwalsh8 $
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
 * This builds a navigational table
 * widget that has a title, any #
 * of subtitles and then navigational
 * links.
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class NavTable extends BaseWidget {


  /**
   * The name of the css file for this class
   * 
   * @access private
   * @var string
   */
  var $_css_file = "NavTable.php";

  /**
   *  Array to hold the css customizable 
   *  colors for themeing.
   *  Each widget will have its own set of
   *  customizable css colors with defaults.
   *  the user can programatically modify the
   *  colors by setting them in this array.
   *
   * @access private
   * @var array
   */
  var $_css_entities = array("title"=> "#666699",
							 "titlefont" => "#FFFFFF",
							 "subtitle" => "#9999CC",
							 "subtitlefont" => "#0000CC");


  /**
   * the constructor for this class.
   * @param string  $title - the title for the widget.
   * @param string  $subtitle - the subtitle if any.
   * @param mixed   $width - the width of the widget.
   *                         can be a % or an int.
   */
  function NavTable( $title, $subtitle=NULL, $width="100%") {

    $this->set_title( $title );
    $this->set_subtitle( $subtitle );
    $this->set_width( $width );
  }


  function set_subtitle( $subtitle ) {
      $this->subtitle = $subtitle;
  }

  //functions for adding/updating data

  /**
   * this function adds an entry to the navtable.
   * It automatically adds the link based on $url,
   * with $text as the viewable text.
   *
   * @param string - the url for the link
   * @param string - the link text
   * @param string - the link title text
   * @param string - the link target   
   */
  function add($url, $text, $title=NULL, $target=NULL) {
      array_push($this->data, array("type"=>"url", 
									"url"=>$url, 
									"text"=>$text, 
									"target"=>$target,
									"title"=>$title));
  }

  /**
   * depricated version of add()
   *
   * @deprecated - use add() instead
   */
  function push($url, $text, $title=NULL, $target=NULL) {
      $this->add($url, $text, $title, $target);
  }

  /**
   * This lets you add a blank line
   * between 2 links
   *
   * @param int - the # of blank lines to insert
   */
  function add_blank( $num = 1 ) {
    for ($x=1; $x<=$num; $x++)
       array_push($this->data, array( "type"=>"blank" ));
  }

  /**
   * depricated version of add_blank()
   *
   * @deprecated - use add_blank() instead
   */
  function push_blank( $num=1 ) {
      $this->add_blank( $num );
  }

  /**
   * this adds a text item in the nav
   * 
   * @param string - the text to display
   */
  function add_text( $text ) {
      array_push($this->data, array( "type"=>"text", "text"=>$text ));
  }
  
  /**
   * depricated version of add_text()
   *
   * @deprecated - use add_text() instead
   */
  function push_text( $text ) {
      $this->add_text( $text );
  }

  /**
   * This adds a new heading in the nav.
   * It will look just like the sub title area
   *
   * @param string - the text in the heading
   */
  function add_heading( $title ) {
      array_push($this->data, array( "type" => "heading", "title" => $title ));
  }

  /**
   * depricated version of add_heading()
   *
   * @deprecated - use add_heading() instead
   */
  function push_heading( $title ) {
      $this->add_headring( $title );
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
   * render a blank tr
   * @access private
   */
  function _render_blank_tr() {
      $tr = new TRtag;
      $space = "&nbsp;&nbsp;";

      $td = new TDtag( array( "style" => "width:1%;", "class" => "navtablediv"), $space );
      $td2 = new TDtag( array( "style" => "width:99%;", "class" => "navtablediv"), $space );

      $tr->add( $td, $td2 );
	  $tr->set_collapse();

      return $tr;
  }

  /**
   * render a url row.
   * @param array() - the item to render.
   */
  function _render_url( $val ) {
      $tr = new TRtag;
      $bullet = "&bull;&nbsp;&nbsp;";

      $tr->add( html_td("bullet", "", $bullet) );

      $url_td = new TDtag( array("class" => "link") );

      $attributes = array("href" => $val["url"]);
      if ($val["target"] != NULL) {
          $target = $val["target"];
      } else {
          $target = "";
      }
      $url = html_a( $val["url"], $val["text"], NULL, $target, $val["title"]);
      
      $url_td->add( $url );
      $tr->add( $url_td );
	  $tr->set_collapse();

      return $tr;
  }

  /**
   * render a text row.
   * @param array() - the item to render.
   */
  function _render_text( $val ) {
      $tr = new TRtag;
      $bullet = "&bull;&nbsp;&nbsp;";

      $td = html_td("bullet", "", $bullet);
	  $text_td = html_td("link", "", $val["text"] );
      
      $tr->add( $td, $text_td );
	  $tr->set_collapse();

      return $tr;
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
	  $span->set_class("navtable");	  
      
      $html = "";

      //render the title area first.
      $title = $this->render_title_table();
	  $span->add( $title );
      
	  $table = html_table($this->width, 0, 0, 2);
	  $table->set_class("content");
      
	  if ($this->subtitle) {
		  $table->add_row( $this->_build_subtitle() );
	  }

	  foreach ($this->data as $key=>$val) {
          switch ($val["type"]) {
              case "blank":
                  $table->add_row( $this->_render_blank_tr() );
                  break;

              case "url":
                  $table->add_row( $this->_render_url( $val ) );
                  break;

              case "text":
                  $table->add_row( $this->_render_text( $val ) );
                  break;

              case "heading":
                  $this->set_subtitle( $val['title'] );
                  $table->add_row( $this->_build_subtitle() );
                  break;
          }
      }

	  $span->add( $table );

	  return $span->render( $indent_level, $output_debug);
  }
}

/**
 * This class defines the css used by the 
 * FooterNav Object.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib 
 */
class NavTableCSS extends CSSBuilder {

	function user_setup() {
		$this->add_entry(".navtable", NULL, 
						 array("font-family" => "arial,verdana,helvetica") );

		$this->add_entry(".navtable", ".title",
						 array("font-size" => "10pt",
							   "font-weight" => "bold",
							   "text-align" => "center",
							   "color" => "#FFFFFF",
							   "background-color" => "#999999",
							   "width" => "98%") );

		$this->add_entry(".navtable", ".barleft",
						 array("background-image" => "url('" . PHPHTMLLIB_RELPATH . "/widgets/images/top-left-corner.gif')",
							   "background-repeat" => "no-repeat",
							   "background-color" => "#999999",
							   "width" => "1%"));

		$this->add_entry(".navtable", ".barright",
						 array("background-image" => "url('" . PHPHTMLLIB_RELPATH . "/widgets/images/top-right-corner.gif')",
							   "background-repeat" => "no-repeat",
							   "background-color" => "#999999",
							   "width" => "1%"));

		$this->add_entry(".navtable", ".content",
						 array("border" => "1px solid #777777",
							   "background-color" => "#FFFFFF") );

		$this->add_entry(".navtable", ".subtitle",
						 array("font-size" => "8pt",
							   "font-weight" => "bold",
							   "text-align" => "center",
							   "color" => "#777777",
							   "background-color" => "#eeeeee") );

		$this->add_entry(".navtable", ".bullet",
						 array("width" => "1%",
							   "font-size" => "10pt",
							   "padding-left" => "5px"));

		$this->add_entry(".navtable", ".link",
						 array("width" => "99%",
							   "font-size" => "10pt",
							   "line-height" => "11pt"));

		$this->add_entry(".navtable", "a:active,a:link,a:visited",
						 array("font-weight" => "bold",
							   "color" => "#505dd8") );
		$this->add_entry(".navtable", "a:hover",
						 array("color" => "#505dd8",
							   "background-color" => "#eeeeee",
							   "text-decoration" => "none") );
	}	
}

?>
