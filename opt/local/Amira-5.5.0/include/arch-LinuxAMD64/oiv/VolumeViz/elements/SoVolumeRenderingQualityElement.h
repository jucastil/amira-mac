/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : B. GRANGE (MMM yyyy)
**=======================================================================*/

#ifndef  _SO_VOLUME_RENDERING_QUALITY_ELEMENT_
#define  _SO_VOLUME_RENDERING_QUALITY_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>

class SoVolumeRenderingQuality;

class VOLUMEVIZ_API SoVolumeRenderingQualityElement : public SoReplacedElement
{
  SO_ELEMENT_HEADER( SoVolumeRenderingQualityElement );

public:
  // Initializes element
  virtual void init( SoState* state );
  // Sets/Gets the current volume data attributes in the state
  static void set(SoState* state, SoNode *node, SoVolumeRenderingQuality *vrq);
  static void get(SoState* state, SoVolumeRenderingQuality *&node);

  // Default values
  static void getDefault(SoVolumeRenderingQuality *&node);

  SoINTERNAL public:
  // Initializes the SoVolumeRenderingQualityElement class
  static void initClass();
  static void exitClass();

protected:
  SoVolumeRenderingQuality *m_vrq;

  virtual void setElt( SoVolumeRenderingQuality *vrq );

  virtual ~SoVolumeRenderingQualityElement() ;
};

#endif // _SO_VOLUME_GROUP_ELEMENT_
