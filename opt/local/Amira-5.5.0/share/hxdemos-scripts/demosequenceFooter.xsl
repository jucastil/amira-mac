<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" omit-xml-declaration="yes" indent="no" encoding="ISO-8859-1" />

<xsl:param name="dirAMIRA_DEMOSDemo"/>

<xsl:template match="/">
} {<xsl:value-of select="$dirAMIRA_DEMOSDemo"/>description.xml}
</xsl:template>

</xsl:stylesheet>