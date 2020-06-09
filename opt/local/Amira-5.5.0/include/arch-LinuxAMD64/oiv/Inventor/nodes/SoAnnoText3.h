/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2004)
**=======================================================================*/



#ifndef  _SO_ANNOT_TEXT_3_
#define  _SO_ANNOT_TEXT_3_

#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoShape.h>

class SoText2;
class SoText3;

/**
 * @VSGEXT Annotation text node.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   SoAnnoText3 has some features of SoText3 and also some of SoText2. However for
 *   the Text2 functionality, the size of the font (see SoFont) is interpreted in the
 *   current units, so the text can be zoomed, but not rotated. The current
 *   annotation property (SoAnnoText3Property) determines this choice.
 *   
 *   @B Stroke Fonts@b: If a stroke font is used (see SoFont), the text is rendered
 *   with lines rather than faces. Line attributes apply instead of polygon
 *   attributes. Text is not extruded.
 *
 *   Shape Antialiasing type is SoShape::TEXT.
 * 
 * @FILE_FORMAT_DEFAULT
 *    AnnoText3 {
 *    @TABLE_FILE_FORMAT
 *       @TR string          @TD ""
 *       @TR spacing         @TD 1.0
 *       @TR justification   @TD LEFT
 *       @TR alternateRep    @TD NULL
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
 *    SoAnnoText3Property,
 *    SoText2,
 *    SoText3,
 *    SoFullSceneAntialiasing
 * 
 * 
 */ 

class INVENTOR_API SoAnnoText3 : public SoShape {

  SO_NODE_HEADER(SoAnnoText3);
  
public:

  /** Justification types */
  enum Justification {
    /**
     *  Left justification 
     */
    LEFT = 0x01,
    /**
     *  Center justification 
     */
    CENTER = 0x03,
    /**
     *  Right justification 
     */
    RIGHT = 0x02,
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
   * remaining strings aligned under it. @BR
   * Use enum #Justification.  Default is Left.
   */
  SoSFEnum justification;  
  /**
   * This field optionally holds an SoText3 node that will be written out
   * in place of this SoAnnoText3 node when saved to a .iv file. 
   * 
   */
  SoSFNode alternateRep;
  
  /**
   * Constructor.
   */
  SoAnnoText3();
  
 SoEXTENDER public:

  // Method to get the bounds of the given character in the given
  // string.  This must be called during the application of an
  // action; use a callbackAction applied to a Path to the text node
  // if you have to (this is really designed to be used in a Text3
  // manipulator, which will have direct access to the state).
  // The bounds are based on the font metric information, not the
  // geometric bounding box of the character.  So, for example,
  // while a space character has an empty bounding box,
  // getCharacterBounds() will return a box as high as the font
  // height, as wide as a space, and as deep as the profile.
  SbBox3f getCharacterBounds(SoState *state,  int stringIndex, int charIndex);
  virtual void GLRender(SoGLRenderAction *action);
  virtual void rayPick(SoRayPickAction *action);
  virtual void write(SoWriteAction *action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);

  // Computes bounding box of text
  virtual void computeBBox(SoAction *action, SbBox3f &box,  SbVec3f &center);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  SoSFNode m_text2Rep;
  SoSFNode m_text3Rep;
  
 protected:
  
  // Generates primitives
  virtual void generatePrimitives(SoAction *);
  
  virtual ~SoAnnoText3();
  
};

#endif // _SO_ANNOT_TEXT_3_

/**/
