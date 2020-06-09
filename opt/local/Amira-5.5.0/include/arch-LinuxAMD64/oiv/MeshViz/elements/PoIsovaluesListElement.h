/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Dec 1997)
**=======================================================================*/

                                                             /* include files */
#ifndef  _PO_ISOVALUES_LIST_ELEMENT_
#define  _PO_ISOVALUES_LIST_ELEMENT_


#include <Inventor/elements/SoReplacedElement.h>


class PbIsovaluesList;

/*----------------------------------------------------------------------------*/

class MESHVIZ_API PoIsovaluesListElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(PoIsovaluesListElement);
  
 public:
  // Initializes element
  virtual void init(SoState *state);
  
  // Set the current IsovaluesList
  static void set(SoState *state, SoNode *node,
                  const PbIsovaluesList *isovaluesList);
  
  // Return the current IsovaluesList from the state
  static const PbIsovaluesList *get(SoState *state);
  
 SoINTERNAL public:
  // Initializes the class
  static void initClass();
	static void exitClass() ;
  
 protected:
  PbIsovaluesList *m_isovaluesList;
  
  virtual ~PoIsovaluesListElement();
};
/*----------------------------------------------------------------------------*/

#endif // _PO_ISOVALUES_LIST_ELEMENT_
