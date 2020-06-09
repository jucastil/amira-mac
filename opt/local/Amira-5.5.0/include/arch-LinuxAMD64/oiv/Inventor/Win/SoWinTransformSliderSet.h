/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/





#ifndef _SO_WIN_TRANSFORM_SLIDER_SET_
#define _SO_WIN_TRANSFORM_SLIDER_SET_

#include <Inventor/Win/SoWinBeginStrict.h>
#include <Inventor/Win/SoWinSliderSet.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinTransformSliderSet
//
//  For editing transformation nodes.
//
//  The SoWinTransformSliderSet allocates:
//     1 SoWinTransSliderModule       (for editing translation)
//     1 SoWinScaleSliderModule       (for editing scaling)
//     1 SoWinRotateSliderModule      (for editing rotation)
//     1 SoWinCenterSliderModule      (for editing center of rotation and scale)
//
//////////////////////////////////////////////////////////////////////////////

class INVENTORW_API SoWinTransformSliderSet : public SoWinSliderSet {
 public:
  SoWinTransformSliderSet( 
                          SoWidget parent = NULL,
                          const char *name = NULL, 
                          SbBool buildInsideParent = TRUE,
                          SoNode *newEditNode = NULL );
  ~SoWinTransformSliderSet();
  
 protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call the buildWidget() method on
  // this class when they are ready for it to be built.
  SoEXTENDER
    SoWinTransformSliderSet(
                            SoWidget parent,
                            const char *name, 
                            SbBool buildInsideParent, 
                            SoNode *newEditNode,
                            SbBool buildNow);
    
  // redefine these
  virtual SbString    getDefaultWidgetName() const;
  virtual SbString    getDefaultTitle() const;
  virtual SbString    getDefaultIconTitle() const;
    
  SoWidget      buildWidget( SoWidget parent);
  
  // this is called by both constructors
  void constructorCommon(SbBool buildNow);
};

#include <Inventor/Win/SoWinEndStrict.h>

#endif // _SO_WIN_TRANSFORM_SLIDER_SET_
