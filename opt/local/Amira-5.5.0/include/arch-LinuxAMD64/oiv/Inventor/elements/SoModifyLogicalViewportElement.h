/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Nov 2007)
**=======================================================================*/


#ifndef SO_MODIFY_LOGICAL_VIEWPORT_ELEMENT_H
#define SO_MODIFY_LOGICAL_VIEWPORT_ELEMENT_H

#include <Inventor/SbViewportRegion.h>
#include <Inventor/elements/SoSubElement.h>

/** 
 * @VSGEXT Stores a logical viewport region subset.
 * 
 * @ingroup elements
 * 
 *   @DESCRIPTION
 *   This element stores a logical viewport region subset.
 * 
 */

SoEXTENDER_Documented class INVENTOR_API SoModifyLogicalViewportElement : public SoElement {
  
  SO_ELEMENT_HEADER(SoModifyLogicalViewportElement);
  
 public:
  /**
  *  Sets the portion of the viewport.
  */
  static void set(SoState *state, const SbVec4f& portion);
  
  /**
  *  Returns the current portion from the state.
  */
  static const SbVec4f &get(SoState *state);

  /**
  *  Returns the default viewport region.
  */
  static SbVec4f getDefault()
    { return SbVec4f( 0.0f, 0.0f, 1.0f, 1.0f ); }

  /**
  *  Returns the top (current) instance of the element in the state.
  *  Note it does NOT cause cache dependency!
  *  It also casts away the const.
  */
  static SoModifyLogicalViewportElement *getInstance(const SoState *state, SbBool &elemIsSet);

  /**
  *  Returns TRUE if the passes match in both elements.
  */
  virtual SbBool matches(const SoElement *elt) const;

  /**
  *  Create and return a copy of this element.
  */
  virtual SoElement *copyMatchInfo() const;

  /**
  *  Prints element (for debugging).
  */
  virtual void print(FILE *fp) const;

 SoINTERNAL public:
    // Initializes the SoModifyLogicalViewportElement class
  static void initClass();
  static void exitClass();
  
  // Initializes element
  virtual void init(SoState *state);
  

 protected:
  SbVec4f portion;

  SbBool isSet;

  virtual ~SoModifyLogicalViewportElement();

private:
  uint64_t nodeId;
};
#endif // SO_MODIFY_LOGICAL_VIEWPORT_ELEMENT_H
