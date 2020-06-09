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


#ifndef  _SO_REPLACED_ELEMENT
#define  _SO_REPLACED_ELEMENT

/**
*   Abstract base class for each state element whose value
*   is replaced whenever it is set
*
* @ingroup elements
*
*   @DESCRIPTION
*   This is the abstract base class for each state element whose value
*   is replaced whenever it is set. (Most state elements fall into
*   this category, so most are derived from this class.)
*
*   This class overrides the SoElement::getElement() method to store
*   the node-id of the node that is about to set the value in the
*   element (i.e., the node that is passed to getElement()). This
*   class also defines the SoElement::matches() method to return TRUE
*   if the node-id's of the two elements match. Subclasses can change
*   this behavior by defining matches() differently, if they wish. For
*   example, they can compare the elements' values, instead.
*
*   @SEE_ALSO
*/

#include <Inventor/elements/SoSubElement.h>

SoEXTENDER_Documented class INVENTOR_API SoReplacedElement : public SoElement {

  SO_ELEMENT_ABSTRACT_HEADER(SoReplacedElement);

 public:
  /**
  *  Returns TRUE if the element matches another element, based on node-id.
  */
  virtual SbBool      matches(const SoElement *elt) const;

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoReplacedElement class
  static void         initClass();
  static void         exitClass();

  // Initializes node id in element (directly calle dby constructor)
  virtual void        commonInit();

  // Initializes node id in element
  virtual void        init(SoState *state);

  // Create and return a copy of this element.  The only operation
  // supported by the copy is matches() (the copy will be
  // unitialized except for the nodeId).
  virtual SoElement   *copyMatchInfo() const;

  // Return nodeId.  This was added so the SoTransformSeparator
  // class can figure out whether or not it contains a camera:
  uint64_t getNodeId() const { return nodeId; }

  // Sets the current nodeId.
  void setNodeId( uint64_t id ) { nodeId = id; }

 protected:

  // Overrides SoElement::getElement() to set the nodeId in the
  // element instance before returning it.
  // static SoElement *  getElement(SoState *state, int stackIndex,
  //                                SoNode *node);
  static SoElement *  getElement(SoState *state, SoType type, int stackIndex,
                                 SoNode *node);
  template<typename T>
  static T* getElement(SoState *state, SoNode *node)
  {
    return static_cast<T*>(getElement(state, T::getClassTypeId(), T::getClassStackIndex(), node));
  }

  // Destructor
  virtual ~SoReplacedElement();

private:
  uint64_t nodeId;

};

#endif /* _SO_REPLACED_ELEMENT */
