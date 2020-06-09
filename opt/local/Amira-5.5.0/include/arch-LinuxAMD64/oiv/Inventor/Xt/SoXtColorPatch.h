/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_XT_COLOR_PATCH_
#define  _SO_XT_COLOR_PATCH_

#include <Inventor/Xt/SoXtGLWidget.h>
#include <Inventor/SbColor.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtColorPatch
//
//      This class simply draws a 3D looking patch of color.
//
//////////////////////////////////////////////////////////////////////////////

class INVENTORXT_API SoXtColorPatch : public SoXtGLWidget {

 public:
    
  SoXtColorPatch(
                 SoWidget parent = NULL,
                 const char *name = NULL, 
                 SbBool buildInsideParent = TRUE);
  ~SoXtColorPatch();
    
  //
  // set/get routines to specify the patch top color
  //
  void                setColor(const SbColor &rgb);
  const SbColor &     getColor()      { return color; }
  
 protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoXtSlider::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoXtColorPatch(
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


#endif  // _SO_XT_COLOR_PATCH_
