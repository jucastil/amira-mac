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


#ifndef  _SO_SPHERE_
#define  _SO_SPHERE_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSphere
//
//  Simple sphere. By default a sphere has radius 1 and is centered
//  around the origin.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Sphere shape node.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This node represents a sphere. By default, the sphere is centered at the origin
 *   and has a radius of 1. The sphere is transformed by the current cumulative
 *   transformation and is drawn with the current lighting model, drawing style,
 *   material, and geometric complexity.
 *   
 *   A sphere does not have faces or parts. Therefore, the sphere ignores material and
 *   normal bindings, using the first material for the entire sphere and using its
 *   own normals. When a texture is applied to a sphere, the texture covers the
 *   entire surface, wrapping counterclockwise from the back of the sphere. The
 *   texture has a seam at the back on the yz-plane.
 *
 *   OpenGL vertex arrays are used if they are available and if the
 *   environment variable IV_NO_VERTEX_ARRAY is not set.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Sphere {
 *    @TABLE_FILE_FORMAT
 *       @TR radius   @TD 1
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws sphere based on the current coordinates, materials, drawing style, and so
 *        on.
 * 
 *    SoRayPickAction @BR
 *        Intersects the ray with the sphere. No details are created for intersections.
 * 
 *    SoGetBoundingBoxAction @BR
 *        Computes the bounding box that encloses the sphere.
 * 
 *    SoCallbackAction @BR
 *        If any triangle callbacks are registered with the action, they will be invoked
 *        for each successive triangle that approximates the sphere.
 * 
 * 
 * @SEE_ALSO
 *    SoCone,
 *    SoCube,
 *    SoCylinder,
 *    SoFullSceneAntialiasing
 * 
 * 
 */ 

class INVENTOR_API SoSphere : public SoShape {

  SO_NODE_HEADER(SoSphere);

 public:
  // Fields
  /**
   * Radius of sphere. This must be greater than 0.
   * 
   */
  SoSFFloat           radius;

  /**
   * Creates a sphere node with default settings.
   */
  SoSphere();

 SoEXTENDER public:
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        rayPick(SoRayPickAction *action);
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

  virtual ~SoSphere();

 private:
  // render the sphere
  void                GLRenderGeneric(SoGLRenderAction *action,
                                      SbBool sendNormals = TRUE, SbBool doTextures = FALSE);

  // Computes tesselation depth based on current complexity
  int                 computeDepth(SoAction *action);
};

#endif /* _SO_SPHERE_ */


