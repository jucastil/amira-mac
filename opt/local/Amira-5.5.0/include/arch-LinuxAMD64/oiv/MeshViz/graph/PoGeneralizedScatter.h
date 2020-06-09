/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_GENERALIZED_SCATTER_
#define  _PO_GENERALIZED_SCATTER_

#include <MeshViz/graph/PoChart.h>

#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoSFInt32.h>

/**
 * @DTEXT  Class to build a 2D generalized scatter.
 * 
 * @ingroup GraphScatter
 * 
 * @DESCRIPTION
 *    Builds a 2D generalized scatter on 1D mesh (PoIrregularMesh1D or PoRegularMesh1D).
 *    A generalized scatter representation is a marker field representation where
 *    each marker is defined by a sub-scene graph. 
 *    The field markers is used to define the sub-scene graph of each marker.
 *    If the number of sub-scene graphs is inferior to the number of markers to draw,
 *    they are cyclically used.
 *    The field scaleFactor defines a possibly non uniform scale applied to each 
 *    marker. If the number of scales is inferior to the number of markers to draw,
 *    they are cyclically used. This scaleFactor can combined with a set of values 
 *    (sizeValuesIndex), to fix the final size of markers. 
 *    The abscissas of the markers are given by the geometry of the current mesh 1D,
 *    and the ordinates are given by one of the value-set of the current mesh 1D 
 *    specified by the field yValuesIndex.
 *    Furthemore a value-set of the current mesh 1D, though the field zValuesIndex,
 *    can be used to define a depth for each marker.
 *    This class also takes into account of the current mesh 1D hints (PoMesh1DHints),
 *    and the current mesh 1D filter (PoMesh1DFilter) to filter the geometry
 *    of the current mesh 1D.
 * 
 *    The interpretation of colorBinding is the following :
 * 
 *    - INHERITED: All markers are colored with the same inherited color.
 * 
 *    - PER_PART, PER_VERTEX: A color is used for each marker.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoGeneralizedScatter {
 *    @TABLE_FILE_FORMAT
 *       @TR colorBinding @TD INHERITED
 *       @TR yValuesIndex @TD 0
 *       @TR colorValuesIndex @TD 1
 *       @TR material @TD NULL
 *       @TR markers @TD NULL
 *       @TR sizeValuesIndex @TD -1
 *       @TR zValuesIndex @TD -1
 *       @TR scaleFactor @TD 1 1 1
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pogeneralizedscatter.cat.html
 * 
 * 
 */

class MESHVIZ_API PoGeneralizedScatter : public PoChart {
  
  SO_KIT_HEADER(PoGeneralizedScatter) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(scatter) ;


 public:

  /* Fields */

  /**
   * Defines the sub-scene graphs used for each marker. If the number of 
   * sub-scene graphs is inferior to the number of markers to draw, they
   * are cyclically used.
   */
  SoMFNode markers ;

  /**
   * Defines the index of the set of values used to specify the size of 
   * markers.
   * If sizeValuesIndex = -1, only the scaleFactor is applied to each marker.
   */
  SoSFInt32 sizeValuesIndex ;

  /**
   * Defines the index of the set of values used to specify a z-coordinate
   * for markers. If zValuesIndex = -1, the z-coordinate used is 0.
   */
  SoSFInt32 zValuesIndex ;

  /**
   * Defines a possibly non uniform scale applied to each marker.
   * If the number of scales is inferior to the number of markers to draw,
   * they are cyclically used.
   * Each scale values are combined to values of the set defined by 
   * the field sizeValuesIndex.
   * For instance, if a value from the selected values-set (with sizeValuesIndex)
   * is equals to 0.5, and the scaleFactor is (2, 1, 2), the size of the marker
   * will be (1, 0.5, 1). If no size is specified (sizeValuesIndex = -1),
   * only a non uniform scale (2, 1, 2) is applied to the original marker.
   */
  SoMFVec3f scaleFactor ;

  /**
   * Constructor.
   */
  PoGeneralizedScatter() ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoGeneralizedScatter() ;
  // Destructor.

  // Overloaded methods
  virtual void rebuild() ;
  virtual void addElementsAllCaches() ;
  virtual void preRebuild() ;

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

#endif /* _PO_GENERALIZED_SCATTER_ */

