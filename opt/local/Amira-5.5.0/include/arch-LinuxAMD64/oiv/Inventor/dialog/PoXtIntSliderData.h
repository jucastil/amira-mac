/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _PO_XT_INT_SLIDER_DATA_H
#define _PO_XT_INT_SLIDER_DATA_H

#include <Inventor/dialog/PoXtSliderData.h>

/**
 * @VSGEXT Class to define an integer slider. 
 * 
 * @ingroup DialogM
 * 
 * @DESCRIPTION
 *    @deprecated Please use DialogViz classes for new development.
 *
 *    An integer slider is a slider where the values are integers. By default 
 *    the limits of the slider are [0-1] and the initial value is 0.
 * 
 */
class INVENTORW_API PoXtIntSliderData : public PoXtSliderData
{

 public:

  /**
   * Constructor
   */
  PoXtIntSliderData(const char * label=NULL, 
                    int min=0, int max=1, int initVal=0, 
                    TriggerMode mode=MOUSE_ON_RELEASE_TRIGGER);

  /**
   * Destructor.
   */
  virtual ~PoXtIntSliderData();

  /**
   * Sets the integer value of the slider. 
   * If the user enters a value greater or less than the limits of the slider 
   * in the numerical field, the corresponding limit is updated to 
   * this value.
   */
  void setValue(int value);

  /**
   * Gets the integer value of the slider.
   */
  int  getValue() const;

  /**
   * Sets the limits of the slider. Update the slider thumb position.
   * If the current value is not beetween the new limit, 
   * the current value is set to the minimal or maximum value, 
   * and a event is raised.
   */
  void setLimit(int min, int max);

  /**
   * Gets the limits of the slider.
   */
  void getLimit(int & min, int & max) const;

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
  // xtElement have to be PoXtIntSliderData
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
  PoXtIntSliderData(const PoXtIntSliderData & slider);
  // get the callback raise by slider to display the value of Text widget
  // Here draw the int value
  virtual void drawTextField(SoWidget numberWidget);


 private:
  int _valueMax, _valueMin;
  int _value;
#else
 SoINTERNAL public:
  virtual void buildWidget(SoWidget parent, int verticalOffset);
  
  virtual void updateValues(const PoXtElementData *);
  
 protected:
  PoXtIntSliderData(const PoXtIntSliderData &);
  
  // Method called by callbacks to update the edit widget
  virtual void updateNumericField(float value);  
  virtual void changeSliderValue();
  virtual void invokeCallbacks();
  
 private:
  void initSliderValue();
  void drawText();
  
  int _valueMax, _valueMin;
  int _value, _oldValue;
#endif
};

#endif //_PO_XT_INT_SLIDER_DATA_H

