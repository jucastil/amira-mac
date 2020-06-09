/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_WIN_INTERLACEDSTEREO
#define _SO_WIN_INTERLACEDSTEREO

#include <Inventor/components/stereo/SoBaseStereo.h>
#include <Inventor/sys/SoGLType.h>

class SoStereoViewer;

/**
 * @VSGEXT Class for interlaced stereo support.
 * 
 * @ingroup Stereo
 * 
 * @DESCRIPTION
 *   This class implements the interlaced stereo type. Using the interlaced mode, the
 *   stereo effect is achieved using special devices (projectors,...) that translate
 *   an interlaced image into a stereoscopic view. Alternating scan lines display
 *   images for the left and right eyes.
 *   
 *   The interlaced mode can work in two modes: fast or best. This is simply a matter
 *   of quality. Due to the interlacing, lines close to horizontal can appear as
 *   dotted lines. In best mode, those parts of the model are drawn as if they were
 *   thicker. By default, the mode is fast.
 * 
 * @SEE_ALSO
 *    SoStereoViewer,
 *    SoBaseStereo,
 *    SoWinViewer
 * 
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 * 
 */ 

class INVENTORW_API SoInterlacedStereo : public SoBaseStereo {
 public:
   /** Interlaced modes */
  enum InterlacedMode {
    /** Horizontal (default) */
    HORIZONTAL = 0, // default
    /** Vertical */
    VERTICAL
  } ;

  /**
   * Constructor.
   */
  SoInterlacedStereo(SoStereoViewer *stereoVwr = NULL);
  
  /**
   * Destructor.
   */
  ~SoInterlacedStereo();

  /**
   * Sets stereo reversal.
   */
  virtual void reverseStereoView(SbBool reverse);
  /**
   * Queries stereo reversal.
   */
  virtual SbBool isStereoViewReversed();

  /**
   * Sets interlaced mode. Default is HORIZONTAL.
   */
  void setInterlacedMode(InterlacedMode mode) { interlacedMode = mode; }
  /**
   * Queries interlaced mode.
   */
  InterlacedMode getInterlacedMode() { return interlacedMode; }

  /**
   * Sets screen interlacing.
   * If screen is TRUE (default), the line interlacing is done according to the
   * screen (if the window is moving, the first line might be either an even or an
   * odd line). Otherwise, do the interlacing according to the window itself (first
   * line is always even).
   */
  void setScreenInterlacing(SbBool screen) { screenInterlacing = screen; }
  /**
   * Queries screen interlacing.
   */
  SbBool isScreenInterlacing() { return screenInterlacing; }

  /**
   * Sets fast interlacing mode. Default is TRUE.
   */
  void setFastInterlacing(SbBool fast=TRUE) { withQuality = !fast; }
  /**
   * Queries fast interlacing mode.
   */
  SbBool isFastInterlacing() { return !withQuality; }

  /**
   * Renders the stereo view.
   */
  virtual void renderStereoView();

  /**
   * Always returns SoBaseStereo::INTERLACED_STEREO.
   */
  virtual StereoViewType getStereoViewType() { return INTERLACED_STEREO; }
  /**
   * Queries ability to clear before rendering.
   */
  virtual SbBool canClearBeforeRender() { return clearBuffer; }

  /**
   * Always returns FALSE. (Although special hardware may be required, this flag only
   * indicates if a special graphics board is required. It's not, hence the return
   * value of FALSE.)
   */
  virtual SbBool requireHardware() { return FALSE; }
        
  /**
   * Clears stereo.
   */
  virtual void clearStereo();

  /**
   * Enable image adjustment specific to Sharp LCD displays.
   */
  virtual void enableGreenShift( SbBool enable ) { m_doGreenShift = enable; }

  /**
   * Query green shift setting
   */
  virtual SbBool isGreenShiftEnabled() const { return m_doGreenShift; }

 SoINTERNAL public:
  /* stereo for MPViewers */
  void doLeftEyeSettings();
  void doRightEyeSettings();
  void doMonoscopicSettings();

 protected:
  /**
   * Renders using textures (copyTexSubimage) - called from renderStereoView
   */
  virtual SbBool renderUsingTextures();

 private:
  InterlacedMode interlacedMode;
  SbBool reversed;
  SbBool clearBuffer;
  SbBool screenInterlacing;
  SbBool withQuality;
  GLfloat * pixels, * result;
  GLubyte * mask;
  int width, height;
  SbBool  m_doGreenShift;

  // State for texture based rendering
  GLuint  m_texId[2];
  GLsizei m_texWidth;
  GLsizei m_texHeight;
};

#endif // _SO_WIN_INTERLACEDSTEREO


