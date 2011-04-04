<?php

/**
 * This contains the ImageThumbnailTable widget
 *
 * $Id: ImageThumbnailWidget.inc 1444 2005-05-12 01:24:05Z hemna $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */

/**
 * This widget creates a N by x visual table of
 * thumbnails.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib 
 */
class ImageThumbnailWidget extends BaseWidget {

  /**
   * hold the path on disk to image dir
   *
   * @access private
   */
  var $_filedir = NULL;

  /**
   * hold the path on disk to the thumbs
   * that we will create.
   *
   * @access private
   */
  var $_thumbsdir = NULL;

  /**
   * hold the url path to the images
   *
   * @access private
   */
  var $_urldir = NULL;

  /**
   * hold the list of images from disk
   *
   * @access private
   */
  var $_filelist = array();


  /**
   * The number of thumbs to show per page.
   *
   * @access private
   */
  var $_maxthumbsperpage = 10;

  /**
   * The number of columns for a 
   * page.
   *
   */
  var $_columns;


  /**
   * The thumbnail image width.
   *
   * @access private
   */
  var $_thumb_width = 50;

  /**
   * The thumbnail image height.
   *
   * @access private
   */
  var $_thumb_height = 50;

  /**
   * Array of supported image
   * type flags.  
   *
   */
  var $_supported_image_types = array("WBMP" => FALSE,
                                      "PNG" => FALSE,
                                      "JPG" => FALSE,
                                      "GIF" => FALSE);


  /**
   * holds the prefix for all variables
   * that are added to a url,
   * so we can possibly have more
   * then 1 of these per page.
   *
   */
  var $_global_prefix='';

  /**
   * Holds the name of the offset
   * variable.  It's prefixed w/
   * the _global_prefix var.
   */
  var $_offsetVar = 'offset';





  /**
   * Constructor for this class
   * It just sets the width for the
   * widget.
   *
   * @param int $width - the width of the widget
   * @param int $cols - the number of columns of images
   *                    the default is 5.
   */
  function ImageThumbnailWidget( $width = 760, $cols=5, $filedir=NULL, $urldir=NULL) {
      $this->set_width( $width );
      $this->set_cols( $cols );
      $this->set_filedir( $filedir );
      $this->set_urldir( $urldir );

      $this->set_global_prefix('');
      $this->get_supported_image_formats();
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
   * This function sets a prefix for all
   * variables that are used in the item list 
   * table on a page.  This allows you to have
   * multiple itemlists on a single html page.
   *
   * @param string $prefix - the prefix for all vars.
   */
  function set_global_prefix($prefix) {
      $this->_global_prefix        = $prefix;
      $this->_offsetVar            = $prefix . "offset";
  }


  /**
   * Set the url for the thumbnail generation
   * script.
   */
  function set_thumbnail_script( $script ) {
      $this->thumbnail_script = $script;
  }


  /** 
   * Set the full path on disk where
   * the images live.
   */
  function set_filedir( $dir ) {
      $this->_filedir = $dir;
      $this->_thumbsdir = $this->_filedir."/thumbs";
  }

  /**
   * Set the base url path where the files
   * live on the web site.
   */
  function set_urldir( $dir ) {
      $this->_urldir = $dir;
  }

  /**
   * set how many columns the user wants
   * to display per row of thumbnails.
   */
  function set_cols( $cols ) {
      $this->_columns = $cols;
  }

  /**
   * set how many thumbnails to display 
   * per page.
   */
  function set_maxthumbs_per_page( $num=10 ) {
      $this->_maxthumbsperpage = $num;
  }

  /**
   * Make sure the maxthumbsperpage
   * isn't > then total items.
   *
   */
  function test_maxthumbs_per_page() {
      if ($this->_maxthumbsperpage > $this->total_items()) {
          $this->set_maxthumbs_per_page( $this->total_items() );
      }
  }

  /**
   * Sets all thumnail dimensions.
   *
   * @param int $width - thumbnail width
   * @param int $height - thumbnail height
   */
  function set_thumbnail_dimensions( $width=50, $height=50 ) { 
      $this->_thumb_width = $width;
      $this->_thumb_height = $height;
  }


  /**
   * This tests to see what type of gd 
   * lib image format this server supports.
   * 
   */
  function get_supported_image_formats() {

      $flag = imagetypes();
      
      $r['WBMP'] = $flag & IMG_WBMP;
      $r['PNG'] = $flag & IMG_PNG;
      $r['JPG'] = $flag & IMG_JPG;
      $r['GIF'] = $flag & IMG_GIF;

      $this->_supported_image_types = $r;
  }


  /**
   * Get the current value of the offset var
   *
   * @return int - the page offset
   */
  function offset() {
      global ${$this->_offsetVar};
      if ( ! isset(${$this->_offsetVar}) )
          ${$this->_offsetVar} = 0;
      return (int) ${$this->_offsetVar};
  }


  /**
   * Calculates the # of rows
   * per page possible.
   *
   * @return int
   */
  function rows_per_page() {
      if ($this->_columns > $this->total_items()) {
          user_error("ImageThumbnailTable: number of columns per page is larger then the total items to display",
                     E_USER_ERROR);
      }
      $rows = ($this->_maxthumbsperpage / $this->_columns);
      if (($rows > 0) & ($rows < 1)) {
          $rows = 1;
      }
      return (int)$rows;;
  }


  /**
   * Calculate the # of items on a page.
   *
   * @return int
   */
  function items_per_page() {
      $this->test_maxthumbs_per_page();
      return $this->rows_per_page() * $this->_columns;
  }


  /**
   * Calculate the number of 
   * pages possible for this
   * list of thumbnails. It depends
   * on the # of columns, and the
   * max thumbs per page, and the total.
   *
   * @return int - # of pages.
   */
  function num_pages() {
      //get the # of items per page
      $pages = $this->total_items() / $this->items_per_page();
      $rem = $this->total_items() % $this->items_per_page();
      if (($rem) > 1) {
          //xmp_var_dump( $pages );
          $pages = ((int)$pages) + 1;
          //xmp_var_dump( $pages );
      }      
      return $pages;
  }

  /**
   * Is thie offset for the last page?
   *
   * @param int - page offset
   *
   * @return boolean TRUE:FALSE
   */
  function is_last_page( $offset ) {
      return ($offset == ($this->num_pages() - 1));
  }


  /**
   * returns the total # of 
   * items we have to display.
   *
   * @return int - total items.
   */
  function total_items() {
      return count($this->_filelist);
  }

  /**
   * Calculate the # of items
   * to on a particular page.
   *
   * @param int - page offset #
   * @return int - # of items on offset's page.
   */
  function num_items_on_page( $offset ) {
      if ($this->is_last_page( $offset )) {
          $items = $this->total_items() - $this->item_index($offset);
          return $items;
      } else {
          return $this->items_per_page();
      }
  }


  /**
   * Calculate the item # for the offset.
   *
   * @return int
   */
  function item_index( $offset ) {
      return $this->offset() * $this->items_per_page();
  }

   


  /**
   * build the list of images
   * from a directory on disk
   */
  function build_filelist() {
      //First lets get the list
      $this->_filelist = $this->getdirlist( $this->_filedir );
  }


  function getdirlist($dir) {
      $dir=str_replace("%20"," ",$dir);
      $d=array();
      $i=0;
      if(is_dir($dir)) {
          $handle=opendir($dir);
          while ($file = readdir($handle)) {              
              if ($file != "." && $file != "..") { 
                $tmp = strtoupper($file);
                if (strstr($tmp, ".JPG")) {
                  $d[] = $file;
                } elseif (strstr($tmp, ".PNG")){
                  $d[] = $file;
                } elseif (strstr($tmp, ".GIF")) {
                  $d[] = $file;
                }
              }
          }
          closedir($handle); 
      } 
      
      //$di=implode("\n",$d);
      //xmp_var_dump( $d );
      return $d;
}

  /**
   * build the link td.
   *
   */
  function build_link_td( $file ) {

      $img_link = $this->thumbnail_script . "?img=";
      $img_link .= $this->_filedir . "/$file&w=50&h=50";
      $filename = $this->_urldir . "/thumbs/" . $file;

      $img =  html_img($filename, $this->_thumb_width, $this->_thumb_height);

      $link = $this->_urldir . "/" . $file;      
      $a = html_a(htmlentities($link), $img, "treenavnormal");

      $td = new TDtag( array("align" => "left"), $a);
      return $td;
  }


  /**
   * This function strips the offset
   */
  function strip_offset( $query_string ) {

     $arr = explode( '&', $query_string );
     $str = '';

     foreach( $arr as $var ) {
         if (($var != '') && (strncmp($var, $this->_offsetVar,
                                      strlen($this->_offsetVar)) != 0) ) {
           $str .= "&".$var;
         }
     } 
     return $str;
  }  



  function build_page_control() {

      $base_url = $_SERVER["PHP_SELF"]. "?" . $this->strip_offset( $_SERVER["QUERY_STRING"] );

      //we just need to render some links
      //to walk thru the pages
      $total = $this->total_items();
      $num_pages = $this->num_pages();
      $offset = $this->offset();

	  $container = container();

      //ok start to add the links
      if ($offset == 0) {
        //we are looking at the first page.
        $container->add("FIRST");
      } else {
        //we aren't on the first page.
        $container->add( html_a(htmlentities($base_url."&".$this->_offsetVar."=0"), "FIRST", "thumblink") );
      }

      //render the "prev" link
      if ($offset == 0) {
        //we are looking at the first page.
        $container->add( "PREV" );
      } else {
        //we aren't on the first page.
        $page = $offset - 1;
        $container->add( html_a(htmlentities($base_url."&".$this->_offsetVar."=$page"), "PREV", "thumblink") );
      }

      //Render the "next" link
      if ($this->is_last_page($offset)) {
        //we are looking at the first page.
        $container->add("NEXT");
      } else {
        //we aren't on the first page.
        $page = $offset + 1;
        $container->add( html_a(htmlentities($base_url."&".$this->_offsetVar."=$page"), "NEXT", "thumblink"));
      }

      //Render the "Last" link
      if ($this->is_last_page($offset)) {
        //we are looking at the first page.
        $container->add("LAST");
      } else {
        //we aren't on the first page.
        $page = $num_pages - 1;
        $container->add( html_a(htmlentities($base_url."&".$this->_offsetVar."=$page"), "LAST", "thumblink"));
      }

     return $container;
  }



  /**
   * function that will render the widget.
   * child class should override this.
   *
   */
  function build_thumb_table( ) {

	  $table = html_table("100%", 0, 1, 0);
	  $table->set_class( "treenvwrapper" );

      $cnt = $this->total_items();
      $tr = new TRtag;

      //set the index into the page
      $items_this_page = $this->num_items_on_page( $this->offset() );
      $index = $this->item_index($this->offset());
      $per_page = $this->items_per_page();
      for ($i=$index; $i <= $index + $items_this_page; $i++) {
          $tr->add( $this->build_link_td( $this->_filelist[$i] ) );
          
          //xmp_var_dump( (($i+1) % $this->_columns) );
          //xmp_var_dump( $i );
          if (((($i+1) % $this->_columns) == 0) && ($i != 0)) {
              $table->add( $tr );
              $tr = new TRtag;
          } else if (( (($i+1) % $this->_columns) < $this->_columns) &
                     ($i == $index + $items_this_page)) {
              //xmp_var_dump ( $i );
              $table->add( $tr );
          }
      }

      return $table;
  }


  /**
   * Render the entire widget.  this includes the
   * page offset links, as well as the thumbnails.
   *
   * @param int - the indentation level for 
   *              the container.
   * @param int - the output debug flag to 
   *              maintain compatibility w/ the API.
   *
   * @return string the raw html output.   
   */
  function render( $indent_level=1, $output_debug=0 ) {

      //try and build the list of images
      $this->build_filelist();

      $this->build_thumbnails();

	  $images_div = html_div("", $this->build_thumb_table() );
	  $images_div->set_style("float: left;padding-top: 5px;" );
	  $container = container( $page_div, html_br(), $images_div );

	  $fieldset = html_fieldset();
	  $fieldset->set_style("width: ".$this->width);
	  $fieldset->set_id("imagethumbnail");

	  $legend = html_legend($this->build_page_control());
	  $fieldset->add( $legend, $images_div );
      
      return $fieldset->render( $indent_level, $output_debug );
  }



  /**
   * this function builds a cache dir of thumbnails, so we
   * don't have to render thumbnails every time we hit the
   * thumbnails page.
   *
   */
  function build_thumbnails() {

      //first make sure the thumnail cache dir
      //exists.
      //Lets try and create it.
      $this->_create_thumbnail_cache_dir();

      set_time_limit(120);

      //ok lets walk through each file,
      //create the resized image, and write it
      //to disk.
      $index = $this->item_index($this->offset());
      $items_this_page = $this->num_items_on_page( $this->offset() );
      for ($i=$index; $i <= $index + $items_this_page; $i++) {
          $this->build_thumbnail_file( $this->_filelist[$i] );
      }
  }


  /**
   * Builds a thumbnail version of a file,
   * and writes it to disk.
   *
   * @param string $filename - the filename to thumbnail
   */
  function build_thumbnail_file( $file ) {
      $filename = $this->_filedir . "/" . $file;
      $thumbname = $this->_thumbsdir . "/" . $file;
      
      if (!file_exists($thumbname)) {
          $type = $this->_get_file_type( $file );      

          //we currently support jpeg and png.
          // Create the image...
          switch( strtolower($type) ) {
              case 'jpg':
                $orig_img = imagecreatefromjpeg($filename);
                break;

              case 'png':
                $orig_img = imagecreatefrompng($filename);
                break;

              default:
                echo 'Error: Unrecognized image format.';
                exit();
                break;
          }
          
          //Ok we have an Image, lets resize it.
          $o_width = imagesx ($orig_img);    // Original image width
          $o_height = imagesy ($orig_img);    // Original image height

          $img = imagecreate($this->_thumb_width, $this->_thumb_height);
          imagecopyresized($img, $orig_img, 0, 0, 0, 0, 
                           $this->_thumb_width, $this->_thumb_height,
                           $o_width, $o_height);
          imagedestroy($orig_img);

          //Now lets write the image to disk
          $this->write_thumb_to_disk( $file, $img, $type );          
      }
  }


  /**
   * discover the type of image based off of the extension
   *
   * @param string $filename - the filename
   */
  function _get_file_type( $file ) {
      $ext = explode('.', $file);
      $ext = $ext[count($ext)-1];
      switch( strtolower($ext) ) {
          case 'jpeg'  :
            $type = 'jpg';
            break;
            
          default :
            $type = $ext;
            break;
      }

      return $type;
  }


  /**
   * write the image to disk.
   * We assume we have write permissions
   * to the images dir.
   *
   */
  function write_thumb_to_disk( $file, &$img, $type ) {

      $filename = $this->_thumbsdir . "/" . $file;
      
      //now lets write file to disk.
      switch( strtolower($type) ) {
        case 'jpg':            
            imagejpeg($img, $filename);
            break;

        case 'png':
            imagepng($img, $filename);
            break;
      }
      imagedestroy($img);
  }

  /**
   * Try and create the thumbnail cache dir.
   *
   */
  function _create_thumbnail_cache_dir() {
      $oldmask = umask(0);
      $ret = @mkdir($this->_thumbsdir, 0755);
      @chmod($this->_thumbsdir, 0755);
      umask($oldmask);
  }
}


/**
 * This class defines the css used by the 
 * FooterNav Object.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib 
 */
class ImageThumbnailWidgetCSS extends CSSBuilder {

	function user_setup() {
		$this->add_entry(".imagethumbnail", "",
						 array("margin" => "0px 0px 0px 0px",
							   "font-family" => "arial, helvetica, sans-serif",
							   "font-size" => "10pt",
							   "border" => "1px solid #999999") );

		$this->add_entry(".imagethumbnail", "legend",
						 array("font-size" => "10pt",
							   "font-weight" => "bold",
                               "color" => "#000000"));

		$this->add_entry(".imagethumbnail", "a.thumblink:active,a.thumblink:link,a.thumblink:visited",
						 array("font-size" => "10pt",
							   "font-weight" => "bold",
							   "color" => "#999999",
							   "background" => "#FFFFFF"));

		$this->add_entry(".imagethumbnail", "a.thumblink:hover",
						 array("font-size" => "10pt",
							   "font-weight" => "bold",
							   "color" => "#4141FF",
							   "background" => "#eeeeee",
							   "text-decoration" => "none"));
		$this->add_entry(".imagethumbnail", "table",
						 array("padding-left" => "5px"));
	}	
}
?>
