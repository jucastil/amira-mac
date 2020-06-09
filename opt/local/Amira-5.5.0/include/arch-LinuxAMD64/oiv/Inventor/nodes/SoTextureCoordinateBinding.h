/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : John Rohlf (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TEXTURE_COORDINATE_BINDING_
#define  _SO_TEXTURE_COORDINATE_BINDING_

#include <Inventor/elements/SoTextureCoordinateBindingElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureCoordinateBinding
//
//  Texture coordinate binding node. This indicates how multiple texture 
//  coordinates are to be distributed over an object.
//
//  If there is a texture function defined, then neither a texture coordinate
//  nor a texture coordinate binding node is needed
//
//  Unlike normal bindings, only a few of the typical bindings make sense:
//  PER_VERTEX, and PER_VERTTEX_INDEXED
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node that specifies how texture coordinates are bound to shapes.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *   This node specifies how the current texture coordinates
 *   are bound to vertex-based shapes that follow in the scene graph.
 *   If you are using multiple textures, note that this binding applies to 
 *   the texture coordinates of the current texture unit (SoTextureUnit).
 *   The DEFAULT binding causes
 *   each shape to define its own default coordinates. These default coordinates
 *   typically cause a texture to be mapped across the whole surface of a shape.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TextureCoordinateBinding {
 *    @TABLE_FILE_FORMAT
 *       @TR value   @TD PER_VERTEX_INDEXED
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction @BR
 *        Sets the current texture coordinate binding type.
 *        Sets: SoTextureCoordinateBindingElement
 * 
 * @SEE_ALSO
 *    SoMaterialBinding,
 *    SoNormalBinding,
 *    SoTexture2,
 *    SoTexture2Transform,
 *    SoTextureCoordinate2,
 *    SoTextureCoordinateFunction,
 *    SoTextureUnit,
 *    SoVertexShape
 * 
 * 
 */ 

class INVENTOR_API SoTextureCoordinateBinding : public SoNode {

  SO_NODE_HEADER(SoTextureCoordinateBinding);

 public:
    
    /** Binding value  */
  enum Binding {
    /**
     *  Current texture coordinates are applied sequentially to vertices of shape 
     */
    PER_VERTEX = SoTextureCoordinateBindingElement::PER_VERTEX,
    /**
     *  Current texture coordinates are indexed per vertex 
     */
    PER_VERTEX_INDEXED = SoTextureCoordinateBindingElement::PER_VERTEX_INDEXED

#ifndef IV_STRICT
    // Obsolete bindings:
    ,                       // Comma to continue list
    DEFAULT = PER_VERTEX_INDEXED
#endif
  };

  // Fields
  /**
   * Specifies how to bind texture coordinates to shapes.
   * Use enum #Binding. Default is PER_VERTEX_INDEXED.
   */
  SoSFEnum value;

  /**
   * Creates a texture coordinate binding node with default settings.
   */
  SoTextureCoordinateBinding();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        pick(SoPickAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoTextureCoordinateBinding();

  // Reads stuff into instance. Upgrades old bindings.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);
};

#endif /* _SO_TEXTURE_COORDINATE_BINDING_ */

