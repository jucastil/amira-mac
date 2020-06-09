/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Oct 1997)
**=======================================================================*/

                                                             /* include files */
#ifndef  _PO_DOMAIN_ELEMENT_
#define  _PO_DOMAIN_ELEMENT_


#include <Inventor/elements/SoReplacedElement.h>


class PbDomain;

/*----------------------------------------------------------------------------*/

class MESHVIZ_API PoDomainElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(PoDomainElement);
  
 public:
  // Initializes element
  virtual void init(SoState *state);
  
  // Set the current domain
  static void  set(SoState *state, SoNode *node, const PbDomain *domain);
  
  // Return the current domain from the state
  static const PbDomain *get(SoState *state);
  
 SoINTERNAL public:
  // Initializes the class
  static void initClass();
	static void exitClass() ;
  
 protected:
  static PbDomain *m_defaultDomain;
  PbDomain *m_domain;
  
  virtual ~PoDomainElement();
};
/*----------------------------------------------------------------------------*/

#endif // _PO_DOMAIN_ELEMENT_
