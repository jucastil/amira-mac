/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#if defined(_WIN32)
#  include <Inventor/Win/viewers/SoWinPlaneViewer.h>
#else // _WIN32

#ifndef  _SO_XT_PLANE_VIEWER_
#define  _SO_XT_PLANE_VIEWER_

#include <Inventor/MP/Xt/viewers/SoXtMPFullViewer.h>
#include <Inventor/SbLinear.h>

class SoXtBitmapButton;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtMPPlaneViewer
//
//  Plane Viewer - allows the user to move the camera in a plane, zoom in
//      and out, as well as rotate the viewing plane.
//
//      Keys used by this viewer:
//      -------------------------
//
//     Left Mouse: Dolly in and out (gets closer to and further away from the
//     object).
//
//     Middle Mouse: 
//     Ctrl + Left Mouse: Translate up, down, left and right.
//
//     Ctrl + Middle Mouse: Used for roll action (rotates around the viewer
//     forward direction).
//
//     \<s\> + click: Alternative to the Seek button. Press (but do not hold down)
//     the \<s\> key, then click on a target object.
//
//     Right Mouse: Open the popup menu.
//  
//////////////////////////////////////////////////////////////////////////////

/**
 * Viewer component which moves the camera in a plane.
 * 
 * @ingroup ScaleVizMultiPipe
 * 
 * @DESCRIPTION
 *   The Plane viewer component allows the user to translate the camera in the
 *   viewing plane, as well as dolly (move foward/backward) and zoom in and out. The
 *   viewer also allows the user to roll the camera (rotate around the forward
 *   direction) and seek to objects which will specify a new viewing plane. This
 *   viewer could be used for modeling, in drafting, and architectural work. The
 *   camera can be aligned to the X, Y or Z axes.
 * 
 * @RESOURCES
 * <PRE>  
 *   !!------------------------------------------------ 
 *   !! Decorations for Plane Viewer !! 
 *   !!------------------------------------------------ 
 *   *IvPlaneTitle.labelString: Plane Viewer 
 *   *IvPlanePrefTitle.labelString: Plane Viewer Preference Sheet 
 *   *IvPlanePopupTitle.labelString: Plane Viewer 
 *   *IvPlaneIconTitle.labelString: Plane Viewer 
 *   *IvPlaneTransx.labelString: transX 
 *   *IvPlaneTransy.labelString: transY 
 *   *IvPlaneZoom.labelString: Zoom 
 *   *IvPlaneDolly.labelString: Dolly 
 * </PRE>
 * 
 * @USAGE
 *  (For 3-button mouse only.)
 *   
 *   @B Left Mouse or @BR
 *   Left + Middle Mouse: @b Dolly in and out (gets closer to and further away from
 *   the object).
 *   
 *   @B Middle Mouse or @BR
 *   Ctrl + Left Mouse: @b Translate up, down, left and right.
 *   
 *   @B Ctrl + Middle Mouse: @b Used for roll action (rotates around the viewer
 *   forward direction).
 *   
 *   @B \<s\> + Left Mouse: @b Alternative to the Seek button. Press (but do not hold
 *   down) the \<s\> key, then click on a target object.
 *   
 *   @B Right Mouse: @b Open the popup menu.
 *   
 *   @B ALT: @b When the viewer is in selection (a.k.a. pick) mode, pressing and
 *   holding the ALT key temporarily switches the viewer to viewing mode. When the
 *   ALT key is released, the viewer returns to selection mode. Note: If any of the
 *   mouse buttons are currently depressed, the ALT key has no effect.
 * 
 * @SEE_ALSO
 *    SoXtFullViewer,
 *    SoXtViewer,
 *    SoXtComponent,
 *    SoXtRenderArea,
 *    SoXtWalkViewer,
 *    SoXtExaminerViewer,
 *    SoXtFlyViewer
 * 
 * 
 */ 

class INVENTORXT_API SoXtMPPlaneViewer : public SoXtMPFullViewer {
 public:
  /**
   * Constructor which specifies the viewer type. Please refer to the
   * SoXtViewer reference pages for a description of the viewer types.
   */
  SoXtMPPlaneViewer(
                    SoWidget parent = NULL,
                    const char *name = NULL, 
                    SbBool buildInsideParent = TRUE, 
                    SoXtMPFullViewer::BuildFlag flag = BUILD_ALL, 
                    SoXtMPViewer::Type type = BROWSER);
  /**
   * Destructor.
   */
  ~SoXtMPPlaneViewer();
    
  /**
   * Moves the camera to be aligned with the given plane
   */
  void setPlane(const SbVec3f &newNormal, const SbVec3f &newRight);

  //
  // redefine these to add Plane viewer functionality
  //
  virtual void        setViewing(SbBool onOrOff);
  virtual void        setCamera(SoCamera *cam);
  virtual void        setCursorEnabled(SbBool onOrOff);
    
 protected:
  
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoXtMPPlaneViewer::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoXtMPPlaneViewer(
                      SoWidget parent,
                      const char *name, 
                      SbBool buildInsideParent, 
                      SoXtMPFullViewer::BuildFlag flag, 
                      SoXtMPViewer::Type type, 
                      SbBool buildNow);

  SoWidget              buildWidget(SoWidget parent);
        
  // redefine these
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
    
  // redefine those routines to do viewer specific stuff
  virtual void        processEvent(XAnyEvent *anyevent);
  virtual void        setSeekMode(SbBool onOrOff);
  virtual void        actualRedraw();
    
  // Define those thumb wheels to translate in the viewer plane
  virtual void        bottomWheelMotion(float newVal);
  virtual void        leftWheelMotion(float newVal);
  virtual void        rightWheelMotion(float newVal);
    
  // add viewer preference stuff
  virtual void        createPrefSheet();
    
  // add some viewer buttons
  virtual void        createViewerButtons(SoWidget parent);
    
  // Define this to bring the viewer help card
  virtual void        openViewerHelpCard();
    
  // Redefine this to keep the same camera rotation when seeking
  virtual void        computeSeekFinalOrientation();

 private:
  // viewer state variables
  int             mode;
  SbBool          createdCursors;
  Cursor          transCursor, dollyCursor, seekCursor;
  SbVec2s         locator; // mouse position
    
  // camera translation vars
  SbVec3f         locator3D;
  SbPlane         focalplane;
  float           transXspeed, transYspeed;
    
  // push button vars and callbacks
  SoXtBitmapButton  *buttonList[10];
  static void     pushButtonCB(SoWidget, int id, void *);
    
  void            updateViewerMode(unsigned int state);
  void            switchMode(int newMode);
  void            updateCursor();
  void            defineCursors();
  void            rollCamera(const SbVec2s &newLocator);
  void            translateCamera(const SbVec2f &newLocator);
  void            dollyCamera(const SbVec2s &newLocator);
    
  // redefine these to also call computeTranslateValues()
  virtual void    bottomWheelStart();
  virtual void    leftWheelStart();
  void            computeTranslateValues();
    
  // this is called by both constructors
  void constructorCommon(SbBool buildNow);

};

#endif  /* _SO_XT_PLANE_VIEWER_ */

#endif // _WIN32


