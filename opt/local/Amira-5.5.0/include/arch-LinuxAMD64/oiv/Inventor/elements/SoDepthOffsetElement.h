/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Dec 2008)
**=======================================================================*/

#ifndef  SO_DEPTH_OFFSET_ELEMENT_H
#define  SO_DEPTH_OFFSET_ELEMENT_H

#include <Inventor/elements/SoFloatElement.h>

/**
 * @VSGEXT Manage SoDepthOffset nodes accumulation in state.
 * 
 * @ingroup elements
 * 
 *   @DESCRIPTION
 *   This element stores SoDepthOffset nodes encountered during traversal at
 *   any given time. Requesting for current offset at a given time
 *   (throught get() method) returns the global accumulated offset, computed
 *   from all previously SoDepthOffset nodes encountered in current path traversal.
 *
 */

SoEXTENDER_Documented class INVENTOR_API SoDepthOffsetElement : public SoFloatElement
{

  SO_ELEMENT_HEADER(SoDepthOffsetElement);
  
public:

  /** Sets the current offset in the state. */
  static void set(SoState *state, float offset);

#ifndef IV_STRICT
  /** Sets the current offset in the state. */
  static void set(SoState *state, SoNode *, float offset);
#endif

  /** Sets the current offset in the state. */
  static void set(SoState *state, float, float, float);

  /** Returns current accumulated offset from the state. */
  static float get(SoState *state);

  /** Sets the current offset in the state. */
  static void setMaxOffset(SoState *state, float offset);

  /** Returns current accumulated offset from the state. */
  static float getMaxOffset(SoState *state);

  /** Push the element into the state. */
  virtual void push( SoState* );

  /** Pop the element from the state. */
  virtual void pop(SoState*, const SoElement*);

SoINTERNAL public:
  // Initializes the class
  static void initClass();
	static void exitClass();
  virtual void init(SoState *state);

protected:
  virtual ~SoDepthOffsetElement();

  float maxOffset;
  float localdata;

};

#endif // SO_DEPTH_OFFSET_ELEMENT_H
