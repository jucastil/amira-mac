/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MESHLIMIT_
#define  _PO_MESHLIMIT_

#include <MeshViz/3Ddata/PoMesh2D.h>

class PbCartesianGrid2D;
class PbParalCartesianGrid2D;
class PbRegularCartesianGrid2D;
class PbPolarGrid2D;
class PbTriangleMesh2D;
class PbQuadrangleMesh2D;
class PbIndexedMesh2D;

/**
 * @DTEXT  Representation of the limits of a surface mesh.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    Class to build the limits of the current surface mesh. The exterior and
 *    the interior boundaries of the mesh are displayed. See PoMesh for more 
 *    explanations about the current mesh. If the current mesh is an indexed
 *    mesh (class PbIndexedMesh2D, PoIndexedMesh2D and derived), the limit
 *    is defined by the list of edges which are referred by only one cell.
 *    
 *    Even if the current mesh has a 2D geometry, a 3D surface can be
 *    obtained if the field PoMesh2D::zValuesIndex is defined (i.e., >= 0) and
 *    if the corresponding scalar data set exist in the mesh. 
 *    
 *    If the current mesh has a 3D geometry, its z coordinates are used
 *    if the field PoMesh2D::zValuesIndex is undefined (i.e., <0).
 * 
 *    Data mapping is not supported. The representation uses only one 
 *    inherited color, independent of the field's value PoMesh::coloringType.
 *
 *    The vector data of the mesh for this representation is unused.
 * @CATALOG_PARTS_INCLUDE pomeshlimit.cat.html
 * 
 * 
 */
class MESHVIZ_API PoMeshLimit : public PoMesh2D {

  SO_KIT_HEADER(PoMeshLimit) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(groupLimit) ;


 public:

  /**
   * Constructor.
   */
  PoMeshLimit() ;

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Methods
  // Destructor
  virtual ~PoMeshLimit() ;
  virtual void setDefaultOnNonWritingFields();
  virtual void addElementsAllCaches() ;
  virtual void preRebuild();

  /*----------------------------------------------------------------------------*/
 private:

  
};
/*----------------------------------------------------------------------------*/

#endif /* _PO_MESHLIMIT_ */



