/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_BASE_VIEW_
#define  _PO_BASE_VIEW_

#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/Gui/SoGui.h>

class SoGuiViewer;

/**
 * @VSGEXT  Abstract base class for views.
 * 
 * @ingroup GuiView
 * 
 * @DESCRIPTION
 *   Views allow the application to specify multiple cameras, each with its
 *   own separate viewport (region of the 3D window). This is more powerful
 *   than just using multiple SoCamera nodes, because camera nodes do not
 *   allow specifying a viewport (the viewport is always the full window).
 *
 *   In addition, when mouse event locations are mapped back into 3D space,
 *   Open Inventor automatically uses the view volume of the camera associated
 *   with the view whose viewport currently contains the mouse cursor.
 *
 *   Views can be used to efficiently create the effect of multiple windows,
 *   without the overhead and system dependent code to manage multiple windows.
 *   For example, views can be used to subdivide the window into multiple
 *   independent views of a 3D scene or to create an inset "bird's eye" view 
 *   inside the window.
 *    
 *    Basically, a view consists of a camera (specifically an SoCameraKit) and a viewport 
 *    attached to this camera. The viewport is the region of the graphics window 
 *    in which the scene graph will be rendered.
 *    
 *    @B NOTES: @b
 *    - When you use HardCopy, the graphics window is the paper sheet.
 *    - If you use a viewer, you should call the method 
 *      SoBaseKit::setSearchingChildren(TRUE) to allow the viewer to search
 *      for cameras inside nodekits (like this one).
 *
 *    @B LIMITATIONS: @b
 *    - The field SoCamera::viewportMapping must be equal to 
 *      ADJUST_CAMERA in order to have a correct vectorisation when you use  
 *      HardCopy,
 *    - Do not use the SoBoxHighlightRenderAction class on a scene graph which contains 
 *      a view,
 *    - Do not push view, 
 *    - Be careful when you use the method viewAll() of the class SoXtViewer, because 
 *      this method works on the entire scene graph and not on a portion of a scene 
 *      graph. Overload this method according to your requirements,
 *    - Views are not compatible with the VRML file format.
 *
 *    @B CHANGES: @b
 *    - Since Open Inventor 8.1, PoBaseView and related classes (PoView, PoSceneView 
 *      and PoToVRML2Action) have been moved from MeshViz into core Open Inventor.
 *    - Since Open Inventor 8.1, the callback viewingEventCB no longer needs to be
 *      registered.  This is now done automatically in the So<XXX>Viewer classes.
 *
 * @ACTION_BEHAVIOR
 *  Sets: SoGLViewportRegionElement, SoLogicalViewportElement, SoModifyViewVolumeElement,
 *        SoViewportRegionElement, SoGLUpdateAreaElement
 * 
 * @SEE_ALSO
 *   PoView, PoSceneView
 */
class INVENTORGUI_API PoBaseView : public SoBaseKit 
{
  SO_KIT_ABSTRACT_HEADER(PoBaseView);

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(cameraKit);

 public:

  /**
   * Lower-left corner coordinates of the viewport of the view. @BR
   * These coordinates must be 
   * given in the normalized space [0-1]*[0-1]. The coordinate (0,0) is the lower-
   * left corner of the display window and (1,1) is the upper-right corner.
   * Default is 0,0.
   */
  SoSFVec2f viewportOrigin;

  /**
   * Size of the viewport of the view. @BR
   * viewportSize[0] is the viewport's width and
   * viewportSize[1] is the viewport's height, each in normalized space. 
   * Therefore viewportOrigin[0]+viewportSize[0] 
   * and viewportOrigin[1]+viewportSize[1] must be less than or equal to 1.
   * Default is 1,1.
   */
  SoSFVec2f viewportSize;

  /**
   * Indicates if a point defined in the normalized space [0-1]x[0-1] is in the 
   * viewport of the view.
   */
  SbBool isPointWithinViewport(float x, float y) const;

  /**
   * Sets the camera of the view on the viewer. (This method is equivalent 
   * to: viewer->setCamera(camera) with camera being the camera of the view).
   *
   * Note: For portability, this method does not take a system dependent viewer
   *       class, e.g. SoXtViewer, as its parameter. The SoGuiViewer
   *       associated with a viewer can be retrieved using the viewer's
   *       getGuiViewer() method.
   * [OIV-WRAPPER-ARG WRAP_AS{SoWinViewer *}&CONVERSION{[ARG_NAME]->getGuiViewer()}]
   */
  void setCamera( SoGuiViewer* viewer );

  /**
   * Specifies if the view is sensitive to events.  Default is false.
   */
  void sensitiveOnEvents(SbBool flag) 
    { m_isSensitiveOnEvents = flag; }

  /**
   * Returns true if the view is sensitive to events.
   */
  SbBool isSensitiveOnEvents() const
    { return m_isSensitiveOnEvents; }

  /** 
   * Returns the view (if any) that contains the given mouse cursor position.
   *
   * If the viewports of multiple views overlap, the chosen view is the last 
   * view drawn (i.e. last view node traversed). Only a 
   * sensitive view (see sensitiveOnEvents() method) can be selected, others are 
   * ignored during the search. (See Chapter 10 of the Open Inventor Mentor, 
   * page 266-268, for the method for getting mouse coordinates).
   *
   * Note: For portability, this method does not take a system dependent viewer
   *       class, e.g. SoXtViewer, as its parameter. The SoGuiViewer
   *       associated with a viewer can be retrieved using the viewer's
   *       getGuiViewer() method.
   * [OIV-WRAPPER-ARG WRAP_AS{SoWinViewer *}&CONVERSION{[ARG_NAME]->getGuiViewer()},IN,IN]
   */
  static PoBaseView* getView( SoGuiViewer* viewer, int mouseX, int mouseY );

  /** 
   * NOTE: Since Open Inventor 8.1, this method is no longer used. 
   * The callback is automatically registered in the So<XXX>Viewer classes.
   */
  SoDEPRECATED static SbBool viewingEventCB( void* viewer, void* anyEvent );

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClasses();
  static void initClass();
	static void exitClass() ;
	static void exitClasses() ;
  
  virtual SbBool getViewportIsEnabled() const;
  virtual const SbVec2f getViewportOrigin() const;
  virtual const SbVec2f getViewportSize() const;
  
 protected:
  // Methods
  virtual void setDefaultOnNonWritingFields();
  
  // Constructor
  PoBaseView();
  
  // Destructor
  virtual ~PoBaseView();
  
 private:
  // Define fields for new parts
  SO_KIT_CATALOG_ENTRY_HEADER(catchActionCallback);
  
  // Methods
  static void catchActionCB(void *, SoAction *);
  static void normalizeMousePoint( SoGuiViewer* viewer, 
                                   int mouseX, int mouseY, 
                                   float& x, float& y );
  
  // Variables
  static SbVec4f m_vvPortion;
  static SbVec2s m_currentLogicalViewportSize;
  SbBool m_isSensitiveOnEvents;
};

inline SbBool 
PoBaseView::viewingEventCB( void* , void* )
{ return FALSE; };

/*----------------------------------------------------------------------------*/

#endif /* _PO_BASE_VIEW_  */


