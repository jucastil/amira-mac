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


#ifndef  _SO_SHAPE_
#define  _SO_SHAPE_

#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFBool.h>

#include <Inventor/sys/SoGLType.h>

class SoCube;
class SoDetail;
class SoFaceDetail;
class SoMaterialBundle;
class SoPickedPoint;
class SoPointDetail;
class SoPrimitiveVertex;
class SoState;
class SoMFInt32;
class SoMultiPassManager ;
class GLUtesselator;

typedef SoPrimitiveVertex *jySoPrimitiveVertexPtr;
typedef SoDetail *jySoDetailPtr;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoShape
//
//  Abstract base shape node class, which provides some convenience
//  functions for its subclasses.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Abstract base class for all shape nodes.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This node is the abstract base class for all shape (geometry) nodes. All classes
 *   derived from SoShape draw geometry during render traversal.
 * 
 * @FILE_FORMAT_DEFAULT
 *    This is an abstract class. See the reference page of a derived class for the
 *   format and default values.
 * 
 * @SEE_ALSO
 *    SoCone,
 *    SoCube,
 *    SoCylinder,
 *    SoFullSceneAntialiasing,
 *    SoIndexedNurbsCurve,
 *    SoIndexedNurbsSurface,
 *    SoNurbsCurve,
 *    SoNurbsSurface,
 *    SoShapeHints,
 *    SoShapeKit,
 *    SoSphere,
 *    SoText2,
 *    SoText3,
 *    SoVertexShape
 * 
 * 
 */ 

class INVENTOR_API SoShape : public SoNode {

  SO_NODE_ABSTRACT_HEADER(SoShape);

 public:
  /**
   * Whether to ignore this node during bounding box traversal. Default is FALSE.
   */
  SoSFBool boundingBoxIgnoring;

  /**
   * Overrides default method on SoNode
   */
  virtual SbBool affectsState() const;

  /** 
   * Basic type for antialiased rendering for this shape (Do not consider the SoDrawStyle
   * property currently in the state). Default shape type is POLYGONS.
   */

  enum ShapeType {
  /** The shape is render based on points (Ex: SoPointSet).*/
    POINTS,
  /** The shape is render based on lines (Ex: SoLineSet).*/
    LINES,
  /** The shape is render based on polygons (Ex: SoFaceSet).*/
    POLYGONS,
  /** The shape is a text and follows the special filter for texts.*/
    TEXT
  };

  /**
   * Gets the current shape Full Scene Antialiasing type.
   */
  ShapeType getShapeType();

  /**
   * Returns TRUE if the primitive restart feature is available.
   *
   * It is better to call this function with an SoGLContext created on
   * the device used for rendering or with a valid state. 
   *
   * Primitive restart (if available) can be used with SoBufferedShape.
   */
  static SbBool isPrimitiveRestartAvailable(SoState* state = NULL);

 SoEXTENDER public:

  /**
   * This type is used by the triangle shape generation methods
   * (beginShape, etc.)
   */
  enum TriangleShape {
    TRIANGLE_STRIP,
    TRIANGLE_FAN,
    TRIANGLES,
    POLYGON
  };

  /**
   * These methods can be used by subclasses to generate triangles
   * more easily when those triangles are part of a larger
   * structure, such as a triangle strip, triangle fan, or
   * triangulated polygon, according to the TriangleShape enumerated
   * type. The sequence of calls is similar to GL's: begin a shape,
   * send vertices of that shape, then end the shape.
   *
   * If the face detail passed to beginShape() is NULL (the
   * default), the details in the vertices will be used as is.
   * Note that some vertices may be copied into local storage; the
   * detail pointers are copied as well, so the details themselves
   * should be consistent for the duration of the shape generation.
   *
   * If the face detail passed to beginShape() is non-NULL, the
   * details in the vertices are assumed to be SoPointDetails. Each
   * vertex of each triangle generated will contain a pointer to the
   * face detail, which will be filled with three copies of the
   * point details from the relevant vertices. Since copies of the
   * point details are made, the storage for each point detail
   * passed to shapeVertex() can be re-used by the caller.
   */
  void beginShape(SoAction *action, TriangleShape shapeType,
    SoFaceDetail *faceDetail = NULL);

  /** 
   * add a primitive vertex to the shape prevously started with beginShape().
   * [OIV-WRAPPER-ARG IN]
   */
  void shapeVertex(const SoPrimitiveVertex *v);

  /**
   * end shape previously started with beginShape().
   */
  void endShape();

 SoEXTENDER public:
  /**
   * Implements bounding box method using virtual computeBBox()
   * method. Subclasses should not need to override this.
   */
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);

  /**
   * Implements rendering by rendering each primitive generated by
   * subclass. May be overridden in subclass.
   */
  virtual void GLRender(SoGLRenderAction *action);

  /**
   * Implements picking along a ray by intersecting the ray with
   * each primitive generated by subclass. May be overridden in
   * subclass.
   */
  virtual void rayPick(SoRayPickAction *action);

  /**
   * Implements primitive generation for all shapes. Calls the 
   * generatePrimitives for the shape.
   */
  virtual void callback(SoCallbackAction *action);

  /**
   * This can be used by subclasses when the complexity type is
   * SCREEN_SPACE to determine how many window pixels are covered by
   * the shape. It returns in rectSize the number of pixels in the
   * window rectangle that covers the given 3D bounding box.
   */
  static void getScreenSize(SoState *state, const SbBox3f &boundingBox, SbVec2s &rectSize);

  /**
   * This can be used by dynamic shape subclasses that use
   * the complexity element, to compute how the decimation
   * element affects the complexity of the shape.
   * The shape passes in the complexity it would have
   * used and this function returns the new complexity to use
   * based on decimation element.
   */
  static float getDecimatedComplexity(SoState *state, float complexity);

  /**
   * Compute axis aligned bounding box (AABB) for subclass using information in the
   * given action (which may not necessarily be an
   * SoGetBoundingBoxAction). This is used by getBoundingBox() and
   * when rendering or picking a shape with bounding-box complexity.
   * Subclasses must define this method.
   */
  virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center) = 0;

  /** 
   * Compute object oriented bounding box (OOB) for subclass using information in the
   * given action (which may not necessarily be an
   * SoGetBoundingBoxAction). This is used by getBoundingBox() and
   * when rendering or picking a shape with bounding-box complexity.
   *
   * This method returns an Object Oriented Bounding Box (OOB), which may
   * be more efficient for picking, colision detection, and culling compared 
   * to an axis aligned bounding box, at the cost of more computing time.
   * Subclasses should override this method, if not then the axis aligned
   * bounding bbox is used.
   * 
   * By default Open Inventor only uses the axis aligned bounding box (AABB).
   * OOB can be enabled using SoComplexity or the OIV_USE_OOB environment variable.
   *
   */
  virtual void computeBBox(SoAction *action, SbXfBox3d &box, SbVec3d &center)
  {
    // SubClass did not redefine this function so by default use AABB version
    SbBox3f boxf;
    SbVec3f centerf;
    computeBBox(action, boxf, centerf);

    box.setTransform(SbMatrixd::identity());
    box.makeEmpty();
    box.setBounds(SbVec3d(boxf.getMin().getValue()),SbVec3d(boxf.getMax().getValue()));
    center.setValue(centerf);
  }

  /**
   * Counts number of primitives produced by this shape.
   * Default action uses primitive callbacks, subclasses should
   * derive their own method if they can do it faster.
   */
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);

  /**
   * Set the OpenGL raster position given an object space point.
   *
   * This utility function correctly handles the case when raster
   * position should be outside the display window, which glRasterPos
   * does not allow.  This is useful for SoText2, SoImage, etc.
   */
  static void setRasterPos( SbVec3f &pos, SoState *state );

  /**
   * Compute transformations from Modelling coordinate to tangent space (facet space).
   */
  virtual SbMatrix3* computeVtxTangentSpaceMat(const float *, int &) const
    {return NULL ;}

  // Gets multi-texturing info:
  //    - Indicates if the multi-texturing is active
  //    - The list of texture units where texture coordinate should be sent (that is
  //       where texture coordinates differents from a function.)
  static SbBool getMultiTextureInfo(SoState *state, SbIntList &imageTextUnitList) ;
                                   
  /**
   * set the antialiasing type for this shape.
   */
  void setShapeType(SoShape::ShapeType st);

  // These methods invoke whatever callbacks are registered with the
  // primitive generation procedures. If primitives are being
  // generated for picking or rendering purposes, the appropriate
  // SoShape methods are called. If primitives are being generated
  // for the SoCallbackAction, the callbacks registered with the
  // action are called.
  void invokeTriangleCallbacks(SoAction *action,
                               const SoPrimitiveVertex *v1,
                               const SoPrimitiveVertex *v2,
                               const SoPrimitiveVertex *v3);
  void invokeLineSegmentCallbacks(SoAction *action,
                                  const SoPrimitiveVertex *v1,
                                  const SoPrimitiveVertex *v2);
  void invokePointCallbacks(SoAction *action,
                            const SoPrimitiveVertex *v);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  SB_THREAD_TLS_HEADER();

  /**
   * Used by BoundingBoxAction to know if bounding box computation should 
   * be ignored or not.
   * By default the returned value is given by boundingBoxIgnoring field.
   */
  inline virtual SbBool isBoundingBoxIgnoring() const
  { return boundingBoxIgnoring.getValue(); }

  // It is possible to disable projection for a given shape even if the element is set
  SbBool m_forceDisableProjection;

  void setForceDisableProjection( SbBool disable ){m_forceDisableProjection = disable;}

  SbBool getTTSA();
  // set Triangles Transparency Sorting Availability
  void setTTSA(SbBool enable);

  static bool isVertexArrayAvailable(SoState* state=NULL);
  static bool isMultiDrawArrayAvailable(SoState* state=NULL);
  static bool isVertexBufferAvailable(SoState* state=NULL);

  // Returns 0 if not available, 1 if NV version, 2 if core
  static int getPrimitiveRestartMode(SoState* state = NULL);

 protected:

  // Constructor
  SoShape();

  virtual SbBool checkShapeHints(SoGLRenderAction *action,SbThreadAutoWriteLock *autolock=0);

  virtual void countPrim(){}

  virtual int getNumPrim(){return 0;}

  virtual SbBool checkTransparency(SoGLRenderAction *action, SbBool isPointsOrLines);

  virtual int getNumVert(){return getNumPrim();}

  virtual SbBool numPrimInvalid(){return FALSE;}

  virtual SbBool isRenderingPointsOrLines(SoGLRenderAction *action);

  virtual SbBool shouldRenderNow(SoGLRenderAction *action,SbBool &isPointsOrLines);

  //-------------------------------------------------------------------------------

  // This method MUST be defined by each subclass to generate
  // primitives (triangles, line segments, points) that represent
  // the shape.
  virtual void generatePrimitives(SoAction *action) = 0;

  // Returns TRUE if the shape should be rendered. Subclasses can
  // call this in their rendering methods to determine whether to
  // continue.  
  virtual SbBool shouldGLRender(SoGLRenderAction *action,
                                SbBool isPointsOrLines = FALSE);

  // Returns FALSE if the shape is invisible. If the complexity
  // is BOUNDING_BOX, it renders the cuboid and returns FALSE.
  // Otherwise returns TRUE.
  SbBool handleInvisibleOrBBox(SoGLRenderAction *action,
                                SbBool isPointsOrLines = FALSE);

  // Returns TRUE if the shape may be picked. Subclasses can call
  // this in their picking methods to determine whether to continue.
  SbBool shouldRayPick(SoRayPickAction *action);

  // Returns TRUE if the shape should be rendered. Subclasses can
  // call this in their rendering methods to determine whether to
  // continue. 
  SbBool shouldPrimitiveCount(SoGetPrimitiveCountAction *action);

  /// These can be used by solid shapes to indicate so during
  // rendering. They take care of setting up shape hints in the
  // state. Calls to these two methods should bracket the rendering
  // code.
  void beginSolidShape(SoGLRenderAction *action);
  void endSolidShape(SoGLRenderAction *action);

  // Computes a picking ray in the object space of the shape
  // instance. The picking ray is stored in the SoRayPickAction for
  // later access by the subclass. The second form takes a matrix to
  // concatenate with the current transformation matrix. It can be
  // used, for example, if a shape has sizing or positioning info
  // built into it.
  void computeObjectSpaceRay(SoRayPickAction *action);
  void computeObjectSpaceRay(SoRayPickAction *action,
                             const SbMatrix &matrix);

  // These methods are called during picking to create details
  // representing extra info about a pick intersection. The default
  // methods implemented in SoShape return NULL. Subclasses can
  // override these methods to set up specific detail instances that
  // contain the extra info. Subclasses can get whatever information
  // they need from the SoPickedPoint, and can set information in it
  // as well.
  virtual SoDetail *createTriangleDetail(SoRayPickAction *action,
                                         const SoPrimitiveVertex *v1,
                                         const SoPrimitiveVertex *v2,
                                         const SoPrimitiveVertex *v3,
                                         SoPickedPoint *pp);
  virtual SoDetail *createLineSegmentDetail(SoRayPickAction *action,
                                            const SoPrimitiveVertex *v1,
                                            const SoPrimitiveVertex *v2,
                                            SoPickedPoint *pp);
  virtual SoDetail *createPointDetail(SoRayPickAction *action,
                                      const SoPrimitiveVertex *v,
                                      SoPickedPoint *pp);
  
  // 
  // This endShape is used by SoIndexedFaceSet and SoFaceSet to create hole 
  // in a face.
  void endShape( int wt, SoMFInt32* indexes );

  virtual ~SoShape();
    
  // Applies GLRender action to the bounding box surrounding the shape.
  // This is used to render shapes when BOUNDING_BOX complexity is on.
  virtual void GLRenderBoundingBox(SoGLRenderAction *action);

  // Fill a matrix with the transformation from Modelling coordinate to tangent space 
  // (facet space).
  void fillOneVtxTangentSpaceMat(const SbVec3f &s, SbVec3f &normal, SbMatrix3 &tgtSpaceMat) const ;

  // Changes the GL_MULTISAMPLE_ARB OpenGL bit value. This method is used to filter the
  // antialiasing when traversing the shape. (See SoFullSceneAntialiasing for more).
  virtual void applyFullSceneAntialiasingFilter(SoState* state);

 protected:
   // below are variables related to vertex arrays
   //typedef std::list< SoAction* > SoApplyingList;
   typedef SbPList SoApplyingList;
   struct MTstruct
   {
     unsigned int *vaIndices;
     float *vaVertex;
     float *vaNormal;
     float *vaTexture;
     unsigned char *vaColor1;
     int *vaColor2;

     int vaIndicesSize;
     int vaVertexSize;
     int vaNormalSize;
     int vaTextureSize;
     int vaColor1Size;
     int vaColor2Size;

     GLUtesselator *tobj;        // Tesselator (for concave polygons)
     SoPrimitiveVertex *polyVerts;        // Array of saved poly vertices
     SoPointDetail     *polyDetails;// Array of poly details
     SoPrimitiveVertex *primVerts;        // Array of saved vertices
     SoPointDetail     *vertDetails;// Array of vertex details
     int numPolyVertsAllocated;        // Size of polyVerts array

     TriangleShape       primShapeType;        // Type of shape generated
     SoFaceDetail        *faceDetail;        // Detail used for each primitive
     int         nestLevel;        // Level of beginShape() nesting
     SoAction    *primAction;        // Action primitives generated for
     SoApplyingList* applyingList;
     int         primVertNum;        // Number of vertices so far
     int         polyVertNum;        // Number of poly vertices so far
     SoShape     *primShape;        // Shape primitives generated for

     jySoPrimitiveVertexPtr *jy_v;
     jySoPrimitiveVertexPtr *jy_v_tmp;
     int jy_v_count;
     int jy_v_count_max;

     jySoDetailPtr *jy_dp;
     jySoDetailPtr *jy_dp_tmp;

     SbBool sendTexCoords;        // TRUE if coords should be sent
     SoMaterialBundle *matlBundle; // Bundle used to send materials
   };
  static int s_keepReset;
  static int s_forceSend;
  static SbBool s_noClip;

  // below are variables related to auto caching
  static int autoCacheMinValue;
  static int autoCacheMaxValue;

  SoMultiPassManager *m_multiPassMgr ;

  // static accessor
  static int getMaxPrimitiveLoop()
  {return s_maxPrimitiveLoop; };

  static int getMinVertexNumForVA()
  { return s_minVertexNumForVA; }

  static int getMinVertexNumForVBO()
  { return s_minVertexNumForVBO; }

  static int getMinVertexNumForVAVBONoCache()
  { return s_minVertexNumForVAVBONoCache; }

  static bool isDesindexingAllowed()
  { return s_allowDesIndexing; }

  static bool isTrisStripAllowedForQuadMesh()
  { return s_useTriangleForQuadMesh; }

  static SbBool isDetailDebugEnabled()
  { return s_detailDebug; }

  static SbThreadRWMutex *getSharedMutex()
  { return s_sharedCacheMutex; }

  static bool isCreaseAngleFixSet()
  { return s_creaseAngleFix; }

private:
  ShapeType m_shapeType;
  SbBool m_TriTranspSort;

  // These are used when rendering or picking a shape whose
  // complexity is set to BOUNDING_BOX. The SoGetBoundingBoxAction
  // is used to compute the bounding box of the shape, and the cube
  // is used as a surrogate object when rendering it.
  static SoGetBoundingBoxAction *bboxAct;
  static SoCube *bboxCube;

  // These methods are used to render primitives generated by
  // subclasses. The userData pointer points to the SoShape instance.
  void GLRenderTriangle(SoGLRenderAction *action,
                        const SoPrimitiveVertex *v1,
                        const SoPrimitiveVertex *v2,
                        const SoPrimitiveVertex *v3);
  void GLRenderLineSegment(SoGLRenderAction *action,
                           const SoPrimitiveVertex *v1,
                           const SoPrimitiveVertex *v2);
  void GLRenderPoint(SoGLRenderAction *action,
                     const SoPrimitiveVertex *v);

  // These methods are used to pick primitives generated by
  // subclasses. The userData pointer points to the SoShape instance.
  void rayPickTriangle(SoRayPickAction *action,
                       const SoPrimitiveVertex *v1,
                       const SoPrimitiveVertex *v2,
                       const SoPrimitiveVertex *v3);
  void rayPickLineSegment(SoRayPickAction *action,
                          const SoPrimitiveVertex *v1,
                          const SoPrimitiveVertex *v2);
  void rayPickPoint(SoRayPickAction *action,
                    const SoPrimitiveVertex *v);

  // Applies rayPick action to the bounding box surrounding the shape.
  // This is used to pick shapes when BOUNDING_BOX complexity is on.
  void rayPickBoundingBox(SoRayPickAction *action);

  // Implements shapeVertex() for one of the three triangle-based types
  void triangleVertex(const SoPrimitiveVertex *v,
                      int vertToReplace);

  // Helper routine that allocate space for concave polygon vertices
  void allocateVerts();

  // Static methods called by the GLU tesselation routines
  static  void CALLBACK beginCB(GLenum primType);
  static void CALLBACK vtxCB(void *vertex);
  static void CALLBACK endCB();
  static void CALLBACK errorCB(GLenum err);
  static void CALLBACK combineCB(GLdouble coords[3], SoPrimitiveVertex *vd[4],
                                 GLfloat wt[4], SoPrimitiveVertex **data);

  // Should we use shared mutex instead of per-instance. (v3.1)
  static int s_useSharedCacheMutex;

  // Shared mutex to protect access to normalCache/vpCache. (v3.1)
  static SbThreadRWMutex *s_sharedCacheMutex;

  static int    s_maxPrimitiveLoop;
  static int    s_minVertexNumForVA;
  static int    s_minVertexNumForVBO;
  static int    s_minVertexNumForVAVBONoCache;
  static bool   s_allowDesIndexing;
  static bool   s_useTriangleForQuadMesh;
  static SbBool s_detailDebug;
  static bool   s_creaseAngleFix;
  static int    s_vertex_array_extensionID;
  static int    s_vertex_buffer_extensionID;
  static int    s_multi_draw_array_extensionID;
  static int    s_primitive_restart_extensionID;
  static int    s_primitive_restartNV_extensionID;
};

inline SbBool 
SoShape::checkShapeHints(SoGLRenderAction *,SbThreadAutoWriteLock *)
{
  return FALSE;
}


#endif /* _SO_SHAPE_ */

