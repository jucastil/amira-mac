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


#ifndef  _SO_VRMLARC2D_
#define  _SO_VRMLARC2D_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLArc2D
//
//  Specifies a linear circular arc
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT 2D arc node.
 * 
 * @ingroup X3D
 * 
 * @DESCRIPTION
 *   See the X3D Specification, below.
 *  
 * @VRMLX3D_SPECIFICATION
 *   This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the X3D specification that are not
 *   present in this help file. The complete X3D spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   The SoVRMLArc2D node specifies a linear circular arc whose center is at (0,0)
 *   and whose angles are measured starting at the positive x-axis and sweeping towards
 *   the positive y-axis. The #radius field specifies the radius of the circle of
 *   which the arc is a portion. The arc extends from the #startAngle counterclockwise
 *   to the #endAngle. The value of #radius must be greater than zero. The values of 
 *   #startAngle and #endAngle must be in the range (0,2*pi). If #startAngle and
 *   #endAngle have the same value, a circle is specified.
 *   
 *   @IMAGE Arc2DNode.gif
 *   
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLArc2D {
 *    @TABLE_FILE_FORMAT
 *       @TR endAngle       @TD 1.5708
 *       @TR radius         @TD 1
 *       @TR startAngle     @TD 0
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

 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END

 * 
 * 
 */ 

class INVENTOR_API SoVRMLArc2D : public SoVRMLGeometry {

  SO_NODE_HEADER(SoVRMLArc2D);

 public:

  // Fields
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
   * Constructor.
   */
  SoVRMLArc2D();

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
  virtual ~SoVRMLArc2D();

  // Called on notification of field change
  virtual void        notify(SoNotList *list);

 private:
   void setupPoints(SoAction *action);
   void setupSegmentAngle(SoAction *action);
   SbVec3f *array;
   int      num_points;
   float    step_angle;
};

#endif /* _SO_VRMLARC2D_ */

