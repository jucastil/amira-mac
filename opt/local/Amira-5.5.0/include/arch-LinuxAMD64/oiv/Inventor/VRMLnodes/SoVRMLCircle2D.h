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


#ifndef  _SO_VRMLCIRCLE2D_
#define  _SO_VRMLCIRCLE2D_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLCircle2D
//
//  Specifies a circular line
//
//////////////////////////////////////////////////////////////////////////////
/**
 * @VSGEXT 2D circle node.
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
 *   The SoVRMLCircle2D node specifies a portion of a circle whose center is at (0,0)
 *   in the local 2D coordinate system. The #radius field specifies the radius of the 
 *   VRMLCircle2D. The value of #radius must be greater than zero. The following 
 *   figure illustrates the SoVRMLCircle2D node with a dashed lineType applied.
 *
 *   @IMAGE Circle2D.gif
 *
 * @FILE_FORMAT_DEFAULT
 *    VRMLCircle2D {
 *    @TABLE_FILE_FORMAT
 *       @TR radius         @TD 1
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

class INVENTOR_API SoVRMLCircle2D : public SoVRMLGeometry {

  SO_NODE_HEADER(SoVRMLCircle2D);

 public:

  // Fields 
  /**
   * Specifies the radius of the arc.
   * Must be greater than 0.0.
   * 
   */
  SoSFFloat           radius;

  /**
   * Constructor.
   */
  SoVRMLCircle2D();

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
  virtual ~SoVRMLCircle2D();

  // Called on notification of field change
  virtual void        notify(SoNotList *list);

 private:
   void setupPoints(SoAction *action);
   void setupSegmentAngle(SoAction *action);
   SbVec3f *array;
   int      num_points;
   float    step_angle;
};

#endif /* _SO_VRMLCIRCLE2D_ */

