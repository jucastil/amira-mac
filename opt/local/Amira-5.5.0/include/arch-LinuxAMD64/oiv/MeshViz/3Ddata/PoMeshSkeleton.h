/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MESHSKELETON_
#define  _PO_MESHSKELETON_

#include <MeshViz/3Ddata/PoMesh3D.h>
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
 * @DTEXT  Representation of the skeleton of a volume mesh.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    Class to build a skeleton of the current volume mesh. This skeleton is 
 *    built by a list of numXContour cross-contours orthogonal to X-axis, a list
 *    of numYContour cross-contours orthogonal to Y-axis and a list of 
 *    numZContour cross-contours orthogonal to Z-axis. See PoMesh for more 
 *    explanations about the current mesh.
 * 
 *    The distance between 2 consecutive X cross-contours is a constant defined 
 *    by the X-size of the mesh skin divided by numXContour. This is identical 
 *    for Y and Z.
 * 
 *    If the field PoMesh::valuesIndex is not defined (or if coloringType = 
 *    COLOR_INHERITED), the representation uses only one inherited color.  
 *    If the field PoMesh::valuesIndex is defined (and if coloringType != 
 *    COLOR_INHERITED), the representation is colored by using the current 
 *    data mapping applied to each mesh node value. (see PoMesh for more 
 *    explanations about the current data-mapping).
 *    
 *    The vector data of the mesh for this representation is unused.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoMeshSkeleton {
 *    @TABLE_FILE_FORMAT
 *       @TR numXContour @TD 3
 *       @TR numYContour @TD 3
 *       @TR numZContour @TD 3
 *       @TR valuesIndex @TD -1
 *       @TR coloringType @TD COLOR_INHERITED
 *       @TR vecsIndex @TD -1
 *       @TR valuesIndexForCellFilter  @TD -1
 *       @TR moduleDataMapping @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pomeshskeleton.cat.html
 * 
 * 
 */
class MESHVIZ_API PoMeshSkeleton : public PoMesh3D {

  SO_KIT_HEADER(PoMeshSkeleton) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(skeletonXContourSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(skeletonXContourApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(skeletonXContourGroup) ;

  SO_KIT_CATALOG_ENTRY_HEADER(skeletonYContourSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(skeletonYContourApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(skeletonYContourGroup) ;

  SO_KIT_CATALOG_ENTRY_HEADER(skeletonZContourSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(skeletonZContourApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(skeletonZContourGroup) ;


 public:

  /**
   * Constructor.
   */
  PoMeshSkeleton() ;

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;

  /* Fields */

  /**
   * Number of cross-contours orthogonal to X-axis. 3 by default.
   */
  SoSFInt32  numXContour; 

  /**
   * Number of cross-contours orthogonal to Y-axis. 3 by default.
   */
  SoSFInt32  numYContour; 

  /**
   * Number of cross-contours orthogonal to Z-axis. 3 by default.
   */
  SoSFInt32  numZContour; 
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

  void indexedMeshSkeleton(PbIndexedMesh3D *mesh, const float *nod_values, 
                           float *x_cont, float *y_cont,float *z_cont);
  void tetrahedronMeshSkeleton(PbTetrahedronMesh3D *mesh, const float *nod_values, 
                               float *x_cont, float *y_cont,float *z_cont);
  void hexahedronMeshSkeleton(PbHexahedronMesh3D *mesh, const float *nod_values, 
                              float *x_cont, float *y_cont,float *z_cont);
  void cartGrid3DSkeleton(PbCartesianGrid3D *mesh, const float *nod_values, 
                          float *x_cont, float *y_cont,float *z_cont);
  void paralCartGrid3DSkeleton(PbParalCartesianGrid3D *mesh, const float *nod_values, 
                               float *x_cont, float *y_cont,float *z_cont);
  void regularGrid3DSkeleton(PbRegularCartesianGrid3D *mesh, const float *nod_values, 
                             float *x_cont, float *y_cont,float *z_cont);

 protected:

  SO_KIT_CATALOG_ENTRY_HEADER(skeletonMaterialBinding) ;
  // Define fields for protected parts
  // Destructor
  virtual ~PoMeshSkeleton() ;  
  virtual void   setDefaultOnNonWritingFields();
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void addElementsAllCaches() ;
  virtual void preRebuild();

  void makeSkeletonContours(int num_cont, float *cont_coord, 
                            float xn, float yn, float zn, 
                            const float *x, const float *y, const float *z,
                            const float *nod_values,
                            const SbString& partName);

  /*----------------------------------------------------------------------------*/
 private:
  
  FieldSensorList m_fieldSensorList ;
  // Sensors

  SoFieldList     m_fieldList ;
  // List of fields defined in this class

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_MESHSKELETON  _ */



