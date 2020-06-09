/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thibaut Andrieu (Jan 2011)
**=======================================================================*/

#if !defined _SO_SCREEN_DRAWER_H_
#define _SO_SCREEN_DRAWER_H_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/SbVec.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/SbBox.h>

class SoHandleEventAction;
class SoOrthographicCamera;
class SoAnnotation;

/** 
 * @VSGEXT Base class to draw a scene graph in screen space.
 *
 * @ingroup drawers
 * 
 * @DESCRIPTION
 *   This node displays the scene graph specified by #scenegraph field in screen space 
 *   normalized in the range ([-1, 1]x[-1, 1]x[-1, 1]).
 *   It is automatically rendered using an orthographic camera.
 *
 *   Classes derived from SoScreenDrawer are normally used to implement dynamically
 *   drawing a 2D shape, for example a rectangle, in response to mouse events.
 *
 *   The convenient onMouseDown(), onMouseMove(), ... methods can be 
 *   implemented by sub-classes to customize behaviors for specific events, but the
 *   application can also reimplement the handleEvent() method to handle any event.
 *
 *   There should be only one of this node in the sceneGraph (to avoid conflicts 
 *   in mouse events).
 *
 * @FILE_FORMAT_DEFAULT
 *    ScreenDrawer {
 *    @TABLE_FILE_FORMAT
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *    SoAnnotation
 *    SoPolyLineScreenDrawer
 *    SoLassoScreenDrawer
 */
class INVENTOR_API SoScreenDrawer : public SoNode
{
  SO_NODE_HEADER( SoScreenDrawer );

public:

  /** Scene graph to render. */
  SoSFNode sceneGraph;

  /** Constructor */
  SoScreenDrawer();

SoINTERNAL public:

  /** Register in database */
  static void initClass();

  /** Unregister from database */
  static void exitClass();

SoEXTENDER public:
  /**
  * Traversal routine for SoHandleEventAction - this will call
  * action->setHandled() if the event is handled
  */
  virtual void handleEvent( SoHandleEventAction* action );

  // Implement actions to redirect to m_root

  /** @copydoc SoNode::doAction */
  virtual void doAction( SoAction *action );

  /** @copydoc SoNode::callback */
  virtual void callback( SoCallbackAction *action );

  /** @copydoc SoNode::GLRender */
  virtual void GLRender( SoGLRenderAction *action );

  /** @copydoc SoNode::rayPick */
  virtual void rayPick( SoRayPickAction *action );

  /** @copydoc SoNode::getBoundingBox */
  virtual void getBoundingBox( SoGetBoundingBoxAction *action );

  /** @copydoc SoNode::getPrimitiveCount */
  virtual void getPrimitiveCount( SoGetPrimitiveCountAction *action );

SoEXTENDER_Documented protected:

  /** Called on keyDown event. Should be implemented by sub-classes. */
  virtual void onKeyDown( SoHandleEventAction* ) {};

  /** Called on mouseDown event. Should be implemented by sub-classes. */
  virtual void onMouseDown( SoHandleEventAction* ) {};

  /** Called on mouseMove event. Should be implemented by sub-classes. */
  virtual void onMouseMove( SoHandleEventAction* ) {};

  /** Called on double click event. Should be implemented by sub-classes. */
  virtual void onMouseDblClick( SoHandleEventAction* ) {};

  /** Called on mouseDrag event. Should be implemented by sub-classes. */
  virtual void onMouseDragging( SoHandleEventAction* ) {};

  /** Called on mouseUp event. Should be implemented by sub-classes. */
  virtual void onMouseUp( SoHandleEventAction* ) {};

  /** Returns last mouse down position in pixels. */
  inline const SbVec2f& getLastMouseDown() const { return m_lastMouseDown; }

protected:

  /** Destructor */
  virtual ~SoScreenDrawer();

  /** catch some fields changes */
  virtual void notify( SoNotList *list );

private:

  /** 
   * Root of sceneGraph to render. Contains an orthographic camera and the user 
   * sceneGraph. All actions will be redirected to this node.
   */
  SoAnnotation* m_root;

  /** 
   * Node containing input user scene graph. It has at most one child (sceneGraph) and
   * its parent is m_root.
   */
  SoSeparator* m_userGraphContainer;

  /** Orthographic normalized camera (viewProj matrix is identity) */
  SoOrthographicCamera* m_camera;

  /** true if left mouse button is currently down. */
  bool m_mouseLeftDown;

  /** Last mouse down position in pixel. */
  SbVec2f m_lastMouseDown;

};


#endif // _SO_SCREEN_DRAWER_H_
