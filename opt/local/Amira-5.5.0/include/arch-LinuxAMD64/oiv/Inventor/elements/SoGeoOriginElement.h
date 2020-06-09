/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Julien SALLANNE (May 2009)
**=======================================================================*/

#ifndef  _SO_GEO_ORIGIN_ELEMENT
#define  _SO_GEO_ORIGIN_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoReplacedElement.h>

/**
* @VSGEXT Stores the current geoOrigin
* 
* @ingroup elements
* 
*   @DESCRIPTION
* 
*   @SEE_ALSO
*/

SoEXTENDER_Documented class INVENTOR_API SoGeoOriginElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(SoGeoOriginElement);

 public:
  /**
  *  Sets the current attributes.
  */
  static void set(SoState *state, SoNode *node, SbBool rotateYUp, const SbVec3f &geoOrigin);

  /**
  *  Returns the current attributes from the state.
  */
  static void get( SoState *state, SbBool &rotateYUp, SbVec3f &geoOrigin );

  /**
  *  Returns the default values.
  */
  static void getDefault( SbBool &rotateYUp, SbVec3f &geoOrigin );

  /**
  *  Create and return a copy of this element.
  */
  virtual SoElement *copyMatchInfo() const;

  /**
  *  Returns TRUE if the geoOrigins match in both elements.
  */
  virtual SbBool matches(const SoElement *elt) const;

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoGeoOriginElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  SbVec3f             geoOrigin;
  SbBool              rotateYUp;

  virtual ~SoGeoOriginElement();
};

#endif /* _SO_GEO_ORIGIN_ELEMENT */
