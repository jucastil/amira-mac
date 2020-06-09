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


#ifndef  _SO_LIGHT_MODEL_
#define  _SO_LIGHT_MODEL_

#include <Inventor/elements/SoLazyElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoLightModel
//
//  Light model node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node that defines the lighting model to use when rendering.
 * 
 * @ingroup LightNodes
 * 
 * @DESCRIPTION
 *   This node defines the lighting model to be used when rendering subsequent
 *   shapes. The lighting model is specified in the #model field. When the
 *   default model (Phong lighting) is used, light sources are required in a scene
 *   for objects to be easily visible.
 * 
 * @FILE_FORMAT_DEFAULT
 *    LightModel {
 *    @TABLE_FILE_FORMAT
 *       @TR model   @TD PHONG
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction @BR
 *        Sets the current lighting model in the state.
 * 
 * 
 * @SEE_ALSO
 *    SoBaseColor,
 *    SoEnvironment,
 *    SoLight,
 *    SoMaterial
 * 
 * 
 */ 

class INVENTOR_API SoLightModel : public SoNode {

  SO_NODE_HEADER(SoLightModel);

 public:
   /** Lighting model */
  enum Model {
    /**
     *  Use only the base (diffuse) object color 
     */
    BASE_COLOR = SoLazyElement::BASE_COLOR,
    /**
     *  Use Phong lighting model 
     */
    PHONG = SoLazyElement::PHONG
  };

  // Fields
  /**
   * Lighting model to use
   * Use enum #Model. Default is PHONG.
   */
  SoSFEnum model;

  /**
   * Creates a light model node with default settings.
   */
  SoLightModel();

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
  virtual void doAction(SoAction *action);
  virtual void GLRender(SoGLRenderAction *action);
  virtual void callback(SoCallbackAction *action);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  SoSFBool override;

 protected:
  virtual ~SoLightModel();
};

#endif /* _SO_LIGHT_MODEL_ */

