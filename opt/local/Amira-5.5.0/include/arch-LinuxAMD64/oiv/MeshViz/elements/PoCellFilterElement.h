/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : JM Godinaud (Sep 2003)
**=======================================================================*/

                                                             /* include files */
#ifndef  _PO_CELL_FILTER_ELEMENT_
#define  _PO_CELL_FILTER_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>
#include <MeshViz/nodes/PoCellFilter.h>

/*----------------------------------------------------------------------------*/

class MESHVIZ_API PoCellFilterElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(PoCellFilterElement);
  
 public:
  // Initializes element
  virtual void init(SoState *state);
  
  // set the current cell filter
  static void set(SoState *state, SoNode *cellFilter);
  
  // return the current cell filter from the state
  static const PoCellFilter* get(SoState *state);
  
 SoINTERNAL public:
  // Initializes the class
  static void initClass();
	static void exitClass() ;
  
 protected:
  const PoCellFilter *m_cellFilter;
  
  virtual ~PoCellFilterElement();
};
/*----------------------------------------------------------------------------*/

#endif // _PO_CELL_FILTER_ELEMENT_
