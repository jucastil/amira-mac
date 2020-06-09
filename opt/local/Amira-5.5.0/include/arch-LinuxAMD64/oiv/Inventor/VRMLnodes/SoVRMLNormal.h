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


#ifndef  _SO_VRMLNORMAL_
#define  _SO_VRMLNORMAL_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLNormal
//
//  Normal vector node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Node that defines surface normals for shapes.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   This node defines a set of 3D surface normal vectors to be used in the
 *   #vector field of some geometry nodes (SoVRMLIndexedFaceSet,
 *   SoVRMLElevationGrid). This node contains one multiple-valued field that contains
 *   the normal vectors. Normals should be unit-length or results are undefined.
 *   Default normals are generated if none are given.
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
 *   This node defines a set of 3D surface normal vectors to be used in the
 *   #vector field of some geometry nodes (SoVRMLIndexedFaceSet,
 *   SoVRMLElevationGrid). This node contains one multiple-valued field that contains
 *   the normal vectors. Normals should be unit-length or results are undefined. 
 *   
 *   To save network bandwidth, it is expected that implementations will be able to
 *   automatically generate appropriate normals if none are given. However, the
 *   results will vary from implementation to implementation. 
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLNormal {
 *    @TABLE_FILE_FORMAT
 *       @TR vector   @TD []
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoCallbackAction  @BR
 *      Sets: SoNormalElement
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoMFVec3f   @TD   set_vector
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFVec3f   @TD   vector_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLNormal : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLNormal);

 public:
  // Fields
  /**
   * Normal vectors.
   * 
   */
  SoMFVec3f           vector;

  /**
   * Constructor.
   */
  SoVRMLNormal();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);
    
 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoVRMLNormal();
};

#endif /* _SO_VRMLNORMAL_ */

