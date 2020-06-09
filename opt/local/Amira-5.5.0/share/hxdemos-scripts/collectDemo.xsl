<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:import href="templates.xsl"/>
	
        <!-- We want the simplest character set to automatically transform Umlauts to html-entities -->
	<xsl:output method="html" omit-xml-declaration="yes" indent="yes" encoding="US-ASCII"/>

	<xsl:param name="path"/>
	<xsl:param name="date"/>
	<xsl:param name="linkTitle"/>
	<xsl:param name="wd"/>
	<xsl:param name="action"/>
	<xsl:param name="relativeSrcDir"/>
	
	<xsl:template match="steps" />
	
	<xsl:template match="/">
		<xsl:choose>
			<xsl:when test="$action='header'">
				<xsl:call-template name="printheader"/>	
			</xsl:when>
			<xsl:when test="$action='footer'">
				<xsl:call-template name="printfooter"/>	
			</xsl:when>
			<xsl:otherwise>
				<xsl:call-template name="printcontent"/>	
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template name="printheader">
		<xsl:text disable-output-escaping="yes">&lt;HTML>
		</xsl:text>
<HEAD>
<TITLE><!-- mandatory tag --></TITLE>
</HEAD>
		<xsl:text disable-output-escaping="yes">
&lt;BODY>
		</xsl:text>
		<b>Demo of <xsl:value-of select="$date" /></b>
		<xsl:if test="/description/@style!='projectlist'">
			<xsl:variable name="projecttitle">
				<xsl:choose>
				<xsl:when test="$linkTitle=''"><xsl:value-of select="document(concat($wd, '../description.xml'))/description/title" /></xsl:when>
				<xsl:otherwise><xsl:value-of select="$linkTitle" /></xsl:otherwise>
				</xsl:choose>
			</xsl:variable> 
	
			<!-- link to get back to previous page -->
			<xsl:choose>
			<xsl:when test="$linkTitle!=''">
				<br />back to the <a href="../index.html"><xsl:value-of select="$linkTitle" /></a>
			</xsl:when>
			<xsl:when test="$projecttitle!=''">
				<br />back to the <a href="../index.html"><xsl:value-of select="$projecttitle" /></a>-demo survey
			</xsl:when>
			</xsl:choose>
		</xsl:if>
			<xsl:apply-templates/>
		<br/>
                <p><a href="stepscripts/startSequence.hx">start sequence</a><br/>
		   <a href="stepscripts/prevDemo.hx">&lt;-</a> Demo <a href="stepscripts/nextDemo.hx">-&gt;</a><br/>
		   <a href="stepscripts/prevStep.hx">&lt;-</a> Step <a href="stepscripts/nextStep.hx">-&gt;</a><br/>
                </p>

		<xsl:text disable-output-escaping="yes">
			&lt;table border="0">
		</xsl:text>
	</xsl:template>
	
	<xsl:template match="prepacked">
	</xsl:template>

	<xsl:template name="printfooter">
				<xsl:text disable-output-escaping="yes">
&lt;/table>
&lt;/BODY>
&lt;/HTML>
				</xsl:text>
	</xsl:template>
	<xsl:template name="printcontent">
		<xsl:variable name="style" select="description/@style"/>
		<xsl:choose>
			<xsl:when test="$style='demo'">
				<xsl:call-template name="printdemocontent"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:call-template name="printcontainercontent"/>	
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>			

	<xsl:template name="printdemocontent">
		<xsl:variable name="thumbnail" select="normalize-space(/description/thumbnail/@src)"/>
			<tr>
				<td style="text-align: center;" halign="center" valign="center">
					<xsl:choose>
						<xsl:when test="$thumbnail=''">
							<a href="{concat($path, 'index.html')}#demo">
								<img src="{$relativeSrcDir}gfx/step0.png" border="0" />
							</a>
						</xsl:when>
						<xsl:otherwise>
							<a href="{$path}index.html#demo">
								<img src="{$relativeSrcDir}{$thumbnail}" border="0" />
							</a>
						</xsl:otherwise>
					</xsl:choose>	
				</td>
				<td valign="center">
					<a>
						<xsl:attribute name="href">
							<xsl:value-of select="concat($path, 'index.html')"/>
						</xsl:attribute>
						<xsl:value-of select="description/title"/>
					
					</a>
				</td>
			</tr>
	</xsl:template>

	<xsl:template name="printcontainercontent">
		<xsl:variable name="thumbnail" select="translate(normalize-space(description/thumbnail/@src), ' ', '')"/>
		<tr>
			<td style="text-align: center;" halign="center" valign="center">
				<xsl:if test="$thumbnail!=''">
					<a href="{$path}index.html">
						<img src="{$relativeSrcDir}{$thumbnail}" border="0" />
					</a>						
				</xsl:if>
			</td>
			<td valign="center">
				<a href="{$path}index.html">
					<xsl:value-of select="description/title"/>
				</a>
			</td>
		</tr>
	</xsl:template>
</xsl:stylesheet>
