/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Jun 2007)
**=======================================================================*/



#ifndef _SO_PASSIVE_STEREO
#define _SO_PASSIVE_STEREO

#include <Inventor/components/stereo/SoBaseStereo.h>

class SoStereoViewer;

/**
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 * 
 */ 
class INVENTORW_API SoPassiveStereo : public SoBaseStereo
{
 public:

  /**
   * Constructor.
   */
  SoPassiveStereo(SoStereoViewer *stereoVwr = NULL) :
    SoBaseStereo(stereoVwr),
    reversed(FALSE),
    clearBuffer(TRUE) {}
    
  /**
   * Destructor.
   */
  ~SoPassiveStereo() {}
    
  /**
   * Sets stereo reversal.
   */
  virtual void reverseStereoView(SbBool reverse);

  /**
   * Queries stereo reversal.
   */
  virtual SbBool isStereoViewReversed();
  
  /**
   * Renders the stereo view.
   */
  virtual void renderStereoView();
 
  /**
   * Queries ability to clear before rendering.
   */
  virtual SbBool canClearBeforeRender();
  
  /**
   * Always returns FALSE.
   */
  SbBool requireHardware() { return FALSE; }

  /**
   * Always returns SoBaseStereo::PASSIVE_STEREO.
   */
  StereoViewType getStereoViewType() { return PASSIVE_STEREO; }

  /**
   * Clears stereo.
   */
  void clearStereo();
 
  /* stereo for MPViewers */
  void doLeftEyeSettings() {};
  void doRightEyeSettings() {};
  void doMonoscopicSettings() {};

private:
  SbBool reversed;
  SbBool clearBuffer;

};

#endif // _SO_WIN_ANAGLYPH_STEREO


