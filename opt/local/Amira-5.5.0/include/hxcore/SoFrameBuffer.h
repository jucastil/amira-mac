#ifndef _SO_FRAME_BUFFER_H_
#define _SO_FRAME_BUFFER_H_

#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>
#include <Inventor/sys/SoGL.h>

/**
 * @TGSEXT Create an OpenGL FrameBuffer
 * @ingroup General
 *
 * @DESCRIPTION
 *    This create an OpenGL FrameBuffer object which may be used for 
 *    accelerated off-screen rendering. Unlike a pixmap or offscreen
 *    bitmap, a FrameBuffer is allocated in frame buffer memory and can be
 *    rendered to directly by the graphics hardware. Unlike Pbuffer, this object
 *    is not dependant on the windowing system and share the current OpenGL.
 *
 *    FrameBuffer are only available if the graphics hardware supports
 *    OpenGL 2.0 or the OpenGL framebufferobject extension. This extension
 *    is named "GL_frame_buffer_object".
 *
 * @SEE_ALSO
 *    SoPBuffer, SoOffscreenRenderer
 *
 * @MODIFICATIONS_ENHANCEMENTS @I Copyright (C) 2006 VISUALIZATION SCIENCES GROUP S.A.S. All rights reserved @i
 */
 
class SoFrameBuffer {

public:

  /**
   * Texture format. TEXTURE_RGB by default.
   */
  enum TextureFormat {
    TEXTURE_RGB = 0,
    TEXTURE_RGBA,
    TEXTURE_DEPTH,
    TEXTURE_DEPTH_RGBA
  };

  /**
   * OpenGL texture target. TEXTURE_2D by default.
   */
  enum TextureTarget {
    TEXTURE_2D = 0,
    TEXTURE_CUBE_MAP,
    TEXTURE_RECTANGLE
  };

  /**
   * Constructor.
   * Creates an object of this class but does *not* create the FrameBuffer
   * until resize is called.
   */
  SoFrameBuffer();

  /**
   * Destructor
   */
  ~SoFrameBuffer();

  /**
   * Queries if FrameBuffer are available on this system
   * There is no guarantee it is possible to create a framebuffer
   * (depends on requested size, available memory, etc).
   */
  static SbBool isAvailable();

  /**
   * Resize the FrameBuffer
   */
  SbBool resize(const SbVec2s size);

  /**
   * Gets current size as an SbVec2s.
   */
  const SbVec2s& getSize() const;

  /**
   * Specifies settings for the FrameBuffer creation.
   * Indicates if it must be created to be compliant with rendering to texture and also sets texture attributes.
   */
  void setRenderToTexture(SbBool enable, GLenum format = GL_RGB, GLenum target = GL_TEXTURE_2D, SbBool hasDepth = FALSE,SbBool autoMipmap = FALSE);

  /**
   * return the attached texture ID
   */
  GLuint getTexture() const;

  /**
   * return the attached texture Format
   */
  GLenum getTextureFormat() const;

  /**
   * return the attached texture Target
   */
  GLenum getTextureTarget() const;

  /**
   * Set this Framebuffer as the current rendering target
   */
  SbBool bind() const;
  
  /**
   * Set the main Framebufer as the rendering target
   */
  static void unbind();


SoINTERNAL public:
 
  private:
    // check the current FBO status creation
    SbBool checkStatus() const;
    
    // current size of the FrameBuffer
    SbVec2s m_size;
    
    // current internal size of the framebuffer
    SbVec2s m_internal_size;

    SbBool m_renderToTexture;
    SbBool m_autoMipmap;
    SbBool m_hasDepth;
    GLenum m_textureFormat;
    GLenum m_textureTarget;
    
    // OpenGL related variables
    GLuint fbo_texID;
    GLuint fbo_depth_rb;
    GLuint fbo_ID;
};

#endif // _SO_FRAME_BUFFER_H_
