/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
/*==============================================================================
 *   File        : MoVec3SetElementIj.h
 *   Classes     : MoVec3SetElementIj
 *   Author(s)   : Pascal Doux
 *   Date        : 6 6 2008
 *==============================================================================
 *
 * Description : Element that stores a vector set Ij.
 *
 *============================================================================*/

#ifndef  _MO_VEC3SET_ELEMENTIJ_
#define  _MO_VEC3SET_ELEMENTIJ_

#include <Inventor/elements/SoAccumulatedElement.h>
#include <MeshVizInterface/mesh/data/MiDataSetIj.h>


/**
* @DTEXT Stores a list of vector3 sets for structured surface meshes.
* 
* @ingroup MeshIViz_Mapping_Elements
*/
class MESHIVIZDM_API MoVec3SetElementIj : public SoAccumulatedElement {

  SO_ELEMENT_HEADER(MoVec3SetElementIj);
  
 public:
  /**
  *  @copydoc MoScalarSetElementI::add()
  */
  static void add(SoState *state, SoNode *node,const MiVec3dSetIj *vec3Set);

  /**
  *  @copydoc MoScalarSetElementI::getNum()
  */
  static int getNum(SoState *state);

  /**
  *  @copydoc MoScalarSetElementI::get()
  */
  static const MiVec3dSetIj * get(SoState *state,int index);
  
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

  virtual ~MoVec3SetElementIj();
  
};
/*----------------------------------------------------------------------------*/

#endif // _MO_VECTORSET_ELEMENTIJK_
