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


#ifndef  _SO_PROFILE_COORDINATE_2_
#define  _SO_PROFILE_COORDINATE_2_

#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoProfileCoordinate2
//
//  2-vector profile coordinate node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Profile coordinate node.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node defines a set of 2D coordinates to be used by subsequent SoProfile
 *   nodes. This node does not produce a visible result during rendering; it simply
 *   replaces the current profile coordinates in the traversal state for subsequent
 *   nodes to use.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ProfileCoordinate2 {
 *    @TABLE_FILE_FORMAT
 *       @TR point   @TD 0 0
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
 *    SoProfileCoordinate3
 * 
 * 
 */ 

class INVENTOR_API SoProfileCoordinate2 : public SoNode {

  SO_NODE_HEADER(SoProfileCoordinate2);

 public:
  // Fields
  /**
   * 2D profile coordinate points.
   * 
   */
  SoMFVec2f           point;

  /**
   * Creates a profile coordinate node with default settings.
   */
  SoProfileCoordinate2();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoProfileCoordinate2();
};

#endif /* _SO_PROFILE_COORDINATE_2_ */

