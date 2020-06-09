<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:import href="templates.xsl"/>

<xsl:output method="text" omit-xml-declaration="yes" indent="no"/>
<xsl:strip-space elements="*"/>

<xsl:param name="whichStep"/>
<xsl:param name="outdir"/>
<xsl:param name="demodir"/>

<xsl:template match="/">
<xsl:apply-templates/>
</xsl:template>

	
<xsl:template match="description">
global AMIRA_DEMOS
	<xsl:variable name="stepnumberlist">
		<xsl:apply-templates/>
	</xsl:variable>
	<xsl:value-of select="$stepnumberlist"/>
</xsl:template>

<xsl:template match="title"/>
<xsl:template match="general"/>
<xsl:template match="staff"/>
<xsl:template match="script"/>
<xsl:template match="thumbnail"/>

<xsl:template match="prepacked"/>

<xsl:template match="demo/steps/step"/>

<xsl:template match="demo[1]/steps/step[1]">
if { [ lsearch [ all ] DemoSequence ] &lt; 0 || ![DemoSequence hasVar demoXMLFilenames] || [lsearch [DemoSequence getVar demoXMLFilenames] {<xsl:value-of select="$demodir"/>description.xml}] == -1 } {
	source <xsl:value-of select="$outdir"/>/demosequence.hx
	DemoSequence startDemo 0 0
} elseif {[DemoSequence getVar currentDemo] != [lsearch [DemoSequence getVar demoXMLFilenames] {<xsl:value-of select="$demodir"/>description.xml}] } {
	DemoSequence startDemo [lsearch [DemoSequence getVar demoXMLFilenames] {<xsl:value-of select="$demodir"/>description.xml}] 0
}
<xsl:if test="$whichStep!=0">
# Jump to Demo 0 Step <xsl:value-of select="$whichStep"/>
<xsl:text>
</xsl:text>
	
DemoSequence jumpDemo [lsearch [DemoSequence getVar demoXMLFilenames] {<xsl:value-of select="$demodir"/>description.xml}]<xsl:text> </xsl:text><xsl:value-of select="number($whichStep)"/> 
</xsl:if>
</xsl:template>


</xsl:stylesheet>