/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
** Modified by : Alan Norton (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_PATH_
#define  _SO_PATH_

#include <Inventor/misc/SoBase.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/SoLists.h>
#include <Inventor/STL/iostream>

class SoTempPath;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPath
//
//  A SoPath represents a scene graph or subgraph. It contains
//  pointers to a chain of nodes, each of which is a child of the
//  previous. The child index of each node is also stored, to
//  disambiguate cases where a node appears more than once as a child
//  of the same group.
//
//  The graph defined by the path consists of all of the nodes in the
//  path, all nodes below the last node in the chain, and any other
//  nodes that have an effect on these nodes.
//
//////////////////////////////////////////////////////////////////////////////

class SoPathList;
class SoWriteAction;

#ifdef OIV_NET_DOC
/**
* Path that points to a list of hierarchical nodes.
*
* @ingroup General
*
* @DESCRIPTION
*   A path represents a scene graph or subgraph. It contains a list of references to
*   nodes forming a chain from some root to some descendant. Each node in the chain
*   is a child of the previous node. Paths are used to refer to some object in a
*   scene graph precisely and unambiguously, even if there are many instances of the
*   object. Therefore, paths are returned by both the SoRayPickAction and
*   SoSearchAction.
*
*   When an action is applied to a path, only the nodes in the subgraph defined by
*   the path are traversed. These include: the nodes in the path chain, all nodes
*   (if any) below the last node in the path, and all nodes whose effects are
*   inherited by any of these nodes.
*
*   SoPath attempts to maintain consistency of paths even when the structure of the
*   scene graph changes. For example, removing a child from its parent when both are
*   in a path chain cuts the path chain at that point, leaving the top part intact.
*   Removing the node to the left of a node in a path adjusts the index for that
*   node. Replacing a child of a node when both the parent and the child are in the
*   chain replaces the child in the chain with the new child, truncating the path
*   below the new child.
*
*   Note that only public children of nodes are accessible from an SoPath. Nodes like
*   node kits that limit access to their children may provide other ways to get more
*   information, such as by using the SoNodeKitPath class.
*
* @FILE_FORMAT_DEFAULT
*    SoPath {
*    @TABLE_FILE_FORMAT
*       @TR [head node]                     @TD
*       @TR [number of remaining indices]   @TD
*       @TR [index]                         @TD
*       @TR &...                            @TD
*       @TR [index]                         @TD
*    @TABLE_END
*    }
*
*   Note that the indices in a written path are adjusted based on the nodes that
*   are actually written to a file. Since nodes in the graph that have no effect on
*   the path (such as some separator nodes) are not written, the siblings of such
*   nodes must undergo index adjustment when written. The actual nodes in the graph
*   remain unchanged.
*
* @SEE_ALSO
*    SoNode,
*    SoRayPickAction,
*    SoSearchAction,
*    SoNodeKitPath
*
*
*/
#else
/**
* Path that points to a list of hierarchical nodes.
*
* @ingroup General
*
* @DESCRIPTION
*   A path represents a scene graph or subgraph. It contains a list of pointers to
*   nodes forming a chain from some root to some descendant. Each node in the chain
*   is a child of the previous node. Paths are used to refer to some object in a
*   scene graph precisely and unambiguously, even if there are many instances of the
*   object. Therefore, paths are returned by both the SoRayPickAction and
*   SoSearchAction.
*
*   When an action is applied to a path, only the nodes in the subgraph defined by
*   the path are traversed. These include: the nodes in the path chain, all nodes
*   (if any) below the last node in the path, and all nodes whose effects are
*   inherited by any of these nodes.
*
*   SoPath attempts to maintain consistency of paths even when the structure of the
*   scene graph changes. For example, removing a child from its parent when both are
*   in a path chain cuts the path chain at that point, leaving the top part intact.
*   Removing the node to the left of a node in a path adjusts the index for that
*   node. Replacing a child of a node when both the parent and the child are in the
*   chain replaces the child in the chain with the new child, truncating the path
*   below the new child.
*
*   Note that only public children of nodes are accessible from an SoPath. Nodes like
*   node kits that limit access to their children may provide other ways to get more
*   information, such as by using the SoNodeKitPath class.
*
* @FILE_FORMAT_DEFAULT
*    SoPath {
*    @TABLE_FILE_FORMAT
*       @TR [head node]                     @TD
*       @TR [number of remaining indices]   @TD
*       @TR [index]                         @TD
*       @TR &...                            @TD
*       @TR [index]                         @TD
*    @TABLE_END
*    }
*
*   Note that the indices in a written path are adjusted based on the nodes that
*   are actually written to a file. Since nodes in the graph that have no effect on
*   the path (such as some separator nodes) are not written, the siblings of such
*   nodes must undergo index adjustment when written. The actual nodes in the graph
*   remain unchanged.
*
* @SEE_ALSO
*    SoNode,
*    SoRayPickAction,
*    SoSearchAction,
*    SoNodeKitPath
*
*
*/
#endif //OIV_NET_DOC


class INVENTOR_API SoPath : public SoBase {

 public:

  /**
   * Constructs an empty path.
   */
  SoPath();

  /**
   * Constructs a path with a hint to length (number of nodes in chain).
   */
  SoPath(int approxLength);

  /**
   * Constructs a path and sets the head node to the given node.
   */
  SoPath(SoNode *node);

  /**
   * Sets head node (first node in chain). The head node must be set before the
   * append() or push() methods may be called.
   */
  void                setHead(SoNode *node);

  /**
   * Adds node to end of chain; the node is the childIndex'th child of the current
   * tail node.
   */
  void                append(int childIndex);

  /**
   * Adds node to end of chain; uses the first occurrence of childNode as child of
   * current tail node. If the path is empty, this is equivalent to
   * @B setHead(childNode) @b.
   */
  void                append(SoNode *childNode);

  /**
   * Adds all nodes in fromPath's chain to end of chain; the head node of fromPath
   * must be the same as or a child of the current tail node.
   */
  void                append(const SoPath *fromPath);

  /**
   * The push() and pop() methods allow a path to be treated as a stack;
   * they push a node at the end of the chain and pop the last node off.
   */
  void                push(int childIndex) { append(childIndex); }
  /**
   * The push() and pop() methods allow a path to be treated as a stack;
   * they push a node at the end of the chain and pop the last node off.
   */
  void                pop()                { truncate(getFullLength() - 1); }

  /**
   * Returns the first node in a path chain.
   */
  SoNode *            getHead() const { return nodes[0]; }
  /**
   * Returns the last node in a path chain.
   */
  SoNode *            getTail() const { return (nodes[getLength() - 1]); }

#ifdef OIV_NET_DOC
  /**
  * Returns a reference to the i'th node (within its parent) in the chain.
  * Calling @B getNode(0) @b is equivalent to calling
  * getHead().
  */

#else
  /**
  * Returns a pointer to the i'th node (within its parent) in the chain.
  * Calling @B getNode(0) @b is equivalent to calling
  * getHead().
  */

#endif //OIV_NET_DOC
  SoNode *            getNode(int i) const    { return (nodes[i]); }

#ifdef OIV_NET_DOC
  /**
  *
  * Returns a reference to the first node and its index, from the head of
  * the given type in the chain.
  * NULL is returned and the index is set to -1 if no node of
  * the given type is found.
  */

#else
  /**
  *
  * Returns a pointer to the first node and its index, from the head of
  * the given type in the chain.
  * NULL is returned and the index is set to -1 if no node of
  * the given type is found.
  */

#endif //OIV_NET_DOC
  SoNode*             getNode(const SoType type, int &i) const ;


#ifdef OIV_NET_DOC
  /**
  * Returns a reference to the i'th node (within its parent)
  * in the chain, counting backward from the tail node. Passing 0 for i
  * returns the tail node.
  */

#else
  /**
  * Returns a pointer to the i'th node (within its parent)
  * in the chain, counting backward from the tail node. Passing 0 for i
  * returns the tail node.
  */

#endif //OIV_NET_DOC
  SoNode *            getNodeFromTail(int i) const
    { return (nodes[getLength() - 1 - i]); }

  /**
   * Returns the index of the i'th node (within its parent) in the chain.
   */
  int                 getIndex(int i) const   { return (indices[i]); }

  /**
   * Returns the index of the i'th node (within
   * its parent) in the chain, counting backward from the tail node. Passing 0 for i
   * returns the index of the tail node.
   */
  int                 getIndexFromTail(int i) const
    { return (indices[getLength() - 1 - i]); }

  /**
   * Returns length of path chain (number of nodes).
   */
  int                 getLength() const;

  /**
   * Truncates the path chain, removing all nodes from index start on. Calling
   * @B truncate(0) @b empties the path entirely.
   */
  void                truncate(int start);

  /**
   * Returns TRUE if the node is found anywhere in the path chain.
   */
  SbBool              containsNode(const SoNode *node) const;


  /**
   *
   * Returns TRUE if the node type is found anywhere in the path chain.
   */
  SbBool              containsNode(const SoType type) const;

  /**
   * Returns TRUE if the nodes in the chain in the passed path are contained (in
   * consecutive order) in this path chain.
   */
  SbBool              containsPath(const SoPath *path) const;

  /**
   * If the two paths have different head nodes, this returns -1. Otherwise, it
   * returns the path chain index of the last node (starting at the head) that is the
   * same for both paths.
   */
  int findFork(const SoPath *path) const;

  /**
   * Creates and returns a new path that is a copy of some or all of this path.
   * Copying starts at the given index (default is 0, which is the head node). A
   * numNodes of 0 (the default) means copy all nodes from the starting index to the
   * end. Returns NULL on error.
   */
  SoPath *copy(int startFromNodeIndex = 0, int numNodes = 0) const;

#ifdef OIV_NET_DOC
  /**
  * Returns true if all node references in the two path chains are identical.
  */

#else
  /**
  * Returns TRUE if all node pointers in the two path chains are identical.
  */

#endif //OIV_NET_DOC
  INVENTOR_API friend int operator ==(const SoPath &p1, const SoPath &p2);

  /**
  * Writes the path to the specified output stream.
  */
  INVENTOR_API friend std::ostream& operator << (std::ostream& os, const SoPath& path);

  // Returns type identifier for path instance
  virtual SoType      getTypeId() const;

  // Returns type identifier for SoPath class
  static SoType       getClassTypeId();

  /**
   * Method to return a path with a given name. Paths are named by
   * calling their setName() method (defined by the SoBase class). This method
   * returns the last path that was given the specified name, either by setName()
   * or by reading in a named path from a file. If there is no path with the given
   * name, NULL will be returned.
   */
  static SoPath *getByName(const SbName &name);
  /**
   * Method to return paths with a given name. Paths are named by
   * calling their setName() method (defined by the SoBase class).
   * This method appends all paths with the given
   * name to the given path list and returns the number of paths that were added. If
   * there are no paths with the given name, zero will be returned and nothing will
   * be added to the list.
   */
  static int getByName(const SbName &name, SoPathList &list);

 SoINTERNAL public:
  // Initializes path class
  static void initClass();
  static void exitClass();

  // This is called when a node in the path chain has a child added.
  // The passed index is the index of the new child
  void                insertIndex(SoNode *parent, int newIndex);

  // This is called when a node in the path chain has a child removed.
  // The passed index is the index of the child to be removed
  void                removeIndex(SoNode *parent, int oldIndex);

  // This is called when a node in the path chain replaces a child.
  // The passed index is the index of the child to be removed
  void                replaceIndex(SoNode *parent, int index, SoNode *newChild);

  // Writes path using given write action
  virtual void        write(SoWriteAction *writeAction) const;

  // Returns TRUE if the given notification list involves a change
  // to a node that affects the path. It is assumed that the last
  // (most recent) node in the list is the head node of the path.
  SbBool isRelevantNotification(SoNotList *list) const;

  void setNumPublic(int num);

  // Appends the given node and index to the lists, updating
  // numPublic as appropriate
  void                append(SoNode *node, int index);

 protected:
  // Allows internal SoTempPath subclass to forego auditor overhead
  void auditPath(SbBool flag) { doAuditors = flag; }

  // Reads stuff into instance of SoPath. Returns FALSE on error.
  virtual SbBool readInstance(SoInput *in, unsigned short flags);

  ~SoPath();

 private:
  SoNodeList          nodes;          // Pointers to nodes
  SbIntList           indices;        // Child indices
  int                 numPublic;      // How many children are public
  int                 minNumPublic;   // Minimum we KNOW are public
  SbBool              doAuditors;     // TRUE if auditors to be maintained
  static SoType      classTypeId;    // TypeId of paths

  // Returns real length of path, including hidden children
  int getFullLength() const
    { return nodes.getLength(); }

  // Returns new SoPath; called by SoType::createInstance()
  static void* createInstance(SoType* dynamicType = NULL);

  // Really does a truncate. Flag indicates whether to notify.
  void truncate(int start, SbBool doNotify);

  friend class SoFullPath;
  friend class SoTempPath;
  friend class SoAction;

};

#ifndef HIDDEN_FROM_DOC

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFullPath
//
//  This SoEXTENDER class allows expert users to examine "hidden"
//  children in paths. SoPath allows access from the head node down to
//  the first node with hidden children, but no further. Casting an
//  SoPath to an SoFullPath (which is always guaranteed to be safe)
//  allows you to get at hidden children. SoFullPath overrides some of
//  the methods defined on paths to make this possible.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoFullPath : public SoPath {

 public:
  //
  // Override methods that normally stop at last public child:
  //

  void pop()
    { truncate(getFullLength() - 1); }

  SoNode *getTail() const
    { return (nodes[getFullLength() - 1]); }

  SoNode *getNodeFromTail(int i) const
    { return (nodes[getFullLength() - 1 - i]); }

  int getIndexFromTail(int i) const
    { return (indices[getFullLength() - 1 - i]); }

  int getLength() const
    { return getFullLength(); }

 private:
  SoFullPath(int approxLength) : SoPath(approxLength) {}
  virtual ~SoFullPath();

  friend class SoTempPath;
};



//////////////////////////////////////////////////////////////////////////////
//
//  SoINTERNAL Class: SoLightPath
//
//  A SoLightPath is a light-weight version of an SoTempPath, intended to
//  be used just to keep track of the current path during traversal.
//  Eventually it is intended to replace SoTempPath (when appropriate
//  modifications are made to SoDraggers).
//  Unlike SoPath, it keeps only a chain of childIndices and a headnode.
//  The methods implemented are only those needed for traversal.
//
//////////////////////////////////////////////////////////////////////////////


class INVENTOR_API SoLightPath {

 SoINTERNAL public:

  // Constructor given approximate number of nodes in chain
  SoLightPath(int approxLength=0);


  // Sets head node (first node in chain)
  // Resulting path has only one node.
  void                setHead(SoNode *node);

  // Adds node specified by childindex to end of chain.
  void                append(int childIndex)
    { indices.append(childIndex);}


  // Allows path to be treated as a stack: push a node at the end of
  // the chain and pop the last node off
  void                push(int childIndex)    { append(childIndex); }
  void                push()                  { append(-1);}
  void                pop()           { truncate(getFullLength() - 1); }
  void                setTail(int childIndex) {
    indices.set(getFullLength() - 1, childIndex);
  }
  SoNode *            getTail()
    { return getNode(getFullLength()-1);}

  // Returns the first node in a path chain.
  SoNode *            getHead() const { return headNode; }

  // Returns pointer to ith node in chain
  SoNode *            getNode(int i) const;

  // BA - added getIndex
  // Returns index of ith node in chain
  int                 getIndex(int i) const
    { return indices[i]; };

  // Returns full length of path chain (number of nodes)
  // note that public/private distinction is ignored.
  int                 getFullLength() const {return indices.getLength();}

  // Removes all nodes from indexed node on
  void                truncate(int start) { indices.truncate(start);}


  // fills in nodes for a TempPath that is represented by this
  // SoLightPath.  Called by SoAction::getCurPath();
  void                makeTempPath(SoTempPath *) const;

 private:

  ~SoLightPath();
  SoNode *            headNode;       // Pointer to headnode
  SbIntList           indices;        // Child indices


  friend class SoAction;
};

#endif // HIDDEN_FROM_DOC

/**
* Writes the path to the specified output stream.
*/
INVENTOR_API std::ostream& operator << (std::ostream& os, const SoPath& path);

#endif /* _SO_PATH_ */

