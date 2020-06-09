/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _SO_BEVEL_PROPERTY_ELEMENT
#define  _SO_BEVEL_PROPERTY_ELEMENT

#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/nodes/SoBevelProperty.h>

/**
* @VSGEXT Stores various beveling attributes.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores various beveling attributes.
*   @SEE_ALSO
*   SoBevelProperty
*/

SoEXTENDER_Documented class INVENTOR_API SoBevelPropertyElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(SoBevelPropertyElement);

 public:

  /**
  *  Sets the bevel angle: if 2 adjacent faces make a greater angle,
  *  then their common edge is beveled.
  */
  static void   setAngle(SoState *state, SoNode *node,
                         float);
  /**
  *  Sets the bevel radius as a percentage [0.0, 1.0]
  *  of the greater value of the length of each edge.
  */
  static void   setRadius(SoState *state, SoNode *node,
                          float = SoBevelProperty::DEFAULT_RADIUS);
  /**
  *  Sets the bevel radius as an absolute value.
  */
  static void   setAbsoluteRadius(SoState *state, SoNode *node,
                                  float);

  /**
  *  Allows the user to switch on/off the tests applied
  *  before the bevel (can increase speed when the tests are not needed).
  */
  static void   setTests(SoState *state, SoNode *node,
                         int);
  /**
  *  Allows the user to select the type of the output shapes (VRML or not).
  */
  static void   setVRMLOutput(SoState *state, SoNode *node,
                              SbBool);

  /**
  *  Returns the top (current) instance of the element in the state.
  */
  static const SoBevelPropertyElement * getInstance(SoState *state)
    {return getConstElement<SoBevelPropertyElement>(state);}

  /**
  *  Gets the bevel properties (angle).
  */
  float         getAngle() const                {return angle;}
  /**
  *  Gets the bevel properties (radius).
  */
  float         getRadius() const               {return radius;}
  /**
  *  Gets the bevel properties (absolute radius).
  */
 SbBool        isAbsoluteRadius() const        {return absoluteRadius;}
  /**
  *  Gets the bevel properties (enabled flag).
  */
 SbBool        isEnabled() const               {return propertyEnabled;}
  /**
  *  Method to know if this test is enabled. If it is, this
  *  test will be performed on each shape before the bevel.
  */
  SbBool        isCoplanarTestEnabled() const {return tests & SoBevelProperty::COPLANAR_TEST;}
  /**
  *  Method to know if this test is enabled. If it is, this
  *  test will be performed on each shape before the bevel.
  */
  SbBool        isDuplicateTestEnabled() const {return tests & SoBevelProperty::DUPLICATE_TEST;}
  /**
  *  Method to know if this test is enabled. If it is, this
  *  test will be performed on each shape before the bevel.
  */
  SbBool        isOrderingTestEnabled() const {return tests & SoBevelProperty::ORDERING_TEST;}
  /**
  *  Method to know the different tests currently selected;
  *  these tests will be performed on each shape before beveling is applied.
  */
  int           getTestsToDoBeforeBevel() const {return tests;}
  /**
  *  Gets the current selected type of the output shape (VRML or not).
  */
  SbBool        isOutputVRML() const { return vrmlOutput;}
  /**
  *  Prints element (for debugging).
  */
  virtual void  print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoBevelPropertyElement class
  static void           initClass();
  static void           exitClass();

  //Initializes element
  virtual void  init(SoState *state);

 protected:
  float         angle, radius;
  SbBool        absoluteRadius, propertyEnabled;
  int           tests;
  SbBool        vrmlOutput;

  virtual ~SoBevelPropertyElement();
};

#endif /* _SO_BEVEL_PROPERTY_ELEMENT */
