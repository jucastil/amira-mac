/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Mott (MMM yyyy)
** Modified by : Thad Beier (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SELECTION_
#define  _SO_SELECTION_

#include <Inventor/SbColor.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/nodes/SoSeparator.h>

class SoCallbackList;
class SoEvent;
class SoHandleEventAction;
class SoSearchAction;
class SoPickedPoint;
class SoPickedPointList;
class SoTypeList;
class SoSelection;
class SoPath;

// callback function prototypes
/** 
 * [OIV-WRAPPER NAME{PathCB}] 
 */
typedef void SoSelectionPathCB(void *userData, SoPath *path);
/** 
 * [OIV-WRAPPER NAME{ClassCB}] 
 */
typedef void SoSelectionClassCB(void *userData, SoSelection *sel);
/** 
 * [OIV-WRAPPER NAME{PickCB}] 
 */
typedef SoPath * SoSelectionPickCB(void *userData, const SoPickedPoint *pick);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSelection
//
//  Selection group node: Manages selection list from picks of its children.
//
//////////////////////////////////////////////////////////////////////////////


 #ifdef OIV_NET_DOC
 /**
 * Manages a list of selected objects.
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 *   SoSelection defines a node which can be inserted into a scene graph and will
 *   generate and manage a selection list from picks on any node in the subgraph
 *   below it. Nodes are selected based on a current selection policy. Delegate
 *   functions report back to the application when a path has been selected or
 *   deselected. The selection list can also be managed programmatically.
 *   
 *   When handling events, by default SoSelection makes sure that the mouse release event was
 *   over the same object as the mouse press event before changing the list of
 *   selected objects. This allows users to mouse down on an object, change their
 *   mind and move the cursor off the object, then release the mouse button without
 *   altering the selection. See the #SetPickMatching method.
 *  
 *   The selection can be highlighted automatically by calling the render
 *   area's redrawOnSelectionChange method with the SoSelection node, and 
 *   calling the setGLRenderAction method with, for example, an instance of
 *   SoBoxHighlightAction.  
 * 
 *   It is possible to use multiple SoSelection nodes in a scene graph, but
 *   there are a few things to keep in mind:
 *   - If two selection nodes could potentially select the same geometry,
 *     the geometry will be selected by the selection node lowest in the
 *     scene graph (the closest ancestor of the geometry).
 *   - The automatic redraw on selection change (#RedrawOnSelectionChange)
 *     feature currently only works for a single selection node. You can
 *     work around this by calling #ScheduleRedraw() in a selection delegate.
 *   - The box and line highlighting render actions currently search for
 *     the first selection node in the scene graph and only highlight
 *     geometry selected by that selection node. You can work around this
 *     by creating a custom highlight action.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Selection {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR policy               @TD SHIFT
 *       @TR fastEditing          @TD DISABLE
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoEventCallback,
 *    SoWinRenderArea,
 *    SoBoxHighlightRenderAction,
 *    SoLineHighlightRenderAction
 * 
 * 
 */
#else
 /**
 * Manages a list of selected objects.
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 *   SoSelection defines a node which can be inserted into a scene graph and will
 *   generate and manage a selection list from picks on any node in the subgraph
 *   below it. Nodes are selected based on a current selection policy. \oivnetdoc Delegate \else Callback \endoivnetdoc
 *   report back to the application when a path has been selected or
 *   deselected. The selection list can also be managed programmatically.
 *   
 *   When handling events, by default SoSelection makes sure that the mouse release event was
 *   over the same object as the mouse press event before changing the list of
 *   selected objects. This allows users to mouse down on an object, change their
 *   mind and move the cursor off the object, then release the mouse button without
 *   altering the selection. See the #setPickMatching method.
 *  
 *   The selection can be highlighted automatically by calling the render
 *   area's redrawOnSelectionChange method with the SoSelection node, and 
 *   calling the setGLRenderAction method with, for example, an instance of
 *   SoBoxHighlightAction.  
 *   For example:
 * <PRE> 
 *       pViewer->redrawOnSelectionChange( pSelectionNode );
 *       pViewer->setGLRenderAction( new SoBoxHighlightRenderAction() );
 * </PRE>
 *   The application can also create a custom highlight action. See the chapter "Creating
 *   a Selection Highlight Style" in the @B Inventor Toolmaker @b.
 * 
 *   It is possible to use multiple SoSelection nodes in a scene graph, but
 *   there are a few things to keep in mind:
 *   - If two selection nodes could potentially select the same geometry,
 *     the geometry will be selected by the selection node lowest in the
 *     scene graph (the closest ancestor of the geometry).
 *   - The automatic viewer redraw on selection change (renderArea's redrawOnSelectionChange method)
 *     feature currently only works for a single selection node. You can
 *     work around this by calling renderArea's scheduleRedraw() method in a selection \oivnetdoc delegate \else callback \endoivnetdoc.
 *   - The box and line highlighting render actions currently search for
 *     the first selection node in the scene graph and only highlight
 *     geometry selected by that selection node. You can work around this
 *     by creating a custom highlight action.
 * 
 *   When a node is selected, SoSelection stores a path, i.e., an SoPath, to
 *   the selected node. SoPath references (increments the reference count) of
 *   every node in the path, including the SoSelection node, which is normally
 *   the head of the path. So the SoSelection node may not be destroyed when 
 *   expected if it still contains some selection paths. In general the #deselectAll
 *   method should be called before, for example, removing the SoSelection node
 *   from its parent node.
 *
 * @FILE_FORMAT_DEFAULT
 *    Selection {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR policy               @TD SHIFT
 *       @TR fastEditing          @TD DISABLE
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoEventCallback,
 *    SoWinRenderArea,
 *    SoBoxHighlightRenderAction,
 *    SoLineHighlightRenderAction
 * 
 * 
 */ 
#endif

class INVENTOR_API SoSelection : public SoSeparator {

  SO_NODE_HEADER(SoSelection);

 public:
  /**
   * Creates a selection node with the default settings.
   */
  SoSelection();
  /**
   * Constructor that specifies the approximate number of children.
   */
  SoSelection(int nChildren);
    
  //
  // Selection policy
  // ----------------

  // Default selection policy is SoSelection::SHIFT.
  enum Policy {
    /**
     * Picking an object object clears current selection, then 
     * selects object. Picking on nothing clears current selection. 
     * Only one object may be selected at a time. 
     */
    SINGLE,
        
    /**
     * Picking an object toggles its selection status. Picking on
     * nothing does nothing. Multiple objects may be selected. 
     */
    TOGGLE,
        
    /**
     * When shift key is down, selection policy is TOGGLE. When shift key is up,
     * selection policy is SINGLE. Multiple objects may be selected. 
     */
    SHIFT,

    /**
     * Disable selection (behave like a normal SoSeparator).
     */
    DISABLE
  };

  // Fields
  /**
   * Selection policy that is followed in response to user interaction.
   * Use enum #Policy. Default is SHIFT.
   * 
   */
  SoSFEnum            policy;

  //
  // Selection list management
  // -------------------------

  /**
   * Selects the passed path by adding it to the selection list. The selection node
   * must lie in the path. The path is copied and truncated such that the selection
   * node is the head of the path. If the selection node does not lie in the path,
   * the selection list remains unchanged. This method ignores the current selection
   * policy.
   */
  void                select(const SoPath *path);    
  /**
   * Selects the passed node by creating a path to it, and adding the path to the
   * selection list by calling @B select(path) @b. If there is more than one
   * instance of node beneath the selection node, the created path will be the first
   * instance found.
   */
  void                select(SoNode *node);

  /**
   * Deselects the passed path by removing it from the selection list.
   */
  void                deselect(const SoPath *path);
  /**
   * Deselects a path by removing it from the selection list. The argument which
   * specifies which path in the list to be removed.
   */
  void                deselect(int which);
  /**
   * Deselects the passed node by creating a path to it, and removing the node from
   * the selection list by calling @B deselect(path) @b. If there is more than one
   * instance of node beneath the selection node, the created path will be the first
   * instance found.
   */
  void                deselect(SoNode *node);

  /**
   * Toggles the selection status of the passed path - if the path is in the selection
   * list, it is removed; if not in the list, it is added.
   */
  void                toggle(const SoPath *path);
  /**
   * Toggles the selection status of the passed node by creating a path to it, then
   * calling @B toggle(path) @b. If there is more than one instance of node beneath
   * the selection node, the created path will be the first instance found.
   */
  void                toggle(SoNode *node);

  /**
   * Returns @B TRUE @b if the passed path is selected, that is, if it is in the
   * selection list.
   */
  SbBool              isSelected(const SoPath *path) const;
  /**
   * Returns @B TRUE @b if the passed node is selected by creating a path to it,
   * then calling isSelected(). If there is more than one instance of node
   * beneath the selection node, the created path will be the first instance found.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  SbBool              isSelected(SoNode *node) const;
  /**
   * Returns @B TRUE @b if the passed node is selected by creating a path to it,
   * then calling isSelected(). If there is more than one instance of node
   * beneath the selection node, the created path will be the first instance found.
   */
  SbBool              isSelected(const SoNode *node) const;
    
  /**
   * Deselects all paths in the selection list, that is, clear the list.
   */
  void                deselectAll();

  /**
   * Returns the number of paths in the selection list.
   */
  int                 getNumSelected() const  { return selectionList.getLength(); }
  /**
   * Returns the list of selected paths.
   */
  const SoPathList    *getList() const { return &selectionList; }
  /**
   * Returns the ith path in the selection list.
   */
  SoPath              *getPath(int index) const;

  /**
   * Returns the ith path in the selection list.
   */
  SoPath *            operator [](int i) const
    { return getPath(i); }

  /** 
   * Sets the radius (in pixels) around the viewport-space point through which the ray
   * passes when doing ray picking. Ray picking is performed when getPickedPoint()
   * is called. The pick radius set here is only used when testing the ray against
   * lines and points.
   */
  void                setPickRadius(float radiusInPixels) 
    { m_pickRadius = radiusInPixels; }

  /** 
   * Returns the radius (in pixels) around the viewport-space point through which the ray
   * passes when doing ray picking.
   */
  float               getPickRadius() const
    { return m_pickRadius; }
  //
  // Selection change callbacks
  // --------------------------
  //
  // Callbacks are invoked when an object is selected or deselected.
  //
    
  /**
   * Adds selection callback.
   * The selection callbacks are invoked every time an object is selected, whether it
   * be from user interaction or from method call. The callbacks are invoked after
   * the object has been added to the selection list.
   * [OIV-WRAPPER EVENT_NAME{Selection}]
   */
  void    addSelectionCallback(SoSelectionPathCB *f, void *userData = NULL);
  /**
   * Removes selection callback.
   * The selection callbacks are invoked every time an object is selected, whether it
   * be from user interaction or from method call. The callbacks are invoked after
   * the object has been added to the selection list.
   * [OIV-WRAPPER EVENT_NAME{Selection}]
   */
  void    removeSelectionCallback(SoSelectionPathCB *f, void *userData = NULL);
    
  /**
   * Adds deselection callback.
   * The deselection callbacks are invoked every time an object is deselected,
   * whether it be from user interaction or from method call. This is invoked after
   * the object has been removed from the selection list.
   * [OIV-WRAPPER EVENT_NAME{Deselection}]
   */
  void    addDeselectionCallback(SoSelectionPathCB *f, void *userData = NULL);
  /**
   * Removes deselection callback.
   * The deselection callbacks are invoked every time an object is deselected,
   * whether it be from user interaction or from method call. This is invoked after
   * the object has been removed from the selection list.
   * [OIV-WRAPPER EVENT_NAME{Deselection}]
   */
  void    removeDeselectionCallback(SoSelectionPathCB *f, void *userData = NULL);

  /**
   * Adds start callback.
   * The start callbacks are invoked when the user has initiated an interactive
   * change to the selection list (by picking objects). This will be followed by
   * invocations of the select and/or deselect callbacks, finally followed by each
   * finish callback. A start callback can be used, for instance, to save the current
   * selection for later restoration (e.g. undo/redo). The start callbacks are not
   * called when the selection list is changed programmatically.
   * [OIV-WRAPPER EVENT_NAME{StartSelection}]
   */
  void    addStartCallback(SoSelectionClassCB *f, void *userData = NULL);
  /**
   * Removes start callback.
   * The start callbacks are invoked when the user has initiated an interactive
   * change to the selection list (by picking objects). This will be followed by
   * invocations of the select and/or deselect callbacks, finally followed by each
   * finish callback. A start callback can be used, for instance, to save the current
   * selection for later restoration (e.g. undo/redo). The start callbacks are not
   * called when the selection list is changed programmatically.
   * [OIV-WRAPPER EVENT_NAME{StartSelection}]
   */
  void    removeStartCallback(SoSelectionClassCB *f, void *userData = NULL);
    
  /**
   * Adds finish callback.
   * The finish callbacks are invoked when the user has finished interactively
   * changing the selection list (by picking objects). This was preceded by an
   * invocation of each start callback, and invocations of the select and/or deselect
   * callbacks. The finish callbacks are not called when the selection list is
   * changed programmatically.
   * [OIV-WRAPPER EVENT_NAME{FinishSelection}]
   */
  void    addFinishCallback(SoSelectionClassCB *f, void *userData = NULL);
  /**
   * Removes finish callback.
   * The finish callbacks are invoked when the user has finished interactively
   * changing the selection list (by picking objects). This was preceded by an
   * invocation of each start callback, and invocations of the select and/or deselect
   * callbacks. The finish callbacks are not called when the selection list is
   * changed programmatically.
   * [OIV-WRAPPER EVENT_NAME{FinishSelection}]
   */
  void    removeFinishCallback(SoSelectionClassCB *f, void *userData = NULL);

  /**
  * The pick filter callback is invoked when a pick has occurred and the selection
  * node is about to change the selection list. The callback function returns the
  * path that the selection node should use when selecting and deselecting. If no
  * pick callback is registered (the default), the selection node will use the path
  * returned by SoPickedPoint::getPath() on the picked point associated with
  * the event being processed. The returned path should not be ref'd - selection
  * will ref() and unref() it. (See SoPath::unrefNoDelete().)
  * 
  * Note that a picked object may or may not be a child of the selection node. A
  * selection node will only select paths that pass through it. Possible return
  * values from the callback:
  * 
  * [a] NULL - selection behaves as if nothing was picked (i.e. for SINGLE and SHIFT
  * policies, this clears the selection list). Handle event action traversal
  * halts.
  * 
  * [b] Path - this path will be selected/deselected according to the selection
  * policy (it must lie under the selection node). Handle event action traversal
  * halts.
  * 
  * [c] Path containing @B only @b the selection node - apply the selection policy
  * as if nothing was picked. Handle event action traversal continues.
  * 
  * [d] Path not passing through the selection node - selection ignores this pick
  * event and no change is made to the selection list. Handle event action traversal
  * continues.
  * 
  * A simple way to tell selection to ignore the pick is to return an SoPath with no
  * nodes in it. (i.e. @B return new SoPath; @b) Selection will always ref
  * the path returned by the callback, make a copy of the path, then unref the
  * path.
  * 
  * The callOnlyIfSelectable argument, when set to TRUE, means the pick callback
  * function will only be invoked on picks which pass through the selection node.
  * When FALSE, all picks will be passed to the callback whether they pass through
  * the selection or not.
  */
  void    setPickFilterCallback(
                                SoSelectionPickCB *f,
                                void *userData = NULL, 
                                SbBool callOnlyIfSelectable = TRUE); 
    
  /**
   * SoSelection will pick once on mouse down and once on mouse up, and make sure the
   * picks match before changing the selection list. This allows the user to pick
   * down on an object, change their mind and drag off the object, release the mouse
   * button and not affect the selection. Pass TRUE to enable this behavior. Pass
   * FALSE to disable this, meaning whatever is picked on a mouse release is added
   * to/removed from the selection list. Default is pick-matching on.
   */
  void    setPickMatching(SbBool pickTwice) { pickMatching = pickTwice; }
  /**
   * Returns pick matching flag.
   */
  SbBool  isPickMatching() const { return pickMatching; }
    
 SoEXTENDER public:
  // Traversal routine for SoHandleEventAction - this will call
  // action->setHandled() if the event is handled
  virtual void        handleEvent(SoHandleEventAction *action);

 SoINTERNAL public:

  virtual void notify(SoNotList *list);

  // Selection notify callbacks - invoked whenever the selection changes.
  // Used by the render area to redraw for selection highlighting.
  void   addChangeCallback(SoSelectionClassCB *f, void *userData = NULL);
  void   removeChangeCallback(SoSelectionClassCB *f, void *userData = NULL);
   
  SbBool  getPickMatching() const { return pickMatching; }

  // Internal:
  static void         initClass();
  static void         exitClass();

 protected:
  // List of paths of selected objects
  SoPathList          selectionList;

  // Selection callback lists
  SoCallbackList      *selCBList;
  SoCallbackList      *deselCBList;
  SoCallbackList      *startCBList;
  SoCallbackList      *finishCBList;
    
  // Pick filter is a single callback function, not a list
  SoSelectionPickCB   *pickCBFunc;
  void                *pickCBData;
  SbBool              callPickCBOnlyIfSelectable;
    
  // Change callbacks
  SoCallbackList      *changeCBList;
    
  // Mouse down picked path
  SoPath              *mouseDownPickPath;
  SbBool              pickMatching;
  SbBool              m_mouse_button_down;
  // Selection policies (shiftSelection is a combination of these)
  // invokeSelectionPolicy() is called from handleEvent() - for a customized
  // selection policy, either derive a class and write a new handleEvent()
  // method, or use an SoEventCallback node placed such that it receives
  // events before the selection node.
  void                invokeSelectionPolicy(SoPath *path, SbBool shiftDown);
  void                performSingleSelection(SoPath *path);
  void                performToggleSelection(SoPath *path);
    
  // This copies the path so the copy is rooted by 'this'.
  // Returns NULL if 'this' not found in the passed path.
  SoPath              *copyFromThis(const SoPath *path) const;
    
  // addPath() assumes the path is rooted by 'this'
  void                addPath(SoPath *path);
  void                removePath(int which);
    
  // This locates path in the selection list. The head of this path
  // does not necessarily have to be 'this'.
  int                 findPath(const SoPath *path) const;
    
  // Destructor removes everything from the list.
  ~SoSelection();

  //The pick radius
  float               m_pickRadius;

 private:
  // This action is used to search for nodes.
  static SoSearchAction *searchAction;

  // this is called from the two constructors.
  void                constructorCommon();  


};



#endif /* _SO_SELECTION_ */

