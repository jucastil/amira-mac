/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
** Modified by : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_NODE_KIT_PATH_
#define  _SO_NODE_KIT_PATH_

#include <Inventor/SbBasic.h>
#include <Inventor/SoPath.h>

class SoBaseKit;
class SoSearchAction;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNodeKitPath
//
//  A SoNodeKitPath represents a scene graph or subgraph. It contains
//  pointers to a chain of nodeKitss, each of which is a child of the
//  previous. 
//  
//  Intermediary nodes between nodeKits are not included in the nodeKit path.
//
//  
//////////////////////////////////////////////////////////////////////////////

/**
 * Path that points to a list of hierarchical nodekits.
 * 
 * @ingroup nodekits
 * 
 * @DESCRIPTION
 *   SoNodeKitPath is a subclass of SoPath that lets you look at nodekits below the
 *   top nodekit in the path. Since nodekits have hidden children, when you call
 *   getTail() on a regular path, it returns the top-most nodekit on the path.
 *   This occurs even though the path might contain extra internal information
 *   leading to a node far deeper in the scene graph. For example, when picking an
 *   object inside an SoSceneKit, the @B regular @b path would end at the scenekit.
 *   But a @B nodekit @b path would continue further down listing the other nodekits
 *   below it in the path.
 *   
 *   Intermediary (private) nodes between nodekits are not included in the nodekit
 *   path.
 *   
 *   Note that there is no constructor for an SoNodeKitPath, so you can not create
 *   one. Rather, you cast an (SoPath *) into an (SoNodeKitPath *),
 *   which returns nodekit-style values from all the same questions as SoPath.
 *   
 *   Also, some methods of SoPath may not be called on an SoNodeKitPath. Any methods
 *   which take a regular SoNode as an argument (except for setHead()) are not
 *   accessible, and replaced by methods that take an SoBaseKit as an argument
 *   instead. Methods which allow the programmer to refer to the child index of a
 *   node beneath its parent are also inaccessible; since an SoNodeKitPath only shows
 *   nodekits and hides any private parts, successive nodekits in the path may not
 *   actually be parent and child.
 * 
 * @SEE_ALSO
 *    SoBaseKit,
 *    SoPath,
 *    SoRayPickAction,
 *    SoSearchAction
 * 
 * 
 */ 

class INVENTOR_API SoNodeKitPath : public SoPath {

 public:

  /**
   * Returns length of path chain (number of nodekits).
   */
  int                 getLength() const;

  /**
   * Return the last nodekit in a path chain. Note that getHead() is not
   * redefined from SoPath, since an SoNodeKitPath need not begin with a nodekit; the
   * restriction is placed only on successive nodes on the path.
   */
  SoNode *            getTail() const;

#ifdef OIV_NET_DOC
  /**
  * Returns a reference to the i'th node in the nodekit path.
  */

#else
  /**
  * Returns a pointer to the i'th node in the nodekit path.
  */

#endif //OIV_NET_DOC
  SoNode *            getNode(int i) const;

#ifdef OIV_NET_DOC
  /**
  * Returns a reference to the i'th nodekit in the chain, counting backward from the
  * tail nodekit. Passing 0 for i returns the tail nodekit.
  */

#else
  /**
  * Returns a pointer to the i'th nodekit in the chain, counting backward from the
  * tail nodekit. Passing 0 for i returns the tail nodekit.
  */

#endif //OIV_NET_DOC
  SoNode *            getNodeFromTail(int i) const;

  /**
   * Truncates the path chain, removing all nodes from index start on. Calling
   * @B truncate(0) @b empties the path entirely.
   */
  void                truncate(int start);

  /**
   * Pops the last nodekit off the end of the path.
   */
  void                pop();

  /**
   * Adds childKit to end of chain; uses first occurrence of childKit as a part
   * within current last nodekit. If the path is empty, this is equivalent to
   * @B setHead(childKit) @b.
   */
  void                append(SoBaseKit *childKit);

  /**
   * Adds all nodekits in fromPath's chain to end of chain; the head node of fromPath
   * must be the same as or a child of the current tail node.
   */
  void                append(const SoNodeKitPath *fromPath);

  /**
   * Returns TRUE if the passed nodekit is found anywhere in the path chain.
   */
  SbBool              containsNode(SoBaseKit *node) const;
    
  /**
   * If the two paths have different head nodes, this returns -1. Otherwise, it
   * returns the path chain index of the last nodekit (starting at the head) that is
   * the same for both paths.
   */
  int                 findFork(const SoNodeKitPath *path) const;

#ifdef OIV_NET_DOC
  /**
  * Returns true if all node reference in the two nodekit path chains are equal.
  */

#else
  /**
  * Returns TRUE if all node pointers in the two nodekit path chains are equal.
  */

#endif //OIV_NET_DOC
  INVENTOR_API friend int operator ==(const SoNodeKitPath &p1, const SoNodeKitPath &p2);

 protected:
  // Hide the constructor
  SoNodeKitPath(int approxLength) : SoPath(approxLength)      {}
  // Destructor
  virtual ~SoNodeKitPath();

 private:
  // This action is used to search for nodes.
  static SoSearchAction *searchAction;

};

#endif /* _SO_NODE_KIT_PATH_ */

