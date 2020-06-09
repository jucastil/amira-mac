/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Fabien ARNAUD (Jul 1997)
**=======================================================================*/


#ifndef _SO_XT_COLLISION_VIEWER_
#define _SO_XT_COLLISION_VIEWER_


//------------------------------------------------------------------------------
// Includes
#include <Inventor/Win/SoWinBeginStrict.h>

#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/collision/SoIntersectionDetectionAction.h>

//------------------------------------------------------------------------------
// Types declaration
class SoWinCollisionViewer;
class SoWinViewer;
class SoIndexedLineSet;
class SoVertexProperty;
class SoCamera;
class SoSceneManager;


//------------------------------------------------------------------------------
// Types definition
/** [OIV-WRAPPER NAME{CollisionCB}] */
typedef void SoWinCollisionViewerCB 
(void *userData, SoWinCollisionViewer *collisionViewer);



/**
 * @VSGEXT Class to manage collisions between the camera and the scene.
 * 
 * @ingroup collision
 * 
 * @DESCRIPTION
 *   This class is used to constrain a viewer, preventing the viewer's camera from
 *   colliding with the objects in the scene. It overrides the RenderCallback on the
 *   viewer that it's attached to.
 *   
 *   The programmer can define the maximum distance between the camera and the
 *   objects.
 *   
 *   When Z-buffer optimization is enabled, the algorithm looks at the Z-buffer to see
 *   if there is an object in front of the camera when the user moves forward, and an
 *   SoIntersectionDetectionAction when the user moves backward.
 *   
 *   NOTE: This class is @I not @i a viewer.
 * 
 * @SEE_ALSO
 *    SoCollisionManager,
 *    SoIntersectionDetectionAction
 * 
 * 
 */ 

class INVENTORW_API SoWinCollisionViewer
{

public :

  /**
   * Constructor.
   */
  SoWinCollisionViewer(SoWinViewer *viewer);
  /**
   * Destructor.
   */
  ~SoWinCollisionViewer();

  /**
   * Gets the original viewer.
   */
  SoWinViewer *getViewer();
 
  /**
   * Sets the distance between the camera and the objects.
   */
  void setDistance(float distance);
  /**
   * Gets the distance between the camera and the objects.
   */
  float getDistance() const;

  /**
   * Sets the number of steps to be used in the collision computation. The
   * default number of steps is 4. The minimum value is 2.
   */
  void setNumSteps(int num_steps);
  /**
   * Gets the number of steps to be used in the collision computation.
   */
  int getNumSteps() const; 

  /**
   * Sets the collision detection active flag. The default value is TRUE.
   */
  void setCollisionDetection(SbBool value = TRUE);
  /**
   * Gets the collision detection active flag.
   */
  SbBool getCollisionDetection() const;
 
  /**
   * Sets the Z buffer optimization active flag. The default value is TRUE.
   *
   * Also sets the useZBufferOnly flag.  When this flag is TRUE, the
   * geometric collision detection algorithm is never used.  Therefore there
   * is no collision check when the camera is moving backward, but this may
   * be desireable for large scenes when this check is too slow.
   */
  void setZBufferOptimization(SbBool value = TRUE, SbBool useZBufferOnly = FALSE);
  /**
   * Gets the Z buffer optimization active flag. 
   */
  SbBool getZBufferOptimistation() const;

  /**
   * Adds callback. This callback is called when a collision occurs
   * between the camera and the scene.
   * [OIV-WRAPPER EVENT_NAME{Collision}]
   */
  void addCallback(SoWinCollisionViewerCB* f, void* ud = NULL);
  /**
   * Removes callback.
   * [OIV-WRAPPER EVENT_NAME{Collision}]
   */
  void removeCallback(SoWinCollisionViewerCB* f, void* ud = NULL);


private : 

  // General data --------------------------------------------------------------
  SoWinViewer*                    m_viewer;
  SbBool                         m_collision_detection;    // On or off ?
  SbBool                         m_zbuffer_optimization;
  SbBool                         m_use_zbuffer_only;
  short                          m_num_steps;              // default 4.
  float                          m_distance;               // default 0.
  SoCallbackList                 m_cb_list;

  // Data about frames ---------------------------------------------------------
  SoCamera*                      m_old_camera;
  short                          m_old_width;
  short                          m_old_height;
  short                          m_old_min_width_height;
  SbBool                         m_old_data_are_valid;
  SoCamera*                      m_new_camera;
  short                          m_new_width;
  short                          m_new_height;
  short                          m_new_min_width_height;

  // Alternate algorithm data --------------------------------------------------
  SbBool                         m_slow_collision;
  SbMatrix                       m_old_matrix;
  SoIntersectionDetectionAction* m_slow_collision_detection_action;
  SoIndexedLineSet*              m_indexed_line_set;
  SoVertexProperty*              m_vertex_property;
  SbBool                         m_segment_line_is_inserted;

  // Computing functions -------------------------------------------------------
  void save();
  void restore();
  void updateInternalData();
  SbBool checkZBufferValue(int x, int y, float z);
  SbBool isThisMoveCorrect();
  SbBool toZBufferCoordinateSpace (float x, float y, float z,
                                   short &x_in_zbuffer,
                                   short &y_in_zbuffer,
                                   float &z_in_zbuffer);
  void addSegmentLineForSlowAlgorithm(float x1, float y1, float z1,
                                      float x2, float y2, float z2);
  void removeSegmentLineForSlowAlgorithm();
  float linearConvertion(float value,
                         float min, float max, float newMin, float newMax);
  SoIntersectionDetectionAction::Resp onSlowCollision ();
  SbBool slowFilter (const SoPath* path1, const SoPath* path2);
  void onRender (void);
  SoCallbackAction::Response onFoundCamera (SoCallbackAction *action,
                                            const SoNode *node);

  // Real callbacks ------------------------------------------------------------
  static SoIntersectionDetectionAction::Resp 
  onSlowCollisionCB(void *ud, 
                    const SoIntersectingPrimitive *, 
                    const SoIntersectingPrimitive *) {
    return ((SoWinCollisionViewer *) ud)->onSlowCollision ();
  }

  static SbBool 
  slowFilterCB(void *ud, const SoPath *p1, const SoPath *p2) {
    return ((SoWinCollisionViewer *)ud)->slowFilter (p1, p2);
  }

  static void 
  onRenderCB(void *ud, SoSceneManager *) {
    ((SoWinCollisionViewer *)ud)->onRender ();
  }

  static SoCallbackAction::Response 
  onFoundCameraCB(void *ud, 
                  SoCallbackAction *action,
                  const SoNode *node) {
    return ((SoWinCollisionViewer*) ud)->onFoundCamera (action, node);
  }


};

#include <Inventor/Win/SoWinEndStrict.h>

#endif//_SO_XT_COLLISION_VIEWER_

