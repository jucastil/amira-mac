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


#ifndef  _SO_GL_SHAPE_HINTS_ELEMENT
#define  _SO_GL_SHAPE_HINTS_ELEMENT

#include <Inventor/elements/SoShapeHintsElement.h>

/**
*   Stores current shape hints and sends commands to GL
*   based on them.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores current shape hints and sends commands to GL
*   based on them. All three hints must be set at the same time; to
*   leave any hint as is, use the "AS_IS" enum value.
*
*   @SEE_ALSO
*   SoShapeHintsElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLShapeHintsElement : public SoShapeHintsElement {

  SO_ELEMENT_HEADER(SoGLShapeHintsElement);

 public:
  /**
  *  Overrides push() method to remember previous element's state so
  *  we can sometimes generate more efficient GL calls.
  */
  virtual void        push(SoState *state);

  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLShapeHintsElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  // Override virtual sets to have GL side effects
  virtual void        setElt(SoState *state, VertexOrdering vertexOrdering,
                             ShapeType shapeType, FaceType faceType);

  // Note the "_" is required because windingType is a member variable in
  // our parent class (gives warning on some compilers).
  virtual void        setElt(SoState *state, WindingType _windingType) {
    SoShapeHintsElement::setElt(state, _windingType);
  };

  virtual ~SoGLShapeHintsElement();

 private:
  void setFixedPipelineShader(SoState *state);

  // We save the state to figure out if the hints were
  // copied from a parent element; if they were, then caches will have
  // to depend on that element because if it changes we have to have
  // a chance to change our decision about what GL calls to make.
  // If this is NULL, then there are no cache dependencies.
  SoState *           copiedFromParent;

  // Sends shape hints in element to GL
  void                send(SoState *state);
};

#endif /* _SO_GL_SHAPE_HINTS_ELEMENT */
