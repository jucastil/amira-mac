/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Dec 1997)
**=======================================================================*/

                                                             /* include files */
#ifndef  _PO_MISC_TEXT_ATTR_ELEMENT_
#define  _PO_MISC_TEXT_ATTR_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>

class PbMiscTextAttr;

/*----------------------------------------------------------------------------*/

class MESHVIZ_API PoMiscTextAttrElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(PoMiscTextAttrElement);
  
 public:
  // Initializes element
  virtual void init(SoState *state);
  
  // set the current MiscTextAttr
  static void set(SoState *state, SoNode *node,
                  const PbMiscTextAttr *miscTextAttr);
  
  // return the current MiscTextAttr from the state
  static const PbMiscTextAttr *get(SoState *state);
  
 SoINTERNAL public:
  // Initializes the class
  static void initClass();
	static void exitClass() ;
  
 protected:
  static PbMiscTextAttr *m_defaultMiscTextAttr;
  PbMiscTextAttr *m_miscTextAttr;
  
  virtual ~PoMiscTextAttrElement();
};
/*----------------------------------------------------------------------------*/

#endif // _PO_MISC_TEXT_ATTR_ELEMENT_
