/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MO_SCALARSETIJK_
#define  _MO_SCALARSETIJK_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoNode.h>

#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>
#include <MeshVizInterface/mapping/nodes/MoActionNode.h>

/**
 * @DTEXT Property node that stores a scalar data set for a structured volume mesh.
 * 
 * @ingroup MeshIViz_Mapping_Attributes
 * 
 * @DESCRIPTION
 *    This node adds a pointer to an object implementing the MiScalardSetIjk interface to the 
 *    list of structured surface scalar sets in the traversal state.
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
 *    ScalarSetIjk {
 *    @TABLE_FILE_FORMAT
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *   Adds a scalar set to the structured volume scalar set list.  See MoScalarSetElementIjk.
 *
 * @SEE_ALSO
 *   MoScalarSetI, MoScalarSetIj
 * 
 */
class MESHIVIZDM_API MoScalarSetIjk : public MoActionNode {

  SO_NODE_HEADER(MoScalarSetIjk) ;
  
 public:

  /**
   * Constructor.
   */
  MoScalarSetIjk() ;

  /**
   * Sets the scalar set interface.
   */
  virtual void setScalarSet(const MiScalardSetIjk* scalarSet) { m_scalarSet = scalarSet; };

  /**
   * Gets the scalar set interface.
   */
  virtual const MiScalardSetIjk* getScalarSet() { return m_scalarSet; };

 /*----------------------------------------------------------------------------*/
  SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
  SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 protected:
  virtual ~MoScalarSetIjk() ;

  const MiScalardSetIjk* m_scalarSet;

} ; 

#endif /* _MO_SCALARSET_  */

