/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas Daguise (Nov 2003)
**=======================================================================*/

#ifndef  _SO_FULL_SCENE_ANTIALIASING_ELEMENT_
#define  _SO_FULL_SCENE_ANTIALIASING_ELEMENT_

#include <Inventor/elements/SoSubElement.h>
/**
* @VSGEXT Stores the current Full-Scene Antialising state.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current Full-Scene Antialising state.
*   @SEE_ALSO
*   SoFullSceneAntialiasing, SoWinGLWidget, SoXtGLWidget, SoQtGLWidget
*/

SoEXTENDER_Documented class INVENTOR_API SoFullSceneAntialiasingElement : public SoElement {

  SO_ELEMENT_HEADER(SoFullSceneAntialiasingElement);

 public:
   /** Filter */
  enum Filter {
    /** Points */
    POINTS   = 0x01,
    /** Lines */
    LINES    = 0x02,
    /** Polygons */
    POLYGONS = 0x04,
    /** Text */
    TEXT     = 0x08,
    /** All */
    ALL      = LINES | POINTS | POLYGONS | TEXT
  };

  /**
  *  Sets the current Full-Scene Antialising attributes in the state.
  */
  static void set(SoState *state, SbBool on, SbBool currOn, int filter);
  /**
  *  Gets the current Full-Scene Antialising attributes in the state.
  */
  static SbBool get(SoState *state, SbBool &on, SbBool &pointsOn, SbBool &linesOn, SbBool &polygonsOn, SbBool &textsOn, int& filter);
  
  /**
  *  Push copies the values from the previous element.
  */
  virtual void  push(SoState *state);

  /**
  *  Returns the top (current) instance of the element in the state.
  *  Note it does NOT cause cache dependency!
  *  It also casts away the const.
  */
  static SoFullSceneAntialiasingElement * getInstance(const SoState *state);

  /**
  *  Returns TRUE if the attributes of polygon offset  match in both elements.
  */
  virtual SbBool matches(const SoElement *elt) const;

  /**
  *  Creates and returns a copy of this element.
  */
  virtual SoElement *copyMatchInfo() const;

  /**
  *  Returns the default values.
  */
  static SbBool getDefault(SbBool &on, SbBool &pointsOn, SbBool &linesOn, SbBool &polygonsOn, SbBool &textsOn, int& filter);

 SoINTERNAL public:
  // Initializes the SoFullSceneAntialiasingElement class
  static void initClass();
  static void exitClass();

  // Initializes element
  virtual void init(SoState *state);

 protected:
  SbBool m_on;
  SbBool m_currOn;
  int  m_filterMask;
  SbBool m_pointsOn;
  SbBool m_linesOn;
  SbBool m_polygonsOn;
  SbBool m_textOn;

  virtual void setElt(SbBool on, SbBool currOn, int filter);

  virtual ~SoFullSceneAntialiasingElement();
};

#endif /* _SO_FULL_SCENE_ANTIALIASING_ELEMENT_ */
