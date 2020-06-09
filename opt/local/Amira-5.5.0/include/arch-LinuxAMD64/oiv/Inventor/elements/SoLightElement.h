/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Feb 1997)
**=======================================================================*/

#ifndef  _SO_LIGHT_ELEMENT_
#define  _SO_LIGHT_ELEMENT_

/* include files */
#include <Inventor/SoLists.h>
#include <Inventor/elements/SoAccumulatedElement.h>
#include <Inventor/SbMatrix.h>

#include <Inventor/STL/vector>

class SoLight;

/**
* @VSGEXT Stores information on lights.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores information on lights.
*
*   @SEE_ALSO
*   SoLight, SoDirectionalLight, SoPointLight, SoSpotLight
*/

SoEXTENDER_Documented class INVENTOR_API SoLightElement : public SoAccumulatedElement {
  SO_ELEMENT_HEADER(SoLightElement) ;

 public:
  /**
  *  Add to the current light list and to the current matrix list.
  */
  static void add(SoState *state, SoLight *light, const SbMatrix &WCToVRCMatrix) ;

  /**
  *  Overrides push() method to copy values from next instance in the stack.
  */
  virtual void push(SoState *state) ;

  /**
  *  Pop method.
  */
  virtual void pop(SoState *, const SoElement *prevTopElement) ;

  /**
  *  Returns the current list of light nodes from the state.
  */
  static const SoNodeList& getLights(SoState *state) ;

  /**
  *  Returns the matrix transform (WC to VRC) for the light i for an SoCallbackAction.
  *  Returns the modelling matrix for other action.
  */
  static const SbMatrix& getMatrix(SoState *state, int index) ;

 SoINTERNAL public:
  typedef std::vector<SoLight*> LightList;

  // Initializes the SoLightElement class
  static void initClass() ;
  static void exitClass() ;

  // Initializes element.
  virtual void init(SoState *state);

  /**
   * Returns the current list of light nodes from the state in a stl list
   */
  static void getLights(SoState *state, LightList& lightList);

  /** Returns model matrix of given light */
  static void getMatrix(SoState *state, SoLight* light, SbMatrix& model, SbMatrix& view);

 protected:
  // list of light nodes
  SoNodeList m_lights ;

  // List of transform matrix from world coordinates to view reference coordinates
  std::vector<SbMatrix*> m_WCToVRCMatrix;
  int        m_startIndex;

  /** List of view matrix */
  std::vector<SbMatrix> m_viewMatrix;

  virtual ~SoLightElement() ;
} ;
/*----------------------------------------------------------------------------*/

#endif // _SO_LIGHT_ELEMENT_
