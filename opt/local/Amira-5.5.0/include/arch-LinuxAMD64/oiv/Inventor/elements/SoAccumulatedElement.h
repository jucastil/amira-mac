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


#ifndef  _SO_ACCUMULATED_ELEMENT
#define  _SO_ACCUMULATED_ELEMENT

/**
* 
*   Abstract base class for each state element whose value
*   may be accumulated when it is set
*
*   @ingroup elements
*
*   @DESCRIPTION
*   This is the abstract base class for each state element whose value
*   may be accumulated when it is set. (This is rare.) Examples are
*   transformations and profiles.
* 
*   Subclasses may need to override the push() method to copy values
*   from the next instance in the stack (using getNextInStack() ),
*   if the new one has to accumulate values on top of the old ones.
* 
*   This class defines the matches() method to compare lists of
*   node-id's. The node-id's represent the states of all nodes that
*   changed the value of the element. SoAccumulatedElement provides
*   methods that maintain lists of node-id's of all nodes that affect
*   an instance. Subclasses must call these methods to make sure the
*   id's are up to date, if they plan to use the standard matches()
*   method. Otherwise, they can define matches() differently, if they
*   wish.
*
*   @SEE_ALSO
*   Referenced classes go here.
*
*/

#include <Inventor/elements/SoSubElement.h>

SoEXTENDER_Documented class INVENTOR_API SoAccumulatedElement : public SoElement {

  SO_ELEMENT_ABSTRACT_HEADER(SoAccumulatedElement);

 public:
  /**
   *  Returns TRUE if the element matches another element, based on node-id's.
   */
  virtual SbBool      matches(const SoElement *elt) const;

  /**
   *  Prints element (for debugging).
   */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoAccumulatedElement class
  static void         initClass();
  static void         exitClass();

 protected:
  // Clears out the list of node id's
  void                clearNodeIds();

  // Adds the id of the given node to the current list
  void                addNodeId(const SoNode *node);

  // Sets the node id list to JUST the id of the given node
  void                setNodeId(const SoNode *node);

  // Create and return a copy of this element; this will copy the
  // nodeId list properly.
  virtual SoElement   *copyMatchInfo() const;

  // Override normal capture method to capture elements at other
  // depths that we are accumulating with.
  virtual void        captureThis(SoState *state) const;

  // Destructor
  virtual ~SoAccumulatedElement();

  typedef std::set<uint64_t> SoNodeIdList;
  void setNodeIdList( SoNodeIdList& nodeIdList );
  SoNodeIdList& getNodeIdList() { return m_nodeIdList; }

 private:
  SbBool accumulatesWithParentFlag;

  // This stores the list of node id's.
  mutable SoNodeIdList m_nodeIdList;
};

#endif /* _SO_ACCUMULATED_ELEMENT */
