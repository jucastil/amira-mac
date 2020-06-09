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


#ifndef  _SO_VRMLCOORDINATE_
#define  _SO_VRMLCOORDINATE_

#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLCoordinate
//
//  3-vector coordinate point node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Coordinate node.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   See the VRML97 Specification, below.
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   This node defines a set of 3D coordinates to be used in the @B coord @b field of
 *   vertex-based geometry nodes (such as SoVRMLIndexedFaceSet, SoVRMLIndexedLineSet,
 *   and SoVRMLPointSet). 
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLCoordinate {
 *    @TABLE_FILE_FORMAT
 *       @TR point   @TD []
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoGetBoundingBoxAction,  SoCallbackAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoMFVec3f   @TD   set_point
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFVec3f   @TD   point_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLCoordinate : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLCoordinate);

 public:
  // Fields
  /**
   * Coordinate points.
   * 
   */
  SoMFVec3f           point;

  /**
   * Constructor.
   */
  SoVRMLCoordinate();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        pick(SoPickAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoVRMLCoordinate();
};

#endif /* _SO_VRMLCOORDINATE_ */

