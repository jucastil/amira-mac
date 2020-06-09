/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
**=======================================================================*/

#ifndef  _SO_QT_COLOR_PATCH_
#define  _SO_QT_COLOR_PATCH_

#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/Qt/SoQtGLWidget.h>
#include <Inventor/SbColor.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoQtColorPatch
//
//      This class simply draws a 3D looking patch of color.
//
//////////////////////////////////////////////////////////////////////////////

class INVENTORQT_API SoQtColorPatch : public SoQtGLWidget {

  Q_OBJECT

public:
    
  SoQtColorPatch(QWidget *parent = NULL,
                 const char *name = NULL, 
                 SbBool buildInsideParent = TRUE);

  ~SoQtColorPatch();
    
  //
  // set/get routines to specify the patch top color
  //
  void                setColor(const SbColor &rgb);
  const SbColor &     getColor()      { return color; }
  
protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoQtSlider::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
  SoQtColorPatch(
                 QWidget *parent,
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

#endif  // _SO_QT_COLOR_PATCH_
