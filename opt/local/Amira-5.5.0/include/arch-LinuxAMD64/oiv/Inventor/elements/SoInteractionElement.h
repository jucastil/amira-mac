/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef SO_INTERACTION_ELEMENT_H
#define SO_INTERACTION_ELEMENT_H

#include <Inventor/elements/SoInt32Element.h>

/**
 *   @VSGEXT Stores the current interaction state.
 *
 * @ingroup elements
 *
 *   @DESCRIPTION
 *   This element stores the current interaction state.
 *
 * @SEE_ALSO
 *  SoWinRenderArea, SoXtRenderArea, SoQtRenderArea
 */

SoEXTENDER_Documented class INVENTOR_API SoInteractionElement : public SoElement
{
  SO_ELEMENT_HEADER(SoInteractionElement);

public:
  /**
   *  Sets the current interaction in the state.
   */
  static void set(SoState *state, bool moving);

  /**
   *  Returns TRUE if a user interaction with the viewer
   *  is in progress.
   */
  static bool isInteracting(SoState *state);

  /**
   * Return number of frames since last interaction flag change
   */
  static uint32_t getElapsedFrames(SoState* state);

  /**
   * Return number of seconds since last interaction flag change
   */
  static double getElapsedSeconds(SoState* state);

  /**
   *  Common initialization
   */
  virtual void commonInit() ;

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual SbBool matches(const SoElement *elt) const;
  virtual SoElement* copyMatchInfo() const;

protected:
  void setElt(SoState *state, bool moving);

  virtual ~SoInteractionElement();

  struct
  {
    /** [OIV-WRAPPER-NO-WRAP] */
    bool interacting;
    /** [OIV-WRAPPER-NO-WRAP] */
    uint32_t numFrames;
    /** [OIV-WRAPPER-NO-WRAP] */
    double startTime;
    /** [OIV-WRAPPER-NO-WRAP] */
  } m_interactionInfos;
};

#endif // SO_INTERACTION_ELEMENT_H
