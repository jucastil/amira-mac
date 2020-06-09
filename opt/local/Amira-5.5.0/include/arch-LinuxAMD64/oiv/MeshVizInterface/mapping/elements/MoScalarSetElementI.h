/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
/*==============================================================================
 *   File        : MoScalarSetElementI.h
 *   Classes     : MoScalarSetElementI
 *   Author(s)   : Pascal Doux
 *   Date        : 6 6 2008
 *==============================================================================
 *
 * Description : Element that stores a scalar set I.
 *
 *============================================================================*/

#ifndef  _MO_SCALARSET_ELEMENT_
#define  _MO_SCALARSET_ELEMENT_

#include <Inventor/elements/SoAccumulatedElement.h>
#include <MeshVizInterface/mesh/data/MiDataSetI.h>


/**
* @DTEXT Stores a list of scalar sets for unstructured meshes.
* 
* @ingroup MeshIViz_Mapping_Elements
*  
* @DESCRIPTION
*   This element stores a list of unstructured scalar data sets.
* @SEE_ALSO
*   MoScalarSetI
*/
class MESHIVIZDM_API MoScalarSetElementI : public SoAccumulatedElement {

  SO_ELEMENT_HEADER(MoScalarSetElementI);
  
 public:
  /**
  *  Adds a ScalarSet to the current set in the state.
  */
  static void add(SoState *state, SoNode *node,const MiScalardSetI *scalarSet);

  /**
  *  Get number of elements in the state.
  */
  static int getNum(SoState *state);

  /**
  *  Get the element number index from the state.
  */
  static const MiScalardSetI * get(SoState *state,int index);
  
  /**
  *  Push the element into the state.
  */
  virtual void push(SoState *);

SoINTERNAL public:
  // Initializes the class
  static void initClass();
	static void exitClass() ;

  /** Initializes element */
  virtual void init(SoState *state);
  

 protected:
  
  SbPList m_scalarSets;   // List of scalar sets 

  virtual ~MoScalarSetElementI();
  
};
/*----------------------------------------------------------------------------*/

#endif // _MO_SCALARSET_ELEMENT_
