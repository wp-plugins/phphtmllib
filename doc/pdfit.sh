#!/bin/bash
cd ..;
BASEDIR=`pwd`;
export BASEDIR;
cd doc;

/usr/local/bin/PhpDocumentor/phpdoc  -o PDF:default:phphtmllib \
-t $BASEDIR/doc \
-d $BASEDIR -dn phpHtmlLib \
-ti phpHtmlLib \
-i includes.inc,test*,localinc.php,thumbnail.php,bluetheme.php,redtheme.php,defaulttheme.php,css.php
