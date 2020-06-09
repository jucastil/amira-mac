/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (May 2007)
**=======================================================================*/

#ifndef  _SO_PROJECTION_ELEMENT
#define  _SO_PROJECTION_ELEMENT

#include <Inventor/elements/SoElement.h>

#include <Inventor/misc/SoState.h>
#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/errors/SoDebugError.h>

class SbProjection;
class SoProjection;

/**
 * @VSGEXT Store current projection node.
 * 
 * @ingroup Element
 * 
 * @DESCRIPTION
 * 
 *  This element stores the current projection node. 
 *
 * @SEE_ALSO
 *   SoProjection
 * 
 * 
 */
SoEXTENDER class INVENTOR_API SoProjectionElement :public SoReplacedElement
{

  SO_ELEMENT_HEADER( SoProjectionElement );

public:

  /**
  *  Sets the current projection node in the state
  */
  static void set( SoState *state, SoProjection *prj );

  /**
  *  Sets the current projection node in the state
  */
  static void set( SoState *state, SoNode *, SoProjection *prj );

  /**
  *  Returns the current projection node from the state
  */
  static SoProjection *get( SoState *state );

  /**
  *  Returns TRUE if the projection are the same in both elements.
  */
  virtual SbBool      matches(const SoElement *elt) const;

  /**
  *  Create and return a copy of this element.
  */
  virtual SoElement   *copyMatchInfo() const;

  /**
  *  Returns the projection routine associated with current SoProjection node
  */
  static SbProjection *getInternalProjection( SoState *state );

  SoINTERNAL public:

  // Initializes element.
  virtual void init( SoState *state );
  // Initialize element : called by constructor.
  virtual void commonInit();

  // Initializes the SoProjectionElement class
  static void initClass();
  static void exitClass();

protected:

  virtual void setProjection( SoProjection *projection ){m_projection = projection;}

  // projection node
  SoProjection *m_projection;

  virtual ~SoProjectionElement();
};

#endif 
