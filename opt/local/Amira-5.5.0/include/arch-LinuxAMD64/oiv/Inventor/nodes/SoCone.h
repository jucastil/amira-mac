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


#ifndef  _SO_CONE_
#define  _SO_CONE_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoShape.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCone
//
//  Simple cone, aligned with y-axis. Default has apex point at y = 1,
//  bottom radius 1, and height 2, so that the size is -1 to +1 in all
//  3 dimensions. There are two parts to the cone: the sides and the
//  bottom face (in that order).
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Cone shape node.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This node represents a simple cone whose central axis is aligned with the
 *   y-axis. By default, the cone is centered at (0,0,0) and has a size of -1 to +1
 *   in all three directions. The cone has a radius of 1 at the bottom and a height
 *   of 2, with its apex at 1. The cone has two parts: the sides and the bottom.
 *   
 *   The cone is transformed by the current cumulative transformation and is drawn
 *   with the current lighting model, drawing style, material, and geometric
 *   complexity.
 *   
 *   If the current material binding is PER_PART or PER_PART_INDEXED, the first
 *   current material is used for the sides of the cone, and the second is used for
 *   the bottom. Otherwise, the first material is used for the entire cone.
 *   
 *   When a texture is applied to a cone, it is applied differently to the sides and
 *   bottom. On the sides, the texture wraps counterclockwise (from above) starting
 *   at the back of the cone. The texture has a vertical seam at the back,
 *   intersecting the yz-plane. For the bottom, a circle is cut out of the texture
 *   square and applied to the cone's base circle. The texture appears right side up
 *   when the top of the cone is tilted away from the camera.
 * 
 *   OpenGL vertex arrays are used if they are available and if the
 *   environment variable IV_NO_VERTEX_ARRAY is not set.
 *
 * @FILE_FORMAT_DEFAULT
 *    Cone {
 *    @TABLE_FILE_FORMAT
 *       @TR parts          @TD ALL
 *       @TR bottomRadius   @TD 1
 *       @TR height         @TD 2
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws cone based on the current coordinates, materials, drawing style, and so
 *        on.
 * 
 *    SoRayPickAction @BR
 *        Intersects the ray with the cone. The part of the cone that was picked is
 *        available from the SoConeDetail.
 * 
 *    SoGetBoundingBoxAction @BR
 *        Computes the bounding box that encloses the cone.
 * 
 *    SoCallbackAction @BR
 *        If any triangle callbacks are registered with the action, they will be invoked
 *        for each successive triangle that approximates the cone.
 * 
 * 
 * @SEE_ALSO
 *    SoConeDetail,
 *    SoCube,
 *    SoCylinder,
 *    SoFullSceneAntialiasing,
 *    SoSphere
 * 
 * 
 */ 

class INVENTOR_API SoCone : public SoShape {

  SO_NODE_HEADER(SoCone);

 public:

   /** Cone parts */
  enum Part {
    /**
     *  The conical part 
     */
    SIDES   = 0x01,
    /**
     *  The bottom circular face 
     */
    BOTTOM  = 0x02,
    /**
     *  All parts 
     */
    ALL     = 0x03
  };

  // Fields
  /**
   * Visible parts of cone.
   */
  SoSFBitMask         parts;
  /**
   * Specifies the radius of the base circle. Value must be greater than 0.0.
   */
  SoSFFloat           bottomRadius;
  /**
   * Specifies the cone's height. Value must be greater than 0.0.
   */
  SoSFFloat           height;

  /**
   * Creates a cone node with default settings.
   */
  SoCone();

  /**
   * Convenience function to turn on a part of the cone.
   */
  void                addPart(SoCone::Part part);
  /**
   * Convenience function to turn off a part of the cone.
   */
  void                removePart(SoCone::Part part);

  /**
   * Convenience function that returns whether a given part is on or off.
   */
  SbBool              hasPart(SoCone::Part part) const;

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        rayPick(SoRayPickAction *action);
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
                                  SbVec3f *&sideNormals) const ;

 protected:
  // Generates triangles representing a cone
  virtual void        generatePrimitives(SoAction *action);

  virtual ~SoCone();

 private:
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

#endif /* _SO_CONE_ */

