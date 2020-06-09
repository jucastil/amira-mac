/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MESHCROSSCONTOUR_
#define  _PO_MESHCROSSCONTOUR_

#include <MeshViz/3Ddata/PoMesh3D.h>
#include <Inventor/fields/SoSFPlane.h>
#include <Inventor/SbBasic.h>

class PbIndexedMesh3D;
class PbTetrahedronMesh3D;
class PbHexahedronMesh3D;
class PbCartesianGrid3D;
class PbParalCartesianGrid3D;
class PbRegularCartesianGrid3D;

class SoMFInt32;
class SoMFVec3f;
class SoCoordinate3;
class SoMaterial;

/**
 * @DTEXT  Representation of cross-contour of a volume mesh.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    The cross-contour is a list of lines defined by the geometric intersection
 *    between the mesh skin and a cross section. 
 *    
 *    If the field PoMesh::valuesIndex is not defined (or if coloringType = 
 *    COLOR_INHERITED), the representation uses only one inherited color. If 
 *    the field PoMesh::valuesIndex is defined (and if coloringType != 
 *    COLOR_INHERITED), the representation is colored by using the current data 
 *    mapping applied to each mesh node value. (see PoMesh for more explanations 
 *    about the current data-mapping).
 *    
 *    The vector data of the mesh for this representation is unused.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoMeshCrossContour {
 *    @TABLE_FILE_FORMAT
 *       @TR plane @TD Z=0 plane
 *       @TR valuesIndex @TD -1
 *       @TR coloringType @TD COLOR_INHERITED
 *       @TR vecsIndex @TD -1
 *       @TR valuesIndexForCellFilter  @TD -1
 *       @TR moduleDataMapping @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pomeshcrosscontour.cat.html
 * 
 * 
 */
class MESHVIZ_API PoMeshCrossContour : public PoMesh3D {

  SO_KIT_HEADER(PoMeshCrossContour) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(groupCrossContour) ;


 public:

  /**
   * Constructor.
   */
  PoMeshCrossContour() ;

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;

  /**
   * Position of the cross section. Z=0 plane by default.
   */
  SoSFPlane  plane;
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

  void indexedMeshCrossContour(PbIndexedMesh3D *mesh) ;
  void tetrahedronMeshCrossContour(PbTetrahedronMesh3D *mesh) ;
  void hexahedronMeshCrossContour(PbHexahedronMesh3D *mesh) ;
  void cartGrid3DCrossContour(PbCartesianGrid3D *mesh);
  void paralCartGrid3DCrossContour(PbParalCartesianGrid3D *mesh);
  void regularGrid3DCrossContour(PbRegularCartesianGrid3D *mesh);

 protected:
  // Destructor
  virtual ~PoMeshCrossContour() ;  
  virtual void   setDefaultOnNonWritingFields();
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void addElementsAllCaches() ;
  virtual void preRebuild();

  /*----------------------------------------------------------------------------*/
 private:
  
  FieldSensorList m_fieldSensorList ;
  // Sensors

  SoFieldList     m_fieldList ;
  // List of fields defined in this class

  void tetrahedronMeshCrossContourInhColr(PbTetrahedronMesh3D *mesh, const float *v) ;
  void tetrahedronMeshCrossContourMapColr(PbTetrahedronMesh3D *mesh, const float *v) ;

  void hexahedronMeshCrossContourInhColr(PbHexahedronMesh3D *mesh, const float *v) ;
  void hexahedronMeshCrossContourMapColr(PbHexahedronMesh3D *mesh, const float *v) ;

  void cartGrid3DCrossContourInhColr(PbCartesianGrid3D *mesh, const float *v);
  void cartGrid3DCrossContourMapColr(PbCartesianGrid3D *mesh, const float *v);

  void paralCartGrid3DCrossContourInhColr(PbParalCartesianGrid3D *mesh, const float *v);
  void paralCartGrid3DCrossContourMapColr(PbParalCartesianGrid3D *mesh, const float *v);

  void regularGrid3DCrossContourInhColr(PbRegularCartesianGrid3D *mesh, const float *v);
  void regularGrid3DCrossContourMapColr(PbRegularCartesianGrid3D *mesh, const float *v);

  void updateCrossContourBindings();
  void updateCrossContourTopology();
  void updateCrossContourColors();
  void updateUnStCrossContourShape(PbIndexedMesh3D *mesh);
  void updateGrid3DCrossContourShape(PbCartesianGrid3D *mesh);

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_MESHCROSSCONTOUR  _ */



