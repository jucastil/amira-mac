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


#ifndef  _SO_VRMLCYLINDER_
#define  _SO_VRMLCYLINDER_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLCylinder
//
//  Simple cylinder, aligned with y-axis. Default size is -1 to +1 in
//  all 3 dimensions, but the radius and height fields can be used to
//  change that. There are essentially three parts to the cylinder:
//  the sides, the top face, and the bottom face (in that order).
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Cylinder shape node.
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
 *   The SoVRMLCylinder node specifies a capped cylinder centered at (0,0,0) in the
 *   local coordinate system and with a central axis oriented along the local Y-axis.
 *   By default, the cylinder is sized at -1 to +1 in all three dimensions. The
 *   #radius field specifies the cylinder's radius and the #height field
 *   specifies the cylinder's height along the central axis. Both #radius and
 *   #height must be greater than 0.0.
 *   
 *   The cylinder has three @I parts @i: the #side, the #top (Y =
 *   +height) and the #bottom (Y = -height). Each part has an associated SFBool
 *   field that indicates whether the part exists (TRUE) or does not exist (FALSE).
 *   If the parts do not exist, they are not considered during collision detection.
 *   
 *   @IMAGE cylinder1.gif 
 *   
 *   When a texture is applied to a cylinder, it is applied differently to the sides,
 *   top, and bottom. On the sides, the texture wraps counterclockwise (from above)
 *   starting at the back of the cylinder. The texture has a vertical seam at the
 *   back, intersecting the YZ plane. For the top and bottom caps, a circle is cut
 *   out of the unit texture square centered at (0, +/- #height, 0) with
 *   dimensions 2*#radius by 2*#radius. The top texture appears right
 *   side up when the top of the cylinder is tilted toward the +Z axis, and the
 *   bottom texture appears right side up when the top of the cylinder is tilted
 *   toward the -Z axis. SoVRMLTextureTransform affects the texture coordinates of
 *   the SoVRMLCylinder.
 *   
 *   The SoVRMLCylinder geometry is considered to be solid and thus requires outside
 *   faces only. When viewed from the inside the results are undefined.
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLCylinder {
 *    @TABLE_FILE_FORMAT
 *       @TR bottom   @TD TRUE
 *       @TR height   @TD 2
 *       @TR radius   @TD 1
 *       @TR side     @TD TRUE
 *       @TR top      @TD TRUE
 *       @TR solid   @TD TRUE
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

class INVENTOR_API SoVRMLCylinder : public SoVRMLGeometry {

  SO_NODE_HEADER(SoVRMLCylinder);

 public:

  // Fields
  /**
   * Specifies the cylinder's height and radius; values must be greater than 0.0.
   * 
   */
  SoSFFloat           radius;
  SoSFFloat           height;
  /**
   * Specifies whether the sides are created.
   * 
   */
  SoSFBool            side;
  /**
   * Specifies whether the top cap is created.
   * 
   */
  SoSFBool            top;
  /**
   * Specifies whether the bottom cap is created.
   * 
   */
  SoSFBool            bottom;
  /**
   * Determines whether the cylinder is visible when viewed from 
   * the inside.
   *
   * @FIELD_SINCE_OIV 5.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when 
   * this node is written to a VRML file, the file will contain
   * this incompatible field and standard VRML97 file readers 
   * will not be able to read it.
   */
  SoSFBool            solid;

  /**
   * Constructor.
   */
  SoVRMLCylinder();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        generatePick(SoRayPickAction *action, SoNode *node);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

  // Computes bounding box of cylinder
  virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                  SbVec3f &center);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SB_THREAD_TLS_HEADER();

  // Modified on 02-25-00: put from private to SoINTERNAL public for the bevel
  // Computes number of sides and sections to use to represent
  // cylinder (based on complexity), then computes ring of x,z
  // coordinates around cylinder and stores in ringCoords.
  void                computeRing(SoAction *action,
                                  int &numSides, int &numSections,
                                  SbVec2f *&ringCoords) const;
 
 protected:
  // Generates triangles representing a cylinder
  virtual void        generatePrimitives(SoAction *action);

  virtual ~SoVRMLCylinder();

 private:
 
  enum Part {                 // VRMLCylinder parts
    SIDES   = 0x01,                 // The tubular part
    TOP     = 0x02,                 // The top circular face
    BOTTOM  = 0x04,                 // The bottom circular face
    ALL     = 0x07                  // All parts
  };

  // Computes number of sides and sections to use, based on complexity
  // and decimation elements.
  void        computeNumSidesSections(SoAction *action, 
                                      int &numSides, int &numSections) const;

  // Computes real radius and half-height
  void                getSize(float &rad, float &hHeight) const;

  // These render the cylinder
  void                GLRenderGeneric(SoGLRenderAction *action,
                                      SbBool sendNormals, SbBool doTextures);
  void                GLRenderNvertTnone(SoGLRenderAction *action);

  // Thread static variables
  struct MTstruct {
    SbVec2f *coordsArray;     // Ring x,z coordinates
    int      maxCoords;       // Current size of coord array
  };
};

#endif /* _SO_VRMLCYLINDER_ */

