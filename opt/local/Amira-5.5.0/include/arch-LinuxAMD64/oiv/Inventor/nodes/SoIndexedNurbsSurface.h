/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Dave Immel (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_INDEXED_NURBS_SURFACE_
#define  _SO_INDEXED_NURBS_SURFACE_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/nodes/SoNurbsGroup.h>
#include <Inventor/threads/SbThreadRWMutex.h>
#include <Inventor/threads/SbThreadLocalStorage.h>
#include <Inventor/caches/SoVBOMgr.h>

class SoState;
class SoPrimitiveVertex;
class SoIndexedNurbsSurfaceCache;
class _SoNurbsNurbsTessellator;
class SoNurbsBREPAction;
class SoBrep;
class Pquad_tess_param;
class GLUnurbs;

/**
 * Indexed NURBS surface shape node.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This shape node represents a NURBS surface based on the knot vectors and the
 *   control points that you specify. The #uKnotVector and #vKnotVector
 *   fields specify floating-point arrays of values; the values are the coordinates
 *   of the knot points in the surface, and you must enter them in non-decreasing
 *   order. The #numUControlPoints and #numVControlPoints fields specify
 *   the number of control points the surface will have in the U and V parametric
 *   directions, and will use the current coordinates that are indexed from the
 *   #coordIndex field.
 *   
 *   You can get a surface of minimum order (2) in the U or V directions by specifying
 *   two more knots than control points in that direction and having at least two
 *   control points in that direction. This surface would appear creased in one
 *   direction.
 *   
 *   You can get a surface of maximum order (8) in the U or V directions by specifying
 *   eight more knots than control points in that direction and having at least eight
 *   control points in that direction.
 *   
 *   The control points of the NURBS surface are transformed by the current cumulative
 *   transformation. The surface is drawn with the current light model and drawing
 *   style. The coordinates, normals, and texture coordinates of a surface are
 *   generated, so you cannot bind explicit normals or texture coordinates to a NURBS
 *   surface. The first material in the state is applied to the entire surface.
 *   
 *   The surface is trimmed according to the currently defined profiles curves.
 *   
 *   When default texture coordinates are applied to a NURBS surface, the edges of the
 *   texture square are stretched to fit the surface. The axes of the texture are
 *   called S and T; S is horizontal and T is vertical. The axes of the NURBS surface
 *   are called U and V; U is horizontal and V is vertical. You can also define
 *   texture coordinates explicitly with the S,T location point, the knot vectors,
 *   and the current texture coordinates.
 *
 *   @B NOTE@b:
 *   - If OIV_FORCE_GLU_NURB is set to 1, GLU is used to render textured and
 *      untextured NURBS surfaces.
 *
 *   - GLU is also used if SoComplexity::type == SCREEN_SPACE. Be careful
 *   as tessellation may take a significant amount of time when the camera is very
 *   close to the surface.
 *
 *   - Otherwise
 *     (i.e., if SoComplexity::type == OBJECT_SPACE and OIV_FORCE_GLU_NURB 
 *      is not set), an Open Inventor NURBS algorithm is used.
 *
 * @FILE_FORMAT_DEFAULT
 *    IndexedNurbsSurface {
 *    @TABLE_FILE_FORMAT
 *       @TR numUControlPoints   @TD 0
 *       @TR numVControlPoints   @TD 0
 *       @TR numSControlPoints   @TD 0
 *       @TR numTControlPoints   @TD 0
 *       @TR coordIndex          @TD 0
 *       @TR uKnotVector         @TD 0
 *       @TR vKnotVector         @TD 0
 *       @TR sKnotVector         @TD 0
 *       @TR tKnotVector         @TD 0
 *       @TR textureCoordIndex   @TD -1
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws the surface based on the current coordinates, material, and so on.
 * 
 *    SoRayPickAction @BR
 *        Picks the surface based on the current coordinates and transformation.
 * 
 *    SoGetBoundingBoxAction @BR
 *        Computes the bounding box that encloses all control points of the surface with
 *        the current transformation applied to them. Sets the center to the average of
 *        the control points.
 * 
 *    SoCallbackAction @BR
 *        If any triangle callbacks are registered with the action, they will be invoked
 *        for each successive triangle approximating the surface.
 * 
 * 
 * @SEE_ALSO
 *    SoFullSceneAntialiasing,
 *    SoIndexedNurbsCurve,
 *    SoNurbsSurface,
 *    SoProfile
 * 
 * 
 */ 

class INVENTOR_API SoIndexedNurbsSurface : public SoShape {
  
  SO_NODE_HEADER(SoIndexedNurbsSurface);
  
 public:
  /**
   * Number of control points in the U direction.
   */
  SoSFInt32 numUControlPoints;

  /**
   * Number of control points in the V direction.
   */
  SoSFInt32 numVControlPoints;

  /**
   * Coordinate indices.
   */
  SoMFInt32 coordIndex;

  /**
   * The knot vectors in the U direction.
   */
  SoMFFloat uKnotVector;

  /**
   * The knot vectors in the V direction.
   */
  SoMFFloat vKnotVector;

  /**
   * Number of control points in the S direction.
   */
  SoSFInt32 numSControlPoints;

  /**
   * Number of control points in the T direction.
   */
  SoSFInt32 numTControlPoints;

  /**
   * Texture coordinate indices.
   */
  SoMFInt32 textureCoordIndex;

  /**
   * The knot vectors in the S direction.
   */
  SoMFFloat sKnotVector;

  /**
   * The knot vectors in the T direction.
   */
  SoMFFloat tKnotVector;

  /**
   * Creates an indexed NURBS surface node with default settings.
   */
  SoIndexedNurbsSurface();

 SoEXTENDER public:
  virtual void GLRender(SoGLRenderAction *action);
  virtual void rayPick(SoRayPickAction *action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);

  // Computes bounding box of surface
  virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);


 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  void sendPrimitive(SoAction *, SoPrimitiveVertex *);

  SoIndexedNurbsSurfaceCache *getNurbsCache() const { return nurbsCache; }

 protected:
  // Generates triangles representing surface
  virtual void generatePrimitives(SoAction *action);

  float setTesselationParams(SoAction* action,
    const SoNurbsGroup::NurbsProperty &nurbsProperty,
    int steps,
    Pquad_tess_param &quad_tess_param);

  ~SoIndexedNurbsSurface();
  
 private:
  SoIndexedNurbsSurfaceCache *nurbsCache;

  SbThreadRWMutex       *nurbsCacheMutex;

  int isValid(SoState *state, SbBool renderAction);

  // Tessellate the surface
  void tesselateNURBS_G5G(SoAction *action,
                          SbBool doTextures,
                          int32_t steps,
                          SoBrep *brep,
                          SoNurbsGroup::NurbsProperty &nurbsProperty);
  void tesselateNURBS_G5G(SoAction *action, SbBool doTextures, int32_t steps);

  // Renders the surface
  void drawNURBS_G5G(SoAction *action, SbBool doTextures, int32_t steps);
  
  // Renders the surface
  void drawNURBS(_SoNurbsNurbsTessellator *render, SoState *state,
                 SbBool doTextures);

  // Renders the surface
  void drawNURBS_GLU(GLUnurbs *nurbsObj, SoState *state, SbBool doTextures);

  // Matrix operations for level of detail and culling
  void calcTotalMatrix(SoState *state, SbMatrix &totalMat);
  void multMatrix4d(SbMatrix &n, SbMatrix left, SbMatrix right);
  
  // This callback gets details from the NURBS library
  static void primCB(SoAction *, SoPrimitiveVertex *, void *);
  
  // Functions to compute complexity from Complexity
  // and decimation elements
  int computeSteps(SoState *state);
  int computePixelTolerance(SoState *state);
  
  void createNurbsCache(SoState *state, SbBool isShadered);
  SbBool isLinearProfile(SoState *state);

  // VBO management
  inline SoVBOMgr     *getVBOMgr() const
  { return (SoVBOMgr*)(m_VBOMgr.getValue()); }
  SoVBOMgr* allocateVBO(SoState* state);
  void deleteVBO(SoState *state);

  SbThreadStorage<SoVBOMgr*> m_VBOMgr;
};

#endif /* _SO_INDEXED_NURBS_SURFACE_ */

