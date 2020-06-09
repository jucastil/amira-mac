/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_GL_TEXTURE_ENABLED_ELEMENT
#define  _SO_GL_TEXTURE_ENABLED_ELEMENT

#include <Inventor/elements/SoReplacedTextureElement.h>

#include <Inventor/STL/vector>

/**
*  Enables/disables textures.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element enables/disables textures. This is implemented as a
*   separate element from the TextureImageElement so the texture image
*   can be changed without blowing caches containing shapes -- shapes
*   need to know if texturing is going on or not so they can decide to
*   send down texture coordinates or not.
*
*   This is set by the GLTextureImageElement and the
*   GLTextureImageElement; the interaction between the three is a
*   little complicated. Each of the other two elements always sets up
*   the GL texture state appropriately; however, texturing is only
*   enabled if both elements agree that it should be enabled (they
*   check each other's value before calling set).
*
*   This element cannot be overridden, but, since the elements that
*   set it check each other's value, overriding those elements has
*   the same effect.
*
*   @SEE_ALSO
*   SoTexture2, SoExtTexture2, SoImageBackground,
*   SoGLTextureCubeMapEnabledElement, SoGLTexture3EnabledElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLTextureEnabledElement : public SoReplacedTextureElement {

  SO_ELEMENT_HEADER(SoGLTextureEnabledElement);

 public:
  /**
  *  Used by GLTextureImageElement, set to TRUE when a non-null
  *  image is set, set to FALSE when there is no texture image (the
  *  default).
  */
  static void         set(SoState *state, SbBool value, SoNode *node=NULL);

  /**
  *  Used by shapes to figure out if they need to send texture
  *  coordinates.
  */
  static SbBool       get(SoState *state, int unit=0) ;

  /**
  *  By default there is no texture.
  */
  static SbBool       getDefault()    { return FALSE; }

  /**
  *  Overrides push() so we can remember previous element's value and
  *  avoid making GL calls if this element has the same value.
  */
  virtual void        push(SoState *state);

  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLTextureEnabledElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 // Common Initialization. Directly called by the constructor.
  virtual void commonInit() ;

  virtual ~SoGLTextureEnabledElement();

 private:
  // Sends enabled in element to GL
  void send(SoState* state, SbBool value);

  bool isEnabled( int unit ) const;

  void setEnabled( int unit, bool enabled );

  typedef std::vector<bool> SoTextureUnitEnabledList;

  // Indicates for each texture unit if texturing is enabled.
  mutable SoTextureUnitEnabledList m_isEnabled;

  // define if we are using a cubeMap or a 2D texture
  SbBool *m_isCubeMap;
};

#endif /* _SO_GL_TEXTURE_ENABLED_ELEMENT */
