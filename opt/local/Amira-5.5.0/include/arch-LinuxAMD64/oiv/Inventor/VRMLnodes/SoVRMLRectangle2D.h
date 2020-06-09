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


#ifndef  _SO_VRMLRECTANGLE2D_
#define  _SO_VRMLRECTANGLE2D_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>
#include <Inventor/threads/SbThread.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLRectangle2D
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Rectangle shape node.
 *
 * 
 *
 * @ingroup X3D
 * 
 * @DESCRIPTION
 *   See the X3D Specification, below.
 * 
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
 *   The SoVRMLRectangle2D node specifies rectangle centered at the (0,0) in the 
 *   local 2D coordinate system and aligned with the local coordinate axes. By default,
 *   the box measures 2 units in each dimension, from -1 to +1. The #size field specifies
 *   the extents of the box along the X-, and Y- axes respectively and each component 
 *   value must be greater than zero.
 *
 *   @IMAGE Rectangle2D.gif
 *
 *   Textures are applied individually to each face of the VRMLRectangle2D. On the front (+Z)
 *   and back (-Z) faces of the VRMLRectangle2D, when viewed from the +Z axis, the 
 *   texture is mapped onto each face with the same orientation as if the image were
 *   displayed normally in 2D. TextureTransform affects the texture coordinates of the 
 *   VRMLRectangle2D node.
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLRectangle2D {
 *    @TABLE_FILE_FORMAT
 *       @TR size       @TD 2 2
 *       @TR solid      @TD FALSE
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


class INVENTOR_API SoVRMLRectangle2D : public SoVRMLGeometry {

  SO_NODE_HEADER(SoVRMLRectangle2D);

 public:

  // Fields
  /**
   * The size field specifies the extents of the box along the 
   * X-, and Y-axes respectively 
   */
  SoSFVec2f           size;
  /**
   * If TRUE, only one side of polygon faces is lit. If FALSE,
   * both sides are lit.
   */
  SoSFBool            solid;
  /**
   * Constructor.
   */
  SoVRMLRectangle2D();

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
  
  SB_THREAD_TLS_HEADER();

 protected:
  // Generates triangles representing a cone
  virtual void        generatePrimitives(SoAction *action);
  virtual ~SoVRMLRectangle2D();

 private:
  static SbVec3f     coords[5];      // Corner coordinates
  static SbVec2f     texCoords[4];   // Face corner texture coordinates
  static const SbVec3f *verts[5]; // Vertex references to coords

    // This flag indicates whether picking is done on a real cube or a
  // cube that is just a bounding box representing another shape. If
  // this flag is TRUE, a pick on the cube should not generate a
  // detail, since the bounding box is not really in the picked path.
  SbBool              pickingBoundingBox;

  // Computes real half-width, -height, -depth
  void                getSize(float &hWidth,
                              float &hHeight,
                              float &hDepth) const;

  // Thread static variables
  struct MTstruct {
    SbBool first;
  };

};

#endif /* _SO_VRMLRECTANGLE2D_ */

