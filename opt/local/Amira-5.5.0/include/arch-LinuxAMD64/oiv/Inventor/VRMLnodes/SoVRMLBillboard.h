/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM yyyy)
** Modified by : David Beilloin (Nov 2009)
**=======================================================================*/


#ifndef  _SO_VRMLBILLBOARD_
#define  _SO_VRMLBILLBOARD_

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLGroup.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLBillboard
//
//  VRMLGroup group node: state is saved before traversing children
//  and restored afterwards.
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/fields/SoSFBitMask.h>

/**
 * @VSGEXT Grouping node that modifies its coordinate system so that its local Z-axis
 * always points at the viewer.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLBillboard node is a grouping node which modifies its coordinate system
 *   so that the billboard node's local Z-axis turns to point at the viewer. The
 *   SoVRMLBillboard node has children which may be other grouping or leaf nodes. 
 *
 *   Note that the orientation of an SoVRMLBillboard depends on the current
 *   camera settings, so generally this node should not be render cached.
 *   SoVRMLBillboard nodes prohibit auto-caching, so that no SoSeparator (or other render
 *   caching node) above an SoVRMLBillboard in the scene graph will automatically create
 *   a render cache.  This can significantly reduce performance and applications should
 *   try to keep nodes that @I can @i be render cached (especially geometry nodes)
 *   under their own SoSeparator below the SoVRMLBillboard.
 *
 *   This implementation contains one additional field, #useSphereBBox, which is not
 *   part of the X3D / VRML standard.
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming X3D / VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   The SoVRMLBillboard node is a grouping node which modifies its coordinate system
 *   so that the billboard node's local Z-axis turns to point at the viewer. The
 *   SoVRMLBillboard node has children which may be other grouping or leaf nodes.
 *   
 *   The #axisOfRotation field specifies which axis to use to perform the
 *   rotation. This axis is defined in the local coordinates of the SoVRMLBillboard
 *   node. The default (0,1,0) is useful for objects such as images of trees and
 *   lamps positioned on a ground plane. But when an object is oriented at an angle,
 *   for example, on the incline of a mountain, then the #axisOfRotation may
 *   also need to be oriented at a similar angle. 
 *   
 *   A special case of billboarding is @I screen-alignment @i -- the object rotates
 *   to always stay aligned with the viewer even when the viewer elevates, pitches
 *   and rolls. This special case is distinguished by setting the
 *   #axisOfRotation to (0, 0, 0). 
 *   
 *   To rotate the SoVRMLBillboard to face the viewer, determine the line between the
 *   SoVRMLBillboard's origin and the viewer's position; call this the
 *   billboard-to-viewer line. The #axisOfRotation and the billboard-to-viewer
 *   line define a plane. The local z-axis of the SoVRMLBillboard is then rotated
 *   into that plane, pivoting around the #axisOfRotation. 
 *   
 *   If the #axisOfRotation and the billboard-to-viewer line are coincident (the
 *   same line), then the plane cannot be established, and the rotation results of
 *   the SoVRMLBillboard are undefined. For example, if the #axisOfRotation is
 *   set to (0,1,0) (Y-axis) and the viewer flies over the SoVRMLBillboard and peers
 *   directly down the Y-axis the results are undefined@B . @b
 *   
 *   Multiple instances of SoVRMLBillboards (DEF/USE) operate as expected - each
 *   instance rotates in its unique coordinate system to face the viewer.
 *   
 *   See the "Concepts - Grouping and Children Nodes" section for a description the
 *   @B children @b, @B addChildren @b, and @B removeChildren @b fields and
 *   eventIns.
 *   
 *   The #bboxCenter and #bboxSize fields specify a bounding box that
 *   encloses the SoVRMLBillboard's children. This is a hint that may be used for
 *   optimization purposes. If the specified bounding box is smaller than the actual
 *   bounding box of the children at any time, then the results are undefined. A
 *   default #bboxSize value, (-1 -1 -1), implies that the bounding box is not
 *   specified and if needed must be calculated by the browser. See "Concepts -
 *   Bounding Boxes" for a description of #bboxCenter and #bboxSize
 *   fields.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLBillboard {
 *    @TABLE_FILE_FORMAT
 *       @TR axisOfRotation   @TD 0 1 0
 *       @TR children         @TD []
 *       @TR metadata         @TD NULL
 *       @TR bboxCenter       @TD 0 0 0
 *       @TR bboxSize         @TD -1 -1 -1
 *       @TR useSphereBBox    @TD FALSE
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoMFNode   @TD   addChildren      
 *       @TR   SoMFNode   @TD   removeChildren      
 *       @TR   SoSFVec3f   @TD   set_axisOfRotation      
 *       @TR   SoMFNode   @TD   set_children
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFVec3f   @TD   axisOfRotation_changed      
 *       @TR   SoMFNode   @TD   children_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLBillboard : public SoVRMLGroup {

  SO_NODE_HEADER(SoVRMLBillboard);


 public:
  /**
   * Specifies which axis to use to perform the rotation.
   */
  SoSFVec3f axisOfRotation;

  /**
   * Specifies if the bounding box returned by SoVRMLBillBoard::getBoundingBox() method
   * should be extended to completely contain the bounding sphere of the children.
   *
   * This hint avoids bounding box cache breaks due to rotation of the billboard
   * geometry (which changes the default axis aligned bounding box) and provides
   * a significant performance increase when many SoVRMLBillboard nodes are used.
   * 
   * LIMITATIONS: This field is not part of the X3D / VRML standard.  When writing
   * the scene graph to an X3D / VRML format file, be aware that the presence of
   * this field will make the file invalid. By default, that is if the value of the 
   * field is not modified, the field will not be written.
   * 
   * Default is FALSE
   *
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFBool useSphereBBox;

  /**
   * Constructor.
   */
  SoVRMLBillboard();

  // Constructor that takes approximate number of children
  SoVRMLBillboard(int nChildren);

 SoEXTENDER public:
  // Implement actions
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        rayPick(SoRayPickAction *action);

  // These methods make render traversal faster by implementing
  // different rendering paths corresponding to different action
  // path codes.
  virtual void        GLRenderBelowPath(SoGLRenderAction *action);
  virtual void        GLRenderInPath(SoGLRenderAction *action);
  virtual void        GLRenderOffPath(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:

  virtual ~SoVRMLBillboard();

 private:
   // call by constructor
   void commonConstructor(const int nChildren);

   void align(SoState *state, const bool flag=true);
};

#endif /* _SO_VRMLBILLBOARD_ */

