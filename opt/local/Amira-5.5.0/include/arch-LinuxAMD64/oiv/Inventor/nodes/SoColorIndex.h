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


#ifndef  _SO_COLOR_INDEX_
#define  _SO_COLOR_INDEX_

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoColorIndex
//
//  Surface color node, specified as an index into the current color
//  table. This is used only for BASE_COLOR lighting in color index
//  mode. Since color indices make sense only in the context of GL
//  rendering, this node implements only the GLRender() action method.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Surface color index node.
 * 
 * @ingroup LightNodes
 * 
 * @DESCRIPTION
 *   This node specifies the color to use for subsequent shapes as an index into the
 *   current color table. This is used only for BASE_COLOR lighting (see
 *   SoLightModel) in color index mode. Color index mode may be enabled by the window
 *   in which rendering occurs.
 *   
 *   Since color indices make sense only in the context of OpenGL rendering, this node
 *   implements only a method for the SoGLRenderAction.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ColorIndex {
 *    @TABLE_FILE_FORMAT
 *       @TR index   @TD 1
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Sets the color index for subsequent shapes rendered with BASE_COLOR lighting.
 * 
 * 
 * @SEE_ALSO
 *    SoBaseColor,
 *    SoLightModel
 * 
 * 
 */ 

class INVENTOR_API SoColorIndex : public SoNode {

  SO_NODE_HEADER(SoColorIndex);

 public:
  // Fields
  /**
   * Color index.
   * 
   */
  SoMFInt32           index;

  /**
   * Creates a color index node with default settings.
   */
  SoColorIndex();

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
  virtual void        GLRender(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SoSFBool override;

 protected:
  virtual ~SoColorIndex();
};

#endif /* _SO_COLOR_INDEX_ */

