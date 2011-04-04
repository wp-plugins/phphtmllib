#!/bin/bash


VERSION='2.4.1'


#the tar line doesn't use these variables!!
XMLFILE='/tmp/package.xml'
LIBDIR="/tmp/phphtmllib-$VERSION"
ARCHIVE="/tmp/phphtmllib-$VERSION.tgz"


rsync -az ../../phphtmllib/ $LIBDIR

(
cat <<EOF
<?xml version="1.0" encoding="ISO-8859-1" ?>
<package version="1.0">
 <name>phphtmllib</name>
 <summary>A set of PHP classes and library functions to help facilitate building, debugging, and rendering of XML, HTML, XHTML, WAP/WML Documents, and SVG (Scalable Vector Graphics) images as well as complex html 'widgets'.</summary>
 <description>
 phpHtmllib is a set of PHP classes and library functions to help facilitate building, debugging, and rendering of XML, HTML, XHTML WAP/WML Documents, and SVG (Scalable Vector Graphics) images as well as complex html 'widgets'.
 </description>
 <license>LGLP</license>
 <maintainers>
  <maintainer>
   <user>walt</user>
   <name>Walter A. Boring IV</name>
   <email>waboring@newsblob.com</email>
   <role>lead</role>
  </maintainer>
 </maintainers>
 <release>
  <version>$VERSION</version>
  <date>2004-08-03</date>
  <state>stable</state>
  <notes>
   This is the first release as a pear package
  </notes>
  <filelist>
EOF
) > $XMLFILE

#    -e 's/^\.\.\/\//    <file role="JELLYROLE" baseinstalldir="phphtmllib" name="/' \
#    -e '/\.inc/s/JELLYROLE/php/' \
#    -e '/name="images/s/JELLYROLE/data/' \
#    -e '/name="scripts/s/JELLYROLE/script/' \
#    -e '/\.php/s/JELLYROLE/php/' \
#    -e '/\.gif/s/JELLYROLE/data/' \
#    -e '/\.csv/s/JELLYROLE/data/' \
#    -e '/\.css/s/JELLYROLE/data/' \
#    -e '/\.txt/s/JELLYROLE/data/' \
#    -e '/name="tutorials/s/JELLYROLE/doc/' \
#    -e '/JELLYROLE/d' \

find ../ -type f -print | \
    sed -e '/CVS/d' \
    -e 's/^\.\.\/\//    <file role="JELLYROLE" baseinstalldir="phphtmllib" name="/' \
    -e '/name="doc/s/JELLYROLE/doc/' \
    -e '/name="CHANGELOG/s/JELLYROLE/doc/' \
    -e '/name="INSTALL/s/JELLYROLE/doc/' \
    -e '/name="SECURITY/s/JELLYROLE/doc/' \
    -e '/name="README/s/JELLYROLE/doc/' \
    -e '/name="TODO/s/JELLYROLE/doc/' \
    -e '/name="LICENSE/s/JELLYROLE/doc/' \
    -e 's/JELLYROLE/php/' \
    -e 's/$/"\/>/' \
>> $XMLFILE
#    -e '1,1d' \

(
cat <<EOF
  </filelist>
 </release>
</package>
EOF
) >> $XMLFILE

cd /tmp
tar -czf phphtmllib-$VERSION.tgz package.xml phphtmllib-$VERSION
#mv phphtmllib-$VERSION.tgz $PWD

rm $XMLFILE
rm -rf $LIBDIR
