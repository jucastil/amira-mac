/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Mar 1999)
**=======================================================================*/

                                                             /* include files */
#ifndef  _PO_MESH1D_HINTS_ELEMENT_
#define  _PO_MESH1D_HINTS_ELEMENT_


#include <Inventor/elements/SoReplacedElement.h>
#include <MeshViz/nodes/PoMesh1DHints.h>


/*----------------------------------------------------------------------------*/

class MESHVIZ_API PoMesh1DHintsElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(PoMesh1DHintsElement);
  
 public:
  // Initializes element
  virtual void init(SoState *state);
  
  // Set the current mesh 1D hints attributes
  static void set(SoState *state, SoNode *node, 
                  PoMesh1DHints::GeomInterpretation geomInterpretation);
  
  // Return the current mesh 1D hints attributes from the state
  static PoMesh1DHints::GeomInterpretation get(SoState *state);
  
  // Default values
  static PoMesh1DHints::GeomInterpretation getDefault() 
    { return PoMesh1DHints::AS_IS; }
  
 SoINTERNAL public:
  // Initializes the class
  static void initClass();
	static void exitClass() ;
  
 protected:
  virtual ~PoMesh1DHintsElement();
  
 private:
  PoMesh1DHints::GeomInterpretation m_geomInterpretation;
};
/*----------------------------------------------------------------------------*/

#endif // _PO_MESH1D_HINTS_ELEMENT_
