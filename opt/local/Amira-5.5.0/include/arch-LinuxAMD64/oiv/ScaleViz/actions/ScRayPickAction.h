/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Ludovic PEINE (Jun 2007)
**=======================================================================*/


#ifndef  SC_RAY_PICK_ACTION
#define  SC_RAY_PICK_ACTION

#include <Inventor/actions/SoRayPickAction.h>

class ScRayPickAction;
class SoPath;

typedef void ScRayPickCallback( void*, ScRayPickAction* );

/**
 * @SCVEXT Defines a distributed ray pick action.
 * 
 * @ingroup ScaleVizAction
 * 
 * @DESCRIPTION
 * 
 * The ScRayPickAction class provides a simple way to distribute an SoRayPickAction across a cluster. 
 *
 * Several distribution modes are available:
 *    - LOCAL_ONLY: action is only applied by the application. 
 *    - CLUSTER_ONLY: action is only applied by the OIRUs. 
 *    - ALL: both application and OIRUs apply the given action.
 *
 * When OIRUs are involved (i.e., in CLUSTER_ONLY and ALL modes), they apply the action 
 * on their own part of the scene graph. The application gets back the result 
 * via the callback defined by the user.
 *
 * This class can be used in all compositing modes (flat, tile, depth, and local compositing).
 *
 * @SEE_ALSO
 *    SoRayPickAction
 *
 *
 */

class SCALEVIZ_API ScRayPickAction : public SoRayPickAction
{
  SO_ACTION_HEADER(ScRayPickAction);

public:

  /**
   * Constructor.
   *
   * @param viewportRegion  viewport region to use for picking 
   * @param distribMode     specify the way the action may be distributed
   * @param callback        pointer to the function used to get the result of the action
   * @param userData        pointer to user data
   */
  ScRayPickAction(
    const SbViewportRegion &viewportRegion,
    SoAction::DistribMode distribMode = SoAction::LOCAL_ONLY,
    ScRayPickCallback* callback = NULL,
    void* userData = NULL
  );

  /**
   * Destructor
   */
#ifndef HIDDEN_FROM_DOC
  ~ScRayPickAction();
#endif // HIDDEN_FROM_DOC

  /**
   *    Applies action to the graph rooted by a node.
   */
  virtual void apply( SoNode *node );

 /**
   * Sets a world-space ray along which to pick. The ray is defined as a world space
   * starting point and direction vector. The direction vector will be normalized
   * automatically. The last two arguments specify optional near and far plane 
   * clipping during the pick operation. These values are distances from the start 
   * point along the direction vector, similar to nearDistance and farDistance in 
   * SoCamera. A negative distance (such as the default values) means disable 
   * clipping to that plane.
   *
   * NOTE: You can use this method or the #setPoint / #setNormalizedPoint methods. 
   * Whichever method you call last is the one that takes effect.
   */
  void setRay( 
    const SbVec3f &rayStart,
    const SbVec3f &rayDirection,
    float nearDistance = -1,
    float farDistance = -1 );

 /**
   * Sets a world-space ray along which to pick in the the same way as function defined
   * above, but allows you to set a view angle value. Alternatively, you can use
   * the setRay method above and then specify the view angle
   * using the environment variable OIV_SET_RAY_PRECISION. See SoPreferences.
   */
  void setRay( 
    float fovy,
    const SbVec3f &rayStart,
    const SbVec3f &rayDirection,
    float nearDistance = -1,
    float farDistance = -1 );

  /**
   * Sets the viewport-space point through which the ray passes, starting at the
   * camera's viewpoint. Viewport coordinates range from (0,0) at the lower left to
   * (width-1,height-1) at the upper right.
   *
   * NOTE: You can use this method or the #setNormalizedPoint / #setRay methods. 
   * Whichever method you call last is the one that takes effect.
   */
  void setPoint( const SbVec2s &viewportPoint );

  /**
   *  Float version of #setPoint(). It can be used when a desktop is magnified
   *  on a wall of screens when using ScaleViz in correlation with a tracker
   *  device calibrated for this wall.
   */
  void setPoint( const SbVec2f &viewportPoint );

  /**
   * Sets the viewport point in normalized coordinates, which range from (0,0) at the
   * lower left to (1,1) at the upper right.
   *
   * NOTE: You can use this method or the #setPoint / #setRay methods. 
   * Whichever method you call last is the one that takes effect.
   */
  void setNormalizedPoint( const SbVec2f &normPoint );

  /**
   * Returns the picked point normal.
   */
  SbVec3f getppNormal();

  /**
   * Returns the picked point. 
   */
  SbVec3f getppPoint();

  /**
   * Returns the picked point path.
   */
  SoPath* getppPath();

  /**
   * Returns 0 if nothing has been picked. Otherwise, returns 1.
   */
  SbBool isValidPp();

  SoINTERNAL public:

  typedef enum ScRayDefinition
  {
    UNDEFINED,
    RAY,
    POINT,
    NORMPOINT
  } ScRayDefinition_t;

  static void initClass();
  static void exitClass();
  virtual bool mustTraverseDepth() { return true; }

  // Retrieve how the ray has been defined
  ScRayDefinition getRayDefinition() { return m_rayDefinition; }

  // Retrieve ray properties
  void getRay( SbVec3f &rayStart, SbVec3f &rayDirection, float &nearDistance, float &farDistance );

  /**
   * Returns the normalized viewport point through which the ray passes.
   * Normalized viewport coordinates range from (0,0) at the lower left to
   * (1,1) at the upper right.
   */
  void getNormalizedPoint( SbVec2f &normPoint );

  /**
   * Returns the viewport-space point through which the ray passes.
   * Viewport coordinates range from (0,0) at the lower left to
   * (width-1,height-1) at the upper right.
   */
  void getPoint( SbVec2s &point );

  /**
   *  Float version of #getPoint(). It can be used when a desktop is magnified
   *  on a wall of screens when using ScaleViz in correlation with a tracker
   *  device calibrated for this wall.
   */
  void getPoint( SbVec2f &point );
  
  // Retrieve the fovy set for the action
  float getFov();

  // Return true if the user set the fovy manually
  bool isFovSet();

  // Method used to set the picked point properties of an action
  void setPickedPoint( SbVec3f ppPoint, SbVec3f ppNormal, SoPath* ppPath, SbBool isValidPp );


private:

  // Pointer to the user callback
  ScRayPickCallback* m_rayPickCallback;

  // Pointer to user data
  void* m_data;

  SbVec3f m_rayStart;                 // ray starting point ( world-space )
  SbVec3f m_rayDirection;             // ray direction
  SbVec2f m_normPoint;                // normalized point
  SbVec2f m_rayPoint;                 // ray point ( viewport-space )
  float m_nearDst;                    // near plane clipping
  float m_farDst;                     // far plane clipping
  ScRayDefinition m_rayDefinition;    // how the ray has been defined
  SbVec3f m_ppPoint;                  // coordinate of picked point
  SbVec3f m_ppNormal;                 // normal of picked point
  SoPath* m_ppPath;                   // SoPath to picked point
  SbBool m_isValidPp;                  // flag to know if something got picked
  float m_fovy;                       // define the field of view angle
  bool m_bFovSet;                     // Indicates if the fov has been changed by user
};

// INLINE METHODS
/*************************************************************************/
inline void
ScRayPickAction::setPickedPoint( SbVec3f ppPoint, SbVec3f ppNormal, SoPath* ppPath, SbBool isValidPp )
{
  m_ppPoint = ppPoint;
  m_ppNormal = ppNormal;
  m_ppPath = ppPath;
  m_isValidPp = isValidPp;
}

/*************************************************************************/
inline SbVec3f
ScRayPickAction::getppNormal()
{
  return m_ppNormal;
}

/*************************************************************************/
inline SbVec3f
ScRayPickAction::getppPoint()
{
  return m_ppPoint;
}

/*************************************************************************/
inline SoPath* 
ScRayPickAction::getppPath()
{
  return m_ppPath;
}

/*************************************************************************/
inline SbBool
ScRayPickAction::isValidPp()
{
  return m_isValidPp;
}

/*************************************************************************/
inline float
ScRayPickAction::getFov()
{
  return m_fovy;
}

inline bool
ScRayPickAction::isFovSet()
{
  return m_bFovSet;
}
#endif // SC_RAY_PICK_ACTION

/**/
