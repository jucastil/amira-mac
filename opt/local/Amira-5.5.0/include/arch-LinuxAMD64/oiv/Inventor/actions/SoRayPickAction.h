/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_RAY_PICK_ACTION_
#define  _SO_RAY_PICK_ACTION_

#include <Inventor/SoLists.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/SbBox.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoRayPickAction
//
//  Picking action that intersects a ray with objects in the scene
//  graph. The ray can be specified by calling setPoint() with a point
//  in a viewport in a rendering window or by calling setRay() with a
//  world-space ray. In the setPoint() case, a valid camera must be
//  encountered in the graph to set up the mapping to world space.
//
//  The "pickAll" flag indicates whether all intersections along the
//  ray should be returned (sorted by distance from the starting point
//  of the ray), or just the closest one. In either case, the
//  intersections are returned as an SoPickedPointList. Each
//  intersection can be examined by accessing the appropriate
//  SoPickedPoint in the list. The SoPickedPoint class provides
//  methods to get the intersection point, normal, and other info.
//
//////////////////////////////////////////////////////////////////////////////

/** @TOBEREVIEWED@
 * Intersects objects with a ray cast into scene.
 * 
 * @ingroup actions
 * 

 * @DESCRIPTION
 *   This class performs picking by casting a ray into a scene and performing
 *   intersection tests with each object. The ray is extended to be a frustum
 *   a pyramid or a rectangular prism, a cone or a cylinder, depending 
 *   on the camera type and client inputs (refer to #setRay and #enableConicPickVolume)
 *   for intersection with points and lines.
 *   Each intersection is returned as an SoPickedPoint instance.
 *   
 *   The picking ray can be specified as either a ray from the camera 
 *   location through a particular viewport pixel, or as a world-space ray.  
 *   Calling any of the #setPoint, #setNormalizedPoint, or #setRadius methods 
 *   tells the action to compute the picking ray from a viewport pixel. 
 *   In this case, a camera node must be encountered during traversal of 
 *   the scene graph in order to determine the location of the ray in
 *   world space.
 *   
 *   Callers can cause the action to compute all intersections along the ray (sorted
 *   closest to farthest) by setting the @B pickAll @b flag to TRUE. By default, the
 *   action computes only the closest intersection. In either case, the intersections
 *   are returned in an SoPickedPointList. Each intersection can be examined by
 *   accessing the appropriate SoPickedPoint in the list. The SoPickedPoint object
 *   provides methods to get the path (SoPath) to the picked geometry in the scene
 *   graph, the intersection point in 3D space and other info.
 *
 *   The SoPickedPoint object can also return one of the subclasses of SoDetail,
 *   which contains more information about the picked geometry.  For example, if
 *   a polygonal geometry node like SoIndexedFaceSet was picked, an SoFaceDetail
 *   object is returned which provides methods to get the index of the face in
 *   the primitive, the vertices of the face and so on.  For vertex based geometry
 *   each vertex can then be queried as an SoPointDetail.
 *
 *   Open Inventor does true geometric picking in 3D coordinates (it does not use
 *   OpenGL for picking), so there are no limits on the number of objects in the
 *   scene or the number of objects that can be picked.  Geometric picking means
 *   that precise intersections with the geometry are computed.  It also means that
 *   picking works for any type of primitive, including polygonal geometry, meshes
 *   (MeshViz) and volumes (VolumeViz).
 *
 *   Applications can use the SoPickStyle node to control if and how geometry 
 *   can be picked.  For example application might want to specify that annotation
 *   geometry, e.g. a legend, is not pickable.  It can also specify that geometry
 *   should be picked using its bounding box rather than exact geometry.  This may
 *   be more efficient for text strings when it is not necessary to know which
 *   character in the string was picked.
 *
 *   The application can get platform independent input events, e.g. mouse button
 *   press, as SoEvent objects using the SoEventCallback node.  In the \oivnetdoc 
 *   delegate \else callback \endoivnetdoc function the application can call the
 *   node's getPickedPoint() method.  Open Inventor automatically applies a pick 
 *   action to the scene graph and returns the result. In this case the application
 *   does not need to use SoRayPickAction directly.  The application may also use
 *   the event position and apply its own pick action to the scene graph.  If using
 *   system events directly, remember that Open Inventor expects Y pixel values to
 *   start from zero at the bottom of the window.
 *
 *   The SoSelection node provides a higher level way to manage selecting and
 *   de-selecting objects in the scene.  This node automatically applies a pick
 *   action and maintains a list of currently selected objects (paths).  Using
 *   SoSelection the application does not need to use SoRayPickAction directly.
 *   The SoExtSelection node provides more complex picking algorithms.  For example
 *   it allows the user to select objects using a "rubberband" rectangle or a 
 *   freeform shape (lasso).  Open Inventor provides special render actions that
 *   can automatically highlight objects selected using an SoSelection or 
 *   SoExtSelection node. See SoBoxHighlightRenderAction and SoLineHighlightRenderAction.
 *
 *   Pick traversals are optimized using hierarchical bounding boxes cached at the
 *   SoSeparator (and a few other) grouping nodes.  If the pick ray does not intersect
 *   the bounding box then the pick action will not traverse the children of that
 *   separator.  When optimizing for picking the application should consider first
 *   how quickly can Open Inventor find the geometry that should be picked.
 *   Organizing the scene graph spatially to take advantage of the bounding box
 *   optimization can help with this.  Second the application should consider how
 *   long will it take to find the face that should be picked.  For a very large
 *   surface this can be significant.  Enabling triangle culling, splitting large
 *   surfaces into smaller pieces or using proxy geometry may be helpful.
 *
 *   Note that when using SoRayPickAction with pixel coordinates (setPoint()) the
 *   pick action must traverse a camera node in order to unproject the coordinate
 *   back into 3D space.  If the application explicitly creates its own camera, 
 *   this is usually not a problem because the camera is in the application scene
 *   graph.  However if the application allows the viewer to automatically create
 *   a camera then the camera is in the viewer's scene graph @I above @i the
 *   application scene graph.  Calling the viewer's getSceneGraph() method
 *   returns the application scene graph, not the complete viewer scene graph.
 *   To ensure that the traversed scene graph contains a camera, we recommend
 *   calling getSceneManager() then getSceneGraph, as shown in the example below.
 *
 *  Picking SoVolumeRender nodes: @BR
 *  Since Open Inventor 8.6, the SoVolumeRender node (by default) uses the GPU to 
 *  compute the picked voxel during an SoRayPickAction. For this to work, the SoRayPickAction 
 *  must have its scene manager initialised using the method SoAction::setSceneManager().
 *  SoHandleEventAction does this automatically, so it is not necessary for the application
 *  to take any action when using (for example) an SoEventCallback node and calling the
 *  getPickedPoint() method.  However if the application creates its own SoRayPickAction
 *  then it should set the scene manager.  If no scene manager is specified, a warning
 *  message is issued and software picking is done.
 *  If necessary, using the GPU for volume picking may be disabled by setting the
 *  environment variable IVVR_GPU_PICKING to 0 (see SoPreferences).
 *
 *   Sets: SoPickRayElement, SoViewportRegionElement
 *
 * @EXAMPLE
 *   \oivnetdoc
 *     \code
 *     private void mouseBtnCB(SoEventCallback sender, Object data)
 *     {
 *       SoMouseButtonEvent btnEvt = (SoMouseButtonEvent)sender.GetEvent();
 *       SoWinViewer        viewer = (SoWinViewer)data;
 *
 *       if (SoMouseButtonEvent.IsButtonPressEvent(btnEvt,SoMouseButtonEvent.Buttons.BUTTON1)) {
 *         SoRayPickAction rayPick = new SoRayPickAction( viewer.GetViewportRegion() );
 *         rayPick.SetPoint(btnEvt.GetPosition());
 *         rayPick.Apply(viewer.GetSceneManager().GetSceneGraph());
 *         SoPickedPoint pickedPt = rayPick.GetPickedPoint();
 *         if (pickedPt != null) {
 *           SoFullPath pickPath = (SoFullPath)pickedPt.GetPath();
 *           . . .
 *         }
 *       }
 *     }
 *     \endcode
 *   \else
 *     \code
 *     void mouseBtnCB(void *userData, SoEventCallback *pNode ) 
 *     {
 *       const SoEvent    *pEvent  = pNode->getEvent();
 *       const SoXtViewer *pViewer = (SoXtViewer*)userData;
 *
 *       if (SO_MOUSE_PRESS_EVENT(pEvent, BUTTON1)) {
 *         SoRayPickAction rayPick( pViewer->getViewportRegion() );
 *         rayPick.setPosition( pEvent->getPosition() );
 *         rayPick.apply( pViewer->getSceneManager()->getSceneGraph() );
 *         const SoPickedPoint *pPickedPt = rayPick.getPickedPoint();
 *         if (pPickedPt != NULL) {
 *           SoFullPath *pPickPath = (SoFullPath*)pPickedPt->getPath();
 *           . . .
 *         }
 *       }
 *     }
 *     \endcode
 *   \endoivnetdoc
 * 
 * @SEE_ALSO
 *    SoPickedPoint,
 *    SoPickedPointList,
 *    SoPickStyle
 * 
 * 
 */ 

class INVENTOR_API SoRayPickAction : public SoPickAction {

  SO_ACTION_HEADER(SoRayPickAction);

 public:

  /** 
   * Tells ray pick action in which view the pick occurs.
   * When stereo mode is active, user can choose between left, right, 
   * or normal view to perform the action. Only applicable when stereo
   * is active. Default is LEFT_VIEW.
   */
  static void setStereoMode(SoCamera::StereoMode stereoMode);

  /** Returns the view used to perform pick when stereo is active.
   */
  static SoCamera::StereoMode getStereoMode();

  /**
   * Constructor takes viewport region to use for picking. Even though the picking
   * operation may not involve a window per se, some nodes need this information to
   * determine their size and placement.
   */
  SoRayPickAction(const SbViewportRegion &viewportRegion);

  // Destructor
#ifndef HIDDEN_FROM_DOC
  virtual ~SoRayPickAction();
#endif // HIDDEN_FROM_DOC

  //////////////////////////////////////////////////////////////////
  //
  //  Setting up the action before it is applied:
  //

  /**
   * Sets the viewport point through which the ray passes, starting at the
   * camera position. Viewport coordinates range from (0,0) at the lower left to
   * (width-1,height-1) at the upper right. Default is (0,0).
   *
   * NOTE: You can use this method or #setNormalizedPoint or #setRay.
   * Whichever method you call last is the one that takes effect.
   */
  void                setPoint(const SbVec2s &viewportPoint);

  /**
   *  Float version of #setPoint. It can be used when a desktop is magnified
   *  on a wall of screens using ScaleViz with a tracker
   *  device calibrated for this wall.
   *
   * NOTE: You can use this method or #setNormalizedPoint or #setRay.
   * Whichever method you call last is the one that takes effect.
   */
  void                setPoint(const SbVec2f &viewportPoint);

  /**
   * Gets the viewport point in pixels
   * (returns the last value passed to setPoint).
   */
  const SbVec2s&  getPoint() const       { return VPPoint; }

  /**
   *  Float version of #getPoint(). It can be used when a desktop is magnified
   *  on a wall of screens using ScaleViz with a tracker
   *  device calibrated for this wall.
   */
  const SbVec2f&  getPointFloat() const   { return VPPointFloat; }

  /**
   * Sets the viewport point in normalized coordinates, which range from (0,0) at the
   * lower left to (1,1) at the upper right.
   *
   * NOTE: You can use this method or #setPoint or #setRay. 
   * Whichever method you call last is the one that takes effect.
   */
  void                setNormalizedPoint(const SbVec2f &normPoint);

  /**
   * Gets the viewport point in normalized coordinates
   * (returns the last value passed to setNormalizedPoint).
   */
  const SbVec2f       getNormalizedPoint() const
    { return normVPPoint; }

  /**
   * Sets the radius around the point. The radius is defined in pixels when defining a ray
   * using the setPoint or setNormalizedPoint method, and is defined in world coordinates, 
   * when the ray is defined using the setRay method. By default, for the setPoint and
   * setNormalizedPoint method the radius is 5 pixels. 
   *
   * For the setRay method, by default, the radius is not taken into account for triangle
   * based shapes, only for points and lines. To enable this use the #enableRadiusForTriangles method.
   * When radius is taken into account, the ray is extended in 3D space.
   * For perspectivecameras, the ray is extended to be a cone.
   * For orthographic cameras, the ray is extended to be a cylinder. 
   */
  void                setRadius(float radius);

  /** 
   * Gets the radius (in pixels) around the point.
   */
  float               getRadius() const
    { return VPRadius; }

  /** @TOBEREVIEWED@
   * Sets a world-space ray along which to pick. The ray is defined as a world space
   * starting point and direction vector. The direction vector will be normalized
   * automatically. The last two arguments specify optional near and far plane 
   * clipping during the pick operation. These values are distances from the start 
   * point along the direction vector, similar to nearDistance and farDistance in 
   * SoCamera. A negative distance (such as the default values) means disable 
   * clipping to that plane. The ray-picking is orthogonal: it means the pick volume
   * is a rectangular prism with a square base with edges having length #VPRadius * 2
   * or a cylinder having radius #VPRadius depending on #enableConicPickVolume value
   *
   * NOTE: You can use this method or the #setPoint / #setNormalizedPoint 
   * Whichever method you call last is the one that takes effect.
   */
  void setRay(const SbVec3f &start, const SbVec3f &direction,
              float nearDistance = -1.0,
              float farDistance = -1.0);

  /** @TOBEREVIEWED@
   * Sets a world-space ray along which to pick in the the same way as function defined
   * above, but allows you to set a view angle value. By using a fovy not null angle the user can
   * do perspective ray-picking: it means the pick volume is a frustum intersecting the plane
   * passing through the point provided as start argument and having normal directed as the provided direction
   * argument along a square having edges of length #VPRadius * 2 or a circle having radius #VPRadius.
   * The shape of the picking volume depends on the #enableConicPickVolume value.
   */
  void setRay(float fovy, const SbVec3f &start, const SbVec3f &direction,
              float nearDistance = -1.0,
              float farDistance = -1.0);

  /**
   * Sets whether the action will return all objects intersected or just the
   * closest one.
   */
  void setPickAll(SbBool flag)                
    { pickAll = flag; }

  /**
   * Returns whether the action will return all objects intersected or just the
   * closest one.
   */
  SbBool isPickAll() const            
    { return pickAll; }

  //////////////////////////////////////////////////////////////////
  //
  //  Examining results after the action is applied:
  //

  /**
   * Returns list of picked points.
   *
   * This results in a copy of the picked point
   * list and a copy of every SoPickedPoint object in
   * the list.
   */
  const SoPickedPointList &getPickedPointList() const
    { return ptList; }

#ifdef OIV_NET_DOC
  /** 
  * Returns the indexed picked point from the list.
  *
  * Note: Each SoPickedPoint object contains an SoPath
  * with the path to the picked node; therefore the
  * picked node will be referenced until the SoPickedPoint
  * object is destroyed.
  *
  * The SoPickedPoint object is owned by the pick action.
  * It will be destroyed when the action is destroyed or
  * when either apply() or clearPickedPointList() is
  * called.
  */

#else
  /** 
  * Returns the indexed picked point from the list.
  *
  * Note: Each SoPickedPoint object contains an SoPath
  * with the path to the picked node; therefore the
  * picked node's ref count has been incremented and
  * will remain incremented until the SoPickedPoint
  * object is destroyed.
  *
  * The SoPickedPoint object is owned by the pick action.
  * It will be destroyed when the action is destroyed or
  * when either apply() or clearPickedPointList() is
  * called.
  */

#endif //OIV_NET_DOC
  SoPickedPoint *getPickedPoint(int index = 0) const;

  /** 
  * Clears the picked point list.
  *
  * The picked point list is automatically cleared
  * when the action is destroyed or re-applied.
  * However it may be useful to clear the list explicitly
  * in order to remove references to picked node(s).
  */
  void clearPickedPointList();

  /** 
   * Enable radius for triangle-based shape
   *
   * If TRUE, the radius of the ray specified by #setRadius
   * is taken in account when checking for a ray intersection with 
   * triangle-based shapes (e.g., SoCylinder).
   * Otherwise, the pick radius for these shapes is 1 pixel regardless of
   * the specified pick radius.  Default is FALSE for performance.
   */
  void enableRadiusForTriangles(SbBool flag);
 
  /**
   * Returns whether the pick radius specified by #setRadius
   * is taken into account for picking on triangle-based shapes.
   */
  SbBool isRadiusEnableForTriangles();

  /**
   * 
   * Enables/disables the culling of triangles relative to the ray
   * frustum.
   * Enabling culling improves performance for shapes containing a large number of triangles.
   */
  static void enableTriangleCulling(SbBool flag) ;


  /**
   * Returns whether triangle culling is enabled
   */
  static SbBool isTriangleCulling()
    { return s_triangleCullingEnabled; }

   /** @TOBEREVIEWED@
   * 
   * Controls the picking volume shape.
   * Picking volume at default is a frustum (false).
   * By setting enableConicVolume to TRUE the picking volume
   * is a conic shape. A cylinder if the user is rayPicking
   * calling setRay without setting the fovy angle,
   * a cone if he calls setRay and a not null fovy angle.
   * ConicPickVolume set to true assures the entities being picked
   * by mean of setRay to be the same picked by mean of an equivalent
   * setPoint but is slightly more costly than frustum picking.
   */
  void enableConicPickVolume(SbBool flag);

  /** @TOBEREVIEWED@
   * Returns whether the picking volume is a conic or a frustum-like shape.
   */
  inline SbBool isConicPickVolume()
  { return m_conicPickVolume; }

 SoEXTENDER public:

  // If a ray was not defined with setRay(), this causes the world
  // space pick ray to be computed from the screen space point and
  // radius, using the current view specification from the state.
  // This is typically done when a camera is encountered during
  // traversal.
  void computeWorldSpaceRay();

  // This returns TRUE if the action has had a world space ray set
  // or computed
  SbBool hasWorldSpaceRay() const;

  // This is called by shapes to set up object space picking. It
  // uses the current state matrices to determine how to map between
  // world and object spaces. It should be called before calling any
  // of the intersection methods.
  // The second form takes a matrix to concatenate with the current
  // objToWorld matrix. It can be used, for example, if a shape has
  // sizing or positioning info built into it.
  void                setObjectSpace();
  void                setObjectSpace(const SbMatrix &matrix);

  // These intersect the current object-space ray with a variety of
  // primitives: triangle, line, point, bounding-box. Intersection
  // with a triangle uses only the ray, while intersection with a
  // line or point uses the cone or cylinder around the ray. The
  // intersection with a bounding-box uses the cone/cylinder also,
  // since the contents of the box may be lines or points. NOTE: you
  // must call setObjectSpace() before calling any of these.

  // Triangle: returns intersection point, barycentric coordinates,
  // and whether the front side (defined by right-hand-rule) was hit.
  SbBool intersect(const SbVec3f &v0,
                   const SbVec3f &v1,
                   const SbVec3f &v2,
                   SbVec3f &intersection, SbVec3f &barycentric,
                   SbBool &front) ;

  // Line:
  SbBool intersect(const SbVec3f &v0, const SbVec3f &v1,
                   SbVec3f &intersection) const;

  // Point:
  SbBool intersect(const SbVec3f &point) const;

  /**
   * Bounding box: just return whether the ray intersects it. If
   * useFullViewVolume is TRUE, it intersects the picking view
   * volume with the box. Otherwise, it uses just the picking ray,
   * which is faster.
   */
  inline SbBool intersect(const SbBox3f &box, SbBool useFullViewVolume = TRUE)
  {
    SbXfBox3f xbox(box);
    return intersect(xbox, useFullViewVolume);
  }

  /**
   * Bounding box: just return whether the ray intersects it. If
   * useFullViewVolume is TRUE, it intersects the picking view
   * volume with the box. Otherwise, it uses just the picking ray,
   * which is faster.
   */
  SbBool intersect(const SbXfBox3f &box, SbBool useFullViewVolume = TRUE);


  // Returns an SbViewVolume that represents the object-space ray to
  // pick along. The projection point of the view volume is the
  // starting point of the ray. The projection direction is the
  // direction of the ray. The distance to the near plane is the
  // same as the distance to the near plane for the ray. The
  // distance to the far plane is the sum of the near distance and
  // the depth of the view volume.
  const SbViewVolume &getViewVolume() const
    { return objVol; }

  // Returns SbLine that can be used for other intersection tests.
  // The line's position is the starting point and the direction is
  // the direction of the ray. Given an intersection with this ray,
  // you can call isBetweenPlanes() to see if the intersection is
  // between the near and far clipping planes.
  const SbLine &getLine() const
    { return objLine; }

  // Returns TRUE if the given object-space intersection point is
  // between the near and far planes of the object-space view
  // volume, as well as any clipping planes that have been defined.
  // This test can be used to determine whether the point of
  // intersection of the ray with an object is valid with respect to
  // the clipping planes.
  SbBool isBetweenPlanes(const SbVec3f &intersection) const;

  /**
  * Adds an SoPickedPoint instance representing the given object
  * space point to the current list and returns it. If
  * pickAll is TRUE, this inserts the instance in correct sorted
  * order. If it is FALSE, it replaces the one instance in the list
  * only if the new one is closer; if the new one is farther away,
  * no instance is created and NULL is returned, meaning that no
  * more work has to be done to set up the SoPickedPoint.
  * [OIVJAVA-WRAPPER VISIBILITY{Public}]
  */
  SoPickedPoint *addIntersection(const SbVec3f &objectSpacePoint);

 protected:
  // Initiates action on graph
  virtual void beginTraversal(SoNode *node);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  // return whether OIV_PICK_OPTIM is set to TRUE
  static SbBool isPickOptimSet()
  { return s_useAlternateIntersection; }

  /** 
   * Properties that can be disabled during the generation of SoPickedPoint to the application.
   * Allows to speedup picking action.
   * Default is ALL.
   */
  enum PickedProperties
  {
    /** normals **/
    NORMALS = 1 << 0,
    /** texture **/
    TEXCOORDS = 1 << 1,
    
    /** All properties */
    ALL = ~0
  };

  /** Allows to speedup picking action by removing some uneeded properties generation when possible. */
  void enablePickedProperties(const enum PickedProperties mask, const SbBool enable);

  /** Checks is a picking properties is currently required or not. */
  SbBool isPickedPropertiesEnabled(const enum PickedProperties mask) const;

  /**
   * Enables whether all traversed shape should use point Picking instead of line or triangle
   * Default is FALSE;
   */
  void enablePointPickingMode(const SbBool enable)
  { m_pointPickingMode = enable; }

  /** 
   * Returns whether all traversed shape should use point Picking instead of line or triangle
   * NOTES: only supported for SoIndexedShape.
   */
  SbBool isPointPickingMode() const
  { return m_pointPickingMode; }

  // Returns TRUE if the two SoPickedPoint are the same.
  SbBool isEqual(const SoPickedPoint *pp0, const SoPickedPoint *pp1) const;

  // Returns TRUE if the first intersection point is closer to the
  // starting point of the ray than the second.
  SbBool isCloser(const SoPickedPoint *pp0, const SoPickedPoint *pp1) const;
  SbBool isCloser(const SbVec3f& p0, const SbVec3f& p1) const;


 protected:
  SbBool lineWasSet;  // TRUE if a world-space line was set
  SbBool rayWasComputed;      // TRUE if ray computed by camera
  SbBool pickAll;     // Pick all objects or just closest
  SbVec2s VPPoint;    // Point in viewport coordinates
  SbVec2f VPPointFloat; // Point in viewport coordinates
  SbVec2f normVPPoint;        // Point in normalized vp coordinates
  SbBool normPointSet;        // TRUE if setNormalizedPoint called
  float VPRadius;     // Radius in viewport space pixels
  SbMatrix objToWorld;        // Object-to-world space matrix
  SbMatrix worldToObj;        // World-to-object space matrix
  SoPickedPointList   ptList;         // List of intersections

  // The ray is defined as an SbViewVolume as in the
  // SoPickRayElement, and is usually stored in an instance of the
  // element. This stores the ray if it is set using setRay().
  SbViewVolume worldVol;

  // Users can specify negative near and far distances to indicate
  // that picks should not be clipped to those planes. These flags
  // store that info, since the distances in the view volume can't
  // be negative.
  SbBool clipToNear, clipToFar;

  // These store the object-space ray info as a view volume and a
  // line. See the comments on getViewVolume() and getLine().
  SbLine  objLine;     // Line representing ray
  SbLined objLineD;
  SbViewVolume objVol;                // View volume representing ray

  // If the caller passes a matrix to setObjectSpace(), the inverse
  // of it is stored here so the object-space angle can be computed
  // correctly later. The extraMatrixSet flag is set to TRUE in this
  // case.
  SbBool extraMatrixSet;
  SbMatrix extraMatrix;

  // Computes matrices to go between object and world space
  void computeMatrices();

  // Computes object-space view volume and line
  void computeObjVolAndLine();

  // Computes distance t of a point along a ray: point = start + t * direction.
  // The point has to be on the ray for this to work
  static float        rayDistance(const SbVec3f &start,
                                  const SbVec3f &direction,
                                  const SbVec3f &point);

  // Set commons properties of the action (called by the setRay method)
  void setRayCommonProperties (const SbVec3f &start, const SbVec3f &direction, 
                               float fovy, float aspectRatio = 1.0f, float nearDistance=-1.0f, float farDistance=-1.0f);

  // Initialize some members variable when a new point in viewport has been set
  void initializeMembersAfterVPPointSet(bool normalizedPointSet);

  // get VPradius in world coordinates
  float getVPRadiusWorld() const ;

  // check if the intersection is inside conic picking volume
  inline SbBool isInConicPickingVolume( const SbVec3f &intersection ) const;

  void initSetRayData ( const SbVec3f &start, const SbVec3f &direction,
                        float fovy, float aspectRatio = 1.0f, 
                        float nearDistance = -1.0f, float farDistance = -1.0f );

  // Store the current ray bounding box for triangle culling
  SbBool m_canUseTriangleCulling;
  SbBox3f  m_rayBBox ;

  // store the current viewvolume matrix and near far in homogene space
  // to optimize intersection computation 
  SbMatrix m_wmat;
  float m_wnear;
  float m_wfar;

  // Indicate if triangle are culled by ray frustum.
  SbBool canUseTriangleCulling() const
  { return (s_triangleCullingEnabled && m_canUseTriangleCulling); }

  static SbBool  s_triangleCullingEnabled ;

  // Use double precision math internally?
  static SbBool  s_doublePrecision;

  //
  static SoCamera::StereoMode s_stereoMode;

  // Use faster intersection method
  static SbBool s_useAlternateIntersection;

  // Force the raypick action to take ray radius in account
  SbBool m_bEnableRadiusForTriangles;

  // Store ray properties
  SbVec3f m_direction;
  SbVec3f m_start;

private:
  int m_pickedPropertiesMask;
  SbBool m_pointPickingMode;

  int m_VPRadiusState;      // how VPRadius has been initialized

  // data buffered for the lineWasSet case
  float m_fovy;             
  float m_nearDistance;
  float m_farDistance;
  float m_aspectRatio;

  // to force pick volume to be a cone (perspective pick) or a cylinder (orthogonal pick)
  SbBool m_conicPickVolume;

};

inline 
void SoRayPickAction::enableRadiusForTriangles(SbBool flag)
{
  m_bEnableRadiusForTriangles = flag;  
}

inline
SbBool SoRayPickAction::isRadiusEnableForTriangles()
{
  return m_bEnableRadiusForTriangles;
}
#endif /* _SO_RAY_PICK_ACTION_ */

