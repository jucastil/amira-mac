/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thierry Dufour (May 2006)
**=======================================================================*/

  
#ifndef  _SOMESHPROPERTYELEMENT_H
#define  _SOMESHPROPERTYELEMENT_H

#include <LDM/elements/SoDataSetElement.h>
#include <ReservoirViz/nodes/SoMeshProperty.h>

//wrapper
/** [OIVNET-WRAPPER-CLASS MODULE{ReservoirViz}] */
class SoMeshPropertyElement : public SoDataSetElement {

public:

  static inline void set(SoState* state, SoNode *node, SoMeshProperty *propertyDataNode)
  {
    SoDataSetElement::set(state, node, (SoDataSet*)propertyDataNode);
  };

  static inline void set(SoState *state, SoNode *node,
                  SoMeshProperty *propertyDataNode, const SbMatrix &matrix )
  {
    SoDataSetElement::set(state, node, (SoDataSet*)propertyDataNode, matrix);
  };

  static inline void get(SoState* state, std::vector<SoMeshProperty*>& s)
  {
    std::vector<SoDataSet*> temp;
    SoDataSetElement::get(state, temp);
    for(unsigned int i = 0 ; i < temp.size() ; i++ ){
      s.push_back((SoMeshProperty*)temp[i]);
    }
  };

  /** [OIVJAVA-WRAPPER NAME{getTileManager}] */
  static inline void get(SoState* state, SoLDMTileManager*& t)
  {
    SoDataSetElement::get(state, t);
  };

  /** [OIVJAVA-WRAPPER NAME{getMeshProperty}] */
  static inline void get(SoState* state, SoMeshProperty*& vd)
  {
    SoDataSetElement::get(state, (SoDataSet*&)vd);
  };

  static inline const SbMatrix &get(SoState *state, SoMeshProperty*& v, SbBool &isIdent )
  {
    return SoDataSetElement::get(state, (SoDataSet*&)v, isIdent);
  };

};

#endif // _SOMESHPROPERTYELEMENT_H
