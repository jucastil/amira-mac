/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas Daguise (Nov 2003)
**=======================================================================*/

#ifndef  _SO_FULL_SCENE_ANTIALIASING
#define  _SO_FULL_SCENE_ANTIALIASING

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/nodes/SoNode.h>

#include <Inventor/elements/SoFullSceneAntialiasingElement.h>

/** 
 * @VSGEXT Node that controls full-scene antialiasing.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION 
 *   This class controls full-scene antialiasing. This node can
 *   be used to enable or disable the antialiasing mode on a part of a scene graph.
 *
 *   This node has no effect if full-scene antialiasing is not supported in the
 *   graphics hardware or has not been enabled. Full-scene antialiasing can
 *   be enabled by defining a graphic configuration template, by calling the
 *   method SoWinGLWidget::setFullSceneAntialiasing(), or (on some systems)
 *   by the user through the system display properties dialog.
 *
 *   The #filter field allows you to select what kind of nodes (derived from SoShape) will be
 *   antialiased. For certain primitives antialiasing may be undesirable. For example,
 *   bitmap text (SoText2, etc.) may be "blurred" by antialiasing.
 *
 *   The filter result is highly dependent on your graphics hardware.
 * 
 *   Note: The quality level specified by the SoWinGLWidget::setFullSceneAntialiasing()
 *   method cannot be changed during a traversal because it depends on the pixel format.
 *   
 * @FILE_FORMAT_DEFAULT
 *    FullSceneAntialiasing {
 *    @TABLE_FILE_FORMAT
 *       @TR on       @TD TRUE
 *       @TR filter   @TD ALL
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *  Sets: SoFullSceneAntialiasingElement
 *
 * @SEE_ALSO
 *  SoGLGraphicConfigTemplate, SoWinGLWidget::setFullSceneAntialiasing(),
 *  SoWinGLWidget::getFullSceneAntialiasing(),
 *  SoWinGLWidget::isFullSceneAntialiasingAvailable(),
 *  SoWinGLWidget::isFullSceneAntialiasingEnabled()
 *
 * 
 */ 

class INVENTOR_API SoFullSceneAntialiasing : public SoNode {  
  SO_NODE_HEADER(SoFullSceneAntialiasing);

public:
  /**
   * Enables/disables full-scene antialiasing. @BR
   * @BR
   * Default = TRUE.
   * The default value can be set using the environment variable 
   * OIV_FULL_SCENE_ANTIALIASING (0 = FALSE, 1 = TRUE). 
   */
  SoSFBool on;

  /** 
   * Defines the types of rendering shapes.
   */
  enum Filter {
    /** The shape is render based on points (Ex: SoPointSet).*/
    POINTS = SoFullSceneAntialiasingElement::POINTS,
    /** The shape is render based on lines (Ex: SoLineSet).*/
    LINES  = SoFullSceneAntialiasingElement::LINES, 
    /** The shape is render based on polygons (Ex: SoFaceSet).*/
    POLYGONS = SoFullSceneAntialiasingElement::POLYGONS,
    /** The shape is a text and follows the special filter for texts.*/
    TEXT = SoFullSceneAntialiasingElement::TEXT,
    /** No specific filter for antialiasing (Default).*/
    ALL = SoFullSceneAntialiasingElement::ALL
  };

  /** 
   * A bit-wise combination of LINES, POINTS, POLYGONS, and TEXT
   * that determines which primitive types should be antialiased. @BR
   * @BR
   * Default = ALL. The default value can be set using the
   * environment variable OIV_FULL_SCENE_ANTIALIASING_FILTER.
   * Valid values are ALL, or any combination of LINES, POINTS, 
   * POLYGONS, and TEXT.
   *
   * The rules to determine if the antialiasing extension should stay
   * enabled or should be disabled are described in the following
   * tables:
   *
   * @htmlinclude ShapeFilterTable.html
   */
  SoSFBitMask filter;

  /**
   * Constructor.
   */
  SoFullSceneAntialiasing();

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
  virtual void  doAction(SoAction *action);
  virtual void  callback(SoCallbackAction *action);
  virtual void  GLRender(SoGLRenderAction *action);

//-----------------------------------------------------------------------------
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  SoSFBool override;

 protected:
  // Destructor
  virtual ~SoFullSceneAntialiasing();
};

#endif /* _SO_FULL_SCENE_ANTIALIASING */
