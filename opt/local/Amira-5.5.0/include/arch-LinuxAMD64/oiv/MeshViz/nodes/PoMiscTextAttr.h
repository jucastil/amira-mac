/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MISC_TEXT_ATTR_
#define  _PO_MISC_TEXT_ATTR_

#include <MeshViz/nodes/PoNode.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFBool.h>

class PbMiscTextAttr ;
class SoFieldSensor  ;

/**
 * @DTEXT  Node to define miscellaneous text attributes (font name, line length,...).
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *    This node defines the current miscellaneous text attributes for all 
 *    subsequent MeshViz representations which contain text.
 *    These attributes are the font name, the line length, the end 
 *    line character.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoMiscTextAttr {
 *    @TABLE_FILE_FORMAT
 *       @TR fontName @TD "defaultFont"
 *       @TR lineLength @TD LINE_LENGTH_MAX
 *       @TR endLineChar @TD ' '
 *       @TR profileEnabled @TD FALSE
 *       @TR predefinedProfileEnabled @TD TRUE
 *       @TR outliningEnabled @TD TRUE
 *    @TABLE_END
 *    }
 * 
 * 
 */

class MESHVIZ_API PoMiscTextAttr : public PoNode {

  SO_NODE_HEADER(PoMiscTextAttr) ;
  

 public:

  /**
   *  Line length.
   */
  enum LineLength {
    /**
     *  The lines are not limited.
     */
    LINE_LENGTH_MAX,  
    /**
     *  The lines are limited to one word.
     */
    LINE_LENGTH_MIN   
  } ;



  /**
   * Font name for text.
   */
  SoSFString fontName ;

  /**
   * Defines the max number of characters per line. 
   * If several endLineChar appear before the lineLength character, only the 
   * last endLineChar is taken into account. if lineLength = 
   * LINE_LENGTH_MAX, the lines length is not limited, and if lineLength = 
   * LINE_LENGTH_MIN, the lines are limited to one word.
   * 
   * Example of use with the string "United States of America" (24 characters) :
   *  - with endLineChar = ' ' and lineLength = 15, the string is cut
   * into two lines:
   *    "United States" and "of America".
   *  
   *  - with endLineChar = ' ' and lineLength = 18, the string is cut
   *    into two lines:
   *    "United States of" and "America".
   *
   * @B Be careful@b, words (consecutive characters delimited by #endLineChar
   * characters) are never truncated, so lines could exceed #lineLength characters
   * if the first word of the line contains more than #lineLength characters.
   */
  SoSFShort  lineLength ;

  /**
   * Defines the end line character.
   */
  SoSFShort  endLineChar ;

  /**
   * Enables/Disables the appearance of a profile for 3D Text.
   * Only SoText3 text takes into account of this option 
   * (cf PoBase::setTextType() and PoBase::setVRML2Mode()) to
   * to select the type of text used).
   */
  SoSFBool   profileEnabled ;

  /**
   * Enables/Disables the use of a predefined profile
   * for 3D text if they are activated (cf profileEnabled field).
   * If this field is set to FALSE, the current profile in the state
   * is used (cf SoLinearProfile,...)
   */
  SoSFBool   predefinedProfileEnabled ;

  /**
   * 
   * Enables/Disables drawing of the outline of polygonal text 
   * (SoText3 and SoAnnoText3). 
   * For filled text that is small relative to the viewer size,
   * drawing the outline improves the appearance of the text.
   * For larger text, the outline can be deactivated to improve 
   * performance and prevent the text having a bold appearance.
   *
   * @FIELD_SINCE_OIV 4.0
   */
  SoSFBool    outliningEnabled ;

  /* Methods */

  /**
   * Constructor.
   */
  PoMiscTextAttr() ;

  /*----------------------------------------------------------------------------*/

  
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  virtual ~PoMiscTextAttr() ;
  
 private:
  static void fieldsChangedCB(void *data, SoSensor *) ;
  static void fontNameChangedCB(void *data, SoSensor *) ;

  SbBool          m_fieldsChanged ;
  SbBool          m_fontNameChanged ;
  PbMiscTextAttr  *m_textAttr ;
  SoFieldSensor   *m_fontNameSensor ;
  SoFieldSensor   *m_lineLengthSensor ;
  SoFieldSensor   *m_endLineCharSensor ;
  SoFieldSensor   *m_profileEnabledSensor ;
  SoFieldSensor   *m_predefProfileEnabledSensor ;
  SoFieldSensor   *m_outliningSensor ;
} ; 
/*----------------------------------------------------------------------------*/

#endif /* _PO_MISC_TEXT_ATTR_  */

