/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/




#ifndef _SO_WIN_MP_EXAMINER_VIEWER_
#define _SO_WIN_MP_EXAMINER_VIEWER_

#if defined(_WIN32)
#  include <Inventor/Win/SoWinBeginStrict.h>
#endif // _WIN32
#include <Inventor/MP/Win/viewers/SoWinMPFullViewer.h>
#include <Inventor/SbLinear.h>

// classes used
class SbSphereSheetProjector;
class SoFieldSensor;
class SoSeparator;
class SoSwitch;
class SoTranslation;
class SoScale;

class SoWinBitmapButton;


//////////////////////////////////////////////////////////////////////////////
//
// Class: SoWinMPExaminerViewer
//
//  Examiner viewer - allows the user to change the camera position
//  by spinning a sphere in front of the viewpoint.
//
//
//      Keys used by this viewer:
//      -------------------------
//
//      Left Mouse: Tumbles the virtual trackball.
//
//      Middle Mouse: 
//      Ctrl + Left Mouse: Translate up, down, left and right.
//
//      Ctrl + Middle Mouse: 
//      Left + Middle Mouse: Dolly in and out (gets closer to and further
//  away from the object).
//
//  Shift + Ctrl + Left Mouse: Dolly in and out (same as Left + Middle
//  behavior but added by VSG to support the
//  standard Microsoft 2-button mouse).
//
//      \<s\> + click: Alternative to the Seek button. Press (but do not hold 
//                         down) the \<s\> key, then click on a target object.
//
//      Right Mouse: Open the popup menu.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @SCVEXT Multi-Pipe viewer component which uses a virtual trackball to view the data.
 * 
 * @ingroup ScaleVizMultiPipe
 * 
 * @DESCRIPTION
 *   Except for its constructor and destructor, this class is identical to
 *   SoWinExaminerViewer.
 * 
 * 
 */ 

class INVENTORW_API SoWinMPExaminerViewer : public SoWinMPFullViewer {

 public:
  SoWinMPExaminerViewer(SoWidget parent = NULL,
                        const char *name = NULL, 
                        SbBool buildInsideParent = TRUE, 
                        SoWinMPFullViewer::BuildFlag flag = BUILD_ALL, 
                        SoWinMPViewer::Type type = BROWSER);
  ~SoWinMPExaminerViewer();

  //
  // Show/hide the point of rotation feedback, which only appears while
  // in Viewing mode. (default OFF)
  //
  void setFeedbackVisibility(SbBool onOrOff);
  SbBool isFeedbackVisible() const { return feedbackFlag; }

  //
  // Set/get the point of rotation feeedback size in pixels (default 20). 
  //
  void setFeedbackSize(int newSize);
  int getFeedbackSize() const { return (int)feedbackSize; }

  //
  // Enable/disable the animation feature of the viewer. 
  // (enabled by default)
  //
  void setAnimationEnabled(SbBool onOrOff);
  SbBool isAnimationEnabled() { return animationEnabled; }

  //
  // Stop animation, if it is occurring, and queuery if the viewer is 
  // currently animating.
  //
  void stopAnimating();
  SbBool isAnimating() { return animatingFlag; }

  //
  // redefine these to add Examiner viewer functionality
  //
  virtual void viewAll();
  virtual void resetToHomePosition();
  virtual void setCamera(SoCamera *cam);
  virtual void setViewing(SbBool onOrOff);
  virtual void setCursorEnabled(SbBool onOrOff);

 protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoWinMPExaminerViewer::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoWinMPExaminerViewer(SoWidget parent,
                          const char *name, 
                          SbBool buildInsideParent, 
                          SoWinMPFullViewer::BuildFlag flag, 
                          SoWinMPViewer::Type type, 
                          SbBool buildNow);

  // redefine these
  virtual SbString getDefaultWidgetName() const;
  virtual SbString getDefaultTitle() const;
  virtual SbString getDefaultIconTitle() const;

  // redefine those routines to do viewer specific stuff
  virtual void processEvent(XAnyEvent *anyevent);
  virtual void setSeekMode(SbBool onOrOff);
  virtual void prepareRedraw();
  virtual void actualRedraw();
  virtual void endRedraw();

  // Get X resources for the widget.
  SoWidget buildWidget(SoWidget parent);

  // Define those thumb wheels to rotate the object
  virtual void bottomWheelMotion(float newVal);
  virtual void leftWheelMotion(float newVal);
  virtual void rightWheelMotion(float newVal);

  // redefine those routines to also stop animation if any
  virtual void bottomWheelStart();
  virtual void leftWheelStart();

  // add viewer preference stuff
  virtual void createPrefSheet();

  // add some viewer buttons
  virtual void createViewerButtons(SoWidget parent);

  // Define this to bring the viewer help card
  virtual void openViewerHelpCard();

  // It's a long story, but since we can't attach callbacks to a window
  // quite like we can to an Xt widget, it makes more sense for the
  // subclass viewer to handle the buttons it knows about then pass
  // the rest back up to SoWinFullViewer.
  //
  // So WINxx this function must be virtual and protected, not private.
  virtual void pushButtonCB(SoWidget, int id, void *);

 private:
  // viewer state variables
  int mode;

  SbSphereSheetProjector *sphereSheet;
  SbVec2s locator; // mouse position
  SbBool firstBuild; // set FALSE after buildWidget called once

  // point of rotation feedback vars
  SbBool feedbackFlag;
  float feedbackSize;
  SoSeparator *feedbackRoot;
  SoSwitch *feedbackSwitch;
  SoTranslation *feedbackTransNode;
  SoScale *feedbackScaleNode;
  static char *geometryBuffer;
  void createFeedbackNodes();

  // variables used for doing spinning animation
  SbBool animationEnabled, animatingFlag;
  SoFieldSensor *animationSensor;
  SbRotation *rotBuffer;
  int firstIndex, lastIndex;
  long lastMotionTime;
  SbRotation averageRotation;
  SbBool computeAverage;
  static void animationSensorCB(void *v, SoSensor *s);
  static void visibilityChangeCB(void *pt, SbBool visible);
  void doSpinAnimation();

  // camera translation vars
  SbVec3f locator3D;
  SbPlane focalplane;

  void updateViewerMode(unsigned int state);
  void switchMode(int newMode);
  void updateCursor();

  void rotateCamera(const SbRotation &rot);
  void rollCamera(const SbVec2s &newLocator);
  void spinCamera(const SbVec2f &newLocator);
  void dollyCamera(const SbVec2s &newLocator);
  void panCamera(const SbVec2f &newLocator);

  // preference sheet stuff
  SoWidget createExamPrefSheetGuts(SoWidget parent);
  static void animPrefSheetToggleCB(SoWidget, SoWinMPExaminerViewer *, void *);

  // point of rotation pref sheet stuff
  int feedbackSizeWheelVal;
  SoWidget feedbackLabel[2], feedbackField, feedbackSizeWheel;
  static void feedbackSizeWheelCB(SoWidget, SoWinMPExaminerViewer *p, XtPointer *d);
  static void feedbackSizeFieldCB(SoWidget, SoWinMPExaminerViewer *, void *);
  static void feedbackPrefSheetToggleCB(SoWidget, SoWinMPExaminerViewer *, void *);
  void toggleFeedbackWheelSize(SoWidget toggle);

  // push button vars and callbacks
  SoWinBitmapButton *buttonList[10];
  static void camPushCB(SoWidget, SoWinMPExaminerViewer *, void *);

  // this is called by both constructors
  void constructorCommon(SbBool buildNow);

  // Utility function called from processEvent
  void processPopupItem(int item);

};

#if defined(_WIN32)
#  include <Inventor/Win/SoWinEndStrict.h>
#endif

#endif /* _SO_WIN_EXAMINER_VIEWER_ */

