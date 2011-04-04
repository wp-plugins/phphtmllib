<?php
/**
 * This file contains the HTMLRedirectPage class
 *
 * $Id: HTMLRedirectPage.inc 1636 2005-11-29 00:55:08Z sumedh_thakar $
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */


/**
 * This builds an entire HTML Page
 * with the sole purpose of doing a redirect to another url.
 *
 * @author Walter A. Boring IV <waboring@newsblob.com>
 * @package phpHtmlLib
 */
class HTMLRedirectPage extends HTMLPageClass {

    /**
     * The constructor
     *
     * @param string - the title of the page
     * @param string - the url to redirect to
     * @param boolean - do we show the fallback message?
     * @param boolean - do we want to destroy a frameset
     *                  with the redirect?
     * @param boolean - do we want to use a Javascript 
     *                  window.location call?
     */
    function HTMLRedirectPage($title, $url, $showMessage=false,
                              $destroy_frameset=FALSE,
                              $usejs=TRUE) {
        $this->HTMLPageClass($title);
        $this->set_refresh(0,$url);

        if ($usejs) {
            if ($destroy_frameset) {
                $this->add_head_js("top.location = '".$url."';");
            } else {
                $this->add_head_js("window.location = '".$url."';");
            }
        }        

        if ($showMessage) {
            //add helper link
            $p = html_p("If you are not automatically redirected, ",
                        "please click ",
                        html_a($url, "here"));
            $p->set_collapse();
            $this->add( $p );
        }
    }
}
?>
