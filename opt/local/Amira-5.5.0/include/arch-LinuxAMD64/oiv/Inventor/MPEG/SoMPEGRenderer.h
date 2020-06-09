/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. HUFSCHMITT (Jul 2001)
**=======================================================================*/
/*=======================================================================
** Modified by : Tristan Mehamli (Nov 2009)
**=======================================================================*/

#ifndef _SO_MPEGRENDERER_
#define _SO_MPEGRENDERER_

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/helpers/SbGlContextHelper.h>
#include <Inventor/SbBasic.h>

#include <Inventor/STL/list>

class TGSMPEG;
class SbThreadSignal;
class SbThreadMutex;

/*----------------------------------------------------------------------------*/

#ifdef OIV_NET_DOC
/**
* @VSGEXT Base class for generating MPEG output from a scene graph.
* 
* @ingroup MPEG
* 
* @DESCRIPTION
*   This class is the base class for creating MPEG video output from a given 
*   scene graph.
*   Warning : writing in multiple streams at the same time is not possible.
*
*   The #SetShareContext method allows you to
*   share an already existing OpenGL context with the MPEG renderer. 
*   This avoids the necessity to re-generate textures and display lists 
*   if they are already available in another OpenGL context (the viewer 
*   context, for instance). This can dramatically reduce offscreen 
*   rendering time, depending on your scene graph. 
*   
*   A corresponding query method (#GetShareContext) is also available. 
*   The #setShareContext method allows you to
*   share an already existing OpenGL context with the MPEG renderer. 
*   This avoids the necessity to re-generate textures and display lists 
*   if they are already available in another OpenGL context (the viewer 
*   context, for instance). This can dramatically reduce offscreen 
*   rendering time, depending on your scene graph. 
*    
*   A corresponding query method (#getShareContext) is also available.
*
*   Here's how you might use these methods to share OpenGL contexts:
* 
* @SEE_ALSO
*    SoMPEGNavRenderer, SoMPEGFrameRenderer
* 
* 
*/ 
#else
/**
* @VSGEXT Generate MPEG video output from a scene graph.
* 
* @ingroup MPEG
* 
* @DESCRIPTION
*   This class is the basic class for creating MPEG video output from a 
*   scene graph.
*
*   Warning : Writing in multiple streams at the same time is not possible.
*
*   This class is used by the viewer classes to record MPEG video (see
*   for example SoWinRenderArea::setMPEGRecorder).  The default right-mouse
*   popup menu in the viewer classes provides an option to display a video
*   recording dialog box.  This dialog allows the user to conveniently
*   start and stop recording the scene in the viewer window.
*
*   Two specialized classes SoMPEGFrameRenderer and SoMPEGNavRenderer are
*   provided to give applications more control over video generation.
*
*   The #setShareContext method allows you to
*   share an already existing OpenGL context with the MPEG renderer. 
*   This avoids the necessity to re-generate textures and display lists 
*   if they are already available in another OpenGL context (the viewer 
*   context, for instance). This can dramatically reduce offscreen 
*   rendering time, depending on your scene graph. 
*   
*   A corresponding query method (#getShareContext) is also available. 
*
*   Here's how you might use these methods to share OpenGL contexts:
* <PRE> 
*       pMPEGRenderer->setShareContext(pViewer->getShareContext());
* </PRE>
* 
* @SEE_ALSO
*    SoMPEGNavRenderer, SoMPEGFrameRenderer
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoMPEGRenderer 
{
public:

  /**
   * Constructor.
   */
  SoMPEGRenderer();

  /**
   * Destructor.
   */
  virtual ~SoMPEGRenderer();

  /** Components */
  enum Components 
  {
    /** Luminance */
    LUMINANCE = 1,
    /** Luminance transparency */
    LUMINANCE_TRANSPARENCY = 2,
    /**
     *  (Default) 
     */
    RGB = 3,
    /** RGB and Alpha channel */
    RGB_TRANSPARENCY = 4
  };

  /**
   * Specifies the MPEG output file name.
   * @I numFrames @i gives an estimate of the number of frames that
   * the MPEG output will contain.
   * Returns FALSE if the file cannot be opened, TRUE otherwise.
   */
  SbBool openFile( const char* filename, unsigned int numFrames = 10000 );

  /**
   * Closes the MPEG file previously opened with the openFile() method.
   */
  void closeFile();

  /**
   * Sets the file pointer for the MPEG output.
   */
  void setFilePointer( FILE* fp );

  /**
   * Gets the MPEG file pointer.
   */
  FILE* getFilePointer() const;

  /**
   * Sets the frame pixel size. The width and height of the frame must be a 
   * multiple of 16. If they are not, they are reduced to the next lower 
   * multiple of 16.
   *  
   * By default, width and height values are 96.
   *
   * NOTE: This method must be called before #openFile or 
   * #setFilePointer in order to have an effect. Calling it after
   * calling #openFile or #setFilePointer may cause undesirable
   * results.
   */
  void setSize( const SbVec2s& size );

  /**
   * Gets the frame pixel size. These values may be different from those given
   * by the setSize() method.
   */
  SbVec2s getSize() const;

  /**
   * Set the number of color components of the frames recorded.
   */
  void setComponents( const Components components );

  /**
   * Returns the number of color components of the frames recorded.
   */
  SoMPEGRenderer::Components getComponents() const;

  /** 
   * Sets the scene graph used for generating frames in the MPEG output.
   */ 
  virtual void setSceneGraph( SoNode* node );

  /**
   * Gets the scene graph used for generating frames in the MPEG output.
   */
  SoNode* getSceneGraph() const;

  /**
   * Sets the background color for rendering each frame.
   * The default background color is 0 0 0 (black).
   *
   * The default value can be set using the environment variable
   * OIV_BACKGROUND_COLOR. Specify three floats (R, G, B) in the range 0. to 1.,  
   * separated by spaces.
   */
  void setBackgroundColor( const SbColor& c );

  /**
   * Gets the background color for rendering each frame.
   */
  SbColor getBackgroundColor() const;

  /**
   *  Sets the GL Render action used to generate each frame.
   *  If no render action is specified, an internal instance of an 
   *  SoGLRenderAction will be maintained with a viewport
   *  region set to the size given with the method setSize().
   */
  void setGLRenderAction( SoGLRenderAction* ra );

  /**
   *  Gets the GL Render action used to generate each frame.
   */
  SoGLRenderAction* getGLRenderAction() const;

  /**
   * Compression rate of the MPEG output.
   * Values are between 0 and 1. 
   * 0=no compression, 1=maximum compression.
   *
   * The default value is 0.3. 
   *
   * NOTE: This method must be called before #openFile or 
   * #setFilePointer in order to have an effect. Calling it after
   * calling #openFile or #setFilePointer may cause undesirable
   * results.
   */
  void setCompressionRate( float value ); 

  /**
   * Returns the compression rate
   */
  float getCompressionRate() const;

  /**
   * This method allows the user to specify a fixed bit rate.
   * This is useful when the MPEG output is to be put on a video CD, for example.
   * If you do not know what this rate means, you can use the default value (-1)
   * which indicates that the bit rate is variable.
   * The standards bit rates for VCD are 1205862 bps and 2726300 bps.
   * (It is the speed the MPEG stream is read by VCD players)
   *
   * The default value is   1205862.
   * The maximum value is 104857600.
   * NOTE: This method must be called before #openFile or 
   * #setFilePointer in order to have an effect. Calling it after
   * calling #openFile or #setFilePointer may cause undesirable
   * results.
   */
  void setBitPerSec( float mbps );

  /** 
   * Sets the number of frames per second encoded in the MPEG output.
   * It has nothing to do with the speed of playback.
   * The default value is 30.
   *
   * NOTE: This method must be called before #openFile or 
   * #setFilePointer in order to have an effect. Calling it after
   * calling #openFile or #setFilePointer may cause undesirable
   * results.
   */
  void setNumFramesPerSecond( float num );

  /**
   * Gets the number of frames per second to be encoded in the MPEG output.
   */
  int getNumFramesPerSecond();

  /**
   * Low level method to add a new frame to the MPEG output from a buffer of 
   * unsigned characters.
   * Each pixel is stored sequentially by scanline, starting
   * with the lower left corner. The data stored for each pixel is determined by the
   * components set before rendering (3 by default). 
   * Pixels are stored in RGBA order and are packed without any padding between pixels 
   * or scanlines.
   */
  void addFrame( const unsigned char* frame );

  /**
   * Sets the OpenGL context to be shared by the SoMPEGRenderer.
   * Its use is strongly recommended, because it can improve performance when 
   * switching between on-screen and off-screen rendering. This is because it allows 
   * the display lists and texture objects to be shared between the on-screen and 
   * off-screen render context.
   * The shared context info is normally obtained by calling the viewer's
   * @B getShareContext@b method.
   *
   * NOTE: It has no effect when the hardware (or driver) does not allow sharing 
   * with the off-screen context, for example if Pbuffers are not supported.
   */
  void setShareContext( const SbGLShareContext shareCxt );

  /**
   * Gets the OpenGL context shared by the SoOffscreenRenderer.
   */
  const SbGLShareContext getShareContext() const;

  /** 
   * Starts the recording.
   *
   * Note: a file must have been opened or a file pointer set.
   */
  void record();

  /** 
   * Pauses the recording.
   */
  void pause();

  /** 
   * Stops the recording and closes the opened file.
   */
  void stop();

  /** 
   * Returns true if this renderer is recording.
   */
  SbBool isRecording() const;

  /**
   * Tells the recorder that the viewer is idle.
   */
  void setViewerIsIdle( bool isIdle );
  bool isViewerIdle() const { return m_viewerIsIdle; };

  /*----------------------------------------------------------------------------*/
  SoINTERNAL public:
  /**
   * It computes the ratio between recorder frame rate and the viewer's FPS.
   * It is used for an adaptative encoding of the frames.
   */
  void computeRate( double curVwrFPS );

  /**
   * Adds the last frame of the stack to the stack of frames to encode.
   */
  void addIdleFrame();

  /**
   * Returns the number of frame left to encode 
   */
  int getNumFrameToEncode();

protected:
  SoMPEGRenderer& operator =( const SoMPEGRenderer& a );
  // Share context
  SbGLShareContext m_glShareContext;

private:
  // Recording
  void encodeTask(void);
  static void* encodeCB( void* data );
  static std::list<unsigned char*>* m_frameStack; // Streamed buffers stack
  // Synchronization between app thread and encoding thread
  static SbThreadMutex* m_stackMutex; // Used when accessing the stack.
  SbThread* m_stackThread;
  int m_frameSize, m_recFrameRate, m_frameCount;
  double m_rate;

  SbVec2s m_Size;
  SbColor m_BgColor;
  SoGLRenderAction* m_ra, *m_defaultRenderAction;
  TGSMPEG* m_mpeg;
  SoNode* m_SceneGraph;
  Components m_numComponents;
  bool m_viewerIsIdle;

  SbBool m_hasFileOpened, m_isRecording;
};/*----------------------------------------------------------------------------*/

#endif /* _SO_MPEGRENDERER_ */
