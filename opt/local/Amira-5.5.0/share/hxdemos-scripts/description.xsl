<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:import href="templates.xsl"/>

<!-- We want the simplest character set to automatically transform Umlauts to html-entities -->
<xsl:output method="html" omit-xml-declaration="yes" indent="yes" encoding="US-ASCII" />

<xsl:param name="path"/>
<xsl:param name="linkTitle"/>
<xsl:param name="relativeSrcDir"/>
<xsl:param name="printHtmlHead"/>
<xsl:variable name="projecttitle">
	<xsl:choose>
	<xsl:when test="$linkTitle=''"><xsl:value-of select="document(concat($path, '../description.xml'))/description/title" /></xsl:when>
	<xsl:otherwise><xsl:value-of select="$linkTitle" /></xsl:otherwise>
	</xsl:choose>
</xsl:variable> 

<xsl:variable name="script" select="/description/script/@file"/>

<xsl:template match="/"><xsl:if test="$printHtmlHead='1'"><xsl:text disable-output-escaping="yes">&lt;HTML>
&lt;HEAD>&lt;TITLE><!-- mandatory element-->&lt;/TITLE>&lt;/HEAD>
&lt;BODY>
</xsl:text>
			<!-- link to get back to previous page -->
			<xsl:choose>
				<xsl:when test="printHtmlHead!='1'">
					show only <a href="{$relativeSrcDir}/index.html"><xsl:value-of select="$projecttitle" /></a>
				</xsl:when>
				<xsl:when test="$linkTitle!=''">
					back to the <a href="../index.html"><xsl:value-of select="$linkTitle" /></a>
				</xsl:when>
				<xsl:when test="$projecttitle!=''">
					back to the <a href="../index.html"><xsl:value-of select="$projecttitle" /></a>-demo survey
				</xsl:when>
			</xsl:choose>	
</xsl:if>
			<xsl:apply-templates/>
<xsl:if test="$printHtmlHead='1'"><xsl:text disable-output-escaping="yes">&lt;/BODY>
&lt;/HTML>
</xsl:text>
</xsl:if>
</xsl:template>

<xsl:template match="description">
	<xsl:apply-templates/>
</xsl:template>

<xsl:template match="prepacked">
</xsl:template>

<xsl:template match="demo">
</xsl:template>
<xsl:template match="demo[1]">
	<a href="stepscripts/step0.hx">
		<img src="{$relativeSrcDir}gfx/step0.png" width="150" border="0"/>
	</a>
	<xsl:apply-templates/>
	<hr/>
</xsl:template>

<xsl:template match="steps">
	<a name="demo">
	</a>
	<h2>Description of the Demo</h2>
	<table border="1">
	<xsl:for-each select="step">
		<xsl:variable name="stepel" select="position ()"/>
		<xsl:variable name="jc" select="@jumpcommand"/>
		<xsl:variable name="pc" select="@playcommand"/>
                <xsl:variable name="scriptname">
                  <xsl:choose>
                    <xsl:when test="$jc!=''">jump</xsl:when>
                    <xsl:otherwise>step</xsl:otherwise>
                  </xsl:choose>
                </xsl:variable>
                <xsl:variable name="jumpsrc">
                  <xsl:choose>
                    <xsl:when test="@jumpthumbsrc!=''">
                      <xsl:value-of select="$relativeSrcDir" /><xsl:value-of select="@jumpthumbsrc" />
                    </xsl:when>
                    <xsl:otherwise><xsl:value-of select="$relativeSrcDir" />gfx/step<xsl:value-of select="$stepel - 1" />.png</xsl:otherwise>
                  </xsl:choose>
                </xsl:variable>
                
		<tr>
                <td align="center" valign="top">
                        <xsl:if test="$jc!=''">
                          <a href="stepscripts/jump{$stepel}.hx">
                                  <img src="{$jumpsrc}" width="150" border="0"/>
                          </a>
                        </xsl:if>
		</td>
		<td align="center" valign="top">
			<a href="stepscripts/step{$stepel}.hx">
				<img src="{$relativeSrcDir}gfx/step{$stepel}.png" width="150" border="0"/>
			</a>
                </td>
                <td valign="top"><xsl:copy-of select="."/></td>
		</tr>	
	</xsl:for-each>
	</table>
</xsl:template>

</xsl:stylesheet>
