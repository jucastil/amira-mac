/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jun 2007)
**=======================================================================*/


#ifndef SO_GUI_PLANE_VIEWER
#define SO_GUI_PLANE_VIEWER

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGuiPlaneViewer
//
// SoXXPlaneViewer implementation class
// 
//
//////////////////////////////////////////////////////////////////////////////


#include <Inventor/Gui/viewers/SoGuiAlgoViewers.h>

/** [OIV-WRAPPER-NO-WRAP] */
class INVENTORGUI_API SoGuiPlaneViewer : public SoGuiAlgoViewers 
{
#ifndef HIDDEN_FROM_DOC
  SO_FIELDCONTAINER_HEADER( SoGuiPlaneViewer );
#endif

SoINTERNAL public:
  //  Defines
  enum ViewerModes 
  {
    PICK_MODE, 
    VIEW_MODE,
    DOLLY_MODE_ACTIVE, 
    PAN_MODE, 
    PAN_MODE_ACTIVE, 
    ROLL_MODE_ACTIVE, 
    SEEK_MODE 
  };

// list of custom push buttons
  enum 
  {
    X_PUSH = 0, 
    Y_PUSH,
    Z_PUSH,
    CAM_PUSH,
    PUSH_NUM
  };

  /**
   * Constructor.
   */
  SoGuiPlaneViewer();

  virtual void setCursorEnabled( SbBool onOrOff );
  SbBool isCursorEnabled() const;
  virtual void setSeekMode( SbBool onOrOff );

  // ----------------------- Extension usage -----------------------------------

  virtual void actualRedraw();

protected:
  /**
   * Destructor.
   */
  virtual ~SoGuiPlaneViewer();
};


#endif  // SO_GUI_PLANE_VIEWER

