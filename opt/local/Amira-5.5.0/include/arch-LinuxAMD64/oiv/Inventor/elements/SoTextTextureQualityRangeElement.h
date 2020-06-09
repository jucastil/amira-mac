/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Aug 2009)
**=======================================================================*/


#ifndef SO_TEXT_TEXTURE_QUALITY_RANGE_ELEMENT
#define SO_TEXT_TEXTURE_QUALITY_RANGE_ELEMENT

#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/SbVec.h>

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

SoEXTENDER_Documented class INVENTOR_API SoTextTextureQualityRangeElement : public SoReplacedElement
{
  SO_ELEMENT_HEADER(SoTextTextureQualityRangeElement);

 public:

  /**
   *  Sets the current range in the state.
   */
  static void set(SoState* state, SoNode *node, const SbVec2i32 range);

  /**
   *  Gets the current range in the state.
   */
  static const SbVec2i32& get(SoState* state);

  /**
   *  Returns the default value.
   */
  static const SbVec2i32& getDefault();
  
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
  SbVec2i32 m_range;

  virtual ~SoTextTextureQualityRangeElement();

private:
  static SbVec2i32 s_defaultRange;
  static bool s_isSet;
};

#endif // SO_TEXT_TEXTURE_QUALITY_RANGE_ELEMENT
