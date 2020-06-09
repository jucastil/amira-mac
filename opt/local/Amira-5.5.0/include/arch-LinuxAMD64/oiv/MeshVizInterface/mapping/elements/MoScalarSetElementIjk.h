/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
/*==============================================================================
 *   File        : MoScalarSetElementIjk.h
 *   Classes     : MoScalarSetElementIjk
 *   Author(s)   : Pascal Doux
 *   Date        : 6 6 2008
 *==============================================================================
 *
 * Description : Element that stores a scalar set Ijk.
 *
 *============================================================================*/

#ifndef  _MO_SCALARSET_ELEMENTIJK_
#define  _MO_SCALARSET_ELEMENTIJK_

#include <Inventor/elements/SoAccumulatedElement.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>


/**
* @DTEXT Stores a list of scalar sets for structured volume meshes.
* 
* @ingroup MeshIViz_Mapping_Elements
*
* @DESCRIPTION
*   This element stores a list of structured volume scalar data sets.
* @SEE_ALSO
*   MoScalarSetIjk
*/
class MESHIVIZDM_API MoScalarSetElementIjk : public SoAccumulatedElement {

  SO_ELEMENT_HEADER(MoScalarSetElementIjk);
  
 public:
  /**
  *  @copydoc MoScalarSetElementI::add()
  */
  static void add(SoState *state, SoNode *node,const MiScalardSetIjk *scalarSet);

  /**
  *  @copydoc MoScalarSetElementI::getNum()
  */
  static int getNum(SoState *state);

  /**
  *  @copydoc MoScalarSetElementI::get()
  */
  static const MiScalardSetIjk * get(SoState *state,int index);

  /**
  *  @copydoc MoScalarSetElementI::push()
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

  virtual ~MoScalarSetElementIjk();
  
};
/*----------------------------------------------------------------------------*/

#endif // _MO_SCALARSET_ELEMENT_
