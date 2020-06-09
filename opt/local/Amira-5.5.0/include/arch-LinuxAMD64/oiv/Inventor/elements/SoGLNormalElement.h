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


#ifndef  _SO_GL_NORMAL_ELEMENT
#define  _SO_GL_NORMAL_ELEMENT

#include <Inventor/elements/SoNormalElement.h>

/**
*   Stores the current surface normals.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current surface normals. This class includes methods to
*   send the surface normal to GL on demand.
* 
*   Note that this class relies on SoNormalElement to store the
*   normals in the instance.
* 
*   @SEE_ALSO
*   SoNormalElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLNormalElement : public SoNormalElement {

  SO_ELEMENT_HEADER(SoGLNormalElement);

 public:
  /**
  *  Sends indexed normal to GL.
  */
  void                send(int index) const;

 SoINTERNAL public:
  // Initializes the SoGLNormalElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  virtual ~SoGLNormalElement();
};

#endif /* _SO_GL_NORMAL_ELEMENT */
