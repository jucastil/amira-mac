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

#ifndef  _SO_STATE_
#define  _SO_STATE_

#include <Inventor/SoLists.h>

class SoAction;
class SoElement;

/**
*  Traversal state
*
* @ingroup General
*
* @DESCRIPTION
*  An SoState collects and holds state while traversing a scene
*  graph. A state is composed of a variety of elements, each of which
*  holds some specific information, such as coordinates or diffuse
*  color of the surface material.
*
*  Each element is stored in its own stack so that save and restore
*  can be implemented as push and pop. These stack operations are
*  performed lazily, so that pushing of a value occurs only when the
*  value would be overwritten, for efficiency.
*
**/
//SoEXTENDER class INVENTOR_API SoState {
class INVENTOR_API SoState {

public:
  /** Constructor.
  * Takes pointer to action instance this state is
  * part of and a list of type-ids of elements that are enabled.
  */
  SoState(SoAction *action, const SoTypeList &enabledElements);

  /** Destructor */
  ~SoState();

  /** Returns the action instance the state is part of */
  inline SoAction* getAction() const
  { return action; }

  /**
   * Returns a writable instance of the element on the top of the
   * stack with the given stack index. @BR
   * @deprecated Use the templated version
   */
  SoElement* getElement(const int stackIndex);

  /**
   * Returns a writable instance of the element on the top of the
   * stack with the given type.
   */
  template<typename T>
  T* getElement()
  {
    return static_cast<T*>(getElement(T::getClassTypeId(), T::getClassStackIndex()));
  }

  /**
   * Returns a writable instance of the element on the top of the
   * stack with the given index and type. @BR
   * We recommend using the templated type safe version.
   */
  SoElement* getElement(SoType type, const int stackIndex);

  /**
   * Returns the top (read-only) instance of the given element
   */
  template<typename T>
  inline const T* getConstElement() const
  {
    return static_cast<const T*>(getConstElement(T::getClassTypeId(), T::getClassStackIndex(), true));
  }

  /**
   * Returns the top (read-only) instance of the given element stack. @BR
   * @deprecated Use the type safe templated version
   */
  const SoElement* getConstElement(const int stackIndex) const;

  /** 
   * Returns the top (read-only) instance of the given element stack. @BR
   * We recommend using the templated type safe version.
   */
  inline const SoElement* getConstElement(SoType type, const int stackIndex) const
  {
    return getConstElement(type, stackIndex, false);
  }

  /** Pushes (saves) the current state until a pop() restores it. The
  * push is done lazily: this just increments the depth in the
  * state. When an element is accessed with getElement() and its
  * depth is less than the current depth, it is then pushed
  * individually.
  */
  void push()
  { depth++; }

  /** Pops the state, restoring the state to just before the last push(). */
  void pop();

  /** Prints state to file (for debugging) */
  void print(FILE *fp);

 SoINTERNAL public:
  /** Returns TRUE if element with given stack index is enabled in state */
  SbBool isElementEnabled(SoType type, const int stackIndex, SbBool checkType = TRUE) const;

  // Returns TRUE if element with given stack index is enabled in state
  SbBool isElementEnabled(const int stackIndex) const
  {
    if (stack)
      return (stack[stackIndex] != NULL);
    else
      return FALSE;
  }

  // Returns current depth of state
  int getDepth() const
  { return depth; }

  // Sets/returns flag that indicates whether a cache is open. This
  // flag lets us optimize element capturing; we don't need to try
  // to capture elements if the flag is FALSE.
  void setCacheOpen(const SbBool flag)
  { cacheOpen = flag; }

  SbBool isCacheOpen() const
  { return cacheOpen; }

  /** @deprecated Use the templated version */
  SoElement* getElementNoPush(const int stackIndex) const;

  /**
   * Internal-only, dangerous method that returns a writeable
   * element without checking for state depth and doing a push.
   * Be very careful and consider the caching implications before
   * using this method!
   */
  template<typename T>
  T* getElementNoPush() const
  {
    return static_cast<T*>(getElementNoPush(T::getClassTypeId(), T::getClassStackIndex()));
  }

  /**
   * Internal-only, dangerous method that returns a writeable
   * element without checking for state depth and doing a push.
   * Be very careful and consider the caching implications before
   * using this method!
   */
  SoElement* getElementNoPush(SoType type, const int stackIndex) const
  {
    return const_cast<SoElement*>(getConstElement(type, stackIndex, true));
  }

  // Internal-only.
  // Pops from the an element corresponding to classStackIndex.
  // Only the side effect of popping is done (ie. the element is not
  // removed from the stack).
  void popElement(const int classStackIndex) ;

  /**
   * Returns the top (read-only) instance of the given element stack
   * If checkType is true, check if a dervied element has not already been enabled
   */
  inline const SoElement* getConstElement(SoType type, const int stackIndex, bool checkType) const
  {
    if ( !stack )
      return NULL;
    enableMissingElement(type, stackIndex, checkType);
    return stack[stackIndex];
  }

private:
  /** Return the type which should be instancied for the current action */
  SoType getBestElementType(SoType type) const;

  /** Create the depth 0 element with given stackIndex */
  void createDepth0Element(int stackIndex);

  /** Show stacked elements */
  void displayStack();

  /**Check that elements are sorted by depth */
  void checkStateConsistency();

  /** Enable stackindex element for the current action */
  void enableMissingElement(SoType type, int stackIndex, bool checkType) const;

  SoAction            *action;        // Action instance state is in
  int                 depth;          // Current depth
  SoElement           **stack;        // Array of element stacks
  int                 numStacks;      // Number of stacks in array
  SoElement *         topElement;     // First element in threaded stack

  SbBool              cacheOpen;      // TRUE if a cache is open

  /** Debug modes */
  static int s_checkStateConsistency;
  static int s_displayStateElements;
  static int s_checkStateElementsType;
};

#endif  /* _SO_STATE_ */
