#!/bin/bash
cd ..;
BASEDIR=`pwd`;
export BASEDIR;
cd doc;

/usr/local/bin/phpdoc -o HTML:default:phphtmllib \
-j \
-q \
-s \
-t $BASEDIR/doc \
-d $BASEDIR -dn phpHtmlLib \
-ti phpHtmlLib \
-i includes.inc,test*,localinc.php,thumbnail.php,bluetheme.php,redtheme.php,defaulttheme.php,css.php
