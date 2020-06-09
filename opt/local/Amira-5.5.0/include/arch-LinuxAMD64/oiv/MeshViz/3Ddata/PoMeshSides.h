/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MESHSIDES_
#define  _PO_MESHSIDES_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>

#include <MeshViz/3Ddata/PoMesh2D.h>

class PbCartesianGrid2D;
class PbParalCartesianGrid2D;
class PbRegularCartesianGrid2D;
class PbPolarGrid2D;
class PbTriangleMesh2D;
class PbQuadrangleMesh2D;
class PbIndexedMesh2D;

/**
 * @DTEXT  Class to build the sides of the current surface mesh. 
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *   The minimum value, or the maximum value, or another value relating to the 
 *   altitude values determines the height (along the Z axis) of the base of 
 *   the representation. See PoMesh for more explanations about the current mesh.
 * 
 *   If PoMesh2D::zValuesIndex is defined (i.e. >= 0), the altitude values
 *   is the mesh scalar value set of which index is zValuesIndex, otherwise 
 *   the altitude values are the z-coordinates of the surface mesh.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoMeshSides {
 *    @TABLE_FILE_FORMAT
 *       @TR thresholdType @TD THRESHOLD_ZMIN
 *       @TR thresholdValue @TD 0.0
 *       @TR valuesIndex @TD -1
 *       @TR coloringType @TD COLOR_INHERITED
 *       @TR zValuesIndex @TD -1
 *       @TR vecsIndex @TD -1
 *       @TR valuesIndexForCellFilter  @TD -1
 *       @TR moduleDataMapping @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pomeshsides.cat.html
 * 
 * 
 */
class MESHVIZ_API PoMeshSides : public PoMesh2D {

  SO_KIT_HEADER(PoMeshSides) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(groupSides) ;


 public:

  /**
   * Constructor.
   */
  PoMeshSides() ;

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void rebuild() ;

  /**
   *  Type of threshold.
   */
  enum ThresholdType {
    THRESHOLD_ZMIN,
    THRESHOLD_ZMAX,
    THRESHOLD_VALUE
  } ;



  /**
   * Defines the type of threshold.
   *
   * #THRESHOLD_ZMIN: the threshold of the side representation is the minimum 
   * of the z-value.
   *
   * #THRESHOLD_ZMAX: the threshold of the side representation is the 
   * maximum of the z-value.
   *
   * #THRESHOLD_ZVALUE: the threshold of the side representation is defined 
   * by the field thresholdValue.
   */
  SoSFEnum   thresholdType;

  /**
   * Defines the limit of the threshold of the mesh sides. thresholdValue is used 
   * only if the field thresholdType = THRESHOLD_VALUE
   */
  SoSFFloat  thresholdValue;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

  void regularCartGridSides(PbRegularCartesianGrid2D *mesh);
  void paralCartGridSides(PbParalCartesianGrid2D *mesh);
  void cartGridSides(PbCartesianGrid2D *mesh);
  void polarGridSides(PbPolarGrid2D *mesh);
  void triangleSides(PbTriangleMesh2D *mesh);
  void quadrangleSides(PbQuadrangleMesh2D *mesh);
  void indexedSides(PbIndexedMesh2D *mesh);

 protected:
  // Destructor
  virtual ~PoMeshSides() ;  
  virtual void   setDefaultOnNonWritingFields();
  virtual void   addElementsAllCaches() ;
  virtual void   preRebuild();
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

  /*----------------------------------------------------------------------------*/
 private:

  FieldSensorList m_fieldSensorList ;
  // Sensors

  SoFieldList     m_fieldList ;
  // List of fields defined in this class



  void regularCartGridSidesInhColr(PbRegularCartesianGrid2D *mesh, const float *z=0, float threshold_val=0) ;
  void regularCartGridSidesAvergColr(PbRegularCartesianGrid2D *mesh, const float *v, const float *z, float threshold_val=0);
  void regularCartGridSidesMapColr(PbRegularCartesianGrid2D *mesh, const float *v, const float *z, float threshold_val=0);
  void regularCartGridSidesContColr(PbRegularCartesianGrid2D *mesh, const float *v, const float *z, float threshold_val=0);

  void paralCartGridSidesInhColr(PbParalCartesianGrid2D *mesh, const float *z=0, float threshold_val=0) ;
  void paralCartGridSidesAvergColr(PbParalCartesianGrid2D *mesh, const float *v, const float *z, float threshold_val=0);
  void paralCartGridSidesMapColr(PbParalCartesianGrid2D *mesh, const float *v, const float *z, float threshold_val=0);
  void paralCartGridSidesContColr(PbParalCartesianGrid2D *mesh, const float *v, const float *z, float threshold_val=0);

  void cartGridSidesInhColr  (PbCartesianGrid2D *mesh, const float **z=0, float threshold_val=0) ;
  void cartGridSidesMapColr  (PbCartesianGrid2D *mesh, const float **v, const float **z=0, float threshold_val=0) ;
  void cartGridSidesAvergColr(PbCartesianGrid2D *mesh, const float **v, const float **z=0, float threshold_val=0) ;
  void cartGridSidesContColr (PbCartesianGrid2D *mesh, const float **v, const float **z=0, float threshold_val=0) ;

  void polarGridSidesInhColr  (PbPolarGrid2D *mesh, const float **z=0, float threshold_val=0);
  void polarGridSidesMapColr  (PbPolarGrid2D *mesh, const float **v, const float **z=0, float threshold_val=0);
  void polarGridSidesAvergColr(PbPolarGrid2D *mesh, const float **v, const float **z=0, float threshold_val=0);
  void polarGridSidesContColr (PbPolarGrid2D *mesh, const float **v, const float **z=0, float threshold_val=0);

  void triangleSidesInhColr   (PbTriangleMesh2D *mesh, const float *z=0, float threshold_val=0);
  void triangleSidesMapColr   (PbTriangleMesh2D *mesh, const float *v, const float *z, float threshold_val=0);
  void triangleSidesAvergColr (PbTriangleMesh2D *mesh, const float *v, const float *z, float threshold_val=0);
  void triangleSidesContColr  (PbTriangleMesh2D *mesh, const float *v, const float *z, float threshold_val=0);

  void quadrangleSidesInhColr   (PbQuadrangleMesh2D *mesh, const float *z=0, float threshold_val=0);
  void quadrangleSidesMapColr   (PbQuadrangleMesh2D *mesh, const float *v, const float *z, float threshold_val=0);
  void quadrangleSidesAvergColr (PbQuadrangleMesh2D *mesh, const float *v, const float *z, float threshold_val=0);
  void quadrangleSidesContColr  (PbQuadrangleMesh2D *mesh, const float *v, const float *z, float threshold_val=0);

  void indexedSidesInhColr   (PbIndexedMesh2D *mesh, const float *z=0, float threshold_val=0);
  void indexedSidesMapColr   (PbIndexedMesh2D *mesh, const float *v, const float *z, float threshold_val=0);
  void indexedSidesAvergColr (PbIndexedMesh2D *mesh, const float *v, const float *z, float threshold_val=0);
  void indexedSidesContColr  (PbIndexedMesh2D *mesh, const float *v, const float *z, float threshold_val=0);
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_MESHSIDES_ */

