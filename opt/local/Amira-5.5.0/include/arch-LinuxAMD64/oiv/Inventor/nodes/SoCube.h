/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_CUBE_
#define  _SO_CUBE_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoShape.h>

class SoVBOMgr;
/**
 * Cube shape node.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This node represents a cuboid aligned with the coordinate axes. By default, the
 *   cube is centered at (0,0,0) and measures 2 units in each dimension, from -1 to
 *   +1. The cube is transformed by the current cumulative transformation and is
 *   drawn with the current lighting model, drawing style, material, and geometric
 *   complexity.
 *   
 *   If the current material binding is PER_PART, PER_PART_INDEXED, PER_FACE, or
 *   PER_FACE_INDEXED, materials will be bound to the faces of the cube in this
 *   order: front, back, left, right, top, and bottom.
 *   
 *   Textures are applied individually to each face of the cube; the entire texture
 *   goes on each face. On the front, back, right, and left sides of the cube, the
 *   texture is applied right side up. On the top, the texture appears right side up
 *   when the top of the cube is tilted toward the camera. On the bottom, the texture
 *   appears right side up when the top of the cube is tilted away from the camera.
 *
 *   OpenGL vertex arrays are used if they are available and if the
 *   environment variable IV_NO_VERTEX_ARRAY is not set.
 *
 * @FILE_FORMAT_DEFAULT
 *    Cube {
 *    @TABLE_FILE_FORMAT
 *       @TR width    @TD 2
 *       @TR height   @TD 2
 *       @TR depth    @TD 2
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws cube based on the current coordinates, materials, drawing style, and so
 *        on.
 * 
 *    SoRayPickAction @BR
 *        Intersects the ray with the cube. The face of the cube that was picked is
 *        available from the SoCubeDetail.
 * 
 *    SoGetBoundingBoxAction @BR
 *        Computes the bounding box that encloses the cube.
 * 
 *    SoCallbackAction @BR
 *        If any triangle callbacks are registered with the action, they will be invoked
 *        for each successive triangle that approximates the cube.
 * 
 * 
 * @SEE_ALSO
 *    SoCone,
 *    SoCubeDetail,
 *    SoCylinder,
 *    SoFullSceneAntialiasing,
 *    SoSphere
 * 
 * 
 */ 

class INVENTOR_API SoCube : public SoShape {

  SO_NODE_HEADER(SoCube);

 public:
  // Fields
  /**
   * Size in the x dimension.
   */
  SoSFFloat           width;          // Size in x dimension
  /**
   * Size in the y dimension.
   */
  SoSFFloat           height;         // Size in y dimension
  /**
   * Size in the z dimension.
   */
  SoSFFloat           depth;

  /**
   * Creates a cube node with default settings.
   */
  SoCube();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        rayPick(SoRayPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

  // Computes bounding box of cube
  virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                  SbVec3f &center);
  
 SoINTERNAL public:

  /** register node in database */
  static void initClass();
  /** unregister node from database */
  static void exitClass();

  SB_THREAD_TLS_HEADER();

  // Renders or picks cube representing given bounding box. These
  // are used by SoShape to implement BOUNDING_BOX complexity.
  void GLRenderBoundingBox(SoGLRenderAction *action, const SbXfBox3d &bbox);
  void GLRenderBoundingBox(SoGLRenderAction *action, const SbBox3f &bbox)
  {
    GLRenderBoundingBox(action, SbXfBox3d(SbBox3d(bbox)));
  }
  void                rayPickBoundingBox(SoRayPickAction *action, const SbBox3f &bbox);

protected:
  // Generates triangles representing a cube
  virtual void        generatePrimitives(SoAction *action);

  // Overrides standard method to create an SoCubeDetail instance
  virtual SoDetail *  createTriangleDetail(SoRayPickAction *action,
                                           const SoPrimitiveVertex *v1,
                                           const SoPrimitiveVertex *v2,
                                           const SoPrimitiveVertex *v3,
                                           SoPickedPoint *pp);

  virtual ~SoCube();

  using SoShape::GLRenderBoundingBox;

 private:
  static SbVec3f coords[8];      // Corner coordinates
  static SbVec2f texCoords[4];   // Face corner texture coordinates
  static SbVec3f normals[6];     // Face normals
  static SbVec3f verts[6][4];    // Vertex

  // PER_VERTEX infos:
  static SbVec3f s_normals[24];   // vertex normals
  static SbVec2f s_texCoords[24]; // vertex texCoords

  // This flag indicates whether picking is done on a real cube or a
  // cube that is just a bounding box representing another shape. If
  // this flag is TRUE, a pick on the cube should not generate a
  // detail, since the bounding box is not really in the picked path.
  SbBool              pickingBoundingBox;

  // Returns TRUE if per face materials are specified
  SbBool              isMaterialPerFace(SoAction *action) const;

  // Computes number of divisions per side based on complexity
  int                 computeNumDivisions(SoAction *action) const;

  // Computes real half-width, -height, -depth
  void                getSize(float &hWidth,
                              float &hHeight,
                              float &hDepth) const;

  // These render the cube
  void                GLRenderGeneric(SoGLRenderAction *action,
                                      SbBool sendNormals, SbBool doTextures);
  void                GLRenderNvertTnone(SoGLRenderAction *action);

  void                GLRenderDivision1(SoGLRenderAction *action);

  // struct for TLS
  static SoVBOMgr* getVBOMgr();
  struct MTstruct {
    SoVBOMgr* VBOMgr;
  };

  // SoShape needs to get at the above methods
  friend class SoShape; 
};

#endif /* _SO_CUBE_ */

