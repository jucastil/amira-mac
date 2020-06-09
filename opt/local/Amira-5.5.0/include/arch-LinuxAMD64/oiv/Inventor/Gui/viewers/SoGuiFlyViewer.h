/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jun 2007)
**=======================================================================*/

#ifndef  SO_GUI_FLY_VIEWER
#define  SO_GUI_FLY_VIEWER

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFlyGuiViewer
//
// SoXXViewer implementation class
// 
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/Gui/viewers/SoGuiAlgoViewers.h>

/** [OIV-WRAPPER-NO-WRAP] */
class INVENTORGUI_API SoGuiFlyViewer : public SoGuiAlgoViewers 
{
#ifndef HIDDEN_FROM_DOC
  SO_FIELDCONTAINER_HEADER( SoGuiFlyViewer );
#endif

SoINTERNAL public:
  enum ViewerModes 
  {
    STILL_MODE, 
    FLY_MODE, 
    TILT_MODE, 
    SEEK_MODE, 
    SET_UP_MODE 
  };
    
  /**
   * Constructor.
   */
  SoGuiFlyViewer();

  void drawViewerFeedback();

protected:
  /**
   * Destructor.
   */
  virtual ~SoGuiFlyViewer();
};

#endif  // SO_GUI_FLY_VIEWER
