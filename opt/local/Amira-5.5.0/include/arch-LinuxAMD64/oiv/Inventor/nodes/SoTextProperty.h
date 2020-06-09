/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Nov 2004)
**=======================================================================*/



#ifndef  _SO_TEXT_PROPERTY_
#define  _SO_TEXT_PROPERTY_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFVec2i32.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFColorRGBA.h>
#include <Inventor/elements/SoTextStyleElement.h>

/**
 * @VSGEXT Text property node.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node specifies properties used for text rendering.
 *
 *   The application can specify text alignment and orientation using the #alignmentH, #alignmentV,
 *   and #orientation fields.  Note that horizontal alignment can also be
 *   specified in some text nodes, for example SoText2 and SoText3, using
 *   the @I justification @i field.  The value in the text node's field is
 *   is used unless that field is explicitly set to INHERIT.  In that the
 *   value from SoTextProperty (if any) is used.
 *
 *   The application can also allow use of font kerning using the #kerning field. Kerning consists
 *   of modifying the spacing between two successive glyphs according to their outlines. For
 *   examples, a "T" and a "y" can be moved closer together as the top of the "y" fits nicely
 *   under the upper right bar of the "T". Kerning depends on the specific font being used.
 *
 *   Different text rendering effects such as underline, strikethrough and background rectangle
 *   can be specified using the #style field.  A color can be specified for each style using
 *   the #styleColors field.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TextProperty {
 *    @TABLE_FILE_FORMAT
 *       @TR aliasingFactor  @TD 1.0
 *       @TR alignmentH   @TD LEFT
 *       @TR alignmentV   @TD BASE
 *       @TR kerning      @TD FALSE
 *       @TR margin       @TD 0.0
 *       @TR orientation  @TD LEFT_TO_RIGHT
 *       @TR textureQualityRange  @TD 150 300
 *       @TR style        @TD NONE
 *       @TR styleColors  @TD (default colors)
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    Sets: SoTextAlignmentHElement, SoTextAlignmentVElement, SoTextOrientationElement,
 *    SoTextKerningElement, SoTextMarginElement
 * 
 * @SEE_ALSO
 *    SoAnnoText3, SoText3, SoText2, SoAsciiText, SoFont
 * 
 * 
 */ 

class INVENTOR_API SoTextProperty : public SoNode {

 SO_NODE_HEADER(SoTextProperty) ;
  
 public:
  /**
   * Text property constructor.
   */
  SoTextProperty();

  /** 
   * Defines the anti-aliasing factor to apply to the textured text rendering.
   * The anti-aliasing applied transfer functions are:
   * if aliasingFactor <= 1.0 => Max( (v + f - 1) / f , 0.0)
   * if aliasingFactor > 1.0 => Min( (v * f) , 1.0)
   */ 
  SoSFFloat aliasingFactor;

  /** Possible horizontal alignment values. */
  enum AlignmentH {
    /**  
     * Left edges of all strings are aligned. (default)
     */
    LEFT = 0x01,

    /**  
     * Horizontal centers of all strings are aligned.
     */
    CENTER = 0x03,

    /**  
     * Right edges of all strings are aligned.
     */
    RIGHT = 0x02
  };

  /** 
   * Indicates horizontal placement and alignment of strings. 
   * Use the #AlignmentH enum. Default value is LEFT. With LEFT alignment, the left
   * edge of the first line is at the (transformed) origin, and all left edges are
   * aligned. RIGHT alignment is similar. CENTER alignment places the center
   * of the first string at the (transformed) origin, with the centers of all
   * remaining strings aligned under it.
   * This field is considered only when the justification field of a text node is set to INHERITED.
   * When orientation is vertical, horizontal alignment is only applied on the first line.
   */
  SoSFEnum alignmentH;

  /** Possible vertical alignment values. */
  enum AlignmentV {
    /**  
     * Top edges of all strings are aligned.
     */
    TOP = 0x01,

    /**  
     * Vertical centers of all strings are aligned.
     */
    HALF = 0x03,

    /** 
     * All strings are aligned on their baseline. (default)
     */
    BASE = 0x04,

    /** 
     * Bottom edges of all strings are aligned.
     */
    BOTTOM = 0x05
  };

  /** 
   * Indicates vertical placement and alignment of strings. 
   * Use the #AlignmentV enum. Default is BASE. With TOP alignment, the top
   * edge of the first line is at the (transformed) origin, and all top edges are
   * aligned. BOTTOM alignment is similar. HALF alignment places the center
   * of the first string at the (transformed) origin, with the centers of all
   * remaining strings aligned under it.
   * When orientation is horizontal, vertical alignment is only applied on the first line.
   */
  SoSFEnum alignmentV;

  /** 
   * Set this field to TRUE to apply kerning on text rendering. For more information about kerning, 
   * refer to the FreeType documentation located at
   * http://www.freetype.org/freetype2/documentation.html
   * Default value is FALSE.
   */
  SoSFBool kerning ;

  /** Possible text orientation values. */
  enum Orientation {
    /** 
     * Text string is left to right oriented. (default)
     */
    LEFT_TO_RIGHT = 0x01,

    /** 
     * Text string is right to left oriented.
     */
    RIGHT_TO_LEFT = 0x02,

    /** 
     * Text string is top to bottom oriented.
     */
    TOP_TO_BOTTOM = 0x03,

    /** 
     * Text string is bottom to top oriented.
     */
    BOTTOM_TO_TOP = 0x04
  };

  /** 
   * Specifies the text rendering orientation. 
   * Use the #Orientation enum.  Default is LEFT_TO_RIGHT.
   */
  SoSFEnum orientation;

  /** 
   * Defines a quality range of values taken into account during textured text
   * texture computation.
   * The size of the generated textures depends on this range, expressed in terms
   * of DPI, and depends on the SoComplexity::value.  Default is 150 to 300.
   * Default range values can be changed using the environment variables
   * OIV_MIN_TEXTURED_FONT_RES and OIV_MAX_TEXTURED_FONT_RES.
   *
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFVec2i32 textureQualityRange;

  /** TextProperty style values. */
  enum Style
  {
    /** No effects. */
    NONE = SoTextStyleElement::NONE,
    /** UNDERLINE */
    UNDERLINE = SoTextStyleElement::UNDERLINE,
    /** STRIKETHROUGH */
    STRIKETHROUGH = SoTextStyleElement::STRIKETHROUGH,
    /** DOUBLE_STRIKETHROUGH */
    DOUBLE_STRIKETHROUGH = SoTextStyleElement::DOUBLE_STRIKETHROUGH,
    /** BACK_FRAME */
    BACK_FRAME = SoTextStyleElement::BACK_FRAME,
    /** BACK_FRAME_LINE */
    BACK_FRAME_LINE = SoTextStyleElement::BACK_FRAME_LINE
  };

  /**
   * Specifies zero or more styles to be applied to text.  
   * Use the #Style enum. Default is NONE.
   *
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFBitMask style;

  /**
   * Index values for setting colors in the #styleColors field.
   */
  enum StyleColor
  {
    /** UNDERLINE_COLOR */
    UNDERLINE_COLOR,
    /** STRIKETHROUGH_COLOR */
    STRIKETHROUGH_COLOR,
    /** DOUBLE_STRIKETHROUGH_COLOR */
    DOUBLE_STRIKETHROUGH_COLOR,
    /** BACK_FRAME_COLOR */
    BACK_FRAME_COLOR,
    /** BACK_FRAME_LINE_COLOR */
    BACK_FRAME_LINE_COLOR,
    /** NUM_EFFECTS_COLORS */
    NUM_EFFECTS_COLORS
  };

  /** 
   * Specifies the color to use for each style. @BR
   * Use the index values defined in the #StyleColor enum, for example:
   * \oivnetdoc
   *   \code
   *   node.styleColors.Set1Value( (int)SoTextProperty.StyleColorType.UNDERLINE_COLOR, new SbColorRGBA(1,0,0,1));
   *   \endcode
   * \else
   *   \code
   *   pNode->styleColors.set1Value( UNDERLINE_COLOR, SbColorRGBA(1,0,0,1) );
   *   \endcode
   * \oivnetdoc
   * Default value is Open Inventor default diffuse color (0.8,0.8,0.8).
   * @FIELD_SINCE_OIV 8.1
   */
  SoMFColorRGBA styleColors;

  /** 
   * Set a margin to apply around the text string for the
   * BACK_FRAME and BACK_FRAME_LINE styles.
   * The margin value is expressed as a percentage of the font size.
   * Default value is 0.0
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFFloat margin;

SoEXTENDER public:
  virtual void  doAction(SoAction *action);
  virtual void  GLRender(SoGLRenderAction *action);
  virtual void  callback(SoCallbackAction *action);
  virtual void  pick(SoPickAction *action);
  virtual void  getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void  getPrimitiveCount(SoGetPrimitiveCountAction *action);

SoINTERNAL public:
  // Init the class
  static void initClass();
  static void exitClass();

protected:
  virtual ~SoTextProperty();
} ;

/*----------------------------------------------------------------------------*/

#endif // _SO_TEXT_PROPERTY_

/**/
