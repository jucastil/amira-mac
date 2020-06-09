/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_FRAME_BUFFER_H_
#define _SO_FRAME_BUFFER_H_

#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>
#include <Inventor/sys/SoGLType.h>

#include <Inventor/SoGLRenderToBuffer.h>

#include <Inventor/STL/vector>

class SoGLRenderBuffer;
class SoState;
class SoGLTexture;
class SoGLObjectCache;

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
 * @VSGEXT Create an OpenGL FrameBuffer
 * @ingroup General
 *
 * @DESCRIPTION
 *    This class encapsulates an OpenGL FrameBuffer object (FBO) which may be used for
 *    accelerated off-screen rendering. Unlike a pixmap or offscreen
 *    bitmap, a FrameBuffer is allocated in frame buffer memory and can be
 *    rendered to directly by the graphics hardware. Unlike Pbuffer, this object
 *    is not dependent on the windowing system and shares the current OpenGL context.
 *
 *    FrameBuffers are only available if the graphics hardware supports
 *    OpenGL 2.0 or the OpenGL framebufferobject extension. This extension
 *    is named "GL_frame_buffer_object".
 *
 * @SEE_ALSO
 *    SoPBuffer, SoOffscreenRenderer
 *
 */

class INVENTOR_API SoFrameBufferObject : public SoGLRenderToBuffer {

public:
  /** Attachement */
  enum Attachment
  {
    /** Color attachment 0 */
    COLOR_ATTACHMENT0,
    /** Color attachment 1 */
    COLOR_ATTACHMENT1,
    /** Color attachment 2 */
    COLOR_ATTACHMENT2,
    /** Color attachment 3 */
    COLOR_ATTACHMENT3,
    /** Color attachment 4 */
    COLOR_ATTACHMENT4,
    /** Color attachment 5 */
    COLOR_ATTACHMENT5,
    /** Color attachment 6 */
    COLOR_ATTACHMENT6,
    /** Color attachment 7 */
    COLOR_ATTACHMENT7,
    /** Color attachment 8 */
    COLOR_ATTACHMENT8,
    /** Color attachment 9 */
    COLOR_ATTACHMENT9,
    /** Color attachment 10 */
    COLOR_ATTACHMENT10,
    /** Color attachment 11 */
    COLOR_ATTACHMENT11,
    /** Color attachment 12 */
    COLOR_ATTACHMENT12,
    /** Color attachment 13 */
    COLOR_ATTACHMENT13,
    /** Color attachment 14 */
    COLOR_ATTACHMENT14,
    /** Color attachment 15 */
    COLOR_ATTACHMENT15,
    /** Depth attachment */
    DEPTH_ATTACHMENT,
    /** Stencil attachment */
    STENCIL_ATTACHMENT,
    /** Last attachment */
    LAST_ATTACHMENT
  };

   /**
   * Constructor.
   * Creates an object of this class but does *not* create the FrameBuffer
   * until resize is called.
   */
  SoFrameBufferObject();

  /**
   * Destructor
   */
  ~SoFrameBufferObject();

  /**
   * Inits the Frame buffer object class.
   */
  static void initClass();

  /**
   * Cleans the Frame buffer object class.
   */
  static void exitClass();

  /**
   * No Effect. Compatibility with PBuffer.
   */
  void setDisplayConnection(SbGlContextHelper::Display);
  void setContextForSharing(SoGLContext *context);

  /**
   * Returns TRUE if FrameBuffers are available on this system. @BR
   * There is no guarantee it is possible to create a framebuffer
   * (depends on requested size, available memory, etc).
   */
  static SbBool isAvailable( SoState* state = NULL );

  /**
   * Returns TRUE if multisampling is available for FrameBuffers on this system. @BR
   * There is no guarantee it is possible to enable multisampling
   * (depends on requested samples).
   */
  static SbBool isMultisamplingAvailable( SoState* state = NULL );

  /** 
   * Returns the maximum number of samples usable for multisampling.
   */
  static int getMaxSamples( SoState* state = NULL );

  /**
   * Sets the number of samples for multisampling.
   */
  void setSamplesCount(int samples);

  /**
   * Returns the number of samples actually used by the FBO.
   * The value is not correct right after a call to setSamplesCount but after the first bind/unbind
   * operation.
   */
  int getActualSamplesCount() const;

  /**
   * Resize the FrameBuffer
   */
  SbBool resize(const SbVec2s &size);

  /**
   * Gets current size as an SbVec2s.
   */
  SbVec2s getSize() const;

  /**
   * Specifies settings for the FrameBuffer creation.
   * Indicates if it must be created to be compliant with rendering to texture and also sets texture attributes.
   */
   void setRenderToTexture(SbBool enable, TextureFormat format = TEXTURE_RGB,
                           TextureTarget target = TEXTURE_2D, SbBool autoMipmap = FALSE,
                           SbBool hasDepth = FALSE);

  /**
   * Returns the attached texture ID
   */
  GLuint getTexture() const;

  /**
   * Returns the attached texture Format
   */
  GLenum getTextureFormat() const;

  /**
   * Returns the attached texture Target
   */
  GLenum getTextureTarget() const;

  /**
   * Set this Framebuffer as the current rendering target
   */
  SbBool bind(SoState* state = NULL, bool bindMultisampleFBO = true);

  /**
   * Set the previous framebuffer object as the rendering target
   */
  void unbind();

  /**
   * Blit the multisampling FBO to the regular FBO. 
   * This function must be called before using the result of the frame buffer operation. 
   * If there is no MSAA FBO active the function doesn't do anything, so it is safe
   * to call it all the time.
   */
  void flush(SoState* state = NULL);

  /**
   * Attach the framebuffer to the current texture object. @BR
   * If bindDepth is set to TRUE, attach the depth instead of the color buffer.
   */
  SbBool bindToTexture(SbBool bindDepth = FALSE, GLuint texObj=-1);

  /**
   * Release the FrameBuffer from the current texture object. @BR
   * Required before rendering again.
   * If bindDepth is set to TRUE, releases the depth buffer instead of the color buffer
   */
  SbBool releaseTexImage(SbBool bindDepth = FALSE );

  /**
   * Select the face to be used when the rendering target is a cube map.
   */
  SbBool selectCubeMapFace(CubeMapTextureFace face);

  /**
   * Create a framebuffer with the specified size. @BR
   * Limited to 32767.
   * Returns TRUE if successful
   */
  SbBool create(SbVec2s size);

  /**
   * Create a framebuffer with the specified size. @BR
   * For sizes greater than 32767.
   * Returns TRUE if successful
   */
  SbBool create(SbVec2i32 size);

  /**
   * Resize framebuffer. @BR
   * Limited to 32767.
   * Returns TRUE if successful
   */
  SbBool resize(const SbVec2i32 &size);

  /**
   * Create a framebuffer with the specified size. @BR
   * For sizes greater than 32767.
   * Returns TRUE if successful
   */
  const SbVec2i32& getSize_i32() const;

  /**
   * Make framebuffer current for OpenGL rendering. @BR
   * Returns TRUE if successful
   */
  SbBool makeCurrent();

  /**
   * Disable render to buffer
   */
  void disable();

  /**
   * Set a new graphics configuration template.
   */
  void setGraphicConfigTemplate(SoGLGraphicConfigTemplate* gTemplate);

  /**
   * Returns the current graphics configuration template.
   */
  SoGLGraphicConfigTemplate* getGraphicConfigTemplate();

  /**
   * Set the current pixel format. @BR  This method allows an application to
   * set a pixel format that has extended attributes that can't be specified in
   * a PFD struct. The specified format must support OpenGL.
   */
  void setPixelFormat(int format);

  /**
   * Returns the current pixel format. @BR This method allow an application to
   * query a pixel format that has extended attributes that can't be specified in
   * a PFD struct.
   */
  int getPixelFormat();

SoINTERNAL public:
  
  GLuint getId(SoState* state = NULL);

  GLenum getStatus() const;

  /**
   *
   * No Effect. Compatibility with PBuffer.
   *
   */
  virtual void setFaceTarget(int faceTarget);

  /**
   * Return true if the binded framebuffer object is valid
   */
  bool isValid() const;

  /**
   * Return the depth render buffer.
   */
  SoGLRenderBuffer* getDepthRenderBuffer() const
  { return m_depthRenderBuffer;}

  /**
   * Attach mipmap level of a texture texId to the currently binded frame buffer object
   * target must be GL_TEXTURE_2D or GL_TEXTURE_RECTANGLE
   * Returns true on success.
   */
  bool attachTexture2D(Attachment attachment, GLenum target,
                       GLuint texId, int level);
  /**
   * Attach mipmap level of a texture texId to the currently binded frame buffer object
   * Returns true on success.
   */
  bool attachTexture1D(Attachment attachement, GLuint texId, int level);

  /**
   * Attach mipmap level of texture texId to the currently binded frame buffer object
   * Returns true on success.
   */
  bool attachTexture2D(Attachment attachement, GLuint texId, int level);

  /**
   * Attach layer with mipmap level of array texture texId to the currently binded frame buffer object
   * Returns true on success.
   */
  bool attachTexture2DArray(Attachment attachement, GLuint texId, int level, int layer);

  /**
   * Attach mipmap level of texture texId to the currently binded frame buffer object
   * Returns true on success.
   */
  bool attachTexture3D(Attachment attachement, GLuint texId, int level, int zoffset);

  /**
   * Attach the specified face of a cubemap texture to the currently
   * binded frame buffer object.
   * Returns true on success.
   */
  bool attachTextureCubeMap(Attachment attachment, GLuint texId, int level,
                            CubeMapTextureFace face);

  /**
   * Attach mipmap level of a texture to the currently binded frame buffer object
   * Returns true on success.
   */
  bool attachTexture1D(SoState* state, Attachment attachement,
                       SoGLTexture* tex, int level);

  /**
   * Attach mipmap level of texture to the currently binded frame buffer object
   * Returns true on success.
   */
  bool attachTexture2D(SoState* state, Attachment attachement, SoGLTexture* tex, int level);

  /**
   * Attach layer of texture to the currently binded frame buffer object
   * Returns true on success.
   */
  bool attachTexture2DArray(SoState* state, Attachment attachement, SoGLTexture* tex,
                       int level, int layer);

  /**
   * Attach mipmap level of texture to the currently binded frame buffer object
   * Returns true on success.
   */
  bool attachTexture3D(SoState* state, Attachment attachement, SoGLTexture* tex,
                       int level, int zoffset);

  /**
   * Attach the specified face of a cubemap texture to the currently
   * binded frame buffer object.
   * Returns true on success.
   */
  bool attachTextureCubeMap(SoState* state, Attachment attachment, SoGLTexture* tex,
                            int level, CubeMapTextureFace face);

  /**
   * Attach renderbuffer to the specified attachment
   * Returns true on success.
   */
  bool attachRenderBuffer(SoState* state, Attachment attachement, SoGLRenderBuffer* renderBuffer);

  /**
   * Attach renderbuffer of id renderBufferId to the specified attachment
   * Returns true on success.
   */
  bool attachRenderBuffer(Attachment attachement, GLuint renderBufferId);

  /**
   * Return the texture corresponding to the specified attachment
   */
  SoGLTexture* getTextureAttachment(Attachment attachment);

  /**
   * Return the render buffer corresponding to the specified attachment
   */
  SoGLRenderBuffer* getRenderBufferAttachment(Attachment attachment);

  /**
   * Check the current FBO status creation and write it on console
   * The FBO must be binded
   */
  SbBool checkStatus() const;

  /** Return true, if the texture is valid for the current context */
  bool isValid(SoState* state);

  /**
  * Convert attachment into the corresponding OpenGL enum
  */
  static GLenum getGLAttachment(Attachment attachment);


  private:

    SbBool bindInternal(SoState* state = NULL, bool bindMultisampleFBO = true);

    bool attachRenderBuffer(Attachment attachment, GLuint renderBufferId, bool createMultisampled);

    /**
     * Convert SoGLGraphicConfigTemplate into texture format for
     * compatibility with pbuffers
     */
    TextureFormat graphicConfigTemplateToTextureFormat(SoGLGraphicConfigTemplate *gct);

    /**
     * Get the texture depth format from SoGLGraphicConfigTemplate for
     * compatibility with pbuffers
     */
    TextureFormat getDepth(SoGLGraphicConfigTemplate *gct);

    /**
     * Return pow(max(bits), 2)
     */
    int getMaxPow2Bits(SbVec4i32 bits);

    /**
     * Create everything OpenGL related according to previous call to
     * setRenderToTexture, setSize...
     */
    bool update(SoState* state = NULL);

    /**
     * Setup the MSAA fbo according to the number of samples
     */
    void setupMSAA(SoState* state);

    /**
     * blit the content of the MSAA to the regular FBO if the MSAA FBO exists.
     */
    void blitMSAA(SoState* state);

    /**
     * Clear all the data allocated for the MSAA.
     */
    void clearMSAA(SoState* state);

    // current size of the FrameBuffer
    SbVec2i32 m_size;
    bool m_needResize;

    SbBool m_renderToTexture;
    SbBool m_autoMipmap;
    SbBool m_hasDepth;
    GLenum m_textureFormat;
    TextureFormat m_textureFormatIV;
    GLenum m_textureTarget;

    // OpenGL related variables
    GLuint m_internalTexID;
    SoGLRenderBuffer* m_depthRenderBuffer;

    SoGLObjectCache* m_fboCache;

    //New FBO
    bool m_needUpdate;

    //Id of previously binded fbos
    std::vector<GLint> m_previousFboIds;

    //Textures and rb currently attached to the fbo
    std::vector<SoGLTexture*> m_attachedTextures;
    std::vector<SoGLRenderBuffer*> m_attachedRenderBuffers;

    // Multisample FBO
    int m_numSamples;
    SoGLObjectCache* m_fboMSAACache;
    std::vector<SoGLRenderBuffer*> m_attachedMSAARenderBuffers;

    SoGLRenderBuffer* m_depthRenderBufferMSAA;
    SoGLRenderBuffer* m_internalTexMSAA;

    // - Indicates if the FBO need to be blited.
    bool m_fboBlited;

    static int s_framebuffer_extensionID;
    static int s_texture3D_extensionID;
    static int s_framebuffer_blit_extensionID;
    static int s_framebuffer_multisample_extensionID;
    static int s_ogl12_extensionID;
};
/*****************************************************************************/

inline void
SoFrameBufferObject::setDisplayConnection(SbGlContextHelper::Display)
{}

inline void
SoFrameBufferObject::setContextForSharing(SoGLContext *)
{}

inline void
SoFrameBufferObject::setFaceTarget(int)
{}

#ifdef _WIN32
#pragma warning( pop )
#endif

#endif // _SO_FRAME_BUFFER_H_
