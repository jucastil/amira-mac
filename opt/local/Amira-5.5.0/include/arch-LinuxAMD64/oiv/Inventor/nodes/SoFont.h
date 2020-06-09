/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thad Beier (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : Nicolas DAGUISE (Dec 2004)
**=======================================================================*/




#ifndef  _SO_FONT_
#define  _SO_FONT_

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFName.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/nodes/SoNode.h>

/**
 * Node that defines font name, size, and type for text.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION 
 *   This node defines the current font type and point size for all subsequent text
 *   shapes in the scene graph. Depending on the font and render style selected, text shapes may be
 *   generated as polygons, lines, or textures. 
 *
 *   Starting with Open Inventor 6.0, text computation is done using the FreeType 2 library (www.freetype.org).
 *   FreeType is a customizable and portable software font engine which is capable of producing
 *   high-quality output. FreeType allows support of more font formats than in previous Open Inventor
 *   versions: TrueType, Type 1, CID-keyed Type 1, CFF, SFNT-based bitmap, X11 PCF (including gz
 *   compressed fonts), Windows FNT, BDF, PFR, dfont, etc.
 *
 *   Starting with Open Inventor 6.0, Unicode text strings are supported. 
 *   Please note that many fonts have limited support for Unicode characters,
 *   especially the Japanese, Chinese, and Korean glyphs. The Code2000 font file is
 *   an open source font file containing a relatively complete set of Unicode glyphs.
 *
 *   Font name:
 *
 * @OL 
 * @LI Common Font: @BR
 *
 *      The font name can be set either of two ways:
 *      - specifying directly the font file name (e.g., arial.ttf) with an absolute or relative path, or no path.
 *      - specifying the font family name and font style name with the form "family : style".
 *
 *       Typical family names include:
 *        - Arial @BR
 *        - Courier New @BR
 *        - Times New Roman
 *       
 *       Typical style names include:
 *        - Bold @BR
 *        - Italic @BR
 *        - Bold Italic
 *
 *     Loadable fonts:@BR
 *       The names of all loadable font files available in your environment 
 *       (depending on Open Inventor environment
 *       variables) can be obtained by calling #getAvailableFonts().
 *
 *     Font file location:@BR
 *
 *       To find the font file on your system, Open Inventor uses several rules. 
 *       The following directories are searched (in this order):
 *       - 1 - Current directory
 *       - 2 - $OIV_FONT_PATH
 *       - 3 - System-default font directory
 *       - 4 - $OIVHOME/data/fonts
 *
 *       The system-default font directory depends on the platform:
 *       
 *       @TABLE_0B
 *         @TR Windows  @TD (Retrieved from the registry. Often c:/Windows/Fonts)
 *         @TR Solaris  @TD /usr/openwin/lib/X11/fonts/Type1/outline
 *         @TR AIX      @TD /usr/lib/X11/fonts/Type1/DPS
 *         @TR HP-UX    @TD /usr/lib/X11/fonts/type1.st/typefaces
 *         @TR OSF      @TD /usr/lib/X11/fonts/Type1Adobe
 *         @TR Linux    @TD /usr/share/X11/fonts;/usr/share/fonts;/usr/lib/X11/fonts
 *         @TR MacOS    @TD /Library/Fonts
 *         @TR Other    @TD /usr/lib/DPS/outline/base
 *       @TABLE_END
 *       
 *       Environment variable OIV_FONT_PATH contains a colon-separated or semicolon-separated list of directories
 *       to search for font definition files.
 *
 *  @LI Stroke Fonts: @BR
 *
 *       Stroke fonts, which are drawn with vectors rather than triangles, can provide
 *       higher performance, and also better readability at small sizes. Stroke fonts can
 *       be used with SoText3 and SoAnnoText3, but not with other text nodes, such as
 *       SoAsciiText. Stroke fonts cannot be extruded.
 *       
 *       To use a stroke font, specify one of the following stroke font names:
 *       
 *       "TGS_Simplex_TGS" @BR
 *       "TGS_Simplex_Roman" @BR
 *       "TGS_Complex_Roman" @BR
 *       "TGS_Duplex_Roman" @BR
 *       "TGS_Triplex_Roman" @BR
 *       "TGS_Simplex_Script" @BR
 *       "TGS_Complex_Script" @BR
 *       "TGS_Simplex_Greek" @BR
 *       "TGS_Complex_Greek" @BR
 *       "TGS_Gothic_German" @BR
 *       "TGS_Gothic_Italian" @BR
 *       "TGS_Gothic_English" @BR
 *       "TGS_Complex_Cyrillic" @BR
 *       "TGS_Upper_Case_Mathematics" @BR
 *       "TGS_Lower_Case_Mathematics" @BR
 *       "TGS_Music" @BR
 *       "TGS_Meteorology" @BR
 *       "TGS_Symbols" @BR
 *       "TGS_Astrology" @BR
 *       "TGS_Complex_Italic" @BR
 *       "TGS_Triplex_Italic" 
 *       
 *       The following figure shows an assortment of characters from each stroke font.
 *       
 *       @IMAGE stroke_fonts.gif 
 *       
 *       Stroked fonts are subject to the current line attributes, line width and line
 *       pattern, which are specified with SoDrawStyle. 
 *       
 *       By default, the stroke font files are found in $OIVHOME/data/fonts. If you move
 *       them to a different directory, set the environment variable
 *       OIV_STROKE_FONT_PATH to be the path to the new directory.
 *
 *       Open Inventor uses several rules to find the font file on your system.
 *       The following directories are searched (in this order): (NB: If one of these
 *       directories exists, the rest are ignored)
 *       - 1 - $OIV_STROKE_FONT_PATH
 *       - 2 - $OIVHOME/data/fonts
 *       - 3 - ./fonts/
 *
 *   Stroke fonts - Kanji and Katakana:
 *
 *       Additional stroke font files are available for Kanji and Katakana output. To
 *       produce Kanji or Katakana stroke output, set the font to any one of the stroke
 *       font names. Then, for the text string, pass the desired multi-byte character
 *       string (MBCS) to Open Inventor, using the usual techniques. The font file name
 *       is not used except as a flag to indicate that stroke output should be produced. 
 *
 * @ol
 *   Font name cache:
 *
 *       Making a call to the getAvailableFonts() method causes Open Inventor to build 
 *       an internal font name cache. This cache allows quick access to a newly requested 
 *       font name without requiring Open Inventor to parse all found font files on your system.
 *       In the general case, when the #name field changes, Open Inventor searches for the 
 *       corresponding font file and adds its name to its cache for faster retrieval the next time.
 *       For example, a request to "Arial : Regular" font name will be internally associated with
 *       the arial.ttf font file. The next time "Arial : Regular" is requested, Open Inventor will use
 *       arial.ttf. Specifying a not-previously-accessed string as a font name will
 *       cause Open Inventor to parse this new string to find a new association. If no association is found,
 *       a default font is used for this association. For instance, "Arial : Regul" doesn't
 *       necessarily correspond to the arial.ttf font file.
 *       To reset the font name cache, call the getAvailableFonts() method and specify the
 *       clearDB parameter as TRUE
 *    
 *   Font rendering - caching strategy:
 *
 *     The maximum number of caches used during text rendering is specified by the OIV_MAX_FONT_CACHES
 *     environment variable. The default number of caches is 20.
 *     A cache corresponds to a set of parameters that are taken into account during the computation
 *     of a text string. These parameters can be, depending on the kind of text node you are using, font name,
 *     size, complexity, etc. The same cache is used
 *     for strings that have exactly the same appearance (but not
 *     necessarily the same characters). 
 *     Note that the cache depends on color only for text bitmap rendering. That is,
 *     2D text with renderStyle POLYGON.
 *
 *     It's important to specify an appropriate value for the maximum number of font caches 
 *     as application performance can be
 *     highly dependent on the font caching. In fact, if not enough caches are available, in some
 *     cases, Open Inventor will have to recompute text metrics. 
 *
 *   Font render style:
 * 
 *     The #renderStyle field allows you to control the rendering mode for the font. It's possible 
 *     to render 3D text, e.g. SoText3, using filled polygons, filled and outlined polygons or 
 *     textured quads. (2D text, e.g. SoText2, is always rendered using bitmaps.)
 *     Polygonal text rendered with high complexity (for nice appearance) may require a large number of
 *     polygons and reduce performance. Text rendering using textures uses very few polygons and
 *     takes advantage of fast texturing hardware on modern graphics boards.  However when rendering
 *     text using textures, it is not possible to apply a texture image (e.g. SoTexture2) to the text
 *     and SoText3 is not extruded even if the parts field is set to ALL.
 *
 *   Textured font rendering considerations: 
 *
 *     Texture generation quality depends on the current complexity (defined by the
 *     SoComplexity::value field) and the current textureQuality (defined by the
 *     SoComplexity::textureQuality field) in collaboration with a texture resolution value range
 *     defined by the SoTextProperty::textureQualityRange field.
 *     Increasing these values will improve the quality of the output, but at the cost of
 *     decreased performance and increased memory consumption.
 *     
 *    If render style TEXTURE is selected, then a texture image is generated for each character.
 *    The image of the character is automatically antialiased, which means that some pixels
 *    in the texture image will be transparent or partially transparent. Text rendered in this
 *    mode is a "transparent" object like any other transparent geometry, and may be rendered
 *    incorrectly depending on the order in which objects are rendered. To avoid this issue,
 *    you can set the transparency type for rendering the scene graph to,
 *    for example, SORTED_DELAYED_BLEND (see SoGLRenderAction or SoTransparencyType). Or, set
 *    the text #renderStyle to TEXTURE_DELAYED. This allows delayed rendering of just the text
 *    objects. Note that even though setting the #renderStyle field to TEXTURE_DELAYED is a very simple
 *    solution, it can reduce performance due to less efficient render caching.
 *    Another option is to move the text node definition in the scene graph to be after
 *    all shapes.
 *
 *    Note also that SORTED_TRIANGLES transparency types are not applicable to textured text. When
 *    using textured text with sorted triangles transparencies, text rendering transparency is
 *    forced to BLEND or ADD transparency (depending on the selected type).
 *
 *    For text rendering with small font sizes,
 *    the default anti-aliasing can lead to undesirable blurring effects. The anti-aliasing level 
 *    can be changed through the use of the SoTextProperty::aliasingFactor.
 *
 * @FILE_FORMAT_DEFAULT
 *    Font {
 *    @TABLE_FILE_FORMAT
 *       @TR name        @TD "defaultFont"
 *       @TR size        @TD 10
 *       @TR renderStyle @TD POLYGON
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
 *        Sets the font name and size in the current traversal state.
 *        Sets: SoFontNameElement, SoFontSizeElement, 
 *              SoFontRenderStyleElement, SoTextOutlineEnabledElement
 * 
 * @SEE_ALSO
 *    SoAnnoText3,
 *    SoAsciiText,
 *    SoText2,
 *    SoText3,
 *    SoTextProperty
 * 
 *
 */ 

class INVENTOR_API SoFont : public SoNode {
  
  SO_NODE_HEADER(SoFont);
  
 public:
  // Fields
  /**
   * This field specifies the font name. 
   * The font name can be set either of two ways: 
   *      - specifying directly the font file name (e.g., arial.ttf) with an absolute or relative path, or no path.
   *      - specifying the font family name and font style name with the form "family : style".
   * Default is "defaultFont" (system dependent).
   */
  //SoSFName name;
  SoSFString name;

  /**
   * This field specifies the font size. The value is in printer's
   * points for 2D text (SoText2) and is in the current (object space) units
   * for 3D text (SoText3). Default is 10.
   */  
  SoSFFloat size;

  /** Render style */
  enum RenderStyle {
    /** Render font as polygonal objects. (default). */
    POLYGON,
    /** Render font as texture objects. */
    TEXTURE,
    /** 
     * Render font as texture objects, but delay the rendering to
     * prevent transparency artifacts, similar to delaying transparent objects.
     * @ENUM_SINCE_OIV 6.1
     */
    TEXTURE_DELAYED,
    /** Render outlining font. Not available for SoText2 text node. */
    POLYGON_AND_OUTLINE
  };

  /**
   * This field specifies the rendering style of the font.
   * Use enum #RenderStyle. Default is POLYGON.
   *
   * @FIELD_SINCE_OIV 5.0
   */
  SoSFEnum renderStyle;

   /**
   * Creates a font node with default settings.
   */
  SoFont();
  
  /**
   * Sets flag to enable strings to be interpreted using the MCS Japanese MBCS
   * encoding. This encoding is only used when a stroke font is specified. Default is
   * TRUE.
   * 
   * Set this flag to FALSE if you want to use characters in the range 128-255 (ISO
   * Latin-1) with stroke fonts.
   * 
   * [Win32] If the current code page is Japanese, the standard Microsoft MBCS
   * encoding is used independent of this flag.
   */
  static void enableMCSJapaneseSF(SbBool flag = TRUE);

  /**
   * Gets flag that indicates whether strings should be interpreted using the 
   * MCS Japanese MBCS encoding. This encoding is only used when a stroke font
   * is specified. 
   */
  static SbBool isMCSJapaneseSFEnabled() ;
  
  /** 
   * Sets the maximum number of caches that can be used for font rendering. Default is 20. This number
   * corresponds to the number of changes that can be applied to a font: for example,
   * to use the "Arial" and the "Times" fonts one after the other, two caches are created.
   * Subsequently changing a rendering property like SoFont::renderStyle causes the creation of new
   * caches.
   * Properties that cause a cache to be rebuilt include the following: 
   *  - SoAsciiText: font name, size, render style, text orientation
   *  - SoText2: font name, size, viewport size, render style, text orientation
   *  - SoText3: font name, size, render style, text orientation, profile definition
   *
   * Note: This list is not exhaustive.
   */
  static void setNumFontCaches(int maxNumCaches);

  /** 
   * Returns the maximum number of caches that can be used for font rendering.
   */
  static int getNumFontCaches();

  /** 
   * Returns the current number of caches used for font rendering.
   */
  static int getCurrNumFontCaches();

  /** 
   * Returns the number of loadable font files and a list of their names. Each name in the list is formatted 
   * as follows: "Name : Style : (font file)".
   * The retrieved string can be passed directly to the SoFont::name field 
   * (the "(font file)" substring will be ignored).
   * Internally, this method builds a font name cache. It scans some predefined directories and
   * registers the association "Name : Style" <=> "font file". Passing the clearDB parameter as TRUE 
   * empties the font name cache, and then regenerates it.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  static int getAvailableFonts(SbString*& strings, SbBool clearDB = FALSE);

  /** 
   * Specifies paths for searching for font files.
   * Using this method overrides all other font path definitions, i.e.,
   * Open Inventor environment variables and default system font directories.
   * The paths must be separated by a semicolon (";")
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void setFontPaths(char*);

  /** 
   * Specifies paths for searching for font files.
   * Using this method overrides all other font path definitions, i.e.,
   * Open Inventor environment variables and default system font directories.
   * The paths must be separated by a semicolon (";")
   */
  static void setFontPaths( const SbString& );

  /** 
   * Specifies paths for searching for font files.
   * Use this method to add new font paths to the current list of searched paths.
   * The paths must be separated by a semicolon (";")
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void addFontPaths(char*);

  /** 
   * Specifies paths for searching for font files.
   * Use this method to add new font paths to the current list of searched paths.
   * The paths must be separated by a semicolon (";")
   */
  static void addFontPaths( const SbString& );

  /** 
   * Gets current font path list.
   */
  static SbString getFontPaths();
  
  /** 
   * Returns TRUE if the specified font is available for use by Open Inventor.
   * Internally, this method builds a font name cache (once only). It scans 
   * some predefined directories and
   * registers the association "Name : Style" <=> "font file". 
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static SbBool isAvailableFont(char* );

  /** 
   * Returns TRUE if the specified font is available for use by Open Inventor.
   * Internally, this method builds a font name cache (once only). It scans 
   * some predefined directories and
   * registers the association "Name : Style" <=> "font file". 
   */
  static SbBool isAvailableFont(const SbString& );

  /** 
   * Clears the Open Inventor internal font name cache, i.e., the list of available fonts.
   */
  static void clearFontNameCache();

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
  virtual void pick(SoPickAction *action);
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  SoSFBool override;

  static void enableTGSJapaneseSF(SbBool flag = TRUE); // Compatibility only
  static SbBool isTGSJapaneseSFEnabled() ;             // Compatibility only

 protected:
  virtual ~SoFont();

  // TRUE by default
  static SbBool m_isMCSJapaneseSFEnabled;

};

#endif /* _SO_FONT_ */

