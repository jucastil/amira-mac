/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Oct 1997)
**=======================================================================*/

                                                             /* include files */
#ifndef  _SO_ANNOT_TEXT3_RENDER_PRINT_ELEMENT_
#define  _SO_ANNOT_TEXT3_RENDER_PRINT_ELEMENT_

#include <Inventor/elements/SoInt32Element.h>

/*----------------------------------------------------------------------------*/
/**
* @VSGEXT Stores the current render print type of an SoAnnoText3Property node.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current render print type of an SoAnnoText3Property node. 
*   @SEE_ALSO
*   SoAnnoText3Property
*/

SoEXTENDER_Documented class INVENTOR_API SoAnnoText3RenderPrintElement : public SoInt32Element {
  
  SO_ELEMENT_HEADER(SoAnnoText3RenderPrintElement);
  
 public:

   /** Render print type */
  enum RenderPrintType {
    /** Render 3D print vector */
    RENDER3D_PRINT_VECTOR,
    /** Render 3D print raster */
    RENDER3D_PRINT_RASTER,
    /** Render 2D print raster */
    RENDER2D_PRINT_RASTER
  } ;
 
  /**
  *  Sets the value in the state.
  */
    static void set(SoState *state, RenderPrintType type);
  
  /**
  *  Returns the current value from the state.
  */
  static RenderPrintType get(SoState *state);
  
  /**
  *  Returns the default value.
  */
  static RenderPrintType getDefault();
  
  SoINTERNAL public:
  // Initializes the class
  static void initClass();
  static void exitClass();

  // Initializes element
  virtual void init(SoState *state);

protected:
  virtual ~SoAnnoText3RenderPrintElement();
};

/*----------------------------------------------------------------------------*/

#endif /* _SO_ANNOT_TEXT3_RENDER_PRINT_ELEMENT_  */
