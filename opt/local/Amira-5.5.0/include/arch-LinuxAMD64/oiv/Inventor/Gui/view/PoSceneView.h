/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_SCENE_VIEW_
#define  _PO_SCENE_VIEW_

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/Gui/view/PoBaseView.h>

class SoFieldSensor ;

/**
 * @VSGEXT  Class to define a view which contains a scene.
 * 
 * @ingroup GuiView
 * 
 * @DESCRIPTION
 *   This class allows the user to define a view which contains a scene.
 *
 *   Views allow the application to specify multiple cameras, each with its
 *   own separate viewport (region of the 3D window). This is more powerful
 *   than just using multiple SoCamera nodes, because camera nodes do not
 *   allow specifying a viewport (the viewport is always the full window).
 *   See PoBaseView for more explanation.
 *
 *   A scene is a set of any nodes (except SoCamera nodes) placed under an SoGroup node 
 *    which must be seen in a viewport according to a camera configuration. To 
 *    define a view, set the fields #viewportOrigin and #viewportSize according to 
 *    the viewport position and size you want to have (relative to the display 
 *    window sizes), configure the camera (set the part cameraKit), build the scene 
 *    under an SoGroup node, and set this scene to the view (set the part scene). All 
 *    shape nodes contained in the scene will be drawn in the viewport previously 
 *    defined and according to the camera definition. You can define as many views 
 *    as you want.
 *
 *    NOTE: 
 *    - You must not place a camera node before this nodekit.
 *    - Since Open Inventor 8.1, the callback viewingEventCB no longer needs to be
 *      registered.  This is now done automatically in the So<XXX>Viewer classes.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoSceneView {
 *    @TABLE_FILE_FORMAT
 *       @TR viewportOrigin @TD 0 0
 *       @TR viewportSize @TD 1 1
 *       @TR isBackgroundVisible @TD FALSE
 *       @TR isBorderVisible @TD FALSE
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE posceneview.cat.html
 * 
 * 
 */
class INVENTORGUI_API PoSceneView : public PoBaseView 
{
  SO_KIT_HEADER(PoSceneView) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(backgroundSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(backgroundApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(background) ;

  SO_KIT_CATALOG_ENTRY_HEADER(topSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(sceneSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(scene) ;

  SO_KIT_CATALOG_ENTRY_HEADER(borderSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(borderApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(border) ;


 public:

  /**
   * Default constructor.
   */
  PoSceneView() ;

  /* Fields */

  /**
   * Defines the visibility of the background of the view.
   */
  SoSFBool isBackgroundVisible ;

  /**
   * Defines the visibility of the borders of the view.
   */
  SoSFBool isBorderVisible ;

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Methods
  // Destructor
  virtual ~PoSceneView() ;
  virtual void   setDefaultOnNonWritingFields() ;

 private:


  // Draw the border of the view
  void drawBorder() ;

  // Draw the background of the view
  void drawBackground() ;

  // This sensor watches for changes of isBackgroundVisible field
  SoFieldSensor *isBackgroundVisibleSensor ;

  // This sensor watches for changes of isBorderVisible field
  SoFieldSensor *isBorderVisibleSensor ;  
  static void fieldSensorCB(void *data, SoSensor *sensor) ;

  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_SCENE_VIEW_  */


