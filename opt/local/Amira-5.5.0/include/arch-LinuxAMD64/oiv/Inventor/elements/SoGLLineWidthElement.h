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


#ifndef  _SO_GL_LINE_WIDTH_ELEMENT
#define  _SO_GL_LINE_WIDTH_ELEMENT

#include <Inventor/elements/SoLineWidthElement.h>

/**
*  Stores the current line width in GL.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current line width in GL. Overrides the
*   virtual methods on SoLineWidthElement to send the line width to GL
*   when necessary.
* 
*   Note that this class relies on SoLineWidthElement to store the
*   width in the instance.
* 
*   @SEE_ALSO
*   SoLineWidthElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLLineWidthElement : public SoLineWidthElement {

  SO_ELEMENT_HEADER(SoGLLineWidthElement);

 public:
  /**
  *  Overrides push() method to copy state pointer and value of
  *  previous element, to avoid sending GL commands if the elements
  *  are the same.
  */
  virtual void        push(SoState *state);

  /**
  *  Overrides pop() method so side effects can occur in GL
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLLineWidthElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  // Sets the line width in an instance. Has GL side effects.
  virtual void        setElt(float width);

  virtual ~SoGLLineWidthElement();

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

  // Sends line width in element to GL
  void                send();

  // see SoPreferences OIV_LINE_WIDTH var
  static bool s_forceLineWidth;
};

#endif /* _SO_GL_LINE_WIDTH_ELEMENT */
