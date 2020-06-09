/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thibaut Andrieu (Jan 2011)
**=======================================================================*/

#if !defined _SO_POLYGON_SCREEN_DRAWER_H_
#define _SO_POLYGON_SCREEN_DRAWER_H_

#include <Inventor/drawers/SoPolyLineScreenDrawer.h>

/** 
 * @VSGEXT Interactively draws a polygon in normalized screen space.
 *
 * @ingroup drawers
 *
 * @DESCRIPTION
 *   This class can be used to interactively draw a polygon on screen.
 *
 *   When the polygon is finished, the LineDrawerEventCallback is called.
 *   (see SoPolyLineScreenDrawer::setFinishCallback ).
 *
 *   The line color and simplification threshold are specified by
 *   fields in the parent class SoPolylineScreenDrawer.
 *
 * @USAGE
 *    Left click to add a point. @BR
 *    Double-click or press enter to finish the polygon.  @BR
 *    Press Escape to cancel creation of the polygon.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PolygonScreenDrawer {
 *    @TABLE_FILE_FORMAT
 *       @TR point        @TD []
 *       @TR color        @TD 1 0 0
 *       @TR simplificationThreshold      @TD 2
 *       @TR isClosed     @TD true
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *    SoEllipseScreenDrawer,
 *    SoLassoScreenDrawer,
 *    SoPolyLineScreenDrawer,
 *    SoRectangleScreenDrawer
 */
class INVENTOR_API SoPolygonScreenDrawer : public SoPolyLineScreenDrawer 
{
  SO_NODE_HEADER( SoPolygonScreenDrawer );

public:
  /** Constructor */
  SoPolygonScreenDrawer();

SoINTERNAL public:

  /** Register in database */
  static void initClass();

  /** Unregister from database */
  static void exitClass();

SoEXTENDER_Documented protected:

  /** Finish polygon line. */
  virtual void onKeyDown( SoHandleEventAction* action );

  /** Move last polygon point. */
  virtual void onMouseMove( SoHandleEventAction* action );

  /** Add a point to polygon. */
  virtual void onMouseDown( SoHandleEventAction* action );

  /** Finish creation of polygon. */
  virtual void onMouseDblClick( SoHandleEventAction* action );

protected:

  /** Destructor */
  virtual ~SoPolygonScreenDrawer();

private:

  /** Is a polyline is creating. */
  inline bool isCreating() const { return m_lastAddedPoint[0] != -1 && m_lastAddedPoint[1] != -1; }

  /** Last added point, in px. If (-1, -1), polyline is not creating. */
  SbVec2s m_lastAddedPoint;

};


#endif // _SO_POLYGON_SCREEN_DRAWER_H_
