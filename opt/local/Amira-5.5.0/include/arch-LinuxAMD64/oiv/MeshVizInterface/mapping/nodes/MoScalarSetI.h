/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MO_SCALARSET_
#define  _MO_SCALARSET_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoNode.h>

#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>
#include <MeshVizInterface/mesh/data/MiDataSetI.h>
#include <MeshVizInterface/mapping/nodes/MoActionNode.h>

/**
* @DTEXT Property node that stores a scalar data set for an unstructured mesh.
* 
* @ingroup MeshIViz_Mapping_Attributes
* 
* @DESCRIPTION
*    This node adds a pointer to an object implementing the MiScalardSetI interface to the 
*    list of unstructured scalar sets in the traversal state.
*
*    Subsequent mesh representations will be able to use this data set for extraction,
*    coloring, etc. During traversal of the scene graph, MoScalarSetI nodes are accumulated 
*    into a list so that an extraction can retrieve several scalar sets during the same 
*    computation. For example, the first set (located at index 0 in the list) for computing 
*    an isosurface and the second set (located at index 1) for coloring it.
*
*    @note Scalar sets for unstructured meshes (MiScalardSetI), structured volume meshes (MiScalardSetIjk) 
*    and unstructured surface meshes (MiScalardSetIj) are stored in separate lists.  
*
* @FILE_FORMAT_DEFAULT
*    ScalarSetI {
*    @TABLE_FILE_FORMAT
*    @TABLE_END
*    }
*
* @ACTION_BEHAVIOR
*   Adds a scalar set to the unstructured scalar set list.  See MoScalarSetElementI.
*
* @SEE_ALSO
*   MoScalarSetIj, MoScalarSetIjk
* 
*/
class MESHIVIZDM_API MoScalarSetI : public MoActionNode {

  SO_NODE_HEADER(MoScalarSetI) ;
  
 public:

  /**
   * Constructor.
   */
  MoScalarSetI() ;

  /**
   * Sets the scalar set interface.
   */
  virtual void setScalarSet(const MiScalardSetI* scalarSet) { m_scalarSet = scalarSet; };

  /**
   * Gets the scalar set interface.
   */
  virtual const MiScalardSetI* getScalarSet() { return m_scalarSet; };

 /*----------------------------------------------------------------------------*/
  SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
  SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 protected:
  virtual ~MoScalarSetI() ;

  const MiScalardSetI* m_scalarSet;

} ; 

#endif /* _MO_SCALARSET_  */

