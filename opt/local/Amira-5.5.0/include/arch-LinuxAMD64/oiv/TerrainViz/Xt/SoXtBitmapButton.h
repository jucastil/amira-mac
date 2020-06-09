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

#ifndef _SO_PIXMAP_BUTTON_
#define _SO_PIXMAP_BUTTON_

#include <X11/Intrinsic.h>
#include <Inventor/SbBasic.h>

class TERRAINVIZW_API SoXtBitmapButton {
public:
  SoXtBitmapButton(Widget parent, SbBool selectable);
  ~SoXtBitmapButton();
    
  // return the motif push button
  Widget      getWidget()         { return widget; }
    
  // set the icon to use for the pixmap
  void        setIcon(char *icon, int width, int height);
    
  // Highlight the pixmap to show it it selected (must pass TRUE
  // to the constructor, in which case another pixmap with a highlight
  // color will be created for the button).
  void        select(SbBool onOrOff);
  SbBool      isSelected()        { return selectFlag; }
    
private:
  Widget      widget;
  SbBool      selectFlag, selectable;
  Pixmap      normalPixmap, selectPixmap;
};

#endif // _SO_PIXMAP_BUTTON_
