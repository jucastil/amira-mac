/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_VIEW_
#define  _PO_VIEW_

#include <Inventor/Gui/view/PoBaseView.h>

/**
 * @VSGEXT  Class to define a view.
 * 
 * @ingroup GuiView
 * 
 * @DESCRIPTION
 *    This class allows the user to define a "view". 
 *
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
 *   Basically, a view consists of a camera (specified with an SoCameraKit) and
 *   a viewport (specified using the fields of this node). The viewport is the 
 *   region of the graphics window in which the scene graph will be rendered.
 *
 *   A To define a view, set the fields #viewportOrigin and #viewportSize to the 
 *   desired viewport position and size in normalized device coordinates [0..1],
 *   then configure the camera (set the part cameraKit). All shape nodes placed 
 *   after this node will be drawn using the specified camera and viewport.
 *   You can define as many views as you want.
 *
 *    NOTE: 
 *    - You must not place a camera node before this nodekit.
 *    - The camera must be defined with the method PoBaseView::setCamera.
 *    - Since Open Inventor 8.1, the callback viewingEventCB no longer needs to be
 *      registered.  This is now done automatically in the So<XXX>Viewer classes.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoView {
 *    @TABLE_FILE_FORMAT
 *       @TR viewportOrigin @TD 0 0
 *       @TR viewportSize @TD 1 1
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE poview.cat.html
 */
class INVENTORGUI_API PoView : public PoBaseView 
{
  SO_KIT_HEADER(PoView) ;
  
 public:

  /**
   * Default constructor.
   */
  PoView() ;

  /*----------------------------------------------------------------------------*/

  
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;


 protected:
  // Destructor
  virtual ~PoView() ;

 private:

  virtual SbBool readInstance(SoInput *in, unsigned short flags);
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_VIEW_  */


