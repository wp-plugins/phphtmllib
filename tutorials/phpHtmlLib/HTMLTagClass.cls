<refentry id="{@id}">
 <refnamediv>
  <refname>HTMLagClass</refname>
  <refpurpose>This is the base HTML Tag class.</refpurpose>
 </refnamediv>
 <refsynopsisdiv>
  <refsynopsisdivinfo>
   <author>
    by Walter A. Boring IV
     <authorblurb>{@link mailto:waboring@3gstech.com}</authorblurb>
    </author>
   <copyright>&copy; September 2005, Walter A. Boring IV</copyright>
   <releaseinfo>phpHtmlLib 2.5.4</releaseinfo>
  </refsynopsisdivinfo>
 </refsynopsisdiv>

 <refsect1 id="{@id description}">
  <title>Description</title>
  <para>This class is a child of the {@tutorial XMLTagClass.cls}.  It has all of the functionality for building all of the various
  HTML tags in either HTML mode or XHTML mode.  Each HTML tag has specific attributes that make it unique, and this class
  provides the framework for all of those features.  Each actual HTML tag is a child of this class that specifies the specific
  attributes and quirks for itself.</para>
  <para> Each W3C supported HTML tag is specified as a child of the HTMLTagClass in the phpHtmlLib tag_classes/ALLTAGS.inc file.
  You should look there to see the particulars on how each supported HTML tag is different from one another.</para>
  </refsect1>

 <refsect1 id="{@id constructor}">
  <title>Creating an HTML tag object.</title>
  <para>
      <para>Since each W3C supported HTML tag is already defined as a child of the HTMLTagClass, we just
      create the specific tag object that we are interested in.</para>
      <para> Each HTML Tag that phpHtmlLib supports is a class that is defined as follows:
        {TAGNAME}tag().  So if you want an img tag the class name is
        IMGtag.  Lets look at an example for an anchor tag.</para>
   <example>
   <![CDATA[
$a = new Atag( array('href'" => "http://phphtmllib.newsblob.com"),
                 'phpHtmlLib website');
print $a->render();]]>
   </example>
  </para>

   <para>Output:
   <example><![CDATA[<a href="http://phphtmllib.newsblob.com">phpHtmlLib website</a>]]></example>
   </para>

 </refsect1>

 <refsect1 id="{@id helper}">
  <title>Creating a HTML tag object with a helper function.</title>
  <para>
      <para>Each HTML tag also has a 'helper' function defined to help build the tag
      with parameters that are for the most common attributes/values for each specific tag.
      The function name is always in the format of
      html_{tagname}().   So an anchor tag function would be as follows.</para>
   <example>
   <![CDATA[$a = html_a("http://phphtmllib.newsblob.com", 'phpHtmlLib website');
print $a->render();]]>
   </example>
  </para>

   <para>Output:
   <example><![CDATA[<a href="http://phphtmllib.newsblob.com">phpHtmlLib website</a>]]></example>
   </para>
 </refsect1>

</refentry>
