/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLTRIANGLE_SET_
#define  _SO_VRMLTRIANGLE_SET_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/VRMLnodes/SoVRMLVertexShape.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLTriangleSet
//
//  TriangleSet node.   
//
//////////////////////////////////////////////////////////////////////////////

class SoNormalBundle;
class SoCoordinateElement;
class SoShapeStyleElement;

/**
 * Triangle set shape node.\ @NO_ACTION 
 * 
 * @ingroup X3D
 * 
 * @DESCRIPTION
 *   The SoVRMLTriangleSet node is a 3D shape that represents a collection of individual
 *   triangles. 
 *
 * @VRMLX3D_SPECIFICATION
 *   This section describes the expected behavior of the node in a conforming X3D
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the X3D specification that are not
 *   present in this help file. The complete X3D spec is available at
 *   @B http://www.web3d.org @b. 
 *
 *   The #coord field contains a Coordinate node that defines the 3D vertices that define
 *   the triangles. Each triangle is formed from a consecutive set of three vertices of 
 *   the coordinate node. If the coordinate node does not contain a multiple of three 
 *   coordinate values, the remaining vertices will be ignored.
 *    
 *   The figure below shows an SoVRMLTriangleSet node with several triangles. The 
 *   ordering of the vertices is also shown. An arrow points to a vertex at the apex 
 *   of the pyramid. Note that vertices 3 and 14 are obscured.
 *
 *   @IMAGE TriangleSet.jpg
 *
 *   The SoVRMLTriangleSet node is specified in the local coordinate system and is affected 
 *   by the transformations of its ancestors. Descriptions of the #color, #coord, #normal, and 
 *   #texCoord fields are provided in the Color, Coordinate, Normal, and TextureCoordinate nodes, 
 *   respectively. If values are provided for the #color, #normal, and #texCoord fields, there 
 *   must be at least as many values as are present in the #coord field. The value of the 
 *   #colorPerVertex field is ignored and always treated as TRUE. If the #normal field is not 
 *   supplied, the normal will be generated as perpendicular to the face for either version 
 *   of #normalPerVertex.
 *   
 *   See the introductory "Concepts - Geometry" section for a description of the #solid field. 
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VRMLTriangleSet {
 *    @TABLE_FILE_FORMAT
 *       @TR color             @TD NULL
 *       @TR coord             @TD NULL
 *       @TR normal            @TD NULL
 *       @TR texCoord          @TD NULL
 *       @TR ccw               @TD TRUE
 *       @TR colorPerVertex    @TD TRUE
 *       @TR normalPerVertex   @TD TRUE
 *       @TR solid             @TD TRUE
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoGetBoundingBoxAction,  SoCallbackAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN       
 *       @TR   SoSFNode    @TD   set_color      
 *       @TR   SoSFNode    @TD   set_coord      
 *       @TR   SoSFNode    @TD   set_normal      
 *       @TR   SoSFNode    @TD   set_texCoord
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode    @TD   color_changed      
 *       @TR   SoSFNode    @TD   coord_changed      
 *       @TR   SoSFNode    @TD   normal_changed      
 *       @TR   SoSFNode    @TD   texCoord_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 



class INVENTOR_API SoVRMLTriangleSet : public SoVRMLVertexShape {
  
  SO_NODE_HEADER(SoVRMLTriangleSet);
  
 public:
  // Fields
  /**
   * Indicates whether the vertices are ordered in a counterclockwise direction when
   * viewed from the outside (TRUE) or in a clockwise direction (FALSE).
   * 
   */
  SoSFBool              ccw;
  /**
   * If the shape encloses a volume, the value is TRUE. Used as a hint to perform
   * backface culling. If nothing is known, the field value is FALSE.
   * 
   */
  SoSFBool            solid;
  /**
   * Creates a TriangleSet node with default settings.
   */
  SoVRMLTriangleSet();
  
 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

  
  // Generates default normals using the given normal bundle. 
  // Returns TRUE.
  virtual SbBool generateDefaultNormals(SoState *state, SoNormalBundle *nb);
  
  // Computes bounding box of triangle strips
  virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);
    
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  // Generates triangles representing strips
  virtual void generatePrimitives(SoAction *action);
  
  // Overrides standard method to create an SoFaceDetail instance
  virtual SoDetail *createTriangleDetail(SoRayPickAction *action,
                                         const SoPrimitiveVertex *v1,
                                         const SoPrimitiveVertex *v2,
                                         const SoPrimitiveVertex *v3,
                                         SoPickedPoint *pp);
  
  virtual ~SoVRMLTriangleSet();

  // vpCache stores information from one render to the next about
  // what information needs to be grabbed from the state, etc.
  SoVRMLVertexPropertyCache   vpCache;
 
 private:
  // Blow vpCache when vertexProperty field changes:
  virtual void notify(SoNotList *list);

  // render function
  void doRendering(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);
};

#endif /* _SO_VRMLTRIANGLE_SET_ */
