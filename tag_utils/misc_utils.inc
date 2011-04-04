<?php
/* vim: set expandtab tabstop=4 shiftwidth=4: */
/**
 * This file contains miscellaneous functions
 * used by the phpHtmllibs that don't seem to
 * fit in the other files.
 *
 * $Id: misc_utils.inc 3083 2007-10-31 03:00:43Z mpwalsh8 $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 * 
 */

/**
 * This builds an IMG tag object that is used
 * to show a spacer image.
 * <img src="spacer.gif" width="$width" height="$height">
 *
 * @param   int $width - the width of the img
 *                       ( DEFAULT : 1)
 * @param   int $height - the height of the img
 *                       ( DEFAULT : 1)
 * @param   string  $img_path - The dir that holds the spacer.gif file.
 *                              ( DEFAULT = "/images" )
 * @return  IMGtag object.
 */
function build_spacergif_imgtag( $width=1, $height=1, $img_path="/images" ) {
    $attributes = array( "src" => $img_path."/spacer.gif",
                         "width" => $width,
                         "height" => $height);
    return html_img( $img_path."/spacer.gif", $width, $height );
}

/**
 * This function pushes an array of keys
 * into an HTMLTagObject
 *
 * @param object - the HTMLTagClass object.
 * @param array - the array of data to push
 *                array("blah", "foo", "bar");
 * @return HTMLTagClass object.
 */
function push_args( $tag_object, $args ) {
    foreach ($args as $content) {
        $tag_object->push( $content );
    }
    return $tag_object;
}



/**
 * This function creates a new container widget
 * and stuffs all the args into it.
 *
 * @param mixed - variable # of args
 * @return ContainerWidget object
 */
function container() {
    $container = new ContainerWidget;

    $num_args = func_num_args();
    for ($i=0;$i<$num_args;$i++) {
        $container->push(func_get_arg($i));
    }
    return $container;
}


/**
 * This function is used to wrap 
 * a string in the standard 
 * CDATA section wrapper for a 
 * tag content
 *
 * <![CDATA[ CONTENT ]]>
 *
 * @param string the content to wrap
 */
function cdata_wrapper( $content ) {
	$tag = new CDATAtag;

	$num_args = func_num_args();
    for ($i=0;$i<$num_args;$i++) {
        $tag->push(func_get_arg($i));
    }
	return $tag;
}

/**
 * This function is used to replicate the information
 * provided by $_SERVER['REQUEST_URI'] which isn't
 * provided by IIS.
 *
 * If the value is available, it is used, of not, it
 * is constructed.
 *
 * @return string - the REQUEST_URI value
 */
function phl_request_uri() 
{ 
   if (!empty($_SERVER['REQUEST_URI'])) 
   { 
      return $_SERVER['REQUEST_URI']; 
   } 
   else 
   { 
      $uri = $_SERVER['SCRIPT_NAME']; 
      if (!empty($_SERVER['QUERY_STRING'])) 
      { 
         $uri .= '?'.$_SERVER['QUERY_STRING']; 
      } 
      $_SERVER['REQUEST_URI'] = $uri; 
      return $uri; 
   } 
}

/**
 * Determine if a URL exists.  Code derived from
 * code found on www.php.net/fsockopen.
 *
 * @param string - URL
 * @return boolean - true if exists, false otherwise
 */
function phl_url_exists($url)
{
    if (!$url_info = parse_url($url))
    {
        return false ;
    }
        
    switch ($url_info['scheme'])
    {
        case 'https':
            $scheme = 'ssl://' ;
            $port = 443 ;
            break;
        case 'http':
        default:
            $scheme = '' ;
            $port = 80 ;
    }
        
    $data = "";
    $fid = @fsockopen($scheme . $url_info['host'], $port, $errno, $errstr, 30) ;

    if ($fid)
    {
        fputs($fid, 'HEAD ' . (isset($url_info['path'])? $url_info['path']: '/') . (isset($url_info['query'])? '?' . $url_info['query']: '') . " HTTP/1.0\r\n" . 
                        "Connection: close\r\n" . 
                        'Host: ' . $url_info['host'] . "\r\n\r\n");    
        while (!feof($fid))
        {
            $data .= @fgets($fid, 128);
        }
        fclose($fid);
        return !empty($data);
    }
    else
    {
        return false;
    }
} 

?>
