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
#  include <Inventor/Win/SoWinMaterialSliderSet.h>
#else // _WIN32

#ifndef _SO_XT_MATERIAL_SLIDER_SET_
#define _SO_XT_MATERIAL_SLIDER_SET_

#include <Inventor/Xt/SoXtSliderSet.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtMaterialSliderSet
//
//  For editing material nodes.
//
//  The SoXtMaterialSliderSet allocates:
//     1 SoXtAmbientColorSliderModule     (for editing ambient color )
//     1 SoXtDiffuseColorSliderModule     (for editing diffues color )
//     1 SoXtSpecularColorSliderModule    (for editing specular color )
//     1 SoXtEmissiveColorSliderModule    (for editing emissive color )
//     1 SoXtShininessSliderModule        (for editing shininess )
//     1 SoXtTransparencySliderModule     (for editing transparency )
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Component with Motif sliders for editing SoMaterial nodes.
 * 
 * @ingroup Xt
 * 
 * @DESCRIPTION
 *   This class defines an editor that uses Motif Sliders to edit the fields in an
 *   SoMaterial node. There are sliders for editing the RGB values of ambientColor,
 *   diffuseColor, specularColor and emissiveColor, as well as for editing the
 *   transparency and shininess values.
 * 
 * @RESOURCES
 * <PRE>  
 *   !!------------------------------------------------ 
 *   !! Material Slider Set 
 *   !!------------------------------------------------ 
 *   *IvMaterialSliderAmbient.labelString: AMBIENT 
 *   *IvMaterialSliderAmbientRed.labelString: Ambient Red 
 *   *IvMaterialSliderAmbientGreen.labelString: Ambient Green 
 *   *IvMaterialSliderAmbientBleu.labelString: Ambient Blue 
 *   *IvMaterialSliderDiffuse.labelString: DIFFUSE 
 *   *IvMaterialSliderDiffuseRed.labelString: Diffuse Red 
 *   *IvMaterialSliderDiffuseGreen.labelString: Diffuse Green 
 *   *IvMaterialSliderDiffuseBleu.labelString: Diffuse Blue 
 *   *IvMaterialSliderSpecular.labelString: SPECULAR 
 *   *IvMaterialSliderSpecularRed.labelString: Specular Red 
 *   *IvMaterialSliderSpecularGreen.labelString: Specular Green 
 *   *IvMaterialSliderSpecularBleu.labelString: Specular Blue 
 *   *IvMaterialSliderEmissive.labelString: EMISSIVE 
 *   *IvMaterialSliderEmissiveRed.labelString: Emissive Red 
 *   *IvMaterialSliderEmissiveGreen.labelString: Emissive Green 
 *   *IvMaterialSliderEmissiveBlue.labelString: Emissive Blue 
 *   *IvMaterialSliderShininess.labelString: SHININESS 
 *   *IvMaterialSliderShininessShininess.labelString: shininess 
 *   *IvMaterialSliderTransparency.labelString: TRANSPARENCY 
 *   *IvMaterialSliderTransparencyTransparency.labelString: transparency  
 * </PRE>
 * 
 * @SEE_ALSO
 *    SoXtMaterialEditor,
 *    SoXtSliderSet,
 *    SoXtSliderSetBase,
 *    SoXtComponent,
 *    SoMaterial,
 *    SoNode
 * 
 * 
 */ 

class INVENTORXT_API SoXtMaterialSliderSet : public SoXtSliderSet {
 public:
  /**
   * Constructor. At construction time the material node to edit can
   * be supplied.
   */
  SoXtMaterialSliderSet(
                        SoWidget parent = NULL,
                        const char *name = NULL, 
                        SbBool buildInsideParent = TRUE,
                        SoNode *newEditNode = NULL );
  /**
   * Destructor.
   */
  ~SoXtMaterialSliderSet();
    
 protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call the buildWidget() method on
  // this class when they are ready for it to be built.
  SoEXTENDER
    SoXtMaterialSliderSet(
                          SoWidget parent,
                          const char *name, 
                          SbBool buildInsideParent, 
                          SoNode *newEditNode,
                          SbBool buildNow);
    
  SoWidget      buildWidget( SoWidget parent);
  
  // this is called by both constructors
  void constructorCommon(SbBool buildNow);

};

#endif /* _SO_XT_MATERIAL_SLIDER_SET_ */

#endif // _WIN32


