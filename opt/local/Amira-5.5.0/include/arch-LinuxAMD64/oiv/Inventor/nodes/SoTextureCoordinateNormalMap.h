/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TEXTURE_COORDINATE_NORMAL_MAP_
#define  _SO_TEXTURE_COORDINATE_NORMAL_MAP_

#include <Inventor/nodes/SoTextureCoordinateFunction.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFRotation.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureCoordinateNormalMap
//
//////////////////////////////////////////////////////////////////////////////

/** 
 * Node that specifies texture coordinates matching the vertex's
 * transformed eye-space normal
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 * Generates texture coordinates matching the vertex's
 * transformed eye-space normal, useful for texture-based diffuse lighting models.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TextureCoordinateNormalMap {
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
 *    SoTextureCoordinatePlane,
 *    SoTextureCoordinateReflectionMap,
 *    SoTextureCubeMap
 * 
 * 
 */ 

class INVENTOR_API SoTextureCoordinateNormalMap : public SoTextureCoordinateFunction {

  SO_NODE_HEADER(SoTextureCoordinateNormalMap);

 public:
  // No fields

  /**
   * Creates a texture function node with default settings.
   */
  SoTextureCoordinateNormalMap();

 SoEXTENDER public:
  void                GLRender(SoGLRenderAction *action);
  void                pick(SoPickAction *action);
  void                callback(SoCallbackAction *action);
    
  void                doAction(SoAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoTextureCoordinateNormalMap();

 private:
  // Callback used internally to project a point:
  static const SbVec4f &valueCallback(void *instance,
                                      const SbVec3f &point, const SbVec3f &normal);

  // Callback used internally to send GL texgen commands:
  static void doTexgen(void *);
};

#endif /* _SO_TEXTURE_COORDINATE_NORMAL_MAP_ */

