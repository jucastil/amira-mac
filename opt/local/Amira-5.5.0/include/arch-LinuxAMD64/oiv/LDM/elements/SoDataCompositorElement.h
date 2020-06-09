/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

  
#ifndef  _SO_DATA_COMPOSITOR_ELT__
#define  _SO_DATA_COMPOSITOR_ELT__

#include <Inventor/elements/SoReplacedElement.h>

#include <LDM/nodes/SoDataCompositor.h>

class LDM_API SoDataCompositorElement : public SoReplacedElement {
  SO_ELEMENT_HEADER( SoDataCompositorElement );

public:
  // Initializes element
  virtual void init( SoState* state );
  // Sets/Gets the current volume data attributes in the state
  static void set(SoState* state, SoNode *node, SoDataCompositor*);
  static void get(SoState* state, SoDataCompositor*&);

  // Default values
  static void getDefault(SoDataCompositor*&);

  SoINTERNAL public:
  // Initializes the SoVolumeData class
  static void initClass();
  static void exitClass();

  /** return true if current compositor transform data in RGBA mode */
  static bool isRGBA(SoState* state);

protected:
  SoDataCompositor *m_dataCompositor;

  virtual void setElt( SoDataCompositor *m_dataCompositor );

  virtual ~SoDataCompositorElement() ;
};

#endif // _SO_DATA_COMPOSITOR_ELT__
