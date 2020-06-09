/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Rodolphe Albou (Dec 2006)
**=======================================================================*/


 
#ifndef  _SO_TIME_HINTS_ELT_
#define  _SO_TIME_HINTS_ELT_

#include <Inventor/elements/SoReplacedElement.h>

#include <LDM/nodes/SoTimeHints.h>

//------------------------------------------------------------------------------

class LDM_API SoTimeHintsElement : public SoReplacedElement {

  SO_ELEMENT_HEADER( SoTimeHintsElement );

public:
  // Initializes element
  virtual void init( SoState* state );

  // Sets/Gets the current time hints attributes in the state
  static void set(SoState* state, SoNode *node, SoTimeHints *timeHintsNode);
  static void get(SoState* state, SoTimeHints *&timeHintsNode);

  // Default values
  static void getDefault(SoTimeHints *&timeHintsNode);

  SoINTERNAL public:
  // Initializes the SoVolumeData class
  static void initClass();
  static void exitClass();

protected:
  SoTimeHints *m_timeHintsNode;

  virtual void setElt( SoTimeHints *timeHintsNode );

  virtual ~SoTimeHintsElement() ;
};

#endif // _SO_TIME_HINTS_ELT_
