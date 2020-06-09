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


#ifndef  _SO_VIEWING_MATRIX_ELEMENT
#define  _SO_VIEWING_MATRIX_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoReplacedElement.h>

/**
*   Stores the current viewing matrix.
* 
*   @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current viewing matrix - the
*   non-projection part of the matrix set up by the camera. Because
*   most operations on this matrix are atomic, it is considered a
*   non-accumulating element.
* 
*   @SEE_ALSO
*   SoCamera, SoOrthographicCamera, SoPerspectiveCamera
*/

SoEXTENDER_Documented class INVENTOR_API SoViewingMatrixElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(SoViewingMatrixElement);

 public:
  /**
  *  Sets the view matrix to the given matrix.
  *  This method will (indirectly) call glLoadMatrix with the
  *  new matrix unless the 'sendToGL' parameter is explicitly FALSE.
  */
  static void         set(SoState *state, SoNode *node,
                          const SbMatrix &matrix, SbBool sendToGL = TRUE);

  /**
  *  Returns current matrix from the state.
  */
  static const SbMatrix &     get(SoState *state);

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoViewingMatrixElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  SbMatrix            viewingMatrix;

  // Sets the matrix in an instance
  virtual void        setElt(const SbMatrix &matrix, SbBool sendToGL = TRUE);

  virtual ~SoViewingMatrixElement();
};

#endif /* _SO_VIEWING_MATRIX_ELEMENT */
