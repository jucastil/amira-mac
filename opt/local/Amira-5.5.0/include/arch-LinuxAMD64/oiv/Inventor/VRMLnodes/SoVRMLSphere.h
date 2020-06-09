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


#ifndef  _SO_VRMLSPHERE_
#define  _SO_VRMLSPHERE_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLSphere
//
//  Simple sphere. By default a sphere has radius 1 and is centered
//  around the origin.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Sphere shape node.
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
 *   The SoVRMLSphere node specifies a sphere centered at (0, 0, 0) in the local
 *   coordinate system. The #radius field specifies the radius of the sphere
 *   and must be >= 0.0.
 *   
 *   @IMAGE sphere1.gif 
 *   
 *   When a texture is applied to a sphere, the texture covers the entire surface,
 *   wrapping counterclockwise from the back of the sphere. The texture has a seam at
 *   the back where the YZ plane intersects the sphere. SoVRMLTextureTransform
 *   affects the texture coordinates of the SoVRMLSphere.
 *   
 *   The SoVRMLSphere geometry is considered to be solid and thus requires outside
 *   faces only. When viewed from the inside the results are undefined.
 *
 * @FILE_FORMAT_DEFAULT
 *    SoVRMLSphere {
 *    @TABLE_FILE_FORMAT
 *       @TR radius   @TD 1
 *       @TR solid    @TD TRUE
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

class INVENTOR_API SoVRMLSphere : public SoVRMLGeometry {

  SO_NODE_HEADER(SoVRMLSphere);

 public:
  // Fields
  /**
   * Radius of the sphere.
   * 
   */
  SoSFFloat           radius;
  /**
   * Determines whether the sphere is visible when viewed from 
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
  SoVRMLSphere();

 SoEXTENDER public:
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        generatePick(SoRayPickAction *action, SoNode *node);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

  // Computes bounding box of sphere
  virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                  SbVec3f &center);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  // Generates triangles representing a sphere
  virtual void        generatePrimitives(SoAction *action);

  virtual ~SoVRMLSphere();

 private:
  // These render the sphere
  void                GLRenderGeneric(SoGLRenderAction *action,
                                      SbBool sendNormals, SbBool doTextures);
  void                GLRenderNvertTnone(SoGLRenderAction *action);

  // Computes tesselation depth based on current complexity
  int                 computeDepth(SoAction *action);
};

#endif /* _SO_VRMLSPHERE_ */


