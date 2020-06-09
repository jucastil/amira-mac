/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/





#ifndef _SO_WIN_LIGHT_SLIDER_SET_
#define _SO_WIN_LIGHT_SLIDER_SET_

#include <Inventor/Win/SoWinBeginStrict.h>
#include <Inventor/Win/SoWinSliderSet.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinLightSliderSet
//
//  For editing light source nodes.
//
//  The SoWinLightSliderSet allocates:
//     1 SoWinLightIntensitySliderModule   (for editing light intensity)
//     1 SoWinLightColorSliderModule       (for editing light color)
//
//////////////////////////////////////////////////////////////////////////////

class INVENTORW_API SoWinLightSliderSet : public SoWinSliderSet {
 public:
  SoWinLightSliderSet( 
                      SoWidget parent = NULL,
                      const char *name = NULL, 
                      SbBool buildInsideParent = TRUE,
                      SoNode *newEditNode = NULL );
  ~SoWinLightSliderSet();
    
 protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call the buildWidget() method on
  // this class when they are ready for it to be built.
  SoEXTENDER
    SoWinLightSliderSet(
                        SoWidget parent,
                        const char *name, 
                        SbBool buildInsideParent, 
                        SoNode *newEditNode,
                        SbBool buildNow);
    
  SoWidget      buildWidget(SoWidget parent);
  
  // this is called by both constructors
  void constructorCommon(SbBool buildNow);
};

#include <Inventor/Win/SoWinEndStrict.h>

#endif /* _SO_WIN_LIGHT_SLIDER_SET_ */
