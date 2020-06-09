/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_WIN_SLIDER_
#define  _SO_WIN_SLIDER_

#include <Inventor/Win/SoWinBeginStrict.h>
#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/Win/SoWinGDIWidget.h>

class SoFloatCallbackList;
class SoWinMouse;

// callback function prototypes
typedef void SoWinSliderCB(void *userData, float val);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWinSlider
//
//      This is the basic slider type, which lets you set the slider value and
//  register callbacks when the slider is being moved (either as soon as the
//  slider changes values, or when the slider has stopped moving (mouse up)).
//
//////////////////////////////////////////////////////////////////////////////

class INVENTORW_API SoWinSlider : public SoWinGDIWidget {
 public:
  
  // constructor/destructor
  SoWinSlider(SoWidget parent = NULL,
              const char *name = NULL, 
              SbBool buildInsideParent = TRUE);
  ~SoWinSlider();
  
  //
  // Those routines are used to specify the slider value (which is automatically
  // reflected in the slider) and get the current value.
  //
  // NOTE: setValue() will call valueChanged callbacks if the value differs.
  //
  // NOTE: currently only values [0.0 , 1.0] are supported
  //
  void setValue(float v, SbBool updateText = TRUE);
  float getValue() const { return value; }
  
  //
  // Specifies the label string which appears before the slider. A NULL 
  // string will remove the label altogether. (default behavior)
  //
  void setLabel(const char *newlabel);
  const char *getLabel() const { return labelStr; }
  
  //
  // Display a numeric value in a text field to the right of the slider
  // which can be edited to change the value of the slider.
  // Default is TRUE (display the numeric value).
  //
  void setNumericFieldVisible(SbBool b);
  SbBool isNumericFieldVisible() const { return numberVisible; }
  
  //
  // Those routines are used to register callbacks for the different slider
  // actions.
  //
  // NOTE: the start and finish callbacks are only to signal when the mouse
  // goes down and up. No valid callback data is passed (0.0 passed).
  //
  void addStartCallback(SoWinSliderCB *f, void *userData = NULL);
  void addValueChangedCallback( SoWinSliderCB *f, void *userData = NULL);
  void addFinishCallback(SoWinSliderCB *f, void *userData = NULL);
  
  void removeStartCallback(SoWinSliderCB *f, void *userData = NULL);
  void removeValueChangedCallback(SoWinSliderCB *f, void *userData = NULL);
  void removeFinishCallback(SoWinSliderCB *f, void *userData = NULL);
  
  // true while the value is changing interactively
  void interactivity( SbBool flag ) { interactive = flag; }
  SbBool isInteractive() { return interactive; }
  
  // sets/gets the size of the actual slider, excluding the label and
  // text field widget sizes which are fixed in size. 
  //
  // This is the prefered behavior since it allows a user to align
  // multiple sliders (same size) regardless of the text label size
  // (which are usually different).
  //
  // NOTE: this is different from most widgets, which do resize their
  // container widgets. This functionality can still be achieved using
  // the setSize() and getSize() methods.
  //
  void setSliderSize(const SbVec2s &size);
  SbVec2s getSliderSize();
  
  void setNumberWidget(SoWidget hWnd) {numberWidget = hWnd;};
  SoWidget getNumberWidget() {return numberWidget;} ;
  static void textFieldCB(SoWinSlider *p,SoWidget hCtrl);
  
 protected:  
  
  // This constructor takes a boolean whether to build the widget now.
  // Subclasses can pass FALSE, then call SoWinSlider::buildWidget()
  // when they are ready for it to be built.
  SoEXTENDER
    SoWinSlider(SoWidget parent,
                const char *name, 
                SbBool buildInsideParent, 
                SbBool buildNow);
  
  // redefine these to do slider specific things
  virtual void redraw();
  virtual void processEvent(XAnyEvent *anyevent);
  virtual void sizeChanged(const SbVec2s &newSize);
  
  SoWidget buildWidget(SoWidget parent);
  
  //
  // this is the routine subclasses would redefine to change the look of
  // the actual slider top region, which defaults to grey with a thin white marker.
  //
  virtual void drawSliderTopRegion();
  
  // slider top region area (used by subclasses to do their own
  // drawings in there).
  short slx1, sly1, slx2, sly2;
  short thumx1, thumy1, thumx2, thumy2;
  
 private:

  SoWidget mgrWidget, numberWidget, sliderWidget, labelWidget;
  SbBool numberVisible; // whether numeric field is visible
  char *labelStr; // label preceeding slider
  SbVec2s sliderSize; // size of the 'widget' and 'shell'
  SoWinMouse *mouse;
  
  // slider local variables (slider value, thum position)
  float value;
  short position, posdiff;
  
  // build routines
  void doLabelLayout();
  void doNumberLayout();
  
  // callback variables
  SoFloatCallbackList *startCallbacks;
  SoFloatCallbackList *changedCallbacks;
  SoFloatCallbackList *finishCallbacks;
  SbBool interactive;
  
  // this is called by both constructors
  void constructorCommon(SbBool buildNow);
  
};

#include <Inventor/Win/SoWinEndStrict.h>

#endif  /* _SO_WIN_SLIDER_ */
