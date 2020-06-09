/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_SCATTER_
#define  _PO_SCATTER_

#include <MeshViz/graph/PoChart.h>

#include <Inventor/fields/SoMFInt32.h>

/**
 * @DTEXT  Class to build a 2D scatter.
 * 
 * @ingroup GraphScatter
 * 
 * @DESCRIPTION
 *    Builds a 2D scatter on 1D mesh (PoIrregularMesh1D or PoRegularMesh1D).
 *    A scatter representation is a bitmap marker field (indeed SoMarkerSet shape 
 *    is used for this representation).
 *    The field markerIndex is used to define the type of marker used (cf SoMarkerSet).
 *    If the number of indices is inferior to the number of markers, they are 
 *    cyclically used. 
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
 *    PoScatter {
 *    @TABLE_FILE_FORMAT
 *       @TR colorBinding @TD INHERITED
 *       @TR yValuesIndex @TD 0
 *       @TR colorValuesIndex @TD 1
 *       @TR material @TD NULL
 *       @TR markerIndex @TD 0
 *       @TR zValuesIndex @TD -1
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE poscatter.cat.html
 * 
 * 
 */

class MESHVIZ_API PoScatter : public PoChart {
  
  SO_KIT_HEADER(PoScatter) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(scatter) ;


 public:

  /* Fields */

  /**
   * Defines the type of marker used (cf SoMarkerSet).
   * If the number of indices is inferior to the number of markers, they are 
   * cyclically used. 
   */
  SoMFInt32 markerIndex ;

  /**
   * Defines the index of the set of values used to specify a z-coordinate
   * for markers. If zValuesIndex = -1, the z-coordinate used is 0.
   */
  SoSFInt32 zValuesIndex ;

  /**
   * Constructor.
   */
  PoScatter() ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoScatter() ;
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

#endif /* _PO_SCATTER_ */

