/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Dec 1998)
**=======================================================================*/

                                                             /* include files */
#ifndef  _SO_POLYGON_OFFSET_ELEMENT_
#define  _SO_POLYGON_OFFSET_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>

/**
* @VSGEXT Stores current polygon offset state.
*
* @ingroup elements
*
*   @DESCRIPTION
*
*   @SEE_ALSO
*   SoPolygonOffset
*/

SoEXTENDER_Documented class INVENTOR_API SoPolygonOffsetElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(SoPolygonOffsetElement) ;

 public:
   /** PolygonOffset style. */
  enum Style {
    /** FILLED */
    FILLED = 0x01,
    /** LINES */
    LINES  = 0x02,
    /** POINTS */
    POINTS = 0x04
  } ;

  /** Initializes element */
  virtual void init(SoState *state) ;
  
  /** Sets the current polygon offset attributes in the state */
  static void set(SoState *state, SoNode *node, float factor, float units, Style styles, SbBool on) ;
  /** Gets the current polygon offset attributes in the state */
  static void get(SoState *state, float &factor, float &units, Style &styles, SbBool &on) ;
  
  /** Push copies the values from the previous element */
  virtual void  push(SoState *state) ;

  /** Returns TRUE if the attributes of polygon offset  match in both elements */
  virtual SbBool matches(const SoElement *elt) const ;

  /** Create and return a copy of this element */
  virtual SoElement *copyMatchInfo() const ;

  /** Default values */
  static void getDefault(float &factor, float &units, Style &styles, SbBool &on) ;

 SoINTERNAL public:
  // Initializes the SoPolygonOffsetElement class
  static void initClass() ;
  static void exitClass() ;

 protected:
  float  m_factor ;
  float  m_units ;
  Style  m_stylesMask ;
  SbBool m_on ;

  virtual void setElt(float factor, float units, Style styles, SbBool on) ;

  virtual ~SoPolygonOffsetElement() ;
} ;

#endif /* _SO_POLYGON_OFFSET_ELEMENT_ */
