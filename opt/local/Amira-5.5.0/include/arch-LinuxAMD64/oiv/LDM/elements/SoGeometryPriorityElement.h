/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Jerome Hummel (Nov 2004)
**=======================================================================*/

  
#ifndef  _SO_WEIGHT_PROP_ELT_
#define  _SO_WEIGHT_PROP_ELT_

#include <Inventor/elements/SoReplacedElement.h>

#include <LDM/nodes/SoGeometryPriority.h>

class LDM_API SoGeometryPriorityElement : public SoReplacedElement {
  SO_ELEMENT_HEADER( SoGeometryPriorityElement );

public:
  // Initializes element
  virtual void init( SoState* state );
  // Sets/Gets the current volume data attributes in the state
  static void set(SoState* state, SoNode *node, SoGeometryPriority *m_geometryPriorityNode);
  static void get(SoState* state, SoGeometryPriority *&m_geometryPriorityNode);

  // Default values
  static void getDefault(SoGeometryPriority *&m_geometryPriorityNode);

  SoINTERNAL public:
  // Initializes the SoVolumeData class
  static void initClass();
  static void exitClass();

protected:
  SoGeometryPriority *m_geometryPriorityNode;

  virtual void setElt( SoGeometryPriority *m_geometryPriorityNode );

  virtual ~SoGeometryPriorityElement() ;
};

#endif // _SO_WEIGHT_PROP_ELT_
