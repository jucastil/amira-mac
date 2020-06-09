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


#ifndef  _SO_GL_POINT_SIZE_ELEMENT
#define  _SO_GL_POINT_SIZE_ELEMENT

#include <Inventor/elements/SoPointSizeElement.h>

/**
*  Stores the current point size in GL.
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current point size in GL. Overrides the
*   virtual methods on SoPointSizeElement to send the point size to GL
*   when necessary.
* 
*   Note that this class relies on SoPointSizeElement to store the
*   size in the instance.
* 
*   @SEE_ALSO
*   SoPointSizeElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLPointSizeElement : public SoPointSizeElement {

  SO_ELEMENT_HEADER(SoGLPointSizeElement);

 public:
  /**
  *  Overrides push() method to copy state pointer and value of
  *  previous element, to avoid sending GL commands if the elements
  *  are the same.
  */
  virtual void        push(SoState *state);

  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLPointSizeElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  // Sets the point size in an instance. Has GL side effects.
  virtual void        setElt(float size);

  virtual ~SoGLPointSizeElement();

 private:
  // This variable is TRUE if the value in this element was copied
  // from our parent.  If set is called with the same value, no GL
  // commands have to be done-- it is as if this element doesn't
  // exist, and the parent's value is used.  Of course, a cache
  // dependency will have to be added in this case (if the parent
  // changes, the cache is not valid).  Set sets this flag to false.
  SbBool              copiedFromParent;

  // We need to store the state so we can get the viewport region element
  SoState             *state;

  // Sends point size in element to GL
  void                send();
};

#endif /* _SO_GL_POINT_SIZE_ELEMENT */
