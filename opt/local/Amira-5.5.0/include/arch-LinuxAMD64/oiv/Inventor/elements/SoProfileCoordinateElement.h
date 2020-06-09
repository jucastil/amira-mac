/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
** Modified by : Thad Beier (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/
 

#ifndef  _SO_PROFILE_COORDINATE_ELEMENT
#define  _SO_PROFILE_COORDINATE_ELEMENT

#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoReplacedElement.h>

/**
*   Stores the current profile coordinates.
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current profile coordinates, as either 2D or
*   3D points.
* 
*   This class allows read-only access to the top element in the state
*   to make accessing several values in it more efficient. Individual
*   values must be accessed through this instance.
* 
*   @SEE_ALSO
*   SoProfileCoordinate2, SoProfileCoordinate3
*/

SoEXTENDER_Documented class INVENTOR_API SoProfileCoordinateElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(SoProfileCoordinateElement);

 public:
  /**
   * Sets the current 2D profile coordinates.
   * [OIV-WRAPPER-ARG IN,IN,NO_WRAP{(coords != NULL? coords->Length: 0)},ARRAY]
   */
  static void         set2(SoState *state, SoNode *node,
                           int32_t numCoords, const SbVec2f *coords);
  /**
   * Sets the current 3D profile coordinates.
   * [OIV-WRAPPER-ARG IN,IN,NO_WRAP{(coords != NULL? coords->Length: 0)},ARRAY]
   */
  static void         set3(SoState *state, SoNode *node,
                           int32_t numCoords, const SbVec3f *coords);

  /**
  *  Returns the top (current) instance of the element in the state.
  */
  static const SoProfileCoordinateElement * getInstance(SoState *state);

  /**
  *  Returns the number of coordinate points in an instance.
  */
  int32_t             getNum() const          { return numCoords; }

  /**
  *  Returns the indexed coordinate from an element as a
  *  2D vector, converting if necessary.
  */
  const SbVec2f &     get2(int index) const;
  /**
  *  Returns the indexed coordinate from an element as a 
  *  3D vector, converting if necessary.
  */
  const SbVec3f &     get3(int index) const;

  /**
  *  Returns the array of SbVec2f without any conversion. 
  *  The pointer may be NULL if coordinates are specified as 3D vectors.
  */
  const SbVec2f *     getCoord2() const { return coords2 ; }
  
  /**
  *  Returns the array of SbVec3f without any conversion. 
  *  The pointer may be NULL if coordinates are specified as 2D vectors.
  */
  const SbVec3f *     getCoord3() const { return coords3 ; }

  /**
  *  TRUE if set2() was called.
  */
  SbBool              is2D() const  { return coordsAre2D; }

  /**
  *  Returns the default 2D profile coordinate.
  */
  static SbVec2f      getDefault2() { return SbVec2f(0.0, 0.0); }
  /**
  *  Returns the default 3D profile coordinate.
  */
  static SbVec3f      getDefault3() { return SbVec3f(0.0, 0.0, 1.0); }

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoCoordinateElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element.
  virtual void        init(SoState *state);

 protected:
  int32_t             numCoords;
  const SbVec2f       *coords2;
  const SbVec3f       *coords3;
  SbBool              coordsAre2D;

  virtual ~SoProfileCoordinateElement();

 private:
  static SbVec2f     *defaultCoord2;
  SbVec2f             convert2;       // To convert from 3-D to 2-D
  SbVec3f             convert3;       // To convert from 2-D to 3-D
};

#endif /* _SO_PROFILE_COORDINATE_ELEMENT */
