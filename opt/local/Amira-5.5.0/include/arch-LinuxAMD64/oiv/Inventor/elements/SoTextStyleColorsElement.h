/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Aug 2009)
**=======================================================================*/

#ifndef SO_TEXT_EFFECTS_COLOR_ELEMENT
#define SO_TEXT_EFFECTS_COLOR_ELEMENT

#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/fields/SoMFColorRGBA.h>
#include <Inventor/SbColorRGBA.h>

/**
 * @VSGEXT Stores the current textured text quality range.
 *
 * @ingroup elements
 * 
 *   @DESCRIPTION
 *   This element stores the current textured text quality range value.
 *
 *   @SEE_ALSO
 *   SoTextProperty
 */

SoEXTENDER_Documented class INVENTOR_API SoTextStyleColorsElement : public SoReplacedElement
{
  SO_ELEMENT_HEADER(SoTextStyleColorsElement);

 public:

  /**
   *  Sets the current range in the state.
   */
  static void set(SoState* state, SoNode *node, const SbColorRGBA* colors);

  /**
   *  Gets the current range in the state.
   */
  static const SbColorRGBA* get(SoState* state);

  /**
   *  Returns the default value.
   */
  static SbColorRGBA* getDefault();
  
  /** Returns TRUE if the attributes match in both elements */
  virtual SbBool matches(const SoElement *elt) const;

  /**
   *  Create and return a copy of this element.
   */
  virtual SoElement* copyMatchInfo() const;

SoINTERNAL public:
 
  // Initializes the SoTextTextureQualityRangeElement class
  static void initClass();
  static void exitClass();
  
  // Initializes element.
  virtual void init(SoState *state);

protected:
  SbColorRGBA* m_colors;
  bool m_colorsUpdated;

  virtual ~SoTextStyleColorsElement();
  virtual void commonInit();

private:
  static SbColorRGBA* s_defaultColors;
  static bool s_isSet;
};

#endif // SO_TEXT_EFFECTS_COLOR_ELEMENT
