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


#ifndef  _SO_VRMLTRIANGLESET2D_
#define  _SO_VRMLTRIANGLESET2D_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>
#include <Inventor/VRMLnodes/SoVRMLCoordinate.h>
#include <Inventor/nodes/SoVertexProperty.h>

class SoCoordinateElement;
class SoNormalBundle;
class SoState;
class SoNormalCache;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLTriangleSet2D
//
//  Specifies a set of triangles
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT 2D triangle set shape node.
 * 
 * 
 * @ingroup X3D
 * 
 * @DESCRIPTION
 *   See the X3D Specification, below.
 * 
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
 *   The SoVRMLTriangleSet2D node specifies a set of triangles in the local 2D coordinate
 *   system. The vertices field specifies the triangles to be displayed. The number of
 *   vertices provided must be evenly divisible by three. Excess vertices will be ignored.
 *
 *   @IMAGE TriangleSet2D.gif
 *
 *   Textures are applied individually to each face of the SoVRMLTriangleSet2D. On the 
 *   front (+Z) and back (-Z) faces of the SoVRMLTriangleSet2D, when viewed from the
 *   +Z axis, the texture is mapped onto each face with the same orientation as if the
 *   image were displayed normally in 2D. TextureTransform affects the texture coordinates
 *   of the SoVRMLTriangleSet2D node.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLTriangleSet2D {
 *    @TABLE_FILE_FORMAT
 *       @TR vertices   @TD [NULL]
 *       @TR solid      @TD FALSE
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoGetBoundingBoxAction,  SoCallbackAction  @BR
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN       
 *       @TR   SoMFVec2f   @TD   set_vertices
 *       @TR   SoSFNode   @TD   set_metadata      
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFVec2f   @TD   vertices_changed
 *       @TR   SoSFNode   @TD   metadata_changed      
 *    @TABLE_END
 *
 * 
 */ 


class INVENTOR_API SoVRMLTriangleSet2D : public SoVRMLGeometry {

  SO_NODE_HEADER(SoVRMLTriangleSet2D);

 public:

  // Fields
  /**
   * Specifies the vertices.
   * 
   */
  SoMFVec2f           vertices;
  /**
   * If TRUE, only the front faces of the shape are displayed.
   * (The back faces are culled.)
   * If FALSE, both sides are displayed.
   */
  SoSFBool            solid;   
  /**
   * Constructor.
   */
  SoVRMLTriangleSet2D();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        generatePick(SoRayPickAction *action, SoNode *node);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

  // Generates default normals using the given normal bundle. 
  // Returns TRUE.
  virtual SbBool      generateDefaultNormals(SoState *state, SoNormalBundle *nb);

  
  // Computes bounding box of cone
  virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                  SbVec3f &center);

  // Typedef of pointer to method on FaceSet;
  // This will be used to simplify declaration and initialization.
  typedef void ( SoVRMLTriangleSet2D::*PMFS)(SoGLRenderAction *);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  // Returns the current normal cache, or NULL if there is none.
  // This method was protected prior to OIV version 3.0.
  // Normal cache will only exist if the node has been traversed
  // by a render action and Inventor needed to compute normals.
  SoNormalCache       *getNormalCache() const { return normalCache; }

  // Redefines this to invalidate normal cache
  virtual void        notify(SoNotList *list);

 protected:
   // This enum is used to indicate the current material or normal binding
  enum Binding {
    OVERALL, PER_FACE, PER_VERTEX
  };
   // Sets up a cache to hold normals. This assumes the cache depends
  // on only the current coordinates, shape hints, and crease angle.
  void                setNormalCache(SoState *state,
                                     int numNormals, 
                                     const SbVec3f *normals,
                                     const SoNormalBindingElement::Binding binding
                                     );
  // Per-instance mutex to protect access to the vpCache
  SbThreadRWMutex *vpCacheMutex;

  // vpCache stores information from one render to the next about
  // what information needs to be grabbed from the state, etc.
  SoVRMLVertexPropertyCache       vpCache;

  // Generates triangles representing a cone
  virtual void        generatePrimitives(SoAction *action);

  // Overrides standard method to create an SoFaceDetail instance
  virtual SoDetail *  createTriangleDetail(SoRayPickAction *action,
                                           const SoPrimitiveVertex *v1,
                                           const SoPrimitiveVertex *v2,
                                           const SoPrimitiveVertex *v3,
                                           SoPickedPoint *pp);
  virtual ~SoVRMLTriangleSet2D();

 private:

  Binding             getNormalBinding(SoAction *action,
                                       SoNormalBundle *nb);

  // Figures out normals, if necessary.
  SbBool              figureNormals(SoState *state, SoNormalBundle *nb);

  // Set number of triangles/quads/faces, based on coordIndex array.
  void setupTris(SoAction *action);

  // Number of triangles
  int     numTris;

  // render function
  void doRendering(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);

  static const int AUTO_CACHE_FS_MIN_WITHOUT_VP;

  static const int AUTO_CACHE_FS_MAX;

  // This allows instances to cache normals that have been generated
  SoNormalCache       *normalCache;
  SoVRMLCoordinate  *m_array;
  int numVerts; 
};

#endif /* _SO_VRMLTRIANGLESET2D_ */

