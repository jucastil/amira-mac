/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_WIN_STEREOVIEWER
#define _SO_WIN_STEREOVIEWER

#include <Inventor/SbBasic.h>
#include <Inventor/SbViewportRegion.h>

class SbVec2s;
class SoCamera;
class SoBaseStereo;

/**
 * @VSGEXT Pure virtual class for stereo support.
 *
 * @ingroup Stereo
 *
 * @DESCRIPTION
 *   This pure virtual class is the class that should be extended by viewer classes
 *   that will do stereo rendering.
 *
 *   Note: because of internal dependant calls between stereo classes and Open Inventor
 *   viewer classes, SoStereoViewer and SoBaseStereo (and inheriting classes) cannot be
 *   used without using SoWinViewer/SoXtViewer/SoQtViewer inheriting classes.
 *
 * @SEE_ALSO
 *    SoWinViewer, SoXtViewer, SoQtViewer
 *
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 *
 */

class INVENTORGUI_API SoStereoViewer {

 public:

  /**
   * Destructor
   */
  virtual ~SoStereoViewer() {}

  /**
   * Sets stereo activation. Default is FALSE.
   * The default can be set using the OIV_STEREO_ACTIVE environment variable.
   */
  virtual void setStereoActive(SbBool activate) = 0;

  /**
   * Queries stereo activation.
   */
  virtual SbBool isStereoActive() = 0;

  /**
   * This method is called automatically when the viewer requests that its
   * SoBaseStereo object perform stereo rendering. actualRendering() may
   * then be called twice (once for each eye view) and therefore must not take into
   * account any stereo-specific settings. It should behave as if it were a rendering
   * method for a monoscopic view.
   */
  virtual void actualRendering() = 0;

  /**
   * Returning the camera allows the SoBaseStereo to manipulate it to achieve
   * the stereo effect.
   */
  virtual SoCamera * getViewerCamera() = 0;

  /**
   * Along with the manipulation of the camera, SoBaseStereo needs to set the
   * scene appropriately when changing the camera settings.
   */
  virtual void adjustClippingPlanes() = 0;

  /**
   * Returns the size of the OpenGL drawing window in absolute screen
   * coordinates (not relative to parent window) of the native window system.
   */
  virtual const SbVec2s& getSize() = 0;

  /**
   * Returns the position of the OpenGL drawing window in absolute screen
   * coordinates (not relative to parent window) of the native window system
   * (typically Y increasing downward). Returns
   * "Top" in the first value of the vector and "Left" in the second value (reverse
   * of the usual X,Y ordering).
   */
  virtual const SbVec2s& getTopLeft() = 0;

  /**
   * Returns the position of the OpenGL drawing window in absolute screen
   * coordinates (not relative to parent window) of the native window system
   * (typically Y increasing downward). Returns
   * "Bottom" in the first value of the vector and "Right" in the second value (reverse
   * of the usual X,Y ordering).
   */
  virtual const SbVec2s& getBottomRight() = 0;

  /**
   * Queries if viewer is double buffered.
   */
  virtual SbBool isViewerDoubleBuffer() = 0;

  /**
   * If stereoViewType is NULL, the stereo is inactivated (see #setStereoActive).
   * Default is SoAnaglyphStereo with RED_CYAN color filter.
   * The default can be set using the OIV_STEREO_TYPE environment variable.
   */
  virtual void setStereoViewType(SoBaseStereo * stereoViewType) = 0;

  /**
   * Returns the stereo view type.
   */
  virtual SoBaseStereo * getStereoViewType() = 0;

  /**
   * Sets reversal of the left and right views.
   */
  virtual void reverseStereoView(SbBool reverse) = 0;

  /**
   * Queries reversal of the left and right views.
   */
  virtual SbBool isStereoViewReversed() = 0;

  /**
  * Specifies if stereo adjustments are absolute. FALSE by default.
  * 
  * The default non-absolute mode allows the stereo settings to be valid over a range 
  * of different view volume settings. If you chose absolute mode, you are responsible 
  * for modifying the stereo settings (if necessary) when the view volume changes.
  *
  * When absolute mode is TRUE, stereo offset and balance are used as follows
  * for the right eye view:
  * <PRE>
  * StereoCameraOffset = getStereoAdjustment();
  * FrustumAsymmetry   = getBalanceAdjustment();
  *
  * glTranslated (-StereoCameraOffset, 0, 0);
  * glFrustum (FrustumLeft + FrustumAsymmetry, FrustumRight + FrustumAsymmetry,
  *            FrustumBottom, FrustumTop, NearClipDistance, FarClipDistance);</PRE>
  * 
  * The left eye view is symmetric.
  *
  * When absolute mode is FALSE, stereo offset and balance are used as follows for the
  * right eye view:
  *
  * Xrange is right minus left (i.e., first two arguments of glFrustum) and
  * multiply that difference by the ratio of the distance to the desired plane
  * of zero parallax to the near clipping plane distance.
  * <PRE>
  * StereoCameraOffset   = Xrange * 0.035 * getStereoAdjustment();
  * FrustumAsymmetry     = -StereoCameraOffset * getBalanceAdjustment();
  * ZeroParallaxDistance = (NearClipDistance + FarClipDistance)/0.5;
  *
  * FrustumAsymmetry *= NearClipDistance / ZeroParallaxDistance;
  *
  * glTranslated (-StereoCameraOffset, 0, 0);
  * glFrustum (FrustumLeft + FrustumAsymmetry, FrustumRight + FrustumAsymmetry,
  *            FrustumBottom, FrustumTop, NearClipDistance, FarClipDistance);</PRE>
  * The left eye view is symmetric.
  *
  * Not virtual pure for compatiblity reasons.
  */
  virtual void setStereoAbsoluteAdjustments(SbBool ) {};

  /**
   * Queries if the stereo adjustments are absolute.
   *
   * Not virtual pure for compatibity reasons.
   */
  virtual SbBool isStereoAbsoluteAdjustments() const { return FALSE; };

  /**
   * Sets the stereo offset (the distance of each eye from the camera position).
   * The right eye is moved plus offset and the left eye is moved minus offset.
   * Default is 0.7. The default can be set using OIV_STEREO_OFFSET environment variable.
   */
  virtual void setStereoOffset(float offset) = 0;

  /**
   * Queries the stereo offset.
   */
  virtual float getStereoOffset() = 0;

  /** 
   * Sets the stereo balance (the position of the zero parallax plane) and specifies whether
   * the balance value is defined as a fraction of the camera near distance.
   *
   * Note: Since the projection matrix always depends on the camera's near plane, in
   * some cases it may be necessary to detect changes to the camera near plane and 
   * adjust by setting a new stereo balance value.  Open Inventor will make these
   * adjustments automatically if the @B nearFrac @b parameter is set to TRUE.  
   * In this case the stereo balance value is defined as a fraction of the camera
   * near distance.
   *
   * Default balance is 1.0. The default can be set using the OIV_STEREO_BALANCE environment variable.
   * Default nearFrac is FALSE. The default can be set using the OIV_STEREO_BALANCE_NEAR_FRAC environment variable.
   */
  virtual void setStereoBalance(float balance, SbBool nearFrac = false) = 0;

  /**
   * Queries the stereo balance (the position of the zero parallax plane).
   */
  virtual float getStereoBalance() = 0;

  /** 
   * Returns TRUE when the stereo balance adjustement is defined as a fraction
   * of the camera near distance.
   */
  virtual SbBool isStereoBalanceNearFrac() = 0;

  /**
   * Sets viewport region with given origin (lower-left corner) and size,
   * given as pixel coordinates.
   */
  virtual void setViewport(short left, short bottom,
                           short width, short height) = 0;

  /**
   * Returns viewport region with origin (lower-left corner) and size,
   * given as pixel coordinates.
   */
  virtual void getViewport(short &left, short &bottom,
                           short &width, short &height) = 0;

  /**
   * @WIN32 Gets the current device context for SbGlContextHelper::makeCurrent.
   */
  virtual HDC getCurrentDC() = 0;

 SoINTERNAL public:

#ifdef __sgi
  // set to TRUE when we are using the SGI specific stereo extensions
  // which enables us to emulate OpenGL stereo on most machines.
  // We also save the camera original aspect ratio and viewport mapping
  // since we need to temporary strech the camera aspect ratio.
  SbBool useSGIStereoExt;
  float camStereoOrigAspect;
  int camStereoOrigVPMapping;
#endif

  //get a pointer to the viewer
  virtual void *getViewer() = 0;
};

#ifdef _WIN32
#  include <Inventor/Win/SoWinEndStrict.h>
#endif

#endif // _SO_WIN_STEREOVIEWER

