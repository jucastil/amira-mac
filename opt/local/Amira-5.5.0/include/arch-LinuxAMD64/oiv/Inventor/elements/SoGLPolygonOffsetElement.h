/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Feb 1998)
**=======================================================================*/

                                                             /* include files */
#ifndef  _SO_GL_POLYGON_OFFSET_ELEMENT_
#define  _SO_GL_POLYGON_OFFSET_ELEMENT_

#include <Inventor/sys/port.h>
#include <Inventor/elements/SoPolygonOffsetElement.h>

/**
* @VSGEXT Stores the current polygon offset in GL.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current polygon offset in GL.
*
*   @SEE_ALSO
*   SoPolygonOffsetElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLPolygonOffsetElement : public SoPolygonOffsetElement {
  SO_ELEMENT_HEADER(SoGLPolygonOffsetElement) ;

 public:
  /**
  *  Overrides push() method to remember previous element's state so
  *  we can sometimes generate more efficient GL calls.
  */
  virtual void push(SoState *state) ;

  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void pop(SoState *state, const SoElement *prevTopElement) ;

 SoINTERNAL public:
  // Initializes the SoGLPolygonOffsetElement class
  static void initClass() ;
  static void exitClass() ;

  // Initializes element
  virtual void init(SoState *state) ;

 protected:
  // Sets the polygon offset attributes in an instance. Has GL side effects.
  virtual void setElt(float factor, float units, Style styles, SbBool on) ;

  virtual ~SoGLPolygonOffsetElement() ;
  
 private:
  // We save the state to figure out if the hints were
  // copied from a parent element; if they were, then caches will have
  // to depend on that element because if it changes we have to have
  // a chance to change our decision about what GL calls to make.
  // If this is NULL, then there are no cache dependencies.
  SoState *copiedFromParent ;

  // Send polygon offset to GL
  void send() ;
} ;

#endif /* _SO_GL_POLYGON_OFFSET_ELEMENT_ */
