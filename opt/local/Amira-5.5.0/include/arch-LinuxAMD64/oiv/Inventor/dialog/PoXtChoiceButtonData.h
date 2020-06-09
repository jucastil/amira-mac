/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _PO_XT_CHOICE_BUTTON_DATA_H
#define _PO_XT_CHOICE_BUTTON_DATA_H

#ifndef _WIN32
#  include <X11/Intrinsic.h>
#endif
#include <Inventor/dialog/PoXtElementData.h>

class SoCallbackList;
class PoXtLabelData;
class ChoiceList;
class PoChoice;

/**
 * @VSGEXT Class to define a choice button. 
 * 
 * @ingroup DialogM
 * 
 * @DESCRIPTION
 *    @deprecated Please use DialogViz classes for new development.
 *
 *    This element is composed of a label on the left and a choice button on 
 *    the right. By default the text of the label is an empty string, and the number 
 *    of items and the selected item are equal to zero.
 * 
 */
class INVENTORW_API PoXtChoiceButtonData : public PoXtElementData
{

 public:



  /**
   * Constructor
   */
  PoXtChoiceButtonData(const char * label=NULL, 
                       int numItems=0, 
                       const char ** itemNames=NULL,
                       int selectedItem=0);

  /**
   * Destructor.
   */
  virtual ~PoXtChoiceButtonData();

  /**
   * Sets the text of the label on the left of the choice button.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setLabel(const char * label);

  /**
   * Sets the text of the label on the left of the choice button.
   */
  void setLabel(const SbString& label);

  /**
   * Gets the text of the label on the left of the choice button.
   */
  //const char * getLabel() const;
  SbString getLabel() const;

  /**
   * Sets items names of the choice button.
   */
  void setItems(int numItems, const char ** itemNames);

  /**
   * Gets items names of the choice button.
   */
  const char ** getItems(int & numItems) const;

  /**
   * Sets the selected item number.
   */
  void setSelectedItem(int itemNumber);

  /**
   * Gets the selected item number.
   */
  int getSelectedItem() const;

  /**
   * Returns the type of the Xt element.
   */
  virtual TypeXtElement getType() const;

  /**
   * Creates and returns a new Xt element which is a copy of this Xt element.
   */
  virtual PoXtElementData * copy() const;

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:

  virtual void updateValues(const PoXtElementData * xtElement);
  // affect the data of current objet to xtElement

  virtual void addCallback(SoCallbackListCB * function, void * data);
  virtual void removeCallback(SoCallbackListCB * function, void * data);

#ifndef _WIN32
  virtual SoWidget buildWidget(SoWidget parent);
  virtual void setPositionElementIfResize();

  virtual int  getRealMinWidgetWidth() const;
  // minimum width for the widget in fact this represent the width of the label
  // The mimimum width for a widget whith no label will be 0, it's a pixel 
  // value

  virtual void setMinWidgetWidth(int value);
  // in fact, set the width of label, it's a pixel value
#else
  virtual void buildWidget (SoWidget parent, int verticalOffset);

  virtual void setSize (int value, int verticalOffset);
  virtual int  getSize () const;
  // To change the size of the label
#endif

 protected:
  PoXtChoiceButtonData(const PoXtChoiceButtonData & choice);

#ifdef _WIN32
  virtual void redraw ();
#endif

 private:

  char ** _choiceStr;
  int _nbItem;
  int _currentItem;

  PoXtLabelData * _label;

  SoCallbackList * _choiceCallback;

#ifndef _WIN32
  static void handleCallback(PoXtChoiceButtonData * userData, 
                             int * currentItemPosition);
  void buildChoiceWidget();
  void attachLabelWidget();
  SoWidget _labelWidget, _choiceWidget;
  ChoiceList * _choiceList;
#else
  void deleteSelection ();  
  static void handleCallback (void *, void *);
  PoChoice * _choice;
  int _height;
  int _choiceOffset;
  int _verticalOffset;
  int _size;
#endif

};

#endif //_PO_XT_CHOICE_BUTTON_DATA_H

