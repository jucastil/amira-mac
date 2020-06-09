/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TEXTURE_TRANSFORM_ELEMENT
#define  _SO_TEXTURE_TRANSFORM_ELEMENT

#include <Inventor/elements/SoReplacedTextureElement.h>
#include <Inventor/STL/vector>

class SoTexture2Transform;
class SoNode ;

/**
*  @VSGEXT Stores the current texture transform.
* 
*  @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current texture transform.
* 
*   @SEE_ALSO
*   SoCallbackAction
*/

SoEXTENDER_Documented class INVENTOR_API SoTextureTransformElement : public SoReplacedTextureElement {

  SO_ELEMENT_HEADER(SoTextureTransformElement);

 public:
  /**
  *  Sets the current texture name.
  */
  static void         set(SoState *state, SoNode *node);

  /**
  *  Returns the current texture name from the state.
  */
  static const SoTexture2Transform *  get(SoState *state, int unit=0);

  /**
  *  Returns the default texture name.
  */
  static SbName       getDefault()    { return NULL; }

  /**
  *  Returns TRUE if the texture name matches given element.
  */
  virtual SbBool      matches(const SoElement *elt) const;

  /**
  *  Creates and returns a copy of this element.
  */
  virtual SoElement   *copyMatchInfo() const;

  virtual void        push(SoState *state);

 SoINTERNAL public:
  // Initializes the SoTextureNameElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

  // Common Initialization. Directly called by the constructor.
  virtual void commonInit() ;

 protected:
  virtual ~SoTextureTransformElement();

 private:
   std::vector<SoNode*> m_textureTransform;
};

#endif /* _SO_TEXTURE_TRANSFORM_ELEMENT */
