/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SEARCH_ACTION_
#define  _SO_SEARCH_ACTION_

#include <Inventor/actions/SoSubAction.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSearchAction
//
//  For searching for specific nodes in scene graphs. Nodes can be
//  searched for by pointer, by type (exact or derived), by name, or
//  by a combination of these. You can also specify whether you are
//  interested in only the first match, only the last match, or all
//  matches. You can also control whether normal traversal rules are
//  followed (switching, separators, etc.) or whether every single
//  node is to be searched.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Searches for nodes in a scene graph.
* 
* @ingroup actions
* 
* @DESCRIPTION
*   This class is used to search scene graphs for specific nodes, nodes of a
*   specific type, nodes with a specific name, or any combination of these. It can
*   search for just the first or last node satisfying the criteria or for all such
*   nodes. The actions return paths to each node found.
*   
*   Note that by default nodekits do not search their children when a search action
*   is applied. The reference page for SoBaseKit discusses the methods
*   SoBaseKit::isSearchingChildren() and
*   SoBaseKit::setSearchingChildren(), which allow you to query and control
*   this behavior.
*
*   All paths created by the
*   action are automatically destroyed when the action is reset
*   or destroyed.
* 
* @SEE_ALSO
*    SoPath,
*    SoBaseKit
*    SoSearchPathAction,
*    SoSearchStepAction
*/ 
#else
/**
* Searches for nodes in a scene graph.
* 
* @ingroup actions
* 
* @DESCRIPTION
*   This class is used to search scene graphs for specific nodes, nodes of a
*   specific type, nodes with a specific name, or any combination of these. It can
*   search for just the first or last node satisfying the criteria or for all such
*   nodes. The actions return paths to each node found.  The searched for node is
*   the "tail" of each path.
*
*   By default SoSearchAction only searches nodes that are actually traversed.
*   For example it would not search all the children of an SoSwitch node unless
*   the whichChild field is set to SO_SWITCH_ALL.  To search all nodes in the
*   scene graph call setSearchingAll(TRUE).
*   
*   Nodekits: @BR
*   - By default SoSearchAction will not search inside nodekits even when
*     setSearchingAll is true.  This is because nodekits try to keep their
*     children hidden.  To allow searching inside nodekits call the static
*     method SoBaseKit::setSearchingChildren(TRUE). @BR
*   - A common problem is that when the searched for node is found inside
*     a nodekit, the SoPath method getTail() does not return the found node.
*     This is also because nodekits try to keep their children hidden.  To
*     avoid this problem simply cast the returned SoPath to SoFullPath.
*
*   \oivnetdoc
*   \else
*   Remember that SoPath automatically increases the ref count
*   of every node in the path(s) (until the SoPath is destroyed).
*   For example, when a search action is applied to a node (e.g.,
*   a separator), the ref count of that node is increased by the
*   number of paths created by the search action. If the result
*   of the search is that N paths were created, the ref count of
*   the separator is increased by N. All paths created by the
*   action are automatically destroyed, and their refs removed,
*   when the action is reset or destroyed.
*   \endoivnetdoc
*
*  @EXAMPLE
*   Example 1: Given the address of a node, create a path to the
*   location of that node in the scene graph:
*   \oivnetdoc
*     \code
*     SoSearchAction sa = new SoSearchAction();
*     sa.SetNode( coneNode );
*     sa.SetSearchingAll( true );              // Search all nodes
*     SoBaseKit.SetSearchingChildren( true );  // Even inside nodekits
*     sa.Apply( rootNode );
*     SoFullPath path = (SoFullPath)sa.GetPath();
*     \endcode
*   \else
*     \code
*     SoSearchAction sa;
*     sa.setNode( pConeNode );
*     sa.setSearchingAll( TRUE );              // Search all nodes
*     SoBaseKit::setSearchingChildren( TRUE ); // Even inside nodekits
*     sa.apply( pRootNode );
*     SoFullPath *pPath = (SoFullPath*)sa.getPath();
*     \endcode
*   \endoivnetdoc
*
*   Example 2: Find all the SoFont nodes in the scene graph:
*   \oivnetdoc
*     \code
*     SoSearchAction sa = new SoSearchAction();
*     sa.SetType( typeof(SoFont) );
*     sa.SetInterest( SoSearchAction.Interests.ALL );   // Find ALL instances
*     sa.SetSearchingAll( true );              // Search all nodes
*     SoBaseKit.SetSearchingChildren( true );  // Even inside nodekits
*     sa.Apply( rootNode );
*     SoPathList pathList = sa.getPaths();    // Get list of paths
*     foreach (SoFullPath path in plist)
*     {
*       SoFont fontNode = (SoFont)path.GetTail();
*       . . .
*     }
*     \endcode
*   \else
*     \code
*     SoSearchAction sa;
*     sa.setType( SoFont::getClassTypeId() );
*     sa.setInterest( SoSearchAction::ALL );   // Find ALL instances
*     sa.setSearchingAll( TRUE );              // Search all nodes
*     SoBaseKit::setSearchingChildren( TRUE ); // Even inside nodekits
*     sa.apply( pRoot );
*     SoPathList &pathList = sa.getPaths();    // Get list of paths
*     int numPaths = pathList.getLength();     // How many instances?
*     for (int i = 0; i < numPaths; i++) {     // Loop over font nodes
*       SoFullPath *pPath = (SoFullPath*)pathList[i];
*       SoFont *pFont = (SoFont*)pPath->getTail();
*       . . .
*     }
*     \endcode
*   \endoivnetdoc
* 
* @SEE_ALSO
*    SoPath,
*    SoBaseKit,
*    SoSearchPathAction,
*    SoSearchStepAction
*
*
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoSearchAction : public SoAction {

  SO_ACTION_HEADER(SoSearchAction);

 public:

  /** Enum that defines the search criterion. */
  enum LookFor {
#ifdef OIV_NET_DOC
	  /**
	  *  Search for a particular node (by reference) 
	  */

#else
	  /**
	  *  Search for a particular node (by pointer) 
	  */

#endif //OIV_NET_DOC
	  NODE = 0x01,
    /**
     *  Search for a particular type of node 
     */
    TYPE = 0x02,
    /**
     *  Search for a node with a particular name 
     */
    NAME = 0x04
  };

  /** Enum that defines which paths to return. */
  enum Interest {
    /**
     *  Return only the first path found (default)
     */
    FIRST,
    /**
     *  Return only the last path found 
     */
    LAST,
    /**
     *  Return all paths found 
     */
    ALL
  };

  /**
   * Constructor.
   */
  SoSearchAction();

  // Destructor
#ifndef HIDDEN_FROM_DOC
  virtual ~SoSearchAction();
#endif // HIDDEN_FROM_DOC

  /**
   * Resets options back to default values; clears list of returned paths. This can
   * be used to apply the action again with a different set of search criteria.
   */
  virtual void reset();

  /**
   * Sets what to look for; @B what @b is a bitmask of @B LookFor @b enum
   * values. Default is no flags at all. Note that setting a node, type, and/or name
   * to search for activates the relevant flag, so you may never need to call this
   * method directly.
   */
  void setFind(int what) { lookingFor = what; }

  /**
   * Returns what to look for.
   */
  int getFind() { return lookingFor; }

  /**
   * Returns the node to search for.
   */
  SoNode *getNode() const { return node; }

  /**
   * Sets the node to search for.
   */
  void setNode(SoNode *n);

  /**
   * Returns the node type to search for. 
   * [OIVJAVA-WRAPPER NAME{getNodeClass},DUPLICATE{isSearchingExtendedClass}]
   * [OIVJAVA-WRAPPER-ARG NO_WRAP]
   * [OIVJAVA-WRAPPER-RETURN-TYPE APPLY_TO{isSearchingExtendedClass} NO_WRAP]
   */
  SoType getType(SbBool &derivedIsOk) const
    { derivedIsOk = derivedOk; return type; }     

  /**
   * Sets the node type to search for. If @B derivedIsOk @b is TRUE, a node
   * that is of a type that is derived from @B t@b will pass this search criterion.
   * [OIVJAVA-WRAPPER NAME{setNodeClass}]
   */
  void setType(SoType t, SbBool derivedIsOk = TRUE);

  /**
   * Returns the name of the node to search for.
   */
  const SbName &getName() const { return name; }

  /**
   * Sets the name of the node to search for.
   */
  void setName(const SbName &n);

  /**
   * Returns which paths to return. 
   */
  Interest getInterest() const { return interest; }

  /**
   * Sets which paths to return. Default is FIRST.
   */
  void setInterest(Interest i) { interest = i; }

  /**
   * Returns FALSE if searching uses regular traversal, TRUE if it traverses
   * every single node. Default is FALSE.
   */
  SbBool isSearchingAll() const { return searchingAll; }

  /**
   * Sets whether searching uses regular traversal or whether it traverses
   * every single node. For example, if this flag is FALSE, an SoSwitch node will
   * traverse only the child or children it would normally traverse for an action. If
   * the flag is TRUE, the switch would always traverse all of its children. The
   * default is FALSE.
   */
  void setSearchingAll(SbBool flag) { searchingAll = flag; }

  /**
   * Returns resulting path, or NULL if no path was found. This should be used if the
   * interest is FIRST or LAST.
   */
  SoPath *getPath() const { return retPath; }

  /**
   * Returns resulting path list. This should be used if the interest is ALL.
   */
  SoPathList &getPaths() { return retPaths; }
  
 SoEXTENDER public:

  // Sets/returns whether action has found all desired nodes
  // (implementation moved into source file for v2.6)
  virtual void setFound();
  SbBool isFound() const { return hasTerminated(); }
  
  // Sets found path or adds to list of found paths (depending on interest)
  void addPath(SoPath *path);
  
 SoINTERNAL public:

  static void initClass();
  static void exitClass();
 
  // This flag is used by the SoSwitch node, which must return a
  // different result from its 'affectsState' method when called
  // during a SearchAction that is searching all children.
  static SbBool duringSearchAll;
  
 protected:

  // Initiates action on graph
  virtual void beginTraversal(SoNode *node);
  
 private:

  // Node type id to search for
  SoType type;

  // Exact match or derived ok
  SbBool derivedOk;

  // Node to search for
  SoNode *node;

  // Name of node to search for 
  SbName name;

  // What to search for
  int lookingFor;

  // Which paths to return
  Interest interest;

  // Search all children or follow normal traversal rules.
  SbBool searchingAll;

  // Found node (if interest != ALL)
  SoPath *retPath;

  // Found nodes (if interest == ALL)
  SoPathList retPaths;
};

#endif /* _SO_SEARCH_ACTION_ */

