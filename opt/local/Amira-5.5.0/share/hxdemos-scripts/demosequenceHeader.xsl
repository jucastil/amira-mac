<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="text" omit-xml-declaration="yes" indent="no" encoding="ISO-8859-1" />

<xsl:param name="path"/>
<xsl:param name="dirAMIRA_DEMOSDemo"/>

<xsl:template match="/">
#################### config section ##################################

# the directory of the .demo file is set as the current directory
# you can override this using "cd"
# cd <xsl:value-of select="$path"/>


# 2 lists for demo control in hx-scripts from browser and snapshots
global internalSigAmiraDemosPaths
global internalSigAmiraDemosRelativePositions

# for compatibility with the old fullscreen.hx-driven scripts
global AMIRA_DEMOS
global FULLSCREEN  
if {![info exists FULLSCREEN]} {
	set FULLSCREEN 1
}
global STEREO 
if {![info exists STEREO]} {
	set STEREO 1
}


####################### demo sequence definition ############################
<xsl:apply-templates/>
</xsl:template>

	
<xsl:template match="description">
	<xsl:apply-templates/>
</xsl:template>

<xsl:template match="title"/>
<xsl:template match="general"/>
<xsl:template match="staff"/>
<xsl:template match="script"/>
<xsl:template match="thumbnail"/>

<xsl:template match="prepacked"/>

<xsl:template match="demo"/>
<xsl:template match="demo[1]">
		<!-- get name of the demo -->
		<xsl:variable name="demoname">
			<xsl:value-of select="normalize-space(/description/title)"/>
		</xsl:variable>
		<!-- get script file of the demo -->
		<xsl:variable name="scriptfile">
			<xsl:value-of select="script/@file"/>
		</xsl:variable>
		demo {<xsl:value-of select="$demoname"/>} {
		script {<xsl:value-of select="$demoname"/>} &quot;<xsl:value-of select="$dirAMIRA_DEMOSDemo"/><xsl:value-of select="$scriptfile"/>&quot;
</xsl:template>

</xsl:stylesheet>
