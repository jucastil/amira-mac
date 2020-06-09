/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Mar 1999)
**=======================================================================*/

                                                             /* include files */
#ifndef  _PO_LABEL_HINTS_ELEMENT_
#define  _PO_LABEL_HINTS_ELEMENT_


#include <Inventor/elements/SoReplacedElement.h>
#include <MeshViz/nodes/PoLabelHints.h>


/*----------------------------------------------------------------------------*/

class MESHVIZ_API PoLabelHintsElement : public SoReplacedElement {
  
  SO_ELEMENT_HEADER(PoLabelHintsElement);
  
 public:
  // Initializes element
  virtual void init(SoState *state);
  
  // Set the current label hints.
  //
  // @UNICODE_WARNING
  SoNONUNICODE static void set(SoState *state, SoNode *node, 
                  PoLabelHints::LabelPath labelPath,
                  PoLabelHints::Justification justif,
                  const char *addString,
                  SbBool isAddStringIgnored,
                  SbBool isLabelLineVisible);


 // Set the current label hints.
  static void set(SoState *state, SoNode *node, 
                  PoLabelHints::LabelPath labelPath,
                  PoLabelHints::Justification justif,
                  const SbString& addString,
                  SbBool isAddStringIgnored,
                  SbBool isLabelLineVisible);
  
  /** Return the current label hints from the state.
   * [OIV-WRAPPER-ARG IN,OUT,OUT,OUT,OUT]
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void get(SoState *state, 
                  PoLabelHints::LabelPath &labelPath,
                  PoLabelHints::Justification &justif,
                  const char *&addString,
                  SbBool &isLabelLineVisible);
  
  /** Return the current label hints from the state.
   * [OIV-WRAPPER-ARG IN,OUT,OUT,OUT,OUT]
   */
  static void get(SoState *state, 
                  PoLabelHints::LabelPath &labelPath,
                  PoLabelHints::Justification &justif,
                  SbString& addString,
                  SbBool &isLabelLineVisible);

  /** Default values
   * [OIV-WRAPPER-ARG OUT,OUT,OUT,OUT]
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static  void getDefault(PoLabelHints::LabelPath &labelPath,
                          PoLabelHints::Justification &justif,
                          char *&addString,
                          SbBool &isLabelLineVisible);
  
  /** Default values
   * [OIV-WRAPPER-ARG OUT,OUT,OUT,OUT]
   */
  static  void getDefault(PoLabelHints::LabelPath &labelPath,
                          PoLabelHints::Justification &justif,
                          SbString& addString,
                          SbBool &isLabelLineVisible);

 SoINTERNAL public:
  // Initializes the class
  static void initClass();
	static void exitClass() ;
  
 protected:
  virtual ~PoLabelHintsElement();
  
 private:
  PoLabelHints::LabelPath m_labelPath;
  PoLabelHints::Justification m_justif;
  SbString m_addString;
  SbBool m_isLabelLineVisible;
};
/*----------------------------------------------------------------------------*/

#endif // _PO_LABEL_HINTS_ELEMENT_
