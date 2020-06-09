/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _PO_XT_TOGGLE_BUTTON_DATA_H
#define _PO_XT_TOGGLE_BUTTON_DATA_H

#ifndef _WIN32
#include <X11/Intrinsic.h>
#include <Xm/ToggleB.h>
#else
class SoCallbackList;
class PoButton;
#endif
#include <Inventor/dialog/PoXtElementData.h>

#include <Inventor/SbString.h>

class PoXtLabelData;

/**
 * @VSGEXT Class to define a toggle button. 
 * 
 * @ingroup DialogM
 * 
 * @DESCRIPTION
 *    @deprecated Please use DialogViz classes for new development.
 *
 *    This element is composed of a string on the left, a toggle button in the 
 *    center, and a string associated to the state of the toggle on the right. By 
 *    default the text of the label, the two strings associated to the state of 
 *    the toggle button are empty and the state of the toggle button is OFF.
 * 
 */
class INVENTORW_API PoXtToggleButtonData : public PoXtElementData
{

 public:

  /**
   *  Type of toggle state.
   */
  enum State
  {
    ON,
    OFF
  } ;

  /**
   * Constructor
   */
  PoXtToggleButtonData(const SbString& label = "", 
                       State state = OFF,
                       const SbString& onString  = "", 
                       const SbString& offString = "");

  /**
   * Destructor.
   */
  virtual ~PoXtToggleButtonData();

  /**
   * Sets the text of the label on the left of toggle button
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setLabel(const char * label);

  /**
   * Sets the text of the label on the left of toggle button
   */
  void setLabel(const SbString& label);

  /**
   * Gets the text of the label on the left of toggle button
   */
  SbString getLabel() const;

  /**
   * Sets a string for the given state.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setString(State state, const char * str);

  /**
   * Sets a string for the given state.
   */
  void setString( State state, const SbString& str );

  /**
   * Gets the string of the given state.
   */
  SbString getString(State state) const;

  /**
   * Sets the state of the toggle button.
   */
  void setState(State state);

  /**
   * Gets the state of the toggle button.
   */
  State getState() const;

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
  virtual void addCallback(SoCallbackListCB * function, void * data);
  virtual void removeCallback(SoCallbackListCB * function, void * data);

  // affect the data of current objet to xtElement
  virtual void updateValues(const PoXtElementData * xtElement);

  // minimum width for the widget in fact this represent the width of the label
  // The mimimum width for a widget whith no label will be 0
  virtual int  getRealMinWidgetWidth() const;
  // in fact set the label width, it's a pixel value
  virtual void setMinWidgetWidth(int value);

 protected:
  PoXtToggleButtonData(const PoXtToggleButtonData & toggle);


 private:
  void attachLabelWidget();
  static void handleCallback(SoWidget button, 
                             PoXtToggleButtonData *userData, 
                             XmToggleButtonCallbackStruct *data);

  SbString _stringOn, _stringOff;
  State _state;
  PoXtLabelData * _label;

  SoWidget _labelWidget, _toggleWidget;
  SoCallbackList * _toggleCallback;
#else
 SoINTERNAL public:
  virtual void buildWidget (SoWidget parent, int verticalOffset);
  
  virtual void updateValues (const PoXtElementData *);
  
  virtual void addCallback (SoCallbackListCB * f, void * data);
  virtual void removeCallback (SoCallbackListCB * f, void * data);
  
  // To change the size of the label
  void setSize (int value, int verticalOffset);
  int  getSize () const;
  
 protected:
  PoXtToggleButtonData (const PoXtToggleButtonData & button);
  
 private:
  static void handleCallback (void * button, void * theToggle);
  static void changedStateCallback (void * button, void * theToggle);
  
  PoXtLabelData * _label;
  PoButton * _button;
  int _buttonOffset;
  
  SbString* _stateStrings;
  State _state;
  
  SoCallbackList *_toggleCallback;
#endif
};

#endif //_PO_XT_TOGGLE_BUTTON_DATA_H

