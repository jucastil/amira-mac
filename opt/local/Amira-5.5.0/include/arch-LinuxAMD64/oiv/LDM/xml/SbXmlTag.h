/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _LDM_XML_TAG_
#define _LDM_XML_TAG_

class SbThreadMutex;
class SiBitFile;
class SoDataCompressor;
class SoDataCompressInfo;

#include <Inventor/SbBasic.h>

/**
 * @LDMEXT XML tag from LDM filer.
 *
 * @ingroup LDMReaders
 *
 * @DESCRIPTION
 *
 * This class allows the application to read back a custom XML section inserted in
 * a LDM file header by using the method SoLDMConverter::setXmlCallback().
 *
 * Let's suppose the following XML text has been inserted:
 * \code
 * ...
 * <MY_CUSTOM_TAG_SECTION>
 *   text
 *   <CUSTOM_TAG1>value1</CUSTOM_TAG1>
 *   <CUSTOM_TAG2>value2</CUSTOM_TAG2>
 * </MY_CUSTOM_TAG_SECTION>
 * ...
 * \endcode
 *
 * The following code will produce the output below:
 *
 * \code
 *  SoVRLdmFileReader *ldmReader = (SoVRLdmFileReader*)(myVolumeData->getReader());
 *  SbXmlTag myTagSection = ldmReader->getXmlTag( "MY_CUSTOM_TAG_SECTION" );
 *  if (myTagSection.exist()) {
 *    printf( "\%s:\%s\\n", myTagSection.getName(), myTagSection.getText() );
 *    for (SbXmlTag t = myTagSection.getFirstChildTag();
 *         t.exist();
 *         t = t.getNextSiblingTag())
 *      printf( "  \%s:\%s\\n", t.getName(), t.getText() );
 *  }
 * \endcode
 * Output:
 * \code
 *  <PRE>
 * MY_CUSTOM_TAG_SECTION:text
 *   CUSTOM_TAG1:value1
 *   CUSTOM_TAG2:value2
 * </PRE>
 * \endcode
 *
 *
 */

class LDM_API SbXmlTag {
public:
  /**
   *  Indicates if this XML tag is valid.
   */
  bool         exist();

  /**
   *  Returns the name of the XML tag.
   */
  const char*  getName();

  /**
   *  Returns the text associated with the XML tag.
   */
  const char*  getText();

  /**
   *  Returns the first XML child tag.
   */
  SbXmlTag     getFirstChildTag();

  /**
   *  Returns the next sibling XML child.
   */
  SbXmlTag     getNextSiblingTag();

SoINTERNAL public:
  SbXmlTag(void* = NULL);

protected:
  void *m_tag;
};

#endif
