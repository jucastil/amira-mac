<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:import href="templates.xsl"/>
<xsl:output method="text" omit-xml-declaration="yes" indent="no"/>


<xsl:template match="/">
<xsl:apply-templates/>
</xsl:template>

	
<xsl:template match="description">
	<xsl:variable name="stepnumberlist">
		<xsl:apply-templates/>
	</xsl:variable>
	<xsl:value-of select="normalize-space($stepnumberlist)"/>
</xsl:template>

<xsl:template match="title"/>
<xsl:template match="general"/>
<xsl:template match="staff"/>
<xsl:template match="script"/>
<xsl:template match="thumbnail"/>

<xsl:template match="prepacked"/>

<xsl:template match="demo[1]">
	<xsl:text> </xsl:text><xsl:value-of select="count(steps/step)"/>
</xsl:template>

<xsl:template match="steps">
</xsl:template>

</xsl:stylesheet>