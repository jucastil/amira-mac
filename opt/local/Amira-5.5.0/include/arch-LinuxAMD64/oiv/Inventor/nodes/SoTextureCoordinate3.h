/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Patrick Vigneras (Nov 1999)
**=======================================================================*/

#ifndef  _SO_TEXTURE_COORDINATE_3_
#define  _SO_TEXTURE_COORDINATE_3_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoSFBool.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureCoordinate3
//
//  TextureCoordinate3 point node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT 3D texture coordinate node.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *   This node defines a set of 3D coordinates to be used to map textures to
 *   subsequent vertex-based shapes (those derived from SoVertexShape). It replaces
 *   the current texture coordinates in the rendering state for the shapes to use.
 *   
 *   The current texture coordinate binding (see SoTextureCoordinateBinding)
 *   determines how texture coordinates are mapped to vertices of shapes. An
 *   alternative to using explicit texture coordinates is to generate them using a
 *   function; see SoTextureCoordinateFunction.
 *   
 *   Texture coordinates range from 0 to 1 across the texture. The horizontal
 *   coordinate, called S, is specified first, then the vertical coordinate, T, and
 *   finally the depth coordinate, R.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TextureCoordinate3 {
 *    @TABLE_FILE_FORMAT
 *       @TR point   @TD [ ]
 *       @TR forceSending   @TD FALSE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction @BR
 *        Sets the current texture coordinates in the state.
 *        Sets: SoTextureCoordinate3Element
 * 
 * @SEE_ALSO
 *    SoTexture3,
 *    SoTextureCoordinateBinding,
 *    SoTextureCoordinateFunction,
 *    SoVertexProperty,
 *    SoVertexShape
 * 
 * 
 */ 

class INVENTOR_API SoTextureCoordinate3 : public SoNode {

  SO_NODE_HEADER(SoTextureCoordinate3);

public:
  // Fields
  /**
   * Texture coordinate points.
   * 
   */
  SoMFVec3f           point;

  /**
   * Forces the texture coordinates to be sent to OpenGL
   * even if no texture is bound. Default is FALSE.
   * The default value can be set using the environment variable OIV_FORCE_TEX_COORD_SENDING.
   * See SoPreferences.
   *
   * @FIELD_SINCE_OIV 5.0.3
   */
  SoSFBool            forceSending; 
  
  /**
   * Creates a texture coordinate node with default settings.
   */
  SoTextureCoordinate3();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        pick(SoPickAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

protected:
  virtual ~SoTextureCoordinate3();
};

#endif /* _SO_TEXTURE_COORDINATE_3_ */

