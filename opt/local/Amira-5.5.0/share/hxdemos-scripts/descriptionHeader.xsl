<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:import href="templates.xsl"/>
        
        <!-- We want the simplest character set to automatically transform Umlauts to html-entities -->
	<xsl:output method="html" omit-xml-declaration="yes" indent="yes" encoding="US-ASCII"/>
<xsl:param name="path"/>
<xsl:param name="linkTitle"/>
<xsl:param name="relativeSrcDir"/>
<xsl:param name="printHtmlHead"/>
<xsl:variable name="projecttitle" select="document(concat($path, '../description.xml'))/description/title"/>
<xsl:variable name="script" select="/description/script/@file"/>

<xsl:template match="/">
        <xsl:if test="$printHtmlHead='1'"><xsl:text disable-output-escaping="yes">
		&lt;html>
	</xsl:text>
		<head><title><!-- mandatory element--></title></head>
	<xsl:text disable-output-escaping="yes">
		&lt;body>
	</xsl:text>
	<!-- link to get back to previous page -->
	<xsl:choose>
	<xsl:when test="$linkTitle!=''">
		back to the <a href="../index.html"><xsl:value-of select="$linkTitle" /></a>
	</xsl:when>
	<xsl:when test="$projecttitle!=''">
		back to the <a href="../index.html"><xsl:value-of select="$projecttitle" /></a>-demo survey
	</xsl:when>
	</xsl:choose>
        </xsl:if>
	<xsl:apply-templates />
	<a href="stepscripts/step0.hx">
		<img src="{$relativeSrcDir}gfx/step0.png" border="0"/>
	</a>
	<br/>
		<h2>Description of the Demo</h2>
	<xsl:text disable-output-escaping="yes">
		&lt;table border="1">
	</xsl:text>

</xsl:template>

<xsl:template match="description">
	<xsl:apply-templates/>
</xsl:template>

<xsl:template match="general"><xsl:copy-of select="." /></xsl:template>
<xsl:template match="prepacked">
</xsl:template>

<xsl:template match="demo">
</xsl:template>

<xsl:template match="steps" />
<xsl:template match="step" />

</xsl:stylesheet>