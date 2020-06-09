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


#ifndef  _SO_PICK_STYLE_
#define  _SO_PICK_STYLE_

#include <Inventor/SbString.h>
#include <Inventor/elements/SoPickStyleElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPickStyle
//
//  Pick style node. Allows picking in subgraphs to be defined in one
//  of the following ways:
//
//      SHAPE (default): points on the surfaces of shapes may be picked
//      BOUNDING_BOX:    points on the surfaces of bounding boxes of
//                       shapes may be picked
//      UNPICKABLE:      objects in the subgraph are transparent to picks
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Picking style node.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node determines how subsequent geometry nodes in the scene graph are to be
 *   picked, as indicated by the #style field.
 *   
 *   Note that this is the only way to change the pick behavior of shapes; drawing
 *   style, complexity, and other rendering-related properties have no effect on
 *   picking.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PickStyle {
 *    @TABLE_FILE_FORMAT
 *       @TR style   @TD SHAPE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoRayPickAction,  SoCallbackAction @BR
 *        Sets the current pick style in the state. Sets: SoPickStyleElement
 * 
 * 
 * @SEE_ALSO
 *    SoComplexity,
 *    SoDrawStyle,
 *    SoRayPickAction
 * 
 * 
 */ 

class INVENTOR_API SoPickStyle : public SoNode {

  SO_NODE_HEADER(SoPickStyle);

 public:
   /** Picking style */
  enum Style {
    /**
     *  Points on the surfaces of shapes may be picked 
     */
    SHAPE           = SoPickStyleElement::SHAPE,
    /**
     *  Points on the surfaces of 3D bounding boxes of shapes may be picked 
     */
    BOUNDING_BOX    = SoPickStyleElement::BOUNDING_BOX,
    /**
     *  Subsequent objects are transparent to picks 
     */
    UNPICKABLE      = SoPickStyleElement::UNPICKABLE
  };

  // Fields
  /**
   * Picking style.
   * Use enum #Style. Default is SHAPE.
   */
  SoSFEnum            style;

  /**
   * Creates a pick style node with default settings.
   */
  SoPickStyle();

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
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        pick(SoPickAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SoSFBool override;

 protected:
  virtual ~SoPickStyle();
};

#endif /* _SO_PICK_STYLE_ */

