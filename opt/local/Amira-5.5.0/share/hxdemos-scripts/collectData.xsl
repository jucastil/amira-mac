<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:output method="text" omit-xml-declaration="yes" indent="yes"/>

	<xsl:template match="/"><xsl:apply-templates /></xsl:template>
	
	<xsl:template match="title"/>
	<xsl:template match="general"/>
	<xsl:template match="staff"/>
	<xsl:template match="script"/>
	<xsl:template match="thumbnail"/>
	<xsl:template match="steps"/>
	
	<xsl:template match="prepacked">
		<xsl:for-each select="file"><xsl:value-of select="../@href"/>
<xsl:text>
</xsl:text>
<xsl:value-of select="@src"/>
<xsl:text>
</xsl:text>
		</xsl:for-each>
	</xsl:template>

</xsl:stylesheet>