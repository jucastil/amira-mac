/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T. DUFOUR (Nov 2002)
**=======================================================================*/

  
#ifndef  _SO_VOLUME_GROUP_ELEMENT_
#define  _SO_VOLUME_GROUP_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>


#include <VolumeViz/nodes/SoVolumeGroup.h>

class VOLUMEVIZ_API SoVolumeGroupElement : public SoReplacedElement {
  SO_ELEMENT_HEADER( SoVolumeGroupElement );

public:
  // Initializes element
  virtual void init( SoState* state );
  // Sets/Gets the current volume data attributes in the state
  static void set(SoState* state, SoNode *node, SoVolumeGroup *VolumeGroupNode);
  static void get(SoState* state, SoVolumeGroup *&VolumeGroupNode);

  // Default values
  static void getDefault(SoVolumeGroup *&VolumeGroupNode);

  SoINTERNAL public:
  // Initializes the SoVolumeGroupElement class
  static void initClass();
  static void exitClass();

protected:
  SoVolumeGroup *m_VolumeGroupNode;

  virtual void setElt( SoVolumeGroup *VolumeGroupNode );

  virtual ~SoVolumeGroupElement() ;
};

#endif // _SO_VOLUME_GROUP_ELEMENT_
