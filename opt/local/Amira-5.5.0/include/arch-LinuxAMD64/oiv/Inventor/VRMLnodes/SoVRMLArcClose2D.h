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


#ifndef  _SO_VRMLARCCLOSE2D_
#define  _SO_VRMLARCCLOSE2D_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>
#include <Inventor/VRMLnodes/SoVRMLCoordinate.h>

class SoNormalBundle;
class SoNormalCache;
/**
 * @VSGEXT 2D closed arc node.
 * 
 * @ingroup X3D
 * 
 * @DESCRIPTION
 *   See the X3D Specification, below.
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
 *   The SoVRMLArcClosed2D node specifies a portion of a circle whose center is at (0,0)
 *   and whose angles are measured starting at the positive x-axis and sweeping towards
 *   the positive y-axis. The end points of the arc specified are connected as defined
 *   by the #closureType field. The #radius field specifies the radius of the circle of
 *   which the arc is a portion. The arc extends from the #startAngle counterclockwise
 *   to the #endAngle. The value of #radius must be greater than zero. The values of
 *   #startAngle and #endAngle must be in the range (0,2*pi). If #startAngle and #endAngle
 *   have the same value, a circle is specified and #closureType is ignored.
 *
 *   A #closureType of "PIE" connects the end point to the start point by defining two
 *   straight line segments first from the end point to the center and then the center
 *   to the start point. This forms a pie wedge as shown below.
 *
 *   @IMAGE ArcClose2DPie.gif 
 *
 *
 *   A closureType of "CHORD" connects the end point to the start point by defining
 *   a straight line segment from the end point to the start point. This forms an 
 *   arc segment as shown below.
 *
 *   @IMAGE ArcClose2DChord.gif
 *
 *
 *   Textures are applied individually to each face of the SoVRMLArcClosed2D. On the
 *   front (+Z) and back (-Z) faces of the SoVRMLArcClosed2D, when viewed from the
 *   +Z axis, the texture is mapped onto each face with the same orientation as if the 
 *   were displayed normally in 2D. TextureTransform affects the texture coordinates of
 *   the SoVRMLArcClosed2D node.
 *  
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLArcClosed2D {
 *    @TABLE_FILE_FORMAT
 *       @TR closureType    @TD "PIE"
 *       @TR endAngle       @TD 1.5708
 *       @TR radius         @TD 1
 *       @TR startAngle     @TD 0
 *       @TR solid          @TD FALSE
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoGetBoundingBoxAction,  SoCallbackAction  @BR
 *
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 *
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 */ 

class INVENTOR_API SoVRMLArcClose2D : public SoVRMLGeometry {

  SO_NODE_HEADER(SoVRMLArcClose2D);

 public:

  // Fields
  /**
   * Specifies the closure type of the arc.
   * 
   */
  SoSFString          closureType;
  /**
   * Specifies the end angle of the arc.
   * 
   */
  SoSFFloat           endAngle;
  /**
   * Specifies the radius of the arc.
   * Must be greater than 0.0.
   * 
   */
  SoSFFloat           radius;
  /**
   * Specifies the start angle of the arc.
   * 
   */
  SoSFFloat           startAngle;
  /**
   * If TRUE, only the front face of the shape is displayed.
   * (The back face is culled.)
   * If FALSE, both sides are displayed.
   */
  SoSFBool            solid;

  /**
   * Constructor.
   */
  SoVRMLArcClose2D();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        generatePick(SoRayPickAction *action, SoNode *node);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

  // Generates default normals using the given normal bundle.
  // Returns TRUE.
  virtual SbBool      generateDefaultNormals(SoState *state,
                                             SoNormalBundle *nb);

  // Computes bounding box of cone
  virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                  SbVec3f &center);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

    // Redefines this to invalidate normal cache
  virtual void        notify(SoNotList *list);

 protected:
  // This enum is used to indicate the current material or normal binding
  enum Binding {
    OVERALL, PER_FACE, PER_VERTEX
  };
  // Generates triangles representing a cone
  virtual void        generatePrimitives(SoAction *action);
  virtual ~SoVRMLArcClose2D();

  static const int AUTO_CACHE_MIN_WITHOUT_VP;
  static const int AUTO_CACHE_MAX;

  // vpCache stores information from one render to the next about
  // what information needs to be grabbed from the state, etc.
  SoVRMLVertexPropertyCache   vpCache;

  // Sets up a cache to hold normals. This assumes the cache depends
  // on only the current coordinates, shape hints, and crease angle.
  void  setNormalCache(SoState *state,
    int numNormals, 
    const SbVec3f *normals,
    const SoNormalBindingElement::Binding binding
    );

  // Returns the current normal cache, or NULL if there is none
  SoNormalCache *getNormalCache() const { return normalCache; }

  // Per-instance mutex to protect access to the vpCache
  SbThreadRWMutex *vpCacheMutex;

 private:

  Binding             getNormalBinding(SoAction *action,
                                       SoNormalBundle *nb);
    
 // render function
  void doRendering(SoGLRenderAction *action,
  const SoShapeStyleElement* shapeStyle);
  SoNormalCache *normalCache;

  // Figures out normals, if necessary. Returns TRUE if normals were
  // generated
  SbBool figureNormals(SoState *state, SoNormalBundle *nb);

   void setupPoints(SoAction *action);
   void setupSegmentAngle(SoAction *action);
   SoVRMLCoordinate* m_array;

   int num_points;
   float    step_angle;
};

#endif /* _SO_VRMLARCCLOSE2D_ */

