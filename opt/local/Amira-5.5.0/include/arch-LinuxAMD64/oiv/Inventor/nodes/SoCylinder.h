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


#ifndef  _SO_CYLINDER_
#define  _SO_CYLINDER_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCylinder
//
//  Simple cylinder, aligned with y-axis. Default size is -1 to +1 in
//  all 3 dimensions, but the radius and height fields can be used to
//  change that. There are essentially three parts to the cylinder:
//  the sides, the top face, and the bottom face (in that order).
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Cylinder shape node.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This node represents a simple capped cylinder centered around the y-axis. By
 *   default, the cylinder is centered at (0,0,0) and has a default size of -1 to +1
 *   in all three dimensions. You can use the #radius and #height fields
 *   to create a cylinder with a different size.
 *   
 *   The cylinder is transformed by the current cumulative transformation and is drawn
 *   with the current lighting model, drawing style, material, and geometric
 *   complexity.
 *   
 *   If the current material binding is PER_PART or PER_PART_INDEXED, the first
 *   current material is used for the sides of the cylinder, the second is used for
 *   the top, and the third is used for the bottom. Otherwise, the first material is
 *   used for the entire cylinder.
 *   
 *   When a texture is applied to a cylinder, it is applied differently to the sides,
 *   top, and bottom. On the sides, the texture wraps counterclockwise (from above)
 *   starting at the back of the cylinder. The texture has a vertical seam at the
 *   back, intersecting the yz-plane. For the top and bottom, a circle is cut out of
 *   the texture square and applied to the top or bottom circle. The top texture
 *   appears right side up when the top of the cylinder is tilted toward the camera,
 *   and the bottom texture appears right side up when the top of the cylinder is
 *   tilted away from the camera.
 *
 *   OpenGL vertex arrays are used if they are available and if the
 *   environment variable IV_NO_VERTEX_ARRAY is not set.
 *
 * @FILE_FORMAT_DEFAULT
 *    Cylinder {
 *    @TABLE_FILE_FORMAT
 *       @TR parts    @TD ALL
 *       @TR radius   @TD 1
 *       @TR height   @TD 2
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws cylinder based on the current coordinates, materials, drawing style, and
 *        so on.
 * 
 *    SoRayPickAction @BR
 *        Intersects the ray with the cylinder. The part of the cylinder that was picked
 *        is available from the SoCylinderDetail.
 * 
 *    SoGetBoundingBoxAction @BR
 *        Computes the bounding box that encloses the cylinder.
 * 
 *    SoCallbackAction @BR
 *        If any triangle callbacks are registered with the action, they will be invoked
 *        for each successive triangle that approximates the cylinder.
 * 
 * 
 * @SEE_ALSO
 *    SoCone,
 *    SoCube,
 *    SoCylinderDetail,
 *    SoFullSceneAntialiasing,
 *    SoSphere
 * 
 * 
 */ 

class INVENTOR_API SoCylinder : public SoShape {

  SO_NODE_HEADER(SoCylinder);

 public:

   /** Cylinder parts */
  enum Part {
    /**
     *  The cylindrical part 
     */
    SIDES   = 0x01,
    /**
     *  The top circular face 
     */
    TOP     = 0x02,
    /**
     *  The bottom circular face 
     */
    BOTTOM  = 0x04,
    /**
     *  All parts 
     */
    ALL     = 0x07
  };

  // Fields
  /**
   * Visible parts of cylinder.
   */
  SoSFBitMask         parts;
  /**
   * Specifies the cylinder's radius. Value must be greater than 0.0.
   */
  SoSFFloat           radius;
  /**
   * Specifies the cylinder's height. Value must be greater than 0.0.
   */
  SoSFFloat           height;

  /**
   * Creates a cylinder node with default settings.
   */
  SoCylinder();

  /**
   * Convenience function to turn on a part of the cylinder.
   */
  void                addPart(SoCylinder::Part part);
  /**
   * Convenience function to turn off a part of the cylinder.
   */
  void                removePart(SoCylinder::Part part);

  /**
   * Convenience function that returns whether a given part is on or off.
   */
  SbBool              hasPart(SoCylinder::Part part) const;

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        rayPick(SoRayPickAction *action);
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
  
  virtual ~SoCylinder();

 private:
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

#endif /* _SO_CYLINDER_ */

