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


#ifndef  _SO_TEXTURE_COORDINATE_ENVIRONMENT_
#define  _SO_TEXTURE_COORDINATE_ENVIRONMENT_

#include <Inventor/nodes/SoTextureCoordinateFunction.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureCoordinateEnvironment
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node that specifies texture coordinates by projection from an environment.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *   This node creates texture coordinates by projecting points on an object's
 *   surface to the interior of a surrounding sphere, along the reflection across the
 *   surface normal of the vector from the camera point to the surface. If the
 *   current texture image represents a spherical reflection map of the current
 *   surrounding environment, subsequent shapes will appear to reflect that
 *   environment.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TextureCoordinateEnvironment {
 *    @TABLE_FILE_FORMAT
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
 *    SoTextureCoordinatePlane
 * 
 * 
 */ 

class INVENTOR_API SoTextureCoordinateEnvironment : public SoTextureCoordinateFunction {

  SO_NODE_HEADER(SoTextureCoordinateEnvironment);

 public:
  // No fields

  /**
   * Creates a texture function node with default settings.
   */
  SoTextureCoordinateEnvironment();

 SoEXTENDER public:
  void                GLRender(SoGLRenderAction *action);
  void                pick(SoPickAction *action);
  void                callback(SoCallbackAction *action);
    
  void                doAction(SoAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoTextureCoordinateEnvironment();

 private:
  // Callback used internally to project a point:
  static const SbVec4f &valueCallback(void *instance,
                                      const SbVec3f &point, const SbVec3f &normal);

  // Callback used internally to send GL texgen commands:
  static void doTexgen(void *);
};

#endif /* _SO_TEXTURE_COORDINATE_ENVIRONMENT_ */

