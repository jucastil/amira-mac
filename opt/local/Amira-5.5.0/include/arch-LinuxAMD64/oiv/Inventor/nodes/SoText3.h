/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : SGI (MMM YYYY)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : Nicolas DAGUISE (Oct 2004)
**=======================================================================*/


#ifndef  _SO_TEXT_3_
#define  _SO_TEXT_3_

#include <Inventor/SbBox.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/threads/SbThreadRWMutex.h>
#include <Inventor/STL/map>

class SoFontServer;
class TextBBoxCache;
class SbBox3f;
class SoAnnoText3;
struct Pid_primitive_data;

/**
 * 3D text shape node.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This node defines one or more strings of 3D text. In contrast with SoText2, 3D
 *   text can be rotated, scaled, lighted, and textured, just like all other 3D
 *   shapes. Each character in a 3D text string is created by extruding an outlined
 *   version of the character (in the current typeface) along the current profile, as
 *   defined by nodes derived from SoProfile. The default text profile, if none is
 *   specified, is a straight line segment one unit long.
 *   
 *   The text origin is at (0,0,0) after applying the current transformation. The
 *   scale of the text is affected by the @B size @b field of the current SoFont as
 *   well as the current transformation.
 *   
 *   SoText3 uses the current set of materials when rendering. If the material binding
 *   is OVERALL, then the whole text is drawn with the first material. If it is
 *   PER_PART or PER_PART_INDEXED, the front part of the text is drawn with the first
 *   material, the sides with the second, and the back with the third.
 *   
 *   Textures are applied to 3D text as follows. On the front and back faces of the
 *   text, the texture origin is at the base point of the first string; the base
 *   point is at the lower left for justification LEFT, at the lower right for RIGHT,
 *   and at the lower center for CENTER. The texture is scaled equally in both S and
 *   T dimensions, with the font height representing 1 unit. S increases to the right
 *   on the front faces and to the left on the back faces. On the sides, the texture
 *   is scaled the same as on the front and back. S is equal to 0 at the rear edge of
 *   the side faces. The T origin can occur anywhere along each character, depending
 *   on how that character's outline is defined.
 *   
 *   @B Stroke Fonts @b: If a stroke font is used (see SoFont), the text is rendered
 *   with lines rather than faces. Line attributes apply instead of polygon
 *   attributes. Text is not extruded.
 *
 *   Shape Antialiasing type is SoShape::TEXT.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Text3 {
 *    @TABLE_FILE_FORMAT
 *       @TR string          @TD ""
 *       @TR spacing         @TD 1
 *       @TR justification   @TD LEFT
 *       @TR parts           @TD FRONT
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws text based on the current font, profiles, transformation, drawing style,
 *        material, texture, complexity, and so on.
 * 
 *    SoRayPickAction @BR
 *        Performs a pick on the text. The string index and character position are
 *        available from the SoTextDetail.
 * 
 *    SoGetBoundingBoxAction @BR
 *        Computes the bounding box that encloses the text.
 * 
 *    SoCallbackAction @BR
 *        For non-stroke fonts,if any triangle callbacks are registered with the action,
 *        they will be invoked for each successive triangle used to approximate the text
 *        geometry.
 *        
 *        For stroke fonts, if any line segment callbacks are registered with the action,
 *        they will be invoked for each successive line segment used to approximate the
 *        text geometry.
 * 
 * 
 * @SEE_ALSO
 *    SoFont,
 *    SoFullSceneAntialiasing,
 *    SoProfile,
 *    SoText2,
 *    SoTextDetail
 * 
 * 
 */ 

class INVENTOR_API SoText3 : public SoShape {

  SO_NODE_HEADER(SoText3);

 public:
   /** Justification types */
  enum Justification {
    /**
     *  Left edges of all strings are aligned 
     */
    LEFT   = 0x01,
    /**
     *  Centers of all strings are aligned 
     */
    CENTER = 0x03,
    /**
     *  Right edges of all strings are aligned 
     */
    RIGHT  = 0x02,
    /** 
     *  The text justification is inherited from the current SoTextProperty::alignmentH value.
     */
    INHERITED = 0x04
  };

  /** Text3 part values. */
  enum Part {
    /**
     *  Front faces of characters 
     */
    FRONT = 0x01,
    /**
     *  Extruded sides of characters 
     */
    SIDES = 0x02,
    /**
     *  Back faces of characters 
     */
    BACK  = 0x04,
    /**
     *  All parts 
     */
    ALL   = 0x07
  };

  // Fields
  /**
   * The text string(s) to display. Each string will appear on its own line.
   * 
   */
  SoMFString string;

  /**
   * Defines the distance (in the negative y direction) between the base points of
   * successive strings, measured with respect to the current font height. A value of
   * 1 indicates single spacing, a value of 2 indicates double spacing, and so on.
   * 
   */
  SoSFFloat spacing;

  /**
   * Which parts of text are visible. Note that, for speed, the default for this
   * field is FRONT only.
   * 
   */
  SoSFBitMask parts;

  /**
   * Indicates placement and alignment of strings. With LEFT justification, the left
   * edge of the first line is at the (transformed) origin, and all left edges are
   * aligned. RIGHT justification is similar. CENTER justification places the center
   * of the first string at the (transformed) origin, with the centers of all
   * remaining strings aligned under it.
   * Use enum #Justification. Default is LEFT.
   */
  SoSFEnum justification;

  /**
   * Creates a 3D text node with default settings.
   */
  SoText3();

 SoEXTENDER public:

  /**
   * Method to get the bounds of the given character in the given
   * string.  This must be called during the application of an
   * action; use a callbackAction applied to a Path to the text node
   * if you have to (this is really designed to be used in a Text3
   * manipulator, which will have direct access to the state).
   * The bounds are based on the font metric information, not the
   * geometric bounding box of the character.  So, for example,
   * while a space character has an empty bounding box,
   * getCharacterBounds() will return a box as high as the font
   * height, as wide as a space, and as deep as the profile.
   */
  SbBox3f getCharacterBounds(SoState *state, int stringIndex, int charIndex);

  virtual void GLRender(SoGLRenderAction *action);
  virtual void notify(SoNotList *list);
  virtual void rayPick(SoRayPickAction *action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);
  
  /**
   * Computes bounding box of text.
   */
  virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  void addFontCache(void *fontCache);
  void removeFontCache(void *fontCache);
  int getNumFontCache();
  void* getFontCache(int i);

protected:
    
  /**
   * Destructor.
   */
  virtual ~SoText3();

  /**
   * Returns TRUE if the shape should be rendered. Subclasses can
   * call this in their rendering methods to determine whether to
   * continue.
   */
  virtual SbBool shouldGLRender(SoGLRenderAction *action, SbBool isPointsOrLines = FALSE);

  /**
   * Generates primitives.
   */
  virtual void generatePrimitives(SoAction *);

  friend class SoAnnoText3;

private:

  SoFontServer* m_fontServer;
  SbPList* m_fontBaseList;

  typedef std::map<void*, TextBBoxCache*> SoTextBBoxCaches;
  SoTextBBoxCaches* m_textBBoxCache;

  // Per-instance mutex to protect access to the vpCache
  SbThreadRWMutex *fontCacheMutex;

  SbVec2f getStringOffset(SoState* state, int line);

  // Creates a text detail when picking:
  SoDetail * createTriangleDetail(SoRayPickAction *, const SoPrimitiveVertex *, const SoPrimitiveVertex *, const SoPrimitiveVertex *, SoPickedPoint *);

// KANJI

  SbBool m_isKanji;
  float kanjiHeight;
  Pid_primitive_data *m_primitive_data;
  int m_num_prim;
 
  SbVec2f getKanjiStringOffset(SoState* state, int line);
  void renderKanji(SoGLRenderAction *action, int line);
  void renderKanjiFont(SoGLRenderAction *action);
  void getKanjiBBox(SoAction *action, SbBox2f &result);
  void getKanjiFont(int kfont);
  SbBool setupFontKanji(SoState *state, SbBool forRender);
  void kanjiSetupCharacters(int line, int *numChar);
  SbBool kanjiCheck();
  void freeKanji();
};

#endif // _SO_TEXT_3_

/**/
