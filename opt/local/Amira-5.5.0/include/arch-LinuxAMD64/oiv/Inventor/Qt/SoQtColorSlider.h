/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _SO_QT_COLOR_SLIDER_
#define  _SO_QT_COLOR_SLIDER_

#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/Qt/SoQtSlider.h>

//////////////////////////////////////////////////////////////////////////////
//  Class: SoQtColorSlider
//
//      This class defines the color slider which is a set of predefined
//  sliders (R, G, B, H, S, V,..) with special behaviors.

class INVENTORQT_API SoQtColorSlider : public SoQtSlider {
  Q_OBJECT

    public:
  // list of color sliders types
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
  SoQtColorSlider(QWidget* parent = NULL,
                  const char *name = NULL, 
                  SbBool buildInsideParent = TRUE, 
                  Type type = INTENSITY_SLIDER);
    
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
  void setBaseColor(const float rgbOrHsv[3]);
  const float *getBaseColor();
    
  // This routine sets the WYSIWYG (What You See Is What You Get) mode
  // to be true or false (default FALSE). Immediate mode.
  // This has no effect on monochrome sliders.
  void setWYSIWYG(SbBool trueOrFalse = TRUE);    // default FALSE
  SbBool isWYSIWYG();
    
  // returns the type of the slider
  SoQtColorSlider::Type getType();
    
 protected:
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoQtSlider::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER SoQtColorSlider (QWidget* parent,
                              const char *name, 
                              SbBool buildInsideParent, 
                              Type type, 
                              SbBool buildNow);
    
 private:
  // local vars
  SoQtBasicSlider::Type type;
  void constructorCommon(SoQtColorSlider::Type type, SbBool buildNow);
};


#endif  /* _SO_QT_COLOR_SLIDER_ */
