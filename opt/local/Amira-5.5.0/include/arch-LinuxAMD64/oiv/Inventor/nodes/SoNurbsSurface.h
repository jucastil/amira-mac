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


#ifndef  _SO_NURBS_SURFACE_
#define  _SO_NURBS_SURFACE_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/nodes/SoNurbsGroup.h>
#include <Inventor/threads/SbThreadRWMutex.h>
#include <Inventor/threads/SbThreadLocalStorage.h>
#include <Inventor/caches/SoVBOMgr.h>

class SoState;
class SoPrimitiveVertex;
class SoNurbsSurfaceCache;
class _SoNurbsNurbsTessellator;
class SoNurbsBREPAction;
class SoBrep;
class Pquad_tess_param;
class GLUnurbs;

/**
 * NURBS surface shape node.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This shape node represents a NURBS surface based on the node's knot vectors and
 *   on control points constructed from the current coordinates. The current
 *   coordinates are used in row-major order (the V direction corresponds to the
 *   rows). The number of coordinates used is determined by the
 *   #numUControlPoints and #numVControlPoints fields. The
 *   #uKnotVector and #vKnotVector fields contain floating point arrays
 *   of non-decreasing values.
 *   
 *   The order of the surface in the U and V directions is defined as the number of
 *   knots minus the number of control points in the particular direction. The
 *   largest order allowed for a NURBS surface is 8.
 *   
 *   The control points of the NURBS surface are transformed by the current cumulative
 *   transformation. The surface is drawn with the current light model and drawing
 *   style. The coordinates, normals, and texture coordinates of a surface are
 *   generated, so you cannot bind explicit normals or texture coordinates to a NURBS
 *   surface. The first material in the state is applied to the entire surface.
 *   
 *   The surface is trimmed according to the currently defined profile's curves.
 *   
 *   When default texture coordinates are applied to a NURBS surface, the edges of the
 *   texture square are stretched to fit the surface. The axes of the texture are
 *   called S and T; S is horizontal and T is vertical. The axes of the NURBS surface
 *   are called U and V; U is horizontal and V is vertical. You can also define
 *   texture coordinates explicitly with the S,T location point, the knot vectors,
 *   and the current texture coordinates. The number of texture coordinates used is 
 *   determined by the #numSControlPoints and #numTControlPoints fields. 
 *   
 *   The approximation of the surface by polygons is affected by the current
 *   complexity value.
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
 *    NurbsSurface {
 *    @TABLE_FILE_FORMAT
 *       @TR numUControlPoints   @TD 0
 *       @TR numVControlPoints   @TD 0
 *       @TR numSControlPoints   @TD 0
 *       @TR numTControlPoints   @TD 0
 *       @TR uKnotVector         @TD 0
 *       @TR vKnotVector         @TD 0
 *       @TR sKnotVector         @TD 0
 *       @TR tKnotVector         @TD 0
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
 *    SoIndexedNurbsSurface,
 *    SoNurbsCurve,
 *    SoNurbsProperty,
 *    SoProfile
 * 
 * 
 */ 

class INVENTOR_API SoNurbsSurface : public SoShape {

  SO_NODE_HEADER(SoNurbsSurface);
  
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
   * Number of control points in the S direction.
   */
  SoSFInt32 numSControlPoints;

  /**
   * Number of control points in the T direction.
   */
  SoSFInt32 numTControlPoints;

  /**
   * The knot vectors in the U direction.
   */
  SoMFFloat uKnotVector;

  /**
   * The knot vectors in the V direction.
   */
  SoMFFloat vKnotVector;

  /**
   * The knot vectors in the S direction.
   */
  SoMFFloat sKnotVector;

  /**
   * The knot vectors in the T direction.
   */
  SoMFFloat tKnotVector;

  /**
   * Creates a NURBS surface node with default settings.
   */
  SoNurbsSurface();

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

  SbBool needBREPUpdate(SoNurbsBREPAction *action);
  void invalidateCache();
  void fillBREP(SoAction *action, SoBrep *brep,
                SbBool doTexture, SoNurbsGroup::NurbsProperty &nurbsProperty);

  SoNurbsSurfaceCache *getNurbsCache() const { return nurbsCache; }
  SoNurbsSurfaceCache *getNurbsCacheUVs() const { return nurbsCacheUVs; }

  // Functions to compute complexity from Complexity
 static int computeSteps(SoState *state);

 protected:
  // Generates triangles representing a surface
  virtual void generatePrimitives(SoAction *action);

  float setTesselationParams(
    SoAction* action,
    const SoNurbsGroup::NurbsProperty &nurbsProperty,
    int steps,
    Pquad_tess_param &quad_tess_param);

  ~SoNurbsSurface();


 private:
  SoNurbsSurfaceCache *nurbsCache;
  SoNurbsSurfaceCache *nurbsCacheUVs;

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
  
  // Functions to compute complexity decimation elements
  int computePixelTolerance(SoState *state);
  
  void createNurbsCache(SoState *state, SbBool isShadered);
  SbBool isLinearProfile(SoState *state);

  // VBO management
  inline SoVBOMgr     *getVBOMgr() const
  { return (SoVBOMgr*)(m_VBOMgr.getValue()); }
  SoVBOMgr* allocateVBO(SoState* state);
  void deleteVBO(SoState *state);

  SbThreadStorage<SoVBOMgr*>  m_VBOMgr;
};

#endif /* _SO_NURBS_SURFACE_ */

