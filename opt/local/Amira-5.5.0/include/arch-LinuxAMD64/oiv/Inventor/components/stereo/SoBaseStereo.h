/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_WIN_STEREOVIEW_TYPE
#define _SO_WIN_STEREOVIEW_TYPE

#include <Inventor/Gui/SoGui.h>
#include <Inventor/sys/port.h>
#include <Inventor/SbBasic.h>

class SoStereoViewer;

/**
 * @VSGEXT Class for stereo management.
 * 
 * @ingroup Stereo
 * 
 * @DESCRIPTION
 *   This class defines a strategy of stereo management. Using a subclass of
 *   SoBaseStereo allows an SoWinViewer object to use a stereoscopic rendering
 *   mode.
 *
 *   Note: because of internal dependant calls between stereo classes and Open Inventor
 *   viewer classes, SoStereoViewer and SoBaseStereo (and inheriting classes) cannot be
 *   used without using SoWinViewer/SoXtViewer/SoQtViewer inheriting classes.
 * 
 * @SEE_ALSO
 *    SoStereoViewer,
 *    SoWinViewer,
 *    SoXtViewer,
 *    SoQtViewer
 * 
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 * 
 */ 

class INVENTORGUI_API SoBaseStereo {

 public:
   /** Stereo view types */
  enum StereoViewType {
    /**
     *  Monoscopic viewing 
     */
    NO_STEREO_VIEW     = 0,
    /**
     *  Two views interlaced in a single image 
     */
    INTERLACED_STEREO  = 1,
    /**
     *  Each view displayed in a half screen 
     */
    HALF_SCREEN_STEREO = 2,
    /**
     *  Two views superimposed on a single image 
     */
    RAW_STEREO         = 3,
    /** Ditto */
    OPENGL_STEREO      = 3,
    /**
     *  Each view is displayed through a color filter 
     */
    ANAGLYPH_STEREO    = 4,
    /** Ditto */
    ANAGLYPH           = 4,
#ifndef HIDDEN_FROM_DOC
    /**
     *  Uses the SSDI library to set the stereo 
     */
    SSDI_STEREO        = 5,
#endif

    PASSIVE_STEREO     = 6
  };
  
  /**
   * Constructor.
   */
  SoBaseStereo(SoStereoViewer *stereoViewer = NULL);
  
  /**
   * Destructor. The destructor calls clearStereo().
   */
  virtual ~SoBaseStereo();
  
  /**
   * Sets the stereo viewer.
   */
  void setStereoViewer(SoStereoViewer *viewer = NULL) { stereoViewer = viewer; }

  /**
   * Queries the stereo viewer.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  SoStereoViewer *getStereoViewer() { return stereoViewer; }
  
  /**
   * Sets stereo reversal. The left view becomes the right view, and the
   * right view becomes the left view.
   */
  virtual void reverseStereoView(SbBool reverse) = 0;
  /**
   * Queries stereo reversal.
   */
  virtual SbBool isStereoViewReversed() = 0;

  /**
   * Renders the stereo view. You can use the SoNoStereoView subclass to render
   * the view without any stereo effect.
   */
  virtual void renderStereoView() = 0;
  

  /**
   * Queries the stereo view type.
   */
  virtual StereoViewType getStereoViewType() = 0;

  /**
   * Queries ability to clear before rendering. This allows a subclass to forbid the
   * color buffer from being cleared before any rendering. Typically, this takes
   * place after rendering the first view. Then, if canClearBeforeRender()
   * returns FALSE, the color buffer can keep previous modifications, such as for the
   * stencil buffer, etc.
   */
  virtual SbBool canClearBeforeRender() = 0;

  /**
   * Returns true or false depending on the type of stereo buffering.
   */
  virtual SbBool requireHardware() = 0;

  /**
   * A stereo view type may need to restore a state when it is no longer used by a
   * stereo viewer.
   */
  virtual void clearStereo();

 SoINTERNAL public:
  /**
   * in commonConstructor of StereoDialog, setStereoViewType
   * is called to get back the stereo type when reopening.
   * The MP crash if the stereo type is not supported
   * (pure virtuals functions not redefined)-
   * Crash is avoided by calling this function to know if mode
   * is supported or not in MP.
   * Redefine this function to support the mode
   */
  virtual SbBool isMPStereoViewTypeSupported();

  /*
   *   methods use in MP mode only. These methods are called by the threads within the
   *   render area if the stereo is active.
   */
  virtual void doLeftEyeSettings() = 0;
  virtual void doRightEyeSettings() = 0;
  virtual void doMonoscopicSettings() = 0;
  
  /**
   * Tell StereoViewer to take care of fast edit nodes or not.
   */
  void setRenderFastEditNodes(SbBool render);

 protected:

  // Render stereo test pattern for specified eye.
  virtual void renderTestPattern( SbBool leftEye );

  SoStereoViewer *stereoViewer;
  SbBool renderFastEdit;

};

#endif // _SO_WIN_STEREOVIEW_TYPE

