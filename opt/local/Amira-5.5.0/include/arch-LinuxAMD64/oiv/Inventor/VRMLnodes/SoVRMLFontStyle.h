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


#ifndef  _SO_VRMLFONTSTYLE_
#define  _SO_VRMLFONTSTYLE_

#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLFontStyle
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Specifies font size, family, style, etc.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLFontStyle node defines the size, font family, and style of text's
 *   font, as well as the direction of the text strings and any specific language
 *   rendering techniques that must be used for non-English text. See SoVRMLText node
 *   for application of SoVRMLFontStyle. 
 *   
 *   The #size field specifies the height (in object space units) of glyphs
 *   rendered and determines the spacing of adjacent lines of text. All subsequent
 *   strings advance in Y by -(#size * #spacing). Only horizontal text is
 *   supported in this release.
 *   
 *   Font attributes are defined with the family and style fields.
 *   
 *   The #family field specifies a case-sensitive MFString value that may be
 *   "SERIF" (the default) for a serif font such as Times Roman; "SANS" for a
 *   sans-serif font such as Helvetica; or "TYPEWRITER" for a fixed-pitch font such
 *   as Courier. A #family value of empty quotes, "", is identical to
 *   "SERIF".
 *   
 *   The #style field specifies a case-sensitive SFString value that may be
 *   "PLAIN" (the default) for default plain type; "BOLD" for boldface type; "ITALIC"
 *   for italic type; or "BOLDITALIC" for bold and italic type. A #style value
 *   of empty quotes, "", is identical to "PLAIN".
 *   
 *   The #horizontal, #leftToRight, and #topToBottom fields indicate
 *   the direction of the text. NOTE: Only horizontal text drawn #leftToRight
 *   is supported in this release. Characters on each line of text advance in the
 *   positive X direction according to their natural advance width. Then each line of
 *   characters is advanced in the negative Y direction.
 *   
 *   The #justify field determines alignment of the above text layout relative
 *   to the origin of the object coordinate system. It is an MFString which can
 *   contain 2 values. The first value specifies alignment along the major axis and
 *   the second value specifies alignment along the minor axis. NOTE: Only the major
 *   axis alignment is supported in this release. A #justify value of "" is
 *   equivalent to the default values. 
 *   
 *   The major alignment is along the X axis. The possible values for each enumerant
 *   of the #justify field are "BEGIN", "MIDDLE", and "END. Each line of text
 *   is positioned individually according to the alignment enumerant. 
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   The SoVRMLFontStyle node defines the size, font family, and style of text's font,
 *   as well as the direction of the text strings and any specific language rendering
 *   techniques that must be used for non-English text. See SoVRMLText node for
 *   application of SoVRMLFontStyle. 
 *   
 *   The #size field specifies the height (in object space units) of glyphs
 *   rendered and determines the spacing of adjacent lines of text. All subsequent
 *   strings advance in either X or Y by -(#size * #spacing).
 *   
 *   Font Family and Style
 *   
 *   Font attributes are defined with the family and style fields. It is up to the
 *   browser to assign specific fonts to the various attribute combinations. 
 *   
 *   The #family field specifies a case-sensitve MFString value that may be
 *   "SERIF" (the default) for a serif font such as Times Roman; "SANS" for a
 *   sans-serif font such as Helvetica; or "TYPEWRITER" for a fixed-pitch font such
 *   as Courier. A #family value of empty quotes, "", is identical to
 *   "SERIF".
 *   
 *   The #style field specifies a case-sensitive SFString value that may be
 *   "PLAIN" (the default) for default plain type; "BOLD" for boldface type; "ITALIC"
 *   for italic type; or "BOLDITALIC" for bold and italic type. A #style value
 *   of empty quotes, "", is identical to "PLAIN".
 *   
 *   Direction, Justification and Spacing
 *   
 *   The #horizontal, #leftToRight, and #topToBottom fields indicate
 *   the direction of the text. The #horizontal field indicates whether the
 *   text advances horizontally in its major direction (#horizontal = TRUE, the
 *   default) or vertically in its major direction (#horizontal = FALSE). The
 *   #leftToRight and #topToBottom fields indicate direction of text
 *   advance in the major (characters within a single string) and minor (successive
 *   strings) axes of layout. Which field is used for the major direction and which
 *   is used for the minor direction is determined by the #horizontal field.
 *   
 *   For horizontal text (#horizontal = TRUE), characters on each line of text
 *   advance in the positive X direction if #leftToRight is TRUE or in the
 *   negative X direction if #leftToRight is FALSE. Characters are advanced
 *   according to their natural advance width. Then each line of characters is
 *   advanced in the negative Y direction if #topToBottom is TRUE or in the
 *   positive Y direction if #topToBottom is FALSE. Lines are advanced by the
 *   amount of #size * #spacing.
 *   
 *   For vertical text (#horizontal = FALSE), characters on each line of text
 *   advance in the negative Y direction if #topToBottom is TRUE or in the
 *   positive Y direction if #topToBottom is FALSE. Characters are advanced
 *   according to their natural advance height. Then each line of characters is
 *   advanced in the positive X direction if #leftToRight is TRUE or in the
 *   negative X direction if #leftToRight is FALSE. Lines are advanced by the
 *   amount of #size * #spacing.
 *   
 *   The #justify field determines alignment of the above text layout relative
 *   to the origin of the object coordinate system. It is an MFString which can
 *   contain 2 values. The first value specifies alignment along the major axis and
 *   the second value specifies alignment along the minor axis, as determined by the
 *   #horizontal field. A #justify value of "" is equivalent to the
 *   default values. If the second string, minor alignment, is not specified then it
 *   defaults to the value "FIRST". Thus, #justify values of "", "BEGIN" and
 *   "BEGIN FIRST" are equivalent.
 *   
 *   The major alignment is along the X axis when #horizontal is TRUE and along
 *   the Y axis when #horizontal is FALSE. The minor alignment is along the Y
 *   axis when #horizontal is TRUE and along the X axis when #horizontal
 *   is FALSE. The possible values for each enumerant of the #justify field are
 *   "FIRST", "BEGIN", "MIDDLE", and "END". For major alignment, each line of text is
 *   positioned individually according to the major alignment enumerant. For minor
 *   alignment, the block of text representing all lines together is positioned
 *   according to the minor alignment enumerant. The following tables describe the
 *   behavior in terms of which portion of the text is at the origin:
 *   
 *   Major Alignment, @I horizontal @i = TRUE:
 *   
 *      @TABLE_0B
 *         @TR @B Enumerant @b  @TD #leftToRight @B  = TRUE @b  @TD #leftToRight @B  = FALSE @b
 *         @TR FIRST            @TD Left edge of each line           @TD Right edge of each line
 *         @TR BEGIN            @TD Left edge of each line           @TD Right edge of each line
 *         @TR MIDDLE           @TD Centered about X-axis            @TD Centered about X-axis
 *         @TR END              @TD Right edge of each line          @TD Left edge of each line
 *      @TABLE_END 
 *   
 *   Major Alignment, @I horizontal @i = FALSE:
 *   
 *      @TABLE_0B
 *         @TR @B Enumerant @b  @TD #topToBottom @B  = TRUE @b  @TD #topToBottom @B  = FALSE @b
 *         @TR FIRST            @TD Top edge of each line            @TD Bottom edge of each line
 *         @TR BEGIN            @TD Top edge of each line            @TD Bottom edge of each line
 *         @TR MIDDLE           @TD Centered about Y-axis            @TD Center about Y-axis
 *         @TR END              @TD Bottom edge of each line         @TD Top edge of each line
 *      @TABLE_END 
 *   
 *   Minor Alignment, @I horizontal @i = TRUE:
 *   
 *      @TABLE_0B
 *         @TR @B Enumerant @b  @TD #topToBottom @B  = TRUE @b  @TD #topToBottom @B  = FALSE @b
 *         @TR FIRST            @TD Baseline of first line           @TD Baseline of first line
 *         @TR BEGIN            @TD Top edge of first line           @TD Bottom edge of first line
 *         @TR MIDDLE           @TD Centered about Y-axis            @TD Centered about Y-axis
 *         @TR END              @TD Bottom edge of last line         @TD Top edge of last line
 *      @TABLE_END 
 *   
 *   Minor Alignment, @I horizontal @i = FALSE:
 *   
 *      @TABLE_0B
 *         @TR @B Enumerant @b  @TD #leftToRight @B  = TRUE @b  @TD #leftToRight @B  = FALSE @b
 *         @TR FIRST            @TD Left edge of first line          @TD Right edge of first line
 *         @TR BEGIN            @TD Left edge of first line          @TD Right edge of first line
 *         @TR MIDDLE           @TD Centered about X-axis            @TD Centered about X-axis
 *         @TR END              @TD Right edge of last line          @TD Left edge of last line
 *      @TABLE_END 
 *   
 *   The default minor alignment is "FIRST". This is a special case of minor alignment
 *   when #horizontal is TRUE. Text starts at the baseline at the Y-axis. In
 *   all other cases, :"FIRST" is identical to "BEGIN". In the following tables, each
 *   small cross indicates where the X and Y axes should be in relation to the text:
 *   
 *   horizontal = TRUE: 
 *   
 *   @IMAGE horizontal.gif 
 *   
 *   horizontal = FALSE: 
 *   
 *   @IMAGE vertical1.gif 
 *   
 *   The #language field specifies the context of the language for the text
 *   string. Due to the multilingual nature of the ISO 10646-1:1993, the
 *   #language field is needed to provide a proper language attribute of the
 *   text string. The format is based on the POSIX locale specification as well as
 *   the RFC 1766: language[_territory]. The values for the language tag is based on
 *   the ISO 639, i.e., zh for Chinese, jp for Japanese, sc for Swedish. The territory
 *   tag is based on the ISO 3166 country code, i.e., TW is for Taiwan and CN for
 *   China for the "zh" Chinese language tag. If the #language field is set to
 *   empty "", then local language bindings are used.
 *   
 *   Please refer to these sites for more details: 
 *   
 *   <PRE>
 *    http://userpage.chemie.fu-berlin.de/diverse/doc/ISO_639.html 
 *    http://userpage.chemie.fu-berlin.de/diverse/doc/ISO_3166.html 
 *   </PRE>
 *    
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLFontStyle {
 *    @TABLE_FILE_FORMAT
 *       @TR family        @TD "SERIF"
 *       @TR horizontal    @TD TRUE
 *       @TR justify       @TD "BEGIN"
 *       @TR language      @TD ""
 *       @TR leftToRight   @TD TRUE
 *       @TR size          @TD 1.0
 *       @TR spacing       @TD 1.0
 *       @TR style         @TD "PLAIN"
 *       @TR topToBottom   @TD TRUE
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoGetBoundingBoxAction,  SoCallbackAction  @BR
 *        Sets: SoFontNameElement, SoFontSizeElement, 
 *
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 *
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLFontStyle : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLFontStyle);

 public:
  /**
   * Constructor.
   */
  SoVRMLFontStyle();
 
    /** Family */
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
 
    /** Style */
  enum Style {
    /**
     *  No modification to Family 
     */
    PLAIN = 0,
    /**
     *  Embolden Family 
     */
    BOLD = 0x1,
    /**
     *  Italicize or Slant Family 
     */
    ITALIC = 0x2,
    /**
     *  Embolden and Italicize Family 
     */
    BOLDITALIC = 0x3
  };

  /**
   * Specifies the height of glyphs rendered and helps determine the spacing of
   * adjacent lines.
   * 
   */
  SoSFFloat size;
  /**
   * Specifies the family of font to use. NOTE: Although it is possible to specify
   * multiple font families, only the first font family is used.
   * 
   */
  SoMFString family;
  /**
   * Defines style modification to the chosen font (bold, italic, etc.).
   * 
   */
  SoSFString style;
  /**
   * Characters advance in the X direction if TRUE. This release supports TRUE
   * only.
   * 
   */
  SoSFBool horizontal;
  /**
   * Characters advance in the positive X direction if TRUE. This release supports
   * TRUE only.
   * 
   */
  SoSFBool leftToRight;
  /**
   *  @NI  Default value of FALSE is used.
   * 
   */
  SoSFBool topToBottom;
  /**
   *  @NI Language-specific rendering techniques used for non-English
   *  text.
   * 
   */
  SoSFString language;
  /**
   * Indicates placement and alignment of strings. With LEFT justification, the left
   * edge of the first line is at the (transformed) origin, and all left edges are
   * aligned. RIGHT justification is similar. CENTER justification places the center
   * of the first string at the (transformed) origin, with the centers of all
   * remaining strings aligned under it. The second justify string, FIRST, is not
   * supported in this release.
   * 
   */
  SoMFString justify;
  /**
   * Specifies the distance (in the negative y direction) between the base points of
   * successive strings, measured with respect to the current font height. A value of
   * 1 indicates single spacing, a value of 2 indicates double spacing, and so on.
   * 
   */
  SoSFFloat spacing;
    
  /**
   * Return the font name used by this node based on the settings of family and style
   */
  SbString getFontName();

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
  virtual ~SoVRMLFontStyle();
    
 private:
  static  const char *fontList[][4];

  SoSFEnum familyenum;
  SoSFBitMask  styleenum;
};

#endif /* _SO_VRMLFONTSTYLE_ */

