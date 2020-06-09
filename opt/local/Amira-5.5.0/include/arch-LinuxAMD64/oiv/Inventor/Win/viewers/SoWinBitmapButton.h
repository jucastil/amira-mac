/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SO_PIXMAP_BUTTON_
#define _SO_PIXMAP_BUTTON_

#include <Inventor/Win/SoWinBeginStrict.h>
#include <windows.h>
#include <Inventor/Win/SoWinDef.h>

#include <Inventor/SbBasic.h>

class INVENTORW_API SoWinBitmapButton {
 public:
  SoWinBitmapButton(SoWidget parent, SbBool selectable);

  ~SoWinBitmapButton();
    
  // return the motif push button
  SoWidget      getWidget()         { return widget; }
    
  // draw the button (called from button parent's wndProc)
  void draw( LPDRAWITEMSTRUCT ) ;

  // specify bitmap id in resource file to use for button
  // (use this instead of the setIcon method)
  // Up and down states of button are simulated like Motif.
  void    setBitmap( HMODULE hModule, ULONG idBitmap );

  // specify both up and down bitmaps for button
  void    setBitmaps( HMODULE hModule,
                      ULONG idUp, ULONG idDown );

  // specify if button will draw differently when it has "focus"
  void    showFocus( SbBool );

  // Highlight the pixmap to show it it selected (must pass TRUE
  // to the constructor, in which case another pixmap with a highlight
  // color will be created for the button).
  void        select(SbBool onOrOff);
  SbBool      isSelected()        { return selectFlag; }
    
 private:
  SoWidget      widget;
  SbBool      selectFlag, selectable;
  Pixmap      normalPixmap, selectPixmap;

  // fetch the bitmap(s) from the resource file
  void loadBitmaps() ;

  ULONG   idUp,idDown ;
  HMODULE hMod ;
  HBITMAP hUpBits ;
  HBITMAP hDownBits ;

  BITMAP cUpBits ;
  BITMAP cDownBits ;

  SbBool showsFocus;

};

#include <Inventor/Win/SoWinEndStrict.h>

#endif // _SO_PIXMAP_BUTTON_
