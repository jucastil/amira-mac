/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
** Modified by : M. Bonaventure (Mar 2010)
**=======================================================================*/
/*==============================================================================
 *   File        : MoDataBindingElement.h
 *   Classes     : MoDataBindingElement
 *   Author(s)   : Pascal Doux
 *   Date        : 8 9 2008
 *==============================================================================
 *
 * Description : Element that stores a data binding.
 *
 *============================================================================*/

#ifndef  _MO_DataBinding_ELEMENT_
#define  _MO_DataBinding_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>
#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>
#include <MeshVizInterface/mapping/nodes/MoDataBinding.h>

class MoDataBinding;

/**
* @DTEXT Stores the current data binding.
* 
* @ingroup MeshIViz_Mapping_Elements
*
* @DESCRIPTION
*   This element stores the current data binding.
* @SEE_ALSO
*   MoDataBinding
*/
class MESHIVIZDM_API MoDataBindingElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(MoDataBindingElement);
  
 public:
  
  /** Sets the current DataBinding */
  static void set(SoState *state, SoNode *node, MoDataBinding::DataBinding dataBinding);
  
  /** Returns the current DataBinding from the state */
  static const MoDataBinding::DataBinding getDataBinding(SoState *state);

  /**
  *  Returns TRUE if the geoOrigins match in both elements.
  */
  virtual SbBool matches(const SoElement *elt) const;

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;
  
 SoINTERNAL public:
  // Initializes the class
  static void initClass();
	static void exitClass() ;

  /** Initializes element */
  virtual void init(SoState *state);

  /**
  *  Create and return a copy of this element.
  */
  virtual SoElement *copyMatchInfo() const;
  
 protected:
  MoDataBinding::DataBinding  m_dataBinding;
  
  virtual ~MoDataBindingElement();
  
};
/*----------------------------------------------------------------------------*/

#endif // _MO_DataBinding_ELEMENT_
