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


#ifndef  _SO_BASE_COLOR_
#define  _SO_BASE_COLOR_

#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>
class SoColorPacker;
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoBaseColor
//
//  Surface base color (of the material) node. This affects the
//  diffuse color of the current material.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node that defines an object's base color.
 * 
 * @ingroup LightNodes
 * 
 * @DESCRIPTION
 *   This node defines the base color (or colors) of subsequent shape nodes in the
 *   scene graph. SoBaseColor sets only the diffuse color(s) of the current material
 *   and has no effect on the material's other attributes.
 * 
 * @FILE_FORMAT_DEFAULT
 *    BaseColor {
 *    @TABLE_FILE_FORMAT
 *       @TR rgb   @TD 0.8 0.8 0.8
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction @BR
 *        Sets the current base color in the state.
 * 
 * 
 * @SEE_ALSO
 *    SoMaterial,
 *    SoPackedColor,
 *    SoVertexProperty
 * 
 * 
 */ 

class INVENTOR_API SoBaseColor : public SoNode {

  SO_NODE_HEADER(SoBaseColor);

 public:
  /**
   * RGB color(s).
   */
  SoMFColor           rgb;

  /**
   * Creates a base color node with default settings.
   */
  SoBaseColor();

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

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SoSFBool override;

 protected:
  virtual ~SoBaseColor();
  SoColorPacker* colorPacker;
};

#endif /* _SO_BASE_COLOR_ */

