/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thibaut Andrieu (Apr 2011)
**=======================================================================*/

#if !defined _SO_RECTANGLE_SCREEN_DRAWER_H_
#define _SO_RECTANGLE_SCREEN_DRAWER_H_


#include <Inventor/drawers/SoPolyLineScreenDrawer.h>
#include <Inventor/fields/SoSFEnum.h>

/**
 * @VSGEXT Interactively draws a rectangle in normalized screen space.
 *
 * @ingroup drawers
 *
 * @DESCRIPTION
 *   This class can be used to interactively draw a rectangle on screen.
 *
 *   When the rectangle is finished, the LineDrawerEventCallback is called.
 *   (see SoPolyLineScreenDrawer::setFinishCallback ).
 *
 *   The line color and simplification threshold are specified by
 *   fields in the parent class SoPolylineScreenDrawer.
 *
 *   The rectangle can be specified by 2 corner points or by
 *   a center point and one corner point (see #CreationMethod).
 *
 * @USAGE
 *    Press left mouse and drag to draw the rectangle. @BR
 *    Release to finish it. @BR
 *    Press Escape to cancel.
 *
 * @FILE_FORMAT_DEFAULT
 *    RectangleScreenDrawer {
 *    @TABLE_FILE_FORMAT
 *       @TR point        @TD []
 *       @TR color        @TD 1 0 0
 *       @TR simplificationThreshold      @TD 2
 *       @TR isClosed     @TD true
 *       @TR method       @TD CORNER_CORNER
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *    SoEllipseScreenDrawer,
 *    SoLassoScreenDrawer,
 *    SoPolyLineScreenDrawer,
 *    SoPolygonScreenDrawer,
 */
class INVENTOR_API SoRectangleScreenDrawer : public SoPolyLineScreenDrawer 
{
  SO_NODE_HEADER( SoRectangleScreenDrawer );

public:
  /** Constructor */
  SoRectangleScreenDrawer();

  /** 
   * Methods to create rectangle. 
   */
  enum CreationMethod
  {
    /** Initial point is a corner, current point is a corner. */
    CORNER_CORNER,
    /** Initial point is the center, current point is a corner. */
    CENTER_CORNER
  };

  /** Method to create rectangle.
   *  Use enum #CreationMethod. Default is CORNER_CORNER. */
  SoSFEnum method;

SoINTERNAL public:

  /** Register in database */
  static void initClass();

  /** Unregister from database */
  static void exitClass();

SoEXTENDER_Documented protected:

  /** Finish rectangle. */
  virtual void onKeyDown( SoHandleEventAction* action );

  /** Update rectangle. */
  virtual void onMouseDragging( SoHandleEventAction* action );

  /** Start creation of new rectangle. */
  virtual void onMouseDown( SoHandleEventAction* action );

  /** Finish creation of rectangle. */
  virtual void onMouseUp( SoHandleEventAction* action );

  /** Is a rectangle creating. */
  inline bool isCreating() const { return m_initPoint[0] != -1 && m_initPoint[1] != -1; }

protected:

  /** Destructor. */
  virtual ~SoRectangleScreenDrawer();

private:

  /** 
   * Initial point of rectangle (usually the mouseDown event). See #CreationMethod.
   * If (-1, -1), rectangle is not creating 
   */
  SbVec2f m_initPoint;

};


#endif // _SO_RECTANGLE_SCREEN_DRAWER_H_
