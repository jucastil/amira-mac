/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/

#ifdef  IV_STRICT
#error SoGLColorIndexElement is obsolete. See So[GL]LazyElement.h instead.
#endif /*IV_STRICT*/
#ifndef  _SO_GL_COLOR_INDEX_ELEMENT
#define  _SO_GL_COLOR_INDEX_ELEMENT

#include <Inventor/SbColor.h>
#include <Inventor/elements/SoLazyElement.h>

 /**
*   Stores color index of current material (superseded by SoLazyElement).
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This class is superseded by the SoLazyElement class.
*   All methods are converted inline to SoLazyElement methods for
*   compatibility.
* 
*   @SEE_ALSO
* [OIV-WRAPPER-CLASS NO_WRAP]
*/

SoEXTENDER_Documented class INVENTOR_API SoGLColorIndexElement {


 public:

  /**
  *  Sets the current indexed color(s).
  */
  static void         set(SoState *state, SoNode * node,
                          int32_t numIndices, const int32_t *indices)
    {
      SoLazyElement::setColorIndices(state, node, numIndices, indices);
    }


  /**
  *  Returns the top (current) instance of the element in the state.
  */
  static const SoGLColorIndexElement * getInstance(SoState *state)
    {
      SoGLColorIndexElement* cie = new SoGLColorIndexElement;
      cie->saveState = state;
      return(cie);
    }


  /**
  *  Returns the number of color indices in current instance.
  */
  int32_t             getNum() const          
    {
      return(SoLazyElement::getInstance(saveState)->getNumColorIndices());
    }
        
  /**
  *  Returns a current color index.
  */
  int32_t     get(int index) const
    {
      return(SoLazyElement::getColorIndex(saveState, index));
    }
        
  /**
  *  Returns the default index.
  */
  static int32_t              getDefault()            
    { return SoLazyElement::getDefaultColorIndex(); }

 private:
  SoState* saveState;
};
#endif /* _SO_GL_COLOR_INDEX_ELEMENT */
