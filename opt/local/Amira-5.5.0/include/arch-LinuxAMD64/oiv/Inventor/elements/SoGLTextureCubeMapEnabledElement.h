/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_GL_TEXTURE_CUBEMAP_ENABLED_ELEMENT
#define  _SO_GL_TEXTURE_CUBEMAP_ENABLED_ELEMENT

#include <Inventor/elements/SoReplacedTextureElement.h>
#include <Inventor/STL/vector>

/**
* @VSGEXT Enables/disables textureCubeMap.
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This element enables/disables textureCubeMap. This is implemented as a
*   separate element from the TextureImageElement so the texture image
*   can be changed without blowing caches containing shapes-- shapes
*   need to know if texturing is going on or not so they can decide to
*   send down texture coordinates or not.
* 
*   This Element is very similar to SoGLTextureEnabledElement but contrary to
*   SoGLTextureImageElement, we can't deal with the texture2d and the CubeMap
*   texture in the same element.
* 
*   This element cannot be overridden, but, since the elements that
*   set it check each other's value, overriding those elements has
*   the same effect.
* 
*   @SEE_ALSO
*   SoTextureCubeMap, SoGLTextureEnabledElement, SoGLTexture3EnabledElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLTextureCubeMapEnabledElement : public SoReplacedTextureElement {

  SO_ELEMENT_HEADER(SoGLTextureCubeMapEnabledElement);

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
  *  Overrides push() so we can remember previous elements value and
  *  avoid making GL calls if this element has the same value.
  */
  virtual void        push(SoState *state);

  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLTextureCubeMapEnabledElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

  /**
  *  Common Initialization. Directly called by the constructor.
  */
  virtual void commonInit() ;

  virtual ~SoGLTextureCubeMapEnabledElement();

 private:
  // Sends enabled in element to GL
  void send(SbBool value);

  // Indicates for each texture unit if the textureCubeMap is enabled.
  SbBool& getEnableFlag(const size_t unit) const;
  mutable std::vector<SbBool> m_enable;
};

#endif /* _SO_GL_TEXTURE_CUBEMAP_ENABLED_ELEMENT */
