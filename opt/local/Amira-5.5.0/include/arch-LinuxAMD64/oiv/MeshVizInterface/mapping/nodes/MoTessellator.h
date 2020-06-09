/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MoTessellator_
#define  _MoTessellator_

#include <MeshVizInterface/mapping/nodes/MoActionNode.h>
#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>

class MiTessellator;

/**
 * @DTEXT Property node that defines a tessellator.
 * 
 * @ingroup MeshIViz_Mapping_Attributes
 * 
 * @DESCRIPTION 
 * This node stores an object implementing a tessellator interface in the scene graph. 
 *
 * Tessellator interfaces are used for creating an approximated graphical representation 
 * of a mesh supporting tesselation such as quadratic meshes. 
 * Representation nodes are using a basic tessellator (see MiTessellator) if no MoTessellator node
 * is provided in the scenegraph. However, the MoMeshSurface and MoMeshLine nodes, which do not perform any extractions,
 * require both a mandatory tessellator for proper rendering of quadratic meshes.
 *
 * @note Providing a tesselator for a non-quadratic mesh has no effect.
 *
 * @FILE_FORMAT_DEFAULT
 *    Tessellator {
 *    @TABLE_FILE_FORMAT
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *  MiTesselator, MoMeshSurface, MoMeshLine
 *
 */
class MESHIVIZDM_API MoTessellator : public MoActionNode {

  SO_NODE_HEADER(MoTessellator) ;
  
 public:

  /**
   * Constructor.
   */
  MoTessellator() ;

  //@{
  /**
   * Sets the tessellator interface. Sets the node as modified by calling touch().
   */
  virtual void setTessellator(MiTessellator* Tessellator);
  //@}
  
  /**
   * Gets the Tessellator interface.
   */
  virtual MiTessellator* getTessellator();

 /*----------------------------------------------------------------------------*/
  SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
  SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

protected:
  virtual ~MoTessellator() ;

private:
  MiTessellator* m_tessellator;
  size_t m_timeStamp;
} ; 

#endif /* _MoTessellator_  */

