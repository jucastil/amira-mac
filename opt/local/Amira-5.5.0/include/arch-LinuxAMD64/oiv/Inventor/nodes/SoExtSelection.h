/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Fabien ARNAUD (MMM yyyy)
** Modified by : Christophe OGNIER (MMM yyyy)
** Modified by : Daniel LICHAU (update)        * (MMM yyyy)
**=======================================================================*/

#ifndef _SO_EXTENDED_SELECTION_H_
#define _SO_EXTENDED_SELECTION_H_

//------------------------------------------------------------------------------
//Include files

#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/nodes/SoColorIndex.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/SbViewportRegion.h>

//------------------------------------------------------------------------------
// Class declaration
class SoCamera;
class SoSeparator;
class SoCoordinate3;
class SbViewportRegion;
class SoMaterial;
class SoPath;
class LassoRenderer;
class SoOrthographicCamera;

/**
 * @VSGEXT Selection node that supports lasso selection.
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 *   This class extends the functionality of SoSelection to allow the user to select
 *   an object or multiple objects by drawing a lasso around the object(s) to be
 *   selected. The lasso can be represented as a rectangle between the mouse up and
 *   down positions or as a set of lines that the user draws around the objects,
 *   depending on the field #lassoType. When #lassoType is NOLASSO, or
 *   when the lasso is empty (the screen coordinates of the button down and button up
 *   event are the same), SoExtSelection behaves exactly like its parent class
 *   SoSelection.
 *   
 *   Objects are selected if they are surrounded by the lasso or if the lasso
 *   intersects them, depending on the field #lassoPolicy, as follows:
 *   
 *   - FULL_BBOX: lasso selects objects whose bounding box is completely contained by
 *   the lasso
 *   
 *   - PART_BBOX: lasso selects objects whose bounding box intersects the lasso (or is
 *   contained by the lasso)
 *   
 *   - FULL: lasso selects objects whose geometry is completely contained by the
 *   lasso
 *   
 *   - PART: lasso selects objects whose geometry intersects the lasso (or is
 *   contained by the lasso)
 *   
 *   FULL and PART require more computation and are generally slower.
 *   
 *   A lasso mode controls whether only visible shapes (front shapes) are selectable,
 *   by controlling the selection algorithm used, either geometry-based or
 *   pixel-based. A specific lasso mode may also be preferred for performance reasons
 *   depending on the scene.
 *   
 *   Primitive details for selected parts of shapes can be obtained through dedicated
 *   callbacks that can be also used to filter the selection. These primitive filter
 *   callbacks can be called for each generated primitive.
 *   
 *   When using SoExtSelection node, the \oivnetdoc delegate \else callback \endoivnetdoc set by @B setPickFilterCallback @b
 *   will be called only once per selected shape. Only
 *   SoPickedPoint::getPath() makes sense for the picked point passed to the
 *   pick filter \oivnetdoc delegate \else callback \endoivnetdoc in this case. Other SoPickedPoint methods may return
 *   undefined results.
 *   
 *   Lasso selection can be also be controlled programmatically, without requiring
 *   user interaction.
 *   
 *   NOTE: The features below which depend on overlay planes are supported only if the
 *   graphics board supports overlay planes.
 *
 *   NOTE: Using the FastEdit mode:
 *
 *   FastEdit mode provides the advantages of overlay mode without the overlay hardware
 *   support requirement. See SoSeparator for more information about the 
 *   fast editing feature. FastEdit mode can allow the lasso geometry to be redrawn
 *   at interactive rates even when the underlying scene takes a long time to redraw. 
 *   On Windows platforms, it also avoids using GDI to draw the lasso, which conflicts
 *   with the "Aero" user interface mode on Windows Vista.
 *
 *   When the application uses fast editing it must call the function useFastEdit(TRUE) first.
 *   If it doesn't call this function, operations which require fast edit will output a warning
 *   in debug mode.
 *
 *   FastEdit mode also provides some powerful additional features including the option to
 *   provide custom (and dynamic) lasso geometry (see the setSelectionSceneGraph()
 *   method) and the option to set callbacks on mouse events during selection (see the
 *   methods setStartSelectionCallback(), setEndSelectionCallback(),
 *   and setMovingSelectionCallback()).
 *   The geometry in the selection scene graph can be dynamically updated by the
 *   application as the user moves the cursor, using these callbacks.  This can useful to 
 *   display dynamic feedback without actually doing selection.  For example to display a 
 *   "rubber band" line while positioning annotations or measurements.
 *
 *   Note: The geometry in the selection scene graph is not automatically used for selection.
 *   (It may not be appropriate.)  However the application can use the select() method, if 
 *   desired, to do a selection using any set of 2D points defining a "lasso".
 * 
 * @FILE_FORMAT_DEFAULT
 *    ExtSelection {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR policy               @TD SHIFT
 *       @TR lassoType            @TD NOLASSO
 *       @TR lassoPolicy          @TD FULL_BBOX
 *       @TR lassoMode            @TD ALL_SHAPES
 *       @TR fastEditing          @TD DISABLE
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoRayPickAction,
 *    SoSelection,
 *    SoWinRenderArea
 * 
 * 
 */ 

class INVENTOR_API SoExtSelection : public SoSelection {
  
  SO_NODE_HEADER(SoExtSelection);
  
  //============================================================================
 public:

  /** Lasso type */
  enum LassoType {
    /** No lasso (default) */
    NOLASSO,
    /** Lasso */
    LASSO,
    /** Rectangle */
    RECTANGLE,
    /** Ellipse */
    ELLIPSE
  };  

  /** Lasso policy */
  enum LassoPolicy {
    /** Full bounding box (default) */
    FULL_BBOX,
    /** Partial bounding box */
    PART_BBOX,
    /** Full */
    FULL,
    /** Partial */
    PART
  };  
  
  /** Lasso mode */
  enum LassoMode {
    /** Visible shapes */
    VISIBLE_SHAPES,
    /** All shapes (default) */
    ALL_SHAPES
  };  

  /**
   * Specifies lasso type (none, lasso, or rectangle).
   * Use enum #LassoType. Default is NOLASSO.
   */
  SoSFEnum lassoType;

  /**
   * Specifies the lasso policy. See description above. 
   * Use enum #LassoPolicy. Default is FULL_BBOX.
   */
  SoSFEnum lassoPolicy;

  /**
   * Specifies the lasso mode (whether ALL_SHAPES or only VISIBLE_SHAPES can be
   * selected).
   * Use enum #LassoMode.  Default is ALL_SHAPES.
   * It applies only when the lasso policy is FULL or PART. When the lasso
   * mode is VISIBLE_SHAPES, you will only select @I visible @i shapes. That is, if
   * a shape is within (or partially within) the lasso volume, but is hidden by
   * another shape, it will not be selected. VISIBLE_SHAPES mode provides faster
   * performance than ALL_SHAPES (the default).
   * 
   * 
   * The algorithm for the ALL_SHAPES mode is based on geometry projection while the
   * VISIBLE_SHAPES mode uses offscreen rendering.
   * 
   * 
   * When using VISIBLE_SHAPES, none of the primitive selection callback nodes can be
   * called. This means that you cannot retrieve selection details using this mode.
   * 
   * 
   * Unlike the ALL_SHAPES mode or the picking action, the VISIBLE_SHAPES mode
   * does not allow you to select multiple overlapping shapes. You cannot select a
   * shape obscured by another.
   * 
   */
  SoSFEnum lassoMode;

  /** Return type */
  enum ReturnType {
    /**
     * same as FALSE - Do not select the node, but continue with node's next 
     * triangle/line/point
     */
    NOSELECT_CONTINUE,
    /** 
     * same as TRUE - Select the node and stop traversing node's 
     * triangle/line/point
     */
    SELECT_RETURN,
    /**
     * Select the node but continue for the remaining triangle/line/point
     */
    SELECT_CONTINUE,
    /**
     * Do not select the node and stop traversing node's triangle/line/point
     */
    NOSELECT_RETURN
  }; 
  
  /**
   * Constructor.
   */
  SoExtSelection();

  /**
   * Sets whether the lasso is drawn in the overlay plane. @BR
   * This only works if the graphics board supports overlay planes
   * (for example the NVIDIA Quadro boards). Default is FALSE.
   */
  void useOverlay(SbBool flg = TRUE)
    { m_use_overlay = flg; }

  /**
   * Gets whether the lasso is drawn in the overlay plane. 
   */
  SbBool isUsingOverlay()
    { return m_use_overlay; }

  /**
   * Sets whether the lasso should be drawn using fast editing. @BR
   * When the application uses the FastEdit mode it must call this
   * function first before calling any other function in this class.
   * See also SoGLRenderAction::setFastEditSavePolicy for possible limitations.
   * Default is FALSE.
   */
  void useFastEditing(SbBool flg = TRUE);

  /**
   * Gets whether the lasso is drawn using fast editing. 
   */
  SbBool isUsingFastEditing()
    { return m_useFastEditing; }

  /**
   * Returns the scene graph that should be passed to the render area function
   * @B setOverlaySceneGraph @b. Applies only if the lasso is drawn in the overlay
   * plane.
   */
  SoSeparator *getOverlaySceneGraph()
    { return m_lasso_root; }

  /**
   * Sets the lasso color index. Applies only if the lasso is drawn in the
   * overlay plane. 
   */
  void setOverlayLassoColorIndex(int index)
    { m_overlay_lasso_color->index.setValue(index); }

  /**
   * Gets the lasso color index. Applies only if the lasso is drawn in the
   * overlay plane. 
   */
  int getOverlayLassoColorIndex()
    { return m_overlay_lasso_color->index[0]; }
  
  /**
   * Sets the lasso color. Applies only if the lasso is not drawn in the overlay
   * plane. This function sets the color in FastEdit mode also.
   * Default is red (1,0,0).
   */
  void setLassoColor(SbColor c);

  /**
   * Gets the lasso color. Applies only if the lasso is not drawn in the overlay
   * plane.
   */
  SbColor getLassoColor()
    { return m_lasso_color; }

  /**
   * Sets the lasso line width.
   * This function sets the width in FastEdit mode also. Default is 1.
   */
  void setLassoWidth(float width)
    { m_lasso_draw_style->lineWidth.setValue(width); }

  /**
   * Gets the lasso line width.
   */
  float getLassoWidth()
    { return m_lasso_draw_style->lineWidth.getValue(); }
  
  /**
   * Sets the lasso stipple pattern. Values can range from 0 (invisible) to
   * 0xffff (solid). This specifies how dashed or dotted lasso lines will be drawn. 
   * This function actually sets the line pattern in all cases, not just overlay.
   * Default is 0xffff (solid).
   */
  void setOverlayLassoPattern(unsigned short pattern);

  /**
   * Gets the lasso stipple pattern. Values can range from 0 (invisible) to
   * 0xffff (solid).
   */
  unsigned short getOverlayLassoPattern()
    { return(unsigned short) m_lasso_pattern; }

  /**
   * Sets the the lasso animation flag. This controls whether the lasso is
   * animated (its line pattern changes) or not.  Default is FALSE.
   */
  void animateOverlayLasso(SbBool flg = TRUE);

  /**
   * Gets the the lasso animation flag.  
   */
  SbBool isOverlayLassoAnimated()
    { return m_lasso_animation; }

  /**
   * Simulates interactive selection starting from the root node with the given lasso
   * contour, updating the selection list and triggering any associated \oivnetdoc delegate \else callback \endoivnetdoc.
   * Even though the selection operation may not involve a window per se, some nodes
   * need the viewport information to determine their size and placement. The flag
   * @B shiftPressed @b simulates the effect of pressing the shift key while
   * selecting, which is applicable along with the SHIFT policy. The lasso will not be
   * drawn when using this method. The lasso coordinates are given in normalized
   * device coordinates ranging from -1 to +1 in the X and Y directions.
   * The selection is done without drawing the lasso.
   *
   * The lasso type can be set using the lassoType field. 
   * Note: When the lassoType is set to LASSO the objects are selected according to the points defined by the 
   * lasso coordinates so the segments between those points are not part of the lasso!.
   * [OIVNET-WRAPPER-ARG IN,IN,ARRAY,IN,IN]
   * [OIVJAVA-WRAPPER-ARG IN,NO_WRAP{lassoCoord->Length},CONST&ARRAY,IN,IN]
   */
  void select(SoNode *root, int numCoord, SbVec2f *lassoCoord,  
              const SbViewportRegion &viewport, SbBool shiftPressed);

  /**
   * @deprecated
   * Use the select method with the lasso coordinates given as SbVec2f.
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,IN,IN]
   * @DEPRECATED_SINCE_OIV 6.0
   */
  void select(SoNode *root, int numCoord, SbVec3f *lassoCoord,  
              const SbViewportRegion &viewport, SbBool shiftPressed);

  /**
   * [OIV-WRAPPER NAME{TriangleCB}]
   * [OIV-WRAPPER-ARG IN,IN,IN,IN,IN]
   */
  typedef SbBool SoExtSelectionTriangleCB(void *userData,
                                          SoCallbackAction *action,
                                          const SoPrimitiveVertex *v1, 
                                          const SoPrimitiveVertex *v2, 
                                          const SoPrimitiveVertex *v3);
  /**
   * [OIV-WRAPPER NAME{LineSegmentCB}]
   * [OIV-WRAPPER-ARG IN,IN,IN,IN]
   */
  typedef SbBool SoExtSelectionLineSegmentCB(void *userData,
                                             SoCallbackAction *action,
                                             const SoPrimitiveVertex *v1, 
                                             const SoPrimitiveVertex *v2);
  /**
   * [OIV-WRAPPER NAME{PointCB}]
   * [OIV-WRAPPER-ARG IN,IN,IN]
   */
  typedef SbBool SoExtSelectionPointCB(void *userData,
                                       SoCallbackAction *action,
                                       const SoPrimitiveVertex *v1); 

   /** 
    * This is the declaration to use for selection event callback functions. @BR
    * See setStartSelectionCallback(), setEndSelectionCallback(),
    * and setMovingSelectionCallback(). These callbacks are useful to
    * modify the selection scene graph (see setSelectionSceneGraph) to
    * implement dynamically changing selection feedback.
    *
    * Note: These callbacks can only be used in FastEdit mode.
    *
    * @param position The position of the event in pixel coordinates (0,0 is lower left corner).
    * @param scenePosition The position of the event in normalized -1..1 3D coordinates.
    * @param selection The selection node that called the function.
    * @param userData Optional pointer specified when the callback was set.
    *
    * @return If the callback handles the event it must return TRUE, else return FALSE.
    */
   typedef SbBool SelectionEventCallback( const SbVec2s& position, const SbVec3f& scenePosition, 
                                          SoExtSelection* selection, void* userData );

  /** 
   * Adds a child at the end of the list of children.
   *
   * It redefines the SoSeparator::addChild function just to ensure that the selection 
   * scenegraph is always the last child in the list.
   */
  virtual void addChild( SoNode *child );

  /**
   * Sets the scenegraph to be displayed as "lasso" in fast edit mode.
   *
   * Note: This function is available only in FastEdit mode.
   *
   * The geometry in this scene graph can be dynamically updated by the
   * application as the user moves the cursor. See the methods
   * setStartSelectionCallback(), setMovingSelectionCallback(), etc.
   * This can useful to display dynamic feedback without actually doing
   * selection.  For example to display a "rubber band" line while
   * positioning annotation or measurements.
   *
   * Note: The geometry in this scene graph is not automatically
   * used for selection!  (It may not be appropriate.)  The application
   * can use the select() method, if desired, to do a selection using 
   * any set of 2D points defining a "lasso".
   */
  virtual void setSelectionSceneGraph( SoNode* sceneGraph );

  /** 
   * Returns the scenegraph displayed as "lasso" in fast edit mode.
   *
   * Note: This function is available only in FastEdit mode, returns NULL otherwise.
   */
  virtual SoNode* getSelectionSceneGraph() const;

  /**
   * Sets the callback called when the mouse button is clicked in selection mode.
   *
   * Note: This function is available only in FastEdit mode.
   */
  virtual void setStartSelectionCallback( SelectionEventCallback* callback, void* userData = NULL );

  /** 
   * Sets the callback called when the mouse button is released in selection mode.
   *
   * Note: This function is available only in FastEdit mode.
   */
  virtual void setEndSelectionCallback( SelectionEventCallback* callback, void* userData = NULL );

  /**
   * Sets the callback called when the mouse is moved in selection mode.
   * The callback is only called while the mouse button is down.
   *
   * Note: This function is available only in FastEdit mode.
   */
  virtual void setMovingSelectionCallback( SelectionEventCallback* callback, void* userData = NULL );

  /**
   * Sets the triangle filter \oivnetdoc delegate \else callback \endoivnetdoc. 
   * The primitive filter callbacks can be used to retrieve information about the
   * selected primitives of traversed shape nodes - points, line segments, or
   * triangles - and to filter the shape selection based on the selected primitives.
   * These callbacks are called while traversing the scene graph shapes with an
   * SoCallbackAction started by the SoExtSelection node. Whenever a shape primitive
   * is surrounded by the lasso, the \oivnetdoc delegate \else callback \endoivnetdoc is called and receives as argument the
   * action and the primitive. Depending on the shape type, the point, line or
   * triangle \oivnetdoc delegate \else callback \endoivnetdoc will be called. See SoCallbackAction.
   * 
   * When a \oivnetdoc delegate \else callback \endoivnetdoc returns TRUE, the corresponding shape is selected according to
   * the selection policy. Then the selection stops processing the current shape's
   * primitives and continues with the next shape in the scene graph. When a \oivnetdoc delegate \else callback \endoivnetdoc
   * returns FALSE, the action continues normally to process the remaining shape's
   * primitives, allowing you to filter or collect additional primitives.
   * 
   * The primitive filter callbacks are called only when the #lassoPolicy is set
   * to SoExtSelection::PART and the #lassoMode is set to
   * SoExtSelection::ALL_SHAPES.
   * 
   * It is the responsibility of the application to manage the primitive selection
   * policy. Exactly like SoSelection, the node selection list can only handle paths
   * to nodes and cannot store primitive detail information.
   */
  void setTriangleFilterCallback(SoExtSelectionTriangleCB *cb, 
                                 void *userData = NULL);

  /**
   * Sets the line segment filter callback. See setTriangleFilterCallback()
   * for details.
   */
  void setLineSegmentFilterCallback(SoExtSelectionLineSegmentCB *cb, 
                                    void *userData = NULL);
  /**
   * Sets the point filter callback. See setTriangleFilterCallback()
   * for details.
   */
  void setPointFilterCallback(SoExtSelectionPointCB *cb, 
                              void *userData = NULL);

  /**
   * Returns the lasso coordinates in device coordinates.
   * [OIVJAVA-WRAPPER-ARG NO_WRAP]
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{numCoords}]
   */
  const SbVec2s *getLassoCoordsDC(int &numCoords);

  /**
   * Returns the lasso coordinates in world coordinates.
   * [OIVJAVA-WRAPPER-ARG NO_WRAP]
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{numCoords}]
   */
  const SbVec3f *getLassoCoordsWC(int &numCoords);

  /**
   * Returns paths list of selected objects.
   */
  const SoPathList &getSelectionPathList() const
    { return tempSelectionList;}

  // Routines to add callbacks for checked primitives 
  //(triangles, line segments, and points) for all shapes. 

 SoEXTENDER public:
  // Traversal routine for SoHandleEventAction - this will call
  // action->setHandled() if the event is handled
  virtual void handleEvent(SoHandleEventAction *action);
  virtual void search(SoSearchAction *action);

 SoINTERNAL public:
  static void           initClass();
  static void           exitClass();

  void setSelection( SbBool on ) { m_makeSelection = on; }
  SbBool getSelection() const { return m_makeSelection; }

  //============================================================================
 protected:

  // Paths list of selected objects
  SoPathList tempSelectionList;
  
  SoExtSelectionTriangleCB *triangleCBFunc;
  SoExtSelectionLineSegmentCB *lineSegmentCBFunc;
  SoExtSelectionPointCB *pointCBFunc;
  void *triangleCBData;
  void *lineSegmentCBData;
  void *pointCBData;

  // Destructor ----------------------------------------------------------------
  // Private to keep people from trying to delete
  // nodes, rather than using the reference count mechanism.
  virtual ~SoExtSelection();

  /**
   * This functions check the callbacks to call according to the specified event.
   */
  void manageEventCallbacks( SoHandleEventAction *action );

  /**
   * This functions check events for the regular selection mode.
   */
  void handleSelectionEvent(SoHandleEventAction *action);

  //============================================================================
 private:

  enum ShapeType {
    TRIANGLE_SHAPE,
    LINE_SHAPE,
    POINT_SHAPE
  };

  // Private data --------------------------------------------------------------

  // Overlay scene graph
  SoTimerSensor *m_lasso_animation_timer;
  SoSeparator *m_lasso_root;
  SoColorIndex *m_overlay_lasso_color;
  SoDrawStyle *m_lasso_draw_style;
  SoCoordinate3 *m_lasso_coordinate;
  SoOrthographicCamera* m_lasso_camera;

  int m_lasso_window_height, m_max_lasso_points;
  SbBool m_new_lasso;

  // Lasso data
  SbBool m_use_overlay, m_lasso_animation;
  SbBool m_useFastEditing;
  unsigned long m_lasso_pattern, m_lasso_work_pattern;
  int m_num_lasso_points;
  SbColor m_lasso_color;
  
  // Misc
  SbBool m_shift_down;
  SbBool m_end_triangle_search, m_end_line_search, m_end_point_search;
  SbBool m_hasBeenOut;
  SbBool m_button_was_pressed;
  
  // Computation
  SbBox2f m_lassoBBox;
  SoPath *m_current_shape;
  SoState *m_current_state;
  SbViewportRegion m_current_viewport, m_current_local_viewport;
  SbBool m_selection_is_valid;

  ShapeType m_currentShapeType;
  SbVec3f  m_lassoFirstPoint;
  LassoRenderer *m_current_scene_offscreen;
  unsigned int m_shape_index;

  SbMatrix m_matrix2, m_matrix3, m_viewMatrix;

  SoGetBoundingBoxAction *m_bbox_action;
  SoSeparator *m_bbox_root;
  SoMatrixTransform *m_bbox_trans;
  SbBool m_do_selection;
  
  // To return lasso point coordinates
  SbVec2s *m_pixelPoints;
  SbVec3f *m_viewPoints;

  SbViewportRegion vpRegionEvent;

  SbBool m_makeSelection; // Activate/deactivate lasso selection (lasso is still drawn)

  SoMaterial* m_lassoMaterial;

  SoPickStyle* m_lassoPickStyle;

  SoSeparator* m_defaultSelectionSceneGraph;

  SoSeparator* m_customSceneGraphSeparator;

  SelectionEventCallback* m_startSelectionCallback;
  void* m_startSelectionCallbackUserData;

  SelectionEventCallback* m_endSelectionCallback;
  void* m_endSelectionCallbackUserData;

  SelectionEventCallback* m_movingSelectionCallback;
  void* m_movingSelectionCallbackUserData;

  bool m_isSelecting;

  const SoCamera* m_activeCamera;

  void* m_impl;

  // Private methods -----------------------------------------------------------
  
  // Misc
  void transformToLocalViewport(float &bbox_x_min, float &bbox_y_min, 
                                float &bbox_x_max, float &bbox_y_max);
  SbVec3f getVec3fPosition(const SbVec2f &pos, 
                           const SbViewportRegion &vp);
  SbVec3f getVec3fMousePosition(const SoEvent *event, 
                                const SbViewportRegion &vp);
  void vec3fToPixel(const SbVec3f &vec, 
                    const SbViewportRegion &vp, 
                    long &x, long &y);
  int isSquareInsideLasso(const SbVec4f &p0, const SbVec4f &p1,
                          const SbVec4f &p2, const SbVec4f &p3);

  SbBool isLassoPtsHalfPlaneLine(const SbVec4f &line0, const SbVec4f &line1) const;

  // Computation
  void selectObjects(SoNode *root);
  void doSelection();
  void computeEllipsePoints(const SbVec3f &start, const SbVec3f &end);

  // Laso animation
  void onLassoAnimation();
  static void onLassoAnimationCB(void *data, SoSensor *);

  // Lasso drawing on non overlay systems
  void initLasso(int x, int y);
  void drawLasso(int x, int y);
  void eraseLasso();

  // Traversal callbacks
  SoCallbackAction::Response examineCamera(SoCallbackAction *action, const SoNode* node);
  SoCallbackAction::Response examineSeparator(SoCallbackAction *action, const SoNode* node);
  SoCallbackAction::Response examineShape(SoCallbackAction *action, const SoNode* node);
  SoCallbackAction::Response postShape(SoCallbackAction *action);
  void examineTriangle(SoCallbackAction *action, 
                       const SoPrimitiveVertex *v1,
                       const SoPrimitiveVertex *v2,
                       const SoPrimitiveVertex *v3);
  void examineLine(SoCallbackAction *action, 
                   const SoPrimitiveVertex *v1,
                   const SoPrimitiveVertex *v2);
  void examinePoint(SoCallbackAction *action, 
                    const SoPrimitiveVertex *v1);
  SoCallbackAction::Response 
    onBBox(SoCallbackAction *action, const SoNode *node);
  SoCallbackAction::Response 
    onAnnoText3(SoCallbackAction *action, const SoNode *node);
  SoCallbackAction::Response 
    onCamera(SoCallbackAction *action, const SoNode *node);
  SoCallbackAction::Response 
    onTransform(SoCallbackAction *action, const SoNode *node);
  SoCallbackAction::Response 
    onShape(SoCallbackAction *action, const SoNode *node);
  SoCallbackAction::Response 
    onSeparator(SoCallbackAction *action, const SoNode *node);
  SoCallbackAction::Response 
    onBaseKitPre(SoCallbackAction *action, const SoNode *node);
  SoCallbackAction::Response 
    onBaseKitPost(SoCallbackAction *action, const SoNode *node);
  void onTriangle(SoCallbackAction *action, SoPrimitiveVertex *v1,
                  SoPrimitiveVertex *v2, SoPrimitiveVertex *v3);
  void onLineSegment(SoCallbackAction *action, 
                     SoPrimitiveVertex *v1,
                     SoPrimitiveVertex *v2);
  void onPoint(SoCallbackAction *action, SoPrimitiveVertex *v1);

  static void examineTriangleCB(void *data,
                                SoCallbackAction *action, 
                                const SoPrimitiveVertex *v1,
                                const SoPrimitiveVertex *v2,
                                const SoPrimitiveVertex *v3);
  static void examineLineCB(void *data,
                            SoCallbackAction *action, 
                            const SoPrimitiveVertex *v1,
                            const SoPrimitiveVertex *v2);
  static void examinePointCB(void *data,
                             SoCallbackAction *action, 
                             const SoPrimitiveVertex *v1);
  static SoCallbackAction::Response 
    examineCameraCB(void *data, SoCallbackAction *action, const SoNode *);
  static SoCallbackAction::Response 
    examineSeparatorCB(void *data, SoCallbackAction *action, const SoNode *);
  static SoCallbackAction::Response 
    examineShapeCB(void *data, SoCallbackAction *action, const SoNode *);
  static SoCallbackAction::Response 
    postShapeCB(void *data, SoCallbackAction *action, const SoNode *);
  static void onTriangleCB(void *object, 
                           SoCallbackAction *action, 
                           SoPrimitiveVertex *v1,
                           SoPrimitiveVertex *v2, 
                           SoPrimitiveVertex *v3);
  static void onLineSegmentCB(void *object, SoCallbackAction *action,
                              SoPrimitiveVertex *v1,
                              SoPrimitiveVertex *v2);
  static void onPointCB(void *object, 
                        SoCallbackAction *action, 
                        SoPrimitiveVertex *v1);
  static void onText2CB(void *object, 
                        SoCallbackAction *action, 
                        const SoNode *node);
  static void onAnnoText3CB(void *object, 
                            SoCallbackAction *action, 
                            const SoNode *node);
  static void onImageCB(void *object, 
                        SoCallbackAction *action, 
                        const SoNode *node);
  static void onCameraCB(void *object, 
                         SoCallbackAction *action, 
                         const SoNode *node);
  static void onTransformCB(void *object, 
                            SoCallbackAction *action, 
                            const SoNode *node);
  static void onSeparatorCB(void *object, 
                            SoCallbackAction *action, 
                            const SoNode *node);
  static SoCallbackAction::Response 
    onShapeCB(void *object, SoCallbackAction *action, const SoNode *node);
  static SoCallbackAction::Response 
    onBaseKitPreCB(void *object, SoCallbackAction *action, const SoNode *node);
  static SoCallbackAction::Response 
    onBaseKitPostCB(void *object, SoCallbackAction *action, const SoNode *node);
};

#endif  // _SO_EXTENDED_SELECTION_H_

