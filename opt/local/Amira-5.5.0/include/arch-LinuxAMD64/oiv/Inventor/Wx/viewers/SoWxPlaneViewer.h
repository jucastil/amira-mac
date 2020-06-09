/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jul 2007)
**=======================================================================*/

#ifndef SO_WX_PLANE_VIEWER
#define SO_WX_PLANE_VIEWER

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWxPlaneViewer
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/Wx/viewers/SoWxFullViewer.h>

#include <Inventor/Gui/viewers/SoGuiPlaneViewer.h>
#include <Inventor/SbLinear.h>

class SoGuiPlaneViewer;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWxPlaneViewer
//
//      Plane Viewer - allows the user to move left, right, up, and down a 
//  given plane, as well as roll the viewer and zoom in and out.
//
//
//      Keys used by this viewer:
//      -------------------------
//
//  Left Mouse: Dolly in and out (gets closer to and further away from the
//  object).
//
//  Middle Mouse: 
//  Ctrl + Left Mouse: Translate up, down, left and right.
//
//  Ctrl + Middle Mouse: Used for roll action (rotates around the viewer
//  forward direction).
//
//  Shift + Ctrl + Left Mouse: Roll (same as Ctrl + Middle Mouse behavior
//  but added by VSG to support the standard
//  Microsoft 2-button mouse).
//
//  \<s\> + click: Alternative to the Seek button. Press (but do not hold down)
//  the \<s\> key, then click on a target object.
//  
//  Right Mouse: Open the popup menu.
//  
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Viewer component which moves the camera in a plane.
 * 
 * @ingroup Wx
 * 
 * @DESCRIPTION
 *   The Plane viewer component allows the user to translate the camera in the
 *   viewing plane, as well as dolly (move foward/backward) and zoom in and out. The
 *   viewer also allows the user to roll the camera (rotate around the forward
 *   direction) and seek to objects which will specify a new viewing plane. This
 *   viewer could be used for modeling, in drafting, and architectural work. The
 *   camera can be aligned to the X, Y or Z axes.
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
 *   @B ALT @b: (Win32) When the viewer is in selection (a.k.a. pick) mode, pressing
 *   and holding the ALT key temporarily switches the viewer to viewing mode. When
 *   the ALT key is released, the viewer returns to selection mode. Note: If any of
 *   the mouse buttons are currently depressed, the ALT key has no effect.
 * 
 * @SEE_ALSO
 *    SoWxFullViewer,
 *    SoWxViewer,
 *    SoWxComponent,
 *    SoWxRenderArea,
 *    SoWxExaminerViewer,
 * 
 * 
 */ 

class INVENTORWX_API SoWxPlaneViewer : public SoWxFullViewer 
{

    public:
  /**
   * Constructor which specifies the viewer type. Please refer to 
   * SoWxViewer for a description of the viewer types. [_WIN32] Note:
   * On Windows, the constructor will not create a new top level window -- you must
   * pass a valid window handle for the @B parent @b parameter and pass TRUE for
   * @B buildInsideParent @b.
   */
  SoWxPlaneViewer( wxWindow* parent = NULL,
                   const char* name = NULL, 
                   SbBool buildInsideParent = TRUE, 
                   SoWxFullViewer::BuildFlag flag = SoWxFullViewer::BUILD_ALL, 
                   SoWxViewer::Type type = SoWxViewer::BROWSER );
  /**
   * Destructor.
   */
  ~SoWxPlaneViewer();

  /**
   * Moves the camera to be aligned with the given plane
   */
  void setPlane( const SbVec3f& newNormal, const SbVec3f& newRight );

  // redefine these to add Plane viewer functionality
  virtual void setViewing( SbBool onOrOff );
  virtual void setCamera( SoCamera* cam );
  virtual void setCursorEnabled( SbBool onOrOff );
  virtual void setSeekMode( SbBool onOrOff );
 
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoWxPlaneViewer::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER public:

    SoGuiPlaneViewer* getGuiPlaneViewer() const;

    SoWxPlaneViewer( wxWindow* parent,
                     const char* name, 
                     SbBool buildInsideParent, 
                     SoWxFullViewer::BuildFlag flag, 
                     SoWxViewer::Type type, 
                     SbBool buildNow,
                     SbBool sync = true );

  SoINTERNAL public:
  
    void visibilityChangeCB( wxShowEvent& se );

protected:

  wxPanel* buildWidget(wxWindow* parent);

  // redefine these
  virtual SbString getDefaultWidgetName() const;
  virtual SbString getDefaultTitle() const;
  virtual SbString getDefaultIconTitle() const;

  // redefine those routines to do viewer specific stuff
  virtual void processEvent( wxEvent& anyEvent );
  virtual void actualRedraw();

  // Define those thumb wheels to translate in the viewer plane
  virtual void bottomWheelMotion( float newVal );
  virtual void leftWheelMotion( float newVal );
  virtual void rightWheelMotion( float newVal );
  virtual void mouseWheelMotion( float newVal );

  // add viewer preference stuff
  virtual void createPrefSheet();

  // add some viewer buttons
  virtual void createViewerButtons( wxPanel* parent );

  // Define this to bring the viewer help card
  virtual void openViewerHelpCard();

  // Redefine this to keep the same camera rotation when seeking
  virtual void computeSeekFinalOrientation();

  // It's a long story, but since we can't attach callbacks to a window
  // quite like we can to an Xt widget, it makes more sense for the
  // subclass viewer to handle the buttons it knows about then pass
  // the rest back up to SoWxFullViewer.
  //
  // So WINxx this function must be virtual and protected, not private.
  virtual void pushButtonCB( int id );

 private:

   enum BUTTONS_ID
   {
     X_PUSH_ID = wxID_HIGHEST + 3001,
     Y_PUSH_ID,
     Z_PUSH_ID,
     CAM_PUSH_ID,
   };

  wxBitmap X_PUSH;
  wxBitmap Y_PUSH;
  wxBitmap Z_PUSH;
  wxBitmap CAM_PUSH_PERSP;
  wxBitmap CAM_PUSH_ORTHO;

  SoGuiPlaneViewer* m_guiPlaneViewer; // Implementation class for SoXxPlaneViewer

  // push button vars and callbacks
  wxBitmapButton* buttonList[10];

  // Added for WINxx port, makes it easier to merge WINxx and X code.
  // For _WIN32 saving this value saves us having to reload the normal
  // cursor all the time.  For X it's always NULL. --mmh 2/12/95

  void updateViewerMode( wxMouseEvent& me );
  void switchMode( int newMode );
  void updateCursor();
  
  // this is called by both constructors
  void constructorCommon( SbBool buildNow );

  // Utility function called from processEvent
  void processPopupItem( int item );

  void slot_xButton( wxCommandEvent& ce );
  void slot_yButton( wxCommandEvent& ce );   
  void slot_zButton( wxCommandEvent& ce );   
  void slotCamPushButton( wxCommandEvent& ce );  
};


#endif  // SO_WX_PLANE_VIEWER
