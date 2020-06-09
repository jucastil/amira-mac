/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_GL_TEXTURE_COMBINER_ELEMENT
#define  _SO_GL_TEXTURE_COMBINER_ELEMENT

#include <Inventor/elements/SoTextureCombinerElement.h>

/**
* @VSGEXT Stores the current texture combiner attributes.
* 
*   @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current texture combiner attributes and sends commands to GL
*   based on them. 
* 
*   @SEE_ALSO
*   SoTextureCombinerElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLTextureCombinerElement : public SoTextureCombinerElement {

  SO_ELEMENT_HEADER(SoGLTextureCombinerElement);

 public:
  /**
  * 
  */
  static void   set(SoState *state, SoNode *node,
                    int _combineRGB, int _combineAlpha,
                    int _source0RGB, int _source1RGB, int _source2RGB,
                    int _source0Alpha, int _source1Alpha, int _source2Alpha,
                    int _operand0RGB, int _operand1RGB, int _operand2RGB,
                    int _operand0Alpha, int _operand1Alpha, int _operand2Alpha,
                    float _scaleRGB, float _scaleAlpha,
                    const SbVec4f &constantColor);

  /**
  *  Override push() method to remember previous element's state so
  *  we can sometimes generate more efficient GL calls.
  */
  virtual void        push(SoState *state);

  /**
  *  Override pop() method so side effects can occur in GL.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLTextureCombinerElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:

  virtual ~SoGLTextureCombinerElement();

 private:

  SbBool needCrossBar(int sourceParameter);

  // Sends texture combine parameters to GL
  void                send(SoState *state);
};

#endif /* _SO_GL_TEXTURE_COMBINER_ELEMENT */
