/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Damien DALLA ROSA (Dec 2008)
**=======================================================================*/


#ifndef SO_BBOX_H
#define SO_BBOX_H

#include <Inventor/nodes/SoNode.h>
#include <Inventor/SoType.h>

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFBox3f.h>

class SoCube;

/**
 * @VSGEXT Bounding box node.
 *
 * @ingroup Nodes
 * 
 * @DESCRIPTION
 * This class specifies a bounding box during scene graph traversal.
 * This allows the application to use an application defined bounding box or to stop a 
 * getBoundingBox action for the current scene graph branch. 
 * Note: if a projection is defined in the scene graph, the SoBBox is ignored.
 *
 * This can be useful, for example:
 * - To specify the bounding box of some very large geometry. @BR
 *   For example to avoid the CPU time to calculate the bounding box. (Use mode = USER_DEFINED)
 * - To "hide" some geometry from the bounding box calculation. @BR
 *   For example to avoid having annotation geometry, like legends and titles, affect
 *   the viewer's viewAll operation. (Use mode = NO_BOUNDING_BOX)
 *
 * @FILE_FORMAT_DEFAULT
 *    BBox {
 *    @TABLE_FILE_FORMAT
 *       @TR mode          @TD DISABLE
 *       @TR boundingBox   @TD 0 0 0 0 0 0
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *      If enabled, draws the specified bbox when complexity type = BOUNDING_BOX.
 *
 *    SoGetBoundingBoxAction @BR
 *      If enabled, stops traversal of this portion of the scene graph and, if mode =
 *      USER_DEFINED, adds the specified bbox to the accumulated bbox.
 * 
 */

class INVENTOR_API SoBBox : public SoNode
{
  SO_NODE_HEADER( SoBBox );

 public:

  /** 
   * This enum specifies how the node interacts with OpenInventor during a traversal.
   */
  enum Mode
  {
    /** 
     * The node doesn't do anything.
     */
    DISABLE,

    /**
     * SoGetBoundingBoxAction will ignore subsequent nodes in this portion of the scene graph
     * (as if the nodes don't exist).
     */
    NO_BOUNDING_BOX,

    /**
     * SoGetBoundingBoxAction will ignore subsequent nodes in this portion of the scene graph
     * and use the box specified in the boundingBox field as the bounding box of those nodes.
     *
     * When the complexity type is BOUNDING_BOX (see SoComplexity), SoGLRenderAction will
     * ignore subsequent nodes in this portion of the scene graph and render the box specified
     * in the boundingBox field.
     */
    USER_DEFINED
  };

  /** 
   * Specifies the behavior of the SoBBox node.
   * Use enum #Mode. Default is DISABLE.
   */
  SoSFEnum mode;

  /**
   * Application-defined bounding box.
   */
  SoSFBox3f boundingBox;

  /**
   * Constructor.
   */
  SoBBox();


 SoINTERNAL public:

  /**
   * Regular init class function
   */
  static void initClass();

  /**
   * Regular exit class function
   */
  static void exitClass();

  /**
   * Overloaded getBoundingBox function to apply the user defined bounding box or to
   * stop the traversal.
   */
  virtual void getBoundingBox( SoGetBoundingBoxAction *action );

  /**
   * Overloaded GLRender function used to render the bounding box.
   */
  virtual void GLRender(SoGLRenderAction *action);

 protected:

  // Destructor
  virtual ~SoBBox();

 private:

 /** The SoCube which is used to render the bounding box */
 SoCube* m_boundingBoxCube;

};

#endif // SOBBOX_H

