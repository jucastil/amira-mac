/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_PBUFFER_H_
#define _SO_PBUFFER_H_

#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SoGLRenderToBuffer.h>
#include <Inventor/helpers/SbGlContextHelper.h>

// In order to make this interface system-independent we need a
// portable opaque type that can contain any of the system-dependent
// types used internally (eg. XID, GLXContext, HANDLE, HDC, etc).
#ifndef _SBHANDLE_
#define _SBHANDLE_ 1
typedef void *SbHandle;
#endif

class SoGLContext;
class SoGLGraphicDevice; 
class SoGLGraphicConfig;
class SoGLWindow;

/**
 * @VSGEXT Creates an OpenGL Pbuffer.
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 *    This class creates an OpenGL Pbuffer object which may be used for
 *    accelerated off-screen rendering. Unlike a pixmap or offscreen
 *    bitmap, a Pbuffer is allocated in frame buffer memory and can be
 *    rendered to directly by the graphics hardware.
 *
 *    For most applications, using the SoOffscreenRenderer class will be
 *    more convenient. SoOffscreenRenderer uses Pbuffers automatically.
 *
 *    Pbuffers are only available if the graphics hardware supports
 *    OpenGL 1.2 or the OpenGL Pbuffer extension. On UNIX this extension
 *    is named "GLX_pbuffer" or "GLX_SGIX_pbuffer". On Windows this
 *    extension is named "WGL_ARB_pbuffer" or "WGL_EXT_pbuffer".
 * 
 * @SEE_ALSO
 *    SoOffscreenRenderer
 * 
 * 
 */ 

class INVENTOR_API SoPBuffer : public SoGLRenderToBuffer {
    
 public:
  /**
   * Constructor.
   * Creates an object of this class but does *not* create a Pbuffer.
   * Use the create() method to attempt creation of a Pbuffer.
   */
  SoPBuffer();

  /**
   * Destructor
   */
  ~SoPBuffer();

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
  SbBool create(SbVec2s size);

  /**
   * Creates a Pbuffer with the specified size.
   * For sizes greater than 32767.
   * Returns TRUE if successful
   */
  SbBool create(SbVec2i32 size);
  /**
   * Makes Pbuffer current for OpenGL rendering.
   * Returns TRUE if successful
   */
  SbBool makeCurrent();

  /**
   * Disable render to buffer
   * Returns TRUE if successful
   */
  void disable();

  /**
   * Share OpenGL object with the current context
   */
  void shareCurrentContext();

  /**
   * Resizes Pbuffer.
   * Limited to 32767.
   * Returns TRUE if successful
   */
  SbBool resize(const SbVec2s &size);

  /**
   * Resizes Pbuffer.
   * For sizes greater than 32767.
   * Returns TRUE if successful
   */
  SbBool resize(const SbVec2i32 &size);

  /**
   * Gets current size as an SbVec2s.
   */  
  SbVec2s getSize() const;  

  /**
   * Gets current size as an SbVec2i32
   */
  const SbVec2i32& getSize_i32() const;


  /**
   * Sets the current pixel format. This method allows an application to
   * set a pixel format that has extended attributes that can't be specified in
   * a PFD struct. The specified format must support OpenGL and drawing to a pbuffer.
   */
  void setPixelFormat(int format);

  /**
   * Returns the current pixel format. This method allow an application to
   * query a pixel format that has extended attributes that can't be specified in
   * a PFD struct. 
   */
  int getPixelFormat();

  /**
   * Specifies settings for the Pbuffer creation.
   * Indicates if it must be created to be compliant with rendering to texture and also sets texture attributes.
   */
  void setRenderToTexture(SbBool enable, TextureFormat format = TEXTURE_RGB, TextureTarget target = TEXTURE_2D, 
                          SbBool autoMipmap = FALSE, SbBool hasDepth = FALSE);

   /**
    * Binds the Pbuffer buffer to a texture object (The current one, texObj is not used)
    * If bindDepth is set to TRUE, binds the depth buffer instead of the color buffer.
    */
  virtual SbBool bindToTexture(SbBool bindDepth = FALSE, GLuint texObj=-1);
  
  /**
   * Releases the Pbuffer from the current texture object.
   * Required before rendering again.
   * If bindDepth is set to TRUE, releases the depth buffer instead of the color buffer
   */
  SbBool releaseTexImage(SbBool bindDepth = FALSE);


  /**
   * Selects the face to be used when the rendering target is a cube map.
   */
  SbBool selectCubeMapFace(CubeMapTextureFace face);

  /**
   * Gets the current graphics configuration template.
   */
  SoGLGraphicConfigTemplate* getGraphicConfigTemplate();
    
 
  /**
   * Sets a new graphics configuration template. 
   */
  void setGraphicConfigTemplate(SoGLGraphicConfigTemplate* gTemplate);



  
 SoEXTENDER public:

  // ----- Methods using system-dependent types -----
  // (only needed for special cases)

  /**
   * Sets X display connection to use for this Pbuffer.
   * Must be set before calling the create() method.
   *
   * On UNIX systems the parameter is a "Display *".
   * On Win32 systems this method is ignored.
   */
  virtual void setDisplayConnection(SbGlContextHelper::Display display);

  /** 
   * Sets OpenGL render context for display list sharing.
   * Must be set before calling the create() method.
   * There is no guarantee that sharing will be allowed.
   * 
   */
  virtual void setContextForSharing(SoGLContext *context);

  /**
   * Gets system-dependent handle of Pbuffer object.
   * Only valid if a Pbuffer has been successfully created.
   *
   * On UNIX systems the returned value is an XID (GLXPBuffer).
   * On Win32 systems the returned value is a HPBUFFERARB.
   */
  SbHandle getHandle();

 /**
   * Get system dependent display for Pbuffer.
   * Only valid if a Pbuffer has been successfully created.
   */
  SbGlContextHelper::Display getDisplay();

  /**
   * Gets OpenGL render context
   * Only valid if a Pbuffer has been successfully created.
   *
   * On UNIX systems the returned value is a GLXContext.
   * On Win32 systems the returned value is an HGLRC.
   */
  SoGLContext* getContext();

  /**
  * Return TRUE if the render buffer is a pbuffer.
  */
  virtual SbBool isPBuffer()
  { return TRUE; }

 SoINTERNAL public:

  // register in database
  static void initClass();
  // unregister from database
  static void exitClass();

  // Gets the current graphic device.
  SoGLGraphicDevice* getGraphicDevice();

  // Gets the current graphic configuration.
  SoGLGraphicConfig* getGraphicConfig();
  
  virtual void setFaceTarget(int faceTarget);

  // Enables alpha channel for pbuffer
  void setAlpha( SbBool enable ) { m_needAlpha = enable; } // Disabled by default
  SbBool hasAlpha() const { return m_needAlpha; }
  
 protected:
  SbHandle m_fbconfig;
  SbHandle m_pbuffer ;

  SbGlContextHelper::Display m_display;
  SbBool   m_displayIsInternal;

  // handles if user request to share the PBuffer with an existing context
  SoGLContext *m_shareContext;
  bool   m_shared;


  SbVec2i32  m_size_i32;
  SbVec2s    m_size;

  SoGLGraphicDevice* m_currentGraphicDevice;
  SbBool m_currentGraphicConfigIsUsed;
  SoGLGraphicConfig* m_currentGraphicConfig;
  SbBool m_currentGraphicDeviceIsUsed;
  SbBool m_renderToTexture;
  TextureFormat m_textureFormat;
  TextureTarget m_textureTarget;
  bool m_autoMipmap;

  int m_cubeMapFaceAttr;
  int m_faceTarget;

private:
  void cleanUpCreate( SoGLWindow* glWindow );

  // this is our openGL context
  SoGLContext* m_glContext;
  SoGLContext* m_baseContext;

  // Needed for a PFD with alpha channel enabled (Windows only)
  SbBool m_needAlpha;

  bool m_isDisabled;

  // handle OIV_PBUFFER_DEBUG envvar
  static SbBool s_debugFlag;
  static void debugPrint(const char *format, void *p1 = NULL, void *p2 = NULL, void *p3 = NULL);

  // handle OIV_PBUFFER_ENABLE envvar
  static SbBool s_isForcedDisabled;

};

#endif //_SO_PBUFFER_H_

