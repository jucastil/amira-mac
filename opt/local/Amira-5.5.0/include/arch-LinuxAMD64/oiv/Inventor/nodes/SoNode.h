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


#ifndef  _SO_NODE_
#define  _SO_NODE_

#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/SoLists.h>
#include <Inventor/SbString.h>
#include <Inventor/SoType.h>
#include <Inventor/sensors/SoDataSensor.h>
#include <Inventor/STL/vector>

class SoNodeList;
class SoAction;
class SoCallbackAction;
class SoChildList;
class SoFieldData;
class SoGLRenderAction;
class SoGetBoundingBoxAction;
class SoGetMatrixAction;
class SoHandleEventAction;
class SoInput;
class SoOutput;
class SoPickAction;
class SoRayPickAction;
class SoSearchAction;
class SoWriteAction;
class SbProjectionCoordinates;
class SoGetPrimitiveCountAction;
class SoComputeRenderUnitIDAction;
class SoNodeImpl;
class SoCache;
class SoDistributeAction;
class SoState;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNode
//
//  Base SoNode class (abstract).
//
//////////////////////////////////////////////////////////////////////////////


#ifdef OIV_NET_DOC
/**
* Abstract base class for all database nodes.
* 
* @ingroup nodes
* 
* @DESCRIPTION
*   This is the abstract base class from which all scene graph node classes are
*   derived.
* 
* @FILE_FORMAT_DEFAULT
*    This is an abstract class. See the reference page of a derived class for the
*   format and default values.
* 
* @ACTION_BEHAVIOR
*    SoSearchAction @BR
*        If the node reference, type, or name matches the search criteria, returns a path
*        to the node.
* 
*    SoWriteAction @BR
*        Writes the contents of the node to the current SoOutput.
* 
* 
* @SEE_ALSO
*    SoPath,
*    SoAction,
*    SoNodeKit
* 
* 
*/ 
#else
/**
* Abstract base class for all database nodes.
* 
* @ingroup nodes
* 
* @DESCRIPTION
*   This is the abstract base class from which all scene graph node classes are
*   derived.
* 
* @FILE_FORMAT_DEFAULT
*    This is an abstract class. See the reference page of a derived class for the
*   format and default values.
* 
* @ACTION_BEHAVIOR
*    SoSearchAction @BR
*        If the node pointer, type, or name matches the search criteria, returns a path
*        to the node.
* 
*    SoWriteAction @BR
*        Writes the contents of the node to the current SoOutput.
* 
* 
* @SEE_ALSO
*    SoPath,
*    SoAction,
*    SoNodeKit
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoNode : public SoFieldContainer {

  SO_NODE_ABSTRACT_HEADER(SoNode);

 public:

  /**
   * Turns the override flag on or off.@BR 
   * @BR
   * The following property nodes are affected by the override flag:
   * SoBaseColor,
   * SoColorIndex,
   * SoComplexity,
   * SoDepthBuffer,
   * SoDrawStyle,
   * SoEnvironment,
   * SoFont,
   * SoFullSceneAntialiasing,
   * SoLightModel,
   * SoMaterial,
   * SoMaterialBinding,
   * SoPackedColor,
   * SoPattern,
   * SoPickStyle,
   * SoPolygonOffset,
   * SoShapeHints,
   * SoTransparencyType,
   * SoVertexProperty.
   * @BR
   * @BR
   * Every node has an override flag associated with it. The override
   * flag is a powerful mechanism typically used (sparingly) near the
   * top of a scene graph. When this flag is set, any nodes of the
   * same type encountered later in the graph are ignored even if they
   * also have their own override flag set. For example, you might
   * insert a line-style SoDrawStyle node at the top of a graph to
   * ensure that the whole scene is drawn as wireframe objects,
   * regardless of drawing styles specified lower in the scene graph.
   * Use the setOverride() method to set and reset the override flag. The
   * #isOverride() method returns the state of the override flag.
   * 
   * Normally, the override flag is not used within a scene graph for
   * modeling. Use it in applications where you need to specify a
   * temporary change to the whole graph.
   * 
   * Note: The override flag is not written to a file.
   * 
   * Setting the override flag on a node whose field values are not
   * inherited (for example on a sphere with a radius of 7) has no
   * effect on other nodes in the graph of that type.
   * 
   */
  inline virtual void setOverride(const SbBool state);

  /**
   * Returns the state of the override flag.
   */
  inline virtual SbBool isOverride() const;

  /**
   * Creates and returns an exact copy of the node. If the node is a group, it copies
   * the children as well. If copyConnections is TRUE (it is FALSE by default), any
   * connections to (but not from) fields of the node are copied, as well. Note that
   * multiple references to a node under the node to be copied will result in
   * multiple references to the copy of that node.
   */
  virtual SoNode *    copy(SbBool copyConnections = FALSE) const;

  /**
   * Returns TRUE if a node has an effect on the state during traversal. The default
   * method returns TRUE. Node classes (such as SoSeparator) that isolate their
   * effects from the rest of the graph override this method to return FALSE.
   */
  virtual SbBool      affectsState() const;

  /**
   * A node's name can be set using SoBase::setName(). This method allows
   * nodes to be looked up by name. It returns the last node given the
   * specified name.
   */
  static SoNode *     getByName(const SbName &name);
#ifdef OIV_NET_DOC
  /**
  * A node's name can be set using SoBase::setName(). This method allows
  * nodes to be looked up by net name. It returns the number of nodes with
  * the given net name,
  * and adds to list references to those nodes.
  */

#else
  /**
  * A node's name can be set using SoBase::setName(). This method allows
  * nodes to be looked up by net name. It returns the number of nodes with
  * the given net name,
  * and adds to list pointers to those nodes.
  */

#endif //OIV_NET_DOC
  static int          getByName(const SbName &name, SoNodeList &list);

SoEXTENDER public:

  /**
   * This method is called by actions to allow the node to provide an "alternate
   * representation" when appropriate (typically depending on the action type).
   *
   * For example, when an SoIndexedTexture2 node is traversed by an SoToU3DAction,
   * it returns an SoTexture2 node as its alternate representation, because
   * indexed textures are not supported in U3D.  A custom node can use this
   * mechanism to provide an alternate representation using standard nodes when
   * it is travered by an SoWriteAction.
   *
   * By default the node itself is returned.
   */
  inline virtual SoNode* getAlternateRep(SoAction* action);

  /**
   * This method is used by getBoundingBox action traversal to know if
   * the current node must be traversed or not, ie the bounding should be ignored.
   * See boundingBoxIgnoring field of nodes SoGroup, SoShape and SoBaseKit.
   * Default is FALSE.
   */
  inline virtual SbBool isBoundingBoxIgnoring() const;

  // This method performs the "typical" operation of a node for any
  // action. The default implementation does nothing.
  virtual void        doAction(SoAction *action);

  // These virtual functions implement all of the actions for nodes,
  // Most of the default implementations do nothing.
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);
  virtual void        handleEvent(SoHandleEventAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        rayPick(SoRayPickAction *action);
  virtual void        search(SoSearchAction *action);
  virtual void        write(SoWriteAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);
  virtual void        distribute(SoDistributeAction *action);

  // These methods make render traversal faster by implementing
  // different rendering paths corresponding to different action
  // path codes.  The SoNode methods just call GLRender.
  virtual void        GLRenderBelowPath(SoGLRenderAction *action);
  virtual void        GLRenderInPath(SoGLRenderAction *action);
  virtual void        GLRenderOffPath(SoGLRenderAction *action);

  // These virtual functions are called when a node gains or loses
  // status as "grabber" of events (see HandleEventAction::setGrabber()).
  // The default methods do nothing.
  virtual void        grabEventsSetup();
  virtual void        grabEventsCleanup();

  // 
  // This virtual function is called when ScaleViz want to now 
  // if the parent separator must be traversed or not in compositing mode.
  //
  // By default such decision is taken by the Separator iteself through the 
  // renderUnitID field and then returned value is SO_RENDERUNITID_INHERIT.
  //
  // For some class of nodes we want to force a specific values.
  //
  // example :
  //   - SoTransparency node in Depth Compositing on OIRU side return SO_RENDERUNITID_ALL
  //   to force all transparent node below the separator to be rendered on all OIRU.
  //
  virtual int32_t     getRenderUnitID() const;

 SoINTERNAL public:

  // Creates and returns an exact copy of the node and returns the
  // dictionary of original and new nodes. This method is used when
  // creating the PROTOInstances on the fly.
  SoNode *            copyForPROTO(SbBool copyConnections = FALSE) const;
  enum Stage {
    FIRST_INSTANCE,         // First real instance being constructed
    PROTO_INSTANCE,         // Prototype instance being constructed
    OTHER_INSTANCE          // Subsequent instance being constructed
  };

  // Initializes base node class
  static void         initClass();
  static void         exitClass();

  // Initialize ALL Inventor node classes
  static void         initClasses();
  static void         exitClasses();

  // Initiates notification from an instance.
  virtual void        startNotify();

  // Propagates modification notification through an instance.
  virtual void        notify(SoNotList *list);

  // Returns the unique id for a node
  uint64_t getNodeId() const { return uniqueId; }

  // Returns the next available unique id
  static uint64_t getNextNodeId();

  // Returns pointer to children, or NULL if none
  virtual SoChildList *getChildren() const;
  virtual bool isSynchronizingContentOnly() { return FALSE; }
  virtual SoChildList *internalGetChildren() const;

  virtual void internalRemoveChild(int);
  virtual void internalRemoveChild(SoNode *);
  virtual void internalRemoveAllChildren();
  virtual void internalAddChild(SoNode *);
  virtual int  internalFindChild(const SoNode *) const;
  virtual void internalInsertChild(SoNode *, int);
  virtual SoNode *internalGetChild( int ) const;
  virtual void internalReplaceChild(int, SoNode *);
  virtual void internalReplaceChild(SoNode *, SoNode *);
  virtual int internalGetNumChildren();

  // Get details of change (only valid during notification)
  virtual SoNode* getChangedChild() const;
  virtual int getChangedIndex() const;
  virtual SoDataSensor::ChangeType getChangeType() const;

  // Writes instance to SoOutput. (Used for either stage of writing.)
  virtual void        writeInstance(SoOutput *out);

  // Returns the index of this node in the action/method table,
  // given its type.
  static int          getActionMethodIndex(SoType t);

  // Recursively adds this node and all nodes under it to the copy
  // dictionary. Returns the copy of this node.
  virtual SoNode *    addToCopyDict() const;

  // Copies the contents of the given node into this instance. The
  // default implementation copies just field values and the name.
  virtual void        copyContents(const SoFieldContainer *fromFC,
                                   SbBool copyConnections);

  // Copies an instance that is encountered through a field connection
  virtual SoFieldContainer *  copyThroughConnection() const;

  // return SoNodeImpl private structure info
  // if not yet done, then it is allocated
  virtual SoNodeImpl *getNodeImpl();

  // Get the curent node alternate representation
  // Cache the alternate rep if requested.
  SoNode* getCachedAlternateRep(SoAction* action, SbBool doCache = FALSE);

 protected:

  static void setNextActionMethodIndex(int index);
  static int  getNextActionMethodIndex();
  static void incNextActionMethodIndex();

  // Constructor, destructor
  SoNode();
  virtual ~SoNode();

  // Notified changes
  virtual void resetChangedStatus();

  // Inner clas that decribes current notification info details.
  class INVENTOR_API SoNotificationInfo 
  {
  public:
    // Constructor.
    SoNotificationInfo()
    {
      reset();
    }
    // reset current notification details.
    inline void reset()
    {
      m_changedChild = NULL;
      m_changedIndex = -1;
      m_changeType = SoDataSensor::UNSPECIFIED;
    }
    // set current notification infos.
    inline void set(SoNode* changedChild, const int changedIndex, const SoDataSensor::ChangeType changeType)
    {
      m_changedChild = changedChild;
      m_changedIndex = changedIndex;
      m_changeType = changeType;
    }
    // Basic accessors
    inline SoNode* getChangedChild() const 
    { return m_changedChild; }
    int getChangedIndex() const
    { return m_changedIndex; }
    SoDataSensor::ChangeType getChangeType() const
    { return m_changeType;}

  private:
    // pointer on the changed child
    SoNode* m_changedChild;
    // index of the changed child
    int m_changedIndex;
    // current type of changed
    SoDataSensor::ChangeType m_changeType;
  };

  // Returns details of change (only valid during notification)
  inline virtual SoNotificationInfo *getNotificationInfo() const;

  // set notification infos.
  inline void setNotificationInfo(SoNode* changedChild, const int changedIndex, const SoDataSensor::ChangeType changeType);

 private:
  // Unique id for this node.
  uint64_t uniqueId;

  // Next available unique id
  static uint64_t nextUniqueId;

  // Next index into the action method table
  static int         nextActionMethodIndex;

  // These static methods are registered with the database - they
  // simply call the appropriate virtual function
  static void callbackS(SoAction *, SoNode *);
  static void GLRenderS(SoAction *, SoNode *);
  static void getBoundingBoxS(SoAction *, SoNode *);
  static void getMatrixS(SoAction *, SoNode *);
  static void handleEventS(SoAction *, SoNode *);
  static void pickS(SoAction *, SoNode *);
  static void rayPickS(SoAction *, SoNode *);
  static void searchS(SoAction *, SoNode *);
  static void writeS(SoAction *, SoNode *);
  static void getPrimitiveCountS(SoAction *, SoNode *);

  static void distributeS(SoAction *, SoNode *);

  SoNode* m_cachedAlternateRep;

 SoINTERNAL public:

  // ----- Local cache verification--------------

  // build the cache 
  void buildCache( SoState *state );

  // check if the cache is valid. If not, rebuild
  SbBool checkCache( SoState *state );

  // check if the cache is valid and tells which element is invalid. If not, rebuild
  //validElements must be std::vector<int> (see above)

  SbBool checkCache( SoState *state , void *validElements );

  // local cache
  SoCache* m_cache;

  // add cache element
  void addCacheElement( int stackIndex );

  typedef std::vector<int> SoCachedElementsVec;

  // Elements to cache (don't use std::vector<int> here)
  void* m_cachedElements;

  //---------------------------------------------

  //directViz integration

  //directViz objects list ( std::vector<> )
  void* m_directVizObjects;

  //apend directViz object to the node's list
  void addDirectVizObject( void *directVizObject );

  //return directViz object at position pos as a void*
  void* getDirectVizObject( unsigned int pos );

  //return number of DirectViz objects
  int getNumDirectVizObjects();

  //clear directViz objects list
  void clearDirectVizObjects();

  //---------------------------------------------

  SbProjectionCoordinates *getProjectionCoordinates(){return m_projCoords;}

  void setProjectionCoordinates(SbProjectionCoordinates *projCoords){
    m_projCoords = projCoords;
  }

  //Projections
  protected :
    SbProjectionCoordinates *m_projCoords;

    // used by ScaleViz for ComputeRenderUnitID action
    SoNodeImpl* m_soNodeImpl;

};


SoNode::SoNotificationInfo *
SoNode::getNotificationInfo() const
{
  return NULL;
}

void 
SoNode::setNotificationInfo(SoNode* changedChild, const int changedIndex, const SoDataSensor::ChangeType changeType)
{
  SoNotificationInfo *notificationInfo = getNotificationInfo();
  if ( notificationInfo )
    notificationInfo->set(changedChild, changedIndex, changeType);
}

SoNode* 
SoNode::getAlternateRep(SoAction*)
{
  return this;
}

SbBool 
SoNode::isBoundingBoxIgnoring() const
{
  return FALSE;
}

void 
SoNode::setOverride(const SbBool)
{
#if defined(_DEBUG)
  SoDebugError::postWarning("SoNode::setOverride","not reimplemented and supported for this inherited node");
#endif
}

SbBool
SoNode::isOverride() const
{
  return FALSE;
}

#endif /* _SO_NODE_ */

