/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MO_VEC3SETIj_
#define  _MO_VEC3SETIj_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoNode.h>

#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>
#include <MeshVizInterface/mesh/data/MiDataSetIj.h>
#include <MeshVizInterface/mapping/nodes/MoActionNode.h>

/**
 * @DTEXT Property node that stores a vector data set for a structured surface mesh.
 * 
 * @ingroup MeshIViz_Mapping_Attributes
 * 
 * @DESCRIPTION
*    This node adds a pointer to an object implementing the MiVec3dSetIj interface to the 
*    list of unstructured vector sets in the traversal state.
*
*    Subsequent mesh representations will then be able to use it during the extraction process. 
*    During traversal of the scene graph, MoVec3SetIj nodes are accumulated into a list so that 
*    an extraction can retrieve multiple data sets during the same extraction. 
*
*    @note Vector sets for unstructured meshes (MiVec3dSetI), structured volume meshes (MiVec3dSetIjk) 
*    and unstructured surface meshes (MiVec3dSetIj) are stored in separate lists.  
*
* @FILE_FORMAT_DEFAULT
*    Vec3SetIj {
*    @TABLE_FILE_FORMAT
*    @TABLE_END
*    }
*
* @ACTION_BEHAVIOR
*   Adds a vector set to the structured surface vector set list.  See MoVec3SetElementIj.
*
* @SEE_ALSO
*   MoVec3SetI, MoVec3SetIjk
 * 
 */
class MESHIVIZDM_API MoVec3SetIj : public MoActionNode {

  SO_NODE_HEADER(MoVec3SetIj) ;
  
 public:

  /**
   * Constructor.
   */
  MoVec3SetIj() ;

  /**
   * Sets the vector set interface.
   */
  virtual void setVec3Set(const MiVec3dSetIj* vec3Set) { m_vec3Set = vec3Set; };

  /**
   * Gets the vector set interface.
   */
  virtual const MiVec3dSetIj* getVec3Set() { return m_vec3Set; };

 /*----------------------------------------------------------------------------*/
  SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
  SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 protected:
  virtual ~MoVec3SetIj() ;

  const MiVec3dSetIj* m_vec3Set;

} ; 

#endif /* _MO_VEC3SETIj_  */

