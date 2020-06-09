/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MESHFILLED_
#define  _PO_MESHFILLED_

#include <MeshViz/3Ddata/PoMesh2D.h>
#include <Inventor/fields/SoSFBool.h>

class PbCartesianGrid2D;
class PbParalCartesianGrid2D;
class PbRegularCartesianGrid2D;
class PbPolarGrid2D;
class PbTriangleMesh2D;
class PbQuadrangleMesh2D;
class PbIndexedMesh2D;
class SoNormal;

/**
 * @DTEXT  Filled representation of surface mesh.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    This class represents a 3D surface by filling each cell of the current
 *    mesh. See PoMesh for more explanation about the current mesh.
 *    
 *    Even if the current mesh has a 2D geometry, a 3D surface can be
 *    obtained if the field PoMesh2D::zValuesIndex is defined (i.e. >= 0) and
 *    the corresponding scalar data set defining the Z values exists in the mesh. 
 *    
 *    If the current mesh has a 3D geometry, its Z coordinates are used
 *    as long as the field PoMesh2D::zValuesIndex is undefined (i.e. <0).
 * 
 *    If the field PoMesh::valuesIndex is not defined (or if coloringType = 
 *    COLOR_INHERITED), the representation uses only one inherited color.  
 *    If the field PoMesh::valuesIndex is defined (and coloringType != 
 *    COLOR_INHERITED), the representation is colored using the current 
 *    data mapping applied to each mesh node value. (See PoMesh for more 
 *    explanation about the current data-mapping).
 *    
 *    Vector data associated with the mesh is not used for this representation.
 *  
 *    If the current mesh is a 2D mesh (it does not contain 3D coordinates and 
 *    the #zValuesIndex field = -1) and all the cells have the same orientation, 
 *    then the field #useOverallNormal can be set to true.  This reduces system 
 *    memory usage (storage for normal vectors) and improves rendering performance.
 *
 * @FILE_FORMAT_DEFAULT
 *    PoMeshFilled {
 *    @TABLE_FILE_FORMAT
 *       @TR valuesIndex @TD -1
 *       @TR zValuesIndex @TD -1
 *       @TR coloringType @TD COLOR_INHERITED
 *       @TR useOverallNormal @TD FALSE
 *    @TABLE_END
 *    }

 * @CATALOG_PARTS_INCLUDE pomeshfilled.cat.html
 * 
 * 
 */
class MESHVIZ_API PoMeshFilled : public PoMesh2D {

  SO_KIT_HEADER(PoMeshFilled) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(groupFilled) ;


 public:

  /**
   * Constructor.
   */
  PoMeshFilled() ;

  /**
  * Indicates if a single overall normal vector can be used to render this mesh 
  * representation.  Default is false.
  *
  * If the current mesh is a 2D mesh (it does not contain 3D coordinates and 
  * the #zValuesIndex field = -1) and all the cells have the same orientation, 
  * then this field can be set to true.  This reduces system memory usage and 
  * improves rendering performance.
  * If the field is false, MeshViz computes one normal per vertex of the shape rendered.
  * 
  * This field should be set to true only when all the cells of the mesh 
  * have the same orientation.  This field is ignored if the mesh contains 3D 
  * coordinates or the zValuesIndex field is not -1.
  */
  SoSFBool useOverallNormal;        


  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

  void regularCartGridFilled(PbRegularCartesianGrid2D *mesh);
  void paralCartGridFilled(PbParalCartesianGrid2D *mesh);
  void cartGridFilled(PbCartesianGrid2D *mesh) ;
  void polarGridFilled(PbPolarGrid2D *mesh) ;
  void triangleMeshFilled(PbTriangleMesh2D *mesh) ;
  void quadrangleMeshFilled(PbQuadrangleMesh2D *mesh) ;
  void indexedMeshFilled(PbIndexedMesh2D *mesh) ;

 protected:
  // Methods
  // Destructor
  virtual ~PoMeshFilled() ;
  virtual void   setDefaultOnNonWritingFields();
  virtual void addElementsAllCaches() ;
  virtual void preRebuild();

  virtual void insertDefaultShapeHints();
  SoNormal* m_overallNormal;


  /*----------------------------------------------------------------------------*/
 private:

  

  void regularCartGridFilledInhColr  (PbRegularCartesianGrid2D *mesh, const float *z=0) ;
  void regularCartGridFilledMapColr  (PbRegularCartesianGrid2D *mesh, const float *v, const float *z=0) ;
  void regularCartGridFilledAvergColr(PbRegularCartesianGrid2D *mesh, const float *v, const float *z=0) ;
  void regularCartGridFilledContColr (PbRegularCartesianGrid2D *mesh, const float *v, const float *z=0) ;
  void regularCartGridFilledTexContColr (PbRegularCartesianGrid2D *mesh, const float *v, const float *z=0) ;

  void paralCartGridFilledInhColr  (PbParalCartesianGrid2D *mesh, const float *z=0) ;
  void paralCartGridFilledMapColr  (PbParalCartesianGrid2D *mesh, const float *v, const float *z=0) ;
  void paralCartGridFilledAvergColr(PbParalCartesianGrid2D *mesh, const float *v, const float *z=0) ;
  void paralCartGridFilledContColr (PbParalCartesianGrid2D *mesh, const float *v, const float *z=0) ;
  void paralCartGridFilledTexContColr (PbParalCartesianGrid2D *mesh, const float *v, const float *z=0) ;

  void cartGridFilledInhColr  (PbCartesianGrid2D *mesh, const float *z=0) ;
  void cartGridFilledMapColr  (PbCartesianGrid2D *mesh, const float *v, const float *z=0) ;
  void cartGridFilledAvergColr(PbCartesianGrid2D *mesh, const float *v, const float *z=0) ;
  void cartGridFilledContColr (PbCartesianGrid2D *mesh, const float *v, const float *z=0) ;
  void cartGridFilledTexContColr (PbCartesianGrid2D *mesh, const float *v, const float *z=0) ;

  void polarGridFilledInhColr  (PbPolarGrid2D *mesh, const float *z=0) ;
  void polarGridFilledMapColr  (PbPolarGrid2D *mesh, const float *v, const float *z=0) ;
  void polarGridFilledAvergColr(PbPolarGrid2D *mesh, const float *v, const float *z=0) ;
  void polarGridFilledContColr (PbPolarGrid2D *mesh, const float *v, const float *z=0) ;
  void polarGridFilledTexContColr (PbPolarGrid2D *mesh, const float *v, const float *z=0) ;

  void triangleMeshFilledInhColr      (PbTriangleMesh2D *mesh, const float *z=0) ;
  void triangleMeshFilledMapColr      (PbTriangleMesh2D *mesh, const float *v, const float *z=0) ;
  void triangleMeshFilledAvergColr    (PbTriangleMesh2D *mesh, const float *v, const float *z=0) ;
  void triangleMeshFilledContColr     (PbTriangleMesh2D *mesh, const float *v, const float *z=0) ;
  void triangleMeshFilledTexContColr  (PbTriangleMesh2D *mesh, const float *v, const float *z=0) ;

  void quadrangleMeshFilledInhColr  (PbQuadrangleMesh2D *mesh, const float *z=0) ;
  void quadrangleMeshFilledMapColr  (PbQuadrangleMesh2D *mesh, const float *v, const float *z=0) ;
  void quadrangleMeshFilledAvergColr(PbQuadrangleMesh2D *mesh, const float *v, const float *z=0) ;
  void quadrangleMeshFilledContColr (PbQuadrangleMesh2D *mesh, const float *v, const float *z=0) ;
  void quadrangleMeshFilledTexContColr (PbQuadrangleMesh2D *mesh, const float *v, const float *z=0) ;

  void indexedMeshFilledInhColr  (PbIndexedMesh2D *mesh, const float *z=0) ;
  void indexedMeshFilledMapColr  (PbIndexedMesh2D *mesh, const float *v, const float *z=0) ;
  void indexedMeshFilledAvergColr(PbIndexedMesh2D *mesh, const float *v, const float *z=0) ;
  void indexedMeshFilledContColr (PbIndexedMesh2D *mesh, const float *v, const float *z=0) ;
  void indexedMeshFilledTexContColr (PbIndexedMesh2D *mesh, const float *v, const float *z=0) ;

  // Sensors
  FieldSensorList m_fieldSensorList;

  // List of fields defined in this class
  SoFieldList m_fieldList;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_MESHFILLED_ */

