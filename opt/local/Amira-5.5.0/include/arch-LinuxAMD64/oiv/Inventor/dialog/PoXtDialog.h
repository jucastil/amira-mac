/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _PO_XT_DIALOG_H
#define _PO_XT_DIALOG_H

#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/SoXtComponent.h>
#include <Inventor/dialog/PoXtElementData.h>

class PoXtElementData;
class SoCallbackList;
#ifdef _WIN32
class PoDialog;
class PoStatic;
#endif

/**
 * @VSGEXT Class to build a generalized dialog box.
 * 
 * @ingroup DialogM
 * 
 * @DESCRIPTION
 *    @deprecated Please use DialogViz classes for new development.
 *
 *    Class to build a generalized dialog box which can contain real sliders,  
 *    integer sliders, toggle buttons, choice buttons, trigger buttons, labels, 
 *    and editable texts. The type of the elements (called Xt elements) contained 
 *    in the dialog box are specified by the application and all these elements 
 *    are displayed underneath each other. The Xt elements in the dialog box are
 *    indexed from 0 (at the top of the dialog box) to N - 1 (at the bottom of 
 *    the dialog box), N is the number of Xt elements.
 *    
 *    One or several \oivnetdoc delegates \else callbacks \endoivnetdoc can be attached to this dialog box. These 
 *    \oivnetdoc delegates \else callbacks \endoivnetdoc are called each time one of its Xt elements receives 
 *    a keyboard or a mouse event.
 *
 *    Win32 note: This component can't be displayed embedded within an MFC panel.
 * 
 *    RESOURCES
 * <PRE>
 *    Resources for dialog box:
 *    *PoXtDialog.dialogForm            Form widget of the dialog box.
 *    *PoXtDialog.dialogForm.Frame      Frame widget of each Xt element.
 *    
 *    Resources for Xt elements:
 *    *PoXtDialog.dialogForm.Frame.< Name of the Xt element resource >
 *    < Name of the Xt element resource > is a form widget.
 *    Example for slider resources: *PoXtDialog.dialogForm.Frame.PoXtSlider
 *    
 *    Resources for sliders:
 *    *PoXtSlider.PoXtLabel             Cf PoXtLabel resources.
 *    *PoXtSlider.sliderText            Text widget.
 *    *PoXtSlider.toogle                Toggle widget.
 *    
 *    Resources for trigger buttons:
 *    *PoXtTriggerButton.PoXtLabel      Cf PoXtLabel resources.
 *    *PoXtTriggerButton.trigger        Button widget.
 *    
 *    Resources for toggle buttons:
 *    *PoXtToggleButton.PoXtLabel       Cf PoXtLabel resources.
 *    *PoXtToggleButton.toogle          Toggle widget.
 * 
 *    Resources for edit texts:
 *    *PoXtEditText.PoXtLabel           Cf PoXtLabel resources.
 *    *PoXtEditText.editText            Text widget.
 *    
 *    Resources for choice buttons:
 *    *PoXtChoiceButton.choiceList                                      Form widget.
 *    *PoXtChoiceButton.choiceList.choiceListArrow                      Arrow widget.
 *    *PoXtChoiceButton.choiceList.choiceListEdit                       Text widget.
 *    *PoXtChoiceButton.choiceList.choiceListPopup                      Popup shell widget.
 *    *PoXtChoiceButton.choiceList.choiceListPopup.ChoiceListListPopup  Scrolled list widget.
 *    
 *    Resources labels:
 *    *PoXtLabel.label                  Text widget.
 * </PRE>
 * 
 */
class INVENTORW_API PoXtDialog : public SoXtComponent
{

 public:



  /**
   * Dialog callback data structure. 
   * 
   * @ingroup DialogM
   * 
   * @DESCRIPTION
   *
   * Contains which Xt element of which dialog box received the event.
   * This structure is used as an argument of the call back of PoXtDialog.
   * Dialog callback data structure.
   *
   * @SEE_ALSO
   *   PoXtDialog
   *
   */
  struct PoXtDialogDataCB

  {

    /**
     * Pointer to the dialog box.
     */
    PoXtDialog * dialog; 

    /**
     * Index of the Xt element which has received the event.
     */
    int widgetNumber;    

  }; 



  /**
   * Prototype of the callBack function.
   */
  typedef void PoXtDialogCB(void * userData, 
                            const PoXtDialogDataCB * data);

 public:

  /**
   * Constructor specifying the number and the list of 
   * the Xt elements to be built inside the dialog box.
   */
  PoXtDialog(SoWidget parent = NULL, 
             const char * name = NULL,
             SbBool buildInsideParent = TRUE,
             int numXtElt = 0, 
             const PoXtElementData ** elts = NULL);

  /**
   * Destructor.
   */
  ~PoXtDialog();



  /**
   * Sets the number and the list of Xt elements to build/be built inside the 
   * dialog box.
   */
  void setValues(int numXtElt, const PoXtElementData ** elts);

  /**
   * Gets the number and the list of Xt elements to build/be built inside the 
   * dialog box.
   */
  const PoXtElementData ** getValues(int & numXtElt) const;

  /**
   * Sets the index'th Xt element in the dialog box.
   */
  void set1Value(int index, const PoXtElementData * elt);

  /**
   * Gets the index'th Xt element in the dialog box. Returns NULL if index is invalid.
   * Although the pointer  returned by get1Value is constant, the application can  
   * call all the methods of PoXtElementData class (and its derived class). 
   * Be careful, changing a label by using the method PoXtElementData::setLabel can 
   * cause the dialog box to no longer be aligned. In this case, use the set1Value 
   * method to force the dialog box to be re-aligned (see example 2 below).
   * In any case, you must not delete the pointer returned by get1Value. 
   * <PRE>
   *   Example 1:
   *   // Example to change the value of a real slider to 0.5
   *   // using the method get1Value
   *   ,...
   *   PoXtRealSliderData *slider = (PoXtRealSlider *
   *   dialog->get1Value(SLIDER_INDEX);
   *   slider->setValue(0.5) ;
   *   ,...
   *   
   *   Example 2:
   *   // Example to change the value of a real slider to 0.5
   *   // using the method set1Value
   *   ,...
   *   PoXtRealSliderData *slider = (PoXtRealSlider *
   *   dialog->get1Value(SLIDER_INDEX).copy() ;
   *   slider->setValue(0.5) ;
   *   dialog->set1Value(SLIDER_INDEX, (PoXtElementData *)slider) ;
   *   ,...
   * </PRE>
   */
  const PoXtElementData * get1Value(int index) const;

  /**
   * Inserts the specified Xt element at the specified index.
   */
  void insert1Value(int index, const PoXtElementData * elt);

  /**
   * Inserts numElt Xt elements at the specified index.
   */
  void insertNValues(int index, int numElt, const PoXtElementData ** elt);

  /**
   * Deletes the Xt element at the specified index.
   */
  void delete1Value(int index);

  /**
   * Deletes numElt Xt elements from the specified index.
   */
  void deleteNValues(int index, int numElt);

  /**
   * Specifies if the dialog box is resized when Xt elements are inserted or 
   * suppressed (each Xt element keeps the same size in the dialog box), or if the 
   * window keeps its size whatever insertions or removals there may be (each 
   * XtElement becomes smaller or larger).
   */
  void windowResizeByXtElement(SbBool flag);

  /**
   * Indicates if the window is resized or not when Xt elements are inserted or 
   * removed.
   */
  SbBool isWindowResizeByXtElement() const;

  /**
   * Sets vertical scroll bar visibility. By default, there is no vertical scrollbar.
   */
  void setVerticalScrollbar(SbBool visible);

  /**
   * Gets vertical scroll bar visibility.
   */
  SbBool isVerticalScrollbar() const;

  /**
   * Adds callbacks which are called each time an Xt element receives a 
   * keyboard or a mouse event.
   */
  void addValueChangedCallback(PoXtDialogCB * function, 
                               void * userData = NULL);

  /**
   * Removes callbacks which are called each time an Xt element receives a 
   * keyboard or a mouse event.
   */
  void removeValueChangedCallback(PoXtDialogCB * function, 
                                  void * userData = NULL);

  /**
   * Shows the component. If this is a topLevelShell component, then show() 
   * will Realize and Map the window, otherwise it will simply Manage the 
   * widget. 
   * In addition, show() will also pop the component window to the top
   * and de-iconify if necessary, to make sure the component is
   * visible by the user.
   */
  virtual void show();

  /**
   * Hides the component. Calls the appropriate unmap or unmanage routines.
   */
  virtual void hide();
 protected:


  virtual SbString getDefaultWidgetName() const;
  virtual SbString getDefaultTitle() const;
  virtual SbString getDefaultIconTitle() const;
  // redefine generic virtual functions for title and IconTitle

#ifdef _WIN32
  virtual void redraw ();
#endif

 private:
#ifndef _WIN32
  SoWidget buildWidget(SoWidget parent);

  // locate all xtElement on the dialog box
  int attachElement(int hightPosition, int indice);


  // it 's use before insert or delete an element
  void beforeUpdateElement();
  // it 's use after insert or delete an element, heightEltChanged is the 
  // height of element number inserted (positive value) or 
  // deleted (negative value)
  void afterUpdateElement(int heightEltChanged=0);


  SbBool _isScrollBar;
  int _numberXtElement;
  int _maxXtElement;
  int _heightDialog;
  // it's the form maximum height whithout risizing 
  //  Dimension _maxHeightForm;
  int _maxWidthLabel;
  SoWidget _baseWidget, _scrollWidget, *_frame;
  SoWidget _areaWidget, _verticalScrollWidget;
  
  SoCallbackList * _callback;

  PoXtElementData ** _listXtElement;
  int _spaceBetweenElement;
  SbBool _windowResizeByXtElement;


  // For the data come from each XtElement callback
  PoXtDialogDataCB **_userData;
  static void handleCallback(PoXtDialogDataCB * dataCB, void * value);

  static void resizeArea(SoWidget, PoXtDialog * dialog, XtPointer notUse);
  static void expose(SoWidget w, PoXtDialog * dataUser, 
                     XEvent * event, Boolean * contDispatch);
  //XmDrawingAreaCallbackStruct *data);
#else
  void buildWidget (SoWidget parent);
  void buildElements ();
  void buildElement  (int, int);
  void initElementsPos ();
  void insertValue (int index, const PoXtElementData * elt);
  void deleteValue (int index);

  
  static void handleCallback (void * element, void * value);
  static void resizeCallback (void * dialog, void * userData, 
                              int width, int height);
  
  void freeXtElementArray ();
  void initXtElementArray (const PoXtElementData **);
  
  int _xtElementNumber;
  PoXtElementData ** _xtElementArray;
  int _arraySize;
  
  SoWidget _dialogWidget;
  PoDialog * _dialog;
  SbBool _windowResize;
  
  int _dialogHeight;
  int _maxLabelSize;
  
  SoCallbackList * _callbackList;
  
  // For the data came from each XtElement callback
  PoXtDialogDataCB ** _userData;
  // Array of frames
  PoStatic ** _frameArray;
#endif
};

#endif //_PO_XT_DIALOG_H


