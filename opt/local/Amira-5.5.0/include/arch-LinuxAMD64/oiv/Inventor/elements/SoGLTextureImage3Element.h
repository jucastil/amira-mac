/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Patrick Vigneras (Nov 1999)
**=======================================================================*/

#ifndef  _SO_GL_TEXTURE_IMAGE3_ELEMENT
#define  _SO_GL_TEXTURE_IMAGE3_ELEMENT

class SoGLDisplayList;
class SoBufferObject;

#include <Inventor/elements/SoTextureImage3Element.h>

#include <Inventor/caches/SoGLTexCacheList.h>
#include <Inventor/STL/vector>

/**
* @VSGEXT Stores the current 3D texture image in GL.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current 3D texture image in GL. Overrides the
*   virtual methods on SoTextureImage3Element to send the 3D image
*   to GL when necessary.
*
*   Note that this class relies on SoTextureImage3Element to store the
*   image in the instance.
*
*   @SEE_ALSO
*   SoTextureImage3Element
*/

SoEXTENDER_Documented class INVENTOR_API SoGLTextureImage3Element : public SoTextureImage3Element {

  SO_ELEMENT_HEADER(SoGLTextureImage3Element);

public:
  /**
  *  Sets the current image, wrap modes and model.
  *  This will try to build or use a GL
  *  display list, if it can; the display list ID is returned (-1 if
  *  there is none), and should be saved and passed in the next time
  *  the element is set.  The node calling this routine is
  *  responsible for calling glDeleteLists to free up the display
  *  list at the right time.
  */
  static SoGLDisplayList *
    set(SoState *state, SoNode *node,
        const SbVec3s &s, int nc,
        const unsigned char *bytes,
        SoBufferObject* bufferObject,
        GLint GLInternalFormat,
        float texQuality,
        int wrapS, int wrapT, int wrapR, int model,
        const SbColor &blendColor, float _maxAnisotropy,
        SbBool _enableBorder, const SbVec4f &_borderColor, SoGLDisplayList *list,
        SbBool enableCompressedTexture );

  /**
  *  Pass texname = -1 to deactivate subtexturing. subtexturing not active
  *  by default. In any case, the regular set method must be called.
  */
  static void set(SoState *state, SoNode *node,
                  const SbVec3s &subSize, int xoffset, int yoffset, int zoffset,
                  const unsigned char *bytes, int texname) ;

  static void setFilter(SoState *state, SoNode *node, int _minFilter, int _magFilter);

  /**
  *  Overrides push() method to copy values from next instance in the stack.
  */
  virtual void push(SoState *state) ;

  /**
  *  Override pop() method so side effects can occur in GL.
  */
  virtual void pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLTextureImage3Element class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

  // Common Initialization. Directly called by the constructor.
  virtual void commonInit() ;

  static int getMaxTextureSize(SoState* state);

protected:
  // Catch setElt; if this setElt is called, it is an error...
  virtual void setElt(const SbVec3s &s, int nc,
                      const unsigned char *bytes,
                      GLint GLInternalFormat,
                      int wrapS, int wrapT, int wrapR, int model,
                      const SbColor &blendColor, float _maxAnisotropy,
                      SbBool _enableBorder, const SbVec4f &_borderColor,
                      int unit=0);


  virtual ~SoGLTextureImage3Element();

private:
  // Send texture environment information
  void                sendTexEnv(SoState *state);

  // Check openGL extensions for textures
  void checkOpenGLextensions(SoState* state, int currUnit);

  // Get the OpenGL internal format
  GLenum getGLFormat(int nc);

  // Sends image in element to GL. The state is needed to determine
  // whether or not OpenGL extensions are available.  This will
  // build or use a texture object or display list, if possible.
  void                sendTex(SoState *state);

  SoGLDisplayList* getDisplayListCache( int unit );

  void setDisplayList( int unit, SoState* state, SoGLDisplayList* displayList );

  void freeDisplayList();
  void unrefDisplayList();

  std::vector< SoGLTexCacheList* > m_cachesList;

   float               m_textureQuality;

  SbBool              m_enableCompressedTexture;

};

#endif /* _SO_GL_TEXTURE_IMAGE3_ELEMENT */
