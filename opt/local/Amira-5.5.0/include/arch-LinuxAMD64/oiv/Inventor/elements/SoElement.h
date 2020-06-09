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


#ifndef  _SO_ELEMENT
#define  _SO_ELEMENT

#include <Inventor/SoType.h>
#include <Inventor/SoTypedObject.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/errors/SoDebugError.h>

/**
 *   Abstract base class for all state elements.
 *
 * @ingroup elements
 *
 *   @DESCRIPTION
 *   This is the abstract base class for all state elements. This class
 *   defines the following features for all of its derived classes:
 *
 *       @B Type identifiers: @b Each class of element has a unique (static)
 *       SoType identifier. The correct type id is also stored in each
 *       instance for easy access.
 *
 *       @B Copying: @b Elements are copied into the list of elements used
 *       in an SoCache. Performing any operation other than matches()
 *       on a copied element is not guaranteed to work (and will not
 *       work for things like Coordinates, if the coordinate they were
 *       pointing to has been deleted).
 *
 *       @B Stack indices: @b Since a subclass of an element class needs to
 *       be in the same state stack as the class from which it is
 *       derived, stack indices are inherited.
 *
 *       @B Capturing: @b Each time an element's value is accessed, that
 *       element is added to the elements-used list of all currently
 *       open caches.
 *
 *   @SEE_ALSO
 */

SoEXTENDER_Documented class INVENTOR_API SoElement: public SoTypedObject {

 public:
  /**
  *  Initializes element. Called for first element of its kind in
  *  stack. Default method does nothing.
  */
  virtual void init(SoState *state);

  /**
  *  Common initialization. Directly called by the constructor.
  *  Default method does nothing.
  */
  virtual void commonInit() ;

  /**
  *  Pushes element. Allows for side effects to occur. Default
  *  methods do nothing.
  */
  virtual void push(SoState *state);
  /**
  *  Pops element. Allows for side effects to occur. Default
  *  methods do nothing.
  */
  virtual void pop(SoState *state, const SoElement *prevTopElement);

  /**
  *  Prints element (for debugging).
  */
  virtual void print(FILE *fp) const;

  /**
  *  Returns TRUE if the element matches another element (of the
  *  same class, presumably) with respect to cache validity.  If you
  *  write a matches() method, you must also write a copy() method.
  */
  virtual SbBool matches(const SoElement *elt) const = 0;

  /**
  *  Create a copy that we can put in a cache used list and call
  *  matches() on later.
  */
  virtual SoElement* copyMatchInfo() const = 0;

  /**
  *  Returns type identifier for SoElement class.
  */
  static SoType getClassTypeId();

  /**
  *  Returns type identifier for element instance.
  */
  virtual SoType getTypeId() const       { return typeId; }

 SoINTERNAL public:
  // Initialize ALL Inventor element classes
  static void initElements();
  static void exitElements();

  // Initializes the SoElement class
  static void initClass();
  static void exitClass();

  // Returns the number of stack indices allocated
  static int getNumStackIndices();

  // Returns the id for the element with the given stack index
  static SoType getIdFromStackIndex(int stackIndex);

  // Returns the stack index for an element instance
  inline int getStackIndex() const   { return stackIndex; }

  // Sets stuff in an element instance
  void setDepth(int dpth)              { depth = dpth; }
  void setNext(SoElement *nxt)         { next = nxt; }
  void setNextInStack(SoElement *nxt)  { nextInStack = nxt; }
  void setNextFree(SoElement *nxt)     { nextFree = nxt; }

  // Returns stuff from element instance
  int getDepth() const               { return depth; }
  SoElement* getNext()  const        { return next; }

  // Returns next instance in specific element stack
  SoElement* getNextInStack() const          { return nextInStack; }

  /** @deprecated Use the type safe templated version.
   * Returns a read-only pointer to the top instance in the given
   * element stack
   */
  static const SoElement* getConstElement(SoState *state, int stackIndex);

  /** @deprecated Use the type version */
  static const SoElement* getStackElement(SoState *state, int stackIndex);

  static const SoElement* getStackElement(SoState *state, SoType type, int stackIndex);
  static const SoElement* getConstElement(SoState *state, SoType type, int stackIndex);

  template<typename T>
  static const T* getConstElement(SoState *state)
  {
    return static_cast<const T*>(getConstElement(state, T::getClassTypeId(), T::getClassStackIndex()));
  }

  // Sets/Gets the pop priority.
  // Higher priority will be popped first.
  void setPopPriority(uint32_t priority) {m_popPriority = priority ;}
  uint32_t getPopPriority() const { return m_popPriority ; }

  // Destructor
  virtual ~SoElement();

#if defined(_DEBUG)
  SbPList* m_dbCheckPoint;
#endif

 protected:
  // Constructor; use typeId.createInstance to create elements.
  SoElement();

  /**
   *@deprecated Use the type safe templated version.
   * Returns an instance of an element from the stack with the given
   * index in the given state. This instance is writeable. This
   * returns NULL if no writable instance can be returned.
   */
  static SoElement* getElement(SoState *state, int stackIndex);

  /**
   *Returns an instance of an element from the stack. This instance is writeable. This
   *returns NULL if no writable instance can be returned.
   */
  template<typename T>
  static T* getElement(SoState *state)
  {
    return static_cast<T*>(getElement(state, T::getClassTypeId(), T::getClassStackIndex()));
  }

  static SoElement* getElement(SoState *state, SoType type, int stackIndex);

  // Does whatever is necessary in state to capture this element for
  // caching purposes. Should be called by subclasses whenever
  // any value in the element is accessed.
  void capture(SoState *state) const
    { if (state->isCacheOpen()) captureThis(state); }

  // Really captures this element, once it has been determined that
  // a cache is open to capture it
  virtual void captureThis(SoState *state) const;

  // Sets typeId in instance
  void setTypeId(SoType id)            { typeId = id; }

  // Sets stackIndex in instance
  void setStackIndex(int index)        { stackIndex = index; }

  // Returns next free element in a specific element stack
  SoElement* getNextFree() const             { return nextFree; }

  inline void setPopped(SbBool flag)         { m_popped = flag; }
  inline SbBool isPopped() const             { return m_popped ; }

  static int getClassStackIndex();

 SoINTERNAL protected:
  // Creates and returns a new stack index
  static int createStackIndex(SoType id);
  int m_popPriority ; // Stores the pop priority.

  /**
   * Insert an element at the given depth in the element list
   * Return the new first element
   */
  SoElement* insertAtDepth(SoElement* elt, int depth);
  SoElement* replaceElement(SoState* state, SoElement* oldElt, SoElement* newElt);

 private:
  void updateNextInStackAndFree(SoElement* oldElt, SoElement* newElt);

  static int         classStackIndex;  // Stack index for SoElement class

  // Type identifier stuff
  static SoType      classTypeId;    // Type identifier for SoElement class
  SoType              typeId;         // Type identifier for instance

  // Stack index stuff
  static int         nextStackIndex; // Next stack index to allocate

  static SoTypeList  *stackToType;   // Correlates stack index to type id
  int                 stackIndex;     // Stack index for instance

  // Other per-instance stuff

  // nextInStack and nextFree are the pointers in a doubly-linked
  // list for each stack in the state.  nextInStack points toward
  // the bottom of the stack and nextFree points toward the top of
  // the stack.  Once a stack has been fully allocated, pushing
  // becomes simply following the nextFree pointer and popping
  // becomes following the nextInStack pointer.

  SoElement           *nextInStack;   // Next element of same type on stack
  SoElement           *nextFree;      // Next free element
  SoElement           *next;          // Next element in all-element


  // stack
  int                 depth;          // Stack depth of element
  SbBool              m_popped ;      // Indicates if the element has been popped.
  friend class SoState;
};

#endif /* _SO_ELEMENT */
