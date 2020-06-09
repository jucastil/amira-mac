<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" omit-xml-declaration="yes" indent="yes"/>
<xsl:param name="printHtmlHead"/>

<xsl:template match="/">
		<xsl:text disable-output-escaping="yes">
                        &lt;/table>
		</xsl:text>
                <hr />
		<xsl:if test="$printHtmlHead='1'"><xsl:text disable-output-escaping="yes">
			&lt;/html>
			&lt;/body>
		</xsl:text></xsl:if>
</xsl:template>

</xsl:stylesheet>