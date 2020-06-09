/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
** Modified by : Thad Beier (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_FONT_NAME_ELEMENT
#define  _SO_FONT_NAME_ELEMENT

#include <Inventor/SbString.h>
#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/nodes/SoFont.h>

/**
*   Stores the current font name.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current font name.
*
*   @SEE_ALSO
*   SoFont, SoFontStyle, SoVRMLFontStyle
*/

SoEXTENDER_Documented class INVENTOR_API SoFontNameElement : public SoReplacedElement {
  
  SO_ELEMENT_HEADER(SoFontNameElement);
  
 public:
/**
*  Sets the current font name.
*/
  static void set(SoState *state, SoNode *node,
                  const SbString &fontName);
  
  /**
  *  Returns the current font name from the state.
  */
  static const SbString &get(SoState *state);
  
  /**
  *  Returns the default font name.
  */
  static const SbString &getDefault();
  
  /**
  *  Returns TRUE if the font name matches given element.
  */
  virtual SbBool matches(const SoElement *elt) const;
  
  /**
  *  Creates and returns a copy of this element.
  */
  virtual SoElement *copyMatchInfo() const;
  
  /**
  *  Prints element (for debugging).
  */
  virtual void print(FILE *fp) const;
  
 SoINTERNAL public:
  // Initializes the SoNormalBindingElement class
  static void initClass();
  static void exitClass();
 
  // Initializes element
  virtual void init(SoState *state);
  
  // Return the current font node from the state
  static const SoFont *getFontNode(SoState *state);

  // Returns the font name set by the font server
  static const SbString& getFontServerFontName();

  // Sets the font name set by the font server
  static void setFontServerFontName( const SbString& fontName );
  
 protected:
  SbString fontName;
  SoFont *fontNode;
  
  virtual ~SoFontNameElement();
private:
  static SbString s_defaultFontName;
  static SbString s_currentFontName;
  static bool s_isSet;
};

#endif /* _SO_FONT_NAME_ELEMENT */
