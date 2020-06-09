/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TEXTURE_COMBINER_ELEMENT
#define  _SO_TEXTURE_COMBINER_ELEMENT

#include <Inventor/elements/SoReplacedTextureElement.h>
#include <Inventor/SbVec.h>
#include <Inventor/STL/vector>

/**
*   @VSGEXT Stores the current texture combiner parameters.
* 
*   @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current texture combiner parameters.
* 
*   @SEE_ALSO
*   SoTextureCombiner
*/

SoEXTENDER_Documented class INVENTOR_API SoTextureCombinerElement : public SoReplacedTextureElement {

  SO_ELEMENT_HEADER(SoTextureCombinerElement);

 public:

  /**
  *  Sets the current texture combiner parameters in the state. Calls virtual
  *  method that subclasses can override.
  */
  static void         set(SoState *state, SoNode *node,
                          int _combineRGB, int _combineAlpha,
                          int _source0RGB, int _source1RGB, int _source2RGB,
                          int _source0Alpha, int _source1Alpha, int _source2Alpha,
                          int _operand0RGB, int _operand1RGB, int _operand2RGB,
                          int _operand0Alpha, int _operand1Alpha, int _operand2Alpha,
                          float _scaleRGB, float _scaleAlpha,
                          const SbVec4f &constantColor);

  /**
  *  Push copies the values from the previous element, so set
  *  doesn't have to set them if they are set AS_IS.
  */
  virtual void        push(SoState *state);

 SoINTERNAL public:
  // Initializes the SoTextureCombinerElement class
  static void         initClass();
  static void         exitClass();


  // Initializes element
  virtual void        init(SoState *state);

  // Common Initialization. Directly called by the constructor.
  virtual void commonInit() ;
 protected:
  // Virtual set methods that subclasses can override.
  virtual void        setElt(int _combineRGB, int _combineAlpha,
                                    int _source0RGB, int _source1RGB, int _source2RGB,
                                    int _source0Alpha, int _source1Alpha, int _source2Alpha,
                                    int _operand0RGB, int _operand1RGB, int _operand2RGB,
                                    int _operand0Alpha, int _operand1Alpha, int _operand2Alpha,
                                    float _scaleRGB, float _scaleAlpha,
                                    const SbVec4f &_constantColor, int unit=0);

  virtual ~SoTextureCombinerElement();

  struct SoTexCombineData {
    SoTexCombineData()
      :combineRGB(0),combineAlpha(0),
        source0RGB(0),source1RGB(0),source2RGB(0),
        source0Alpha(0),source1Alpha(0),source2Alpha(0),
        operand0RGB(0),operand1RGB(0),operand2RGB(0),
        operand0Alpha(0),operand1Alpha(0),operand2Alpha(0),
        scaleRGB(0),scaleAlpha(0),constantColor(0,0,0,0)
    {};

    SoTexCombineData& operator=(const SoTexCombineData &data) 
    {
      combineRGB =data.combineRGB;
      combineAlpha = data.combineAlpha;
      source0RGB =data.source0RGB;
      source1RGB =data.source1RGB;
      source2RGB =data.source2RGB;
      source0Alpha =data.source0Alpha;
      source1Alpha =data.source1Alpha;
      source2Alpha =data.source2Alpha;
      operand0RGB =data.operand0RGB;
      operand1RGB =data.operand1RGB;
      operand2RGB =data.operand2RGB;
      operand0Alpha =data.operand0Alpha;
      operand1Alpha =data.operand1Alpha;
      operand2Alpha =data.operand2Alpha;
      scaleRGB =data.scaleRGB;
      scaleAlpha =data.scaleAlpha;
      constantColor =data.constantColor;
      return *this ;
    }

    //members
    int combineRGB;
    int combineAlpha;
    int source0RGB;
    int source1RGB;
    int source2RGB;
    int source0Alpha;
    int source1Alpha;
    int source2Alpha;
    int operand0RGB;
    int operand1RGB;
    int operand2RGB;
    int operand0Alpha;
    int operand1Alpha;
    int operand2Alpha;
    float scaleRGB;
    float scaleAlpha;
    SbVec4f constantColor;

  }  ;

  SoTexCombineData& getCombinerData(const size_t unit) const;

private:
  mutable std::vector<SoTexCombineData> m_texCombineData;
};

#endif /* _SO_TEXTURE_COMBINER_ELEMENT */

