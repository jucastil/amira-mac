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


#ifndef  _SO_PACKED_COLOR_
#define  _SO_PACKED_COLOR_

#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>

class SoColorPacker;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPackedColor
//
//  Surface base color (of material) node. This affects the diffuse
//  color and transparency of the current material. Colors are packed
//  into uint32_ts as 0xaabbggrr. The alpha value is used for
//  transparency.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node that defines base colors using packed representation.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   SoPackedColor is similar to SoBaseColor in that it sets the diffuse color
 *   component of the current material. However, it also changes the transparency
 *   component. The color and transparency information is packed into unsigned 32-bit
 *   integers: 0xrrggbbaa, where aa represents the alpha (0x00 = fully transparent,
 *   0xff = opaque), and rr, gg, and bb represent the red, blue, and green components
 *   of the color, respectively. Note that the order (r,g,b,a) of these components is
 *   reversed from the ordering in releases of Open Inventor prior to 2.1.
 *   
 *   If the transparency type is SoGLRenderAction::SCREEN_DOOR(), only the first
 *   transparency value will be used. With other transparency types, multiple
 *   transparencies will be used.
 *   
 *   SoPackedColor uses less memory than SoBaseColor or SoMaterial to store multiple
 *   color and transparency values. It can be used in cases where space is critical.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PackedColor {
 *    @TABLE_FILE_FORMAT
 *       @TR orderedRGBA   @TD 0xccccccff
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction @BR
 *        Sets the current base (diffuse) color(s) in the state.
 * 
 * 
 * @SEE_ALSO
 *    SoBaseColor,
 *    SoVertexProperty,
 *    SoMaterial
 * 
 * 
 */ 

class INVENTOR_API SoPackedColor : public SoNode {

  SO_NODE_HEADER(SoPackedColor);

 public:
  // Fields
  /**
   * Defines the packed colors.
   * 
   */
  SoMFUInt32          orderedRGBA;

  /**
   * Creates a packed color node with default settings.
   */
  SoPackedColor();

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
  SbBool              isTransparent()
    {return transparent;}

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SoSFBool override;

 protected:
  virtual ~SoPackedColor();
  SoColorPacker *colorPacker; 
    
 private:
  // check for transparency when field changes.
  virtual void        notify(SoNotList *list);
  // store whether transparent or not
  SbBool transparent;
    
};

#endif /* _SO_PACKED_COLOR_ */

