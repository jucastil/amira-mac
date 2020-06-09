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


#ifndef  _SO_HANDLE_EVENT_ACTION_
#define  _SO_HANDLE_EVENT_ACTION_

#include <Inventor/SbViewportRegion.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/actions/SoRayPickAction.h>

class SoEvent;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoHandleEventAction
//
//  Event handling action. This traverses a graph looking for a node
//  or nodes interested in a particular event.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Allows nodes in a graph to receive input events.
 * 
 * @ingroup actions
 * 
 * @DESCRIPTION
 *   This class is used to allow nodes in a scene graph to handle input events. It is
 *   usually invoked from a component derived from SoWinRenderArea when the component
 *   receives a window system event.
 *   
 *   Manipulator, dragger and selection nodes respond to and process events. Most
 *   other group nodes just pass the event to their children, while most other nodes
 *   simply ignore the action entirely. Once a node has indicated to the action that
 *   it has handled the event, traversal stops.
 *   
 *   A node that handles an event can also grab future events. Once it has done so,
 *   all events will be sent directly to that node, with no traversal taking place,
 *   until the node releases the grab.
 *
 *   Sets: SoViewportRegionElement
 * 
 * @SEE_ALSO
 *    SoEvent,
 *    SoPickedPoint,
 *    SoRayPickAction
 * 
 * 
 */ 

class INVENTOR_API SoHandleEventAction : public SoAction {

  SO_ACTION_HEADER(SoHandleEventAction);

 public:
  /**
   * Constructor takes viewport region to use; this is needed to perform a pick
   * operation when requested.
   */
  SoHandleEventAction(const SbViewportRegion &viewportRegion);

  // Destructor
#ifndef HIDDEN_FROM_DOC
  virtual ~SoHandleEventAction();
#endif // HIDDEN_FROM_DOC

  /**
   * Sets current viewport region to use for action.
   */
  void                setViewportRegion(const SbViewportRegion &newRegion);


  /**
   * Returns current viewport region to use for action.
   */
  const SbViewportRegion &getViewportRegion() const   { return vpRegion; }


  /**
   * Sets the event being handled.
   */
  void                setEvent(const SoEvent *ev)     { event = ev; }
  /**
   * Returns the event being handled.
   */
  const SoEvent *     getEvent() const                { return event; }

  /**
   * Sets whether any node has yet handled the event.
   */
  void                setHandled()            { setTerminated(TRUE); }
  /**
   * Returns whether any node has yet handled the event.
   */
  SbBool              isHandled() const       { return hasTerminated(); }

  /**
   * Initiates grabbing of future events. All events will be sent to the given node
   * until the grab is released.
   */
  void                setGrabber(SoNode *node);
  /**
   * Releases the grab.
   */
  void                releaseGrabber()            { setGrabber(NULL); }
  /**
   * Returns the node that is currently grabbing events, or NULL if there is none.
   */
  SoNode *            getGrabber() const          { return eventGrabber; }

  /**
   * Sets the root node used for initiating a pick action for those nodes
   * that want to know what is under the cursor.
   */
  void                setPickRoot(SoNode *node);
  /**
   * Returns the root node used for initiating a pick action for those nodes
   * that want to know what is under the cursor.
   */
  SoNode *            getPickRoot() const             { return pickRoot; }

  /**
   * Sets the radius (in pixels) around the viewport-space point through which the ray
   * passes when doing ray picking. Default is 5 pixels. Ray picking is performed when 
   * getPickedPoint() is called.
   *
   * @B Note: @b By default the pick radius set here is only used when testing the ray 
   * against lines and points.  To enable pick radius for triangle based geometry use the
   * enableRadiusForTriangles() method.
   */
  void                setPickRadius(float radiusInPixels) 
    { pickAct->setRadius(radiusInPixels); }

  /** 
   * Returns the radius (in pixels) around the viewport-space point through which the ray
   * passes when doing ray picking
   */
  float               getPickRadius() const
    { return pickAct->getRadius(); }

   /** 
   * Enable pick radius for triangle-based shapes.
   *
   * If TRUE, the radius of the ray specified by setPickRadius()
   * is taken in account when checking for a ray intersection with 
   * triangle-based shapes (e.g. SoIndexedFaceSet).
   * Otherwise, the pick radius for these shapes is 1 pixel regardless of
   * the specified pick radius.  Default is FALSE for performance.
   */
  void enableRadiusForTriangles(SbBool flag);

  /**
   * Returns the frontmost object hit (as an SoPickedPoint) by performing a pick
   * based on the mouse location specified in the event for which the action is being
   * applied. The first time this is called for a particular event, an
   * SoRayPickAction is applied to find this object; subsequent calls for the same
   * event return the same information. The storage for the picked point remains
   * valid as long as the action is not re-applied or deleted.
   */
  const SoPickedPoint *getPickedPoint();

  /**
   * Returns a list of objects intersected by a picking operation, sorted from
   * nearest to farthest.
   */
  const SoPickedPointList &getPickedPointList();

 SoEXTENDER public:
  /**
   * Set the SoPickedPoint object that will be returned by getPickedPoint.
   * Useful in some special cases where a pick operation has already been
   * done and the picked point is known.  Avoids doing the pick operation
   * again.  In other words, events will be processed as if the specified
   * point had been picked.  Reset the picked point by calling with NULL.
   */
  void                setPickedPoint( SoPickedPoint *point = NULL );

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  // Initiates action on graph
  virtual void        beginTraversal(SoNode *node);

 private:
  const SoEvent       *event;         // Event being handled
  SoNode              *pickRoot;      // Root node for initiating picking
  SoPickedPoint       *pickedPoint;   // PickedPoint from last pick
  SbBool              pickValid;      // Whether last pick is still valid
  SbBool              usedPickAll;    // TRUE if last pick used pickAll=TRUE
  SoRayPickAction     *pickAct;       // Pick action
  SoNode              *eventGrabber;  // Event grabber - gets all events
  SbViewportRegion    vpRegion;       // Current viewport region
  SbBool              pickedPtSet;    // TRUE if picked pt was set by app

};

#endif /* _SO_HANDLE_EVENT_ACTION_ */

