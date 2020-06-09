/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
/*==============================================================================
 *   File        : MoVec3SetElementIjk.h
 *   Classes     : MoVec3SetElementIjk
 *   Author(s)   : Pascal Doux
 *   Date        : 6 6 2008
 *==============================================================================
 *
 * Description : Element that stores a vector set Ijk.
 *
 *============================================================================*/

#ifndef  _MO_VECTORSET_ELEMENTIJK_
#define  _MO_VECTORSET_ELEMENTIJK_

#include <Inventor/elements/SoAccumulatedElement.h>
#include <MeshVizInterface/mesh/data/MiDataSetIjk.h>


/**
* @DTEXT Stores a list of vector3 sets for structured volume meshes.
* 
* @ingroup MeshIViz_Mapping_Elements
*/
class MESHIVIZDM_API MoVec3SetElementIjk : public SoAccumulatedElement {

  SO_ELEMENT_HEADER(MoVec3SetElementIjk);
  
 public:
  /**
  *  @copydoc MoScalarSetElementI::add()
  */
  static void add(SoState *state, SoNode *node,const MiVec3dSetIjk *vectorSet);

  /**
  *  @copydoc MoScalarSetElementI::getNum()
  */
  static int getNum(SoState *state);

  /**
  *  @copydoc MoScalarSetElementI::get()
  */
  static const MiVec3dSetIjk * get(SoState *state,int index);
  
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
  
  SbPList m_vectorSets;   // List of vector sets 

  virtual ~MoVec3SetElementIjk();
  
};
/*----------------------------------------------------------------------------*/

#endif // _MO_VECTORSET_ELEMENTIJK_
