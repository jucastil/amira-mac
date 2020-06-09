/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Oct 2000)
**=======================================================================*/

#ifndef  _SO_GL_EXT_TEXTURE_IMAGE_ELEMENT
#define  _SO_GL_EXT_TEXTURE_IMAGE_ELEMENT

#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/nodes/SoExtTexture2.h>

/**
*  @VSGEXT Stores the current texture image in GL.
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

SoEXTENDER_Documented class INVENTOR_API SoGLExtTextureImageElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(SoGLExtTextureImageElement);

public:
  /**
  *  Sets the current image, wrap modes, and model.
  *  This will try to build or use a GL
  *  display list, if it can; the display list ID is returned (-1 if
  *  there is none), and should be saved and passed in the next time
  *  the element is set. The node calling this routine is
  *  responsible for calling glDeleteLists to free up the display
  *  list at the right time.
  */
  static SoGLDisplayList* set(SoState *state, SoNode *node,
    const SbVec2s &s, int nc,
    unsigned char*& bytes, 
    GLint GLInternalFormat, 
    GLenum compressedFormat,
    unsigned char*& palette,
    float texQuality,
    int wrapS, int wrapT, int model, 
    const SbColor &blendColor,
    float maxAnisotropy, SbBool enableBorder,
    const SbVec4f &borderColor, 
    SbBool enableCompressedTexture,
    SbBool isCompressed, int numCompressedMipmaps,
    SoGLDisplayList *list);

  static void setFilter(SoState *state, SoNode *node, int _minFilter, int _magFilter);

  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

  SoINTERNAL public:
  // Initializes the SoGLExtTextureImageElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

protected:
  // Catch setElt; if this setElt is called, it is an error...
  virtual void        setElt(const SbVec2s &s, int nc, unsigned char *& , GLint GLInternalFormat,
    int wrapS, int wrapT, int model,
    const SbColor &blendColor, float _maxAnisotropy,
    SbBool _enableBorder, const SbVec4f &_borderColor,
    SbBool _enableCompressedTexture, float _quality, 
    unsigned char** _palette, SoNode* _node, 
    SoGLDisplayList* _list, GLenum _compressedFormat, 
    SbBool isCompressed, int _numCompressedMipmaps);

  virtual ~SoGLExtTextureImageElement();

  virtual void        commonInit();

private:
  // Send texture environment information
  void  sendTexEnv(SoState *state);

  // Sends image in element to GL. The state is needed to determine
  // whether or not OpenGL extensions are available.  This will
  // build or use a texture object or display list, if possible.
  void  sendTex(SoState *state, SoNode* node);

  // Scale the image. gluScaleImage makes two copies of the image.
  // For very large images, the computer could run out of texture 
  // memory. By doing our own scaling we can eliminate this problem.

  void  scaleImage(GLenum format, GLint xsize, GLint ysize, int numComponents, GLenum typein, void *,
    GLint newSizex, GLint newSizey, GLenum typeout, GLubyte *dataout);

  // Returns a texture object index available
  int genTextureIdx();

  //check some OpenGL extensions for textures
  void checkOpenGLextensions(SoState* state);

  GLenum getGLFormat(int nc);


  float              quality;
  unsigned char**    palette;
  GLuint             texName;
  SoNode*            texNode;
  SbVec2s            size;
  int                numComponents;
  int                wrapS;
  int                wrapT;
  int                model;
  SbColor            blendColor;
  float              maxAnisotropy;
  SbBool             enableBorder;
  SbVec4f            borderColor;
  int                minFilter;
  int                magFilter;
  unsigned char**    bytes;
  GLint              GLInternalFormat;
  SoGLTexCacheList   *m_cacheList;
  GLenum             compressedFormat;
  SbBool             isCompressed;
  int                numCompressedMipmaps;

  static GLenum      texPalIntFormat;

  SbBool m_enableCompressedTexture;

  void *_GlColorTable; 

  void unrefDisplayList();
  void freeDisplayList();
  SoGLDisplayList* getDisplayListCache( );
  void setDisplayList( SoState* state, SoGLDisplayList* displayList );

};

#endif /* _SO_GL_EXT_TEXTURE_IMAGE_ELEMENT */
