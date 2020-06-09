/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_QT_BASIC_SLIDER_
#define _SO_QT_BASIC_SLIDER_
#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/Qt/SoQtGLWidget.h>

class SbColor;
class SoFloatCallbackList;

// callback function prototypes
typedef void SoQtBasicSliderCB(void *userData, float val);

//////////////////////////////////////////////////////////////////////////////
//  Class: SoQtBasicSlider
class INVENTORQT_API SoQtBasicSlider : public SoQtGLWidget
{
  Q_OBJECT

    public:
  // Type of slider
  enum Type {
    RED_SLIDER, 
    GREEN_SLIDER, 
    BLUE_SLIDER, 
    HUE_SLIDER, 
    SATURATION_SLIDER, 
    VALUE_SLIDER, 
    INTENSITY_SLIDER, // independent of the slider value
    PLAIN_SLIDER
  };

  // Constructor / Destructor
  SoQtBasicSlider (QWidget *parent, Type t);
  ~SoQtBasicSlider ();

  // value management
  void setValue(float v);
  float getValue() const 
    { return value; }

  // Routine used to specify the slider value and also the top region
  // color (WYSIWYGmode in most cases). Users should call this routine 
  // instead of the base class setValue() routine if they want the color 
  // slider top region to correctly reflect the current color.
  // (code is optimized for WYSIWYGmode off)
  //
  // NOTE: routine expects
  //        an rgb color for R, G or B slider type
  //        an hsv color for H, S, or V slider type
  //        an rgb color for Intensity slider type
  //
  // NOTE: if calling setBaseColor() changes the thumb position the
  // valueChanged callbacks will be called with the new value.
  void setBaseColor(const float rgbOrHsv[3]);
  const float *getBaseColor() { return color; }

  // This routine sets the WYSIWYG (What You See Is What You Get) mode
  // to be true or false (default FALSE). Immediate mode.
  // This has no effect on monochrome sliders.
  void  setWYSIWYG(SbBool trueOrFalse);    // default FALSE
  SbBool        isWYSIWYG()             { return WYSIWYGmode; }

  // Those routines are used to register callbacks for the different slider
  // actions.
  // NOTE: the start and finish callbacks are only to signal when the mouse
  // goes down and up. No valid callback data is passed (0.0 passed).
  void  addStartCallback (SoQtBasicSliderCB *f, void *userData = NULL);
  void  addValueChangedCallback (SoQtBasicSliderCB *f, void *userData = NULL);
  void  addFinishCallback (SoQtBasicSliderCB *f, void *userData = NULL);
  void  removeStartCallback (SoQtBasicSliderCB *f, void *userData = NULL);
  void  removeValueChangedCallback (SoQtBasicSliderCB *f, void *userData = NULL);
  void  removeFinishCallback (SoQtBasicSliderCB *f, void *userData = NULL);

  // true while the value is changing interactively
  void interactivity( SbBool flag ) { interactive = flag; }
  SbBool isInteractive() { return interactive; }

 protected:

  // drawing
  virtual void redraw();
  virtual void drawSliderTopRegion();

  // Slider geometry values
  short slx1, sly1, slx2, sly2;
  short thumx1, thumy1, thumx2, thumy2;

 private:

  // Slider core values
  float     value;
  short     position;
  short     posdiff;
  SbBool    interactive;
  SbBool    leftButtonPressed;

  // Colors values
  SbBool    WYSIWYGmode;
  SbColor   *defaultColors;
  SbColor   *colors;
  SbVec2f   *geometry;
  Type      type;
  float     color[3];

  // Colors management
  void makeDefaultColors();
  void makeWYSIWYGcolors();


  // callback variables
  SoFloatCallbackList  *startCallbacks;
  SoFloatCallbackList  *changedCallbacks;
  SoFloatCallbackList  *finishCallbacks;

  // Events
  virtual void sizeChanged(const SbVec2s &newSize);
  void processEvent(QEvent *anyevent);
  static void sliderChangedCB(void *, float val);
};

#endif // _SO_QT_BASIC_SLIDER_
