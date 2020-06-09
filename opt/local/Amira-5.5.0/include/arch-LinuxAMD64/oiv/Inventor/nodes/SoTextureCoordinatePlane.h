/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thad Beier (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TEXTURE_COORDINATE_PLANE_
#define  _SO_TEXTURE_COORDINATE_PLANE_

#include <Inventor/nodes/SoTextureCoordinateFunction.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureCoordinatePlane
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node that specifies texture coordinates by projection from a plane.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *   This node creates texture coordinates for points on an object's surface by
 *   projecting them onto a plane. The #directionS and #directionT fields
 *   define the plane. The S coordinate is computed as the distance from the
 *   object-space origin along the vector specified in the #directionS field.
 *   The T coordinate is computed similarly, using the #directionT field.
 *   
 *   The length of the direction vector is also taken into account. For example,
 *   assume #directionS is (0.5, 0, 0) and #directionT is (0, 1, 0). The
 *   square defined by the (x, y, z) vertices:
 *   
 *   <PRE>
 *    (-1, -1, 0) (1, -1, 0) (1, 1, 0) (-1, 1, 0)
 *    </PRE>
 *    will be assigned the (s, t) texture coordinates:
 *   
 *   <PRE>
 *    (-2, -1) (2, -1) (2, 1) (-2, 1)
 *    </PRE>
 *    
 * 
 * @FILE_FORMAT_DEFAULT
 *    TextureCoordinatePlane {
 *    @TABLE_FILE_FORMAT
 *       @TR directionS   @TD 1 0 0
 *       @TR directionT   @TD 0 1 0
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoRayPickAction @BR
 *        Sets the current texture function in the state.
 * 
 * 
 * @SEE_ALSO
 *    SoTexture2,
 *    SoTexture2Transform,
 *    SoTextureCoordinateDefault,
 *    SoTextureCoordinateEnvironment
 * 
 * 
 */ 

class INVENTOR_API SoTextureCoordinatePlane : public SoTextureCoordinateFunction {

  SO_NODE_HEADER(SoTextureCoordinatePlane);

 public:
  // Fields
  SoSFVec3f           directionS; // S coordinates projection direction
  /**
   * Directions of projection for S and T coordinates.
   * 
   */
  SoSFVec3f           directionT;

  /**
   * Creates a texture function node with default settings.
   */
  SoTextureCoordinatePlane();

 SoEXTENDER public:
  void                GLRender(SoGLRenderAction *action);
  void                pick(SoPickAction *action);
  void                callback(SoCallbackAction *action);
    
  void                doAction(SoAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoTextureCoordinatePlane();

 private:
  // Callback used internally to project a point:
  static const SbVec4f &valueCallback(void *instance,
                                      const SbVec3f &position, const SbVec3f &);

  // Callback used internally to send GL texgen commands:
  static void doTexgen(void *);
};

#endif /* _SO_TEXTURE_COORDINATE_PLANE_ */

