/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
/*==============================================================================
 *   File        : MoVec3SetElementI.h
 *   Classes     : MoVec3SetElementI
 *   Author(s)   : Pascal Doux
 *   Date        : 6 6 2008
 *==============================================================================
 *
 * Description : Element that stores a vector set.
 *
 *============================================================================*/

#ifndef  _MO_VEC3SET_ELEMENTI_
#define  _MO_VEC3SET_ELEMENTI_

#include <Inventor/elements/SoAccumulatedElement.h>
#include <MeshVizInterface/mesh/data/MiDataSetI.h>


/**
* @DTEXT Stores a list of vector3 sets for unstructured meshes.
* 
* @ingroup MeshIViz_Mapping_Elements
*/
class MESHIVIZDM_API MoVec3SetElementI : public SoAccumulatedElement {

  SO_ELEMENT_HEADER(MoVec3SetElementI);
  
 public:
  /**
  *  @copydoc MoScalarSetElementI::add()
  */
  static void add(SoState *state, SoNode *node,const MiVec3dSetI *scalarSet);

  /**
  *  @copydoc MoScalarSetElementI::getNum()
  */
  static int getNum(SoState *state);

  /**
  *  @copydoc MoScalarSetElementI::get()
  */
  static const MiVec3dSetI * get(SoState *state,int index);
  
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

  virtual ~MoVec3SetElementI();
  
};
/*----------------------------------------------------------------------------*/

#endif // _MO_VEC3SET_ELEMENTI_
