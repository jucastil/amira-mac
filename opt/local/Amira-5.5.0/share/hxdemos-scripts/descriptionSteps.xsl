<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<!-- We want the simplest character set to automatically transform Umlauts to html-entities -->
<xsl:output method="html" omit-xml-declaration="yes" indent="yes" encoding="US-ASCII" />
<xsl:param name="relativeSrcDir"/>
<xsl:param name="step"/>
<xsl:variable name="stepNr" select="number($step)"/>
<xsl:param name="script"/>
<xsl:variable name="scriptNr" select="number($script)"/>

<xsl:template match="/">
<xsl:choose>
	<xsl:when test="$stepNr>0">
        
		<xsl:variable name="jc" select="description/demo[1]/steps/step[$stepNr]/@jumpcommand"/>
		<xsl:variable name="pc" select="description/demo[1]/steps/step[$stepNr]/@playcommand"/>
                <xsl:variable name="scriptname">
                  <xsl:choose>
                    <xsl:when test="$jc!=''">jump</xsl:when>
                    <xsl:otherwise>step</xsl:otherwise>
                  </xsl:choose>
                </xsl:variable>
                <xsl:variable name="jumpsrc">
                  <xsl:choose>
                    <xsl:when test="description/demo[1]/steps/step[$stepNr]/@jumpthumbsrc!=''">
                      <xsl:value-of select="$relativeSrcDir" /><xsl:value-of select="description/demo[1]/steps/step[$stepNr]/@jumpthumbsrc" />
                    </xsl:when>
                    <xsl:otherwise><xsl:value-of select="$relativeSrcDir" />gfx/step<xsl:value-of select="$stepNr - 1" />.png</xsl:otherwise>
                  </xsl:choose>
                </xsl:variable>
                
		<tr>
                <td align="center" valign="top">
                        <xsl:if test="$jc!=''">
                          <a href="stepscripts/jump{$scriptNr}.hx">
                                  <img src="{$jumpsrc}" width="150" border="0"/>
                          </a>
                        </xsl:if>
		</td>
		<td align="center" valign="top">
			<a href="stepscripts/step{$scriptNr}.hx">
				<img src="{$relativeSrcDir}gfx/step{$stepNr}.png" width="150" border="0"/>
			</a>
                </td>
                <td valign="bottom">
                <xsl:copy-of select="description/demo[1]/steps/step[$stepNr]"/></td>
		</tr>	
	</xsl:when>
	<xsl:otherwise>
		<tr>
                <td style="text-align: center;" halign="center" valign="top">
			<a href="stepscripts/step0.hx">
				<img src="{$relativeSrcDir}gfx/step0.png" width="150" border="0"/>
			</a>
			</td>
			<td colspan="2" valign="bottom">load demo script</td>
		</tr>	
	</xsl:otherwise>
</xsl:choose>
</xsl:template>

<xsl:template match="description" />

</xsl:stylesheet>