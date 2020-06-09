/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Fabien ARNAUD (Jul 1997)
**=======================================================================*/


#ifndef _SO_COLLISION_MANAGER_
#define _SO_COLLISION_MANAGER_


//------------------------------------------------------------------------------
// Includes
#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>


//------------------------------------------------------------------------------
// Types declaration
class SoNode;
class SoGroup;
class SoPath;
class SoTransform;
class SoPrimitiveVertex;
class SoSensor;
class SoDragger;
class SoNodeSensor;
class SoFieldSensor;
class SoCallbackAction;


//------------------------------------------------------------------------------
// Types definition
/**
 * [OIV-WRAPPER NAME{FilterCollisionCB}]
 */
typedef SbBool SoFilterCollisionCB (void* userData,
                                    const SoPath* p1,
                                    const SoPath* p2);
/**
 * [OIV-WRAPPER NAME{BBoxCollisionCB}]
 */
typedef void SoBBoxCollisionCB (void* userData, 
                                const SoPath* p1, 
                                const SoPath* p2);

struct SoCollidingPrimitive {
  /** Primitive type */
  enum PrimitiveType {
    /** Segment */
    SEGMENT = 2,
    /** Line segment */
    LINE_SEGMENT = 2,
    /** Triangle */
    TRIANGLE = 3
  };
  /**
   * Path of the shape
   */ 
  SoPath*    path; 
  /**    
   * Type of primitive
   */
  PrimitiveType type;
  /**     
   *  Vertex of the primitive
   */
  SbVec3f    vertex [3];
};


/**
 * @VSGEXT Class to manage collisions.
 * 
 * @ingroup collision
 * 
 * @DESCRIPTION
 *   The SoCollisionManager class manages collisions, i.e., it controls the position
 *   of an object in a scene, preventing it from colliding with other objects in the
 *   scene.
 *   
 *   The collision manager references a scene, an object and a transformation. It can
 *   prevent collisions between the specified object and other objects within the
 *   scene. 
 *   
 *   It can use the actual primitives of the objects during the computation, or for
 *   faster performance, it may use their bounding boxes.
 *   
 *   When the referenced transformation changes, the collision manager looks for a
 *   collision between the bounding box of the object and the bounding boxes of
 *   objects within the scene. If a collision between the bounding boxes is detected,
 *   the algorithm can (depending on what the programmer specifies) compute a more
 *   precise intersection using the actual primitives of the object and/or the
 *   objects of the scene.
 *   
 *   The algorithm can call programmer-supplied \oivnetdoc delegates \else callbacks \endoivnetdoc when there is a
 *   collision between the bounding boxes, and when there is a collision between the
 *   primitives of the shapes.
 *   
 *   When there is a collision, the collision manager can "glue" the object on the
 *   scene. This refers to placing the object at the position just before the first
 *   collision that would occur along the transformation path. For example, if an
 *   object would collide with (intersect) a wall, the object would be placed
 *   directly against the wall. 
 * 
 * @SEE_ALSO
 *    SoIntersectionDetectionAction,
 *    SoWinCollisionViewer
 * 
 * 
 */ 

class INVENTOR_API SoCollisionManager
{

public :

  // Types definitions ---------------------------------------------------------
  /** Types definitions */
  enum Resp {
    /** Continue and call again for next colliding primitive */
    NEXT_PRIMITIVE,
    /** Continue and call again for next colliding shape */
    NEXT_SHAPE,
    /** Do not continue */
    ABORT    
  };

  /**
   * [OIV-WRAPPER NAME{CollisionCB}]
   * [OIV-WRAPPER-ARG IN,IN,IN]
   */
  typedef Resp SoCollisionCB (void* userData, 
                              const SoCollidingPrimitive* object,
                              const SoCollidingPrimitive* scene);
 
  /**
   * Constructor.
   * The specified @B scene @b must be the head of the path to the specified
   * @B object@b. 
   */
  SoCollisionManager(SoPath* object,
                     SoGroup* scene,
                     SoTransform* transform);
  /**
   * Destructor.
   */
  ~SoCollisionManager();

  /**
   * Sets the object that will be transformed.
   */
  void setObject (SoPath* object);

  /**
   * Returns the object that will be transformed.
   */
  SoPath* getObject () const;

  /**
   * Sets the scene the object is interacting with.
   */
  void setScene (SoGroup* scene);

  /**
   * Returns the scene the object is interacting with.
   */
  SoGroup* getScene () const;

  /**
   * Sets the transformation that will be watched.
   */
  void setTransform (SoTransform* transform);

  /**
   * Returns the transformation that will be watched.
   */
  SoTransform* getTransform () const;

  /**
   * Sets the gluing level. The larger the number, the more precise the check
   * for intermediate collisions, and the longer the computation will take. If this
   * level is set to 0, the collision manager will act as if the gluing flag was set
   * to FALSE, except the collision callbacks are called with a gluing flag of TRUE.
   * Default value is 1.
   */
  void setGluingLevel (unsigned int level);

  /**
   * Returns the gluing level.
   */
  unsigned int getGluingLevel() const;

  /**
   * Sets a flag indicating whether to use the object's bounding box instead
   * of the actual primitives when computing collisions. Default value is FALSE.
   */
  void setObjectBBoxOnly (SbBool flag = TRUE);

  /**
   * Returns a flag indicating whether to use the object's bounding box instead
   * of the actual primitives when computing collisions.
   */
  SbBool isObjectBBoxOnly () const;

  /**
   * Sets a flag indicating whether to use the bounding boxes of objects in
   * the scene instead of the actual primitives when computing collisions. Default
   * value is FALSE.
   */
  void setSceneBBoxOnly (SbBool flag = TRUE);

  /**
   * Returns a flag indicating whether to use the bounding boxes of objects in
   * the scene instead of the actual primitives when computing collisions.
   */
  SbBool isSceneBBoxOnly () const;

  /**
   * Sets a flag indicating that the collision manager should place the object
   * at the position just before the first collision that would occur along the
   * transformation path. For example, if an object would collide with (intersect) a
   * wall, the object would be placed directly against the wall. Default value is
   * FALSE.
   */
  void setGluing (SbBool flag = TRUE);

  /**
   * Returns a flag indicating whether the collision manager should place the object
   * at the position just before the first collision that would occur along the
   * transformation path.
   */
  SbBool isGluing () const;

  /**
   * Sets a flag to activate the collision manager, for instance, to tell it to watch
   * the transformation and start collision detection computations when the
   * transformation changes. Default value is TRUE.
   */
  void activate (SbBool flag = TRUE);

  /**
   * Returns a flag indicating whether the collision manager is activated. 
   */
  SbBool isActivated () const;

  /**
   * Sets the callback function called when an object shape collides with a scene
   * shape. If the callback function returns TRUE, the Collision Manager looks
   * forward for collisions; else, it aborts searching. If it is NULL, no filter is
   * applied.
   */
  void setFilterCallback (SoFilterCollisionCB* f, void* userData = NULL);

  /**
   * Adds bounding box collision callback.
   * Bounding box collision callbacks are called after the bounding box collision
   * detection and before real detection, allowing the programmer to change the
   * @B ObjectBBoxOnly @b and @B SceneBBoxOnly @b flags. The callback functions are
   * passed the paths of the two nodes whose bounding boxes are colliding.
   * [OIV-WRAPPER EVENT_NAME{BBoxCollision}]
   */
  void addBBoxCollisionCallback (SoBBoxCollisionCB* f, void* userData = NULL);

  /**
   * Removes bounding box collision callback.
   * [OIV-WRAPPER EVENT_NAME{BBoxCollision}]
   */
  void removeBBoxCollisionCallback (SoBBoxCollisionCB* f,
                                    void* userData = NULL);
  /**
   * Adds collision callback.
   * Collision callbacks are called when there is a collision. The callback functions
   * receive information about the primitives which collide. If the callback returns
   * NEXT_PRIMITIVE, it will be called for the two next colliding triangles or
   * segments; if it returns NEXT_SHAPE, it will be called for the two next colliding
   * shapes; if it returns ABORT, it will be called only if another transformation
   * generates a collision.
   * 
   * When the gluing flag is TRUE, the object and scene passed to the callback
   * function are NULL because there is no collision.
   * [OIV-WRAPPER EVENT_NAME{Collision}, EVENT_INVOKE_METHOD{InvokeCollisionEventDelegates}]
   */
  void addCollisionCallback (SoCollisionCB* f, void* userData = NULL);

  /**
   * Removes collision callback.
   * [OIV-WRAPPER EVENT_NAME{Collision}, EVENT_INVOKE_METHOD{InvokeCollisionEventDelegates}]
   */
  void removeCollisionCallback(SoCollisionCB* f, void* userData = NULL);

  // Computing types -----------------------------------------------------------
  /** Transform change type */
  enum TransformChangeType {
    /** None */
    NONE,
    /** Translation */
    TRANSLATION,
    /** Scale */
    SCALE,
    /** Rotation */
    ROTATION,
    /** Orientation */
    ORIENTATION,
    /** Center */
    CENTER
  };

  /** Axis */
  enum Axis {
    /** X */
    X_AXIS = 1,
    /** Y */
    Y_AXIS = 2,
    /** Z */
    Z_AXIS = 4
  };

  /** Postion */
  enum Position {
    /** Begin */
    BEGIN,
    /** End */
    END
  };

#ifndef HIDDEN_FROM_DOC

  struct ShapeBBoxInformationItem {
    SoPath*  path;
    float    x_min, y_min, z_min;
    float    x_max, y_max, z_max;
  };

  struct PairTableItem {
    int      overlap_flags;
    float    x_min, y_min, z_min;
    float    x_max, y_max, z_max;
  };

  struct CompListItem
  {
    int      shape_index;
    Position position;
    SbBool   to_remove;
    float    x, y, z;
  };

  struct ManagerListItem {
    SoCollisionManager*  manager;
    ManagerListItem*     next;
  };

  class INVENTOR_API SceneInformationItem {
  public:
    ~SceneInformationItem();

    SoGroup*              root;
    SoNodeSensor*             sensor;
    SbBool                    need_refresh;
    SbBool                    one_object_has_changed;

    int                 refs;
    ManagerListItem*          manager_list;
    int                       active_manager_count;

    int                       shape_count;
    int                       shape_bbox_information_reserved_size;
    ShapeBBoxInformationItem* shape_bbox_information;

    int            pair_table_reserved_size;
    PairTableItem*            pair_table;

    int            comp_list_size;
    int            comp_list_reserved_size;
    CompListItem*             comp_list;


    SceneInformationItem*     next;
  };
#endif // HIDDEN_FROM_DOC

private : 

  // General data --------------------------------------------------------------
  SoPath*      m_object;
  SoGroup*     m_scene;
  SoTransform* m_transform;
  int          m_gluing_level;

  // Flags ---------------------------------------------------------------------
  SbBool       m_object_bbox_only;
  SbBool       m_scene_bbox_only;
  SbBool       m_gluing;
  SbBool       m_activated;

  // Managing callbacks --------------------------------------------------------
  SoFilterCollisionCB* m_filter_cb;
  void*                m_filter_cb_ud;
  void*                m_bbox_cb_list;
  void*                m_collision_cb_list;
  void invokeBBoxCallbacks (const SoPath* p1, const SoPath* p2);
  Resp invokeCollisionCallbacks (const SoCollidingPrimitive* object,
                                 const SoCollidingPrimitive* scene);

  // Computing variables -------------------------------------------------------
  SbBool                       m_need_check;
  SbBool                       m_object_geometry_has_changed;
  int                          m_primitive_count;
  int                          m_num_primitive_reserved;
  SoCollidingPrimitive*        m_primitives; 
  SoPath*                      m_current_shape_path;
  Resp                         m_upper_response;
  SbBool                       m_new_moving;
  SbBool                       m_new_shapes_pair;
  static SceneInformationItem* m_scene_information_list;
  SceneInformationItem*        m_scene_information;
  SbBool                       m_is_a_good_transform;
  SbBool                       m_there_is_a_good_transform;
  SbBool                       m_need_gluing;
  SoTransform*                 m_last_know_good_transform;
  SoTransform*                 m_temporary_transform;
  SoFieldSensor*               m_translation_sensor;
  SoFieldSensor*               m_scale_sensor;
  SoFieldSensor*               m_rotation_sensor;
  SoFieldSensor*               m_orientation_sensor;
  SoFieldSensor*               m_center_sensor;

  // Computing functions -------------------------------------------------------
  PairTableItem* pairTableGetItem (int shape1, int shape2);
  void pairTableCompute (int (*fct)(const void*, const void*), Axis axis);
  static int compListXCompare(const void* v1, const void* v2);
  static int compListYCompare(const void* v1, const void* v2);
  static int compListZCompare(const void* v1, const void* v2);
  void refresh ();
  void addPrimitiveToTable (SoPath* p,
                            SoCollidingPrimitive::PrimitiveType type,
                            SbVec3f v1,
                            SbVec3f v2,
                            SbVec3f v3);
  void addPrimitiveToTable (SoPath* p,
                            SoCollidingPrimitive::PrimitiveType type,
                            SbVec3f v1,
                            SbVec3f v2)
  { addPrimitiveToTable (p, type, v1, v2, SbVec3f (0, 0, 0)); }
  void addTriangleToTable (SoCallbackAction* action,
                           const SoPrimitiveVertex* v1,
                           const SoPrimitiveVertex* v2,
                           const SoPrimitiveVertex* v3);
  void addSegmentToTable (SoCallbackAction* action,
                          const SoPrimitiveVertex* v1,
                          const SoPrimitiveVertex* v2);
  void onObjectTriangle (SoCallbackAction* action,
                         const SoPrimitiveVertex* v1,
                         const SoPrimitiveVertex* v2,
                         const SoPrimitiveVertex* v3);
  void onObjectTriangleReal (const SbVec3f v0,
                             const SbVec3f v1,
                             const SbVec3f v2);
  void onObjectSegment (SoCallbackAction* action,
                        const SoPrimitiveVertex* v1,
                        const SoPrimitiveVertex* v2);
  SbBool intersectionTwoTriangles (SoCollidingPrimitive* t1,
                                SoCollidingPrimitive* t2);
  //  int intersectionTriangleAndSegment (SoCollidingPrimitive*  t,
  //                                      SbVec3f s0, SbVec3f s1);
  SbBool onTransformChange(SoSensor *sensor, TransformChangeType type);
  SbBool onTransformChange(SbBool sensorIsNotNULL, TransformChangeType type);
  SbBool checkSensor (SoSensor* sensor);
  static SceneInformationItem* getSceneInformation(SoCollisionManager* manager);
  static void removeSceneInformation (SoCollisionManager* manager);
  static void onSceneChange (void* ud, SoSensor* sensor);
  static void refresh (SceneInformationItem* scene);
  void lastKnowGoodTransformComputing ();

  // Real callbacks ------------------------------------------------------------
  static void addTriangleToTableCB (void* ud, SoCallbackAction* action,
                                    const SoPrimitiveVertex* v1,
                                    const SoPrimitiveVertex* v2,
                                    const SoPrimitiveVertex* v3)
  { ((SoCollisionManager*) ud)->addTriangleToTable (action, v1, v2, v3); }
  static void addSegmentToTableCB (void* ud, SoCallbackAction* action,
                                   const SoPrimitiveVertex* v1,
                                   const SoPrimitiveVertex* v2)
  { ((SoCollisionManager*) ud)->addSegmentToTable (action, v1, v2); }
                   
  static void onObjectTriangleCB (void* ud, SoCallbackAction* action,
                                  const SoPrimitiveVertex* v1,
                                  const SoPrimitiveVertex* v2,
                                  const SoPrimitiveVertex* v3)
  { ((SoCollisionManager*) ud)->onObjectTriangle (action, v1, v2, v3); }
  static void onObjectSegmentCB (void* ud, SoCallbackAction* action,
                                 const SoPrimitiveVertex* v1,
                                 const SoPrimitiveVertex* v2)
  { ((SoCollisionManager*) ud)->onObjectSegment (action, v1, v2); }
  static void onTranslationChangeCB (void* ud, SoSensor* sensor)
  { ((SoCollisionManager*) ud)->onTransformChange (sensor, TRANSLATION); }
  static void onScaleChangeCB (void* ud, SoSensor* sensor)
  { ((SoCollisionManager*) ud)->onTransformChange (sensor, SCALE); }
  static void onRotationChangeCB (void* ud, SoSensor* sensor)
  { ((SoCollisionManager*) ud)->onTransformChange (sensor, ROTATION); }
  static void onOrientationChangeCB (void* ud, SoSensor* sensor)
  { ((SoCollisionManager*) ud)->onTransformChange (sensor, ORIENTATION); }
  static void onCenterChangeCB (void* ud, SoSensor* sensor)
  { ((SoCollisionManager*) ud)->onTransformChange (sensor, CENTER); }
  static void onDraggerMotionCB (void* ud, SoDragger *)
  { ((SoCollisionManager*) ud)->onDraggerMotion (); }

  // Manipulator features ------------------------------------------------------
  SbVec3f    m_dragger_translation;
  SbRotation m_dragger_rotation;
  SbVec3f    m_dragger_scale_factor;
  SbRotation m_dragger_scale_orientation;
  SbVec3f    m_dragger_center;
  void onDraggerMotion ();

  // Miscelaneous --------------------------------------------------------------
  void quickSort(void *array, int nElm, int elmSize,
                 int (*compare)(const void*, const void*),
                 char *tmp);

};

#endif //_SO_COLLISION_MANAGER_

