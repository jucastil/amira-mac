/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_WIN_RAWSTEREO
#define _SO_WIN_RAWSTEREO

#include <Inventor/components/stereo/SoBaseStereo.h>

class SoStereoViewer;

/**
 * @VSGEXT Class for OpenGL stereo support.
 * 
 * @ingroup Stereo
 * 
 * @DESCRIPTION
 *   This class implements the OpenGL "quad buffered" stereo type. This requires a
 *   stereo accelerated graphics board.
 * 
 * @SEE_ALSO
 *    SoStereoViewer,
 *    SoBaseStereo,
 *    SoWinViewer
 *    SoXtViewer
 *    SoQtViewer 
 * 
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 * 
 */ 

class INVENTORW_API SoRawStereo : public SoBaseStereo
{
 public:
  /**
   * Constructor.
   */
  SoRawStereo(SoStereoViewer *stereoVwr = NULL);
  /**
   * Destructor.
   */
  ~SoRawStereo();

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
   * Always returns SoBaseStereo::RAW_STEREO.
   */
  virtual StereoViewType getStereoViewType();
  /**
   * Queries ability to clear before rendering.
   */
  virtual SbBool canClearBeforeRender();

  /**
   * Always returns TRUE. 
   */
  virtual SbBool requireHardware();

  /**
   * Clears stereo.
   */
  virtual void clearStereo();

 SoINTERNAL public:
  /**
   * For internal use only.
   */
  virtual SbBool isMPStereoViewTypeSupported()
    { return TRUE; };
  
  /* stereo for MPViewers */
  void doLeftEyeSettings();
  void doRightEyeSettings();
  void doMonoscopicSettings();


 private:
  SbBool reversed;
  SbBool clearBuffer;

};

#endif // _SO_WIN_RAWSTEREO


