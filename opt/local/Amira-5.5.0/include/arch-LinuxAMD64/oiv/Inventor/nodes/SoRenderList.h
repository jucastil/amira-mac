/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
/*---------------------------------------------------------------------
 *  Header file for SoRenderList Separator node
 *
 *  Author: Brian Anderson, 
 *  Modified by Jerome Hummel, 2002
 *-------------------------------------------------------------------*/

#ifndef _SO_RENDER_LIST_HH
#define _SO_RENDER_LIST_HH

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/SbBox.h>
#include <Inventor/SbColor.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFUInt32.h>

#ifndef HIDDEN_FROM_DOC

class SoState;
class SoNodeSensor;
class SoSearchAction;
class SoComplexity;

SoEXTENDER class INVENTOR_API SoRenderObject {

 public:
 
  SoRenderObject(const SoPath *p);
  virtual ~SoRenderObject();
  
  // Called when path has changed, invalidates render cache
  virtual void invalidate();
    
  // Added for bug in renderlist
  virtual SoPath *getPath(void) { return path; };
   
  // To improve spatial Traversal
  const SbBox3f& getBox(void) { return bbox; };

  // To know if the obj has transparent attribute or not
  SbBool isTranslucent;

  SbBool isOccluder;

  // We need to store the decimation value in the object.
  // For instance, this value depends on the octant, but to render
  // transparent object after having traversed the octree, we must
  // remember this value to do a traverseRenderObjectDecimated.
  // if the user wishes so
  float getDecimation() { return decimation; };
  void setDecimation(float value) { decimation = value; };

  void setIndex(int i) { index = i; };
  SbBool hasIndex(void) { return (index == -1 ? FALSE : TRUE); };
  int getIndex(void) { return index; };
  void resetIndex(void) { index = -1; };

 private:
  // This particular implementation has a SoPath in SoRenderObject; however,
  // future implementations will probably change this, so use the 
  // SoRenderList::getPathFromRenderObject() function to access the path.
  SoPath *path;
  SoGLCacheList *pathCache;
  SoPrimitiveCountCache *primCountCache;
  
  // Need it for more precise culling test in the octree and for occlusion culling
  SbBox3f bbox;
   
  float decimation;

  friend class SoRenderList;

  int index;

  int m_numRenderCaches;
};


SoEXTENDER class INVENTOR_API SoRenderObjectList : public SbPList {
  
 public:
  
  void append(SoRenderObject *string)
    { ((SbPList *) this)->append((void *) string); }
  
  int find(SoRenderObject *string)
    { return ((SbPList *) this)->find((void *) string); }
  
  void insert(SoRenderObject *string, int addBefore)
    { ((SbPList *) this)->insert((void *) string, addBefore); }
  
  SoRenderObject *&operator [](int i) const
    { return ( (SoRenderObject *&) ( (*(const SbPList *) this) [i] ) ); }
};

#endif // HIDDEN_FROM_DOC

#ifdef OIV_NET_DOC
/**
* @VSGEXT Abstract group node that changes traversal from the scene graph to a list of
* render objects.
* 
* @ingroup GroupNodes LMV
* 
* @DESCRIPTION
*   This abstract node keeps track of paths to the shapes beneath it. Derived
*   classes can traverse or reorganize this list instead of traversing in scene
*   graph order. As the scene graph changes, the SoRenderList node will update the
*   list of paths, calling virtual functions for the derived classes to update their
*   data structures.
*   
*   By default, the SoRenderList node keeps track of paths to instances of SoShape,
*   SoLOD, and some manipulators. The list of types to look for can be changed with
*   the functions addRenderObjectType() and removeRenderObjectType().
*   You can also mark a specific node as a Render Object by giving its name through
*   addRenderObjectName().
*   
*   Applications should not use an instance of class SoRenderList directly; instead,
*   instances of the derived classes, such as SoValueOrdering and SoOctreeOrdering,
*   should be used.
* 
* @ACTION_BEHAVIOR
*    Sets: SoCacheElement
*
* @SEE_ALSO
*    SoGetPrimitiveCountAction,
*    SoLevelOfSimplification,
*    SoOctreeOrdering,
*    SoValueOrdering
*    SoOcclusionCulling
* 
* 
*/ 
#else
/**
* @VSGEXT Abstract group node that changes traversal from the scene graph to a list of
* render objects.
* 
* @ingroup GroupNodes LMV
* 
* @DESCRIPTION
*   This abstract node keeps track of paths to the shapes beneath it. Derived
*   classes can traverse or reorganize this list instead of traversing in scene
*   graph order. As the scene graph changes, the SoRenderList node will update the
*   list of paths, calling virtual functions for the derived classes to update their
*   data structures.
*   
*   By default, the SoRenderList node keeps track of paths to instances of SoShape,
*   SoLOD, and some manipulators. The list of types to look for can be changed with
*   the functions addRenderObjectType() and removeRenderObjectType().
*   You can also mark a specific node as a Render Object by giving its name through
*   addRenderObjectName().
*   
*   Applications should not use an instance of class SoRenderList directly; instead,
*   instances of the derived classes, such as SoValueOrdering and SoOctreeOrdering,
*   should be used.
*
* Note: Do not modify an instance of this node or any of its children
* unless this node has a ref count greater than zero. If the
* node is itself the child of a grouping node then the ref
* count is automatically greater than zero, otherwise you must
* explicitly increment the ref count by calling the ref() method.   
* 
* @ACTION_BEHAVIOR
*    Sets: SoCacheElement
* 
* @SEE_ALSO
*    SoGetPrimitiveCountAction,
*    SoLevelOfSimplification,
*    SoOctreeOrdering,
*    SoValueOrdering
*    SoOcclusionCulling
* 
* 
*/ 
#endif //OIV_NET_DOC

class INVENTOR_API SoRenderList : public SoSeparator {

  SO_NODE_HEADER(SoRenderList);

 public:
  /**
   * Default constructor.
   */
  SoRenderList();

  /**
   * Constructor that takes approximate number of children as a hint.
   */
  SoRenderList(int numChildren);

  /**
   * Adds a new type to the search list.
   */
  void addRenderObjectType(SoType t);

  /**
   * Removes a type from the search list.
   */
  void removeRenderObjectType(SoType t);

  /**
   * Returns number of types in the search list.
   */
  int getNumRenderObjectTypes() const
    { return types.getLength(); }

  /**
   * Returns the @B i @b th type of the search list. 
   */
  SoType getRenderObjectType(int i) const
    { return  types[i]; }

  /**
   * Notifies an SoNotList nodes list. 
   */
  virtual void notify(SoNotList *list);

  /**
   * Adds a new name to the search list.
   */
  void addRenderObjectName(SbName n);

  /**
   * Removes a name from the search list.
   */
  void removeRenderObjectName(SbName n);

  /**
   * Returns number of names in the search list.
   */
  int getNumRenderObjectNames() const
    { return names.getLength(); }

  /**
   * Returns the @B i @b th name of the search list. 
   */
  const SbName &getRenderObjectName(int i) const;

  /**
   * Clears all names from the search list.
   */
  void removeAllRenderObjectNames();
  
  /**
   * Normally each culling node maintains its own render list. However,
   * culling nodes can be chained, meaning that a culling node (B)
   * that is a child of another culling node (A), can use the result
   * of the culling operation in the parent node (A) instead of
   * maintaining its own render list. In order to enable this behavior,
   * this field should be set to TRUE for the parent (A) and FALSE
   * for the child (B). The default is TRUE.
   */
  SoSFBool isHead;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  // Constructs path to Render object, the derived class can then 
  // apply an action to this path.  
  SoPath *getPathFromRenderObject (SoRenderObject *obj)
    { 
      if(obj->hasIndex())return obj->path->copy(obj->getIndex());
      else return obj->path; 
    };
  
  // Applies action to render object from the list, 
  // using caching where possible.
  void renderObject(SoGLRenderAction *action, SoRenderObject *);
  void traverseRenderObject(SoAction *action, SoRenderObject *);
  void primitiveCountRenderObject(SoGetPrimitiveCountAction *action, 
                                  SoRenderObject *);

  // Renders an object with BOUNDING_BOX complexity
  void traverseRenderObjectAsBox(SoAction *action, SoRenderObject *);

  // Traverses an object setting decimation value
  void traverseRenderObjectDecimated(SoAction *action, 
                                     SoRenderObject *, 
                                     float decimationPercentage);
  
  // Virtual callbacks for when changes are made to the RenderObject list.
  virtual SoRenderObject *createRenderObject(const SoPath *p);
  virtual void removingRenderObject(SoRenderObject *);
  virtual void renderObjectChanged(SoRenderObject *);
  virtual void ourFieldChanged(SoField *);
  
  // Destructor
  virtual ~SoRenderList();
  
  // Our list of paths to shapes below us:
  SoRenderObjectList shapes;    
  
  // CallbackAction used to find paths to shapes within scene graph,
  // creating list of RenderObjects. Keep it around always to keep 
  // overhead down.  Make it protected so subclasses can affect search.
  SoCallbackAction *shapeSearchAction;
  
  // Convenience function to get DecimationPercentageValue from state
  float getDecimationValue(SoState *state);
  
  // Detach and attach change sensor, so that derived classes can turn
  // off the notification during certain actions:
  void detachChangeSensor();
  void attachChangeSensor();
  
  // Returns TRUE if RenderList should keep a path to this node, 
  // with given type.  Subclasses could override this to 
  // change the algorithm used; this function checks the type against
  // the type list and the node's name against the name list.
  virtual SbBool lookingForNode(SoType t, const SoNode *n);   

  //add on to make different culling operations work together.
  SoSearchAction *searchForRenderList;
  SoRenderList* coworker;
  SbBool searchForACoworker;

  enum SortType {
    BUBBLE,
    MERGE
  };

  //To sort objects-The furthest object will be the first one (yourList[0]) unless backToFront is FALSE
  //2 types of sort are available. Bubble is sometimes faster if the stack is already partially sorted.
  void sortObjects(SoState* state, 
                   SoRenderObjectList &vobject,
                   int firstIndex,
                   int lastIndex,
                   SbBool backToFront=TRUE,
                   SortType type = SoRenderList::MERGE);

  // This will check in the current state if the renderObject has attributes (transparency, ...).
  void checkForAttribute(SoRenderObject*);

  // Added and used by octree or occlusion to manage trans obj
  SbBool sortTransparentObjs;

  // Manage transparency only if DELAYED or SORTED mode
  SbBool manageTransparency;


 private:
  // Common code for the two constructors:
  void commonConstructor();
  
  // Our complexity node for adjusting rendering:
  SoComplexity *boxComplexity;
  
  // List of whether a path has been affected or not by the last change
  SbIntList pathsAffected;
  void markAffected(int whichPath);
  // this function calls "pathChanged" for each path that was affected
  // by the last change
  void callAffectedPathsCallbacks();
  
  // List of types to search for
  SoTypeList types;
  SbPList names;
  
  // Get paths to renderObjects under graph
  int indexIntoShapes;
  SoRenderObject* mergePath(const SoPath *path, int where);
  SoRenderObject* addRenderObject(const SoPath *p, int where);
  void removeRenderObject(int where);
  void renderObjectChanged(int where);
  
  // SearchAction for finding affected paths:      
  SoSearchAction *pathSearchAction;
  void findAffectedPaths(SoNode *node);
  void findContainingPaths(SoNode *node, int start);
  int findTruncatedPaths();
  
  // Save the relationship between field change and affected paths:
  void saveRelationship(SoNode* changedNode, 
                        const SbIntList &affectedPaths);
  SbBool haveRelationship(SoNode *changedNode, 
                          SbIntList &affectedPaths);
  void clearRelationships();
  SbPList relateNodes, relatePaths;
  
  // Node sensor for finding when nodes underneath this node are added
  // and removed:
  SoNodeSensor *childChangeSensor;
  SbPList sensorList;
  static void childSensorCB(void *data, SoSensor *sensor)
    { ((SoRenderList*)data)->childChange( (SoNodeSensor*) sensor); };
  void childChange(SoNodeSensor *sensor);
  static void tailSensorCB(void *data, SoSensor *sensor)
    { ((SoRenderList*)data)->tailChange( (SoNodeSensor*) sensor); };
  void tailChange(SoNodeSensor *sensor);
  
  // PRE Callbacks from SoCallbackAction, looking for render objects
  static SoCallbackAction::Response foundRenderObjectCB(void *userData,
                                                        SoCallbackAction *action,
                                                        const SoNode *);
  // POST Callbacks from SoCallbackAction, looking for render objects
  static SoCallbackAction::Response afterFoundingRenderObjectCB(void *userData,
                                                        SoCallbackAction *action,
                                                        const SoNode *);

  //for LOD case
  SbBool doNotCreateRenderObject;
  SoRenderObject* objectToCheck;
  // Utility functions to sort objects from front to back or B to F
  void mergeSort(float *A, int firstIndex, int lastIndex, SoRenderObjectList &obj,SbBool);
  void mergeBtoF(float *A, int f, int m, int l, SoRenderObjectList &obj);
  void mergeFtoB(float *A, int f, int m, int l, SoRenderObjectList &obj);

  void bubbleSort(float *A, int firstIndex, int lastIndex,SoRenderObjectList &obj,SbBool);
  void bubbleBtoF(float *A, int firstIndex, int lastIndex, SoRenderObjectList &obj);
  void bubbleFtoB(float *A, int firstIndex, int lastIndex, SoRenderObjectList &obj);

  // Save current state when creating renderObject to checkForAttribute.
  SoState *currentState;
};

#endif

