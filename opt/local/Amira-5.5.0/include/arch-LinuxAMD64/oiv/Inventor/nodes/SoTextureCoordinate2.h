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


#ifndef  _SO_TEXTURE_COORDINATE_2_
#define  _SO_TEXTURE_COORDINATE_2_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoSFBool.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureCoordinate2
//
//  TextureCoordinate2 point node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * 2D texture coordinate node.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *   This node defines a set of 2D coordinates to be used to map textures
 *   to subsequent vertex-based shapes 
 *   (those derived from SoVertexShape). If you are using multiple textures,
 *   these texture coordinates apply to the current texture unit
 *   (SoTextureUnit).
 *   This node replaces
 *   the current texture coordinates in the rendering state for the shapes to use.
 *   
 *   The current texture coordinate binding (see SoTextureCoordinateBinding)
 *   determines how texture coordinates are mapped to vertices of shapes. An
 *   alternative to using explicit texture coordinates is to generate them using a
 *   function; see SoTextureCoordinateFunction.
 *   
 *   Texture coordinates range from 0 to 1 across the texture. The horizontal
 *   coordinate, called S, is specified first, followed by the vertical coordinate,
 *   T.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TextureCoordinate2 {
 *    @TABLE_FILE_FORMAT
 *       @TR point          @TD [ ]
 *       @TR forceSending   @TD FALSE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction @BR
 *        Sets the current texture coordinates in the state.
 *        Sets: SoTextureCoordinateElement
 * 
 * @SEE_ALSO
 *    SoTexture2,
 *    SoTextureCoordinateBinding,
 *    SoTextureCoordinateFunction,
 *    SoTextureUnit,
 *    SoVertexProperty,
 *    SoVertexShape
 * 
 * 
 */ 

class INVENTOR_API SoTextureCoordinate2 : public SoNode {

  SO_NODE_HEADER(SoTextureCoordinate2);

 public:
  // Fields
  /**
   * Texture coordinate points.
   * 
   */
  SoMFVec2f           point;

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
  SoTextureCoordinate2();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        pick(SoPickAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoTextureCoordinate2();
};

#endif /* _SO_TEXTURE_COORDINATE_2_ */

