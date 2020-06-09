/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Jan 2005)
**=======================================================================*/
  
#ifndef  _SO_COLOR_MAP_ELEMENT_
#define  _SO_COLOR_MAP_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>

class SoColorMap ;
/**
* @VSGEXT Stores the current color map.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current color map.
*   @SEE_ALSO
*   SoColorMap
*/

SoEXTENDER_Documented class INVENTOR_API SoColorMapElement : public SoReplacedElement {

  SO_ELEMENT_HEADER( SoColorMapElement );

public:
   /**
   *  Sets the current color map in the state.
   */
   static void        set(SoState* state, SoNode *node, SoColorMap *colorMapNode);

   /**
   *  Gets the current color map in the state.
   */
   static SoColorMap* get(SoState* state);

   /**
   *  Returns the default values.
   */
   static SoColorMap* getDefault();

  SoINTERNAL public:
  // Initializes the SoVolumeData class
  static void initClass();
  static void exitClass();

  // Initializes element
  virtual void init( SoState* state );

protected:
  SoColorMap *m_colorMapNode;

  virtual ~SoColorMapElement() ;
};

#endif // _SO_COLOR_MAP_ELEMENT_
