/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Mar 2000)
**=======================================================================*/

  
#ifndef  _SO_ROI_ELEMENT_
#define  _SO_ROI_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>


#include <Inventor/SbBox.h> // To Suppress in the VERSION
#include <LDM/nodes/SoROI.h>

class LDM_API SoROIElement : public SoReplacedElement {
  SO_ELEMENT_HEADER( SoROIElement );

public:
  // Initializes element
  virtual void init( SoState* state );
  // Sets/Gets the current volume data attributes in the state
  static void set(SoState* state, SoNode *node, SoROI *ROINode);
  static void get(SoState* state, SoROI *&ROINode);

  // Default values
  static void getDefault(SoROI *&ROINode);

  SoINTERNAL public:
  // Initializes the SoVolumeData class
  static void initClass();
  static void exitClass();

protected:
  SoROI *m_ROINode;

  virtual void setElt( SoROI *ROINode );

  virtual ~SoROIElement() ;
};

#endif // _SO_ROI_ELEMENT_
