/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (Apr 2009)
**=======================================================================*/

#ifndef _SO_DEPTH_BUFFER_ELEMENT_
#define _SO_DEPTH_BUFFER_ELEMENT_

#include <Inventor/SbBasic.h>
#include <Inventor/SbVec.h>
#include <Inventor/elements/SoSubElement.h>

class SoDepthBuffer;

/**
 * @VSGEXT Stores the current depth buffer parameters.
 *
 * @ingroup elements
 *
 * @DESCRIPTION
 * This element stores the current depth buffer parameters used for rendering,
 * including:
 * - Depth buffer test enabled,
 * - Depth buffer writing enabled,
 * - Depth buffer range, and
 * - Depth comparison function.
 *
 * @SEE_ALSO
 *   SoDepthBuffer
 */
class INVENTOR_API SoDepthBufferElement : public SoElement
{
  SO_ELEMENT_HEADER(SoDepthBufferElement);

public:
  /**
   * Depth function mode as defined by OpenGL.
   */
  enum DepthWriteFunction {
    /** Never passes. */
    NEVER,
    /** Passes if the	incoming depth value is	less than the stored depth value. */
    LESS,
    /** Passes if the	incoming depth value is	equal to the stored depth value. */
    EQUAL,
    /** Passes if the	incoming depth value is	less than or equal	to the stored depth value. */
    LEQUAL,
    /** Passes if the	incoming depth value is greater than the stored depth	value. */
    GREATER,
    /** Passes if the	incoming depth value is	not equal	to the stored depth value. */
    NOTEQUAL,
    /** Passes if the	incoming depth value is greater than or equal	to the stored depth value. */
    GEQUAL,
    /** Always passes. */
    ALWAYS
  };

  /**
  * Sets the depth buffer parameters.
  * This method will (indirectly) call glDepthMask, glDepthFunc, glDepthRange
  * with the new values
  */
  static void set(SoState* state, const SbBool test, const SbBool write, const DepthWriteFunction function, const SbVec2f range);

  /**
  * Sets the depth buffer parameters.
  * This method will (indirectly) call glDepthMask, glDepthFunc, glDepthRange
  * with the new values
  */
  static void set(SoState* state, SoDepthBuffer* depthBuffer,  const SbBool test, const SbBool write, const DepthWriteFunction function, const SbVec2f range);

  /**
  *  Returns current depth buffer parameters.
  */
  static void get(SoState* state, SbBool& test, SbBool& write, DepthWriteFunction& function, SbVec2f& range);

  /**
  *  Returns TRUE if depth parameters match.
  */
  virtual SbBool matches(const SoElement *elt) const;

  /**
  *  Create and return a copy of this element.
  */
  virtual SoElement* copyMatchInfo() const;

  /**
  *  Prints element (for debugging).
  */
  virtual void print(FILE *fp) const;

  /**
  *  Override push() method to keep GL up to date.
  */
  virtual void push(SoState *state);

  /**
  *  Override pop() method to keep GL up to date.
  */
  virtual void pop(SoState *state, const SoElement *prevTopElement);

SoINTERNAL public:

  /** register in database. */
  static void initClass();

  /** unregister from database. */
  static void exitClass();

  /** Initializes element. */
  virtual void init(SoState *state);

  /** depth test enable accessor */
  static SbBool getTestEnable(SoState * state);

  /** write enable accessor */
  static SbBool getWriteEnable(SoState * state);

  /** function accessor */
  static DepthWriteFunction getFunction(SoState * state);

  /** range accessor */
  static SbVec2f getRange(SoState * state);

  /** dethbuffer accessor */
  static SoDepthBuffer* getDepthBuffer(SoState * state);

protected:

  /** Destructor */
  virtual ~SoDepthBufferElement();

  /**
   * Sets the depth buffer parameter in an instance. Has GL side effects.
   * This method will enable or not GL_DEPTH_TEST mode and call glDepthRange/glDepthMask
   * with the new values.
   */
  virtual void setElt(SoDepthBuffer* depthBuffer, const SbBool enable, const SbBool write, const DepthWriteFunction function, const SbVec2f range);

protected:
  /** depth test is enable or not */
  SbBool test;
  /** depth write is enbale or not */
  SbBool write;
  /** write mode functions */
  DepthWriteFunction function;
  /** current depth range */
  SbVec2f range;

  /** current depth buffer */
  SoDepthBuffer* m_depthBuffer;
};

#endif /* _SO_DEPTH_BUFFER_ELEMENT_ */
