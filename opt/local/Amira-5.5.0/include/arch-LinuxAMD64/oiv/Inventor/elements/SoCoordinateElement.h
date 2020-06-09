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


#ifndef  _SO_COORDINATE_ELEMENT
#define  _SO_COORDINATE_ELEMENT

#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoReplacedElement.h>


/**
*   Stores the current coordinates.
*
*   @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current coordinates. Coordinates may be
*   specified as 3-D or 4-D vectors. This element remembers the last
*   type of value stored.
*
*   This class allows read-only access to the top element in the state
*   to make accessing several values in it more efficient. Individual
*   values must be accessed through this instance.
*   @SEE_ALSO
*   SoCoordinate3, SoCoordinate4, SoProjection, SoVertexProperty
*/

SoEXTENDER_Documented class INVENTOR_API SoCoordinateElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(SoCoordinateElement);

 public:

  /**
   * Sets the current coordinates in the state as 3-vectors.
   * [OIV-WRAPPER-ARG IN,IN,NO_WRAP{(coords != NULL? coords->Length: 0)},ARRAY]
   */
  static void         set3(SoState *state, SoNode *node,
                           int32_t numCoords, const SbVec3f *coords);
  /**
   * Sets the current coordinates in the state as 4-vectors.
   * [OIV-WRAPPER-ARG IN,IN,NO_WRAP{(coords != NULL? coords->Length: 0)},ARRAY]
   */
  static void         set4(SoState *state, SoNode *node,
                           int32_t numCoords, const SbVec4f *coords);

  /**
  *  Returns the top (current) instance of the element in the state.
  */
  static const SoCoordinateElement * getInstance(SoState *state)
    {return getConstElement<SoCoordinateElement>(state);}

  /**
  *  Returns the number of coordinate points in an instance.
  */
  int32_t             getNum() const          { return numCoords; }

  /**
  *  Returns TRUE if the coordinates were specified as 3-vectors,
  *  FALSE if 4-vectors.
  */
  SbBool              is3D() const            { return coordsAre3D; }

  /**
  *  Returns the indexed coordinate from an element as a
  *  3-vector, converting if necessary. A returned reference may be
  *  invalid after the next call to this method or the get4() method.
  */
  const SbVec3f &     get3(int index) const;
  /**
  *  Returns the indexed coordinate from an element as a
  *  4-vector, converting if necessary. A returned reference may be
  *  invalid after the next call to this method or the get3() method.
  */
  const SbVec4f &     get4(int index) const;

  /**
  *  Returns the array of SbVec3f without any conversion.
  *  The pointer may be NULL if coordinates are specified as 4D vectors.
  */
  const SbVec3f *     getCoord3() const { return coords3 ; }

  /**
  *  Returns the array of SbVec4f without any conversion.
  *  The pointer may be NULL if coordinates are specified as 3D vectors.
  */
  const SbVec4f *     getCoord4() const { return coords4 ; }

  /**
  *  Returns the default 3-D coordinate.
  */
  static SbVec3f getDefault3()                { return SbVec3f(0, 0, 0); }
  /**
  *  Returns the default 4-D coordinate.
  */
  static SbVec4f getDefault4()                { return SbVec4f(0, 0, 0, 1); }

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoCoordinateElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

  // check if coord is a real user coord or the default3 value
  bool isEmpty() const;

 protected:
  int32_t             numCoords;
  const SbVec3f       *coords3;
  const SbVec4f       *coords4;
  SbBool              coordsAre3D;

  virtual ~SoCoordinateElement();

 private:
  // This stores a pointer to the default coordinates so that we can
  // set "coords3" to point to them if no other values have been set.
  static SbVec3f     *defaultCoord3;

  SbVec3f             convert3;       // To convert from 4-D to 3-D
  SbVec4f             convert4;       // To convert from 3-D to 4-D
};

#endif /* _SO_COORDINATE_ELEMENT */
