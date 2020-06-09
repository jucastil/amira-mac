/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _PO_MESH3DVECGRIDCROSSSECTION_
#define  _PO_MESH3DVECGRIDCROSSSECTION_

#include <MeshViz/3Ddata/PoMesh3DVecCrossSection.h>
#include <Inventor/fields/SoSFPlane.h>

class PbIndexedMesh3D;
class PbTetrahedronMesh3D;
class PbHexahedronMesh3D;
class PbCartesianGrid3D;
class PbParalCartesianGrid3D;
class PbRegularCartesianGrid3D;

/**
 * @DTEXT  Representation of vectors on a grid of a cross section.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *     A grid of points on a #plane of a volume mesh is built. Then a vector 
 *     is computed by interpolation on each point of the grid, possibly projected
 *     (depending on the #projectionType field) and is represented according to the 
 *     different fields of PoMesh3DVec.
 * 
 *     It may be time consuming to use this class depending on the value of the gridSpacing.
 *     For each point of the grid, this class looks for the cell that contains
 *     the point by using a probe tool. The vector drawn at the point is computed by 
 *     interpolation between each point of the containing cell.
 *     The probing process may be slow depending on the number of cells, the mesh type, the
 *     spatial organization of the cells, etc...
 *     The quickest way to draw a vector field may be by using the parent class
 *     PoMesh3DVecCrossSection. Note also that if #gridSpacing = 0, this class behaves like 
 *     PoMesh3DVecCrossSection.
 *  
 * @FILE_FORMAT_DEFAULT
 *    PoMesh3DVecGridCrossSection {
 *    @TABLE_FILE_FORMAT
 *       @TR plane @TD Z=0 plane
 *       @TR gridSpacing @TD 0.05
 *       @TR projectionType @TD NO_PROJECTION
 *       @TR density @TD 1
 *       @TR eliminationStatus @TD NONE
 *       @TR minLength @TD 0.0
 *       @TR maxLength @TD 1E30
 *       @TR bodyShape @TD LINE
 *       @TR bodyLengthType @TD RELATIVE_LENGTH
 *       @TR bodyLengthFactor @TD 1.0
 *       @TR bodyRadiusType @TD CONSTANT_RADIUS
 *       @TR bodyRadiusFactor @TD 0.02
 *       @TR bodyColoringType @TD CONSTANT_COLOR
 *       @TR startArrowShape @TD NO_SHAPE
 *       @TR startArrowHeightType @TD RELATIVE_HEIGHT
 *       @TR startArrowHeightFactor @TD 0.1
 *       @TR startArrowRadiusFactor @TD 0.5
 *       @TR startArrowColoringType @TD CONSTANT_COLOR
 *       @TR endArrowShape @TD CHEVRON
 *       @TR endArrowHeightType @TD RELATIVE_HEIGHT
 *       @TR endArrowHeightFactor @TD 0.1
 *       @TR endArrowRadiusFactor @TD 0.5
 *       @TR endArrowColoringType @TD CONSTANT_COLOR
 *       @TR coloringType @TD COLOR_INHERITED
 *       @TR valuesIndex @TD -1
 *       @TR valuesIndexForCellFilter  @TD -1
 *       @TR vecsIndex @TD -1
 *       @TR moduleDataMapping @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pomesh3dveccrosssection.cat.html
 * 
 * 
 * @SEE_ALSO
 *   PoMesh3DVecCrossSection
 * 
 */
class MESHVIZ_API PoMesh3DVecGridCrossSection : public PoMesh3DVecCrossSection {

  SO_KIT_HEADER(PoMesh3DVecGridCrossSection) ;


 public:

  /**
   * Constructor.
   */
  PoMesh3DVecGridCrossSection() ;

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;

  /* Fields */

  /**
   * GridSpacing is relating to the number of points on the grid :
   * the smaller gridSpacing is, the greater the number of points is.
   * It represents a factor of the biggest size of the mesh. 0.05 by default.
   * If gridSpacing = 0, this class behaves like PoMesh3DVecCrossSection.
   */
  SoSFFloat  gridSpacing;    

 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual void   setDefaultOnNonWritingFields();
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual ~PoMesh3DVecGridCrossSection() ;  

  virtual void addElementsAllCaches() ;
  virtual void preRebuild();

  /*----------------------------------------------------------------------------*/
 private:
  
  FieldSensorList m_fieldSensorList ;
  // Sensors

  SoFieldList     m_fieldList ;
  // List of fields defined in this class

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_MESH3DVECGRIDCROSSSECTION_ */



