/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : JHUMMEL (Apr 2006)
**=======================================================================*/

  
#ifndef  _SOMESHGEOMETRYELEMENT_H
#define  _SOMESHGEOMETRYELEMENT_H

#include <LDM/elements/SoDataSetElement.h>
#include <ReservoirViz/nodes/SoMeshGeometry.h>

//wrapper
/** [OIVNET-WRAPPER-CLASS MODULE{ReservoirViz}] */
class SoMeshGeometryElement : public SoDataSetElement {

public:

  static inline void set(SoState* state, SoNode *node, SoMeshGeometry *meshDataNode)
  {
    SoDataSetElement::set(state, node, (SoDataSet*)meshDataNode);
  };

  static inline void set(SoState *state, SoNode *node,
                  SoMeshGeometry *meshDataNode, const SbMatrix &matrix )
  {
    SoDataSetElement::set(state, node, (SoDataSet*)meshDataNode, matrix);
  };

  static inline void get(SoState* state, std::vector<SoMeshGeometry*>& s)
  {
    std::vector<SoDataSet*> temp;
    SoDataSetElement::get(state, temp);
    for(unsigned int i = 0 ; i < temp.size() ; i++ ){
      s.push_back((SoMeshGeometry*)temp[i]);
    }
  };

  /** [OIVJAVA-WRAPPER NAME{getTileManager}] */
  static inline void get(SoState* state, SoLDMTileManager*& t)
  {
    SoDataSetElement::get(state, t);
  };

  /** [OIVJAVA-WRAPPER NAME{getMeshGeometry}] */
  static inline void get(SoState* state, SoMeshGeometry*& vd)
  {
    SoDataSetElement::get(state, (SoDataSet*&)vd);
  };

  static inline const SbMatrix &get(SoState *state, SoMeshGeometry*& v, SbBool &isIdent )
  {
    return SoDataSetElement::get(state, (SoDataSet*&)v, isIdent);
  };

};

#endif // _SOMESHGEOMETRYELEMENT_H
