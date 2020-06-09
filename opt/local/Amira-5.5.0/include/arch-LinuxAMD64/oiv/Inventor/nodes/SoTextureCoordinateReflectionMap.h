/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TEXTURE_COORDINATE_REFLECTION_MAP_
#define  _SO_TEXTURE_COORDINATE_REFLECTION_MAP_

#include <Inventor/nodes/SoTextureCoordinateFunction.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureCoordinateReflectionMap
//
//////////////////////////////////////////////////////////////////////////////

/** 
 * Node that specifies texture coordinates matching the
 * vertex's eye-space reflection vector.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 * Generates texture coordinates (s,t,r) matching the
 * vertex's eye-space reflection vector, which is useful for environment mapping without
 * the singularity inherent in sphere mapping.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TextureCoordinateReflectionMap {
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
 *    SoTextureCoordinateDefault,
 *    SoTextureCoordinateEnvironment,
 *    SoTextureCoordinateFunction,
 *    SoTextureCoordinateNormalMap,
 *    SoTextureCoordinatePlane,
 *    SoTextureCubeMap
 * 
 * 
 */ 

class INVENTOR_API SoTextureCoordinateReflectionMap : public SoTextureCoordinateFunction {

  SO_NODE_HEADER(SoTextureCoordinateReflectionMap);

 public:
  // No fields

  /**
   * Creates a texture function node with default settings.
   */
  SoTextureCoordinateReflectionMap();

 SoEXTENDER public:
  void                GLRender(SoGLRenderAction *action);
  void                pick(SoPickAction *action);
  void                callback(SoCallbackAction *action);
    
  void                doAction(SoAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoTextureCoordinateReflectionMap();

 private:
  // Callback used internally to project a point:
  static const SbVec4f &valueCallback(void *instance,
                                      const SbVec3f &point, const SbVec3f &normal);

  // Callback used internally to send GL texgen commands:
  static void doTexgen(void *);
};

#endif /* _SO_TEXTURE_COORDINATE_REFLECTION_MAP_ */

