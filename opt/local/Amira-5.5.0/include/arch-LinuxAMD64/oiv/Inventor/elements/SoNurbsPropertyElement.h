/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Jun 1998)
**=======================================================================*/

                                                             /* include files */
#ifndef  _SO_NURBS_PROPERTY_ELEMENT_
#define  _SO_NURBS_PROPERTY_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/nodes/SoNurbsProperty.h>

#include <Inventor/SbColor.h>
/**
*   @VSGEXT Stores current NURBS properties.
* 
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current NURBS properties.
* 
*   @SEE_ALSO
*   SoNurbsProperty
*/

SoEXTENDER_Documented class INVENTOR_API SoNurbsPropertyElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(SoNurbsPropertyElement) ;
 public:

   /** Draw style */
  enum DrawStyle {
    /** Normal */
    NORMAL                      = 0x01,
    /** Boundaries and trim curves */
    BOUNDARIES_AND_TRIM_CURVES  = 0x02,
    /** Central iso param curves */
    CENTRAL_ISO_PARAM_CURVES    = 0x04
  } ;

  /**
  *  Sets the current NURBS properties attributes in the state.
  */
  static void set(SoState *state, SoNode *node, DrawStyle drawStyleMask, 
		  int numSamplePoints, const SbColor &color, 
		  u_short isoParamCurvesPattern,
		  SoNurbsProperty::TessellationType tessType,
		  float tessDistance, float tessAngle);
  /**
  *  Gets the current NURBS properties attributes in the state.
  */
  static void  get(SoState *state, DrawStyle &drawStyleMask, int &numSamplePoints, 
		   SbColor &color, u_short &isoParamCurvesPattern,
		   SoNurbsProperty::TessellationType &tessType,
		   float &tessDistance, float &tessAngle);

  /**
  *  Get default values.
  */
  static void getDefault(DrawStyle &drawStyleMask, int &numSamplePoints, 
			 SbColor &color, u_short &isoParamCurvesPattern,
			 SoNurbsProperty::TessellationType &tessType,
			 float &tessDistance, float &tessAngle);
  
 SoINTERNAL public:
  // Initializes the SoNurbsPropertyElement class
  static void initClass() ;
  static void exitClass() ;
 
  // Initializes element
  virtual void init(SoState *state) ;
  
 private:
  DrawStyle m_drawStyleMask         ;
  int       m_numSamplePoints       ;
  SbColor   m_color                 ;
  u_short   m_isoParamCurvesPattern ;
  SoNurbsProperty::TessellationType m_tessType;
  float m_tessDistance;
  float m_tessAngle;

 protected:
  virtual ~SoNurbsPropertyElement() ;
} ;

#endif /* _SO_NURBS_PROPERTY_ELEMENT_ */
