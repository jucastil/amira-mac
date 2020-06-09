/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Sep 2003)
**=======================================================================*/

#ifndef  _SO_REPLACED_TEXTURE_ELEMENT_
#define  _SO_REPLACED_TEXTURE_ELEMENT_

/**
*  @VSGEXT Abstract base class for each texture state element.
*
*  @ingroup elements
*
*   @DESCRIPTION
*   This is the abstract base class for each texture state element.
*   A node-id is associated to each texture unit.
*
*   Subclasses may need to override the push() method to copy values
*   from the next instance in the stack (using getNextInStack() ),
*   if the new one has to copy values (node-id) on top of the old ones.
*
*   This class defines the matches() method to compare lists of
*   node-id's associated to each texture unit.
*   The node-id's represent the states of all nodes that
*   changed the value of the element. SoReplacedTextureElement provides
*   methods that maintain lists of node-id's of all nodes that affect
*   an instance. Subclasses must call these methods to make sure the
*   id's are up to date, if they plan to use the standard matches()
*   method. Otherwise, they can define matches() differently, if they
*   wish.
*
*   @SEE_ALSO
*/

#include <Inventor/elements/SoSubElement.h>
#include <Inventor/STL/vector>

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

SoEXTENDER_Documented class INVENTOR_API SoReplacedTextureElement : public SoElement {

  SO_ELEMENT_ABSTRACT_HEADER(SoReplacedTextureElement);

 public:
  /**
  *  Returns TRUE if the element matches another element, based on node-id's.
  */
 virtual SbBool      matches(const SoElement *elt) const;

 /**
 *  Prints element (for debugging).
 */
 virtual void        print(FILE *fp) const;

  /**
  *  Pushes the element, copying values from previous element in
  *  state. node-ids associated to each texture unit are copied.
  */
  virtual void push(SoState *state) ;

 SoINTERNAL public:
  // Initializes the SoReplacedTextureElement class
  static void         initClass();
  static void         exitClass();

  // Common Initialization. Directly called by the constructor.
  virtual void commonInit() ;

protected:
  // Overrides SoElement::getElement() to set the nodeId of the current
  // texture unit in the element instance before returning it.
  // static SoElement *getElement(SoState *state, int stackIndex, SoNode *node) ;
  static SoElement *getElement(SoState *state, SoType type, int stackIndex, SoNode *node) ;

  template<typename T>
  static T *getElement(SoState *state, int stackIndex, SoNode *node)
  {
    return static_cast<T*>(getElement(state, T::getClassTypeId(), stackIndex, node));
  }

  // Sets the id of the given node of the current texture unit
  void                setNodeId(SoState *state, const SoNode *node);

  // Create and return a copy of this element; this will copy the
  // nodeId list properly.
  virtual SoElement   *copyMatchInfo() const;

  // Destructor
  virtual ~SoReplacedTextureElement();

  // return the nodeId for the given texture unit
  uint64_t& getNodeId(const int unit) const;

private:
  // This stores the list of node id's as pointers associated to
  // each texture unit.
  typedef std::vector<uint64_t> SoNodeIdList;
  mutable SoNodeIdList m_nodeIdList;
};

#ifdef WIN32
#pragma warning( pop )
#endif

#endif /* _SO_REPLACED_TEXTURE_ELEMENT_ */
