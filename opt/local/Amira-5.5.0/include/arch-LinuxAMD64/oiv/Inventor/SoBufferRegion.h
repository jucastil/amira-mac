/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas Daguise (Oct 2003)
**=======================================================================*/
#ifndef  _SO_BUFFER_REGION_H
#define  _SO_BUFFER_REGION_H

#include <Inventor/SoPBuffer.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/sys/SoGLType.h>

/**
 * 
 * @VSGEXT Creates an OpenGL BufferRegion.
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 *    The purpose of this class is to save and restore a portion of the
 *    frame buffer. If possible, it will create
 *    an OpenGL buffer region object which may be used to
 *    accelerate rendering.
 *    The buffer region extension is a mechanism that allows an area of
 *    an OpenGL window to be saved in off-screen memory for quick
 *    restores. The off-screen memory can either be frame buffer memory
 *    or system memory, although frame buffer memory might offer better
 *    performance.
 *
 *    A buffer region can be created for the front color, back color,
 *    depth, and/or stencil buffer.
 *
 *    Buffer regions are only available if the graphics hardware supports
 *    OpenGL 1.2.1 or the OpenGL Buffer Region extension.
 *    On Windows this extension is named "WGL_ARB_buffer_region".
 *    You can disable the use of buffer regions by setting the
 *    OIV_BUFFER_REGION_ENABLE environment variable to '0'. By default, if this
 *    variable is not defined, buffer regions will be used if available.
 *
 *    This class tries first to use the buffer region extension. If this extension
 *    is not available, then it tries to use Pbuffers.
 *    To use Pbuffers, the graphics hardware must support the OpenGL Pbuffer extension
 *    and the OpenGL MakeCurrentRead extension. If either one of these two extensions 
 *    is not available,
 *    the last resort is to use glReadPixels and glDrawPixels.
 * 
 * @SEE_ALSO
 *    SoPBuffer
 * 
 * 
 */ 

class INVENTOR_API SoBufferRegion {

public:

  enum BufferType {
    FrontColor = 0x01,
    BackColor  = 0x02,
    Depth      = 0x04,
    Stencil    = 0x08
  };

  /**
   * Constructor. 
   * @param hDC Build a new Buffer Region for the specified device context.
   * @param type User must specify which buffer(s) to save and restore.
   * @param sMode Specifies if the buffer region is used in stereo or in monoscopic mode.
   */
  SoBufferRegion(SbGlContextHelper::Display display, unsigned int type, SoCamera::StereoMode sMode = SoCamera::MONOSCOPIC);

  /**
   * Destructor.
   */
  ~SoBufferRegion();

  /**
   * Saves the buffers.
   */
  void save(int x, int y, int width, int height);

  /**
   * Restores the buffers.
   */
  void restore(int x, int y, int width, int height, int xSrc, int ySrc);

  
  /** 
   * Returns TRUE if buffer region is valid for current passed size and position.
   */
  bool isValid( int x, int y, int width, int height );

private:
 
  SoPBuffer* m_pBuffer;
  GLfloat* m_bufferLeft;
  GLfloat* m_bufferRight;
  GLfloat* m_depthBuffer;
  GLfloat* m_stencilBuffer;

  void* m_bufferRegionHandle;
  GLuint m_region;

  unsigned int m_type;
  GLuint m_glType;
  SoCamera::StereoMode m_sMode;
  SbVec2s m_pos;
  SbVec2s m_size;

  SbGlContextHelper::Display m_currentDC;

  static SbBool s_isInitializedBufferRegion;
  static SbBool s_isInitializedMakeCurrentRead;
  static SbBool s_useExtVersion;
  static SbBool s_isAvailableBufferRegion;
  static SbBool s_isAvailablePBuffer;  // alternative to buffer region.
  static SbBool s_useReadDrawPixels;   // alternative to pBuffer.
};

#endif // _SO_BUFFER_REGION_H
