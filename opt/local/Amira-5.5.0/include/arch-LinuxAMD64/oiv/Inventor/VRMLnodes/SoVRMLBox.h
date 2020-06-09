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


#ifndef  _SO_VRMLBOX_
#define  _SO_VRMLBOX_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLBox
//
//  Simple cube. Default size is -1 to +1 in all 3 dimensions, but the
//  width, height, and depth fields can be used to change these.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Box shape node.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   See the VRML97 Specification, below.
 * 
 *   OpenGL vertex arrays are used if they are available and if the
 *   environment variable IV_NO_VERTEX_ARRAY is not set.
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
 *   The SoVRMLBox node specifies a rectangular parallelepiped box in the local
 *   coordinate system centered at (0,0,0) in the local coordinate system and aligned
 *   with the coordinate axes. By default, the box measures 2 units in each
 *   dimension, from -1 to +1. The SoVRMLBox's #size field specifies the
 *   extents of the box along the X, Y, and Z axes respectively and must be greater
 *   than 0.0.
 *   
 *   @IMAGE box1.gif 
 *   
 *   
 *   Textures are applied individually to each face of the box; the entire
 *   untransformed texture goes on each face. On the front, back, right, and left
 *   faces of the box, when viewed from the outside with the Y-axis up, the texture
 *   is mapped onto each face with the same orientation as the if image was displayed
 *   in normally 2D. On the top face of the box, when viewed from the outside along
 *   the +Y axis looking down with the -Z axis as the view up direction, the texture
 *   is mapped onto the face with the same orientation as if the image were displayed
 *   normally in 2D. On the bottom face of the box, when viewed from the outside
 *   along the -Y axis looking up with the +Z axis as the view up direction, the
 *   texture is mapped onto the face with the same orientation as if the image were
 *   displayed normally in 2D. SoVRMLTextureTransform affects the texture coordinates
 *   of the SoVRMLBox.
 *   
 *   The SoVRMLBox geometry is considered to be solid and thus requires outside faces
 *   only. When viewed from the inside the results are undefined.
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLBox {
 *    @TABLE_FILE_FORMAT
 *       @TR size    @TD 2 2 2
 *       @TR solid   @TD TRUE
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoGetBoundingBoxAction,  SoCallbackAction  @BR
 * 
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

class INVENTOR_API SoVRMLBox : public SoVRMLGeometry {

  SO_NODE_HEADER(SoVRMLBox);

 public:
  // Fields
  /**
   * Size of the box.
   */
  SoSFVec3f           size;           // Size
  /**
   * Determines whether the box is visible when viewed from 
   * the inside. 
   *
   * @FIELD_SINCE_OIV 5.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when this node
   * is written to a VRML file, the file will contain this incompatible
   * field and standard VRML97 file readers will not be able to read it.
   */  SoSFBool            solid;
  /**
   * Constructor.
   */
  SoVRMLBox();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        generatePick(SoRayPickAction *action, SoNode *node);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

  // Computes bounding box of cube
  virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                  SbVec3f &center);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SB_THREAD_TLS_HEADER();

 protected:
  // Generates triangles representing a cube
  virtual void        generatePrimitives(SoAction *action);

  // Overrides standard method to create an SoCubeDetail instance
  virtual SoDetail *  createTriangleDetail(SoRayPickAction *action,
                                           const SoPrimitiveVertex *v1,
                                           const SoPrimitiveVertex *v2,
                                           const SoPrimitiveVertex *v3,
                                           SoPickedPoint *pp);

  virtual ~SoVRMLBox();

 private:
  static SbVec3f     coords[8];      // Corner coordinates
  static SbVec2f     texCoords[4];   // Face corner texture coordinates
  static SbVec3f     normals[6];     //Face normals
  static SbVec3f     edgeNormals[12];// Edge normals (for wire-frame)
  static const SbVec3f *verts[6][4]; // Vertex references to coords

  // This flag indicates whether picking is done on a real cube or a
  // cube that is just a bounding box representing another shape. If
  // this flag is TRUE, a pick on the cube should not generate a
  // detail, since the bounding box is not really in the picked path.
  SbBool              pickingBoundingBox;

  // Computes number of divisions per side based on complexity
  int                 computeNumDivisions(SoAction *action) const;

  // Computes real half-width, -height, -depth
  void                getSize(float &hWidth,
                              float &hHeight,
                              float &hDepth) const;

  // These render the box
  void                GLRenderGeneric(SoGLRenderAction *action,
                                      SbBool sendNormals, SbBool doTextures);
  void                GLRenderNvertTnone(SoGLRenderAction *action);

  // Thread static variables
  struct MTstruct {
    SbBool first;
  };

  // SoVRMLGeometry needs to get at the above methods
  friend class SoVRMLGeometry; 
};

#endif /* _SO_VRMLBOX_ */

