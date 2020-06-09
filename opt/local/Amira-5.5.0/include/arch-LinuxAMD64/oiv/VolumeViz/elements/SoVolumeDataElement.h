/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Feb 2000)
** Modified by : J. HUMMEL to collect multiple volume data node (Apr 2005)
**=======================================================================*/


#ifndef  _SO_VOLUME_DATA_ELEMENT_
#define  _SO_VOLUME_DATA_ELEMENT_

#include <LDM/elements/SoDataSetElement.h>
#include <VolumeViz/nodes/SoVolumeData.h>

//wrapper
class VOLUMEVIZ_API SoVolumeDataElement : public SoDataSetElement {

public:
  static void set(SoState* state, SoNode *node, SoVolumeData *volumeDataNode)
  {
    SoDataSetElement::set(state, node, (SoDataSet*)volumeDataNode);
  }

  static void set(SoState *state, SoNode *node,
                  SoVolumeData *volumeDataNode, const SbMatrix &matrix )
  {
    SoDataSetElement::set(state, node, (SoDataSet*)volumeDataNode, matrix);
  }

  static void get(SoState* state, std::vector<SoVolumeData*>& s)
  {
    std::vector<SoDataSet*> temp;
    SoDataSetElement::get(state, temp);
    for(unsigned int i = 0 ; i < temp.size() ; i++ ){
      s.push_back((SoVolumeData*)temp[i]);
    }
  }

  /** [OIVJAVA-WRAPPER NAME{getTileManager}] */
  static void get(SoState* state, SoLDMTileManager*& t)
  {
    SoDataSetElement::get(state, t);
  }

  /** [OIVJAVA-WRAPPER NAME{getVolumeData}] */
  static void get(SoState* state, SoVolumeData*& vd)
  {
    std::pair<SoVolumeData*, int> p = SoDataSetElement::getLastOfType<SoVolumeData>(state, true);
    vd = p.first;
  }

  static const SbMatrix &get(SoState *state, SoVolumeData*& v, SbBool &isIdent )
  {
    return SoDataSetElement::get(state, (SoDataSet*&)v, isIdent);
  }
};

#endif // _SO_VOLUME_DATA_ELEMENT_
