<refentry id="{@id}">
 <refnamediv>
  <refname>Container</refname>
  <refpurpose>This is the base class for all of phpHtmlLib</refpurpose>
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
  <para>This class is nothing more then a container widget.  It lets you
   push data into it, and it will render each item indented properly so it works with the rest of the libs.</para>
  <para>This is helpfull when you have a function that wants to return multiple Tag Objects
   or widgets.  Just wrap them in this container
   and they will all get rendered with the current indentation level.</para>
 </refsect1>
 <refsect1 id="{@id example}">
  <title>Example</title>
  <para>
   <example>
   <![CDATA[
  $c = container('this is a', html_b('test') );
  $c->add( html_br() );
  print $c->render();]]>
   </example>
  </para>
 </refsect1>

 <refsect1 id="{@id constructor}">
  <title>Constructor call</title>
  <para>
      <para>This lets you pass in data that you want automatically
       added to the container.  You can add as man items in the
       call the constructor.  Then you can use the add() method
       to add more items later.</para>
   <example>
   <![CDATA[$c = container('this is a', html_b('test'));]]>
   </example>
  </para>
 </refsect1>
 <refsect1 id="{@id add}">
  <title>add Method</title>
  <para>
      <para>This lets you add new data to the container. You can pass in
      strings, integers and other Container child objects that implement the
      render() method.</para>
   <example>
   <![CDATA[$c = container();
$c->add('testing', 1, 2, 3);]]>
   </example>
   <para>The output:
   <example><![CDATA[testing
1
2
3]]>
   </example>
   </para>
  </para>
 </refsect1>

 <refsect1 id="{@id collapse}">
  <title>Collapse</title>
  <para>
      <para>This method is used to force the output to exist on 1 line, instead
      of a newline for every element added.  </para>
   <example>
   <![CDATA[$c = container();
$c->set_collapse();
$c->add('testing', 1, 2, 3);]]>
   </example>
   <para>The output:
   <example><![CDATA[testing123]]></example>
   </para>
  </para>
 </refsect1>
</refentry>
