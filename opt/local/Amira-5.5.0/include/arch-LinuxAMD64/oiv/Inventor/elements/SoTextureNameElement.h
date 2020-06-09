/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TEXTURE_NAME_ELEMENT
#define  _SO_TEXTURE_NAME_ELEMENT

#include <Inventor/SbString.h>
#include <Inventor/elements/SoReplacedElement.h>

/**
*   @VSGEXT Stores the current texture name.
* 
*   @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current texture name.
* 
*   @SEE_ALSO
*   SoCallbackAction
*/

SoEXTENDER_Documented class INVENTOR_API SoTextureNameElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(SoTextureNameElement);

 public:
  /**
  *  Sets the current texture name.
  */
  static void         set(SoState *state, SoNode *node,
                          const SbName &textureName);

  /**
  *  Returns the current texture name from the state.
  */
  static const SbName &get(SoState *state);

  /**
  *  Returns the default texture name.
  */
  static SbName       getDefault();

  /**
  *  Returns TRUE if the texture name matches given element.
  */
  virtual SbBool      matches(const SoElement *elt) const;

  /**
  *  Create and return a copy of this element.
  */
  virtual SoElement   *copyMatchInfo() const;

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoTextureNameElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  SbName                      textureName;

  virtual ~SoTextureNameElement();
};

#endif /* _SO_TEXTURE_NAME_ELEMENT */
