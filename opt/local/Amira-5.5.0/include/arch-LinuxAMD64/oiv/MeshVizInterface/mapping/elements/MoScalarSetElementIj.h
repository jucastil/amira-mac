/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
/*==============================================================================
 *   File        : MoScalarSetElementIj.h
 *   Classes     : MoScalarSetElementIj
 *   Author(s)   : Pascal Doux
 *   Date        : 6 6 2008
 *==============================================================================
 *
 * Description : Element that stores a scalar set Ij.
 *
 *============================================================================*/

#ifndef  _MO_SCALARSET_ELEMENTIJ_
#define  _MO_SCALARSET_ELEMENTIJ_

#include <Inventor/elements/SoAccumulatedElement.h>
#include <MeshVizInterface/mesh/data/MiDataSetIj.h>


/**
* @DTEXT Stores a list of scalar sets for structured surface meshes.
* 
* @ingroup MeshIViz_Mapping_Elements
*
* @DESCRIPTION
*   This element stores a list of structured surface scalar data sets.
* @SEE_ALSO
*   MoScalarSetIj
*/
class MESHIVIZDM_API MoScalarSetElementIj : public SoAccumulatedElement {

  SO_ELEMENT_HEADER(MoScalarSetElementIj);
  
 public:
  /**
  *  @copydoc MoScalarSetElementI::add()
  */
  static void add(SoState *state, SoNode *node,const MiScalardSetIj *scalarSet);

  /**
  *  @copydoc MoScalarSetElementI::getNum()
  */
  static int getNum(SoState *state);

  /**
  *  @copydoc MoScalarSetElementI::get()
  */
  static const MiScalardSetIj * get(SoState *state,int index);
  
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

  virtual ~MoScalarSetElementIj();
  
};
/*----------------------------------------------------------------------------*/

#endif // _MO_SCALARSET_ELEMENT_
