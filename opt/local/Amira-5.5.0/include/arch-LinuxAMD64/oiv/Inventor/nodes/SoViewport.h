/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (May 2011)
**=======================================================================*/
#ifndef _SO_VIEWPORT_H_
#define _SO_VIEWPORT_H_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/elements/SoViewportRegionElement.h>

#include <Inventor/fields/SoSFVec2f.h>


class SoGLRenderAction;
class SoCallbackAction;
class SoPickAction;

//@TOBEWRAPPED
/**
 * @VSGEXT Viewport parameters node.
 *
 * @ingroup PropertyNodes
 *
 * @DESCRIPTION
 *   This node specifies the viewport used for rendering.
 *
 *   The view volume specified by the current camera will be mapped
 *   into this region of the render target (e.g. the viewer window).
 *   By default Open Inventor manages the viewport to be the entire
 *   render target, even if the window (for example) is resized.
 *   So this node is useful for rendering objects in a specific part
 *   of the window, for example screen locked annotation graphics
 *   like legends and a "compass".  Tip: You can use the
 *   SoViewportClipping and SoDepthBuffer nodes to clear the depth
 *   buffer in the viewport region to ensure annotation graphics render
 *   correctly.
 *
 *   If you want to place multiple "views" inside the same window,
 *   consider the PoView and PoSceneView nodes.  Views allow the application 
 *   to specify multiple cameras, each with its own separate viewport   
 *   Views can be used, for example, to subdivide the window into multiple 
 *   independent views of a 3D scene or to create an inset "bird's eye" view 
 *   inside the window, without the overhead of creating separate windows. 
 *   The advantage of using the view nodes over SoViewport is that when mouse
 *   event locations are mapped back into 3D space, Open Inventor automatically 
 *   uses the view volume of the camera associated with the view node whose
 *   viewport currently contains the mouse cursor.
 *
 *   @NODE_SINCE_OIV 8.6
 *
 * @FILE_FORMAT_DEFAULT
 *    Viewport {
 *      @TABLE_FILE_FORMAT
 *       @TR origin  @TD (0,0)
 *       @TR size    @TD (0,0)
 *      @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction
 *      Sets: SoViewportRegionElement
 *
 * @SEE_ALSO
 *       SbViewportRegion, SoViewportClipping, SoDepthBuffer, PoView, PoSceneView
 *
 *
 */
class INVENTOR_API SoViewport : public SoNode
{
  SO_NODE_HEADER(SoViewport);

public:

  /**
   * Specifies the position of the viewport in pixels.
   * (Although this is a float field, the values really
   * are pixels, not normalized units.) Default is 0,0.
   */
  SoSFVec2f origin;

  /**
   * Specifies the size of the viewport in pixels.
   * (Although this is a float field, the values really
   * are pixels, not normalized units.) Default is 0,0.
   */
  SoSFVec2f size;

  /** Constructor */
  SoViewport();

SoEXTENDER public:

  /** default actions behavior */
  virtual void doAction(SoAction *action);

  /** @copydoc SoNode::pick */
  virtual void pick(SoPickAction *action);

  /** @copydoc SoNode::callback */
  virtual void callback(SoCallbackAction* action);

  /** @copydoc SoNode::GLRender */
  virtual void GLRender(SoGLRenderAction * action);


SoINTERNAL public:
  /** @copydoc SoNode::initClass. */
  static void initClass();

  /** @copydoc SoNode::exitClass. */
  static void exitClass();

protected:
  /** Destructor */
  virtual ~SoViewport();
};

#endif /* _SO_VIEWPORT_H_ */
