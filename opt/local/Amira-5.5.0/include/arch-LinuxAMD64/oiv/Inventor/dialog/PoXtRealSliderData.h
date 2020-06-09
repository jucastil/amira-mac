/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _PO_XT_REAL_SLIDER_DATA_H
#define _PO_XT_REAL_SLIDER_DATA_H

#include <Inventor/dialog/PoXtSliderData.h>

/**
 * @VSGEXT Class to define an real slider. 
 * 
 * @ingroup DialogM
 * 
 * @DESCRIPTION
 *    @deprecated Please use DialogViz classes for new development.
 *
 *    An real slider is a slider where the values are reals. By default 
 *    the limits of the slider are [0-1] and the initial value is 0.
 * 
 */
class INVENTORW_API PoXtRealSliderData : public PoXtSliderData
{

 public:

  /**
   * Constructor
   */
  PoXtRealSliderData(const char *label=NULL, 
                     float min=0, float max=1, float initVal=0, 
                     TriggerMode mode=MOUSE_ON_RELEASE_TRIGGER);

  /**
   * Destructor.
   */
  virtual ~PoXtRealSliderData();

  /**
   * Sets the real value of the slider. 
   * If the user enters a value greater or less than the limits of the slider 
   * in the numerical field, the corresponding limit is updated to 
   * this value.
   */
  void setValue(float value);

  /**
   * Gets the real value of the slider.
   */
  float getValue() const;

  /**
   * Sets the limits of the slider. Update the slider thumb position.
   * If the current value is not beetween the new limit, 
   * the current value is set to the minimal or maximum value, 
   * and a event is raised.
   */
  void setLimit(float min, float max);

  /**
   * Gets the limits of the slider.
   */
  void getLimit(float & min, float & max) const;

  /**
   * Returns the type of the Xt element.
   */
  virtual TypeXtElement getType() const;

  /**
   * Creates and returns a new Xt element which is a copy of this Xt element.
   */
  virtual PoXtElementData * copy() const;

  /*----------------------------------------------------------------------------*/

#ifndef _WIN32
 SoINTERNAL public:
  virtual SoWidget buildWidget(SoWidget parent);
  virtual void handleTextFieldCallback(SoWidget w);

  // affect the internal data xtElement to current object
  // xtElement have to be PoXtRealSliderData
  virtual void updateValues(const PoXtElementData * xtElement);

  // Callback function for treat the redraw of numeric field when the slider 
  // thumb position changed.
  virtual void valueChangedCallback(PoXtSliderData * slider, 
                                    float * thumbPosition);
  // Callback for treat when the mouse button is released
  virtual void releaseCallback(PoXtSliderData * slider, 
                               float * thumbPosition);
  // Callback function for update the numeric field when the callback
  // have to raise on release mouse button
  virtual void updateNumericFieldCallback(PoXtSliderData * slider, 
                                          float * thumbPosition);

 protected:
  PoXtRealSliderData(const PoXtRealSliderData & slider);
  // get the callback raise by slider to display the value of Text widget
  // Here draw the float value.
  virtual void drawTextField(SoWidget textWidget);

 private:
  float _valueMax, _valueMin;
  float _value;
#else
 SoINTERNAL public:
  virtual void buildWidget (SoWidget parent, int verticalOffset);

  virtual void updateValues (const PoXtElementData *);  
  
 protected:
  PoXtRealSliderData (const PoXtRealSliderData &);
  
  // Method called by the callback to update the edit SoWidget
  virtual void updateNumericField (float value);  
  virtual void changeSliderValue ();
  virtual void invokeCallbacks ();
  
 private:
  void initSliderValue ();
  void drawText ();

  float _valueMax, _valueMin;
  float _value, _oldValue;
#endif
};

#endif //_PO_XT_REAL_SLIDER_DATA_H




