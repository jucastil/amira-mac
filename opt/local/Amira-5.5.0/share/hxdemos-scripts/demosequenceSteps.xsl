<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="text" omit-xml-declaration="yes" indent="no" encoding="ISO-8859-1" />

<xsl:param name="step" />
<xsl:param name="dirAMIRA_DEMOSDemo" />

<xsl:variable name="stepNr" select="number($step)" />
<xsl:template match="/">
<xsl:apply-templates />
</xsl:template>

	
<xsl:template match="description">
	<xsl:apply-templates/>
</xsl:template>

<xsl:template match="title" />
<xsl:template match="general" />
<xsl:template match="staff" />
<xsl:template match="script" />
<xsl:template match="thumbnail" />

<xsl:template match="prepacked" />

<xsl:template match="demo" />
<xsl:template match="demo[1]">
			<xsl:apply-templates />
</xsl:template>
<xsl:template match="step" />
<xsl:template match="steps">
    <xsl:for-each select="step">
      <xsl:if test="$stepNr=position()">
	<xsl:variable name="stepname"><xsl:value-of select="@name" /></xsl:variable>
	<xsl:variable name="procedurecall">
          <xsl:choose>
          <xsl:when test="@playcommand!=''">
            <xsl:value-of select="@playcommand" />
          </xsl:when>
          <xsl:otherwise>
            <xsl:value-of select="@jumpcommand" />
          </xsl:otherwise>
        </xsl:choose>
        </xsl:variable>
	<xsl:variable name="procedurecalljump"><xsl:value-of select="@jumpcommand"/></xsl:variable>
			step "<xsl:value-of select="$stepname" />" { 
				# when invoked from a demosequence of a higher container/project/projectlist, move to the right directory
				cd &quot;<xsl:value-of select="$dirAMIRA_DEMOSDemo" />&quot;
				<xsl:text>
				</xsl:text>
				<xsl:value-of select="$procedurecall" />
			} {<xsl:value-of select="$procedurecalljump"/>}
      </xsl:if>
    </xsl:for-each>
  <xsl:apply-templates />
</xsl:template>
<!--
<xsl:template match="step" />
<xsl:template match="step[$stepNr]">
	<xsl:variable name="stepname"><xsl:value-of select="@name" /></xsl:variable>
	<xsl:variable name="procedurecall">
          <xsl:choose>
          <xsl:when test="@playcommand!=''">
            <xsl:value-of select="@playcommand" />
          </xsl:when>
          <xsl:otherwise>
            <xsl:value-of select="@jumpcommand" />
          </xsl:otherwise>
        </xsl:choose>
        </xsl:variable>
	<xsl:variable name="procedurecalljump"><xsl:value-of select="@jumpcommand"/></xsl:variable>
			step "<xsl:value-of select="$stepname" />" { 
				# when invoked from a demosequence of a higher container/project/projectlist, move to the right directory
				cd &quot;<xsl:value-of select="$dirAMIRA_DEMOSDemo" />&quot;
				<xsl:text>
				</xsl:text>
				<xsl:value-of select="$procedurecall" />
			} {<xsl:value-of select="$procedurecalljump"/>}
</xsl:template>
-->
</xsl:stylesheet>
