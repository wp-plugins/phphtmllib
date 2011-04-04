#!/bin/bash
cd ..;
BASEDIR=`pwd`;
export BASEDIR;
cd doc;

/usr/local/bin/phpdoc -o XML:DocBook/peardoc2:default \
-j \
-q \
-s \
-t $BASEDIR/docxml \
-d $BASEDIR -dn phpHtmlLib \
-ti phpHtmlLib \
-i includes.inc,test*,localinc.php,thumbnail.php,bluetheme.php,redtheme.php,defaulttheme.php,css.php
