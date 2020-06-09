/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifdef _WIN32
#  include <Inventor/Win/SoWinLightSliderSet.h>
#else // _WIN32

#ifndef _SO_XT_LIGHT_SLIDER_SET_
#define _SO_XT_LIGHT_SLIDER_SET_

#include <Inventor/Xt/SoXtSliderSet.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtLightSliderSet
//
//  For editing light source nodes.
//
//  The SoXtLightSliderSet allocates:
//     1 SoXtLightIntensitySliderModule   (for editing light intensity)
//     1 SoXtLightColorSliderModule       (for editing light color)
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Component with Motif sliders for editing SoLight nodes.
 * 
 * @ingroup Xt
 * 
 * @DESCRIPTION
 *   This class is used to manipulate the intensity and color of an SoLight node
 *   using an arrangement of Motif sliders and buttons.
 * 
 * @RESOURCES
 * <PRE>  
 *   !!------------------------------------------------ 
 *   !! Light Slider Set 
 *   !!------------------------------------------------ 
 *   *IvLightSliderColor.labelString: COLOR 
 *   *IvLightSliderRed.labelString: Red 
 *   *IvLightSliderGreen.labelString: Green 
 *   *IvLightSliderBlue.labelString: Blue 
 *   *IvLightSliderIntensity1.labelString: INTENSITY 
 *   *IvLightSliderIntensity2.labelString: Intensity  
 * </PRE>
 * 
 * @SEE_ALSO
 *    SoXtSliderSet,
 *    SoXtSliderSetBase,
 *    SoXtComponent,
 *    SoLight,
 *    SoNode
 * 
 * 
 */ 

class INVENTORXT_API SoXtLightSliderSet : public SoXtSliderSet {
 public:
  /**
   * Constructor. At construction time the light node to edit can be
   * supplied. 
   */
  SoXtLightSliderSet( 
                     SoWidget parent = NULL,
                     const char *name = NULL, 
                     SbBool buildInsideParent = TRUE,
                     SoNode *newEditNode = NULL );
  /**
   * Destructor.
   */
  ~SoXtLightSliderSet();
    
 protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call the buildWidget() method on
  // this class when they are ready for it to be built.
  SoEXTENDER
    SoXtLightSliderSet(
                       SoWidget parent,
                       const char *name, 
                       SbBool buildInsideParent, 
                       SoNode *newEditNode,
                       SbBool buildNow);
    
  SoWidget      buildWidget(SoWidget parent);
  
  // this is called by both constructors
  void constructorCommon(SbBool buildNow);

};

#endif /* _SO_XT_LIGHT_SLIDER_SET_ */

#endif // _WIN32


