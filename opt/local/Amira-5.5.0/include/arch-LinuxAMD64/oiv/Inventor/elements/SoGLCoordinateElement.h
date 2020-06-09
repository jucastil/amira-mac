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


#ifndef  _SO_GL_COORDINATE_ELEMENT
#define  _SO_GL_COORDINATE_ELEMENT

#include <Inventor/elements/SoCoordinateElement.h>

/**
*  Stores the current coordinates.
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current coordinates. Adds methods to
*   send the surface coordinate to GL on demand. The coordinates are
*   sent in the appropriate form, depending on whether they are stored
*   as 3-D or 4-D values.
* 
*   Note that this class relies on SoCoordinateElement to store the
*   coordinates in the instance.
* 
*   @SEE_ALSO
*   SoCoordinateElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLCoordinateElement : public SoCoordinateElement {

  SO_ELEMENT_HEADER(SoGLCoordinateElement);

 public:
  /**
  *  Sends indexed coordinate to GL.
  */
  void                send(int index) const;

 SoINTERNAL public:
  // Initializes the SoGLCoordinateElement class
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoGLCoordinateElement();
};

#endif /* _SO_GL_COORDINATE_ELEMENT */
