/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : B. GRANGE (Aug 2006)
**=======================================================================*/
  
#ifndef  _SO_VOLUME_CLIPPING_GROUP_ELEMENT_
#define  _SO_VOLUME_CLIPPING_GROUP_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>

class SoVolumeClippingGroup;

class VOLUMEVIZ_API SoVolumeClippingGroupElement : public SoReplacedElement {
  SO_ELEMENT_HEADER( SoVolumeClippingGroupElement );

public:
  // Initializes element
  virtual void init( SoState* state );
  // Sets/Gets the current volume data attributes in the state
  static void set(SoState* state, SoNode *node, SoVolumeClippingGroup *ClippingGroupNode);
  static void get(SoState* state, SoVolumeClippingGroup *&ClippingGroupNode);

  // Default values
  static void getDefault(SoVolumeClippingGroup *&ClippingGroupNode);

  SoINTERNAL public:
  // Initializes the SoVolumeClippingGroupElement class
  static void initClass();
  static void exitClass();

protected:
  SoVolumeClippingGroup *m_ClippingGroupNode;

  virtual void setElt( SoVolumeClippingGroup *ClippingGroupNode );

  virtual ~SoVolumeClippingGroupElement() ;
};

#endif // _SO_VOLUME_GROUP_ELEMENT_
