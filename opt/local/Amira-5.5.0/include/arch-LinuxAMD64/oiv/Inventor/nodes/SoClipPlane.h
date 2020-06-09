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


#ifndef  _SO_CLIP_PLANE_
#define  _SO_CLIP_PLANE_

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFPlane.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoClipPlane
//
//  Clipping plane node. All subsequent shapes in the scene graph will
//  be clipped to the half-space defined by the "plane" field. The
//  half-space is the side of the plane in the direction of the plane
//  normal. Any number of clipping planes may be active
//  simultaneously, although the graphics library may place a limit on
//  this number during rendering.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Clipping plane node.
 * 
 * @ingroup TransformNodes
 * 
 * @DESCRIPTION
 *   This node clips all subsequent shapes in the scene graph to the half-space
 *   defined by the #plane field. The half-space is the side of the plane in
 *   the direction of the plane normal. For example, if the plane is positioned at
 *   the origin and the normal is pointing down the positive X axis, everything in
 *   the negative X space will be clipped away.
 *   
 *   Any number of clipping planes may be active simultaneously, although the graphics
 *   library may place a limit on this number during rendering.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ClipPlane {
 *    @TABLE_FILE_FORMAT
 *       @TR plane   @TD 1 0 0 0
 *       @TR on      @TD TRUE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoRayPickAction @BR
 *        Adds the plane to the current list of clipping planes in the state.
 *        Sets: SoClipPlaneElement
 * 
 * @SEE_ALSO
 *    SoCamera,
 *    SoShapeHints
 * 
 * 
 */ 

class INVENTOR_API SoClipPlane : public SoNode {

  SO_NODE_HEADER(SoClipPlane);

 public:
  // Fields
  /**
   * Plane defining half-space.
   * 
   */
  SoSFPlane           plane;
  /**
   * Whether clipping plane is active.
   * 
   */
  SoSFBool            on;

  /**
   * Creates a clip plane node with default settings.
   */
  SoClipPlane();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        pick(SoPickAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoClipPlane();
};

#endif /* _SO_CLIP_PLANE_ */

