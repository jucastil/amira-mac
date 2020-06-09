/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_MISC_TEXT_ATTR_
#define  _PB_MISC_TEXT_ATTR_

#include <MeshViz/graph/PbBase.h>
#include <Inventor/SbString.h>

/**
 * @DTEXT  Class to define a numeric display format.
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *    This class is used to define miscellaneous text attributes.
 * 
 */
class MESHVIZ_API PbMiscTextAttr : public PbBase {


 public:



  PbMiscTextAttr() ;
  PbMiscTextAttr(const PbMiscTextAttr &miscTextAttr) ;

  enum LineLength {
    /** The lines are not limited.  */
    LINE_LENGTH_MAX, 
    /** The lines are limited to one word. */
    LINE_LENGTH_MIN  
  } ;

  /**
   * Sets line length attributes. lineLength is the max number of characters per 
   * line. If several endLineChar appear before the lineLength character, only the 
   * last endLineChar is taken into account. if lineLength = 
   * LINE_LENGTH_MAX, the lines length is not limited, and if lineLength = 
   * LINE_LENGTH_MIN, the lines are limited to one word. By default 
   * endLineChar is ' ' and lineLength is LINE_LENGTH_MAX.
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
  void setLineLength(char endLineChar, int lineLength) ;

  /**
   * Gets line length attributes. 
   * [OIVJAVA-WRAPPER PACK{LineLength}]
   */
  void getLineLength(char &endLineChar, int &lineLength) const
    { endLineChar = m_endCharLine ; lineLength = m_lineLength ; }

  /**
   * Sets the font name for texts. The default font name is "defaultFont".
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setFontName(const char *name) ;

  /**
   * Sets the font name for texts. The default font name is "defaultFont".
   */
  void setFontName(const SbString& name) ;

  /**
   * Gets the font name for texts. 
   */
  SbString getFontName() const { return m_fontName; }

  void enableProfile(SbBool flag) ;

  /**
   * Enables/Disables the appearance of a profile for 3D Text.
   * Only SoText3 text takes into account of this option 
   * (cf PoBase::setTextType() and PoBase::setVRML2Mode()) to
   * to select the type of text used).
   * This option is disabled by default.
   */
  SbBool isProfileEnabled() const
    { return m_isProfileEnabled ; }

  void enablePredefinedProfile(SbBool flag) ;

  /**
   * Enables/Disables the use of a predefined profile
   * for 3D text if they are activated (cf enableProfile()).
   * If this option is disabled, the current profile in the state
   * is used (cf SoLinearProfile,...)
   * This option is enabled by default.
   */
  SbBool isPredefinedProfileEnabled() const
    { return m_isPredefinedProfile ; }

  /**
   * Assignment operator.
   */
  PbMiscTextAttr& operator=(const PbMiscTextAttr &miscTextAttr) ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:

  // Enable/disable outlining.
  void enableOutlining(SbBool flag) ;

  SbBool isOutliningEnabled() const
    {return m_isOutliningEnabled ;}

 private:
  void copy(const PbMiscTextAttr &miscTextAttr, SbBool isConstructorPerCopy) ;
  // Used by constructor per copy and affectation operator

  char      m_endCharLine ;
  int       m_lineLength ;
  SbString  m_fontName ;
  SbBool    m_isProfileEnabled, m_isPredefinedProfile, m_isOutliningEnabled ;
} ;

/*---------------------------------------------------------------------------*/

#endif /* _PB_MISC_TEXT_ATTR_ */

