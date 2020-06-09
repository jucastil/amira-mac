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
#  include <Inventor/Win/SoWinTransformSliderSet.h>
#else // _WIN32

#ifndef _SO_XT_TRANSFORM_SLIDER_SET_
#define _SO_XT_TRANSFORM_SLIDER_SET_

#include <Inventor/Xt/SoXtSliderSet.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtTransformSliderSet
//
//  For editing transformation nodes.
//
//  The SoXtTransformSliderSet allocates:
//     1 SoXtTransSliderModule       (for editing translation)
//     1 SoXtScaleSliderModule       (for editing scaling)
//     1 SoXtRotateSliderModule      (for editing rotation)
//     1 SoXtCenterSliderModule      (for editing center of rotation and scale)
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Component with Motif sliders for editing SoTransform nodes.
 * 
 * @ingroup Xt
 * 
 * @DESCRIPTION
 *   This class defines an editor that uses Motif Sliders to edit fields in an
 *   SoTransform node. There are sliders for editing the translation, scale,
 *   rotation, and transform center.
 * 
 * @RESOURCES
 * <PRE>  
 *   !!------------------------------------------------ 
 *   !! Transform Slider Set 
 *   !!------------------------------------------------ 
 *   *IvTransformSliderTrans.labelString: TRANSLATIONS 
 *   *IvTransformSliderTransX.labelString: X Translation 
 *   *IvTransformSliderTransY.labelString: Y Translation 
 *   *IvTransformSliderTransZ.labelString: Z Translation 
 *   *IvTransformSliderScale.labelString: SCALES 
 *   *IvTransformSliderScaleX.labelString: X Scale 
 *   *IvTransformSliderScaleY.labelString: Y Scale 
 *   *IvTransformSliderScaleZ.labelString: Z Scale 
 *   *IvTransformSliderRotate.labelString: ROTATIONS 
 *   *IvTransformSliderRotateX.labelString: X Rotate 
 *   *IvTransformSliderRotateY.labelString: Y Rotate 
 *   *IvTransformSliderRotateZ.labelString: Z Rotate 
 *   *IvTransformSliderScaleOrient.labelString: SCALE ORIENTATION 
 *   *IvTransformSliderScaleOrientX.labelString: X Rotate 
 *   *IvTransformSliderScaleOrientY.labelString: Y Rotate 
 *   *IvTransformSliderScaleOrientZ.labelString: Z Rotate 
 *   *IvTransformSliderCenter.labelString: CENTER 
 *   *IvTransformSliderCenterX.labelString: X Center 
 *   *IvTransformSliderCenterY.labelString: Y Center 
 *   *IvTransformSliderCenterZ.labelString: Z Center 
 *   *IvTransformSliderTitle.labelString: Transform Editor 
 *   *IvTransformSliderIconTitle.labelString: Xf Editor  
 * </PRE>
 * 
 * @SEE_ALSO
 *    SoXtSliderSet,
 *    SoXtSliderSetBase,
 *    SoXtComponent,
 *    SoTransform
 * 
 * 
 */ 

class INVENTORXT_API SoXtTransformSliderSet : public SoXtSliderSet {
 public:
  /**
   * Constructor. At construction time the transform node to edit can
   * be supplied. 
   */
  SoXtTransformSliderSet( 
                         SoWidget parent = NULL,
                         const char *name = NULL, 
                         SbBool buildInsideParent = TRUE,
                         SoNode *newEditNode = NULL );
  /**
   * Destructor. 
   */
  ~SoXtTransformSliderSet();
  
 protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call the buildWidget() method on
  // this class when they are ready for it to be built.
  SoEXTENDER
    SoXtTransformSliderSet(
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

#endif // _SO_XT_TRANSFORM_SLIDER_SET_

#endif // _WIN32


