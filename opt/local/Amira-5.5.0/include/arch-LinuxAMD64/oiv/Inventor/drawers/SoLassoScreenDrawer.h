/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thibaut Andrieu (Jan 2011)
**=======================================================================*/

#if !defined _SO_LASSO_SCREEN_DRAWER_H_
#define _SO_LASSO_SCREEN_DRAWER_H_

#include <Inventor/drawers/SoPolyLineScreenDrawer.h>

/** 
 * @VSGEXT Interactively draw a lasso in normalized screen space.
 *
 * @ingroup drawers
 *
 * @DESCRIPTION
 *   This class can be used to interactively draw a lasso (freeform shape) on screen.
 *
 *   When the lasso is finished, the LineDrawerEventCallback is called.
 *   (see SoPolyLineScreenDrawer::setFinishCallback ).
 *
 *   The line color and simplification threshold are specified by
 *   fields in the parent class SoPolylineScreenDrawer.
 *
 * @USAGE
 *    Press left mouse and drag to draw the lasso. @BR
 *    Release to finish the lasso. @BR
 *    Press Escape to cancel construction of the lasso.
 *
 * @FILE_FORMAT_DEFAULT
 *    LassoScreenDrawer {
 *    @TABLE_FILE_FORMAT
 *       @TR point        @TD []
 *       @TR color        @TD 1 0 0
 *       @TR simplificationThreshold      @TD 2
 *       @TR isClosed     @TD false
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *    SoEllipseScreenDrawer,
 *    SoPolyLineScreenDrawer,
 *    SoPolygonScreenDrawer,
 *    SoRectangleScreenDrawer
 */
class INVENTOR_API SoLassoScreenDrawer : public SoPolyLineScreenDrawer 
{
  SO_NODE_HEADER( SoLassoScreenDrawer );

public:
  /** Constructor */
  SoLassoScreenDrawer();

SoINTERNAL public:

  /** Register in database */
  static void initClass();

  /** Unregister from database */
  static void exitClass();

SoEXTENDER_Documented protected:

  /** Called when key down. Finish lasso. */
  virtual void onKeyDown( SoHandleEventAction* action );

  /** Called when user click. Start a new lasso. */
  virtual void onMouseDown( SoHandleEventAction* action );

  /** 
   * Called when the mouse is dragging. Append the current mouse position to 
   * drawing lasso. 
   */
  virtual void onMouseDragging( SoHandleEventAction* action );

  /** Called when user release the mouse button. Finish the lasso. */
  virtual void onMouseUp( SoHandleEventAction* action );

protected:

  /** Destructor */
  virtual ~SoLassoScreenDrawer();

private:

  /** Finalize the lasso: ensure line have 2 points, remove duplicated points, etc... */
  void finalizeLasso( SoHandleEventAction* action );

private:

  /** Position of last added point (in px). Used to avoid add point every pixels. */
  SbVec2s m_lastAddedPoint;

};


#endif // _SO_LASSO_SCREEN_DRAWER_H_
