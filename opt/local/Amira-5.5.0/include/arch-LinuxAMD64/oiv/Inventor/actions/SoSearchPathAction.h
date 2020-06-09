/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Mike Heck (Apr 2000)
**=======================================================================*/


#ifndef  _SO_SEARCHPATH_ACTION_
#define  _SO_SEARCHPATH_ACTION_

// Note: Not necessary to include SoSubAction.h because it is already
//       included by SoSearchAction.h
#include <Inventor/actions/SoSearchAction.h>

#ifdef OIV_NET_DOC

/**
 * @VSGEXT Searches for a node in a scene graph using a sequence of search criteria.
 * 
 * @ingroup actions
 * 
 * @DESCRIPTION
 *   This class extends SoSearchAction to search for a sequence of items defined in a
 *   string, e.g., "Wheel1/Hub/Bearing". Each item can be a
 *   
 *   - Node name, or
 *   
 *   - Node type (type name in angle brackets, e.g., "<Cone>"), or
 *   
 *   - Node address (hex value starting with zero, e.g., "0x100fa30").
 *
 *   When the action finds a node that satisfies the current search item, it
 *   effectively restarts the search from that node, using the next search item. This
 *   means that the search for each item (after the first) is confined to the
 *   subgraph under the node that satisfied the previous search item. In most cases
 *   each item (except possibly the last one) will be a grouping node, but this is
 *   not enforced by the action.
 *   
 *   Finding nodes by name is a useful technique for modifying a scene graph, but
 *   using SoNode::getByName or SoSearchAction requires assigning a unique name to
 *   every (interesting) node. Often the same subgraph will be used multiple times
 *   and it would be convenient to assign each instance of the subgraph a unique
 *   name, but reuse the same names for the nodes inside the subgraph.
 *   SoSearchPathAction allows this kind of hierarchical naming.
 *   
 *   Given a scene graph with hierarchical names, for example:
 *   
 *   <PRE>
 *   DEF Wheel1 Separator {
 *       DEF Hub Separator {
 *           DEF Bolt Separator {
 *               Cylinder { height 3 }
 *           }
 *       }
 *   }
 *   DEF Wheel2 Separator {
 *       DEF Hub Separator {
 *           DEF Bolt Separator {
 *               Cylinder { height 13 }
 *           }
 *       }
 *   } </PRE>
 *    
 *   
 *   "Wheel1/Hub/Bolt" would find "Bolt" in the first wheel. Intermediate names may be
 *   omitted if the search string is still unambiguous. For example "Wheel1/Bolt"
 *   would find the same node in this simple case. "Wheel2/Hub/Bolt/<Cylinder>" would
 *   return a path including the leaf SoCylinder node in the second wheel.
 *
 *   In the simplest case:
 *   \code 
 *    SoSearchPathAction spa;
 *    spa.SetSearchString( "Wheel1" );
 *   \endcode
 *    is equivalent to:
 *   \code 
 *    SoSearchAction sa;
 *    sa.SetName( "Wheel1" ); // By default, interest is FIRST
 *   \endcode
 *   
 *   Most of the methods inherited from SoSearchAction are ignored and do not return
 *   useful information (set/getNode, set/getName, etc.). Relevant inherited methods
 *   are set/isSearchingAll, getPath, and reset.
 *   
 *   Note that by default nodekits do not search their children when a search action
 *   is applied. The reference page for SoBaseKit discusses the methods
 *   SoBaseKit::isSearchingChildren() and
 *   SoBaseKit::setSearchingChildren(), which allow you to query and control
 *   this behavior.
 * 
 * @SEE_ALSO
 *    SoPath,
 *    SoSearchAction,
 *    SoSearchStepAction,
 *    SoBaseKit
 */ 
#else
/**
 * @VSGEXT Searches for a node in a scene graph using a sequence of search criteria.
 * 
 * @ingroup actions
 * 
 * @DESCRIPTION
 *   This class extends SoSearchAction to search for a sequence of items defined in a
 *   string, e.g., "Wheel1/Hub/Bearing". Each item can be a
 *   
 *   - Node name, or
 *   
 *   - Node type (type name in angle brackets, e.g., "<Cone>"), or
 *   
 *   - Node address (hex value starting with zero, e.g., "0x100fa30").
 *
 *   When the action finds a node that satisfies the current search item, it
 *   effectively restarts the search from that node, using the next search item. This
 *   means that the search for each item (after the first) is confined to the
 *   subgraph under the node that satisfied the previous search item. In most cases
 *   each item (except possibly the last one) will be a grouping node, but this is
 *   not enforced by the action.
 *   
 *   Finding nodes by name is a useful technique for modifying a scene graph, but
 *   using SoNode::getByName or SoSearchAction requires assigning a unique name to
 *   every (interesting) node. Often the same subgraph will be used multiple times
 *   and it would be convenient to assign each instance of the subgraph a unique
 *   name, but reuse the same names for the nodes inside the subgraph.
 *   SoSearchPathAction allows this kind of hierarchical naming.
 *   
 *   Given a scene graph with hierarchical names, for example:
 *   
 *   <PRE>
 *   DEF Wheel1 Separator {
 *       DEF Hub Separator {
 *           DEF Bolt Separator {
 *               Cylinder { height 3 }
 *           }
 *       }
 *   }
 *   DEF Wheel2 Separator {
 *       DEF Hub Separator {
 *           DEF Bolt Separator {
 *               Cylinder { height 13 }
 *           }
 *       }
 *   } </PRE>
 *    
 *   "Wheel1/Hub/Bolt" would find "Bolt" in the first wheel. Intermediate names may be
 *   omitted if the search string is still unambiguous. For example "Wheel1/Bolt"
 *   would find the same node in this simple case. "Wheel2/Hub/Bolt/<Cylinder>" would
 *   return a path including the leaf SoCylinder node in the second wheel.
 *
 *   In the simplest case:
 *   \code 
 *    SoSearchPathAction spa;
 *    spa.setSearchString( "Wheel1" );
 *   \endcode
 *    is equivalent to:
 *   \code 
 *    SoSearchAction sa;
 *    sa.setName( "Wheel1" ); // By default, interest is FIRST
 *   \endcode
 *   
 *   Most of the methods inherited from SoSearchAction are ignored and do not return
 *   useful information (set/getNode, set/getName, etc.). Relevant inherited methods
 *   are set/isSearchingAll, getPath, and reset.
 *   
 *   Note that by default nodekits do not search their children when a search action
 *   is applied. The reference page for SoBaseKit discusses the methods
 *   SoBaseKit::isSearchingChildren() and
 *   SoBaseKit::setSearchingChildren(), which allow you to query and control
 *   this behavior.
 * 
 * @SEE_ALSO
 *    SoPath,
 *    SoSearchAction,
 *    SoSearchStepAction,
 *    SoBaseKit
 */ 
#endif  // OIV_NET_DOC

class INVENTOR_API SoSearchPathAction : public SoSearchAction {

  SO_ACTION_HEADER(SoSearchPathAction);

 public:

  /**
   * Constructor. The default action searches for first node of or derived from given
   * type, using regular traversal rules.
   */
  SoSearchPathAction();

  /**
   * Destructor
   */
  virtual ~SoSearchPathAction();

  /**
   * Reset options back to default values, clears returned path.
   */
  void            reset();

  /**
   * Sets the search path string.
   */
  void            setSearchString( const char *searchString );
  /**
   * Gets the search path string.
   */
  const SbString& getSearchString() const
    { return m_strSearchString; };

  /**
   * Sets separator char for search string. The default is '/'.
   */
  void            setSeparatorChar( const char sepChar )
    { m_cSepChar = sepChar; }
  /**
   * Gets separator char for search string. 
   */
  char            getSeparatorChar() const
    { return m_cSepChar; }

  /**
   * Sets flag to allow search on a type to match derived types. 
   */
  void            setDerivedIsOK( const SbBool derivedIsOK )
    { m_bDerivedIsOK = derivedIsOK; };
  /**
   * Gets flag to allow search on a type to match derived types. 
   */
  SbBool          getDerivedIsOK() const
    { return m_bDerivedIsOK; };

  /**
   * Get the number of search items that were successfully found. If the complete
   * search succeeded and a path was returned, then this will be the total number of
   * search items (not in general the same as the number of nodes in the returned
   * path!). If the search failed, this indicates which search item was the problem.
   */
  int             getNumItemsFound() const
    { return m_nItemNum; };

 SoEXTENDER public:
  // Notifies action that the current node satisfies the current search item.
  virtual void    setFound();

 SoINTERNAL public:
  static void     initClass();
  static void     exitClass();

  // Static and instance-specific callbacks called during traversal
  static  void    searchStatic(SoAction *action, SoNode *node);
  virtual void    search      (SoNode *node);

 protected:
  // Initiates action on graph
  virtual void    beginTraversal(SoNode *node);

  // Classify search item and call appropriate SearchAction method
  SbBool          setSearchParameters( const char* item );

  // Result of setupNextSearchItem
  enum ItemSetupResult {
    NO_MORE_ITEMS,
    VALID_ITEM,
    INVALID_ITEM
  };

  // Extract next search item from search string and get ready to go.
  ItemSetupResult setupNextSearchItem();

  SbString        m_strSearchString;  // Search string
  char           *m_pStartChar;       // Points to next search item
  char            m_cSepChar;         // Char that separates search items
  SbBool          m_bDerivedIsOK;     // Will type search match derived types
  int             m_nItemNum;         // Which search item is active (for error reporting)

 private:

};

#endif /* _SO_SEARCHPATH_ACTION_ */

