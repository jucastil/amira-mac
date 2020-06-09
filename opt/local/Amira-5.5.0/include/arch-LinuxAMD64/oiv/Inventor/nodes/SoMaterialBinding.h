/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_MATERIAL_BINDING_
#define  _SO_MATERIAL_BINDING_

#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoMaterialBinding
//
//  Material binding node. This indicates how multiple materials are
//  to be distributed over an object.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node that specifies how multiple materials are bound to shapes.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node specifies how the current materials are bound to shapes that follow in
 *   the scene graph. Each shape node may interpret bindings differently. The current
 *   material always has a base value, which is defined by the first value of all
 *   material fields. Since material fields may have multiple values, the binding
 *   determines how these values are distributed over a shape.
 *   
 *   The bindings for faces and vertices are meaningful only for shapes that are made
 *   from faces and vertices. Similarly, the indexed bindings are only used by the
 *   shapes that allow indexing.
 *   
 *   The bindings apply only to diffuse colors and transparency. Other materials
 *   (emissive, specular, ambient, shininess) will have the first value applied to
 *   the entire shape, regardless of the material binding or the number provided.
 *   
 *   If the number of transparencies is less than the number of diffuse colors, only
 *   the first transparency value will be used, regardless of the material binding.
 *   If the number of diffuse colors in the state is less than the number required
 *   for the given binding, a debug warning will be printed and unpredictable colors
 *   will result.
 * 
 * @FILE_FORMAT_DEFAULT
 *    MaterialBinding {
 *    @TABLE_FILE_FORMAT
 *       @TR value   @TD OVERALL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction @BR
 *        Sets the current material binding type.
 *        Sets: SoMaterialBindingElement
 * 
 * @SEE_ALSO
 *    SoMaterial,
 *    SoNormalBinding,
 *    SoShape,
 *    SoVertexProperty,
 *    SoTextureCoordinateBinding
 * 
 * 
 */ 

class INVENTOR_API SoMaterialBinding : public SoNode {

  SO_NODE_HEADER(SoMaterialBinding);

 public:
  enum Binding {
    /**
     *  Whole object has same material 
     */
    OVERALL           = SoMaterialBindingElement::OVERALL,
    /**
     *  One material for each part of object 
     */
    PER_PART          = SoMaterialBindingElement::PER_PART,
    /**
     *  One material for each part, indexed 
     */
    PER_PART_INDEXED  = SoMaterialBindingElement::PER_PART_INDEXED,
    /**
     *  One material for each face of object 
     */
    PER_FACE          = SoMaterialBindingElement::PER_FACE,
    /**
     *  One material for each face, indexed 
     */
    PER_FACE_INDEXED  = SoMaterialBindingElement::PER_FACE_INDEXED,
    /**
     *  One material for each vertex of object 
     */
    PER_VERTEX        = SoMaterialBindingElement::PER_VERTEX,
    /**
     *  One material for each vertex, indexed 
     */
    PER_VERTEX_INDEXED= SoMaterialBindingElement::PER_VERTEX_INDEXED

#ifndef IV_STRICT
    // Obsolete bindings:
    ,  // Comma to continue list
    DEFAULT = OVERALL,
    NONE = OVERALL
#endif
  };

  // Fields
  /**
   * Specifies how to bind materials to shapes.
   * Use enum #Binding. Default is OVERALL.
   */
  SoSFEnum value;

  /**
   * Creates a material binding node with default settings.
   */
  SoMaterialBinding();

  /**
   * Set the state of the override field.
   * see SoNode::setOverride doc.
   */
  inline virtual void setOverride(const SbBool state)
  { override.setValue(state); }

  /**
   * Returns the state of the override field.
   */
  inline virtual SbBool isOverride() const
  { return override.getValue(); }

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  SoSFBool override;

 protected:
  virtual ~SoMaterialBinding();

  // Reads stuff into instance. Upgrades old bindings.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);
};

#endif /* _SO_MATERIAL_BINDING_ */

