/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/





#ifndef _SO_WIN_MATERIAL_SLIDER_SET_
#define _SO_WIN_MATERIAL_SLIDER_SET_

#include <Inventor/Win/SoWinBeginStrict.h>
#include <Inventor/Win/SoWinSliderSet.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinMaterialSliderSet
//
//  For editing material nodes.
//
//  The SoWinMaterialSliderSet allocates:
//     1 SoWinAmbientColorSliderModule     (for editing ambient color )
//     1 SoWinDiffuseColorSliderModule     (for editing diffues color )
//     1 SoWinSpecularColorSliderModule    (for editing specular color )
//     1 SoWinEmissiveColorSliderModule    (for editing emissive color )
//     1 SoWinShininessSliderModule        (for editing shininess )
//     1 SoWinTransparencySliderModule     (for editing transparency )
//
//////////////////////////////////////////////////////////////////////////////

class INVENTORW_API SoWinMaterialSliderSet : public SoWinSliderSet {
 public:
  SoWinMaterialSliderSet(
                         SoWidget parent = NULL,
                         const char *name = NULL, 
                         SbBool buildInsideParent = TRUE,
                         SoNode *newEditNode = NULL );
  ~SoWinMaterialSliderSet();
    
 protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call the buildWidget() method on
  // this class when they are ready for it to be built.
  SoEXTENDER
    SoWinMaterialSliderSet(
                           SoWidget parent,
                           const char *name, 
                           SbBool buildInsideParent, 
                           SoNode *newEditNode,
                           SbBool buildNow);
    
  SoWidget      buildWidget( SoWidget parent);
  
  // this is called by both constructors
  void constructorCommon(SbBool buildNow);
};

#include <Inventor/Win/SoWinEndStrict.h>

#endif /* _SO_WIN_MATERIAL_SLIDER_SET_ */
