/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MO_DRAWSTYLE_
#define  _MO_DRAWSTYLE_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoNode.h>

#include <MeshVizInterface/mapping/nodes/MoActionNode.h>
#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>
 
/**
 * @DTEXT Property node that defines the draw style of surface representations.
 * 
 * @ingroup MeshIViz_Mapping_Attributes
 * 
 * @DESCRIPTION
 * This node specifies the draw style to be used in subsequent nodes inheriting 
 * from MoMeshRepresentation and defining a surface.
 * - The displayFaces field controls drawing cell faces as solid.
 * - The displayEdges field controls drawing cell edges.
 * - The displayPoints field controls drawing node points.
 *
 * See MoMaterial for setting the rendering attributes of facets, edges and points.
 *
 * Use this node, for example, to efficiently render a colored surface and
 * the outlines of its cells using a single rendering node.
 *
 * @note This node applies only to surface representations.
 *
 * @FILE_FORMAT_DEFAULT
 *    DataBinding {
 *    @TABLE_FILE_FORMAT
 *       @TR displayFaces           @TD TRUE
 *       @TR displayEdges           @TD FALSE
 *       @TR displayPoints          @TD FALSE
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *  MoMaterial
 *
 * @ACTION_BEHAVIOR
 *  Sets the current draw style. See MoDrawStyleElement.
 * 
 */
class MESHIVIZDM_API MoDrawStyle : public MoActionNode {

  SO_NODE_HEADER(MoDrawStyle) ;
  
 public:

  /**
   * Constructor.
   */
  MoDrawStyle() ;

  /** 
  * The display mode for mesh faces.
  * When set to TRUE (default), the surface of mesh representations are filled.
  * Otherwise, they are not filled.
  */
  SoSFBool displayFaces;

  /** 
  * The display mode for mesh edges.
  * When set to TRUE, the edges of faces are displayed. 
  * Otherwise, they are not displayed (Default).
  */
  SoSFBool displayEdges;
   
  /** 
  * The display mode for mesh node points.
  * When set to TRUE, the node points are displayed. 
  * Otherwise, they are not displayed (Default).
  */
  SoSFBool displayPoints;

 /*----------------------------------------------------------------------------*/
  SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
  SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

protected:
  virtual ~MoDrawStyle() ;

} ; 

#endif /* _MO_DRAWSTYLE_  */

