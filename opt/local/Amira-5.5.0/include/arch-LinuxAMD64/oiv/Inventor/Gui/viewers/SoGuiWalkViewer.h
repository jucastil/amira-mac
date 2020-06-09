/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jun 2007)
**=======================================================================*/

#ifndef  SO_GUI_WALK_VIEWER
#define  SO_GUI_WALK_VIEWER

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGuiViewer
//
// SoXXWalkViewer implementation class
// 
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/Gui/viewers/SoGuiAlgoViewers.h>

#ifndef HIDDEN_FROM_DOC
 //  Defines
#  define REC_SIZE	12	// size of the square region on the screen
#  define CROSSWALK		12	// cross feedback size
#  define TURN_SPEED	5.0
#  define WALK_SPEED_FACTOR 6.0
#  define WHEEL_DOLLY_FACTOR  0.5
#  define WHEEL_HEIGHT_FACTOR 0.01
#endif

/** [OIV-WRAPPER-NO-WRAP] */
class INVENTORGUI_API SoGuiWalkViewer : public SoGuiAlgoViewers 
{
#ifndef HIDDEN_FROM_DOC
  SO_FIELDCONTAINER_HEADER( SoGuiWalkViewer );
#endif

  SoINTERNAL public:

  enum ViewerModes 
  {
    PICK_MODE, 
    VIEW_MODE, 
    WALK_MODE_ACTIVE, 
    PAN_MODE, 
    PAN_MODE_ACTIVE, 
    TILT_MODE_ACTIVE, 
    SEEK_MODE, 
    SET_UP_MODE 
  };
    
  /**
   * Constructor.
   */
  SoGuiWalkViewer();

  /**
   * Set viewer speed multiplier (default is 1).
   */
  void setViewerSpeed( float speed );

  /**
   * Get viewer speed multiplier
   */
  float getViewerSpeed() const;

  // ----------------------- Extension usage -----------------------------------
  
  virtual void actualRedraw();

protected:
  
  /**
   * Destructor.
   */
  virtual ~SoGuiWalkViewer();
};

#endif  // SO_GUI_WALK_VIEWER

