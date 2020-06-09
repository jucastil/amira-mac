/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_WIN_HALFSCREENSTEREO
#define _SO_WIN_HALFSCREENSTEREO

#include <Inventor/components/stereo/SoBaseStereo.h>

class SoStereoViewer;

/**
 * @VSGEXT Class for half-screen stereo support.
 * 
 * @ingroup Stereo
 * 
 * @DESCRIPTION
 *   This class implements the half-screen stereo type. The display area is divided
 *   into two parts, one for displaying the left eye view and one for displaying the
 *   right eye view.
 * 
 * @SEE_ALSO
 *    SoStereoViewer,
 *    SoBaseStereo,
 *    SoWinViewer
 *    SoXtViewer
 * 
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 * 
 */ 

class INVENTORW_API SoHalfScreenStereo : public SoBaseStereo {
 public:
   /** Half screen modes */
  enum HalfScreenMode {
    /** Overunder fill (default value) */
    OVERUNDER_FILL = 0, 
    /** Overunder */
    OVERUNDER,
    /** Side by side fill */
    SIDEBYSIDE_FILL,
    /** Side by side */
    SIDEBYSIDE
  };

  /**
   * Constructor.
   */
  SoHalfScreenStereo(SoStereoViewer *stereoVwr = NULL);
  /**
   * Destructor.
   */
  ~SoHalfScreenStereo();

  /**
   * Sets stereo reversal.
   */
  virtual void reverseStereoView(SbBool reverse);
  /**
   * Queries stereo reversal.
   */
  virtual SbBool isStereoViewReversed();

  /**
   * Sets half-screen mode. Default is OVERUNDER_FILL.
   */
  void setHalfScreenMode(HalfScreenMode mode);
  /**
   * Queries half-screen mode.
   */
  HalfScreenMode getHalfScreenMode();
  /**
   * Renders the stereo view.
   */
  virtual void renderStereoView();

  /**
   * Always returns SoBaseStereo::HALF_SCREEN_STEREO.
   */
  virtual StereoViewType getStereoViewType();

  /**
   * Queries ability to clear before rendering.
   */
  virtual SbBool canClearBeforeRender();

  /**
   * Always returns FALSE.
   */
  virtual SbBool requireHardware();
        
  /**
   * Clears stereo.
   */
  virtual void clearStereo();

  /* stereo for MPViewers */
  void doLeftEyeSettings();
  void doRightEyeSettings();
  void doMonoscopicSettings();


 private:
  HalfScreenMode halfScreenMode;
  SbBool reversed;
  SbBool clearBuffer;
};

#endif // _SO_WIN_HALFSCREENSTEREO


