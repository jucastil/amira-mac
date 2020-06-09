/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CHART_
#define  _PO_CHART_

#include <MeshViz/graph/PoGraphMaster.h>

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFNode.h>

/**
 * @DTEXT  Abstract base class for all charting representations.
 * 
 * @ingroup graph
 * 
 * @DESCRIPTION
 *    A charting representation may depend on other MeshViz objects :
 *    The current mesh1D (PoRegularMesh1D or PoIrregularMesh1D), the current
 *    data-mapping (PoDataMapping), the current domain (PoDomain).
 * 
 */
class MESHVIZ_API PoChart : public PoGraphMaster {
  
  SO_KIT_ABSTRACT_HEADER(PoChart) ;
  

 public:

  /**
   *  Color binding.
   */
  enum ColorBinding {
    INHERITED,
    PER_VERTEX,
    PER_PART
  } ;



  /* Fields */

  /**
   * Specify how the colors are bound to the representation.
   *
   * INHERITED: The entire representation is colored with the same inherited
   * color whatever values of the fields colorValuesIndex and material.
   *  
   * PER_VERTEX: Each vertex of the representation is colored with a different color
   * from the field material or colorValuesIndex.
   *
   * PER_PART: Each part of the representation is colored with a different color
   * from the field material or colorValuesIndex.
   *
   * The interpretation of colorBinding is retailed in the derived classes.
   * If not enough colors is provided, they are circular used.
   */
  SoSFEnum colorBinding ;

  /**
   * Defines the index of the set of values used by a charting representation as a 
   * y-coordinate of each mesh node.
   */
  SoSFInt32 yValuesIndex ;

  /**
   * Defines the index of the set of values for the coloring. If colorValuesIndex = -1, 
   * (the colorValuesIndex is called undefined) the charting representation is colored with
   * only one color which is inherited. If colorValuesIndex >= 0, the representation is colored 
   * relating to values of the specified set, and relating to the color binding method defined by the 
   * field colorBinding. If the field material is different from NULL and not ignored 
   * (cf setIgnored method of SoField class), this is the field material which is used for coloring.
   */
  SoSFInt32 colorValuesIndex ;

  /**
   * Defines the list of materials used for the coloring. The representation
   * is colored relating to the color binding method defined by the field colorBinding.
   * If this field is ignored (cf setIgnored method of SoField class) or NULL, this is
   * the field colorValuesIndex (if this one is also ignored, the color will be inherited)
   * which is used for coloring.
   */
  SoSFNode material ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

  enum ColorSource {
    DATA_MAPPING,
    COLOR_LIST,
    INHERITED_SOURCE
  } ;
  
  // Retreives the color source.
  ColorSource getColorSource() const ;

 protected:
  PoChart() ;
  // Constructor.

  virtual ~PoChart() ;
  // Destructor.

  // Overloaded methods
  virtual void addElementsAllCaches() ;
  virtual void preRebuild() ;

  // Compute the step angle for circular shape according to
  // the current complexity.
  virtual float computeStepAngle(SoState *state, float radius) const ;

  // Decompose a SoMaterial in N SoMaterial.
  // N is the max number of components of the material source.
  static SoNodeList* decomposeSoMaterial(SoMaterial *matSrc) ;

  // Methods
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

 private:
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /*  _PO_CHART_ */

