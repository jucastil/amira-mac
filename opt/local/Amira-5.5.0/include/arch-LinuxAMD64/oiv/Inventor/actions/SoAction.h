/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_ACTION_
#define  _SO_ACTION_

#include <Inventor/SoLists.h>
#include <Inventor/SoTypedObject.h>
#include <Inventor/threads/SbThreadRWMutex.h>
#include <Inventor/SoPath.h>
#include <Inventor/STL/cassert>

class SoCompactPathList;
class SoEnabledElementsList;
class SoActionMethodList;
class SoSceneManager;

#ifdef __hpux
#  undef IN_PATH
#endif

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoAction
//
//  This is the parent class for all traversal methods.  When
//  traversing, lookup is done based on the node type and the action
//  type.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Abstract base class for all actions.
 *
 * @ingroup actions
 *
 * @DESCRIPTION
 *   SoAction is the abstract base class for all actions. Classes derived from
 *   SoAction define operations to be applied at each node encountered during
 *   traversal of a scene graph. The function that gets called to implement the
 *   action for a particular node type is determined by a lookup table in the global
 *   database.
 *
 *   An action may be applied to a node (SoNode), a path (SoPath) or a list of
 *   paths (SoPathList).
 *
 *   \oivnetdoc
 *   \else
 *   Reference counting: Most actions call ref() on the node before 
 *   traversing the scene graph, then call unref() after traversal.  If the node 
 *   previously had a reference count of zero (the default), the call to unref()
 *   will cause the node to be destroyed.  A warning message is posted in this
 *   case when using a debug build of Open Inventor.
 *   \endoivnetdoc
 *
 * @SEE_ALSO
 *    SoNode,
 *    SoPath,
 *    SoPathList,
 *    SoCallbackAction,
 *    SoGLRenderAction,
 *    SoGetBoundingBoxAction,
 *    SoGetMatrixAction,
 *    SoHandleEventAction,
 *    SoPickAction,
 *    SoRayPickAction,
 *    SoSearchAction,
 *    SoWriteAction
 *
 *
 */

class INVENTOR_API SoAction: public SoTypedObject {

 public:
  /**
   * Destructor.
   */
  virtual ~SoAction();

  /**
   * Returns the type identifier for this class.
   */
  static SoType       getClassTypeId();

  /**
   * Initiates an action on the graph defined by a node.
   */
  virtual void        apply(SoNode *node);

  /**
   * Initiates an action on the graph defined by a path.
   */
  virtual void        apply(SoPath *path);

  /**
   * Initiates an action on the graph defined by a list of
   * paths. TRUE can be passed for the @B obeysRules @b flag if the given path list
   * has the following 4 properties:
   *   -# All paths have the same head node.
   *   -# Paths are sorted in traversal order.
   *   -# If one path ends at node @B A@b, no other path continues through @B A@b.
   *   -# No two paths are the same.
   *
   * These rules will be obeyed by path lists returned by picking and by searches for
   * non-group nodes.
   */
  virtual void        apply(const SoPathList &pathList,
                            SbBool obeysRules = FALSE);

  /**
   * Invalidates the current traversal state in the action, forcing it to be
   * recreated when the action is next applied. This is typically unnecessary in most
   * applications.
   */
  virtual void        invalidateState();

  /**
   * This function stops the action in the current Scene Graph branch.
   * Note: It doesn't mean we kill the action!
   *
   * It is mainly used to stop the GetBoundingBox action in the SoBBox node.
   */
  void stopActionInBranch();

  /**
   * This function indicates if the action must stop in the current branch.
   *
   * @return TRUE if the action must continue for this branch.
   */
  SbBool getContinueActionInBranchFlag() const;

  /**
   * This function resets the continue action flag.
   */
  void resetContinueActionInBranchFlag();

  /**
   * This is used to define the way an action is distributed across a cluster
   */
  enum DistribMode {
    /** Action is only applied by the application. */
    LOCAL_ONLY,
    /** Action is only applied by OIRU of the cluster */
    CLUSTER_ONLY,
    /** Both application and cluster apply the action */
    ALL
  };

  /**
   * Tell the action to use alternate representations during traversal when available. @BR
   * See SoNode::getAternateRep(). Default is FALSE.
   * When true, it is the responsibility of each SoNode derived
   * object to choose to provide or not an alternate representation for
   * a given action.
   */
  void useAlternateRep(const SbBool enable);

  /**
   * Returns TRUE if current action is using alternate representations.
   * Default is FALSE.
   */
  SbBool isUsingAlternateRep() const;

  /** 
   * Set the scene manager associated with this action (if any ).
   * When appropriate, this allows the action to query information like the OpenGL
   * rendering context.  The SoSCeneManager class calls this method automatically
   * for the actions that it creates (SoHandleEventAction, SoRayPickAction, etc).
   */
  void setSceneManager(SoSceneManager* mgr);

  /**
  * Return the SoSceneManager associated with this action.
  */
  SoSceneManager* getSceneManager() const;

 SoEXTENDER public:

  // Null action method that can be stored in lookup table when desired
  static void         nullAction(SoAction *, SoNode *);

  // This enum is used to determine what the action is being applied to
  enum AppliedCode {
    NODE,                   // Applied to graph rooted by a node
    PATH,                   // Applied to graph defined by a path
    PATH_LIST               // Applied to graphs defined by list of paths
  };

  // This enum may be used during traversal of nodes to indicate
  // where the node is with respect to the path being traversed
  enum PathCode {
    NO_PATH,                // Not traversing a path
    IN_PATH,                // In middle of path chain (not tail node)
    BELOW_PATH,             // Tail node of path or below tail node
    OFF_PATH                // None of the above (Probably to the left)
  };

  // Returns code indicating what action is being applied to
  AppliedCode         getWhatAppliedTo() const   { return appliedTo.code; }

  // These returns a pointer to the node, path, or path list the
  // action is being applied to. Each returns NULL if the action is
  // not being applied to the appropriate class.
  SoNode *            getNodeAppliedTo() const  { return appliedTo.node; }
  SoPath *            getPathAppliedTo() const  { return appliedTo.path; }
  // A single path list may be split into several, one for each
  // different head node. These methods allow subclasses to
  // determine the current path list, the original path list, and
  // whether the current list is the last one from the original
  const SoPathList *  getPathListAppliedTo() const
    { return appliedTo.pathList; }
  const SoPathList *  getOriginalPathListAppliedTo() const
    { return appliedTo.origPathList; }
  SbBool              isLastPathListAppliedTo() const
    { return appliedTo.isLastPathList; }

  /**
   * Returns path code based on where current node (the node at the
   * end of the current path) lies with respect to the path(s) the
   * action is being applied to. If this returns IN_PATH, indices is
   * set to point to an array of indices corresponding to the
   * children that continue the paths and numIndices is set to the
   * number of such children.
   * [OIV-WRAPPER-ARG NO_WRAP,ARRAY{numIndices}]
   */
  PathCode    getPathCode(int &numIndices, const int *&indices)
    {   if (appliedTo.curPathCode == IN_PATH) {
      usePathCode(numIndices, indices);
    }
    return appliedTo.curPathCode;
    }


  // Does traversal of a graph rooted by a node
  // now defined in the .cxx
  void                traverse(SoNode *node);


  // Returns TRUE if the traversal has reached a termination condition
  SbBool              hasTerminated() const   { return terminated; }

  // Returns a pointer to the path accumulated during traversal,
  // i.e., the chain of nodes from the root of the traversed graph
  // to the current node being traversed.
  const SoPath *      getCurPath();

  // Get the state from the action
  // Note: Will return NULL if action has not been applied to anything
  //       or if invalidateState has been called.
  SoState *           getState() const        { return state; }

  // Changed to virtual so that derived actions that need to do
  // things to the state such as the GLRenderAction. This action
  // needs to change the value of whatChanged to ALL if the state has
  // been recreated because the number of elements has changed.

  // Creates state if it is NULL or it is no longer valid because new
  // elements have been enabled since it was created.  Automatically
  // called by the apply() methods, but can be useful for application
  // to get a non-null state pointer to "pre-load" certain elements.
  virtual void                setUpState();

  /** Returns the list of enabled elements for a given action subclass
   * [OIV-WRAPPER NAME{EnableElements}]
   * [OIV-WRAPPER-RETURN-TYPE NO_WRAP]
   */
  virtual const SoEnabledElementsList & getEnabledElements() const;

  /**
   * Sets/Gets pipe identifier in the range [1..N] associated to this render action
   * while running a ScaleViz Multipipe configuration.
   */
  void setPipeId( int id );
  int getPipeId() const;

  /** Returns TRUE if this action is currently being applied. */
  bool isBeingApplied() { return m_isBeingApplied; }

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  // Initialize ALL Inventor action classes
  static void         initClasses();
  static void         exitClasses();

  /** Returns TRUE if given elements is enabled for this action. */
  virtual bool isEnabledElement( const SoType& ) const;

  // These methods maintain the current path accumulated so far
  // during traversal. The action needs to know whether this path is
  // a subset of the path being applied to; it saves this info in
  // the onPath variable. Before a node is pushed onto the current
  // path, call getOnPath() to determine the current setting. The
  // value of this flag should be passed in to popCurPath() so the
  // onPath variable can be restored.
  PathCode            getCurPathCode() const { return appliedTo.curPathCode;}
  void                pushCurPath(int childIndex);
  void                popCurPath(PathCode prevPathCode);
  // This is virtual, so that SoCallbackAction can use current node.
  virtual SoNode *    getCurPathTail();

  // called by inline getPathCode:
  void                usePathCode(int &numIndices, const int *&indices);

  // Optimized versions of push/pop when we know path codes won't
  // change:
  void                pushCurPath()
    { curPath.append(-1); }
  void                popPushCurPath(int childIndex)
    { curPath.setTail(childIndex);}
  void                popCurPath()
    { curPath.pop(); }

  // added two switch..Traversal functions for SoRenderList
  //  Switches traversal to path, without calling beginTraversal.
  //  This allows a node during traversal to stop the current traversal
  //  method and start rendering a path.  The head of the path needs
  //  to be the currently traversed node, or a child.
  void                switchToPathTraversal(SoPath *path);

  // Switches traversal to node not in current scene graph,
  // without calling beginTraversal and keeping state the same.
  // The curPath starts over again with this node.
  // Saves appliedTo struct and curPath, and then sets up
  // appliedTo struct for this node.
  void                switchToNodeTraversal(SoNode *node);

  SbBool hasChangedState() { return m_hasStateChanged; }

  DistribMode getDistribMode() { return m_distribMode; }

  // Enter critical section for this action
  inline void lock()
  { m_criticalSection->lock(); }

  // Exit critical section for this action
  inline void unlock()
  { m_criticalSection->unlock(); }

#if defined(_DEBUG)
  SbPList* m_dbCheckPoint;
#endif

 protected:
  // Constructor
  SoAction();

  // WARNING : Copy constructor should never be called.
  // WARNING : Implemented here only to add a debug message to derived class.
  SoAction(const SoAction&);

  // Begins traversal of an action at the given node. The default
  // method just calls traverse(node). This is virtual to allow
  // subclasses to do extra work before or after traversing the node.
  virtual void        beginTraversal(SoNode *node);

  // Ends traversal of an action at the given node. By default
  // nothing is gone
  virtual void        endTraversal(SoNode *) { ; }

  // Allows subclass instance to indicate that traversal has reached
  // a termination condition
  void                setTerminated(SbBool flag)      { terminated = flag; }

  // This method is used when applying an action to an SoPathList.
  // It returns TRUE if the action should create a compact version
  // of the path list before applying itself to it. The default
  // method returns TRUE, since the compact version is more
  // efficient. Some actions may choose to return FALSE; for
  // example, the SoWriteAction applies itself to each path
  // separately, so it doesn't need the extra overhead of compacting
  // the list.
  virtual SbBool      shouldCompactPathLists() const;

SoINTERNAL protected:
  SoState             *state;         // Traversal state

  // This indicates if we must stop this action in the current Scene Graph branch
  SbBool m_continueInBranchFlag;

  // This is the current path through the graph the action is being
  // applied to
  SoLightPath         curPath;

  // Holds list of enabled elements for the SoAction class
  static SoEnabledElementsList *enabledElements;

  // ... and the methods
  static SoActionMethodList *methods;

  SbBool m_hasStateChanged;

  virtual bool mustTraverseDepth() { return false; }

  DistribMode m_distribMode;

 SoINTERNAL public:

  virtual SoActionMethodList* getActionMethods();
  SbBool getUseAlternateRep() const;
  SbBool isForcedUseAlternateRep() const;

 private:

  // Type identifier
  static SoType      classTypeId;
  static bool s_defaultAlternateRepUsage;

  SbThreadMutex* m_criticalSection;

  // This structure holds the necessary information about what the
  // action is being applied to. It allows this information to be
  // saved and restored when necessary.
  struct AppliedTo {
    AppliedCode code;
    SoNode *node;             // If code is NODE
    SoPath *path;             // If code is PATH
    const SoPathList *pathList;       // If code is PATH_LIST
    const SoPathList *origPathList;
    SoCompactPathList *compactPathList;
    int isLastPathList;
    PathCode curPathCode;
  } appliedTo;

  // This is set to TRUE while the action is being applied, so we
  // can tell if the action is being applied recursively.
  bool m_isBeingApplied;

  // Indicate if we should ask for alternate representation or not
  // default is FALSE.
  SbBool m_useAlternatRep;

  // Indicate if we force for using alternate representation or not
  // default is FALSE.
  SbBool m_forceUseAlternateRep;

  // This holds the current path (nodes and childindices) whenever
  // action->getCurPath is called:
  SoTempPath  *       tempPath;


  // Holds enabled-elements counter when state is created; used to
  // determine whether list of enabled elements is up to date.
  int                 enabledElementsCounter;

  // This is TRUE if the action has reached a termination condition
  SbBool              terminated;

  // Stores next index in path being applied to so a pointer to it
  // can be returned
  int                 index;

  // Cleans up after an action is done
  void                cleanUp();

  // Splits a sorted path list based on head nodes, then applies to each
  void                splitPathList(const SoPathList &sortedList,
                                    const SoPathList &origPathList);

  // Applies action to sorted path list
  void                apply(const SoPathList &sortedList,
                            const SoPathList &origPathList,
                            SbBool isLastPathList);

  int m_pipeId;   // this render action pipe id

  SoSceneManager* m_sceneManager;

  friend class SoDB;

};

#ifndef HIDDEN_FROM_DOC
//////////////////////////////////////////////////////////////////////////////
//
//  Classes can use this macro to enable a specific element class
//  within a specific action class. E.g.:
//
//      SO_ENABLE(SoGetBoundingBoxAction, SoModelMatrixElement);
//

#define SO_ENABLE(actionClass, elementClass)                            \
  if ( elementClass::getClassTypeId().isBad() )                         \
          elementClass::initClass();                                    \
        actionClass::enableElement(elementClass::getClassTypeId(),      \
                                   elementClass::getClassStackIndex())

//
//////////////////////////////////////////////////////////////////////////////
#endif // HIDDEN_FROM_DOC


#ifndef HIDDEN_FROM_DOC
typedef void    SoActionMethod(SoAction *, SoNode *);
typedef void    SoActionMethodUserData(SoAction *, SoNode *, void *);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoActionMethodList
//
//  Internal class.  A list of routines to call, one for each node type.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoActionMethodList : public SbPList {

 public:
  // Constructor.  Pass in list from parent action.
  SoActionMethodList(SoActionMethodList *parentList);
  ~SoActionMethodList();

  // Operator used to get and set methods.  The list will grow
  // dynamically as we access items off the end of the list, and
  // entries will be initialized to NULL.
  /*SoActionMethod* &    operator [](int i) const
    { return ((SoActionMethod* &)((*(const SbPList *)this)[i])); }*/

  // Add a method to the appropriate place in the list.
  void                addMethod(SoType nodeType, SoActionMethod* method);

  // Add a method to the appropriate place in the list.
  void                addMethod(SoType nodeType, SoActionMethodUserData* method, void* userData);

  // Flag which indicates if at least one function with user
  // data has been specifed.
  bool                hasFunctionWithUserData();
  void*               userData(int i);

  // This MUST be called before using the list.  It fills in NULL
  // entries with their parents' method.
  void                setUp();

  // These methods need to be public for the protection off the
  // [] operator. The mutex has to be lock and unlock to make
  // the SbPList thread safe. They're used in SoAction::traverse().
  void readlockMutex() { actionMethodListRWMutex->readlock(); }
  void readunlockMutex() { actionMethodListRWMutex->readunlock(); }
  void writelockMutex() { actionMethodListRWMutex->writelock(); }
  void writeunlockMutex() { actionMethodListRWMutex->writeunlock(); }

 private:
  void*     parentMethod(SoType);   // Method from parent node
  void*     parentMethod(SoType, int&);   // Method from parent node
  SoActionMethodList  *parent;
  int                 numValidTypes;   // Stores the number of types at most
  // recent setup

  // Dummy action used internally
  static void         dummyAction(SoAction *, SoNode *);

  // OIV.NET specific.
  // Function user data. NULL if any present
  SbPList             *functionUserData;

  // Mutex to protect access to the SbPList
  SbThreadRWMutex *actionMethodListRWMutex;
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoEnabledElementsList
//
//  Internal class.  A list of elements enabled for a given action
//  class. Lists of elements can be merged, allowing an action class
//  to inherit enabled elements from its parent class.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoEnabledElementsList
{

 public:
  // Constructor
  SoEnabledElementsList(SoEnabledElementsList *parentList);

  // Returns list of elements.  This automatically merges the
  // elements with elements enabled in the parentList.
  const SoTypeList &  getElements() const;

  // Adds an element to the list if it's not already in it
  void enable(SoType elementType, int stackIndex);

  // Returns the current setting of the global counter used to
  // determine when lists are out of date.
  static int getCounter();

  // Reset the element counter to 0;
  static void resetCounter();

 private:
  // This maintains a global counter used to determine when lists
  // are out of date. It is incremented whenever a new element is
  // added to a list.
  static int counter;

  // Used to protect access to the ststai counter variable.
  static SbThreadMutex counterMtx;

  // And a per-instance counter so we don't merge enabled elements
  // with the parent list unnecessarily.
  int setUpCounter;

  // This list holds type id's of enabled elements, indexed by the
  // stack index of the elements.
  SoTypeList elements;

  // Pointer to parent's list of enabled elements (NULL for
  // SoAction).
  SoEnabledElementsList *parent;
};

#endif // HIDDEN_FROM_DOC

#endif /* _SO_ACTION_ */

