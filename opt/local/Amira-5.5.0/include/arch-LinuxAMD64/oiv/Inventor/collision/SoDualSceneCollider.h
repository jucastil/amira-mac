/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : JM Godinaud (Jan 2006)
**=======================================================================*/

#ifndef  _SO_DUAL_SCENE_COLLIDER_
#define  _SO_DUAL_SCENE_COLLIDER_

#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>
#include <Inventor/sensors/SoNodeSensor.h>

class SoNode;
class SoGroup;
class SoPath;
class SoTransform;

class SoCmStaticScene;
class SoCmMovingScene;

/**
 * @VSGEXT Class to check for collisions between two scenes.
 * 
 * @ingroup collision
 * 
 * @DESCRIPTION
 *   The SoDualSceneCollider class manages collisions, i.e., it checks the intersection of one scene 
 *   with a second scene. Both scenes are tessellated into a list of triangles by using an
 *   SoCallbackAction and its addTriangleCallback method.
 *   An intersection occurs when a triangle of the first scene intersects
 *   a triangle of the second scene. For each pair of intersecting triangles some response 
 *   methods are called.
 *   These response methods can be overridden, for instance, 
 *       - to highlight the intersecting shape
 *       - to highlight the intersecting pair of triangles
 *       - to compute points common to the two scenes
 *       - to count the number of intersecting pairs of triangles
 *       - etc.
 *   
 *   The SoDualSceneCollider references a static scene and a moving scene (with two SoPaths) and a 
 *   transformation (with an SoTransform). The user scene graph must be organized
 *   such that the transformation will affect the moving scene during traversal.
 *   The static scene is specified by the method #setStaticScene and the moving scene by
 *   the method #setMovingScene. 
 *   
 *   The SoDualSceneCollider references a scene by storing its triangle list (see SoCallbackAction) 
 *   and by building a database as a tree. This database spatially organizes the list
 *   of triangles in order to optimize the number of triangle intersection tests.
 *   Note that the SoDualSceneCollider does not monitor the scene graph. Any modifications to the 
 *   Open Inventor nodes in the static scene or the moving scene are not reflected in the 
 *   internal tree database unless #setMovingScene or #setStaticScene are called again by 
 *   the application.
 *
 *   However SoDualSceneCollider watches for any modification to the given transformation. Each
 *   time the transformation changes, an intersection test is done between the two scenes
 *   by automatically calling #checkCollision(). This method searches for pairs
 *   of intersecting triangles in an optimal way. For each pair of intersecting triangles 
 *   found, the Boolean method #searchNextIntersection() is called. By default this method 
 *   returns FALSE, but in most cases, it will be overridden. If it returns FALSE, 
 *   the process of searching intersecting triangles is stopped and checkCollision()
 *   returns TRUE. If searchNextIntersection returns TRUE, the process continues to 
 *   search other pairs of intersecting triangles. If searchNextIntersection always returns 
 *   TRUE, all pairs of intersecting triangles will be found. If the two scenes do 
 *   not collide, searchNextIntersection is never called and checkCollision returns FALSE.
 *   When searchNextIntersection is overridden, some methods can be called to 
 *   get information about the current pair of intersecting triangles:  
 *   getCollidingStaticPath(), getCollidingStaticTriangle(), getCollidingMovingPath(), 
 *   getCollidingMovingTriangle(), and getCommonPoints().
 * 
 *   In the static or moving scene, each internal node of the tree contains a 
 *   bounding box while the leaf nodes contain triangles of the tessellation. 
 *   The maximum number of triangles per leaf (max_triangles_per_leaf) is given 
 *   as the second argument of the method setMovingScene and setStaticScene. 
 *   Note how max_triangles_per_leaf affects the computation:
 *      - the smaller max_triangles_per_leaf, the deeper the tree. 
 *      - the smaller max_triangles_per_leaf, the more memory the tree needs
 *      - the smaller max_triangles_per_leaf, the quicker the checkCollision() function becomes
 *      - the smaller max_triangles_per_leaf, the slower the #setMovingScene/#setStaticScene() 
 *        functions become @BR
 *
 *   A compromise must be chosen between the initial time to build the tree 
 *   (setMovingScene/setStaticScene) and the time to check the collisions.
 *   
 *   Depending on the total number of triangles and the value of max_triangles_per_leaf, 
 *   the execution of setMovingScene/setStaticScene can take several seconds. 
 *   The methods #staticTriangleListBuilt/#movingTriangleListBuilt
 *   and #staticLeafBuilt/#movingLeafBuilt have been defined and can be overridden 
 *   to implement, for instance, a progress bar. However, note that the methods
 *   #staticLeafBuilt/#movingLeafBuilt are not called in linear time.
 * 
 * 
 */ 
class INVENTOR_API SoDualSceneCollider {

 public:

  /**
   * Default constructor.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  SoDualSceneCollider();
  virtual ~SoDualSceneCollider() {};

  /**
   * Specifies the scene that will be moved or transformed.
   * @I max_triangles_per_leaf@i is the maximum number of triangles 
   * stored in each leaf of the internal tree database representing 
   * the moving scene. If @I max_triangles_per_leaf@i
   * is 0, a default maximum number 
   * is computed based on the total number of triangles in the moving scene.
   */
  void setMovingScene(SoPath* object, int max_triangles_per_leaf=0);

  /**
   * Specifies the scene the moving scene is interacting with.
   * @I max_triangles_per_leaf@i is the maximum number of triangles 
   * stored in each leaf of the internal tree database representing 
   * the static scene
   * If @I max_triangles_per_leaf@i is 0, a default maximum number 
   * is computed based on the total number of triangles in the static scene.
   */
  void setStaticScene(SoPath* scene, int max_triangles_per_leaf=0);

  /**
   * Specifies the transformation that will be watched.
   * When the transformation changes, collision detection computations are started.
   * @I transform@i is the transformation node to watch. If NULL, the collision are
   * not checked.
   */
  void activate(SoTransform* transform);

  /**
   * Checks if the current moving scene collides with the static scene.
   * This method is automatically called when the transform node 
   * given to activate() is updated (or touched).
   * Returns TRUE if the two scenes collide, FALSE otherwise.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  virtual SbBool checkCollision() const;

  /** 
   * Method called by checkCollision() for each pair of intersecting triangles found.
   * The method returns FALSE by default and may be overridden.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  virtual SbBool searchNextIntersection() const { return FALSE; }

  
  /** 
   * Specifies the minimum length of a triangle edge. Any triangle having an edge smaller 
   * than this minimum is not registered in the static and moving scene. This minimum length
   * prevents the collider from having floating point precision errors which could lead to
   * invalid detection of intersections.
   * @param minEdgeLength if < 0, no edges are checked and all triangles of the scene 
   *                      are registered. Default value is 1E-8.
   */
  void   setMinEdgeLength(double minEdgeLength);

  /** 
   * Returns the minimum length of a triangle edge. 
   * @see setMinEdgeLength().
   * 
   */
  double getMinEdgeLength() const;


 protected: //PROTECTED_TO_DOCUMENT

  /**
   * Returns the path in the static scene of the current colliding shape.
   * This method could be called, for instance, by an overridden version
   * of #searchNextIntersection().
   */
  const SoPath* getCollidingStaticPath() const;

  /**
   * Returns the path in the moving scene of the current colliding shape.
   * This method could be called, for instance, by an overridden version
   * of #searchNextIntersection().
   */
  const SoPath* getCollidingMovingPath() const;

  /**
   * Returns the coordinates of the current colliding triangle in the static scene.
   * This method could be called, for instance, by an overridden version
   * of #searchNextIntersection().
   */
  void getCollidingStaticTriangle(SbVec3f &v0, SbVec3f &v1, SbVec3f &v2) const;

  /**
   * Returns the coordinates of the current colliding triangle in the moving scene.
   * This method could be called, for instance, by an overridden version
   * of #searchNextIntersection().
   */
  void getCollidingMovingTriangle(SbVec3f &v0, SbVec3f &v1, SbVec3f &v2) const;

  /**
   * Returns the coordinates of the two common points of the current pair of intersecting triangles.
   * This method could be called, for instance, by an overridden version
   * of #searchNextIntersection().
   */
  void getCommonPoints(SbVec3f &p0, SbVec3f &p1) const;

   /** 
   * Tells if an object of the static scene is sensitive to collision detection or not.
   * This method is called by #setStaticScene() for each node found during the traversal. 
   * If it returns FALSE, the node is not inserted in the static scene.
   * By default it returns always TRUE and can be overridden by the application.
   */
  virtual SbBool isSensitiveStaticObject(const SoPath *object_path) const;

   /** 
   * Tells if an object of the moving scene is sensitive to collision detection or not.
   * This method is called by #setMovingScene() for each node found during the traversal. 
   * If it returns FALSE, the node is not inserted in the moving scene.
   * By default it returns always TRUE and can be overridden by the application.
   */
  virtual SbBool isSensitiveMovingObject(const SoPath *object_path) const; 

  /**
   * Method called by #setStaticScene() when the list of triangles in 
   * the static scene is built. By default this method does nothing.
   * But when it is overridden in a subclass, an application can use it,
   * for instance, to start a progress bar.
   * @I num_triangles@i is the total number of triangles found in the 
   *        static scene.
   * See #staticLeafBuilt.
   */
  virtual void staticTriangleListBuilt(int num_triangles) const;

  /**
   * Method called by #setStaticScene() when a new leaf is stored 
   * in the static tree. By default this method does nothing.
   * But when it is overridden in a subclass, an application can use it,
   * for instance, to modify the state of a progress bar.
   * @I num_triangles@i is the number of triangles stored in the leaf.
   * See #staticTriangleListBuilt.
   */
  virtual void staticLeafBuilt(int num_triangles) const;

  /**
   * Method called by #setMovingScene() when the list of triangles in 
   * the moving scene is built. By default this method does nothing.
   * But when it is overridden in a subclass, an application can use it,
   * for instance, to start a progress bar.
   * @I num_triangles@i is the total number of triangles found in the 
   *        moving scene.
   * See #movingLeafBuilt.
   */
  virtual void movingTriangleListBuilt(int num_triangles) const;

  /**
   * Method called by #setMovingScene() when a new leaf is stored 
   * in the moving tree. By default this method does nothing.
   * But when it is overridden in a subclass, an application can use it,
   * for instance, to modify the state of a progress bar.
   * @I num_triangles@i is the number of triangles stored in the leaf.
   * See #movingTriangleListBuilt.
   */
  virtual void movingLeafBuilt(int num_triangles) const;

 SoINTERNAL public:
  //private usage
  void updateMovingScene();
  void triangleListBuilt(int num_triangles) const;
  void leafBuilt(int num_triangles) const; // a new leaf is built : it contains num_triangles
  SbBool isSensitiveObject(const SoPath *object_path) const;

 protected:

  SoPath            *m_staticPath;
  SoCmStaticScene   *m_staticScene;
  SoCmMovingScene   *m_movingScene;
  SoPath            *m_movingPath;

 private:
  SoNodeSensor      m_sensor;
  SoTransform       *m_transform;
  int               m_trianglePerStaticLeaf;
  int               m_trianglePerMovingLeaf;
  SbBool            m_staticSceneBeingBuilt;
  double            m_minEdgeLength;
};

inline SbBool
SoDualSceneCollider::isSensitiveStaticObject(const SoPath *) const
{ return TRUE; }

inline SbBool
SoDualSceneCollider::isSensitiveMovingObject(const SoPath *) const
{ return TRUE; }

inline void 
SoDualSceneCollider::staticTriangleListBuilt(int) const
{}

inline void 
SoDualSceneCollider::staticLeafBuilt(int) const
{}

inline void 
SoDualSceneCollider::movingTriangleListBuilt(int) const
{}

inline void
SoDualSceneCollider::movingLeafBuilt(int) const
{}



#endif // SO_DUAL_SCENE_COLLIDER_
