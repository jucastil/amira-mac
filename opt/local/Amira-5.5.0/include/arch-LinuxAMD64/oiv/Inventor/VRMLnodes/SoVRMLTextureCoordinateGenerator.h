/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : John Rohlf (MMM yyyy)
** Modified by : Thad Beier (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLTEXTURE_COORDINATE_GENERATOR_
#define  _SO_VRMLTEXTURE_COORDINATE_GENERATOR_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLMultiTextureTransform
//
//  VRMLTextureCoordinateGenerator point node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Texture coordinate generator node.\ @NO_ACTION
 * 
 * @ingroup X3D
 * 
 * @DESCRIPTION
 *   See the X3D Specification, below.
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
 *   TextureCoordinateGenerator supports the automatic generation 
 *   of texture coodinates for geometric shapes. 
 *   
 *   This node can be used to set the texture coordinates for a node 
 *   with a #texCoord field.
 *
 *   The #mode field describes the algorithm used to compute texture
 *   coordinates, as shown in the table below.
 *
 *   @TABLE_1B
 *   @TR
 *   @B mode@b
 *   @TD 
 *   @B Description@b
 *   @TR
 *   SPHERE
 *   @TD 
 *   Creates texture coordinates for a spherical environment 
 *   or "chrome" mapping based on the vertex normals transformed 
 *   to camera space. @BR
 *   u = Nx/2 + 0.5 @BR
 *   v = Ny/2 + 0.5 @BR
 *   where u and v are the texture coordinates being computed, 
 *   and Nx and Ny are the x and y components of the camera-space 
 *   vertex normal. If the normal has a positive x component, 
 *   the normal points to the right, and the u coordinate is 
 *   adjusted to address the texture appropriately. Likewise 
 *   for the v coordinate: positive y indicates that the normal 
 *   points up. The opposite is of course true for negative values 
 *   in each component. If the normal points directly at the camera, 
 *   the resulting coordinates should receive no distortion. 
 *   The +0.5 bias to both coordinates places the point of 
 *   zero-distortion at the center of the sphere map, and a vertex 
 *   normal of (0, 0, z) addresses this point. Note that this formula 
 *   doesn't take account for the z component of the normal.
 *   @TR
 *   CAMERASPACENORMAL
 *   @TD 
 *   Use the vertex normal, transformed to camera space, as input 
 *   texture coordinates, resulting coordinates are in -1 to 1 range.
 *   @TR
 *   CAMERASPACEPOSITION
 *   @TD
 *   Use the vertex position, transformed to camera space, as input 
 *   texture coordinates
 *   @TR
 *   CAMERASPACEREFLECTIONVECTOR
 *   @TD
 *   Use the reflection vector, transformed to camera space, as 
 *   input texture coordinates. The reflection vector is computed 
 *   from the input vertex position and normal vector. @BR 
 *   R=2 * DotProd(E,N) * N - E; @BR
 *   In the preceding formula, R is the reflection vector being 
 *   computed, E is the normalized position-to-eye vector, and N 
 *   is the camera-space vertex normal. 
 *   Resulting coordinates are in -1 to 1 range.
 *   @TR
 *   SPHERE-LOCAL
 *   @TD 
 *   Sphere mapping but in local coordinates
 *   @TR
 *   COORD
 *   @TD 
 *   Use vertex coordinates
 *   @TR
 *   COORD-EYE
 *   @TD
 *   Use vertex coordinates transformed to camera space
 *   @TR
 *   NOISE
 *   @TD 
 *   Computed by applying Perlin solid noise function on vertex coordinates, parameter contains scale and translation [scale.x scale.y scale.z translation.x translation.y translation.z]
 *   @TR
 *   NOISE-EYE
 *   @TD 
 *   Same as above but transform vertex coordinates to camera space first
 *   @TR
 *   SPHERE-REFLECT
 *   @TD
 *   Similar to "CAMERASPACEREFLECTIONVECTOR" with optional index of 
 *   refraction, parameter[0] contains index of refraction. @BR 
 *   Resulting coordinates are in -1 to 1 range.
 *   @TR
 *   SPHERE-REFLECT-LOCAL
 *   @TD
 *   Similar to "SPHERE-REFLECT", parameter[0] contains index 
 *   of refraction, parameter[1 to 3] the eye point in local 
 *   coordinates. By animating parameter [1 to 3] the reflection 
 *   changes with respect to the point. @BR 
 *   Resulting coordinates are in -1 to 1 range 
 *   @TABLE_END
 * 
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.

 * 
 * @FILE_FORMAT_DEFAULT
 *    SoVRMLTextureCoordinateGenerator {
 *    @TABLE_FILE_FORMAT
 *       @TR mode      @TD "SPHERE"
 *       @TR parameter @TD []
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoCallbackAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFString   @TD   set_mode
 *       @TR   SoMFFloat    @TD   set_parameter
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFString   @TD   mode_changed
 *       @TR   SoMFFloat    @TD   parameter_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLTextureCoordinateGenerator : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLTextureCoordinateGenerator);

 public:
  // Fields
  /**
   * The algorithm used to compute texture coordinates.
   * See table above for mode values.
   * 
   */
  SoSFString           mode;

  /**
   * Inputs to the generator as needed by the algorithm.
   * See table above for required parameters for the selected
   * #mode.
   * 
   */
  SoMFFloat            parameter;

  /**
   * Constructor.
   */
  SoVRMLTextureCoordinateGenerator();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);
    
 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();
 protected:
  virtual ~SoVRMLTextureCoordinateGenerator();
};

#endif /* _SO_VRMLTEXTURE_COORDINATE_GENERATOR_ */

