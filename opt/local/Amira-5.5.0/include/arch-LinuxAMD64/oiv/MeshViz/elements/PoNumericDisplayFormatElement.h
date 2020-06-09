/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Dec 1997)
**=======================================================================*/

                                                             /* include files */
#ifndef  _PO_NUMERIC_DISPLAY_FORMAT_ELEMENT_
#define  _PO_NUMERIC_DISPLAY_FORMAT_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>

class PbNumericDisplayFormat;

/*----------------------------------------------------------------------------*/

class MESHVIZ_API PoNumericDisplayFormatElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(PoNumericDisplayFormatElement);
  
 public:
  // Initializes element
  virtual void init(SoState *state);
  
  // set the current NumericDisplayFormat
  static void set(SoState *state, SoNode *node,
                  const PbNumericDisplayFormat *numericDisplayFormat);
  
  // return the current NumericDisplayFormat from the state
  static const PbNumericDisplayFormat *get(SoState *state);
  
 SoINTERNAL public:
  // Initializes the class
  static void initClass();
	static void exitClass() ;
  
 protected:
  static PbNumericDisplayFormat *m_defaultNumericDisplayFormat;
  PbNumericDisplayFormat *m_numericDisplayFormat;
  
  virtual ~PoNumericDisplayFormatElement();
};
/*----------------------------------------------------------------------------*/

#endif // _PO_NUMERIC_DISPLAY_FORMAT_ELEMENT_
