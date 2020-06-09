/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Chris Marrin (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_FONTSTYLE_
#define  _SO_FONTSTYLE_

#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoFont.h>
#include <Inventor/actions/SoCallbackAction.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFontStyle
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Defines font family and style for text.
 * 
 * @ingroup PropertyNodes VRML1
 * 
 * @DESCRIPTION
 *   This node defines the current font family and style for all subsequent text
 *   shapes in the scene graph. The node was implemented to support VRML 1.0. If you
 *   are using VRML 2.0, you should use SoVRMLFontStyle rather than this node. 
 *   
 *   On Windows, the font families are mapped as follows:
 *   
 *      @TABLE_0B
 *         @TR SERIF       @TD Times New Roman
 *         @TR SANS        @TD Arial
 *         @TR TYPEWRITER  @TD Courier New
 *      @TABLE_END 
 * 
 * @FILE_FORMAT_DEFAULT
 *    FontStyle {
 *    @TABLE_FILE_FORMAT
 *       @TR name         @TD "defaultFont"
 *       @TR size         @TD 10
 *       @TR family       @TD SERIF
 *       @TR style        @TD NONE
 *       @TR renderStyle  @TD POLYGON
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
 *        Sets the font family and style in the current traversal state.
 *        Sets: SoFontNameElement, SoFontSizeElement, 
 * 
 * @SEE_ALSO
 *    SoAsciiText,
 *    SoFont,
 *    SoText2,
 *    SoText3
 * 
 * 
 */ 

class INVENTOR_API SoFontStyle : public SoFont {

  SO_NODE_HEADER(SoFontStyle);

 public:
  /**
   * Creates a font style node with default settings.
   */
  SoFontStyle();

  /** Font style family */
  enum Family {
    /**
     *  Use Serif style (such as Times-Roman) 
     */
    SERIF,
    /**
     *  Use Sans Serif style (such as Helvetica) 
     */
    SANS,
    /**
     *  Use fixed pitch style (such as Courier) 
     */
    TYPEWRITER
  };

  enum Style {
    /**
     *  No modification to Family 
     */
    NONE = 0,
    /**
     *  Embolden Family 
     */
    BOLD = 0x1,
    /**
     *  Italicize or slant Family 
     */
    ITALIC = 0x2
  };

  // Fields
  /**
   * Specifies the family of font to use.
   * Use enum #Family.  Default is SERIF.
   */
  SoSFEnum    family;
  /**
   * Specifies style modifications to the chosen font.
   * Use enum #Style. Default is NONE.
   */
  SoSFBitMask style;
    
  /**
   * Returns the font name used by this node based on the settings of family and
   * style.
   */
  SbString            getFontName();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoFontStyle();
    
 private:
  static const char *fontList[][4];
};

#endif /* _SO_FONTSTYLE_ */

