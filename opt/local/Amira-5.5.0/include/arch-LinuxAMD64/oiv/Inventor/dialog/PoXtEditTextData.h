/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _PO_XT_EDIT_TEXT_DATA_H
#define _PO_XT_EDIT_TEXT_DATA_H

#if defined(WIN32)
class PoEdit;
#endif

#include <Inventor/dialog/PoXtElementData.h>
#include <Inventor/SbString.h>

class PoXtLabelData;
class SoCallbackList;
#ifdef _WIN32
class PoEdit;
#endif

/**
 * @VSGEXT Class to define an editable text. 
 * 
 * @ingroup DialogM
 * 
 * @DESCRIPTION
 *    @deprecated Please use DialogViz classes for new development.
 *
 *    This element is composed of a label on the left and by an editable text 
 *    on the right. By default the text of the label and of the editable text are 
 *    empty strings and the number of characters to read is 10.
 * 
 */
class INVENTORW_API PoXtEditTextData : public PoXtElementData
{

 public:

  /**
   * Constructor
   */
  PoXtEditTextData(const SbString& label = "", 
                   const SbString& defaultString = "",
                   int numCharToRead = 10);


  /**
   * Destructor.
   */
  virtual ~PoXtEditTextData();

  /**
   * Sets the text of the label on the left of editable text.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setLabel(const char * label);

  /**
   * Sets the text of the label on the left of editable text.
   */
  void setLabel(const SbString& label);

  /**
   * Gets the text of the label on the left of editable text.
   */
  SbString getLabel() const;

  /**
   * Sets the string of the editable text.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setString(const char * label);

  /**
   * Sets the string of the editable text.
   */
  void setString(const SbString& label);

  /**
   * Gets the string of the editable text.
   */
  SbString getString() const;

  /**
   * Sets the number of character to read. When the enter key is pressed or when 
   * the number of characters to read is reached, this element triggers the 
   * corresponding \oivnetdoc delegate \else callback \endoivnetdoc.
   */
  void setNumCharToRead(int number);

  /**
   * Gets the number of character to read. 
   */
  int getNumCharToRead() const;

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
  // The mimimum width for a widget whith no label will be 0, it's a pixel 
  // value
  virtual int  getRealMinWidgetWidth() const;

  // in fact, set the width of label, it's a pixel value
  virtual void setMinWidgetWidth(int value);

  virtual void setPositionElementIfResize();

 protected:
  PoXtEditTextData(const PoXtEditTextData & edit);

 private:
  void attachLabelWidget();

  // Callback call when the user invoke an activate event
  static void handleCallbackEnter(SoWidget textWidget, 
                                  PoXtEditTextData * userData, 
                                  XtPointer * data);

  // Callback call when the user give _nbCharToRead character into text SoWidget
  static void handleCallbackCharMax(SoWidget text, 
                                    PoXtEditTextData * userData, 
                                    XtPointer * data);
  int _nbCharToRead;

  SoWidget _labelWidget, _textWidget;
  SoCallbackList * _textCallback;
  PoXtLabelData * _label;
  char * _editTextStr;
#else
 SoINTERNAL public:
  virtual void buildWidget (SoWidget parent, int verticalOffset);
  
  virtual void updateValues (const PoXtElementData *);
  
  // To change the size of the label
  void setSize (int length, int verticalOffset);
  int  getSize () const;
  
  virtual void addCallback (SoCallbackListCB *f, void *data);
  virtual void removeCallback (SoCallbackListCB *f, void *data);
  
 protected:
  PoXtEditTextData (const PoXtEditTextData &);
  
 private:
  static void handleCallback (void * edit, void * theEdit);
  static void updateCallback (void * edit, void * theEdit);
  
  PoXtLabelData * _label;
  PoEdit * _edit;
  
  int _editOffset;
  int _height;
  SbBool _changedValue;
  
  int _maxCharNumber;  
  SoCallbackList *_editCallback;
#endif
};

#endif //_PO_XT_EDIT_TEXT_DATA_H

