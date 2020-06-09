/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MO_MESH_
#define  _MO_MESH_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>

#include <MeshVizInterface/mapping/nodes/MoActionNode.h>
#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>

class MiVolumeMeshUnstructured;
class MiVolumeMeshUnstructuredIjk;
class MiVolumeMeshHexahedronIjk;
class MiVolumeMeshVertexHexahedronIjk;
class MiVolumeMeshRegular;
class MiVolumeMeshRectilinear;
class MiVolumeMeshCurvilinear;
class MiSurfaceMeshUnstructured;
class MiSurfaceMeshRegular;
class MiSurfaceMeshRectilinear;
class MiSurfaceMeshCurvilinear;
class MiLineMeshUnstructured;
class MiLineMeshRegular;
class MiLineMeshCurvilinear;
class MiMesh;
class MoMeshRepresentation;

/**
 * @DTEXT Property node that defines a mesh.
 * 
 * @ingroup MeshIViz_Mapping_Attributes
 * 
 * @DESCRIPTION 
 * This node stores the object implementing a mesh interface in the scene graph. 
 * Any kind of mesh can be stored in the scene graph. 
 * All mesh representation nodes derived from MoMeshRepresentation use this mesh.
 * The mesh can be set explicitly using one of the setMesh() methods or implicitly by using the 
 * connectFrom() method to use the result of a previous representation. 
 *
 * @FILE_FORMAT_DEFAULT
 *    Mesh {
 *    @TABLE_FILE_FORMAT
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *   Sets the current mesh interface. See MoMeshElement.
 *
 * @SEE_ALSO
 *   MiMesh
 * 
 */
class MESHIVIZDM_API MoMesh : public MoActionNode {

  SO_NODE_HEADER(MoMesh) ;
  
 public:

  /**
   * Constructor.
   */
  MoMesh() ;

  //@{
  /**
   * Sets the mesh interface. Sets the node as modified by calling touch().
   * If the mesh must come from the output of another representation, use the connectFrom() 
   * method instead of setMesh().
   */
  virtual void setMesh(const MiVolumeMeshUnstructured* mesh);
  virtual void setMesh(const MiVolumeMeshUnstructuredIjk* mesh);
  virtual void setMesh(const MiVolumeMeshHexahedronIjk* mesh);
  virtual void setMesh(const MiVolumeMeshVertexHexahedronIjk* mesh);
  virtual void setMesh(const MiVolumeMeshRegular* mesh);
  virtual void setMesh(const MiVolumeMeshRectilinear* mesh);
  virtual void setMesh(const MiVolumeMeshCurvilinear* mesh);

  virtual void setMesh(const MiSurfaceMeshUnstructured* mesh);
  virtual void setMesh(const MiSurfaceMeshRegular* mesh);
  virtual void setMesh(const MiSurfaceMeshRectilinear* mesh);
  virtual void setMesh(const MiSurfaceMeshCurvilinear* mesh);

  virtual void setMesh(const MiLineMeshUnstructured* mesh);
  virtual void setMesh(const MiLineMeshRegular* mesh);
  virtual void setMesh(const MiLineMeshCurvilinear* mesh);
  //@}

  /**
  * Resets the mesh interface to NULL (as if setMesh was given a NULL pointer).
  * Sets the node as modified by calling touch().
  */
  virtual void reset();

  /**
   * Sets the mesh interface by giving the mesh representation node from which the input mesh will be created.
   * When calling this method, the mesh is set internally each time the inputRep representation changes during traversal.
   * This is useful when a representation must be made on top of another one such as isolines on top of an isosurface.
   *
   */
  virtual void connectFrom(MoMeshRepresentation* inputRep);
  
  /**
   * Gets the mesh interface and the type of mesh stored
   */
  virtual const MiMesh* getMesh(MeshType &meshType);

 /*----------------------------------------------------------------------------*/
  SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
  SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

protected:
  virtual ~MoMesh() ;

private:
  const MiMesh* m_mesh;
  MeshType m_meshType;
  MoMeshRepresentation* m_connectFrom;
  size_t m_timeStamp;
} ; 

#endif /* _MO_MESHP_  */

