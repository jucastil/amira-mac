/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _PO_XT_TRIGGER_BUTTON_DATA_H
#define _PO_XT_TRIGGER_BUTTON_DATA_H

#ifndef _WIN32
#include <X11/Intrinsic.h>
#include <Xm/PushB.h>
#else
class SoCallbackList;
class PoButton;
#endif
#include <Inventor/dialog/PoXtElementData.h>

#include <Inventor/SbString.h>

class PoXtLabelData;

/**
 * @VSGEXT Class to define a trigger button.
 * 
 * @ingroup DialogM
 * 
 * @DESCRIPTION
 *    @deprecated Please use DialogViz classes for new development.
 *
 *    This element is composed of a label on the left and by a button. By 
 *    default the text of the label and the text of the button is an empty string.
 * 
 */
class INVENTORW_API PoXtTriggerButtonData : public PoXtElementData
{

 public:

  /**
   * Constructor
   */
  PoXtTriggerButtonData( const SbString& label = "",
                         const SbString& buttonLabel = "" );

  /**
   * Destructor.
   */
  virtual ~PoXtTriggerButtonData();

  /**
   * Sets the text of the label on the left of the button.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setLabel(const char * label);

  /**
   * Sets the text of the label on the left of the button.
   */
  void setLabel( const SbString& label );

  /**
   * Gets the text of the label on the left of the button.
   */
  SbString getLabel() const;

  /**
   * Sets the label of the button.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setButtonLabel(const char * label);

  /**
   * Sets the label of the button.
   */
  void setButtonLabel(const SbString& label);

  /**
   * Gets the label of the button.
   */
  SbString getButtonLabel() const;

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
  virtual void setMinWidgetWidth(int value);

 protected:
  PoXtTriggerButtonData(const PoXtTriggerButtonData & trigger);

 private:
  void attachLabelWidget();
  static void handleCallback(SoWidget button, 
                             PoXtTriggerButtonData * userData, 
                             XmPushButtonCallbackStruct * data);
  SbString _buttonLabel;
  PoXtLabelData * _label;

  SoWidget _labelWidget, _buttonWidget;
  SoCallbackList * _triggerCallback;
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
  PoXtTriggerButtonData (const PoXtTriggerButtonData & button);
  
 private:
  static void handleCallback (void * button, void * theTrigger);
  
  PoXtLabelData * _label;
  PoButton * _button;
  int _buttonOffset;
  
  SoCallbackList *_triggerCallback;
#endif
};

#endif //_PO_XT_TRIGGER_BUTTON_DATA_H

