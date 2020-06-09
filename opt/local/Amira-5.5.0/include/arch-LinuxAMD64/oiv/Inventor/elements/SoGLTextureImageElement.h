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


#ifndef  _SO_GL_TEXTURE_IMAGE_ELEMENT
#define  _SO_GL_TEXTURE_IMAGE_ELEMENT

class SoGLDisplayList;
class SoRenderToTextureProperty;
class SoBufferObject;

#include <Inventor/elements/SoTextureImageElement.h>
#include <Inventor/caches/SoGLTexCacheList.h>
#include <Inventor/STL/vector>

/**
*   Stores the current texture image in GL.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current texture image in GL. Overrides the
*   virtual methods on SoTextureImageElement to send the image
*   to GL when necessary.
*
*   Note that this class relies on SoTextureImageElement to store the
*   image in the instance.
*
*   @SEE_ALSO
*   SoTextureImageElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLTextureImageElement : public SoTextureImageElement {

  SO_ELEMENT_HEADER(SoGLTextureImageElement);

 public:

  /**
  *  Sets the current image, wrap modes and model.
  *  This will try to build or use a GL
  *  display list, if it can; the display list ID is returned (-1 if
  *  there is none), and should be saved and passed in the next time
  *  the element is set. The node calling this routine is
  *  responsible for calling glDeleteLists to free up the display
  *  list at the right time.
  */
  static SoGLDisplayList *
    set(SoState *state, SoNode *node,
        const SbVec2s &s, int nc,
        const void* _buffer,
        SoBufferObject* _bufferObject,
        SoSFImage::DataType _dataType,
        GLint _GLInternalFormat,
        SoRenderToTextureProperty* renderToTexProp,
        float texQuality,
        int wrapS, int wrapT, int wrapR, int model,
        const SbColor &blendColor, float _maxAnisotropy,
        SbBool _enableBorder, const SbVec4f &_borderColor,
        SbBool isCompressed, int numCompressedMipmaps,  SoGLDisplayList *list,
        int hasTransparency = -1, /* default is unknown */
        SbBool enableCompressedTexture = FALSE , int CurrentImg=-1);

  /**
  *  Pass texname = -1 to deactivate subtexturing. subtexturing not active
  *  by default. In any case, the regular set method must be called.
  */
  static void   set(SoState *state, SoNode *node,
                    const SbVec2s &subSize, int xoffset, int yoffset,
                    const void *buffer, SoSFImage::DataType dataType, int texname) ;

  /**
  *  override matches method (needed for shadowing)
  */
  virtual SbBool matches(const SoElement *elt) const;

  /**
  *  override copyMatchInfo method (needed for shadowing)
  */
  SoElement *copyMatchInfo() const;

  /**
  *  Sets the texture filter.
  */
  static void setFilter(SoState *state, SoNode *node, int _minFilter, int _magFilter);

  /**
  *  Sets the shadows rendering state
  */
  static void setIsRenderingShadows( SoState *state, SoNode *node, SbBool isRenderingShadows );

  /**
  *  Override push() method to copy values from next instance in the stack.
  */
  virtual void push(SoState *state) ;

  /**
  *  Override pop() method so side effects can occur in GL.
  */
  virtual void  pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLTextureImageElement class
  static void           initClass();
  static void           exitClass();

  // Initializes element
  virtual void  init(SoState *state);

  // Common Initialization. Directly called by the constructor.
  virtual void commonInit() ;

  static int getMaxTextureSize();

  /**
  *  Special value set for shadowing (FxViz)
  *  If rendering shadowed textures,
  *  A texture model REPLACE will be transformed by glDisable(GL_LIGHTING)
  */
  SbBool m_isRenderingShadows;

 protected:

   virtual ~SoGLTextureImageElement();

 private:


  // Send texture environment information
  void          sendTexEnv(SoState *state);

  // Sends image in element to GL. The state is needed to determine
  // whether or not OpenGL extensions are available.  This will
  // build or use a texture object or display list, if possible.
  void          sendTex(SoState *state);

  // Useful functions

  // Setup 2D textures:
  // Do the main code for both texture2D and RTT and
  // call sendTex2D or setupTexRTT according to the texture type.
  void setupTexture2D(SoState *state);

  // Main function to send 2D textures to OpenGL
  void sendTex2D(SoState *state);

  // This function managers sub 2D textures.
  void  sendSubTex2D(SoState *state);

  // This function sets the Render To Texture texture
  void setupTexRTT(SoState *state);

  // This function is called by sendTex to finalize the setup process.
  void sendFinish(SoState *state);

  // This function checks if the texture is supported and if so if we have to send it.
  SbBool reallySend(SoState* state);

  // Scale the image. gluScaleImage makes two copies of the image.
  // For very large images, the computer could run out of texture
  // memory. By doing our own scaling we can eliminate this problem.

  void  scaleImage(GLenum format, GLint xsize, GLint ysize, int numComponents, GLenum typein, const void *buffer,
                   GLint newSizex, GLint newSizey, GLenum typeout, void *dataout);

  void checkOpenGLextensions(SoState* state, int currUnit);

  GLenum getGLFormat(int nc, int currUnit);

  SoGLDisplayList* getDisplayListCache( int unit );

  void setDisplayList( int unit, SoState* state, SoGLDisplayList* displayList );

  unsigned long getTextureSizeInBytes(int textureWidth, int textureHeight, int unit) const;

  void freeDisplayList();
  void unrefDisplayList();


  std::vector< SoGLTexCacheList* > m_cachesList;

  float m_textureQuality;
  SbBool m_enableCompressedTexture;

  /** */
  static bool s_useGLBufferObject;
};

#endif /* _SO_GL_TEXTURE_IMAGE_ELEMENT */
