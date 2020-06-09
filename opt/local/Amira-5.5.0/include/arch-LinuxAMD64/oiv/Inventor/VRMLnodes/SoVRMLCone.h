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


#ifndef  _SO_VRMLCONE_
#define  _SO_VRMLCONE_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLCone
//
//  Simple cone, aligned with y-axis. Default has apex point at y = 1,
//  bottom radius 1, and height 2, so that the size is -1 to +1 in all
//  3 dimensions. There are two parts to the cone: the sides and the
//  bottom face (in that order).
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Cone shape node.
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
 *   The SoVRMLCone node specifies a cone which is centered in the local coordinate
 *   system and whose central axis is aligned with the local Y-axis. The
 *   @B bottonRadius @b field specifies the radius of the cone's base, and the
 *   #height field specifies the height of the cone from the center of the base
 *   to the apex. By default, the cone has a radius of 1.0 at the bottom and a height
 *   of 2.0, with its apex at y=1 and its bottom at y=-1. Both #bottomRadius
 *   and #height must be greater than 0.0.
 *   
 *   @IMAGE cone1.gif 
 *   
 *   The #side field specifies whether sides of the cone are created, and the
 *   #bottom field specifies whether the bottom cap of the cone is created. A
 *   value of TRUE specifies that this part of the cone exists, while a value of
 *   FALSE specifies that this part does not exist (not rendered). Parts with field
 *   values of FALSE are not collided with during collision detection.
 *   
 *   When a texture is applied to the sides of the cone, the texture wraps
 *   counterclockwise (from above) starting at the back of the cone. The texture has
 *   a vertical seam at the back in the YZ plane, from the apex (0, #height/2,
 *   0) to the point (0, 0, -r). For the bottom cap, a circle is cut out of the unit
 *   texture square centered at (0, -#height/2, 0) with dimensions (2 *
 *   @B bottomRadius) @b by (2 * @B bottomRadius) @b. The bottom cap texture
 *   appears right side up when the top of the cone is rotated towards the -Z axis.
 *   SoVRMLTextureTransform affects the texture coordinates of the SoVRMLCone.
 *   
 *   The SoVRMLCone geometry is considered to be solid and thus requires outside faces
 *   only. When viewed from the inside the results are undefined.
 *
 * @FILE_FORMAT_DEFAULT
 *    VRMLCone {
 *    @TABLE_FILE_FORMAT
 *       @TR bottomRadius   @TD 1
 *       @TR height         @TD 2
 *       @TR side           @TD TRUE
 *       @TR bottom         @TD TRUE
 *       @TR solid          @TD TRUE
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 *
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 *
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 *
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoGetBoundingBoxAction,  SoCallbackAction  @BR
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLCone : public SoVRMLGeometry {

  SO_NODE_HEADER(SoVRMLCone);

 public:

  // Fields
  /**
   * Specifies the radius of the base circle; value must be
   * greater than 0.0.
   * 
   */
  SoSFFloat           bottomRadius;   // Radius of bottom circular face
  /**
   * Specifies the cone's height; value must be
   * greater than 0.0.
   * 
   */
  SoSFFloat           height;
  /**
   * Specifies whether the sides of the cone are created.
   * 
   */
  SoSFBool            side;
  /**
   * Specifies whether the bottom cap of the cone is created.
   * 
   */
  SoSFBool            bottom;
  /**
   * Determines whether the cone is visible when viewed from 
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
  SoVRMLCone();

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

  // Modified on 02-25-00: put from private to SoINTERNAL public for the bevel
  // Computes number of sides and sections to use to represent
  // cone (based on complexity), then computes ring of x,z
  // coordinates around base of cone and stores in baseCoords. It
  // computes and stores normals in sideNormals, too.
  void                computeBase(SoAction *action,
                                  int &numSides, int &numSections,
                                  SbVec2f *&baseCoords,
                                  SbVec3f *&sideNormals) const;

 protected:
  // Generates triangles representing a cone
  virtual void        generatePrimitives(SoAction *action);
  virtual ~SoVRMLCone();

 private:
 
  enum Part {                 // VRMLCone parts:
    SIDES   = 0x01,                 // The conical part
    BOTTOM  = 0x02,                 // The bottom circular face
    ALL     = 0x03                  // All parts
  };

  // Computes number of sides and sections to use, based on complexity
  // and decimation elements.
  void        computeNumSidesSections(SoAction *action, 
                                      int &numSides, int &numSections) const;
    
  // Computes real radius and half-height
  void                getSize(float &rad, float &hHeight) const;

  // These render the cone
  void                GLRenderGeneric(SoGLRenderAction *action,
                                      SbBool sendNormals, SbBool doTextures);
  void                GLRenderNvertTnone(SoGLRenderAction *action);

  // Computes intersection of ray with infinite canonical cone
  SbBool              intersectInfiniteCone(const SbLine &ray,
                                            SbVec3f &enterPoint,
                                            SbVec3f &exitPoint) const;

  // Thread static variables
  struct MTstruct {
    SbVec2f   *coordsArray;           // Ring x,z coordinates
    SbVec3f   *normalsArray;          // Ring normals
    int       maxCoords;              // Current size of arrays
  };
};

#endif /* _SO_VRMLCONE_ */

