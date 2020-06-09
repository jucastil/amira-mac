/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLDISK2D_
#define  _SO_VRMLDISK2D_


#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLDisk2D
//
//  Specifies a circular disk.
//
//////////////////////////////////////////////////////////////////////////////

class SoNormalBundle;

/**
 * @VSGEXT 2D disk node.
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
 *   The SoVRMLDisk2D node specifies a circular disk which is centered at (0,0) in 
 *   the local coordinate system. The #outerRadius field specifies the radius of the
 *   outer dimension of the SoVRMLDisk2D. The #innerRadius field specifies the inner
 *   dimension of the SoVRMLDisk2D. The value of #outerRadius must be greater than zero. 
 *   The value of #innerRadius must be greater than or equal to zero and less than or equal to #outerRadius.
 *   If #innerRadius is zero, the SoVRMLDisk2D is completely filled. Otherwise, the area
 *   within the #innerRadius forms a hole in the SoVRMLDisk2D. The figure below illustrates
 *   the SoVRMLDisk2D node containing a non-zero #innerRadius.
 *
 *   @IMAGE Disk2D.gif
 *
 * 
 *   Textures are applied individually to each face of the SoVRMLDisk2D. On the front (+Z)
 *   and back (-Z) faces of the SoVRMLDisk2D, when viewed from the +Z axis, the 
 *   texture is mapped onto each face with the same orientation as if the image were
 *   displayed normally in 2D. TextureTransform affects the texture coordinates of the 
 *   SoVRMLDisk2D node.
 *
 * @FILE_FORMAT_DEFAULT
 *    VRMLDisk2D {
 *    @TABLE_FILE_FORMAT
 *       @TR innerRadius         @TD 0
 *       @TR outerRadius         @TD 1
 *       @TR solid               @TD FALSE
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
 * 
 */ 

class INVENTOR_API SoVRMLDisk2D : public SoVRMLGeometry {

  SO_NODE_HEADER(SoVRMLDisk2D);

 public:

  // Fields 
  /**
   * Specifies the outer radius of the disk.
   * Must be greater than 0.0.
   * 
   */
  SoSFFloat           outerRadius;
  /**
   * Specifies the inner radius of the disk.
   * Must be greater or equal to  0.0. If the value of innerRadius is 0.0,
   * the Disk2D is completely filled. Otherwise, the area within the
   * innerRadius forms a hole in the Disk2D.
   * 
   */
  SoSFFloat           innerRadius;
  /**
   * If TRUE, only the front face of the disk is displayed.
   * (The back face is culled.)
   * If FALSE, both sides are displayed.
   */
  SoSFBool            solid;

  /**
   * Creates a VRMLDisk2D with default settings.
   */
  SoVRMLDisk2D();

 SoEXTENDER public:
  // Implement actions
  virtual void        GLRender(SoGLRenderAction *action);
    
  virtual void  getPrimitiveCount(SoGetPrimitiveCountAction *action);
  virtual void        generatePick(SoRayPickAction *action, SoNode *node);
  // Generates default normals using the given normal bundle. 
  // Returns TRUE.
  virtual SbBool      generateDefaultNormals(SoState *state, SoNormalBundle *nb);

  // Computes bounding box of face set
  virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                  SbVec3f &center);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:	 
  // This enum is used to indicate the current material or normal binding
  enum Binding {
    OVERALL, PER_FACE, PER_VERTEX
  };
  // Generates triangles representing faces
  virtual void        generatePrimitives(SoAction *action);

  // Overrides standard method to create an SoFaceDetail instance
  virtual SoDetail *  createTriangleDetail(SoRayPickAction *action,
                                           const SoPrimitiveVertex *v1,
                                           const SoPrimitiveVertex *v2,
                                           const SoPrimitiveVertex *v3,
                                           SoPickedPoint *pp);

  ~SoVRMLDisk2D();

  // Called on notification of field change
  virtual void        notify(SoNotList *list);

 private:

  SbVec3f            *array;
  SbVec2f            *texArray;
  Binding             getNormalBinding(SoAction *action,
                                       SoNormalBundle *nb);

  // Figures out normals, if necessary.
  SbBool              figureNormals(SoState *state, SoNormalBundle *nb);

  void                setupPoints(SoAction *action);
  void                setupSegmentAngle(SoAction *action);
  float               step_angle[2];
    
  int     numFaces, totalVertices;
  int     num_points[2];
    
   SbBool nvNotifyEnabled;

  // render function
  void doRendering(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);

  static const int AUTO_CACHE_FS_MIN_WITHOUT_VP;

  static const int AUTO_CACHE_FS_MAX;
};

#endif /*  _SO_VRMLDISK2D_ */

