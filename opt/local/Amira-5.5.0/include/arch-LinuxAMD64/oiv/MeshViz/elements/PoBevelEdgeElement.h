/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Mar 1999)
**=======================================================================*/

                                                             /* include files */
#ifndef  _PO_BEVEL_EDGE_ELEMENT_
#define  _PO_BEVEL_EDGE_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>

#include <MeshViz/nodes/PoBevelEdge.h>

/*----------------------------------------------------------------------------*/

class MESHVIZ_API PoBevelEdgeElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(PoBevelEdgeElement);
  
 public:
  // Initializes element
  virtual void init(SoState *state);
  
  // Set the current beveled edge attributes
  static void set(SoState *state, SoNode *node, SbBool on, float radius,
                  PoBevelEdge::RadiusFlag radiusFlag, float bevelAngle);
  
  // Return the current beveled edge attributes from the state
  static void get(SoState *state, SbBool &on, float &radius,
                  PoBevelEdge::RadiusFlag &radiusFlag, float &bevelAngle);
  
  // Default values
  static void getDefault(SbBool &on, float &radius, 
                         PoBevelEdge::RadiusFlag &radiusFlag, 
                         float &bevelAngle);
  
 SoINTERNAL public:
  // Initializes the class
  static void initClass();
	static void exitClass() ;
  
 protected:
  virtual ~PoBevelEdgeElement();
  
 private:
  SbBool m_on;
  float m_radius, m_bevelAngle;
  PoBevelEdge::RadiusFlag m_radiusFlag;
};
/*----------------------------------------------------------------------------*/

#endif // _PO_BEVEL_EDGE_ELEMENT_
