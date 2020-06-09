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


#ifndef  _SO_ASCII_TEXT_
#define  _SO_ASCII_TEXT_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/STL/map>

class SoFontServer;
class TextBBoxCache;
class SbBox3f;

/**
 * @VSGEXT Simple 3D text shape node.
 * 
 * @ingroup ShapeNodes VRML1
 * 
 * @DESCRIPTION
 *   This node defines one or more strings of 3D text. In contrast with SoText2, 3D
 *   text can be rotated, scaled, lighted, and textured, just like all other 3D
 *   shapes. In contrast with SoText3, this 3D Ascii text cannot be extruded.
 *   
 *   The text origin is at (0,0,0) after applying the current transformation. The
 *   scale of the text is affected by the @B size @b field of the current SoFont as
 *   well as the current transformation.
 *   
 *   SoAsciiText uses the current material when rendering. Textures are applied to
 *   ascii text as follows. On the front face of the text, the texture origin is at
 *   the base point of the first string; the base point is at the lower left for
 *   justification LEFT, at the lower right for RIGHT, and at the lower center for
 *   CENTER. The texture is scaled equally in both S and T dimensions, with the font
 *   height representing 1 unit. S increases to the right on the front face.
 *
 *   Shape Antialiasing type is SoShape::TEXT.
 * 
 * @FILE_FORMAT_DEFAULT
 *    AsciiText {
 *    @TABLE_FILE_FORMAT
 *       @TR string          @TD ""
 *       @TR spacing         @TD 1
 *       @TR justification   @TD LEFT
 *       @TR width           @TD 0
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws text based on the current font, transformation, drawing style, material,
 *        texture, complexity, and so on.
 * 
 *    SoRayPickAction @BR
 *        Performs a pick on the text. The string index and character position are
 *        available from the SoTextDetail.
 * 
 *    SoGetBoundingBoxAction @BR
 *        Computes the bounding box that encloses the text.
 * 
 *    SoCallbackAction @BR
 *        If any triangle callbacks are registered with the action, they will be invoked
 *        for each successive triangle used to approximate the text geometry.
 * 
 * 
 * @SEE_ALSO
 *    SoFont,
 *    SoFontStyle,
 *    SoText2,
 *    SoText3,
 *    SoTextDetail,
 *    SoFullSceneAntialiasing
 * 
 * 
 */ 

class INVENTOR_API SoAsciiText : public SoShape {

  SO_NODE_HEADER(SoAsciiText);

 public:
  enum Justification {                // Justification types
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
   * Default is 1.
   */
  SoSFFloat spacing;

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
   * Defines the width of each text string. Each string will be scaled so that it
   * spans this many units. Default is 0.
   * 
   */
  SoMFFloat width;

  /**
   * Creates an ascii text node with default settings.
   */
  SoAsciiText();

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

  // Propagates modification notification through an instance.
  virtual void notify(SoNotList *list);

 protected:
  
  /**
   * Generates primitives.
   */
  virtual void generatePrimitives(SoAction *);
    
  /**
   * Destructor.
   */
  virtual ~SoAsciiText();

  /**
   * Returns TRUE if the shape should be rendered. Subclasses can
   * call this in their rendering methods to determine whether to
   * continue.
   */
  virtual SbBool shouldGLRender(SoGLRenderAction *action, SbBool isPointsOrLines = FALSE);

 private:

  SoFontServer* m_fontServer;
  SbPList* m_fontBaseList;

  typedef std::map<void*, TextBBoxCache*> SoTextBBoxCaches;
  SoTextBBoxCaches* m_textBBoxCache;

  SbVec2f getStringOffset(SoState* state, int line, float& pAdd);

  // Creates a text detail when picking:
  SoDetail * createTriangleDetail(SoRayPickAction *, const SoPrimitiveVertex *, const SoPrimitiveVertex *, const SoPrimitiveVertex *, SoPickedPoint *);

};

#endif // _SO_ASCII_TEXT_

/**/
