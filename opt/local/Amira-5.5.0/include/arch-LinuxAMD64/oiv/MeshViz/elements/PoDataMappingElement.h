/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Jan 1998)
**=======================================================================*/

                                                             /* include files */
#ifndef  _PO_DATA_MAPPING_ELEMENT_
#define  _PO_DATA_MAPPING_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>
#include <MeshViz/graph/PbLinearDataMapping.h>

class PbDataMapping;

/*----------------------------------------------------------------------------*/

class MESHVIZ_API PoDataMappingElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(PoDataMappingElement);
  
 public:
  // Initializes element
  virtual void init(SoState *state);
  
  // set the current dataMapping
  static void set(SoState *state, SoNode *node,
                  const PbDataMapping *dataMapping);
  
  // return the current data mapping from the state
  static const PbDataMapping *get(SoState *state);
  
 SoINTERNAL public:
  // Initializes the class
  static void initClass();
	static void exitClass() ;
  
 protected:
  PbDataMapping *m_dataMapping;
  
  virtual ~PoDataMappingElement();
};
/*----------------------------------------------------------------------------*/

#endif // _PO_DATA_MAPPING_ELEMENT_
