/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Patrick Vigneras (Nov 1999)
**=======================================================================*/

#ifndef  _SO_GL_TEXTURE3_ENABLED_ELEMENT
#define  _SO_GL_TEXTURE3_ENABLED_ELEMENT

#include <Inventor/elements/SoReplacedTextureElement.h>

/**
* @VSGEXT Enables/disables 3D textures.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element enables/disables 3D textures. This is implemented as a
*   separate element from the TextureImage3Element so the texture image
*   can be changed without blowing caches containing shapes -- shapes
*   need to know if texturing is going on or not so they can decide to
*   send down texture coordinates or not.
* 
*   This is set by the GLTextureImage3Element and the
*   GLTextureEnabledElement; the interaction between the three is a
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
*   SoTexture3, SoGLTextureEnabledElement, SoGLTextureCubeMapEnabledElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLTexture3EnabledElement : public SoReplacedTextureElement {

  SO_ELEMENT_HEADER(SoGLTexture3EnabledElement);

public:
 /**
 *  Used by GLTexture3ImageElement, set to TRUE when a non-null
 *  image is set, set to FALSE when there is no 3D texture image (the
 *  default).
 */
 static void         set(SoState *state, SbBool value, SoNode *node=NULL);

  /**
  *  Used by shapes to figure out if they need to send texture
  *  coordinates.
  */
  static SbBool       get(SoState *state, int unit=0) ;

  /**
  *  By default there is not texture
  */
  static SbBool       getDefault()    { return FALSE; }

  /**
  *  Overrides push() so we can remember previous elements value and
  *  avoid making GL calls if this element has the same value.
  */
  virtual void        push(SoState *state);

  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLTexture3EnabledElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

  // Common Initialization. Directly called by the constructor.
  virtual void commonInit() ;

  virtual ~SoGLTexture3EnabledElement();

private:
  // Sends enabled in element to GL
  void send(SbBool value);

private:
  // return texture enbale flag for the given texture unit
  SbBool& getTexEnable(const int unit) const;

  // This stores the enable flag for each texture unit
  typedef std::vector<SbBool> SbBoolList;
  mutable SbBoolList m_enableList;
};

#endif /* _SO_GL_TEXTURE3_ENABLED_ELEMENT */
