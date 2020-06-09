/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MO_Vec3Set_
#define  _MO_Vec3Set_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoNode.h>

#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>
#include <MeshVizInterface/mapping/nodes/MoActionNode.h>

#include <MeshVizInterface/mesh/data/MiDataSetI.h>

/**
 * @DTEXT Property node that stores a vector data set for an unstructured mesh.
 * 
 * @ingroup MeshIViz_Mapping_Attributes
 * 
 * @DESCRIPTION
*    This node adds a pointer to an object implementing the MiVec3dSetI interface to the 
*    list of unstructured vector sets in the traversal state.
*
*    Subsequent mesh representations will then be able to use it during the extraction process. 
*    During traversal of the scene graph, MoVec3SetI nodes are accumulated into a list so that 
*    an extraction can retrieve multiple data sets during the same extraction. 
*
*    @note Vector sets for unstructured meshes (MiVec3dSetI), structured volume meshes (MiVec3dSetIjk) 
*    and unstructured surface meshes (MiVec3dSetIj) are stored in separate lists.  
*
* @FILE_FORMAT_DEFAULT
*    Vec3SetI {
*    @TABLE_FILE_FORMAT
*    @TABLE_END
*    }
*
* @ACTION_BEHAVIOR
*   Adds a vector set to the unstructured vector set list.  See MoVec3SetElementI.
*
* @SEE_ALSO
*   MoVec3SetIj, MoVec3SetIjk
 * 
 */

class MESHIVIZDM_API MoVec3SetI : public MoActionNode {

  SO_NODE_HEADER(MoVec3SetI) ;
  
 public:

  /**
   * Constructor.
   */
  MoVec3SetI() ;

  /**
   * Sets the vector set interface.
   */
  virtual void setVec3Set(const MiVec3dSetI* vec3Set) { m_vec3Set = vec3Set; };

  /**
   * Gets the vector set interface.
   */
  virtual const MiVec3dSetI* getVec3Set() { return m_vec3Set; };

 /*----------------------------------------------------------------------------*/
  SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
  SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 protected:
  virtual ~MoVec3SetI() ;

  const MiVec3dSetI* m_vec3Set;

} ; 

#endif /* _MO_Vec3Set_  */

