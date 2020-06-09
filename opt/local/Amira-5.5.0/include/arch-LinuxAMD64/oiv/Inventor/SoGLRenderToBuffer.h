/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef SOGLRENDERTOBUFFER_H
#define SOGLRENDERTOBUFFER_H

#include <Inventor/SbLinear.h>
#include <Inventor/sys/SoGLType.h>
#include <Inventor/helpers/SbGlContextHelper.h>

class SoGLGraphicConfigTemplate;
class SoGLContext;

class INVENTOR_API SoGLRenderToBuffer
{
public:
  /**
  *
  * Texture format. TEXTURE_RGB by default.
  */
  enum TextureFormat {
    TEXTURE_RGB = 0,
    TEXTURE_RGBA,
    TEXTURE_DEPTH,
    TEXTURE_DEPTH16,
    TEXTURE_DEPTH_RGBA,
    TEXTURE_RGB_FLOAT16,
    TEXTURE_RGBA_FLOAT16,
    TEXTURE_RGB_FLOAT32,
    TEXTURE_RGBA_FLOAT32,
    TEXTURE_STENCIL_INDEX8,
    TEXTURE_STENCIL_INDEX,
    TEXTURE_DEPTH_STENCIL,
    TEXTURE_UNKNOW
  };

  /**
  *
  * OpenGL target. TEXTURE_2D by default.
  */

  enum TextureTarget {
    TEXTURE_1D = 0,
    TEXTURE_2D,
    TEXTURE_3D,
    TEXTURE_CUBE_MAP,
    TEXTURE_RECTANGLE
  };

  /**
  *
  * Face id of the cube map.
  */
  enum CubeMapTextureFace {
    TEXTURE_CUBE_MAP_POSITIVE_X = 0,
    TEXTURE_CUBE_MAP_POSITIVE_Y,
    TEXTURE_CUBE_MAP_POSITIVE_Z,
    TEXTURE_CUBE_MAP_NEGATIVE_X,
    TEXTURE_CUBE_MAP_NEGATIVE_Y,
    TEXTURE_CUBE_MAP_NEGATIVE_Z
  };

  /**
  * Destructor
  */
  virtual ~SoGLRenderToBuffer();

  /**
  * Queries if Pbuffers are available on this system
  * (on the specified display connection if this is a UNIX system).
  * There is no guarantee it is possible to create a Pbuffer
  * (depends on requested size, available memory, etc).
  *
  * - On UNIX systems the parameter is a "Display *".
  * - On Win32 systems the parameter is ignored.
  */
  static SbBool isAvailable(SbGlContextHelper::Display display = NULL);

  /**
   * Creates a Pbuffer with the specified size.
   * Limited to 32767.
   * Returns TRUE if successful
   */
  virtual SbBool create(SbVec2s size) = 0;

  /**
   * Creates a Pbuffer with the specified size.
   * For sizes greater than 32767.
   * Returns TRUE if successful
   */
  virtual SbBool create(SbVec2i32 size) = 0;

  /**
  * Enable render to buffer for OpenGL rendering.
  * Returns TRUE if successful
  */
  virtual SbBool makeCurrent() = 0;

  /**
   * Disable render to buffer
   * Returns TRUE if successful
   */
  virtual void disable() = 0;

  /**
   * ++ This has effect only when using PBuffer. ++
   * Share OpenGL objects with the current context.
   */
  void shareCurrentContext() {}

  /**
   * ++ This has effect only when using PBuffer. ++
   *
   * Sets X display connection to use for this Pbuffer.
   * Must be set before calling the create() method.
   *
   * On UNIX systems the parameter is a "Display *".
   * On Win32 systems this method is ignored.
   */
  virtual void setDisplayConnection(SbGlContextHelper::Display display) = 0;

  /**
   * ++ This has effect only when using PBuffer. ++
   *
   *  Sets OpenGL render context for display list sharing.
   * Must be set before calling the create() method.
   * There is no guarantee that sharing will be allowed.
   */
  virtual void setContextForSharing(SoGLContext *context) = 0;

  /**
  * Resizes Pbuffer.
  * Limited to 32767.
  * Returns TRUE if successful
  */
  virtual SbBool resize(const SbVec2s &size) = 0;

  /**
  * Resizes Pbuffer.
  * For sizes greater than 32767.
  * Returns TRUE if successful
  */
  virtual SbBool resize(const SbVec2i32 &size) = 0;

  /**
  * Gets current size as an SbVec2s.
  */
  virtual SbVec2s getSize() const = 0;

  /**
  * Gets current size as an SbVec2i32
  */
  virtual const SbVec2i32& getSize_i32() const = 0;

  /**
  * Sets the current pixel format. This method allows an application to
  * set a pixel format that has extended attributes that can't be specified in
  * a PFD struct. The specified format must support OpenGL and drawing to a pbuffer.
  */
  virtual void setPixelFormat(int format) = 0;

  /**
  * Returns the current pixel format. This method allow an application to
  * query a pixel format that has extended attributes that can't be specified in
  * a PFD struct.
  */
  virtual int getPixelFormat() = 0;

  /**
  * Specifies settings for the Pbuffer creation.
  * Indicates if it must be created to be compliant with rendering to texture and also sets texture attributes.
  */
  virtual void setRenderToTexture(SbBool enable, TextureFormat format = TEXTURE_RGB, TextureTarget target = TEXTURE_2D,
                                  SbBool autoMipmap = FALSE, SbBool hasDepth = FALSE) = 0;

  /**
   * Binds the render buffer to a texture object.
   * If bindDepth is set to TRUE, binds the depth buffer instead of the color buffer.
   * [OIV-WRAPPER-ARG IN,WRAP_AS{int}]
   */
  virtual SbBool bindToTexture(SbBool bindDepth = FALSE, GLuint texObj=-1) = 0;

  /**
  * Releases the Pbuffer from the current texture object.
  * Required before rendering again.
  * If bindDepth is set to TRUE, releases the depth buffer instead of the color buffer
  */
  virtual SbBool releaseTexImage(SbBool bindDepth = FALSE) = 0;

  /**
  * Selects the face to be used when the rendering target is a cube map.
  */
  virtual SbBool selectCubeMapFace(CubeMapTextureFace face) = 0;

  /**
  * Gets the current graphics configuration template.
  */
  virtual SoGLGraphicConfigTemplate* getGraphicConfigTemplate() = 0;

  /**
  * Sets a new graphics configuration template.
  */
  virtual void setGraphicConfigTemplate(SoGLGraphicConfigTemplate* gTemplate) = 0;

  /**
   * Create a framebuffer if available otherwise use pbuffer.
   * forcePbuffer is true don't use framebuffer.
   * Create a pbuffer if SO_FBO_ENABLE is set to 0 whatever FBO availability.
   */
  static SoGLRenderToBuffer* createInstance(bool forcePbuffer, SbGlContextHelper::Display display = NULL);

  /**
   * Return TRUE if the render buffer is a pbuffer.
   */
  virtual SbBool isPBuffer()
  { return FALSE; }

SoINTERNAL public:
  static GLenum getGLInternalFormat(SoGLRenderToBuffer::TextureFormat fmt);
  static GLenum getGLTextureTarget(TextureTarget target);
  static GLenum getGLCubeMapTextureFace(CubeMapTextureFace face);

  static SoGLRenderToBuffer::TextureFormat getTextureFormatFromGLFormat(GLenum fmt);

  virtual void setFaceTarget(int faceTarget)=0;

protected:
  SoGLRenderToBuffer();

  SoGLGraphicConfigTemplate* m_currentGraphicConfigTemplate;

  int m_pfd;
private:
};
/*****************************************************************************/

#endif // SOGLRENDERTOBUFFER_H
