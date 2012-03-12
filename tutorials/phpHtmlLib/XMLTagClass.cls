<refentry id="{@id}">
 <refnamediv>
  <refname>XMLTagClass</refname>
  <refpurpose>This is the base tag class.</refpurpose>
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
  <para>This class is the main tag class for all XML tags that phpHtmlLib supports.</para>
  <para>Each XML tag is broken down into it's name, attributes, content and an optional
  closing tag.  This is also true for HTML tags.</para>
 </refsect1>

 <refsect1 id="{@id constructor}">
  <title>Creating an XML tag object.</title>
  <para>
      <para>The constructor of the XML tag object has 3 main parameters.
      The first parameter is the name of the tag to create.  The second parameter is an array
      of key value pairs that make up the attributes and values for the tag. The third parameters is
      an infinite list of parameters that will make up the content portion of the tag.</para>
   <example>
   <![CDATA[$test = new XMLTagClass('foo', array('test' => 1), 'some content');
print $test->render();]]>
   </example>
  </para>

   <para>Output:
   <example><![CDATA[<foo test="1">some content</foo>]]></example>
   </para>

 </refsect1>

 <refsect1 id="{@id helper}">
  <title>Creating an XML tag object with a function.</title>
  <para>
      <para>The alternative way to create the same xml tag can be accomplised with a call
      to xml_tag().</para>
   <example>
   <![CDATA[$test = xml_tag('foo', array('test' => 1), 'some content');
print $test->render();]]>
   </example>
  </para>

   <para>Output:
   <example><![CDATA[<foo test="1">some content</foo>]]></example>
   </para>

 </refsect1>

  <refsect1 id="{@id closetag}">
  <title>Closing tag</title>
  <para>
      <para>The XMLTagClass automatically determines if the closing tag is needed.  If there is content in the tag,
      then a closing tag is built, otherwise it closes the tag in the open tag.

      NOTE: you can force a close tag to be required by defining a child of the XMLTagClass and setting
      the flag the forces the close tag.</para>
   <example>
   <![CDATA[$test = xml_tag('foo', array('test' => 1));
print $test->render();]]>
   </example>
  </para>

   <para>Output:
   <example><![CDATA[<foo test="1" />]]></example>
   </para>
 </refsect1>

</refentry>
