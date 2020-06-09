<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:param name="printHtmlHead"/>

<xsl:template name="extracttitle" match="title">
<xsl:choose>
<xsl:when test="$printHtmlHead!='1'">
<h1 style="page-break-before:always"><xsl:value-of select="."/></h1>
</xsl:when>
<xsl:otherwise>
<h1><xsl:value-of select="."/></h1>
</xsl:otherwise>
</xsl:choose>
</xsl:template>

<xsl:template name="extractgeneral" match="general">
<xsl:copy-of select="."/>
</xsl:template>

<xsl:template name="extractstaff" match="staff">
<h2>People in charge:</h2>
<p>
    <xsl:for-each select="person">
    <xsl:if test="@status='responsible'"><b>Responsible: </b></xsl:if>
        <a>
            <xsl:if test="email!=''">
                <xsl:attribute name="href">
                    <xsl:text>mailto:</xsl:text>
                    <xsl:value-of select="email"/>
                </xsl:attribute>
            </xsl:if>
            <xsl:value-of select="name"/>
        </a>
        <xsl:text> (</xsl:text>
        <xsl:value-of select="userid"/>
        <xsl:if test="tel!=''">
            <xsl:if test="userid!=''">
                <xsl:text>, </xsl:text>
            </xsl:if>
            <xsl:text>Tel. </xsl:text>
            <xsl:value-of select="tel" />
        </xsl:if>
        <xsl:text>)</xsl:text>
        
        <xsl:if test="position () != last ()">
            <xsl:text>, </xsl:text>
        </xsl:if>
    </xsl:for-each>
</p>

</xsl:template>


</xsl:stylesheet>
