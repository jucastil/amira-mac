/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Jan 1999)
**=======================================================================*/

                                                             /* include files */
#ifndef  _PO_MESH1D_FILTER_ELEMENT_
#define  _PO_MESH1D_FILTER_ELEMENT_


#include <Inventor/elements/SoReplacedElement.h>


class PoMesh1DFilter;

/*----------------------------------------------------------------------------*/

class MESHVIZ_API PoMesh1DFilterElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(PoMesh1DFilterElement);
  
 public:
  // Initializes element
  virtual void init(SoState *state);
  
  // Set the current mesh 1D filter node
  static void  set(SoState *state, SoNode *node, const PoMesh1DFilter *filter);
  
  // Return the current mesh 1D filter node from the state
  static const PoMesh1DFilter *get(SoState *state);
  
  // Default values
  static PoMesh1DFilter *getDefault() 
    { return NULL; }
  
 SoINTERNAL public:
  // Initializes the class
  static void initClass();
	static void exitClass() ;
  
 protected:
  virtual ~PoMesh1DFilterElement();
  
 private:
  PoMesh1DFilter *m_mesh1DFilter;
};
/*----------------------------------------------------------------------------*/

#endif // _PO_MESH1D_FILTER_ELEMENT_
