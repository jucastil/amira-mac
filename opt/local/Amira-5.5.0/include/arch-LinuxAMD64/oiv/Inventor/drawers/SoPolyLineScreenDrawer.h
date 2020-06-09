/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thibaut Andrieu (Jan 2011)
**=======================================================================*/

#if !defined _SO_POLY_LINE_SCREEN_DRAWER_H_
#define _SO_POLY_LINE_SCREEN_DRAWER_H_

#include <Inventor/drawers/SoScreenDrawer.h>
#include <Inventor/fields/SoSFUInt32.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoSFBool.h>

/**
 * @VSGEXT Interactively draw a polyline in normalized screen space.
 *
 * @ingroup drawers
 *
 * @DESCRIPTION
 *   This class is a base class used to allow the user to dynamically draw 
 *   line-based shapes (lasso, circle, rectangle, ...) on screen.  The
 *   geometry is defined in normalized screen space ([-1, 1]x[-1, 1]). 
 *   
 *   Sub-classes can implement the onMouseDown, onMouseMove, etc... methods, 
 *   to add and edit points. 
 *
 *   A callback can be specified when the line is finished (setFinishCallback()).
 *   This callback is called at the end of line finalization. 
 *
 *  @EXAMPLE
 *    The following example will write the number of generated points in stdout:
 *    \code
 *    // Callback definition
 *    SbBool myCallback ( SoHandleEventAction*, SoPolyLineScreenDrawer* lineDrawer, void* )
 *    {
 *      std::cout << "Line has: " << lineDrawer->point.getNum() << " points" << std::endl;
 *    }
 *
 *    // somewhere in your code:
 *    SoScreenDrawer* lineDrawer = new SoLassoScreenDrawer();
 *    lineDrawer->setFinishCallback ( myCallback );
 *    \endcode
 *
 * @FILE_FORMAT_DEFAULT
 *    PolyLineScreenDrawer {
 *    @TABLE_FILE_FORMAT
 *       @TR point        @TD []
 *       @TR color        @TD 1 0 0
 *       @TR simplificationThreshold      @TD 5
 *    @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *    SoEllipseScreenDrawer,
 *    SoLassoScreenDrawer,
 *    SoPolygonScreenDrawer,
 *    SoRectangleScreenDrawer,
 *    SoScreenDrawer
 */
class INVENTOR_API SoPolyLineScreenDrawer : public SoScreenDrawer 
{
  SO_NODE_HEADER( SoPolyLineScreenDrawer );

public:
  /** Constructor */
  SoPolyLineScreenDrawer();

  /**
   * Threshold (in pixels) used to simplify line when it is finished. 
   * A value of 0 means no simplification. Default value is 5 pixels. 
   */
  SoSFUInt32 simplificationThreshold;

  /** Color of line. Default value is red. */
  SoSFColor color;

  /** Points of line. Default is empty. */
  SoMFVec2f point;

  /** 
   * Close the line during display. Default is FALSE.
   * @warning This only affects the display.
   */
  SoSFBool isClosed;

  /** 
  * This is the declaration to use for mouse event callback functions.
  * Note: These callbacks are called just after the event occurs.
  *
  * @param action Action that generate the event.
  * @param drawer The ScreenDrawer node that called the function.
  * @param userData Optional pointer specified when the callback was set.
  *
  * @return If the callback handles the event it must return TRUE, else return 
  * FALSE.
  * [OIV-WRAPPER NAME{PolyLineCallback}]
  */
  typedef SbBool LineDrawerEventCallback( SoHandleEventAction* action, 
                                          SoPolyLineScreenDrawer* drawer, 
                                          void* userData );

  /** 
   * Specifies a callback to call when the line is finished. 
   * @param callback The callback method.
   * @param userData Parameter that will be given to callback.
   * Basically, when the line is finished, this drawer will call:
   * @code
   * callback ( action, this, userData );
   * @endcode 
   * [OIV-WRAPPER EVENT_NAME{Finish}]
   */
  virtual void setFinishCallback( LineDrawerEventCallback* callback, 
                                    void* userData = NULL );

  /** Convenience method to clear the points in the line. */
  inline void clear() { point.deleteValues(0); }

SoINTERNAL public:

  /** Register in database */
  static void initClass();

  /** Unregister from database */
  static void exitClass();

  /** Convenient method to add a point in screen space ([-1, 1]x[-1, 1]) */
  void addPoint( const SbVec2f& point );

  /** 
   *Convenient method to remove the id'th point. if id > point->getNum(), nothing is 
   * done. 
   */
  void removePoint( unsigned id );

  /** 
   *Convenient method to set new value for the id'th point. 
   * If id >= point->getNum(), nothing is done. 
   */
  void setPoint( unsigned id, const SbVec2f& newPoint);

  /** 
   * Finalize creation of line: simplify it and ensure it is CCW.
   * @warning The finalized line is not closed (first point != last point). 
   */
  void finalize( SoHandleEventAction* action );

protected:

  /** Destructor */
  virtual ~SoPolyLineScreenDrawer();

private:

  /** Return distance from P to (AB) line*/
  static float getDistance( const SbVec2f& P, const SbVec2f& A, const SbVec2f& B );

  /** Return oriented angle between 2 vectors in [-PI, PI]. */
  static float getAngle( const SbVec2f& v1, const SbVec2f& v2 );

  /** simplify the specified polyline using specified epsilon. */
  static void simplify( std::vector<SbVec2f>& polyline, float epsilon );

   /** Return true if line is CCW. */
  static bool isCCW( const std::vector<SbVec2f>& polyline );

  /** Make specified polyline line in CCW order. */
  static void makeCCW( std::vector<SbVec2f>& polyline );

private:

  /** Root of scenegraph that contains the line. */
  SoSeparator* m_lineRoot;

  // Engine used to convert from MFVec2 to MFVec3. it is used only internally by 
  // this class to draw line in screen space and should not be used by everyone 
  // else, so it is defined in in SoPolyLineScreenDrawer.cxx file.

  /** Engine used to convert from MFVec2 to MFVec3. */
  class MFVec2ToMFVec3;
  /** Engine used to convert from MFVec2 to MFVec3. */
  MFVec2ToMFVec3* m_vec2ToVec3;

  /** Callback called when the line is finalized. */
  LineDrawerEventCallback* m_finalizeCallback;

  /** User datas given the m_finalizeCallback. */
  void* m_finalizeCallbackUserData;

};


#endif // _SO_POLY_LINE_SCREEN_DRAWER_H_
