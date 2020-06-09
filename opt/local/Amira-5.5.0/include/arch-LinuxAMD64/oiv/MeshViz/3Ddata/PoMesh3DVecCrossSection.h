/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _PO_MESH3DVECCROSSSECTION_
#define  _PO_MESH3DVECCROSSSECTION_

#include <MeshViz/3Ddata/PoMesh3DVec.h>
#include <Inventor/fields/SoSFPlane.h>

class PbIndexedMesh3D;
class PbTetrahedronMesh3D;
class PbHexahedronMesh3D;
class PbCartesianGrid3D;
class PbParalCartesianGrid3D;
class PbRegularCartesianGrid3D;

/**
 * @DTEXT  Representation of vectors on a cross section.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *     A vector is drawn at each edge intersecting the plane.
 *     Each vector is computed by interpolation of the two given vectors at the 
 *     edge's extremities, possibly projected
 *     (depending on the #projectionType field) and is represented according to the 
 *     different fields of PoMesh3DVec.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoMesh3DVecCrossSection {
 *    @TABLE_FILE_FORMAT
 *       @TR plane @TD Z=0 plane
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
 * @SEE_ALSO
 *   PoMesh3DVecGridCrossSection
 * 
 */
class MESHVIZ_API PoMesh3DVecCrossSection : public PoMesh3DVec {

  SO_KIT_HEADER(PoMesh3DVecCrossSection) ;


 public:

  /**
   * Constructor.
   */
  PoMesh3DVecCrossSection() ;

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;

  /**
   *  Type of projection of vectors.
   */
  enum ProjectionType {
    /**
     *  Each vector is drawn as is
     */
    NO_PROJECTION,           
    /**
     *  Each vector is projected onto the plane
     */
    PROJECTION_ON_PLANE,     
    /**
     *  Each vector is projected onto the normal of the plane
     */
    PROJECTION_ON_NORMAL     
  } ;



  /* Fields */

  /**
   * Position of the cross section. Z=0 plane by default.
   */
  SoSFPlane  plane;          

  /**
   * Defines how each vector is projected. NO_PROJECTION by default.
   */
  SoSFEnum   projectionType; 
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual void   setDefaultOnNonWritingFields();
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual ~PoMesh3DVecCrossSection() ;  

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

#endif /* _PO_MESH3DVECCROSSSECTION_ */



