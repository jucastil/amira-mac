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


#ifndef  _SO_DRAW_STYLE_
#define  _SO_DRAW_STYLE_

#include <Inventor/SbString.h>
#include <Inventor/elements/SoDrawStyleElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDrawStyle
//
//  Draw style node.
//
//////////////////////////////////////////////////////////////////////////////

class SoGLRenderAction;
class SoCallbackAction;

/**
 * Node that defines the style to use when rendering.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node defines the current drawing style for all subsequent shape nodes in a
 *   scene graph. SoDrawStyle specifies how primitives should be rendered. 
 *
 *   The drawing style has no effect on picking or callback primitive generation.
 *   In particular, geometry with style INVISIBLE is not rendered but is still pickable.  
 *   It can be useful to put, for example, an invisible sphere around an assembly to
 *   ensure that it is always picked as a unit.
 *
 *   Style INVISIBLE should generally not be used to "turn off" geometry.  It is more
 *   efficient to put an SoSwitch node above the geometry and all its associated nodes.
 *   Using the Switch's whichChild field to "turn off" geometry avoids traversing any
 *   of the associated nodes.
 * 
 * @FILE_FORMAT_DEFAULT
 *    DrawStyle {
 *    @TABLE_FILE_FORMAT
 *       @TR style                    @TD FILLED
 *       @TR pointSize                @TD 0
 *       @TR lineWidth                @TD 0
 *       @TR linePattern              @TD 0xffff
 *       @TR linePatternScaleFactor   @TD 1
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction @BR
 *        Sets the current drawing style. 
 *        Sets: SoDrawStyleElement, SoPointSizeElement,
 *        SoLineWidthElement, SoLinePatternElement.
 * 
 * @SEE_ALSO
 *    SoLightModel,
 *    SoPickStyle,
 *    SoShapeHints
 * 
 * 
 */ 

class INVENTOR_API SoDrawStyle : public SoNode {

  SO_NODE_HEADER(SoDrawStyle);
  
 public:
   /** Draw styles */
  enum Style {
    /**
     *  Draw filled regions 
     */
    FILLED = SoDrawStyleElement::FILLED,
    /**
     *  Draw only outlines (wireframe) 
     */
    LINES = SoDrawStyleElement::LINES,
    /**
     *  Draw points at vertices 
     */
    POINTS = SoDrawStyleElement::POINTS,
    /**
     *  Do not draw anything at all 
     */
    INVISIBLE = SoDrawStyleElement::INVISIBLE,
    /**
     *  Draw markers
     */
    MARKERS = SoDrawStyleElement::MARKERS
  };

  // Fields
  /**
   * Drawing style.
   * Use enum #Style. Default is FILLED.
   */
  SoSFEnum style;

  /**
   * Radius of points (for POINTS style).
   * Units are printer's points (1 inch = 72.27 printer's points). 
   * Default is 0 (meaning to use default OpenGL value).
   */
  SoSFFloat pointSize;

  /**
   * Width of lines (for LINES style).
   * Units are printer's points (1 inch = 72.27 printer's points). 
   * Values can range from 0.0 to 256.0. The default value is 0.0, 
   * which indicates to use the fastest value for rendering.
   * 
   * Note: Non-antialiased line width may be clamped to an 
   *       implementation-dependent maximum. If so a message will be
   *       displayed specifying the supported range.
   */
  SoSFFloat lineWidth;

  /**
   * Stipple pattern for lines (for LINES style). 
   * This specifies how dashed or dotted lines will be drawn.
   * The pattern is a 16-bit series of 0s and 1s and is repeated
   * as necessary to stipple a given line. A 1 indicates that 
   * drawing occurs, and a 0 that it does not, on a 
   * pixel-by-pixel basis, starting with the low-order bits of the pattern.
   * Values can range from 0 (invisible) to 0xffff (solid). Default is 0xffff.
   *
   * The line pattern can be stretched using the #linePatternScaleFactor field.
   */
  SoSFUShort linePattern;

  /** 
   * Stipple pattern scale factor (for LINES style). It stretches the line pattern
   * (see #linePattern) by multiplying each subseries of consecutive 1s and 0s. 
   * Scale factors are clamped to lie between 1 and 255. Default is 1.
   *
   * @FIELD_SINCE_OIV 4.0
   */
  SoSFInt32 linePatternScaleFactor;

  /**
   * Creates a drawing style node with default settings.
   */
  SoDrawStyle();

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
  virtual ~SoDrawStyle();
};

#endif /* _SO_DRAW_STYLE_ */

