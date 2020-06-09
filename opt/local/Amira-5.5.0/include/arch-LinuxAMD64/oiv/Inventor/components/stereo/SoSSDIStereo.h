/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_WIN_SSDISTEREO
#define _SO_WIN_SSDISTEREO

#if defined(_WIN32)

#include <Inventor/components/stereo/SoBaseStereo.h>
#include <Inventor/components/stereo/ssdi.h>

class SoStereoViewer;

/**
 * @VSGEXT Class for SSDI stereo support.
 * 
 * @ingroup Stereo
 * 
 * @DESCRIPTION
 *   This class implements the SSDI stereo type [Win32 only].
 *   
 *   ATTENTION: THIS CLASS IS NO LONGER FUNCTIONAL DUE TO THE DEMISE OF SSDI.
 * 
 *   This type of stereo relies on the SSDI library. This library, which is provided
 *   by VRex Systems (http://www.vrex.com), is capable of supporting a large variety
 *   of stereo systems (shutter glasses, polarized projectors, etc.). Once the
 *   library is installed on the system, choose which driver the library will make
 *   use of (according to the hardware connected to your system), and activate the
 *   SSDI stereo.
 * 
 * @SEE_ALSO
 *    SoStereoViewer,
 *    SoBaseStereo,
 *    SoWinViewer
 * 
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 * 
 */ 

class INVENTORW_API SoSSDIStereo : public SoBaseStereo
{
 public:

  /**
   * Constructor.
   */
  SoSSDIStereo(SoStereoViewer *stereoVwr = NULL);

  /**
   * Destructor.
   */
  ~SoSSDIStereo();

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
  virtual void renderMPStereoView();

  /**
   * Always returns SoBaseStereo::SSDI_STEREO.
   */
  virtual StereoViewType getStereoViewType() { return SSDI_STEREO; }
  /**
   * Queries ability to clear before rendering.
   */
  virtual SbBool canClearBeforeRender();
  /**
   * Always returns FALSE. 
   */
  virtual SbBool requireHardware() { return FALSE; }
  /**
   * Clears stereo.
   */
  virtual void clearStereo();

  /* stereo for MPViewers */
  void doLeftEyeSettings();
  void doRightEyeSettings();
  void doMonoscopicSettings();


 private:
  SbBool initSSDIStereo();
  int setupStereoBuffers();

  ssdiModeInfo modeInfo;
  ssdiStereoInfo stereoInfo;
  ssdiDeviceInfo deviceInfo;
  ssdiBufferSet bufferSet;
  SbBool reversed;
  SbBool clearBuffer;
  SbBool init;
  SbBool ssdiEnabled;
  SoBaseStereo * stereoRenderer;

};
#endif // _WIN32

#endif // _SO_WIN_SSDISTEREO

