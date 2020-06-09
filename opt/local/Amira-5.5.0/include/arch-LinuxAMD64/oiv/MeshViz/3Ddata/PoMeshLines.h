/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MESHLINES_
#define  _PO_MESHLINES_

#include <MeshViz/3Ddata/PoMesh2D.h>

class PbCartesianGrid2D;
class PbParalCartesianGrid2D;
class PbRegularCartesianGrid2D;
class PbPolarGrid2D;
class PbTriangleMesh2D;
class PbQuadrangleMesh2D;
class PbIndexedMesh2D;

/**
 * @DTEXT  Representation of the edges of surface mesh.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    This representation draws all edges joining each adjacent nodes of the 
 *    current mesh. 
 *    
 *    Even if the current mesh has a 2D geometry, a 3D surface can be
 *    obtained if the field PoMesh2D::zValuesIndex is defined (i.e. >= 0) and
 *    if the corresponding scalar data set exist in the mesh. 
 *    
 *    If the current mesh has a 3D geometry, its z coordinates are used
 *    if the field PoMesh2D::zValuesIndex is undefined (i.e. <0).
 * 
 *    If the field PoMesh::valuesIndex is not defined (or if coloringType = 
 *    COLOR_INHERITED), the representation uses only one inherited color.  
 *    If the field PoMesh::valuesIndex is defined (and if coloringType != 
 *    COLOR_INHERITED), the representation is colored by using the current 
 *    data mapping applied to each mesh node value. (see PoMesh for more 
 *    explanations about the current data-mapping).
 *    
 *    The vector data of the mesh for this representation is unused.
 * @CATALOG_PARTS_INCLUDE pomeshlines.cat.html
 * 
 * 
 */
class MESHVIZ_API PoMeshLines : public PoMesh2D {

  SO_KIT_HEADER(PoMeshLines) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(groupLines) ;


 public:

  /**
   * Constructor.
   */
  PoMeshLines() ;

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

  void regularCartGridLines(PbRegularCartesianGrid2D *mesh);
  void paralCartGridLines(PbParalCartesianGrid2D *mesh);
  void cartGridLines(PbCartesianGrid2D *mesh);
  void polarGridLines(PbPolarGrid2D *mesh);
  void triangleLines(PbTriangleMesh2D *mesh);
  void quadrangleLines(PbQuadrangleMesh2D *mesh) ;
  void indexedLines(PbIndexedMesh2D *mesh) ;

 protected:
  // Methods
  // Destructor
  virtual ~PoMeshLines() ;
  virtual void   setDefaultOnNonWritingFields();
  virtual void addElementsAllCaches() ;
  virtual void preRebuild();

  /*----------------------------------------------------------------------------*/
 private:

  

  void regularCartGridLinesInhColr(PbRegularCartesianGrid2D *mesh, const float *z=0) ;
  void regularCartGridLinesMapColr(PbRegularCartesianGrid2D *mesh, const float *v, const float *z=0) ;
  void regularCartGridLinesAvergColr(PbRegularCartesianGrid2D *mesh, const float *v, const float *z=0) ;

  void paralCartGridLinesInhColr(PbParalCartesianGrid2D *mesh, const float *z=0) ;
  void paralCartGridLinesMapColr(PbParalCartesianGrid2D *mesh, const float *v, const float *z=0) ;
  void paralCartGridLinesAvergColr(PbParalCartesianGrid2D *mesh, const float *v, const float *z=0) ;
  void paralCartGridLinesContColr(PbParalCartesianGrid2D *mesh, const float *v, const float *z=0) ;

  void cartGridLinesInhColr(PbCartesianGrid2D *mesh, const float *z=0) ;
  void cartGridLinesMapColr(PbCartesianGrid2D *mesh, const float *v, const float *z=0) ;
  void cartGridLinesAvergColr(PbCartesianGrid2D *mesh, const float *v, const float *z=0) ;
  void cartGridLinesContColr(PbCartesianGrid2D *mesh, const float *v, const float *z=0) ;

  void polarGridLinesInhColr(PbPolarGrid2D *mesh, const float *z=0) ;
  void polarGridLinesMapColr(PbPolarGrid2D *mesh, const float *v, const float *z=0) ;
  void polarGridLinesAvergColr(PbPolarGrid2D *mesh, const float *v, const float *z=0) ;
  void polarGridLinesContColr(PbPolarGrid2D *mesh, const float *v, const float *z=0) ;

  void triangleLinesInhColr(PbTriangleMesh2D *mesh, const float *z=0) ;
  void triangleLinesMapColr(PbTriangleMesh2D *mesh, const float *v, const float *z=0) ;
  void triangleLinesAvergColr(PbTriangleMesh2D *mesh, const float *v, const float *z=0);
  void triangleLinesContColr(PbTriangleMesh2D *mesh, const float *v, const float *z=0);

  void quadrangleLinesInhColr(PbQuadrangleMesh2D *mesh, const float *z=0) ;
  void quadrangleLinesMapColr(PbQuadrangleMesh2D *mesh, const float *v, const float *z=0) ;
  void quadrangleLinesAvergColr(PbQuadrangleMesh2D *mesh, const float *v, const float *z=0);
  void quadrangleLinesContColr(PbQuadrangleMesh2D *mesh, const float *v, const float *z=0);

  void indexedLinesInhColr(PbIndexedMesh2D *mesh, const float *z=0);
  void indexedLinesMapColr(PbIndexedMesh2D *mesh, const float *v, const float *z=0);
  void indexedLinesAvergColr(PbIndexedMesh2D *mesh, const float *v, const float *z=0);
  void indexedLinesContColr(PbIndexedMesh2D *mesh, const float *v, const float *z=0);
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_MESHLINES_ */



