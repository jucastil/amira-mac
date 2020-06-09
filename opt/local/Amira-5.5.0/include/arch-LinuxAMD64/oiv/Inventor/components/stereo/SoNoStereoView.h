/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_WIN_NO_STEREOVIEW
#define _SO_WIN_NO_STEREOVIEW

#include <Inventor/components/stereo/SoBaseStereo.h>
#include <Inventor/components/stereo/SoStereoViewer.h>
/**
 * @VSGEXT Makes a stereo viewer behave like a monoscopic (non-stereo) viewer.
 * 
 * @ingroup Stereo
 * 
 * @DESCRIPTION
 *   SoNoStereoView makes a stereo viewer behave as if it were a monoscopic
 *   viewer. Modifying the stereo view technique has no effect.
 * 
 * @SEE_ALSO
 *    SoStereoViewer,
 *    SoBaseStereo,
 *    SoWinViewer
 * 
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 * [OIVNET-WRAPPER-CLASS MODULE{Inventor}]
 * 
 */ 

class SoNoStereoView : public SoBaseStereo {
 public:
  /**
   * Constructor.
   */
  SoNoStereoView(SoStereoViewer *stereoVwr = NULL)
    : SoBaseStereo(stereoVwr)
    { }

  /**
   * Destructor.
   */
  ~SoNoStereoView() {}

  /**
   * This does nothing.
   */
  void reverseStereoView(SbBool reverse);

  /**
   * Always returns FALSE.
   */
  SbBool isStereoViewReversed() { return FALSE; }

  /**
   * Renders the stereo view. It calls the @B actualRendering @b method of the
   * SoStereoViewer only once, without modifying any parameters, such as the
   * camera.
   */
  virtual void renderStereoView() {
    if (stereoViewer != NULL)
      stereoViewer->actualRendering();
  }

  /**
   * Always returns SoBaseStereo::NO_STEREO_VIEW.
   */
  virtual StereoViewType getStereoViewType() { return NO_STEREO_VIEW; }

  /**
   * Always returns TRUE.
   */
  virtual SbBool canClearBeforeRender() { return TRUE; }

  /**
   * Always returns FALSE.
   */
  virtual SbBool requireHardware() { return FALSE; }

  /**
   * This does nothing.
   */
  virtual void clearStereo() { }

SoINTERNAL public:
  /*
   *   methods use in MP mode only. These methods are called by the threads within the
   *   render area if the stereo is active.
   */
  virtual void doLeftEyeSettings() { }
  virtual void doRightEyeSettings() { }
  virtual void doMonoscopicSettings() { }
};

inline void 
SoNoStereoView::reverseStereoView(SbBool)
{}

#endif // _SO_WIN_NO_STEREOVIEW

