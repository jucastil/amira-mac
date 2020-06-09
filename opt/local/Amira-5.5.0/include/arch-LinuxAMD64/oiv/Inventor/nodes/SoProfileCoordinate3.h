/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thad Beier (MMM yyyy)
** Modified by : Dave Immel (MMM yyyy)
** Modified by : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_PROFILE_COORDINATE_3_
#define  _SO_PROFILE_COORDINATE_3_

#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoProfileCoordinate3
//
//  3-vector profile coordinate node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Rational profile coordinate node.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node defines a set of rational 3D coordinates to be used by subsequent
 *   SoProfile nodes. (These coordinates may be used for any type of profile; they
 *   may be useful in some cases for specifying control points for SoNurbsProfile
 *   nodes.) This node does not produce a visible result during rendering; it simply
 *   replaces the current profile coordinates in the traversal state for subsequent
 *   nodes to use.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ProfileCoordinate3 {
 *    @TABLE_FILE_FORMAT
 *       @TR point   @TD 0 0 1
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
 *        Sets profile coordinates in current traversal state. Sets: SoProfileCoordinateElement
 * 
 * 
 * @SEE_ALSO
 *    SoProfile,
 *    SoProfileCoordinate2
 * 
 * 
 */ 

class INVENTOR_API SoProfileCoordinate3 : public SoNode {

  SO_NODE_HEADER(SoProfileCoordinate3);

 public:
  // Fields
  /**
   * Rational 3D profile coordinate points.
   * 
   */
  SoMFVec3f           point;

  /**
   * Creates a profile coordinate node with default settings.
   */
  SoProfileCoordinate3();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoProfileCoordinate3();
};

#endif /* _SO_PROFILE_COORDINATE_3_ */

