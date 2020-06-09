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


#ifndef  _SO_TEXT_2_
#define  _SO_TEXT_2_

#include <Inventor/SbViewportRegion.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/STL/map>

class SoFontServer;
class TextBBoxCache;
class SoAnnoText3;

/**
 * Screen-aligned 2D text shape node.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This node defines one or more strings of 2D text. The text is always aligned
 *   horizontally with the screen and does not change size with distance in a
 *   perspective projection. The text origin is at (0,0,0) after applying the current
 *   transformation. Rotations and scales have no effect on the orientation or size
 *   of 2D text, just the location.  A transform node, e.g. SoTranslation, should be
 *   used to position the text in 3D space.
 *   
 *   SoText2 uses the current font to determine the typeface and size. The text is
 *   always drawn with the diffuse color of the current material; it is not lit,
 *   regardless of the lighting model. Furthermore, 2D text can not be textured, and
 *   it ignores the current draw style and complexity.
 *   
 *   Because 2D text is screen-aligned, it has some unusual characteristics. For
 *   example, the 3D bounding box surrounding a 2D text string depends on the current
 *   camera and the current viewport size, since changing the field of view or the
 *   mapping onto the window changes the relative size of the text with respect to
 *   the rest of the scene.
 *
 *   Note: SoText2 nodes using CENTER or RIGHT justification cannot be cached
 *   because the bounding box and justification offset depend on the camera.  As a
 *   result, no SoSeparator above the SoText2 will be able to build a render cache
 *   or a bounding box cache and this can reduce performance. If possible put other 
 *   geometry, that can be cached, under its own SoSeparator. SoText2 nodes using 
 *   LEFT justification (the default) can be cached.
 *
 *   Shape Antialiasing type is SoShape::TEXT.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Text2 {
 *    @TABLE_FILE_FORMAT
 *       @TR string          @TD ""
 *       @TR spacing         @TD 1
 *       @TR justification   @TD LEFT
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws text based on the current font, at a location based on the current
 *        transformation.
 * 
 *    SoRayPickAction @BR
 *        Performs a pick on the text. Text will be picked if the picking ray intersects
 *        the bounding box of the strings. The string index and character position are
 *        available from the SoTextDetail.
 * 
 *    SoGetBoundingBoxAction @BR
 *        Computes the bounding box that encloses the text.
 * 
 * @SEE_ALSO
 *    SoFont,
 *    SoFullSceneAntialiasing,
 *    SoText3,
 *    SoTextDetail
 */ 

class INVENTOR_API SoText2 : public SoShape {

  SO_NODE_HEADER(SoText2);

 public:
   /** Justification types. */
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
   * Indicates placement and alignment of strings. With LEFT justification, the left
   * edge of the first line is at the (transformed) origin, and all left edges are
   * aligned. RIGHT justification is similar. CENTER justification places the center
   * of the first string at the (transformed) origin, with the centers of all
   * remaining strings aligned under it.
   * Use enum #Justification. Default is LEFT.
   */
  SoSFEnum justification;

  /**
   * Creates a 2D text node with default settings.
   */
  SoText2();

 SoEXTENDER public:
  virtual void GLRender(SoGLRenderAction *action);
  virtual void rayPick(SoRayPickAction *action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);
  void testRayPick(SoRayPickAction *action, SoNode *node);
  
  // Computes bounding box of text
  virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);

  /**
   * Returns an alternative representation of this node 
   * for PDF and U3D exports.
   */
  virtual SoNode* getAlternateRep( SoAction* action );

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  void setRenderZoom(bool zoom);

  virtual SoNode* createAlternateRep( SoAction* action );

  void addFontCache(void *fontCache);
  void removeFontCache(void *fontCache);
  int getNumFontCache();
  void* getFontCache(int i);

  // Propagates modification notification through an instance.
  virtual void notify(SoNotList *list);

protected:
  // Returns TRUE if the shape should be rendered. Subclasses can
  // call this in their rendering methods to determine whether to
  // continue.
  virtual SbBool shouldGLRender(SoGLRenderAction *action, SbBool isPointsOrLines = FALSE);
  
  // This method is a no-op for SoText2, since there are no
  // primitives it can generate
  virtual void generatePrimitives(SoAction *action);

  virtual ~SoText2();

  friend class SoAnnoText3;

 private:

  // Based on justification and line spacing, this returns the
  // offset (in pixels) for one of the lines of text.
  SbVec3f getStringOffset(SoState* state, int whichLine);

  SoFontServer* m_fontServer;
  SbPList* m_fontBaseList;
  
  typedef std::map<void*, TextBBoxCache*> SoTextBBoxCaches;
  SoTextBBoxCaches* m_textBBoxCache;

  bool m_renderZoom;
};

#endif // _SO_TEXT_2_

/**/
