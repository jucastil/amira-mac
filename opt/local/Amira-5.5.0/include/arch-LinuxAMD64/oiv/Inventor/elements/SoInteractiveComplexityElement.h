/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _SO_INTERACTIVE_COMPLEXITY_ELEMENT
#define  _SO_INTERACTIVE_COMPLEXITY_ELEMENT

#include <Inventor/elements/SoAccumulatedElement.h>
#include <Inventor/STL/vector>

class SoInteractiveComplexity;
class SoSField;
class SoSFBool;
class SoSFEnum;

/**
 * @VSGEXT Stores the current interactive complexity.
 *
 * @ingroup elements
 *
 *   @DESCRIPTION
 *   This element stores the current interactive complexity.
 *
 *   @SEE_ALSO
 *   SoInteractiveComplexity
*/

SoEXTENDER_Documented class INVENTOR_API SoInteractiveComplexityElement : public SoAccumulatedElement
{
  SO_ELEMENT_HEADER(SoInteractiveComplexityElement);

 public:

  /** Set the current SoInteractiveComplexity node */
  static void set(SoState *state, SoInteractiveComplexity* node);

  /** Return value of scalar field as a double */
  static double getScalarFieldValue(SoState *state,
                                    const SoSField* field);

  /** Return value of a SoSFBool */
  static SbBool getBooleanFieldValue(SoState *state, const SoSFBool* field);

  /** Return value of a SoSFEnum */
  static int getEnumFieldValue(SoState *state, const SoSFEnum* field);

  /**
   *  Overrides push() method to copy values from next instance in the stack.
   */
  virtual void push(SoState *state) ;

  /** Pop method. */
  virtual void pop(SoState *, const SoElement *prevTopElement) ;

 SoINTERNAL public:
  // Initializes the SoInteractiveComplexityElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

  /** Return value of field as a double */
  static double getCurrentScalarFieldValue(const SoSField* field);

  /** Return true if the field is bounded  */
  static bool isBounded(SoState* state, const SoSField* field);

 protected:
  typedef std::vector<SoInteractiveComplexity*> ComplexityVector;
  typedef ComplexityVector::const_reverse_iterator ComplexityVectorConstRevIt;

  /** Return the last complexity on state which change this field */
  SoInteractiveComplexity* findComplexity(const SoSField* field) const;

  /** Return value of field as a double */
  double getScalarFieldValueInternal(SoState* state, const SoSField* field) const;
  SbBool getBooleanFieldValueInternal(SoState* state, const SoSFBool* field) const;
  int getEnumFieldValueInternal(SoState* state, const SoSFEnum* field) const;

  void setElt(SoState *state, SoInteractiveComplexity* node);

  virtual ~SoInteractiveComplexityElement();

  /** List of SoInteractiveComplexity */
  ComplexityVector m_nodeList;

  //Element has been pushed at this point
  size_t m_startIndex;
};

#endif /* _SO_COMPLEXITY_ELEMENT */
