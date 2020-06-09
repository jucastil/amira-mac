/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_XT_COLOR_SLIDER_
#define  _SO_XT_COLOR_SLIDER_

#include "SoXtSlider.h"

class SbColor;
class SbVec2f;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoXtColorSlider
//
//      This class defines the color slider which is a set of predefined
//  sliders (R, G, B, H, S, V,..) with special behaviors.
//
//////////////////////////////////////////////////////////////////////////////

class INVENTORXT_API SoXtColorSlider : public SoXtSlider {
    
 public:
    
  //
  // list of color sliders types
  //
  enum Type {
    RED_SLIDER, 
    GREEN_SLIDER, 
    BLUE_SLIDER, 
    HUE_SLIDER, 
    SATURATION_SLIDER, 
    VALUE_SLIDER, 
    INTENSITY_SLIDER // independent of the slider value
  };
    
  // Constructor/Destructor
  SoXtColorSlider(
                  SoWidget parent = NULL,
                  const char *name = NULL, 
                  SbBool buildInsideParent = TRUE, 
                  Type type = INTENSITY_SLIDER);
  ~SoXtColorSlider();
    
  //
  // Routine used to specify the slider value and also the top region
  // color (WYSIWYGmode in most cases). Users should call this routine 
  // instead of the base class setValue() routine if they want the color 
  // slider top region to correctly reflect the current color.
  // (code is optimized for WYSIWYGmode off)
  //
  // NOTE: routine expects
  //      an rgb color for R, G or B slider type
  //      an hsv color for H, S, or V slider type
  //      an rgb color for Intensity slider type
  //
  // NOTE: if calling setBaseColor() changes the thumb position the
  // valueChanged callbacks will be called with the new value.
  //
  void        setBaseColor(const float rgbOrHsv[3]);
  const float *getBaseColor()         { return color; }
    
  //
  // This routine sets the WYSIWYG (What You See Is What You Get) mode
  // to be true or false (default FALSE). Immediate mode.
  // This has no effect on monochrome sliders.
  //
  void        setWYSIWYG(SbBool trueOrFalse);    // default FALSE
  SbBool      isWYSIWYG()             { return WYSIWYGmode; }
    
  // returns the type of the slider
  SoXtColorSlider::Type getType()     { return type; }
    
 protected:

  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoXtSlider::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoXtColorSlider(
                    SoWidget parent,
                    const char *name, 
                    SbBool buildInsideParent, 
                    Type type, 
                    SbBool buildNow);
    
  // redefine this routine to cache slider top geometry
  virtual void    sizeChanged(const SbVec2s &newSize);
    
  // redefine this routine to do the actual slider top region drawing.
  // This routine is automatically called by the SoXtSlider::redraw() routine.
  virtual void    drawSliderTopRegion();
    
 private:
    
  // local vars
  Boolean             WYSIWYGmode;
  Type                type;
  float               color[3];
  SbColor             *defaultColors, *colors;
  SbVec2f             *geometry;
    
  // routine that make the default and WYSIWYG colors
  void    makeDefaultColors();
  void    makeWYSIWYGcolors();
    
  static void     sliderChangedCB(void *, float val);

  // this is called by both constructors
  void constructorCommon(SoXtColorSlider::Type type, SbBool buildNow);
};


#endif  /* _SO_XT_COLOR_SLIDER_ */
