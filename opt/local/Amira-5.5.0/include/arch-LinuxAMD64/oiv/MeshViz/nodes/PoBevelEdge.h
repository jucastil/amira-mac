/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_BEVEL_EDGE_
#define  _PO_BEVEL_EDGE_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>

#include <MeshViz/nodes/PoNode.h>

/**
 * @DTEXT  Node to define the beveled edge values.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *    This node defines the current values to bevel edges of all subsequent
 *    MeshViz representations inhering from PoChart.
 *    The way in which edges are beveled is defined by a radius to indicate the
 *    size of the bevel and by a bevelAngle to indicate the minimum angle between
 *    two adjacent face normals required to bevel the edge common to these 
 *    two faces.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoBevelEdge {
 *    @TABLE_FILE_FORMAT
 *       @TR on @TD TRUE
 *       @TR radius @TD 0.05
 *       @TR radiusFlag @TD PERCENTAGE_RADIUS
 *       @TR bevelAngle @TD 0.5
 *    @TABLE_END
 *    }
 * 
 * 
 */

class MESHVIZ_API PoBevelEdge : public PoNode {
  
  SO_NODE_HEADER(PoBevelEdge) ;
  

 public:

  /**
   *  Radius Type.
   */
  enum RadiusFlag {
    ABSOLUTE_RADIUS,
    PERCENTAGE_RADIUS
  } ;

  /* Fields */

  /**
   * Activate/Desactivate bevel attributes.
   */
  SoSFBool  on ;

  /**
   * Indicates the radius of the bevel.
   */
  SoSFFloat radius ;

  /**
   * Defines the interpretation of the field radius. 
   * If radiusFlag == ABSOLUTE_RADIUS, the radius value is absolute.
   * If radiusFlag == PERCENTAGE_RADIUS, the field radius is a percentage (0. <= radius <= 1.),
   * the real radius corresponding is max * radius, where max is the maximun length of all 
   * the edges of the current shape to be beveled.
   */
  SoSFEnum  radiusFlag ;

  /**
   * Indicates the minimum angle (in radians) between two adjacent face normals required
   * to bevel the edge common to these two faces.
   */
  SoSFFloat bevelAngle ;

  /**
   * Constructor.
   */
  PoBevelEdge() ;

  /*----------------------------------------------------------------------------*/

  
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;
  
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  virtual ~PoBevelEdge() ;
  
} ;
/*----------------------------------------------------------------------------*/

#endif /* _PO_BEVEL_EDGE_  */

