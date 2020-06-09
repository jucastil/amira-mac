/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Dec 1997)
**=======================================================================*/

                                                             /* include files */
#ifndef  _PO_DATE_FORMAT_MAPPING_ELEMENT_
#define  _PO_DATE_FORMAT_MAPPING_ELEMENT_


#include <Inventor/elements/SoReplacedElement.h>


class PbDateFormatMapping;

/*----------------------------------------------------------------------------*/

class MESHVIZ_API PoDateFormatMappingElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(PoDateFormatMappingElement);
  
 public:
  // Initializes element
  virtual void init(SoState *state);
  
  // set the current DateFormatMapping
  static void set(SoState *state, SoNode *node,
                  const PbDateFormatMapping *dateFormatMapping);
  
  // return the current DateFormatMapping from the state
  static const PbDateFormatMapping *get(SoState *state);
  
 SoINTERNAL public:
  // Initializes the class
  static void initClass();
	static void exitClass() ;
  
 protected:
  static PbDateFormatMapping *m_defaultDateFormatMapping;
  PbDateFormatMapping *m_dateFormatMapping;
  
  virtual ~PoDateFormatMappingElement();
};
/*----------------------------------------------------------------------------*/

#endif // _PO_DATE_FORMAT_MAPPING_ELEMENT_
