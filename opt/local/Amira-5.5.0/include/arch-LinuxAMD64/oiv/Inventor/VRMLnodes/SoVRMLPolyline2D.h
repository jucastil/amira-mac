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


#ifndef  _SO_VRMLPOLYLINE2D_
#define  _SO_VRMLPOLYLINE2D_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLPolyline2D
//
//  Simple cone, aligned with y-axis. Default has apex point at y = 1,
//  bottom radius 1, and height 2, so that the size is -1 to +1 in all
//  3 dimensions. There are two parts to the cone: the sides and the
//  bottom face (in that order).
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT 2D polyline node.
 * 
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
 *   The SoVRMLPolyline2D node specifies a series of contiguous line segments in
 *   the local 2D coordinate system connecting the specified vertices. The #lineSegments
 *   field specifies the vertices to be connected.
 *
 *   The following figure illustrates the SoVRMLPolyline2D node.
 *
 * @IMAGE Polyline2D.gif 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLPolyline2D {
 *    @TABLE_FILE_FORMAT
 *       @TR lineSegments   @TD []
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoGetBoundingBoxAction,  SoCallbackAction  @BR
 *
 *
 *    @TABLE_EVENT_IN 
 *       @TR   SoMFVec2f  @TD   set_lineSegments
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 *
 *    @TABLE_EVENT_OUT 
 *       @TR   SoMFVec2f  @TD   lineSegments_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 


class INVENTOR_API SoVRMLPolyline2D : public SoVRMLGeometry {

  SO_NODE_HEADER(SoVRMLPolyline2D);

 public:

  // Fields
  /**
   * Specifies the vertices to be connected.
   * 
   */
  SoMFVec2f           lineSegments;
  /**
   * Constructor.
   */
  SoVRMLPolyline2D();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        generatePick(SoRayPickAction *action, SoNode *node);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

  // Computes bounding box of cone
  virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                  SbVec3f &center);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();
 protected:
  // Generates triangles representing a cone
  virtual void        generatePrimitives(SoAction *action);
  virtual ~SoVRMLPolyline2D();

 private:
    private:

  SbVec3f            *array;

  void                setupPoints(SoAction *action);
    
   SbBool nvNotifyEnabled;

  // render function
  void doRendering(SoGLRenderAction *action, const SoShapeStyleElement* shapeStyle);

  static const int AUTO_CACHE_FS_MIN_WITHOUT_VP;

  static const int AUTO_CACHE_FS_MAX;
};

#endif /* _SO_VRMLPOLYLINE2D_ */

