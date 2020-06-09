/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thibaut Andrieu (Jan 2011)
**=======================================================================*/

#if !defined _SO_ELLIPSE_SCREEN_DRAWER_H_
#define _SO_ELLIPSE_SCREEN_DRAWER_H_


#include <Inventor/drawers/SoPolyLineScreenDrawer.h>
#include <Inventor/fields/SoSFEnum.h>

/**
 * @VSGEXT Interactively draw an ellipse in normalized screen space.
 *
 * @ingroup drawers
 *
 * @DESCRIPTION
 *   This class can be used to interactively draw an ellipse on screen.
 *
 *   When the ellipse is finished, the LineDrawerEventCallback is called.
 *   (see SoPolyLineScreenDrawer::setFinishCallback ).
 *
 *   The line color and simplification threshold are specified by
 *   fields in the parent class SoPolylineScreenDrawer.
 *
 *   The ellipse can be specified by the 2 corners of its bounding box or 
 *   by its center and one corner of its bounding box (see #CreationMethod).
 *
 * @USAGE
 *   Press and drag left mouse to draw the ellipse. @BR
 *   Release to finish the ellipse. @BR
 *   Press Escape to cancel construction of the ellipse.
 *
 * @FILE_FORMAT_DEFAULT
 *    EllipseScreenDrawer {
 *    @TABLE_FILE_FORMAT
 *       @TR point        @TD []
 *       @TR color        @TD 1 0 0
 *       @TR simplificationThreshold      @TD 2
 *       @TR isClosed     @TD true
 *       @TR method       @TD CORNER_CORNER
 *       @TR nbPoint      @TD 32
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *    SoLassoScreenDrawer,
 *    SoPolyLineScreenDrawer,
 *    SoPolygonScreenDrawer,
 *    SoRectangleScreenDrawer,
 */
class INVENTOR_API SoEllipseScreenDrawer : public SoPolyLineScreenDrawer 
{
  SO_NODE_HEADER( SoEllipseScreenDrawer );

public:
  /** Constructor */
  SoEllipseScreenDrawer();

  /** 
   * Methods to create ellipse. 
   */
  enum CreationMethod
  {
    /** Initial point is a corner, current point is a corner. */
    CORNER_CORNER,
    /** Initial point is the center, current point is a corner. */
    CENTER_CORNER
  };

  /** Method to create ellipse.
   *  Use enum #CreationMethod. Default is CORNER_CORNER. */
  SoSFEnum method;

  /** Number of points in generated ellipse. 
   *  Default is 32. Must be > 0. 
   */
  SoSFUInt32 nbPoint;

SoINTERNAL public:

  /** Register in database */
  static void initClass();

  /** Unregister from database */
  static void exitClass();

SoEXTENDER_Documented protected:

  /** Finish ellipse. */
  virtual void onKeyDown( SoHandleEventAction* action );

  /** Update ellipse. */
  virtual void onMouseDragging( SoHandleEventAction* action );

  /** Start creation of new ellipse. */
  virtual void onMouseDown( SoHandleEventAction* action );

  /** Finish creation of ellipse. */
  virtual void onMouseUp( SoHandleEventAction* action );

  /** Is an ellipse is creating. */
  inline bool isCreating() const { return m_initPoint[0] != -1 && m_initPoint[1] != -1; }

protected:

  /** Destructor. */
  virtual ~SoEllipseScreenDrawer();

private:

  /** 
   * Retrieve ellipse parameters from current method and current initPoint. 
   * @param currentPoint The current mouse move position.
   * @param xRadius half ellipse x axis.
   * @param yRadius half ellipse y axis.
   * @param center ellipse center.
   */
  void getEllipseParameters( const SbVec2f& currentPoint, 
    float& xRadius, 
    float& yRadius, 
    SbVec2f& center ) const;

  /** 
   * Initial point of ellipse (usually the mouseDown event). See #CreationMethod.
   * If (-1, -1), ellipse is not creating 
   */
  SbVec2f m_initPoint;

};


#endif // _SO_ELLIPSE_SCREEN_DRAWER_H_
