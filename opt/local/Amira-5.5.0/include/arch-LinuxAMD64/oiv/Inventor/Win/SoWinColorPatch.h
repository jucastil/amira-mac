/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_WIN_COLOR_PATCH_
#define  _SO_WIN_COLOR_PATCH_

#include <Inventor/Win/SoWinBeginStrict.h>
#include <Inventor/Win/SoWinGDIWidget.h>
#include <Inventor/SbColor.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinColorPatch
//
//      This class simply draws a 3D looking patch of color.
//
//////////////////////////////////////////////////////////////////////////////

//class INVENTORW_API SoWinColorPatch : public SoWinGLWidget {
class INVENTORW_API SoWinColorPatch : public SoWinGDIWidget {


 public:
    
  SoWinColorPatch(
                  SoWidget parent = NULL,
                  const char *name = NULL, 
                  SbBool buildInsideParent = TRUE);
  ~SoWinColorPatch();
    
  //
  // set/get routines to specify the patch top color
  //
  void                setColor(const SbColor &rgb);
  const SbColor &     getColor()      { return color; }
  
 protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoWinSlider::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoWinColorPatch(
                    SoWidget parent,
                    const char *name, 
                    SbBool buildInsideParent, 
                    SbBool buildNow);
    
 private:
    
  // redefine to do ColorPatch specific things
  virtual void    redraw();
  virtual void    sizeChanged(const SbVec2s &newSize);
    
  // local variables
  SbColor     color;

  // this is called by both constructors
  void constructorCommon(SbBool buildNow);
};

#include <Inventor/Win/SoWinEndStrict.h>

#endif  // _SO_WIN_COLOR_PATCH_
