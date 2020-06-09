/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifdef SOQT
#  include <Inventor/Qt/viewers/SoQtPlaneViewer.h>
#elif defined(SOWX)
#  include <Inventor/Wx/viewers/SoWxPlaneViewer.h>
#elif defined _WIN32
#  include <Inventor/Win/viewers/SoWinPlaneViewer.h>
#else // _WIN32

#ifndef  _SO_XT_PLANE_VIEWER_
#define  _SO_XT_PLANE_VIEWER_

#include <Inventor/Xt/viewers/SoXtFullViewer.h>
#include <Inventor/SbLinear.h>

#include <Inventor/Gui/viewers/SoGuiPlaneViewer.h>

class SoXtBitmapButton;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtPlaneViewer
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
 * @ingroup Xt
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
 *   the object) (Perspective camera) or zoom in and out (Orthographic camera).
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

class INVENTORXT_API SoXtPlaneViewer : public SoXtFullViewer
{
 public:
  /**
   * Constructor which specifies the viewer type. Please refer to the
   * SoXtViewer reference pages for a description of the viewer types.
   */
  SoXtPlaneViewer( SoWidget parent = NULL,
                   const char* name = NULL,
                   SbBool buildInsideParent = TRUE,
                   SoXtFullViewer::BuildFlag flag = SoXtFullViewer::BUILD_ALL,
                   SoXtViewer::Type type = SoXtViewer::BROWSER );
  /**
   * Destructor.
   */
  ~SoXtPlaneViewer();

  /**
   * Moves the camera to be aligned with the given plane
   */
  void setPlane( const SbVec3f& newNormal, const SbVec3f& newRight );

  // redefine these to add Plane viewer functionality
  virtual void setViewing( SbBool onOrOff );
  virtual void setCamera( SoCamera* cam );
  virtual void setCursorEnabled( SbBool onOrOff );
  virtual void setSeekMode( SbBool onOrOff );

  SoINTERNAL public:
    SoGuiPlaneViewer* getGuiPlaneViewer() const;

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoXtPlaneViewer::buildWidget()
  // when they are ready for it to be built.
   SoEXTENDER public:
    SoXtPlaneViewer( SoWidget parent,
                     const char* name,
                     SbBool buildInsideParent,
                     SoXtFullViewer::BuildFlag flag,
                     SoXtViewer::Type type,
                     SbBool buildNow,
                     SbBool sync = TRUE );
 protected:

  SoWidget buildWidget( SoWidget parent );

  // redefine these
  virtual SbString getDefaultWidgetName() const;
  virtual SbString getDefaultTitle() const;
  virtual SbString getDefaultIconTitle() const;

  // redefine those routines to do viewer specific stuff
  virtual void processEvent( XAnyEvent* anyevent );
  virtual void actualRedraw();

  // Define those thumb wheels to translate in the viewer plane
  virtual void bottomWheelMotion( float newVal );
  virtual void leftWheelMotion( float newVal );
  virtual void rightWheelMotion( float newVal );

  // add viewer preference stuff
  virtual void createPrefSheet();

  // add some viewer buttons
  virtual void createViewerButtons( SoWidget parent );

  // Define this to bring the viewer help card
  virtual void openViewerHelpCard();

  // Redefine this to keep the same camera rotation when seeking
  virtual void computeSeekFinalOrientation();

 private:
  // viewer state variables
  Cursor transCursor, dollyCursor, seekCursor;

  // push button vars and callbacks
  SoXtBitmapButton* buttonList[10];
  static void pushButtonCB( SoWidget w, int id, void* data );

  void updateViewerMode( unsigned int state );
  void switchMode( int newMode );
  void updateCursor();
  void defineCursors();

  // this is called by both constructors
  void constructorCommon( SbBool buildNow );

  SoGuiPlaneViewer* m_guiPlaneViewer; // Implementation class for SoXxPlaneViewer
};

#endif  /* _SO_XT_PLANE_VIEWER_ */

#endif // _WIN32


