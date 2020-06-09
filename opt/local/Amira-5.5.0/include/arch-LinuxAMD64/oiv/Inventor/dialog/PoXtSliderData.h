/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _PO_XT_SLIDER_DATA_H_
#define _PO_XT_SLIDER_DATA_H_

#include <Inventor/dialog/PoXtElementData.h>

#ifndef _WIN32
class SliderGl;
class PoXtLabelData;
#else
class SoCallbackList;
class PoXtLabelData;
class PoXtCustomSlider;
class PoEdit;
class PoButton;
#endif

class SbColor;
class SbVec2s;

/**
 * @VSGEXT Abstract class for a slider.
 * 
 * @ingroup DialogM
 * 
 * @DESCRIPTION
 *    @deprecated Please use DialogViz classes for new development.
 *
 *    This element contains a text label on the left, a GL slider in the center 
 *    and an editable text field on the right. Futhermore, the appearance of the
 *    slider can be defined. By default, the editable text is visible, the text 
 *    of label is an empty string, and the trigger mode is MOUSE_ON_RELEASE_TRIGGER.
 * 
 */
class INVENTORW_API PoXtSliderData : public PoXtElementData
{

 public:

  /**
   *  Type of slider's triggering.
   */
  enum TriggerMode
  {
    /**
     *  The slider is triggered each time the mouse move.
     */
    CONTINUOUS_TRIGGER,      
    /**
     *  The slider is triggered only when the mouse is released.
     */
    MOUSE_ON_RELEASE_TRIGGER 
  } ;



  /**
   * Destructor.
   */
  virtual ~PoXtSliderData();

  /**
   * Sets the text of the label on the left of the GL slider.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setLabel(const char * label);

  /**
   * Sets the text of the label on the left of the GL slider.
   */
  void setLabel( const SbString& label );

  /**
   * Gets the text of the label on the left of the GL slider.
   */
  SbString getLabel() const;

  /**
   * Returns the visibility of the numerical field on the right of the GL slider.
   */
  SbBool isNumericFieldVisible() const;

  /**
   * Sets the visibility of the numeric field on the right of the GL slider.
   */
  void setNumericFieldVisibility(SbBool flag);

  /**
   * Sets the trigger mode. Either the slider is triggered when the mouse is 
   * released on the thumb of the slider (MOUSE_ON_RELEASE_TRIGGER ) or 
   * each time the thumb of the slider is moved (CONTINUOUS_TRIGGER).
   */
  void setTrigger(TriggerMode mode);

  /**
   * Gets the trigger mode. Either the slider is triggered when the mouse is 
   * released on the thumb of the slider (MOUSE_ON_RELEASE_TRIGGER ) or 
   * each time the thumb of the slider is moved (CONTINUOUS_TRIGGER).
   */
  TriggerMode getTrigger() const;

  /**
   * Sets if the limits are fixed or not.
   * The limits are not fixed by default.
   */
  void   setFixedLimits(SbBool flag) ;

  /**
   * Indicates if the limits are fixed or not.
   */
  SbBool isFixedLimits() const ;

  /* Defines the appearence of Slider */



  /**
   * Defines the appearance of the slider with a constant color.
   */
  void setAppearance(const SbColor & color);

  /**
   * Defines the appearance of the slider. It has a shade of colors 
   * from the startColor to the endColor.
   */
  void setAppearance(const SbColor & startColor, const SbColor & endColor);

  /**
   * Defines the appearance of the slider. It is represented by a list of 
   * colors, and according to the state of isColorsShaded,
   */
  void setAppearance(int numColors, 
                     const SbColor * colors, 
                     SbBool isColorShaded=TRUE);

  /**
   * Prototype of the callback used by the next setAppearance method. The parameters 
   * represent the left inferior and the right superior corners of the slider.
   */
  typedef void PoXtSliderAppearanceCB(const SbVec2s & start, 
                                      const SbVec2s & end,
                                      void * userData);

  /**
   * Defines the appearance of the slider by a function given by the user.
   * This function will be called when the slider is drawn. The parameters 
   * start and end of the function represent the lower left and the upper 
   * right corners of the slider. To draw the appearance of the slider, 
   * you must imperatively call OpenGL functions only.
   */
  void setAppearance(PoXtSliderAppearanceCB * function, void * userData=NULL);

  /**
   * Returns the type of the Xt element.
   */
  virtual TypeXtElement getType() const=0;

  /*----------------------------------------------------------------------------*/

#ifndef _WIN32
 SoINTERNAL public:

  virtual SoWidget buildWidget(SoWidget parent);
  virtual void handleTextFieldCallback(SoWidget w)=0;

  // affect the internal data xtElement to current object
  // xtElement have to be PoXtSliderData
  virtual void updateValues(const PoXtElementData * xtElement);

  // minimum width for the widget in fact this represent the width of the label
  // The mimimum width for a widget whith no label will be 0
  virtual int  getRealMinWidgetWidth() const;
  virtual void setMinWidgetWidth(int value);


  // To attach a Callback to the slider and numberWidget
  SliderGl * getSliderGl() const;
  SoWidget     getNumberWidget() const;

  virtual void addCallback(SoCallbackListCB * function, void * data);
  virtual void removeCallback(SoCallbackListCB * function, void * data);

  // Callback function for treat the redraw of numeric field when the slider 
  // thumb position changed.
  virtual void valueChangedCallback(PoXtSliderData * slider, 
                                    float * thumbPosition)=0;
  // Callback for treat when the mouse button is released
  virtual void releaseCallback(PoXtSliderData * slider, 
                               float * thumbPosition)=0;
  // Callback function for update the numeric field when the callback
  // have to raise on release mouse button
  virtual void updateNumericFieldCallback(PoXtSliderData * slider, 
                                          float * thumbPosition)=0;

 protected:
  PoXtSliderData(const char * label=NULL, 
                 TriggerMode mode=MOUSE_ON_RELEASE_TRIGGER);

  PoXtSliderData(const PoXtSliderData & slider);
  
  // Update the numeric field with slider value by raising slider callback
  virtual void drawTextField(SoWidget numericWidget)=0;
  SoCallbackList * _sliderCallback;
  
 private:
  void buildNumericField();
  void attachLabel();
  void buildToggle();

  SliderGl * _sliderGl;
  SoWidget   _sliderGlWidget, _labelWidget, _numberWidget;
  SoWidget   _toggleWidget;
  SbBool   _numberVisible;      // whether numeric field is visible
  TriggerMode _modeTrigger;
  PoXtLabelData * _label; 
  SbBool _isFixedLimits ;
#else
 SoINTERNAL public:
  virtual void buildWidget(SoWidget parent, int verticalOffset);  
  
  virtual void updateValues(const PoXtElementData *);
  
  // To change the size of the label
  virtual void setSize (int value, int verticalOffset);
  virtual int  getSize () const;
  
  virtual void addCallback(SoCallbackListCB * function, void * data);
  virtual void removeCallback(SoCallbackListCB * function, void * data);
  
  static const int toggleSize;
  static const int editSize;
  
 protected:  
  PoXtSliderData(const char * label=NULL, 
                 TriggerMode mode=MOUSE_ON_RELEASE_TRIGGER);
  PoXtSliderData (const PoXtSliderData &);
  
  // Update numeric field with slider value by raising slider callback
  virtual void updateNumericField(float value);
  
  virtual void changeSliderValue();
  virtual void invokeCallbacks();
  
  SoCallbackList * _sliderCallback;
  
  static void handleCallback (void *, float);
  static void updateEditCallback (void *, float);
  
  PoXtCustomSlider * _slider;
  PoEdit      * _edit;
  PoButton    * _toggle;
  PoXtLabelData * _label;
  
  TriggerMode _triggerMode;
  
 private:
  void buildNumericField(SoWidget Parent);
  void buildToggle(SoWidget Parent);
  void redrawNumericField();
  void redrawToggle();
  
  void redraw ();
  
  static void toggleCallback (void *, void *);
  static void editCallback   (void *, void *);
  
  int _verticalOffset;
  int _horizontalOffset;
  int _size;
  int _height;

  SbBool _isFixedLimits ;
  
  SbBool _numberVisible;        // whether numeric field is visible
#endif
};

#endif //_PO_XT_SLIDER_DATA_H_


