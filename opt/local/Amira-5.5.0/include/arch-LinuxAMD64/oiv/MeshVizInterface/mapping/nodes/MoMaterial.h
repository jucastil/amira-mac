/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MO_MATERIAL_
#define  _MO_MATERIAL_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoNode.h>

#include <MeshVizInterface/mapping/nodes/MoActionNode.h>
#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>
 
/**
 * @DTEXT Property node that defines the material of surface representations.
 * 
 * @ingroup MeshIViz_Mapping_Attributes
 * 
 * @DESCRIPTION
 * This node specifies the coloring to be used in subsequent nodes inheriting from MoMeshRepresentation
 * and defining a surface.
 * Specifically the face, edge and point coloring methods which can be uniform or contouring.
 * - Uniform color means that all entities are drawn using the face, line or edge color.
 * - Contouring means that the rendering uses the color mapping defined by a scalar set and a 
 *   color mapping function (see MoColorMapping) to display color contours.
 *
 * When the enhanced coloring method is enabled (enhancedColoring field set to TRUE), polygons are colored using a technique allowing 
 * to display more accurately the color gradient than what can be achieved normally with OpenGL.
 *
 * @note This node applies only to surface representations.
 *
 * @FILE_FORMAT_DEFAULT
 *    DataBinding {
 *    @TABLE_FILE_FORMAT
 *       @TR faceColoring      @TD CONTOURING
 *       @TR faceColor         @TD (1,1,1)
 *       @TR lineColoring      @TD CONTOURING
 *       @TR lineColor         @TD (1,0,0)
 *       @TR pointColoring     @TD CONTOURING
 *       @TR pointColor        @TD (0,1,0)
 *       @TR transparency      @TD (0.0)
 *       @TR enhancedColoring  @TD FALSE
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *  MoDrawStyle for turning on display of facets, edges and points.
 *
 * @ACTION_BEHAVIOR
 *  Sets the current color and coloring options. See MoMaterialElement.
 * 
 */
class MESHIVIZDM_API MoMaterial : public MoActionNode {

  SO_NODE_HEADER(MoMaterial) ;
  
 public:

  /**
   * Constructor.
   */
  MoMaterial() ;


  /** Color Coloring type  */
  enum ColoringType {
    COLOR,           /**< Use the color field to fill facets in an uniform color */
    CONTOURING,      /**< (default) Use the color mapping defined by a scalar set and a color mapping function to display color contours. */
  };

  /** 
  * The coloring method for faces. 
  * Use enum #ColoringType. Default is CONTOURING.
  */
  SoSFEnum faceColoring;
   
  /** 
  * Uniform color used for faces when faceColoring is set to COLOR. Default is white (1,1,1).
  */
  SoSFColor faceColor; 
  
  /** 
  * The coloring method for lines. 
  * Use enum #ColoringType. Default is CONTOURING.
  */
  SoSFEnum lineColoring;
   
  /** 
  * Uniform color used for lines and edges when lineColoring is set to COLOR. Default is red (1,0,0).
  */
  SoSFColor lineColor; 

  /** 
  * The coloring method for points. Default is CONTOURING.
  */
  SoSFEnum pointColoring;
   
  /** 
  * Uniform color used for points when pointColoring is set to COLOR. Default is green (0,1,0).
  */
  SoSFColor pointColor; 

  /** 
  * Transparency value used to display surfaces. 1 means fully transparent, 0 opaque (default).
  */
  SoSFFloat transparency; 

  /** 
  * When set to TRUE, polygons with more than three points are colored using a technique
  * that more accurately displays the color gradient. @n
  * The default interpolation (FALSE) provided by OpenGL is done by splitting the polygons 
  * into triangles and coloring each triangle independently, ignoring information about the 
  * other nodes of the polygon.
  *
  * On the following image, you can see the difference between the coloring obtained with this 
  * flag set (left) and not set (right).  
  *
  * @TABLE_0B
  *         @TR @IMAGE enhancedColoring.png  
  * @TABLE_END
  *
  * @note This technique may significantly impact the rendering performance and requires a 
  *       graphic board supporting OpenGL 2.0 or higher.
  *       This mode simulates the lighting of a single diffuse white light source. Other 
  *       lights defined in the scene graph have no effect. 
  */
  SoSFBool enhancedColoring; 

 /*----------------------------------------------------------------------------*/
  SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
  SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

protected:
  virtual ~MoMaterial() ;

} ; 

#endif /* _MO_MATERIAL_  */

